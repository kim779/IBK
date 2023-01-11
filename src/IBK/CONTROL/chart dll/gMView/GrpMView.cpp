// GrpMView.cpp : implementation file
//

#include "stdafx.h"
#include "axisgmview.h"
#include "GrpMView.h"
#include "PnInput.h"
#include "PnCtrl.h"
#include "ConfigBarMulti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRLEN	8
#define	MAX_TRKEY	MAX_MMAPY*MAX_MMAPX

#define	TIMER_ID	10001
#define	TIMER_GAP	300

#define COLOR_OUT	RGB(0, 81, 142)
#define COLOR_IN	RGB(255, 255, 255)

/////////////////////////////////////////////////////////////////////////////
// CGrpMView

CGrpMView::CGrpMView(CWnd* pwndView, char* pcDllName)
{
	m_pApp = (CAxisGMViewApp*)AfxGetApp();
	m_pwndView	= pwndView;
	strcpy(m_acDllName, pcDllName);

	m_pwndView = pwndView;
	m_pwndInput = NULL;
	m_pwndCtrl = NULL;
	m_pCfg = NULL;
	m_mapChart.RemoveAll();

	m_idUnit = GU_CODE;
	m_pActiveChart = NULL;
	m_pMultiChartInfo = NULL;
	m_bDominoExist = false;

	ZeroMemory(&m_DummyGraph, SZ_DUMMYGRAPH);
	m_DummyGraph.graph.wGKind = GK_JPN;

	m_rcOrgChart.SetRectEmpty();
	m_rcChart.SetRectEmpty();
	m_bAutotran	= false;
	m_bTransaction = false;
	m_iAutoTRCnt = 0;
	m_trSender = NULL;
}

CGrpMView::~CGrpMView()
{
	if (m_pCfg)	
		LIB_DELETE(m_pCfg);
	if (m_pwndInput)
		LIB_DELETE(m_pwndInput);
	if (m_pwndCtrl)		
		LIB_DELETE(m_pwndCtrl);
	if (m_pMultiChartInfo)
		LIB_DELETE(m_pMultiChartInfo);		

	ClearChart();
}


BEGIN_MESSAGE_MAP(CGrpMView, CWnd)
	//{{AFX_MSG_MAP(CGrpMView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnMessage)
	ON_MESSAGE(GEV_VIEW, OnViewEvent)
	ON_MESSAGE(GEV_CHART, OnChartEvent)
	ON_MESSAGE(GEV_INPUT, OnInputEvent)
	ON_MESSAGE(GEV_CTRL, OnCtrlEvent)
	ON_MESSAGE(GEV_CFG, OnCfgEvent)
	ON_MESSAGE(UM_FROM_MAIN, OnFromMain)
	ON_MESSAGE(WM_VIEW_SENDTR, OnViewSendTR)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGrpMView message handlers

int CGrpMView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ReadHistory();
	InitView();

	m_timerID = TIMER_ID;
	SetTimer(m_timerID, TIMER_GAP, NULL);

	return 0;
}

void CGrpMView::OnDestroy() 
{
	SaveMultiInfo();

	if (m_pCfg)
	{
		m_pCfg->DestroyWindow();
		delete m_pCfg;
		m_pCfg = NULL;
	}

	if (m_timerID)	
	{
		KillTimer(m_timerID);
		m_timerID = 0;
	}

	//m_pwndView->SendMessage(WM_USER, MAKEWPARAM(revokeDLL, 0), NULL);

	CWnd::OnDestroy();
}

void CGrpMView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	if (cx == 0 && cy == 0)
		return;

	ResizeWnd(CRect(0, 0, cx, cy));
}

void CGrpMView::OnPaint() 
{
/*	CPaintDC dc(this); // device context for painting

	CPen	*cPen = m_pApp->GetPen(m_pwndView, PS_SOLID, 1, RGB(0,0,0));
	CPen	*sPen = dc.SelectObject(cPen);
	dc.MoveTo(m_rcOrgChart.left, m_rcOrgChart.top);
	dc.LineTo(m_rcOrgChart.right, m_rcOrgChart.top);
	dc.SelectObject(sPen);
*/
	CPaintDC dc(this); // device context for painting
	
	CRect crc, rc;
	GetClientRect(crc);

	DWORD bkColor = m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), 64);
	dc.FillSolidRect(crc, bkColor);

	rc = crc;
	rc.top += HEIGHT_INPUT;
	int iGabCfg = GetControlShow(PN_CFG)? WIDTH_CFG:0;

	CPen pn(PS_NULL, 1, m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), 181));
	CPen	*sPen = dc.SelectObject(&pn);

	if (iGabCfg != 0)
	{
		rc.left += iGabCfg + 10 + 2;
		rc.InflateRect(-1,-2, 0, -2);
		dc.RoundRect(rc,CPoint(5,5));

		rc.SetRect(crc.left, HEIGHT_INPUT, iGabCfg + 8, crc.bottom);
		rc.InflateRect(-1,-2, 1, -2);
		dc.RoundRect(rc,CPoint(5,5));
	}
	else
	{
		rc.InflateRect(-1,-2, 0, -2);
		dc.RoundRect(rc,CPoint(5,5));
	}

	dc.SelectObject(sPen);
}

BOOL CGrpMView::OnEraseBkgnd(CDC* pDC) 
{
	return true;
//	return CWnd::OnEraseBkgnd(pDC);
}

void CGrpMView::OnSetFocus(CWnd* pOldWnd) 
{
	if (m_pwndInput)
		m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(inputViewFocus, 0), 1);

	CWnd::OnSetFocus(pOldWnd);
}

void CGrpMView::OnKillFocus(CWnd* pNewWnd) 
{
	if (m_pwndInput)
		m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(inputViewFocus, 0), 0);

	CWnd::OnKillFocus(pNewWnd);
}

LRESULT CGrpMView::OnMessage(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	if (LOWORD(wParam) == invokeTRx)	// ��Ʈ�� TR ��û�̹Ƿ� Wizard���� ����
	{
		return m_pwndView->SendMessage(WM_USER, wParam, lParam);
	}

	switch (LOBYTE(LOWORD(wParam)))
	{
	case DLL_OUB:		// Tran Data
		if (HIBYTE(LOWORD(wParam)) <= MAX_TRKEY)	// ��ƮTR �����̹Ƿ� ��Ʈ���� ����
			return MultiOub(wParam, lParam);
		return Oub(wParam, lParam);
		break;
	case DLL_ALERT:		// RealTime
		if (!m_bAutotran)
			MultiAlert(wParam, lParam);
		break;
	case DLL_TRIGGER:	// Trigger
		// 2009.11.02 : RESTORE : �� ��Ʈ���� ���� Ʈ���� ��� ����
		if (m_pwndInput && !m_bAutotran)
			m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, triggerCode), lParam);
		break;
