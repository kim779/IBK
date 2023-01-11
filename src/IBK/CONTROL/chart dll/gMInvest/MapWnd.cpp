// MapWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MapWnd.h"
#include "GrpWnd.h"
#include "../../h/axisgwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	SPACE		2
#define	CTRL_HEIGHT	18
#define	PNL_HEIGHT	22
#define	RBT_WIDTH	70

#define	CLR_BK		7
#define	CLR_TXT		63

#define	ID_BTNKOSPI	200
#define	ID_BTNKOSDAQ	201


#define LIN_NUM 4
#define MAX_REC 130

#define	TR_CHART	"bg703030"

struct  _mid720130 {
        char    gbdt[1];                /* 구분(0:시간별 1:일자별)      */
        char    sjcd[2];
        char    upcd[4];
        char    vagb[2];
        char    unit[2];
        char    tgab[2];
        struct  _cdHeader cdHeader;
};
#define	L_mid720130	sizeof(struct _mid720130)

/////////////////////////////////////////////////////////////////////////////
// CMapWnd

CMapWnd::CMapWnd(CWnd* view, CWnd* parent, int trKey)
{
	m_view = view;
	m_parent = parent;
	m_trKey = trKey;

	m_pKospiBtn = m_pKospiBtn = NULL;
	m_pGrpWnd = NULL;
	m_pcTemp = NULL;
	m_iTimerID = 0;

	m_enumCType = ctKospi;
}

CMapWnd::~CMapWnd()
{
}


BEGIN_MESSAGE_MAP(CMapWnd, CWnd)
	//{{AFX_MSG_MAP(CMapWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(GEV_VIEW, OnViewEvent)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapWnd message handlers

int CMapWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_app = (CaxisMInvestApp *)AfxGetApp();
	m_app->Init(m_view);
	updatePalette();

	m_pKospiBtn = new CButton();
	m_pKospiBtn->Create("거래소", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(0, 0, 0, 0), this, ID_BTNKOSPI);
	m_pKospiBtn->SetFont(m_app->m_font);
	m_pKospiBtn->SetCheck(TRUE);

	m_pKosdaqBtn = new CButton();
	m_pKosdaqBtn->Create("코스닥", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(0, 0, 0, 0), this, ID_BTNKOSDAQ);
	m_pKosdaqBtn->SetFont(m_app->m_font);

	struct _param	param;
	//param.key   = 
	param.name  = "CONTROL0";
	param.rect  = CRect(0, 0, 0, 0);
	param.fonts = "굴림";
	param.point = 9;
	param.style = 0;
	param.tRGB  = PALETTERGB(0, 0, 0);
	param.pRGB  = PALETTERGB(255, 255, 255);
	param.options = "/c/w외국인,개인,기관계,skip,skip/d500/r500/u1/t2/p0/n"; // "/c" ctrl

	m_pGrpWnd = new CGrpWnd(m_view, this, &param);
	m_pGrpWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 0);

	resize();	

	return 0;
}

BOOL CMapWnd::Create()
{
	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), m_parent, 100, NULL);

	return TRUE;
}

void CMapWnd::OnDestroy() 
{
	if (m_iTimerID)	
	{
		KillTimer(m_iTimerID);
		m_iTimerID = 0;
	}

	CWnd::OnDestroy();

	if (m_pcTemp)
		delete [] m_pcTemp;

	if (m_pKospiBtn)
	{
		m_pKospiBtn->DestroyWindow();
		delete m_pKospiBtn;
		m_pKospiBtn = NULL;
	}

	if (m_pKosdaqBtn)
	{
		m_pKosdaqBtn->DestroyWindow();
		delete m_pKosdaqBtn;
		m_pKosdaqBtn = NULL;
	}

	if (m_pGrpWnd)
	{
		m_pGrpWnd->DestroyWindow();
		delete m_pGrpWnd;
		m_pGrpWnd = NULL;
	}
}

void CMapWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cx == 0 || cy == 0)
		return;

	resize();	
}


long CMapWnd::OnUser(WPARAM wParam, LPARAM lParam)
{
	switch(LOBYTE(LOWORD(wParam)))
	{
	case DLL_SETPAL:
		if (m_pGrpWnd)
			m_pGrpWnd->SendMessage(WM_USER+100, wParam, lParam);
		updatePalette();
		Invalidate();
		break;
	case DLL_ALERT:
		m_cs.Lock();
		alert(wParam, lParam);
		m_cs.Unlock();
		break;
	case DLL_OUB:
		m_cs.Lock();
		if (m_pGrpWnd)
			m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);
		m_cs.Unlock();
		break;
	default:
		if (m_pGrpWnd)
			m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);
		break;
	}

	return 0;
}

long CMapWnd::OnViewEvent(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case viewMulti:
		switch (HIWORD(wParam))
		{
		case codeInput:			// code change by Input
			{
				SetCode((char*)lParam);
			}
			break;
		}
		break;
	}

	return 0;
}

void CMapWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.FillSolidRect(m_rcCtrl, m_clrBk);

	COLORREF	sColor = dc.SetTextColor(m_clrTxt);
	int			sMode = dc.SetBkMode(TRANSPARENT);
	CFont		*sFont = dc.SelectObject(m_app->m_font);

	dc.DrawText("[단위:억원] ", strlen("[단위:억원] "), m_rcTxt, DT_SINGLELINE|DT_VCENTER|DT_RIGHT);
	dc.SelectObject(sFont);
	dc.SetTextColor(sColor);
	dc.SetBkMode(sMode);
}

void CMapWnd::resize()
{
	CRect rcClient, rcTmp;
	GetClientRect(rcClient);

	rcTmp = CRect(SPACE, SPACE, SPACE + RBT_WIDTH, SPACE + CTRL_HEIGHT);
	m_pKospiBtn->MoveWindow(rcTmp);

	rcTmp.OffsetRect(rcTmp.Width() + 4, 0);
	m_pKosdaqBtn->MoveWindow(rcTmp);

	m_rcCtrl = rcClient;
	m_rcCtrl.bottom = PNL_HEIGHT;
	m_rcTxt = m_rcCtrl;
	m_rcTxt.left = rcTmp.right + 2;

	rcTmp = CRect(0, PNL_HEIGHT, rcClient.right, rcClient.bottom);
	m_pGrpWnd->MoveWindow(rcTmp);
}

void CMapWnd::updatePalette()
{
	m_clrBk = m_app->GetColor(m_view, CLR_BK);
	m_clrTxt = m_app->GetColor(m_view, CLR_TXT);
	m_brBk.DeleteObject();
	m_brBk.CreateSolidBrush(m_app->GetColor(m_view, CLR_BK));
}

BOOL CMapWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(LOWORD(wParam))
	{
	case ID_BTNKOSPI:
	case ID_BTNKOSDAQ:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			requestChart(m_pKospiBtn->GetCheck());
			break;
		}
		break;
	}
	
	return CWnd::OnCommand(wParam, lParam);
}

HBRUSH CMapWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
	case CTLCOLOR_BTN:
		pDC->SetBkColor(m_clrBk);
		hbr = (HBRUSH)m_brBk;
		break;
	}

	return hbr;
}

void CMapWnd::requestChart(BOOL Kospi)
{
	if (!m_pGrpWnd)
		return;

	if (Kospi)
		m_enumCType = ctKospi;
	else
		m_enumCType = ctKosdaq;

	CString sTmp;
	struct _mid720130*	pmid;

	if (m_pcTemp) delete [] m_pcTemp;
	m_pcTemp  = new char[L_mid720130 + L_userTH];
	ZeroMemory(m_pcTemp, L_mid720130 + L_userTH);

	pmid = (struct _mid720130 *)&m_pcTemp[L_userTH];
	pmid->gbdt[0] = '0';
	sprintf(pmid->sjcd, "%d", 1);
	sprintf(pmid->upcd, "%d", Kospi ? 1 : 9001);	// '1': kospi, '0': kosdaq
	sprintf(pmid->vagb, "%d", 4);			// '4':금액 '5':수량
	sprintf(pmid->unit, "%d", 1);			// 단위(억원)
	sprintf(pmid->tgab, "%d", 1);			// 시간Interval(1분단위)

	sTmp = (char *)m_pGrpWnd->SendMessage(WM_USER, MAKEWPARAM(DLL_INB, 0), 0);
	CopyMemory(&(pmid->cdHeader), sTmp, sizeof(struct  _cdHeader));

	_userTH* puserTH = (_userTH *)m_pcTemp;
	CopyMemory(puserTH->trc, TR_CHART, 8);
	puserTH->stat = 0;
	puserTH->key = (char)m_trKey;

	m_view->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, L_mid720130), (long)m_pcTemp);
}

void CMapWnd::SetCode(char* code)
{
	byte btCodeType;
	CString sCode(code), sName;
	sName = (char *)m_view->SendMessage(WM_USER, MAKEWPARAM(nameDLL, whichTYPE), (long)(LPSTR)(LPCTSTR)sCode);
	btCodeType = sCode[0];
	
	if (btCodeType == 2)
	{
		m_pKospiBtn->SetCheck(FALSE);
		m_pKosdaqBtn->SetCheck(TRUE);
	}
	else
	{
		m_pKospiBtn->SetCheck(TRUE);
		m_pKosdaqBtn->SetCheck(FALSE);
	}

	if (m_iTimerID > 0)	KillTimer(m_iTimerID);

	requestChart(m_pKospiBtn->GetCheck());

	m_iTimerID = 1001;
	SetTimer(m_iTimerID, 30000, NULL);
}

void CMapWnd::alert(WPARAM wParam, LPARAM lParam)
{
	if (!m_pGrpWnd)
		return;

	Sleep(0);
return;
	int pos;
	CString sCode, sData((char*)lParam);
	
	pos = sData.Find("\t");
	if (pos != -1)
	{
		sCode = sData.Left(pos);

		if (m_enumCType == ctKosdaq)
		{
			
		}
		else
		{

		}

		m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);
	}
}

void CMapWnd::OnTimer(UINT nIDEvent) 
{
	requestChart(m_pKospiBtn->GetCheck());
	CWnd::OnTimer(nIDEvent);
}