//		if (m_pwndInput && !m_bAutotran)
//			m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, triggerCode), lParam);

		break;
	case DLL_DOMINO:	// Domino
		m_bDominoExist = true;
		if (m_pwndInput && !m_bAutotran)
			m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, domminoCode), lParam);
		break;
	case DLL_DROP:		// OnDrop
		OnDrop(wParam, lParam);
		break;
	case DLL_INVOKE:
		// axisAP.h
		break;
	case DLL_SETPAL:	// Change Palette
		if (m_pwndInput)	m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(inputChgPalette, 0), 0);
		if (m_pCfg)	m_pCfg->ChangePalette();
		MultiAllMsg(WM_USER, wParam, lParam);
		break;
	case DLL_SETFONT:
		MultiAllMsg(WM_USER, wParam, lParam);
		break;
	case DLL_SETFCB:
		MultiAllMsg(WM_USER, wParam, lParam);
		break;
	}
	return TRUE;
}

LRESULT CGrpMView::OnNotifyEvent(WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
	case dispDayChart:	// display change on Chart
		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlDisplay), lParam);
		break;
	case dispDayCtrl:		// display change by Ctrl
		if (m_pActiveChart)
			m_pActiveChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, CHART_DISPLAY), lParam);
		break;
	case dispScaleChart:	// display change by Chart
		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlDisplay), lParam);
		break;
	case dispScaleCtrl:		// display change by Ctrl
		if (m_pActiveChart)
			m_pActiveChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartScale), lParam);
		break;
	case mainChart:			// Main change by chart, if Active Chart->Ctrl disable 
		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlMain), lParam);
		break;
	case aidAddCfg:			// ������ǥ�߰� by CFG
		MultiAidAdd(lParam);
		return 1L;
	case aidDelCfg:			// ������ǥ���� by CFG
		MultiAidDel(lParam);
		return 1L;
	case unitInput:			// unit change by Input(�ϴ� ���常 �Ѵ�)
		m_idUnit = lParam;
		break;
	case indexInput:		// index change by Input
		MultiIndex(lParam);		
		break;
	case inputAutotran:
		OnAutoTran(lParam);
		break;
	case cfgMainChart:	// Change Main by CFG
		MultiMain(lParam);
		break;
	}

	return TRUE;
}

LRESULT CGrpMView::OnMultiEvent(WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
	case codeUnit:			// unit change by input
		return m_idUnit;
	case codeInput:			// code change by Input
		MultiCode(lParam);
		break;
	case codeMultiInput:
		PluralMultiCode(lParam);
		break;
	case totalInput:		// total change by Input
		MultiGigan(lParam);
		break;
	case total2Input:		// multi total change by Input
		MultiGigan2(lParam);
		break;
	case matrixInput:		// new matrix by Input
		MultiMatrix(lParam);
		break;
	case matrix2Input:		// matrix change by Input
		MultiMatrix2(lParam);
		break;
	case selectInput:		// select change by Input
		MultiCheck(lParam);
		break;
	case focusInput:		// ���ߺм� by Input
		MultiFocus(lParam);
		break;
	case orderInput:		// �ֹ� by Input
		break;
	case todayInput:		// Today by Input
		MultiToday(lParam);
		break;
	case activeView:		// Set active View, Reset ActiveView
		if (m_pActiveChart == (CWnd*)lParam)
			break;

		if (m_pActiveChart)	
			m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, inactiveView), 0);
		m_pActiveChart = (CWnd*)lParam;
		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CtrlMulti, CtrlInit), 0);

		m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, ChangeChart), 0);
		break;
	case activeInfo:		// get Active chart info(Input->View--->View->Chart)
		if (m_pActiveChart)	
			return m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeInfo), 0);
		return 0;
	case mainInput:			// get Main Chart Type by Ctrl
		if (m_pActiveChart)
			return m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, mainInput), lParam);
		return GK_PV;
	case getRotCnt:
		return GetRotChartCnt();
	case getMultiInfo:
		return int(m_pMultiChartInfo);
	case setMultiCode:
		OnSetMultiCode(lParam);
		break;
	case autoComplete:
		if (m_bAutotran)
			OnAutoComplete(lParam);
		break;
	case initAllChart:
		OnInitAllChart();
		break;
	}

	return TRUE;
}

LRESULT CGrpMView::OnViewEvent(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case viewInterface:
		switch (HIWORD(wParam))
		{
		case getRootPath:
			return (LRESULT)(LPCTSTR)m_pApp->GetRoot();
		case getTabPath:
			return (LRESULT)(LPCTSTR)m_pApp->GetTabPath();
		case getUserName:
			return (LRESULT)(LPCTSTR)m_pApp->GetUName();
		case getUserID:
			return (LRESULT)(LPCTSTR)m_pApp->GetUID();
			break;
		case requestTR:			break;
		}
		break;
	case viewDialog:
		switch (HIWORD(wParam))
		{
		case dlgJCode:	case dlgUCode:	case dlgFCode:	case dlgOCode:	
		case dlgJUCode:	case dlgFOCode:
		// 20090907 : ADD
		case dlgCommoditiesFutureCode:
			return (long)OpenCodeDlg(HIWORD(wParam), lParam);
		case dlgGubnFOSO:
			return m_pwndView->SendMessage(WM_USER, MAKEWPARAM(nameDLL, whichKIND), lParam);
		case dlgEnv:	case dlgSave:
			break;
		default:
			return (long)OpenCodeDlg(usCODE, lParam);
			break;
		}
		break;
	case viewMain:
		switch (HIWORD(wParam))
		{
		case getPalette:
			return m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), lParam);
			break;
		case getHistory:
			return m_pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, historyCC), lParam);
			break;
		case setHistory:
			m_pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, codeCC), lParam);
			break;
		case setTrigger:
			m_pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, triggerCC), lParam);
			break;
		case openView:
			m_pwndView->SendMessage(WM_USER, MAKEWPARAM(viewDLL, typeVIEW), lParam);
			break;
		case isSiseOnly:
			{
				char	*accn = (char*)m_pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, accountCC), 0);
				if (strlen(accn) <= 0)	return TRUE;
				else			return FALSE;
			}
			break;
		}
		break;
	case viewNotify:
		return OnNotifyEvent(wParam, lParam);
	case viewMulti:
		return OnMultiEvent(wParam, lParam);
	case viewShowWindow:
		{
			if (lParam == 9999)
				return GetControlShow(HIWORD(wParam));

			bool	bShow = (lParam) ? true:false;
			switch (HIWORD(wParam))
			{
			case showCfg:
				ControlShow(PN_CFG, bShow);
				break;
			default:
				return 0;
			}
		}
		break;
	}

	return TRUE;
}

LRESULT CGrpMView::OnChartEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_pActiveChart)
		return m_pActiveChart->SendMessage(GEV_CHART, wParam, lParam);

	return FALSE;
}

LRESULT CGrpMView::OnInputEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_pwndInput)	return m_pwndInput->SendMessage(GEV_INPUT, wParam, lParam);
	return TRUE;
}

LRESULT CGrpMView::OnCtrlEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_pwndCtrl)	return m_pwndCtrl->SendMessage(GEV_CTRL, wParam, lParam);
	return FALSE;
}

LRESULT CGrpMView::OnCfgEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_pCfg)	m_pCfg->SendMessage(GEV_CFG, wParam, lParam);
	return FALSE;
}

LRESULT CGrpMView::OnFromMain(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)		// load
	{

	}
	else if (wParam == 1)	// save
	{
		
	}

	return 0;
}

LRESULT CGrpMView::OnViewSendTR(WPARAM wParam, LPARAM lParam)
{
	LPTRINFO tr = (LPTRINFO)lParam;

	SendTR(tr->sender, tr->trCode, tr->data, tr->size, tr->stat);

	return 0L;
}

void CGrpMView::InitView()
{
	CString strMapPath;
	strMapPath.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_acDllName, MCI);
	m_pMultiChartInfo = new _MultiChart;
	m_pApp->ReadFile(this, strMapPath, (char*)m_pMultiChartInfo, SZ_MULTICHART);

	_fontR rFont;
	rFont.name = "����";
	rFont.point = 9;
	rFont.italic = 0;
	rFont.bold = 0;
	m_pFont = (CFont *)m_pwndView->SendMessage(WM_USER, getFONT, long(&rFont));

	// library loading
	if (!m_pApp->m_hiGMTotalLib)
		m_pApp->m_hiGMTotalLib = LoadLibrary("axisGMTotal.dll");
	if (m_pMultiChartInfo->btType == MT_MONITOR)
	{
		if (!m_pApp->m_hiGMInvestLib)
			m_pApp->m_hiGMInvestLib = LoadLibrary("axisGMInvest.dll");
		if (!m_pApp->m_hiGMThemeLib)
			m_pApp->m_hiGMThemeLib = LoadLibrary("axisGMTheme.dll");
	}

	CreateWnd();
	m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, SetTodayCheck), m_pMultiChartInfo->btToday);

	m_pwndView->SendMessage(WM_USER, MAKEWPARAM(dropDLL, 0), NULL);

	CRect	crc;
	m_pwndView->GetClientRect(&crc);
	ResizeWnd(CRect(0, 0, crc.Width(), crc.Height()));
}

void CGrpMView::CreateWnd()
{
	m_pwndInput = new CPnInput(m_pwndView, this, m_pFont, PN_INPUT, (char *)m_pMultiChartInfo);
	m_pwndInput->Create(NULL, NULL, WS_CHILD | WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,  CRect(0, 0, 0, 0), this, 0);
	m_pwndInput->MoveWindow(0, 0, 0, 0);

	m_pwndCtrl = new CPnCtrl(m_pwndView, this, m_pFont, PN_CTRL, (char *)m_pMultiChartInfo);
	m_pwndCtrl->Create(NULL, NULL, WS_CHILD | WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, 0);
	m_pwndCtrl->MoveWindow(0, 0, 0, 0);

	_barChart	barChart;
	barChart.mkind = m_pMultiChartInfo->btMainKind;
	barChart.rgncnt = 0;
	barChart.grpcnt = 1;
	barChart.minfo = (char*)&m_DummyGraph.graph;
	barChart.ulist = m_pMultiChartInfo->acUlist;

	m_pCfg = new CConfigBarMulti(m_pwndView, this, m_pFont, (char*)&barChart);
	BOOL bCreate = m_pCfg->Create(this, CRect(0, 0, 160, 300), 50000);
	m_pCfg->ChangePalette();
	m_pCfg->ShowWindow(SW_SHOW);

	CreateChart(true);
	InitMultiCode();
}

void CGrpMView::CreateChart(bool bFirst)
{
	CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
	if (bFirst)
	{
		pMerge->SetMergeString(m_pMultiChartInfo->acMatrix);
		int	Row = pMerge->GetRowCount();
		int	Col = pMerge->GetColCount();
		for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
		{  
			for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
			{ 
				CreateMTotal(ii*6 + jj + 1);
			}
		}
	}
	else
	{
		CWnd	*pWnd;
		int	Row = pMerge->GetRowCount();
		int	Col = pMerge->GetColCount();
		for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
		{
			for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
			{
				int	key = ii*6 + jj + 1;
				if (!m_mapChart.Lookup(key, pWnd))
					CreateMTotal(key);
			}
		}
	}
}

CWnd* CGrpMView::CreateMTotal(int Key)
{
	if (m_pMultiChartInfo->btType == MT_MONITOR)
	{
		if (Key == 14)		// �׸���Ʈ
		{
			CWnd*	(APIENTRY *axCreate)(CWnd*, CWnd*, int);
			axCreate = (CWnd* (APIENTRY *)(CWnd *, CWnd*, int))
				GetProcAddress(m_pApp->m_hiGMThemeLib, "axCreate");

			CWnd*	pMTheme = axCreate(m_pwndView, this, Key);
			pMTheme->MoveWindow(0, 0, 0, 0);
			
			m_mapChart.SetAt(Key, pMTheme);

			return pMTheme;
		}
		else if (Key == 15)	// �����ں� ������Ʈ
		{
			CWnd*	(APIENTRY *axCreate)(CWnd*, CWnd*, int);
			axCreate = (CWnd* (APIENTRY *)(CWnd *, CWnd*, int))
				GetProcAddress(m_pApp->m_hiGMInvestLib, "axCreate");

			CWnd*	pMInvest = axCreate(m_pwndView, this, Key);
			pMInvest->MoveWindow(0, 0, 0, 0);
			
			m_mapChart.SetAt(Key, pMInvest);

			return pMInvest;
		}
	}

	struct _param	param;
	SetParam(&param, m_acDllName, Key);

	CWnd*	(APIENTRY *axCreate)(CWnd*, CWnd*, void*, int);
	axCreate = (CWnd* (APIENTRY *)(CWnd *, CWnd*, void *, int))
		GetProcAddress(m_pApp->m_hiGMTotalLib, "axCreate");

	CWnd*	pMTotal = axCreate(m_pwndView, this, &param, m_pMultiChartInfo->btType);
	pMTotal->MoveWindow(0, 0, 0, 0);
	
	m_mapChart.SetAt(Key, pMTotal);

	if (m_pMultiChartInfo->acSelect[Key-1])
		pMTotal->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, setCheckState), 1);

//	Stay(100);

	return pMTotal;
}

void CGrpMView::ResizeWnd(CRect wRC)
{
	int cx = wRC.Width();
	int cy = wRC.Height();
	
	MoveWindow(0, 0, cx, cy);

	int iGabCfg = GetControlShow(PN_CFG)? WIDTH_CFG:0;
	int iGabInput = HEIGHT_INPUT;
	int iGabCtrl = HEIGHT_CTRL;

	int	iLeft = iGabCfg;
	if (m_pCfg)
	{
		if (iGabCfg)
		{
			m_pCfg->MoveWindow(5, iGabInput + 5, iGabCfg, cy - iGabInput - 10);
			iLeft  = iGabCfg + 10;
		}
		else
		{
			m_pCfg->MoveWindow(0, iGabInput, iGabCfg, cy - iGabInput);
		}
	}

	if (m_pwndInput)	m_pwndInput->MoveWindow(0, 0, cx, HEIGHT_INPUT);
	if (m_pwndCtrl)		m_pwndCtrl->MoveWindow(iLeft + 5, cy - iGabCtrl - 5, cx - iLeft - 10, iGabCtrl);

	CRect iRC;
	iRC.left = iLeft + 5;
	iRC.top = iGabInput + 5;
	iRC.right = iRC.left + (cx - iLeft - 10);
	iRC.bottom = cy - iGabCtrl - 7;

	m_rcChart = m_rcOrgChart = iRC;
	m_rcChart.top += 1;
	ResizeChart();
}

void CGrpMView::ResizeChart()
{
	if (m_rcChart.IsRectEmpty())
		return;

	CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
	CRect	rc = m_rcChart;
	rc.OffsetRect(-m_rcChart.left, -m_rcChart.top);
	pMerge->SetSize(rc);

	int		Key;
	CWnd	*pWnd;
	int	Row = pMerge->GetRowCount();
	int	Col = pMerge->GetColCount();
	if (m_pMultiChartInfo->acCntX > Col || m_pMultiChartInfo->acCntY > Row)
	{	// ���� ��Ʈ�������� �پ ���ο� ��Ʈ�������� ��Ʈ�� �����.
		if (m_pMultiChartInfo->acCntX > Col && m_pMultiChartInfo->acCntY > Row)
		{
			for (int ii = 0; ii < m_pMultiChartInfo->acCntY; ii++)
			{
				for (int jj = 0; jj < m_pMultiChartInfo->acCntX; jj++)
				{
					if (ii < Row && jj < Col)
						continue;

					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						pWnd->ShowWindow(SW_HIDE);
					}
				}
			}
		}
		else if (m_pMultiChartInfo->acCntX > Col)
		{
			for (int ii = 0; ii < m_pMultiChartInfo->acCntY; ii++)
			{
				for (int jj = Col; jj < m_pMultiChartInfo->acCntX; jj++)
				{
					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						pWnd->ShowWindow(SW_HIDE);
					}
				}
			}
		}
		else
		{
			for (int ii = Row; ii < m_pMultiChartInfo->acCntY; ii++)
			{
				for (int jj = 0; jj < m_pMultiChartInfo->acCntX; jj++)
				{
					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						pWnd->ShowWindow(SW_HIDE);
					}
				}
			}
		}
	}

	for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
	{
		for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
		{
			int	key = ii*6 + jj + 1;
			if (pMerge->IsActive(jj, ii)) 
			{
				rc = pMerge->GetRect(jj, ii);
				rc.OffsetRect(m_rcChart.left, m_rcChart.top);
				if (m_mapChart.Lookup(key, pWnd))
				{
					pWnd->MoveWindow(rc);
					pWnd->ShowWindow(SW_SHOW);
				}
			}
			else
			{
				if (m_mapChart.Lookup(key, pWnd))
					pWnd->ShowWindow(SW_HIDE);		
			}
		}
	}
}

bool CGrpMView::GetControlShow(int iID)
{
	if (iID == PN_CFG)
		return m_pMultiChartInfo->btShowCFG? true:false;

	return true;
}

bool CGrpMView::ControlShow(int iID, bool bShow)
{
	if (iID != PN_CFG)	return false;

	if (m_pMultiChartInfo->btShowCFG)	
		m_pMultiChartInfo->btShowCFG = 0;
	else	
		m_pMultiChartInfo->btShowCFG = 1;

	CRect	wRC;
	GetWindowRect(&wRC);
	ResizeWnd(wRC);
	Invalidate();

	return true;
}

void CGrpMView::SendTR(CWnd* sender, CString strCode, LPCTSTR strData, int nSize, char stat)
{
	if (m_trSender) return;

	m_trSender = sender;

	char*	cDataBuffer = new char [L_userTH + nSize]; //10240];
	struct	_userTH* userTH;
	userTH = (struct _userTH *) cDataBuffer;
	
	strcpy(userTH->trc, strCode);
	userTH->key = 120;
	userTH->stat = stat;
	
	CopyMemory(&cDataBuffer[L_userTH], strData, nSize);

	m_pwndView->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, nSize), (LPARAM)cDataBuffer);
	delete [] cDataBuffer;	

	m_bTransaction = true;
}

char* CGrpMView::OpenCodeDlg(int kind, UINT lParam)
{
//	ClearBuffer();

	int dKind;
	switch (kind)
	{
	case dlgJCode:
		dKind = kospiCODE;
		break;
	case dlgUCode:
		dKind = indexCODE;
		dKind = MAKEWORD(indexCODE, 99);
		break;
	case dlgFCode:
		dKind = futureCODE;
		break;
	case dlgOCode:
		dKind = optionCODE;
		break;
	case dlgJUCode:
		dKind = allCODE;
		break;
	case dlgFOCode:
		dKind = faoptionCODE;
		break;
	// 20090907 : ADD
	case dlgCommoditiesFutureCode:
		dKind = 127; 
	default:
		dKind = usCODE;
		break;
	}
/*
Kind : LOBYTE(HIWORD(wParam))
Type : HIBYTE(HIWORD(wParam))
Point.x : LOWORD(lParam)
Point.y : HIWORD(lParam)
*/
	return (char*) m_pwndView->SendMessage(WM_USER, MAKEWPARAM(codeDLL, dKind), lParam);
}

// text : point.x \t point.y \n SYM \t DATA (\t ...)
// LOBYTE(HIWORD(WPARAM)) : source window ID
// HIBYTE(HIWORD(WPARAM)) : destination window ID
void CGrpMView::OnDrop(WPARAM wParam, LPARAM lParam)
{
	//if (m_acDllName != _T("IB702000"))
	if (m_pMultiChartInfo->btType != MT_MULTI)
		return;

	CPoint	point;
	int	index;
	CString dropS, str;

	dropS = (char *)lParam;
	index = dropS.Find("\t");
	if (index == -1)
		return;
	str = dropS.Left(index);
	point.x = atoi(str);

	dropS = dropS.Mid(++index);
	index = dropS.Find("\n");
	if (index == -1)
		return;
	str = dropS.Left(index);
	point.y = atoi(str);

	dropS = dropS.Mid(++index);
	index = dropS.Find("\t");
	if (index == -1)
		return;

	CString	strSymbol = dropS.Left(index);
	CString	strCode = dropS.Mid(index+1);
	if (strCode.GetLength() != 6)
		return;

	CPoint	dropPt;
	GetCursorPos(&dropPt);
	//ScreenToClient(&dropPt);

	int		Key;
	CWnd	*pWnd;
	CRect	rc;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		if (pWnd->IsWindowVisible())
		{
			pWnd->GetWindowRect(&rc);

			if (rc.PtInRect(dropPt))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), (LPARAM)(LPCTSTR)strCode);
		}
	}
}

LRESULT CGrpMView::Oub(WPARAM wParam, LPARAM lParam)
{
	struct  _zcom_head 
	{
		char ywin[4];
		char tcnt[4];
		char seqn[4];
		char fill[4];
	};
	#define SZ_ZCOMHEAD	sizeof(struct  _zcom_head)

	if (m_trSender) 
	{
		m_trSender->SendMessage(WM_USER, wParam, lParam);
		m_trSender = NULL;

		m_bTransaction = false;
		return TRUE;
	}

	return TRUE;
}

// i : data index - 1:��, 2:��, 3:��, 4:��, 5:ƽ
// u : data unit - 1:����, 2:����, 3:����, 4:����, 5:�ؿ�
void CGrpMView::SetParam(_param *param, CString fName, int key)
{
	param->name.Format("%s_%d", fName, key);	// file name + "_" + Key(������ ��ȸ�ϴ� Ű = �迭�� ��ġ(1,2,3...7,8,...)
	param->options.Format("/n%s/r300/d150/i1/u1/m15/m220/m360/", param->name);
	param->fonts.Format("����");
	param->point = 9;
	param->key = key;
	param->tRGB = 232;
	param->pRGB = 192;
}

void CGrpMView::MultiAidAdd(LPARAM lParam)
{	// CFG���� ������ǥ �߰�(üũ�� �͸�)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewNotify, aidAddCfg), lParam);
}

void CGrpMView::MultiAidDel(LPARAM lParam)
{	// CFG���� ������ǥ ����(üũ�� �͸�)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewNotify, aidDelCfg), lParam);
}

void CGrpMView::MultiIndex(LPARAM lParam)
{	// ���ֿ� ����(üũ�� �͸�)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewMulti, giganInput), lParam);
}

void CGrpMView::MultiMain(LPARAM lParam)
{	// CFG���� ������Ʈ ����(üũ�� �͸�)
	MultiChkMsg(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_MAIN_GRP), lParam);
	if (m_pActiveChart && m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
	{
		if (m_pwndCtrl)		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlMain), lParam);
	}
}

void CGrpMView::MultiCode(LPARAM lParam)
{	// �����ڵ�
	CWnd* pWnd;
	int	Key;
	POSITION pos;
	int	ii;
	switch (m_pMultiChartInfo->btType)
	{
	case MT_SINGLE:	case MT_MULTI:
		if (m_bDominoExist && m_arHistory.GetSize())
		{	// ó�� ������ ���̳뿡 ���� �ڵ�� ���´�.
			m_bDominoExist = false;
			return;
		}

		for (pos = m_mapChart.GetStartPosition(); pos; )
		{
			m_mapChart.GetNextAssoc(pos, Key, pWnd);
			if (pWnd->IsWindowVisible() && pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), lParam);
		}		
		break;
	case MT_MONITOR:	// üũ�� �����ϰ� �׻� �������� ��ο���
		for (ii = 0; ii < 3; ii++)
		{
			Key = ii+1;
			if (m_mapChart.Lookup(Key, pWnd))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), lParam);
		}

		{	// �ش� ���� �ڵ带 ã�ƶ�
			char	*pICode = FindIndexCode((char*)lParam);
			if (pICode && strlen(pICode) == 3)
			{
				if (m_mapChart.Lookup(13, pWnd))
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(pICode));
			}

			if (m_mapChart.Lookup(14, pWnd))	// �׸���Ʈ
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), lParam);
			if (m_mapChart.Lookup(15, pWnd))	// �����ں� �Ÿŵ���
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), lParam);
		}
		break;
	}
}

void CGrpMView::PluralMultiCode(LPARAM lParam)
{	// ���������ڵ�
	CWnd	*pWnd;
	int	Key, Index = 0;
	char	*pData = (char*)lParam, pCode[16];
	int	len = strlen(pData);
	if (m_pMultiChartInfo->btType == MT_MULTI)
	{
		for (int ii = 0; ii < m_pMultiChartInfo->acCntY; ii++)
		{
			for (int jj = 0; jj < m_pMultiChartInfo->acCntX; jj++)
			{
				Key = ii*6 + jj + 1;
				if (m_mapChart.Lookup(Key, pWnd))
				{
					if (len < Index+6)
						Index = 0;

					if (pWnd->IsWindowVisible() && pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
					{
						sprintf(pCode, "%.6s", &pData[Index]);
						pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeMultiInput), long(pCode));
						Index += 6;
					}	
				}
			}
		}
	}
}

void CGrpMView::MultiGigan(LPARAM lParam)
{	// �Ⱓ ����(üũ�� �͸�)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewMulti, totalInput), lParam);
}

void CGrpMView::MultiGigan2(LPARAM lParam)
{	// ���� �Ⱓ �ڽ�(��ο���)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewMulti, total2Input), lParam);
}

void CGrpMView::MultiChkMsg(UINT message, WPARAM wParam, LPARAM lParam)
{	// üũ�Ȱ͸� ����
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		if (pWnd->IsWindowVisible() && pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
			pWnd->SendMessage(message, wParam, lParam);
	}		
}

void CGrpMView::MultiAllMsg(UINT message, WPARAM wParam, LPARAM lParam)
{	// ��ο��� ����
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		pWnd->SendMessage(message, wParam, lParam);
	}		
}

void CGrpMView::MultiEnableChart(bool bEnable)
{
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		pWnd->EnableWindow(bEnable);
	}		
}

void CGrpMView::MultiMatrix(LPARAM lParam)
{	// new Matrix
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	DefaultMap(x, y);
	CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
	sprintf(m_pMultiChartInfo->acMatrix, "%d,%d;", x, y);
	pMerge->SetMergeString(m_pMultiChartInfo->acMatrix);

	ResizeChart();	
	m_pMultiChartInfo->acCntX = x;
	m_pMultiChartInfo->acCntY = y;
/*
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	sprintf(m_pMultiChartInfo->acMatrix, "%d,%d;", x, y);

	// check new chart
	if (m_pMultiChartInfo->acCntX < x || m_pMultiChartInfo->acCntY < y)
	{
		CWnd	*pWnd;
		int		Key;

		ReadHistory();
		CreateChart(false);
		if (m_pMultiChartInfo->acCntX < x && m_pMultiChartInfo->acCntY < y)
		{
			for (int ii = 0; ii < y; ii++)
			{
				for (int jj = 0; jj < x; jj++)
				{
					if (ii < m_pMultiChartInfo->acCntY && jj < m_pMultiChartInfo->acCntX)
						continue;

					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						char	*pCode = (char*)pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMapCode), 0);
						if (pCode && strlen(pCode) > 0)	// �̹� ��ȸ������ ������ �ٽ� ��ȸ
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, mTotalTran), 0);
						}
						else if (strlen(m_pMultiChartInfo->acCode[Key-1]))	// �ű� ���������� ����� �ڵ带 ������
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
						}
						else	// �ֱ� ��ȸ �ڵ带 ������.
						{
							if (m_arHistory.GetSize() > 0)
							{
								CString	code = m_arHistory.GetAt(0);
								pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
							}
						}
					}
				}
			}
		}
		else if (m_pMultiChartInfo->acCntX < x)
		{
			for (int ii = 0; ii < m_pMultiChartInfo->acCntY; ii++)
			{
				for (int jj = m_pMultiChartInfo->acCntX; jj < x; jj++)
				{
					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						char	*pCode = (char*)pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMapCode), 0);
						if (pCode && strlen(pCode) > 0)	// �̹� ��ȸ������ ������ �ٽ� ��ȸ
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, mTotalTran), 0);
						}
						else if (strlen(m_pMultiChartInfo->acCode[Key-1]))	// �ű� ���������� ����� �ڵ带 ������
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
						}
						else	// �ֱ� ��ȸ �ڵ带 ������.
						{
							if (m_arHistory.GetSize() > 0)
							{
								CString	code = m_arHistory.GetAt(0);
								pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
							}
						}
					}
				}
			}
		}
		else// if (m_pMultiChartInfo->acCntY < y)
		{
			for (int jj = 0; jj < m_pMultiChartInfo->acCntX; jj++)
			{
				for (int ii = m_pMultiChartInfo->acCntY; ii < y; ii++)
				{
					Key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(Key, pWnd))
					{
						char	*pCode = (char*)pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMapCode), 0);
						if (pCode && strlen(pCode) > 0)	// �̹� ��ȸ������ ������ �ٽ� ��ȸ
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, mTotalTran), 0);
						}
						else if (strlen(m_pMultiChartInfo->acCode[Key-1]))	// �ű� ���������� ����� �ڵ带 ������
						{
							pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
						}
						else	// �ֱ� ��ȸ �ڵ带 ������.
						{
							if (m_arHistory.GetSize() > 0)
							{
								CString	code = m_arHistory.GetAt(0);
								pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
							}
						}
					}
				}
			}
		}
	}

	ResizeChart();

	m_pMultiChartInfo->acCntX = x;
	m_pMultiChartInfo->acCntY = y;
*/
	CheckActiveChart();
}

void CGrpMView::MultiMatrix2(LPARAM lParam)
{	// merge Matrix
	sprintf(m_pMultiChartInfo->acMatrix, "%s", (char*)lParam);
	ResizeChart();

	CheckActiveChart();
}

void CGrpMView::MultiCheck(LPARAM lParam)
{	// CheckButton(��ο���)
	MultiAllMsg(GEV_VIEW, MAKEWPARAM(viewMulti, setCheckState), lParam);
}

void CGrpMView::MultiFocus(LPARAM lParam)
{	// Default��
	if (m_pMultiChartInfo->btType > MT_MULTI)
		return;

	int	x = 3;
	int	y = 3;

	CString	code = (char*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, getCurCode), 0);
	char	checkCode[32];
	sprintf(checkCode, "%s", code);
	CString	name = (char*)SendMessage(GEV_VIEW, MAKEWPARAM(viewDialog, dlgGubnFOSO), long(checkCode));
	if (name.IsEmpty())
		code = "";

	DefaultMap(x, y, code);

	CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
	sprintf(m_pMultiChartInfo->acMatrix, "%d,%d;", x, y);
	pMerge->SetMergeString(m_pMultiChartInfo->acMatrix);

	ResizeChart();	
	m_pMultiChartInfo->acCntX = x;
	m_pMultiChartInfo->acCntY = y;
}

void CGrpMView::MultiToday(LPARAM lParam)
{	// ����(üũ�� �͸�)
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewMulti, todayInput), lParam);
}

int CGrpMView::MultiOub(WPARAM wParam, LPARAM lParam)
{	// ���� ������ ��û ����
	CWnd	*pWnd;
	int	Key = HIBYTE(LOWORD(wParam));
	if (m_mapChart.Lookup(Key, pWnd))
		pWnd->SendMessage(WM_USER, wParam, lParam);

	return 1;
}

void CGrpMView::MultiAlert(WPARAM wParam, LPARAM lParam)
{	// ���� ������ �ǽð� ó��
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		if (pWnd->IsWindowVisible())
			pWnd->SendMessage(WM_USER, wParam, lParam);
	}
}

int CGrpMView::GetRotChartCnt()
{	// ��������� ���� ����� ��û
	if (m_pMultiChartInfo->btType == MT_MULTI)
	{	// üũ�� �͸�
		CWnd* pWnd;
		int	Key;
		int	cnt = 0;
		for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
		{
			m_mapChart.GetNextAssoc(pos, Key, pWnd);
			if (pWnd->IsWindowVisible() && pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
				cnt++;
		}

		return cnt;
	}
	else if (m_pMultiChartInfo->btType == MT_SINGLE || m_pMultiChartInfo->btType == MT_MONITOR)
	{	// üũ�����ϰ� �׻� ������
		return 1;
	}

	return 0;
}

void CGrpMView::InitMultiCode()
{	// ������ ����� �ڵ带 ��/��/��/�� ���о��� �ش� ��Ʈ�� �ѱ��.
	CWnd* pWnd;
	int	Key;
	int	ChartCnt = 0;
	int	EmptyCnt = 0;
	if (m_pMultiChartInfo->btType == MT_SINGLE)
	{
		for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
		{
			ChartCnt++;
			m_mapChart.GetNextAssoc(pos, Key, pWnd);
			if (strlen(m_pMultiChartInfo->acCode[Key-1]))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
			else
				EmptyCnt++;
		}

		if (ChartCnt == EmptyCnt && m_arHistory.GetSize() > 0)
		{
			CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
			int	Row = pMerge->GetRowCount();
			int	Col = pMerge->GetColCount();
			for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
			{
				for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
				{
					int	key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(key, pWnd))
					{
						CString	code = m_arHistory.GetAt(0);
						pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
					}
				}
			}			
		}
	}
	else if (m_pMultiChartInfo->btType == MT_MULTI)
	{
		for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
		{
			ChartCnt++;
			m_mapChart.GetNextAssoc(pos, Key, pWnd);
			if (strlen(m_pMultiChartInfo->acCode[Key-1]))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
			else
				EmptyCnt++;
		}
		
		int	hSize = m_arHistory.GetSize();
		if (ChartCnt == EmptyCnt && hSize > 0)
		{
			int	Cnt = 0;
			CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
			int	Row = pMerge->GetRowCount();
			int	Col = pMerge->GetColCount();
			for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
			{
				for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
				{
					int	key = ii*6 + jj + 1;
					if (m_mapChart.Lookup(key, pWnd))
					{
						int	index = Cnt % hSize;
						Cnt++;
						CString	code = m_arHistory.GetAt(index);
						pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
					}
				}
			}			
		}
	}
	else if (m_pMultiChartInfo->btType == MT_MONITOR)
	{
		if (m_arHistory.GetSize() <= 0)	// history�� ������ ���� ����� �ڵ�� ä���.
		{
			for (Key = 1; Key <= 3; Key++)
			{
				if (m_mapChart.Lookup(Key, pWnd))
				{
					if (strlen(m_pMultiChartInfo->acCode[Key-1]))
					{
						pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));

						if (Key == 1)
						{	// �ش� ���� �ڵ带 ã�ƶ�
							char	*pICode = FindIndexCode(m_pMultiChartInfo->acCode[Key-1]);
							if (pICode && strlen(pICode) == 3)
							{
								if (m_mapChart.Lookup(13, pWnd))
								{
									pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(pICode));
								}
							}

							if (m_mapChart.Lookup(14, pWnd))	//�׸���Ʈ
								pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), int(m_pMultiChartInfo->acCode[Key-1]));
							if (m_mapChart.Lookup(15, pWnd))	// �����ں� �Ÿŵ���
								pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), int(m_pMultiChartInfo->acCode[Key-1]));

						}	// if (Key
					}	// if (strlen
				}	// if (m_mapChart
			}	// for (Key = 1
		}
		
		for (Key = 7; Key <= 9; Key++)
		{
			if (m_mapChart.Lookup(Key, pWnd))
			{
				if (strlen(m_pMultiChartInfo->acCode[Key-1]))
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
			}
		}
	}
	else if (m_pMultiChartInfo->btType == MT_FOREIGN)
	{
		for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
		{
			m_mapChart.GetNextAssoc(pos, Key, pWnd);
			if (strlen(m_pMultiChartInfo->acCode[Key-1]))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(m_pMultiChartInfo->acCode[Key-1]));
		}
	}
}

void CGrpMView::InitMConfig()
{
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		if (pWnd->IsWindowVisible() && pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
		{
			struct _envInfo	*envinfo = NULL;
			envinfo = (_envInfo*)pWnd->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
			int	sIndex = envinfo->datainfo.btIndex - GI_DAY;
			int	rcnt = envinfo->grpinfo[sIndex].wRgnCnt;
			int	gcnt = envinfo->grpinfo[sIndex].wGrpCnt;

			char *buf = (char *)pWnd->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_MAP), 0);
			if (!buf)
				return;

			int	mapsize = sz_INTERCHART + rcnt*SZ_REGION + gcnt*SZ_GRAPH;
			char	*mapBuf = new char[mapsize];
			CopyMemory(&mapBuf[0], buf, rcnt*SZ_REGION);
			CopyMemory(&mapBuf[rcnt*SZ_REGION], &buf[rcnt*SZ_REGION], gcnt*SZ_GRAPH);

			m_pCfg->ReloadGraph(envinfo->datainfo.wMainGrpKind);
			_barChart	barChart;
			barChart.mkind = envinfo->datainfo.wMainGrpKind;
			barChart.rgncnt = BYTE(rcnt);
			barChart.grpcnt = BYTE(gcnt);
			barChart.minfo = mapBuf;
			barChart.ulist = envinfo->ulist;
			m_pCfg->ReloadGraph((char*)&barChart);			

			delete[] mapBuf;

			break;
		}
	}
}

void CGrpMView::ClearChart()
{	
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		delete pWnd;
		pWnd = NULL;
	}

	m_mapChart.RemoveAll();
}

void CGrpMView::SaveMultiInfo()
{
	SaveChart();
	m_pMultiChartInfo->btToday = (char)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetTodayCheck), 0);
	if (m_pCfg)
		CopyMemory(m_pMultiChartInfo->acUlist, m_pCfg->GetUserGraph(), sizeof(m_pMultiChartInfo->acUlist));


	CString strMapPath;
	strMapPath.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_acDllName, MCI);
	m_pApp->WriteFile(this, strMapPath, (char*)m_pMultiChartInfo, SZ_MULTICHART);
}

void CGrpMView::SaveChart()
{	// ������ üũ,�ڵ� ����
	CWnd* pWnd;
	int	Key;
	for (POSITION pos = m_mapChart.GetStartPosition(); pos; )
	{
		m_mapChart.GetNextAssoc(pos, Key, pWnd);
		m_pMultiChartInfo->acSelect[Key-1] = char(pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0));
		char	*pCode = (char*)pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMapCode), 0);
		if (pCode && strlen(pCode) > 0)
			sprintf(m_pMultiChartInfo->acCode[Key-1], "%s", pCode);
	}
}

void CGrpMView::CheckActiveChart()
{	// ��Ƽ�� ��Ʈ�� ������� 1�� ȭ���� ��Ƽ��� ����
	if (!m_pActiveChart || !m_pActiveChart->IsWindowVisible())
	{
		int	Key = 1;
		CWnd	*pWnd;
		if (m_mapChart.Lookup(Key, pWnd))
		{
			if (m_pActiveChart)	m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, inactiveView), 0);
			
			m_pActiveChart = pWnd;
			m_pActiveChart->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeView), 1);
			m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CtrlMulti, CtrlInit), 0);
		}
	}
}

int CGrpMView::ReadHistory()
{
	CString	symbol, history;
	symbol = JTRG;
	history = (char *)SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getHistory), (long)symbol.operator LPCTSTR());

	if (!history || strlen(history) < 5)
		return 0;

	CString	Str, Code;
	int	index;

	m_arHistory.RemoveAll();
	for (;;)
	{
		index = history.Find("\t");
		if (index <= 0)
			break;

		Str = history.Left(index);
		history = history.Mid(index + 1);

		index = Str.Find(" ");
		if (index > 0)
		{
			Code = Str.Left(index);
			m_arHistory.Add(Code);
		}
	}

	return m_arHistory.GetSize();
}

void CGrpMView::DefaultMap(int x, int y, CString curCode/* = _T("")*/)
{
	ReadHistory();
	CWnd	*pWnd;
	int		Key, unit, iLoop = 0;
	CString	code = "005930";
	if (m_pMultiChartInfo->btType == MT_SINGLE)	// ���ֿ�ƽ��....
	{
		if (!curCode.IsEmpty())
			code = curCode;
		else if (m_arHistory.GetSize() > 0)		code = m_arHistory.GetAt(0);

		if (code.GetLength() > 6)
			unit = GU_FUTURE;
		else
			unit = GU_CODE;

		int	index[9] = {GI_DAY, GI_WEEK, GI_MONTH, GI_TICK, GI_MINUTE, GI_MINUTE, GI_MINUTE, GI_MINUTE, GI_MINUTE};
		int	gap[9] = {0, 0, 0, 1, 1, 5, 10, 30, 60};
		for (int ii = 0; ii < y; ii++)
		{
			for (int jj = 0; jj < x; jj++)
			{
				Key = ii*6 + jj + 1;
				iLoop = iLoop%9;
				if (!m_mapChart.Lookup(Key, pWnd))
					pWnd = CreateMTotal(Key);

				if (pWnd)
				{
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, onlyGigan), MAKELPARAM(index[iLoop], gap[iLoop]));
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranUnit), unit);
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranCode), int(code.operator LPCTSTR()));
				}
				iLoop++;
			}
		}
	}
	else										// ������..
	{
		int	hSize = m_arHistory.GetSize();
		for (int ii = 0; ii < y; ii++)
		{
			for (int jj = 0; jj < x; jj++)
			{
				Key = ii*6 + jj + 1;
				if (!m_mapChart.Lookup(Key, pWnd))
					pWnd = CreateMTotal(Key);

				if (pWnd)
				{
					if (hSize > 0)
					{
						iLoop = iLoop % hSize;
						code = m_arHistory.GetAt(iLoop);
					}
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, onlyGigan), MAKELPARAM(GI_DAY, 0));
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranUnit), GU_CODE);
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranCode), int(code.operator LPCTSTR()));
				}
				iLoop++;
			}
		}
	}
}

char* CGrpMView::FindIndexCode(char *pCode)
{
	return (LPSTR)(LPCTSTR)m_pCfg->FindIndexCode(pCode);
}

void CGrpMView::OnSetMultiCode(LPARAM lParam)
{
	CStringArray* arCode = (CStringArray*)lParam;

	CWnd	*pWnd;
	CAxMTableMergeCtrl	*pMerge = (CAxMTableMergeCtrl*)m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, GetMergeCtrl), 0);
	int	Row = pMerge->GetRowCount();
	int	Col = pMerge->GetColCount();
	int	trSize = arCode->GetSize();
	m_iAutoTRCnt = trSize;

	if (trSize < 1)	return;

	if (m_pMultiChartInfo->btType == MT_SINGLE)		// üũ�� �͸� ������ ������.
	{
		CString	code = arCode->GetAt(0);
		int	unit;
		int	cSize = code.GetLength();
		if (cSize == 6)			// �����ڵ�
			unit = GU_CODE;
		else if (cSize == 3)	// ���� skip
		{
			this->PostMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoComplete), 1);
			return;
		}
		else
			unit = GU_FUTURE;

		for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
		{
			for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
			{
				int	Key = ii*6 + jj + 1;
				if (m_mapChart.Lookup(Key, pWnd) && pWnd->IsWindowVisible() &&
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
				{
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranUnit), unit);
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranCode), int(code.operator LPCTSTR()));
					
				}
			}
		}
	}
	else if (m_pMultiChartInfo->btType == MT_MULTI)		// üũ�� �͸� ��Ƽ�� ������.
	{
		int	cnt = 0;
		for (int ii = 0; ii < Row; ii++)		// ������ RowCount ��ŭ
		{
			for (int jj = 0; jj < Col; jj++)	// ������ ColCount ��ŭ
			{
				int	Key = ii*6 + jj + 1;
				if (m_mapChart.Lookup(Key, pWnd) && pWnd->IsWindowVisible() &&
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getCheckState), 0))
				{
					int	index = cnt % trSize;
					cnt++;

					int	unit;
					CString	code = arCode->GetAt(index);
					int	cSize = code.GetLength();
					if (cSize == 6)			// �����ڵ�
						unit = GU_CODE;
					else if (cSize == 3)	// ���� skip
					{
						PostMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoComplete), 1);
						continue;
					}
					else
						unit = GU_FUTURE;

					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranUnit), unit);
					pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoTranCode), int(code.operator LPCTSTR()));
					
				}
			}
		}
	}
	else if (m_pMultiChartInfo->btType == MT_MONITOR)	// üũ�� �����ϰ� ������ ������.
	{
		CString	code = arCode->GetAt(0);
		if (code.GetLength() != 6)	// �����ڵ常 ó���Ѵ�
		{
			PostMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoComplete), 1);
			return;
		}

		for (int ii = 0; ii < 3; ii++)
		{
			int	Key = ii+1;
			if (m_mapChart.Lookup(Key, pWnd))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(code.operator LPCTSTR()));
		}

		// �ش� ���� �ڵ带 ã�ƶ�
		char	*pICode = FindIndexCode((char*)code.operator LPCTSTR());
		if (pICode && strlen(pICode) == 3)
		{
			if (m_mapChart.Lookup(13, pWnd))
				pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, savedCodeInput), int(pICode));
		}

		if (m_mapChart.Lookup(14, pWnd))	// �׸���Ʈ
			pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), int(code.operator LPCTSTR()));
		if (m_mapChart.Lookup(15, pWnd))	// �����ں� �Ÿŵ���
			pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), int(code.operator LPCTSTR()));
	}
}

void CGrpMView::OnAutoTran(BOOL bSet)
{
	m_bAutotran = bSet? true:false;
	
	m_pwndInput->EnableWindow(!m_bAutotran);
	m_pwndCtrl->EnableWindow(!m_bAutotran);
	MultiEnableChart(!m_bAutotran);
}

void CGrpMView::OnAutoComplete(LPARAM lParam)
{
	m_iAutoTRCnt--;

	if (m_iAutoTRCnt <= 0)
		m_pCfg->ContinueAutoPlay();
}

void CGrpMView::OnInitAllChart()
{
	MultiChkMsg(GEV_VIEW, MAKEWPARAM(viewMulti, initAllChart), 0);
	InitMConfig();
}

void CGrpMView::OnTimer(UINT nIDEvent) 
{
	KillTimer(m_timerID);

	int	Key = 1;
	CWnd	*pWnd;
	if (m_mapChart.Lookup(Key, pWnd))
	{
		pWnd->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeView), 1);
		m_pwndCtrl->SendMessage(GEV_CTRL, MAKEWPARAM(CtrlMulti, CtrlInit), 0);
	}
	
	CWnd::OnTimer(nIDEvent);
}

void CGrpMView::Stay(DWORD dwGap)
{
	DWORD dwTickStop = ::GetTickCount() + dwGap;

	for (;;)
	{
		if (::GetTickCount() > dwTickStop)
			break;
	}
}