// MainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "axisGMTotal.h"
#include "MainWnd.h"
#include "FileIO.h"
#include "ExtraMsg.h"
#include "PnInput.h"
#include "PnCtrl.h"
#include "../../chart_dll/Common/SavedHead.h"
#include "../../h/menudef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	TIMER_EXTR_TR	10001
#define	TIMER_NEXT_TR	10002	// 강제로 신규 종목을 조회해야 하는데 이미 TR중이라 부득이하게 다 받은후 처리
/////////////////////////////////////////////////////////////////////////////
// CMainWnd


CMainWnd::CMainWnd(CWnd *pView, CWnd* pParent, CString name, struct _param* pInfo, int mType)
{
	EnableAutomation();

	m_pwndView = pView;
	m_pwndParent = pParent;
	m_strDllName.Format("%s", name);
	m_strFName.Format("%s", pInfo->fonts);
	m_iFPoint = pInfo->point;

	m_iKey = pInfo->key;
	m_iType = mType;
	m_strIName.Format("%s\t", pInfo->name);
	m_strJName = _T("");
	m_ChartRC.SetRect(0, 0, 0, 0);

	m_pApp = (CAxisGMTotalApp *)AfxGetApp();
	m_pExtraMsg = new CExtraMsg(this);
	m_bActive = false;

	m_pwndInput = NULL;
	m_pwndChart = NULL;
	m_pwndCtrl = NULL;

	m_mapPanel.RemoveAll();

	m_strEnvPath = _T("");
	m_strGrpPath = _T("");
	m_strDatPath = _T("");
	m_strNextCode = _T("");

	m_pEnvInfo = NULL;
	ZeroMemory(m_pacRegion, sizeof(m_pacRegion));
	ZeroMemory(m_pacGraph, sizeof(m_pacGraph));
	ZeroMemory(&m_TrData, SZ_TRDATA);
	m_pcGDat = NULL;

	m_pcTemp = NULL;
	m_bForeign		= false;
	m_bTransaction		= false;
	m_bTransactionS		= false;
	m_bExtrTr		= false;

	m_iDtUnit = GU_CODE;
	m_iDtIndex = GI_DAY;
	m_iMGap = m_iTGap = 1;
	m_AutoUnit = GU_CODE;

	m_sParam.Format("%s", pInfo->options);
}

CMainWnd::~CMainWnd()
{
	if (m_pwndInput)
		LIB_DELETE(m_pwndInput);
	if (m_pwndChart)
		LIB_DELETE(m_pwndChart);
	if (m_pwndCtrl)
		LIB_DELETE(m_pwndCtrl);

	if (m_pEnvInfo)	BUF_DELETE(m_pEnvInfo);
	for (int ii = 0; ii < MAX_INDEX; ii++)
	{
		if (m_pacRegion[ii])	BUF_DELETE(m_pacRegion[ii]);
		if (m_pacGraph[ii])	BUF_DELETE(m_pacGraph[ii]);
	}
	if (m_pcTemp)	BUF_DELETE(m_pcTemp);
	if (m_pcGDat)	BUF_DELETE(m_pcGDat);

	if (m_TrData.pcData[0])
		BUF_DELETE(m_TrData.pcData[0]);

	if (m_TrData.pcData[1])
		BUF_DELETE(m_TrData.pcData[1]);

	DelPanels();
	delete m_pExtraMsg;

	for (ii = 0; ii < m_arData.GetSize(); ii++)
	{
		char* pcData = m_arData.GetAt(ii);
		delete pcData;
	}
	m_arData.RemoveAll();
	m_arLen.RemoveAll();
}

void CMainWnd::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnMessage)
	ON_MESSAGE(GEV_VIEW, OnViewEvent)
	ON_MESSAGE(GEV_CHART, OnChartEvent)
	ON_MESSAGE(GEV_INPUT, OnInputEvent)
	ON_MESSAGE(GEV_SISE, OnSiseEvent)
	ON_MESSAGE(GEV_CTRL, OnCtrlEvent)
	ON_MESSAGE(GEV_TOOL, OnToolEvent)
	ON_MESSAGE(GEV_TABLE, OnTableEvent)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CMainWnd, CWnd)
	//{{AFX_DISPATCH_MAP(CMainWnd)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMainWnd to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D84DE0C7-2D41-4A41-A2CF-BF86EA6A9B95}
static const IID IID_IMainWnd =
{ 0xd84de0c7, 0x2d41, 0x4a41, { 0xa2, 0xcf, 0xbf, 0x86, 0xea, 0x6a, 0x9b, 0x95 } };

BEGIN_INTERFACE_MAP(CMainWnd, CWnd)
	INTERFACE_PART(CMainWnd, IID_IMainWnd, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

LRESULT CMainWnd::OnMessage(WPARAM wParam, LPARAM lParam)
{
	switch (LOBYTE(LOWORD(wParam)))
	{
	case DLL_OUB:		// Tran Data
		Oub(wParam, lParam);
		m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, inputSiseUpdate), 0);
		break;
	case DLL_ALERT:		// RealTime
		if (m_pwndChart) 
		{
			//*Debug("DLL_ALERT = %s", (LPSTR)lParam);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REALTIME_DATA), lParam);
			m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, inputSiseUpdate), 0);
		}
		break;
	case DLL_TRIGGER:	// Trigger
		break;
	case DLL_DOMINO:	// Domino
		break;
	case DLL_DROP:		// OnDrop
		break;
	case DLL_INVOKE:
		// axisAP.h
		break;
	case DLL_SETPAL:	// Change Palette
		if (m_pwndInput)	m_pwndInput->SendMessage(GEV_INPUT, inputChgPalette, 0);
		if (m_pwndChart)	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(chartChgPalette, 0), 0);
		break;
	case DLL_SETFONT:
		break;
	case DLL_SETFCB:
		break;
	}

	return TRUE;
}

LRESULT CMainWnd::Oub(WPARAM wParam, LPARAM lParam)
{
	struct  _zcom_head* pZComHead = (struct  _zcom_head*)lParam;
	// 데이터가 여러번에 거쳐 올경우 저장

	int iTCnt = atoi(CString(pZComHead->tcnt, sizeof(pZComHead->tcnt)));
	int iSeqn = atoi(CString(pZComHead->seqn, sizeof(pZComHead->seqn)));

	char* pcTotalBuf = NULL;
	int iTotalLen = 0;

	if (iTCnt > 1)
	{
		int iLen = HIWORD(wParam) - SZ_ZCOMHEAD;
		char* pcBuf = new char[iLen];
		CopyMemory(pcBuf, (char*)lParam + SZ_ZCOMHEAD, iLen);
		m_arData.Add(pcBuf);
		m_arLen.Add(iLen);
		if (iSeqn < iTCnt - 1)
			return TRUE;

		
		for (int ii = 0; ii < m_arData.GetSize(); ii++)
		{
			iTotalLen += m_arLen.GetAt(ii);
		}

		pcTotalBuf = new char[iTotalLen];
		char* pcWrite = pcTotalBuf;
		for (ii = 0; ii < m_arData.GetSize(); ii++)
		{
			pcBuf = m_arData.GetAt(ii);
			iLen = m_arLen.GetAt(ii);

			CopyMemory(pcWrite, pcBuf, iLen);
			pcWrite += iLen;
			delete pcBuf;
		}
		

		m_arData.RemoveAll();
		m_arLen.RemoveAll();

		lParam = (LPARAM)pcTotalBuf;
	}
	else
	{
		lParam += SZ_ZCOMHEAD;
		wParam = MAKEWPARAM(LOWORD(wParam), HIWORD(wParam) - SZ_ZCOMHEAD);
	}

	if (m_bExtrTr)
	{
		m_TrData.iLen[0] = iTotalLen > 0 ? iTotalLen : HIWORD(wParam);
		m_TrData.pcData[0] = new char[m_TrData.iLen[0]];
		m_TrData.iSiseLen[0] = 0;
		CopyMemory(m_TrData.pcData[0], (char*)lParam, m_TrData.iLen[0]);

		SetTimer(TIMER_EXTR_TR, 1, NULL);
	}
	else if (m_bTransactionS)
	{
		m_TrData.iLen[0] = iTotalLen > 0 ? iTotalLen : HIWORD(wParam);
		m_TrData.pcData[0] = new char[m_TrData.iLen[0]];
		CopyMemory(m_TrData.pcData[0], (char*)lParam, m_TrData.iLen[0]);
		m_TrData.iSiseLen[0] = 0;

		if (!m_TrData.pcData[0] || m_TrData.iLen[0] == 0)
		{
			m_bTransactionS = false;
			if (pcTotalBuf)
				delete pcTotalBuf;
			return 0;
		}

		m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_TR_DATAS, 0), (LPARAM)&m_TrData);

		delete m_TrData.pcData[0];
		ZeroMemory(&m_TrData, sizeof(m_TrData));
		m_bTransaction = false;
		m_bTransactionS = false;
	}
	else
	{
		m_TrData.iLen[m_iTRIndex] = iTotalLen > 0 ? iTotalLen : HIWORD(wParam);
		m_TrData.pcData[m_iTRIndex] = new char[m_TrData.iLen[m_iTRIndex]];
		CopyMemory(m_TrData.pcData[m_iTRIndex], (char*)lParam, m_TrData.iLen[m_iTRIndex]);

		if (m_TrData.iLen[0] == 0 || m_TrData.pcData[0] == NULL)
		{
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_TR_DATA, 0), NULL);
			m_bTransaction = false;
			m_pwndParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoComplete), 1);

			if (pcTotalBuf)
				delete pcTotalBuf;
			return 0;
		}

		SendMessage(GEV_SISE, MAKEWPARAM(SISE_TR_DATA, NULL), (LPARAM)&m_TrData);
		m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_TR_DATA, 0), (long)&m_TrData);

		delete m_TrData.pcData[0];
		if (m_TrData.pcData[1])
			delete m_TrData.pcData[1];

		ZeroMemory(&m_TrData, sizeof(m_TrData));
		
		m_bTransaction = false;
		m_pwndParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, autoComplete), 1);

		if (!m_strNextCode.IsEmpty())
			SetTimer(TIMER_NEXT_TR, 1, NULL);
	}

	if (pcTotalBuf)
		delete pcTotalBuf;

	return TRUE;
}

LRESULT CMainWnd::OnMultiEvent(WPARAM wParam, LPARAM lParam)
{
	WORD	mMsg = HIWORD(wParam);
	switch (mMsg)
	{
	case codeInput:	// 코드(unit) 완료
		m_strCode = (char*)lParam;
		CheckUnit(-1);
		SendRequest();
		break;
	case codeMultiInput:
		if (m_bTransaction || m_bTransaction)
		{
			m_strNextCode = (char*)lParam;
		}
		else
		{
			m_strCode = (char*)lParam;
			CheckUnit(-1);
			SendRequest();
		}
		break;
	case savedCodeInput:
		if ((m_iType == MT_MONITOR && m_iKey == 9) || (m_iType == MT_FOREIGN && m_iKey == 3))	// 선물 시세
			m_strCode = (char*) m_pwndView->SendMessage(WM_USER, MAKEWPARAM(codeDLL, getCODEfuture), 0);
		else
			m_strCode = (char*)lParam;

		SendRequest();
		break;
	case autoTranUnit:
		m_AutoUnit = lParam;
		break;
	case autoTranCode:
		m_strCode = (char*)lParam;
		CheckUnit(m_AutoUnit);
		SendRequest();
		break;
	case totalInput:	// 기간 완료
		m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartTotal), lParam);
		SendRequest();
		break;
	case total2Input:	// 멀티 기간(일주월분틱 int Array)
		{
			int	*pTotal = (int*)lParam;
			if (!pTotal || m_iDtIndex > GI_TICK)
				return 0;

			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartTotal), pTotal[m_iDtIndex - GI_DAY]);
			SendRequest();
		}
		break;
	case todayInput:	// 당일 체크
		{
			struct _envInfo* pEnvInfo = (struct _envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
			if (pEnvInfo->datainfo.cToday == lParam)
				break;

			pEnvInfo->datainfo.cToday = char(lParam);
			if (m_iDtIndex == GI_MINUTE || m_iDtIndex == GI_TICK)
				SendRequest();
		}
		break;
	case activeView:	// 처음 오픈시 맨 처음 차트에게 전달됨
		OnActiveEvent(lParam? true:false);
		break;
	case activeInfo:	// get current chart info(MView->MTotal)
			sprintf(m_ActiveChartInfo.acCode, "%s", m_strCode);
			m_ActiveChartInfo.iUnit = m_iDtUnit;
			m_ActiveChartInfo.iIndex = m_iDtIndex;
			m_ActiveChartInfo.iMGap = m_iMGap;
			m_ActiveChartInfo.iTGap = m_iTGap;
			m_ActiveChartInfo.iRCnt = SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA,GET_TOTAL_DAY), 0);
			m_ActiveChartInfo.iToday = SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, GET_TODAY), 0);
			return int(&m_ActiveChartInfo);
	case inactiveView:	// 다른 차트가 액티브 됬을때 전달됨
		OnInActiveEvent();
		break;
	case getCheckState:	// 체크된 상태를 요구
		if (m_pwndInput)
			return m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, getCheckBox), 0);
		return 0;
	case setCheckState:	// 강제로 체크
		if (m_pwndInput)
			m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, setCheckBox), lParam);
		break;
	case giganInput:	// 일주월..갭 전달
	case onlyGigan:		// TR날리지 않고 일주월..갭 전달
		{
			int	index = LOWORD(lParam);
			int	gap = HIWORD(lParam);

			if (m_iDtUnit == GU_FOREIGN && (index == GI_MINUTE || index == GI_TICK))	
				return 0;		// 해외차트에서는 분/틱 스킵

			if (index == GI_MINUTE)
			{
				if (m_iDtIndex == index && m_iMGap == HIWORD(lParam))	
					return 0;
			}
			else if (m_iDtIndex == index && index == GI_TICK)
			{
				if (m_iTGap == HIWORD(lParam))	
					return 0;
			}
			else if (index == m_iDtIndex)
				return 0;

			if (m_pwndInput)
				m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(InputMulti, inputIndex), lParam);
			if (mMsg == giganInput)
				SendRequest();
		}
		break;
	case mainInput:	// get Main Chart
		{
			struct _envInfo* env = (struct _envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
			if (this->m_strJName.IsEmpty())
				return GK_PV;
			return env->datainfo.wMainGrpKind;
		}
	case getMapCode:
		return int(m_strCode.operator LPCTSTR());
	case mTotalTran:
		SendRequest();
		break;
	case initAllChart:
		InitGraph();
		break;
	}

	return TRUE;
}

LRESULT CMainWnd::OnViewEvent(WPARAM wParam, LPARAM lParam)
{
	struct _graph	graph;
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
		case getDatPath:
			return (LRESULT)(LPCTSTR)m_strDatPath;
			break;
		case requestTR:
			SendRequest();
			break;
		case requestTRS:
			SendRequestS();
			break;
		}
		break;
	case viewDialog:
		switch (HIWORD(wParam))
		{
		case dlgSave:	break;
		case dlgEnv:
			EnvProc();
			break;
		case dlgEnvchart: // direct call
			if (CallEnvDlg(NULL, true))
				m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_ENV_INFO));
			break;
		case dlgMap:	// 화면 설정(region + graph), lParam - _interChart *
			{
				if (m_pcTemp)	BUF_DELETE(m_pcTemp);
				
				_interChart	*iChart = (_interChart*)lParam;
				int	bufSize = sz_INTERCHART + SZ_REGION*iChart->rgncnt + SZ_GRAPH*iChart->grpcnt;
				m_pcTemp = new char[bufSize];
				CopyMemory(m_pcTemp, (char*)lParam, bufSize);

				char* pScreen = CallMapDlg(m_pcTemp);
				BUF_DELETE(m_pcTemp);

				if (!pScreen)	return FALSE;

				SyncMap(pScreen);
			}
			break;
		case DlgIndc:	// 개별 차트 설정, lParam - _graph *
			return CallEnvDlg((char*)lParam, false);
		case dlgSIndc:
			return CallStandardIndc(lParam);
		case dlgTool:
			return CallToolDlg((char *)lParam);
		case dlgJCode:
		case dlgUCode:
		case dlgFCode:
		case dlgOCode:	
		case dlgJUCode:
		case dlgFOCode:
		default:
			break;
		}
		break;
	case viewMain:
		switch (HIWORD(wParam))
		{
		case getPalette:	return m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), lParam);
		case getHistory:	break;
		case setHistory:	break;
		case setTrigger:	break;
		case openView:
			m_pwndView->PostMessage(WM_USER, MAKEWPARAM(viewDLL, typeVIEW), lParam);
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
	case viewChartInfo:
		switch (HIWORD(wParam))
		{
		case getMapInfo:	// 맵그래프 정보
			return (LRESULT)GetMapInfo();
		case setMapInfo:	// 맵그래프 정보
			break;
		case getSGrpInfo:	// 개별 그래프 정보(from dat file)
			return GetGrpFromDat((char*)lParam);
		case getDatInfo:	// 전체 그래프 기본정보
			return (LRESULT)GetDat();
		case initGrpInfo:
			InitGraph();
			break;
		}
		break;
	case viewCode:
		switch (HIWORD(wParam))
		{
		case hideList:	break;
		case showGroupTree:	break;
		case getPreCode:	break;
		case getNextCode:	break;
		}
		break;
	case viewUtility:
		switch(HIWORD(wParam))
		{
		case viewImage:
			{
				CString	path, tmpS;
				path = m_pApp->GetUserPath() + m_strDllName + ".bmp";

				if (CFileIO::ImageWindow(this, path))
				{
					tmpS = path + _T("로 저장되었습니다");
					AfxGetMainWnd()->MessageBox(tmpS, "확인", MB_OK);
				}
			}
			break;
		case viewPrint:
			CFileIO::PrintWindow(this, false);
			break;
		case viewExcel:
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, excelData), 0);
			break;
		}
		break;
	case viewNotify:
		switch (HIWORD(wParam))
		{
		case dispDayChart:
			if (m_bActive)	
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlDisplay), lParam);
			break;
		case dispDayInput:	break;
		case dispDayCtrl:		// 컨트롤에서 보는일자 변경
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, CHART_DISPLAY), lParam);
			break;
		case dispScaleChart:	// 그래프에서 보는일자 드래그 **
			if (m_bActive)
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlDisplay), lParam);
			break;
		case dispScaleCtrl:	// 컨트롤에서 확장/축소 버튼 **
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartScale), lParam);
			break;
		case mainChart:	// Main change by Chart
			if (m_bActive)
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlMain), lParam);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_MAIN_GRP), lParam);
			break;
		case aidAddChart:
			if (!IsAidAddable(lParam)) return 0L;

			graph.wGKind = WORD(lParam);
			GetGrpFromDat((char*)&graph);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, ADD_AID_GRP), (long)&graph);
			break;
		case aidDelChart:	
			break;
		case aidAddCfg:	// Add Aid by Cfg **
			if (!IsAidAddable(lParam)) return 0L;

			graph.wGKind = WORD(lParam);
			GetGrpFromDat((char*)&graph);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, ADD_AID_GRP), (long)&graph);
			break;
		case aidDelCfg:		// Delete Aid by Cfg **
			if (MainChartIsVarType()) return 0L;

			graph.wGKind = WORD(lParam);
			GetGrpFromDat((char*)&graph);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, delAidGrp), (long)&graph);
			break;
		case unitInput:
//			if (m_pwndInput)
//				m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_CHANGE, ipUnit), lParam);
//			else	
				m_pExtraMsg->InputEvent(MAKEWPARAM(INPUT_CHANGE, ipUnit), lParam);

			SendMessage(GEV_SISE, siseUnit, lParam);
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartUnit), lParam);
			if (m_bActive)
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlUnit), lParam);
			break;
		case inputAutotran:	break;
		case gridChart:		// view grid by chart
			if (m_bActive)	
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlGrid), lParam);
			break;
		case gridCtrl:		// view grid by ctrl
			if (m_pwndChart)	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartGrid), lParam);
			break;
		case tipChart:		// tooltip by chart
			if (m_bActive)	
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlTip), lParam);
			break;
		case tipCtrl:		// tooltip by ctrl
			if (m_pwndChart)	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartTip), lParam);
			break;		
		case cfgMainChart:	// change Main Chart by CFG **
				m_pExtraMsg->InputEvent(MAKEWPARAM(inputEnv, inputMain), lParam);
			if (m_bActive)
				m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlMain), lParam);
			if (m_pwndChart)
				m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_MAIN_GRP), lParam);
			break;
		case indexInput:	// 일주월 완료
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartIndex), lParam);
			if (m_pEnvInfo)		IndexChange(LOWORD(lParam));	
			break;
		}
		break;
	case viewMulti:
		return OnMultiEvent(wParam, lParam);
//	case viewWindow:
//		break;
	}

	return TRUE;
}

LRESULT CMainWnd::OnChartEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_pwndChart)	return m_pwndChart->SendMessage(GEV_CHART, wParam, lParam);
	return FALSE;
}

LRESULT CMainWnd::OnInputEvent(WPARAM wParam, LPARAM lParam)
{
//	if (m_pwndInput)	
//		return m_pwndInput->SendMessage(GEV_INPUT, wParam, lParam);
//	else		
		return m_pExtraMsg->InputEvent(wParam, lParam);
	
	return FALSE;
}

LRESULT CMainWnd::OnSiseEvent(WPARAM wParam, LPARAM lParam)
{
	return m_pExtraMsg->SiseEvent(wParam, lParam);
}

LRESULT CMainWnd::OnCtrlEvent(WPARAM wParam, LPARAM lParam)
{
	if (m_bActive)
		return m_pwndParent->SendMessage(GEV_CTRL, wParam, lParam);

	return FALSE;
}

LRESULT CMainWnd::OnToolEvent(WPARAM wParam, LPARAM lParam)
{
	// 2006.11.20 lsh (start)
	switch(LOWORD(wParam))
	{
	case TOOL_MAP_CLICK_EVENT:
		{
			CString ctrlName;
			ctrlName = m_strIName.Left(m_strIName.GetLength() -1);
			m_pwndView->SendMessage(WM_USER, MAKEWPARAM(eventDLL, MAKEWORD(m_iKey, evOnClick)), (long)ctrlName.operator LPCTSTR());
		}
		break;
	}
	// 2006.11.20 lsh (end)
	return FALSE;
}

LRESULT CMainWnd::OnTableEvent(WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_strEnvPath.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_strDllName, ENV);
	m_strGrpPath.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_strDllName, GRP);
	m_strDatPath.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_strDllName, DAT);

	m_pEnvInfo = (_envInfo*)new char[SZ_ENVINFO];
	if (!ReadEnv() || !ReadGrp())
	{
		if (!ReMakeFile())
			return -1;
	}


	ModifyEnv();

	// 챠트설정반영
	CString sToken;

	m_iDtUnit = m_pEnvInfo->datainfo.btUnit;
	m_iDtIndex = m_pEnvInfo->datainfo.btIndex;
	m_iMGap = m_pEnvInfo->datainfo.wMGap;
	m_iTGap = m_pEnvInfo->datainfo.wTGap;
	if (m_pEnvInfo->datainfo.btUnit == GU_FOREIGN)
		m_bForeign = true;

	CTime	time = CTime::GetCurrentTime();
	m_strDay.Format("%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());

	m_pFont = m_pApp->GetFont(m_pwndView, m_iFPoint, m_strFName);

	if (!m_pApp->m_hGMainLib)
	{
		m_pApp->m_hGMainLib = LoadLibrary("axisGMain.dll");
	}

	if (!m_pApp->m_hGMainLib)
	{
		AfxGetMainWnd()->MessageBox("axisGMain.dll LoadLibrary error", COMPANYNAME);
		return -1;
	}

	InitPnInfo(m_pEnvInfo->panel);
	CreatePn();
	
	return 0;
}

void CMainWnd::OnDestroy() 
{
	WriteDat();
	if (WriteEnv())
		WriteGrp();

	CWnd::OnDestroy();
}

void CMainWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cx == 0 && cy == 0)
		return;
	ResizeWnd(CRect(0, 0, cx, cy));
}

void CMainWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == TIMER_EXTR_TR)
	{
		KillTimer(nIDEvent);
		SendRequest2();
	}
	else if (nIDEvent == TIMER_NEXT_TR)
	{
		KillTimer(nIDEvent);
		SendNextTR();
	}

	CWnd::OnTimer(nIDEvent);
}

int CMainWnd::GetToken(char *pData, char token[])
{
	int	idx = 0;
	ZeroMemory(token, sizeof(token));
	for(;;)
	{
		switch (pData[idx])
		{
		case '\t':
			token[idx++] = 0x00;
			return idx;
		case '\n':
			token[idx++] = 0x00;
			return idx;
		default:
			token[idx] = pData[idx];
			idx++;
			break;
		}
	}

	return 0;
}

////////////////////////////////////

void CMainWnd::ResizeWnd(CRect wRC)
{
	int cx = wRC.Width();
	int cy = wRC.Height();
	
	int mhInput = GetPnSize(PN_INPUT) - 8;
	int mhCtrl = 0;//GetPnSize(PN_CTRL);

	if (m_pwndInput)	m_pwndInput->MoveWindow(0, 0, cx, mhInput);
	if (m_pwndCtrl)		m_pwndCtrl->MoveWindow(0, cy - mhCtrl, cx, mhCtrl);
	if (m_pwndChart)
	{
		m_ChartRC.left = 0;
		m_ChartRC.top = mhInput+1;
		m_ChartRC.right = m_ChartRC.left + (cx);
		m_ChartRC.bottom = cy-mhCtrl;

		CRect	rc;
		rc.left = m_ChartRC.left+2;
		rc.top = m_ChartRC.top;
		rc.right = m_ChartRC.right-2;
		rc.bottom = m_ChartRC.bottom-2;
		
		m_pwndChart->MoveWindow(rc);
	}
}

int CMainWnd::GetPnSize(int ctrlID)
{
	int size = 0;
	struct _pninfo *pninfo = NULL;
	if (!m_mapPanel.Lookup(ctrlID, pninfo))
		return size;

	if (pninfo->info & PO_USE)
	{
		if (pninfo->info & PO_SHOW)
			size = pninfo->whsize;
		else 
			size = 0;
	}
	return size;
}

void CMainWnd::InitPnInfo(struct _panel *panel)
{
	struct _pninfo	*pninfo = NULL;
	int iPnID = 0;
	int size = 0;
	WORD info = 0;
	for (int ii = 0; ii < PANEL_CNT; ii++)
	{
		if ((iPnID = panel[ii].btPnID) == 0)
			continue;

		info = panel[ii].wPnOption;
		pninfo = new struct _pninfo();
		memset(pninfo, 0x00, sizeof(struct _pninfo));
		if (info & PO_USE)
		{
			switch (iPnID)
			{
			case PN_INPUT:
				size = HEIGHT_INPUT;
				break;
			case PN_SISE:
				size = HEIGHT_SISE;
				break;
			case PN_CTRL:
				size = HEIGHT_CTRL;
				break;
			}
		}
		pninfo->whsize = size;
		pninfo->info = info;
		panel[ii].wPnOption = info;
		m_mapPanel.SetAt(iPnID, pninfo);
	}
}

void CMainWnd::CreatePn()
{
	struct _pninfo *pninfo;

	m_pwndChart = CreateWnd(PN_CHART, m_pwndChart);

	pninfo = GetPnInfo(PN_INPUT);
	if (pninfo)	m_pwndInput = CreateWnd(PN_INPUT, m_pwndInput);

//	pninfo = GetPnInfo(PN_CTRL);
//	if (pninfo)	m_pwndCtrl = CreateWnd(PN_CTRL, m_pwndCtrl);
}

struct _pninfo* CMainWnd::GetPnInfo(int localID)
{
	struct _pninfo *pninfo = NULL;
	if (!m_mapPanel.Lookup(localID, pninfo))
		return NULL;

	return pninfo;
}

CWnd* CMainWnd::CreateWnd(int ctrlID, CWnd* pWnd)
{
	switch (ctrlID)
	{
	case PN_INPUT:	
		{
			if (pWnd)	return pWnd;
			struct _pninfo* pninfo = GetPnInfo(ctrlID);
			if (!pninfo || !(pninfo->info & PO_USE))
				break;

			pWnd = new CPnInput(m_pwndView, this, m_pFont, ctrlID, (char *)m_pEnvInfo);
			pWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 
				CRect(0, 0, 0, 0), this, 0);

			pWnd->MoveWindow(0, 0, 0, 0);

			return pWnd;
		}
		break;
	case PN_CTRL:	
		{
			if (pWnd)	return pWnd;
			struct _pninfo* pninfo = GetPnInfo(ctrlID);
			if (!pninfo || !(pninfo->info & PO_USE))
				break;

			pWnd = new CPnCtrl(m_pwndView, this, m_pFont, ctrlID, (char *)m_pEnvInfo);
			pWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 
				CRect(0, 0, 0, 0), this, 0);

			pWnd->MoveWindow(0, 0, 0, 0);

			return pWnd;
		}
		break;
	case PN_CFG:	break;
	case PN_CHART:
		{
			if (pWnd)	return pWnd;
			CWnd*	(APIENTRY *axCreateCtrl)(int, CWnd *, CWnd *, char *, CFont *);
			axCreateCtrl = (CWnd* (APIENTRY *)(int, CWnd *, CWnd *, char *, CFont *))
				GetProcAddress(m_pApp->m_hGMainLib, "axCreateCtrl");
			pWnd = axCreateCtrl(GEV_CHART, m_pwndView, this, (char *)m_pEnvInfo, m_pFont);
			pWnd->MoveWindow(0, 0, 0, 0);

			return pWnd;
		}
		break;
	}
	return NULL;
}

void CMainWnd::SendRequest()
{
	if (m_bTransaction || m_bTransactionS || !m_pwndChart)
		return;

	m_bTransaction = true;
	m_bTransactionS = false;

	m_iTRIndex = 0;
	ZeroMemory(&m_TrData, SZ_TRDATA);

	int dataHLen;
	if (m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_HEADER2), long(&dataHLen)))
		m_bExtrTr = true;
	else
		m_bExtrTr = false;

	if (m_pcTemp)
		BUF_DELETE(m_pcTemp);

	int	inputLen = 0;
	char	inputStr[128];
	
//	if (m_pwndInput)
//		inputLen = m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, GET_TR_INFO), (long)inputStr);
//	else
		inputLen = m_pExtraMsg->InputEvent(MAKEWPARAM(INPUT_DATA, GET_TR_INFO), (long)inputStr);

	if (inputLen == 0)
	{
		m_bTransaction = false;
		return;
	}
	
	char	*gDataH;
	if (m_pwndChart)
	{
		gDataH = (char*)m_pwndChart->SendMessage(GEV_CHART, 
			MAKEWPARAM(CHART_DATA, REQUEST_HEADER), long(&dataHLen));
	}
	
	int	TRLen = inputLen + dataHLen;
	m_pcTemp = new char[TRLen + L_userTH];
	_userTH *userTH = (_userTH *)m_pcTemp;

	ZeroMemory(userTH, L_userTH);
	CopyMemory(userTH->trc, GRP_HOOP, 8);
	userTH->stat = US_OOP;
	userTH->key = m_iKey;
	
	CopyMemory(&m_pcTemp[L_userTH], inputStr, inputLen);
	CopyMemory(&m_pcTemp[L_userTH + inputLen], gDataH, dataHLen);

	int ret = m_pwndParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, TRLen), (long)m_pcTemp);
}

void CMainWnd::SendRequest2()
{
	m_iTRIndex++;
	m_bExtrTr = false;
	if (m_pcTemp)
		BUF_DELETE(m_pcTemp);

	int	inputLen = 0;
	char	inputStr[128];
//	if (m_pwndInput)
//		inputLen = m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, getTRInfo2), (long)inputStr);
//	else
		inputLen = m_pExtraMsg->InputEvent(MAKEWPARAM(INPUT_DATA, getTRInfo2), (long)inputStr);

	if (inputLen == 0)
	{
		m_bTransaction = false;
		return;
	}

	int	dataHLen;
	char	*gDataH;
	if (m_pwndChart)
	{
		gDataH = (char*)m_pwndChart->SendMessage(GEV_CHART, 
			MAKEWPARAM(CHART_DATA, REQUEST_HEADER2), long(&dataHLen));
	}
	
	int	TRLen = inputLen + dataHLen;
	m_pcTemp = new char[TRLen + L_userTH];

	_userTH *userTH = (_userTH *)m_pcTemp;

	ZeroMemory(userTH, L_userTH);
	CopyMemory(userTH->trc, GRP_HOOP, 8);
	userTH->stat = US_OOP;
	userTH->key = m_iKey;
	
	CopyMemory(&m_pcTemp[L_userTH], inputStr, inputLen);
	CopyMemory(&m_pcTemp[L_userTH + inputLen], gDataH, dataHLen);

	m_pwndParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, TRLen), (long)m_pcTemp);
}

// request single data
void CMainWnd::SendRequestS()
{
	m_iTRIndex = 0;
	if (m_pcTemp)
		BUF_DELETE(m_pcTemp);

	m_bTransactionS = true;

	int	inputLen = 0;
	char	inputStr[128];
//	if (m_pwndInput)
//		inputLen = m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, getTRInfo2), (long)inputStr);
//	else
		inputLen = m_pExtraMsg->InputEvent(MAKEWPARAM(INPUT_DATA, getTRInfo2), (long)inputStr);

	if (inputLen == 0)
	{
		m_bTransactionS = false;
		return;
	}

	int	dataHLen;
	char	*gDataH;
	if (m_pwndChart)
	{
		gDataH = (char*)m_pwndChart->SendMessage(GEV_CHART, 
			MAKEWPARAM(CHART_DATA, requestHeaderS), long(&dataHLen));
	}
	
	int	TRLen = inputLen + dataHLen;
	m_pcTemp = new char[TRLen + L_userTH];

	_userTH *userTH = (_userTH *)m_pcTemp;

	ZeroMemory(userTH, L_userTH);
	CopyMemory(userTH->trc, GRP_HOOP, 8);
	userTH->stat = US_OOP;
	userTH->key = m_iKey;
	
	CopyMemory(&m_pcTemp[L_userTH], inputStr, inputLen);
	CopyMemory(&m_pcTemp[L_userTH + inputLen], gDataH, dataHLen);

	m_pwndParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, TRLen), (long)m_pcTemp);
}

void CMainWnd::SendNextTR()
{
	m_strCode = m_strNextCode;
	m_strNextCode = _T("");
	CheckUnit(-1);
	SendRequest();
}

int CMainWnd::WhichFOCode(LPCTSTR code)
{
	CString cd(code);
	if (cd.GetLength() != 8) return foNone;

	if ((cd[0] == '2' || cd[0] == '3'))
	{
		return foOption;
	}
	else if (cd[0] == '1')	// 1xxxxxxx
	{
		if (cd[1] >= '1')	// 11xxxxxx
			return foCoFut;
		else if (cd[2] == '3')
			return foStar;

		return foFuture;
	}
	else	// "4xxxxxxx	spread
	{
		return foFuture;
	}

	return foFuture;
}

void CMainWnd::DelPanels()
{
	struct _pninfo *pninfo = NULL;
	int pID = 0;
	POSITION pos;
	for (pos = m_mapPanel.GetStartPosition(); pos; )
	{
		m_mapPanel.GetNextAssoc(pos, pID, pninfo);
		BUF_DELETE(pninfo);
	}
	m_mapPanel.RemoveAll();
}

void CMainWnd::SavePanel(struct _panel *panel)
{
	memset(panel, 0x00, SZ_PANEL * PANEL_CNT);
	struct _pninfo *pninfo = NULL;
	int localID = 0;
	int panelID = 0;
	POSITION pos;
	int ii = 0;
	for (pos = m_mapPanel.GetStartPosition(); pos; )
	{
		m_mapPanel.GetNextAssoc(pos, localID, pninfo);
		if (!pninfo)	continue;
		panel[ii].btPnID = localID;
		panel[ii].wPnOption = pninfo->info;
		ii++;
	}
}

char* CMainWnd::GetDat()
{
	if (m_pcGDat)
		return m_pcGDat;

	ReadData();

	return m_pcGDat;
}

bool CMainWnd::ReadData()
{
	DWORD dwReadLen;
	CSavedHead sh;
	char* pcDat = sh.Read(m_strDatPath, dwReadLen);

	if (!pcDat || dwReadLen < 1)
		return false;

	if (sh.m_sh.dwVersion != VERSION_DAT)
	{
		return false;
	}

	if (m_pcGDat)
		delete m_pcGDat;

	m_pcGDat = new char[sh.m_sh.dwDataLength];
	CopyMemory(m_pcGDat, pcDat, sh.m_sh.dwDataLength);

//	CheckNewList();

	return true;
}

bool CMainWnd::ReMakeFile()
{
	m_pApp->ReMakeFile(m_pwndView);
	if (!ReadEnv() || !ReadGrp())
		return false;

	return true;
}

char* CMainWnd::GetMapInfo(int wKey)
{
	if (m_pcTemp)	BUF_DELETE(m_pcTemp);

	int	index = m_iDtIndex - GI_DAY;
	int	rcnt = m_pEnvInfo->grpinfo[index].wRgnCnt;
	int	gcnt = m_pEnvInfo->grpinfo[index].wGrpCnt;
	struct _interChart ichart;
	if (wKey == -1)	// all
	{
		m_pcTemp = new char[sz_INTERCHART + rcnt*SZ_REGION + 
			gcnt*SZ_GRAPH];
		
		ichart.bAll = 1;
		ichart.grpcnt = gcnt;
		ichart.rgncnt = rcnt;
		
		CopyMemory(m_pcTemp, (char *)&ichart, sz_INTERCHART);
		CopyMemory(&m_pcTemp[sz_INTERCHART], m_pacRegion[index], rcnt*SZ_REGION);
		CopyMemory(&m_pcTemp[sz_INTERCHART + rcnt*SZ_REGION], m_pacGraph[index], 
			gcnt*SZ_GRAPH);
	}
	else		// unique key
	{
		m_pcTemp = new char[sz_INTERCHART+SZ_GRAPH];
		ichart.bAll = 0;
		ichart.grpcnt = 1;
		ichart.rgncnt = 0;
		for (int ii = 0; ii < gcnt; ii++)
		{
			struct _graph *pGrp = (struct _graph*)&m_pacGraph[index][ii * SZ_GRAPH];
			if (pGrp->wKey == wKey)
			{
				CopyMemory(m_pcTemp, &ichart, sz_INTERCHART);
				CopyMemory(&m_pcTemp[sz_INTERCHART], pGrp, SZ_GRAPH);
				break;
			}
		}

		if (ii >= gcnt)
			return NULL;
	}

	return m_pcTemp;
}

bool CMainWnd::GetGrpFromDat(char *info)
{
	struct _graph	*graph = (struct _graph*)info;

	char	*pDat = GetDat();
	if (pDat == NULL)
		return false;

	struct _cntInfo *cntInfo = (struct _cntInfo *)pDat;
	int	count = cntInfo->wMainCnt + cntInfo->wAidCnt;
	for (int ii = 0; ii < count; ii++)
	{
		struct _graph *pGrp = (struct _graph*)&pDat[SZ_CNTINFO + SZ_GRAPH*ii];
		if (graph->wGKind == pGrp->wGKind)
		{
			CopyMemory(graph, pGrp, SZ_GRAPH);
			return true;
		}
	}

	return false;
}

bool CMainWnd::SetGrpAtDat(char *info)
{
	struct _graph	*graph = (struct _graph*)info;

	char	*pDat = GetDat();
	if (pDat == NULL)
		return false;

	switch (graph->wGKind)
	{
	case GK_JPN:	case GK_BAR:	case GK_LIN:	case GK_POLE:
	case GK_EQV:	case GK_CDV:
	case GK_CLOCK:	case GK_PV:	case GK_THREE:	case GK_PNF:	case GK_SWING:
	case GK_KAGI:	case GK_RENKO:
	case GK_BALANCE:	case GK_AVOL:
		break;
	default:
		return false;
	}

	struct _cntInfo *cntInfo = (struct _cntInfo *)pDat;
	int	count = cntInfo->wMainCnt + cntInfo->wAidCnt;
	for (int ii = 0; ii < count; ii++)
	{
		struct _graph *pGrp = (struct _graph*)&pDat[SZ_CNTINFO + SZ_GRAPH*ii];
		if (graph->wGKind == pGrp->wGKind)
		{
			CopyMemory(pGrp, graph, SZ_GRAPH);
			return true;
		}
	}

	return false;
}

BOOL CMainWnd::IsAidAddable(LPARAM lParam)
{
	if (MainChartIsVarType())
		return FALSE;

	switch (lParam)
	{
	case GK_RRATE:		// 회전율(주 - 일주월)
		if ((m_iDtUnit == GU_CODE) && 
			(m_iDtIndex == GI_DAY || m_iDtIndex == GI_WEEK || m_iDtIndex == GI_MONTH))
			return TRUE;
		return FALSE;
	case GK_AMT:		// 거래대금(주,업 - 일주월)
	case GK_AMA:		// 대금이평(주,업 - 일주월)
		if ((m_iDtUnit == GU_CODE || m_iDtUnit == GU_INDEX) && 
			(m_iDtIndex == GI_DAY || m_iDtIndex == GI_WEEK || m_iDtIndex == GI_MONTH))
			return TRUE;
		return FALSE;
	case GK_ADR:		// ADR
		if (m_iDtUnit == GU_INDEX && m_iDtIndex == GI_DAY)
			return TRUE;
		return FALSE;
	case GK_FRGNHAVE:	// 외국인보유현황(수량)
	case GK_FRGNRATE:	// 외국인보유비율
		if (m_iDtUnit == GU_CODE && m_iDtIndex == GI_DAY)
			return TRUE;
		return FALSE;
	case GK_PSNLPBUY:	// 개인순매수량
	case GK_FRGNPBUY:	// 외국인순매수량
	case GK_ORGNPBUY:	// 기관순매수량
	case GK_PSNLTBUY:	// 개인누적순매수량
	case GK_FRGNTBUY:	// 외국인누적순매수량
	case GK_ORGNTBUY:	// 기관누적순매수량
		if ((m_iDtUnit == GU_CODE || m_iDtUnit == GU_INDEX) && (m_iDtIndex == GI_DAY))
			return TRUE;
		return FALSE;
	}

	return TRUE;
}

BOOL CMainWnd::MainChartIsVarType()
{
	struct _envInfo* env = (struct _envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
	int mainGKind = env->datainfo.wMainGrpKind;

	if (mainGKind >= GK_EQV && mainGKind <= GK_CDVV)
		return TRUE;
	if (mainGKind >= GK_PNF && mainGKind <= GK_GUKKI)
		return TRUE;

	return FALSE;
}

bool CMainWnd::ReadEnv()
{
	memset(m_pEnvInfo, 0x00, SZ_ENVINFO);

	DWORD dwReadLen;
	CSavedHead sh;
	char* pcEnv = sh.Read(m_strEnvPath, dwReadLen);

	if (!pcEnv || dwReadLen < 1)
		return false;

	if (sh.m_sh.dwVersion != VERSION_ENV)
		return false;

	CopyMemory(m_pEnvInfo, pcEnv, SZ_ENVINFO);

	m_iDtIndex = m_pEnvInfo->datainfo.btIndex;
	m_pEnvInfo->display.dwDspOption &= ~DO_VIEWGRID;

	return true;
}

bool CMainWnd::ReadGrp()
{
	if (m_pacRegion[4])
		return true;

	int iTotalLen = 0;
	for (int ii = 0; ii < MAX_INDEX; ii++)
		iTotalLen += m_pEnvInfo->grpinfo[ii].wRgnCnt*SZ_REGION + 
			m_pEnvInfo->grpinfo[ii].wGrpCnt*SZ_GRAPH;

	DWORD dwReadLen;
	CSavedHead sh;
	char* pcGrp = sh.Read(m_strGrpPath, dwReadLen);
	if (!pcGrp || dwReadLen < 1)
		return false;

	
	if (sh.m_sh.dwVersion != VERSION_GRP)
	{
		return false;
	}

	int iLen = 0;
	for (ii = 0; ii < MAX_INDEX; ii++)
	{
		int iRCnt = m_pEnvInfo->grpinfo[ii].wRgnCnt;
		int iGCnt = m_pEnvInfo->grpinfo[ii].wGrpCnt;
		m_pacRegion[ii] = new char[iRCnt*SZ_REGION];
		m_pacGraph[ii] = new char[iGCnt*SZ_GRAPH];
		CopyMemory(m_pacRegion[ii], &pcGrp[iLen], iRCnt*SZ_REGION);
		iLen += iRCnt*SZ_REGION;
		CopyMemory(m_pacGraph[ii], &pcGrp[iLen], iGCnt*SZ_GRAPH);
		iLen += iGCnt*SZ_GRAPH;
	}

	return true;
}

void CMainWnd::WriteGrp()
{
	int iTotalSize = 0;
	int iIndex = m_iDtIndex - GI_DAY;
	int iRgnCnt = m_pEnvInfo->grpinfo[iIndex].wRgnCnt;
	int iGrpCnt = m_pEnvInfo->grpinfo[iIndex].wGrpCnt;

//	Debug("rcnt = %d, gcnt = %d", iRgnCnt, iGrpCnt);
	
	for (int ii = 0; ii < MAX_INDEX; ii++)
		iTotalSize += m_pEnvInfo->grpinfo[ii].wRgnCnt * SZ_REGION + m_pEnvInfo->grpinfo[ii].wGrpCnt * SZ_GRAPH;

	char* pcBuf = (char*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_MAP), 0);
	if (!pcBuf)
		return;
		
	if (m_pacRegion[iIndex])
		BUF_DELETE(m_pacRegion[iIndex]);
	if (m_pacGraph[iIndex])
		BUF_DELETE(m_pacGraph[iIndex]);

	m_pacRegion[iIndex] = new char[iRgnCnt * SZ_REGION];
	m_pacGraph[iIndex] = new char[iGrpCnt * SZ_GRAPH];
	CopyMemory(m_pacRegion[iIndex], pcBuf, iRgnCnt * SZ_REGION);
	CopyMemory(m_pacGraph[iIndex], &pcBuf[iRgnCnt * SZ_REGION], iGrpCnt * SZ_GRAPH);

	CSavedHead sh;
	char* pcGrp = sh.Make(VERSION_GRP, 1, iTotalSize);

	int iLen = 0;
	for (ii = 0; ii < MAX_INDEX; ii++)
	{
		iRgnCnt = m_pEnvInfo->grpinfo[ii].wRgnCnt;
		iGrpCnt = m_pEnvInfo->grpinfo[ii].wGrpCnt;
		CopyMemory(&pcGrp[iLen], m_pacRegion[ii], iRgnCnt * SZ_REGION);

		iLen += iRgnCnt * SZ_REGION;
		CopyMemory(&pcGrp[iLen], m_pacGraph[ii], iGrpCnt * SZ_GRAPH);

		iLen += iGrpCnt * SZ_GRAPH;
	}
	
	sh.Write(m_strGrpPath);
}

bool CMainWnd::WriteEnv()
{
	struct _envInfo* penvinfo = NULL;
	if (m_pwndChart)
		penvinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);

	if (!penvinfo)
		return false;

	if (m_pwndInput)
		m_pwndInput->SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_DATA, getCurGapList), long(penvinfo->datainfo.acIGap));

	if (penvinfo->wEnvOption & EO_SAVE)
	{
		CopyMemory(m_pEnvInfo, penvinfo, SZ_ENVINFO);
		CSavedHead sh;
		char* pcEnv = sh.Make(VERSION_ENV, 1, SZ_ENVINFO);

		SavePanel(penvinfo->panel);
		CopyMemory(pcEnv, penvinfo, SZ_ENVINFO);
		sh.Write(m_strEnvPath);
	}

	return true;
}

void CMainWnd::WriteDat()
{
	if (!m_pcGDat)
		return;

	struct _cntInfo* cntInfo = (_cntInfo *)m_pcGDat;

	int iMainCnt = cntInfo->wMainCnt;
	int iAidCnt = cntInfo->wAidCnt;
	int iUserCnt = cntInfo->wUserCnt;
	int iSize = SZ_CNTINFO + (iMainCnt + iAidCnt + iUserCnt) * SZ_GRAPH;

	CSavedHead sh;
	char* pcDat = sh.Make(VERSION_DAT, 1, iSize);
	CopyMemory(pcDat, m_pcGDat, iSize);

	sh.Write(m_strDatPath);

}

void CMainWnd::ModifyEnv()
{
}

void CMainWnd::EnvProc()
{
	CMenu cMenu;
	if (m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_ENV, chartIsValid), 0))
	{
		cMenu.CreatePopupMenu();
		cMenu.AppendMenu(MFT_STRING, 999, "환경설정");
		cMenu.AppendMenu(MFT_SEPARATOR, 0, "");
		m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_MENU, ADD_CHART_MENU), long(&cMenu));
	}
	else
	{
		return;
	}

	CPoint	point;
	GetCursorPos(&point);
	int menuID = cMenu.TrackPopupMenu(TPM_RIGHTBUTTON|TPM_RETURNCMD, point.x, point.y, this, NULL);
	int	aKind = 0;
	switch (menuID)
	{
	case 999:
		if (CallEnvDlg(NULL, true))
			m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_ENV_INFO));
		break;
	default:
		if (menuID <= 0)
			aKind = 0;
		else if (menuID >= MENU_CHART_AID)
			aKind = g_aMenuAid[menuID - MENU_CHART_AID].nKind;
		else if (menuID >= MENU_CHART_TYPE)
			aKind = g_aMenuType[menuID - MENU_CHART_TYPE].nKind;

		m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_MENU, selChartMenu), MAKELPARAM(menuID, aKind));
		break;
	}
}

bool CMainWnd::CallEnvDlg(char *pInfo, bool bTotal)
{
	if (!m_pApp->m_hGDlgLib)
	{
		m_pApp->m_hGDlgLib = LoadLibrary("axisGDlg.dll");
		if (!m_pApp->m_hGDlgLib)
		{
			AfxGetMainWnd()->MessageBox("axisGDlg.dll LoadLibrary error", COMPANYNAME);
			return false;
		}
	}

	bool bRet;
	if (bTotal)
	{
		char*	(APIENTRY *axTotalConfig)(CWnd *, DWORD, char *, char *, char *);
		axTotalConfig = (char* (APIENTRY *)(CWnd *, DWORD, char *, char *, char *)) 
			GetProcAddress(m_pApp->m_hGDlgLib, "axTotalConfig");
		if (!axTotalConfig)
			return false;

		_envInfo *envinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);

/////////////////////////////  get screen info
		if (m_pcTemp)	BUF_DELETE(m_pcTemp);
		m_pcTemp = (char*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, requestCurInter), 0);
		if (m_pcTemp == NULL)
			return false;
/////////////////////////////

		DWORD tkColor = m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), 4);

		char *pScreen = (char*)axTotalConfig(this, tkColor, (char*)envinfo, m_pcGDat, m_pcTemp);
		if (m_pcTemp)	BUF_DELETE(m_pcTemp);

		if (pScreen)
		{
			SyncMap(pScreen);			
			return true;
		}
		
		return false;
	}
	else
	{
		bool	(APIENTRY *axIndcConfig)(CWnd *, DWORD, char *, char *, char *);
		axIndcConfig = (bool (APIENTRY *)(CWnd *, DWORD, char *, char *, char *)) 
			GetProcAddress(m_pApp->m_hGDlgLib, "axIndcConfig");
		if (!axIndcConfig)
			return false;

		_envInfo *envinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
		DWORD tkColor = m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), 4);
		bRet = axIndcConfig(this, tkColor, (char*)envinfo, m_pcGDat, pInfo);

		if (bRet)	SetGrpAtDat(pInfo);
	}

	return bRet;
}

char* CMainWnd::CallMapDlg(char *pInfo)
{
	if (!m_pApp->m_hGDlgLib)
	{
		m_pApp->m_hGDlgLib = LoadLibrary("axisGDlg.dll");
		if (!m_pApp->m_hGDlgLib)
		{
			AfxGetMainWnd()->MessageBox("axisGDlg.dll LoadLibrary error", COMPANYNAME);
			return false;
		}
	}

	char*	(APIENTRY *axScreenConfig)(CWnd*, DWORD, char*, char *, char*);
	axScreenConfig = (char* (APIENTRY *)(CWnd*, DWORD, char*, char *, char*)) 
		GetProcAddress(m_pApp->m_hGDlgLib, "axScreenConfig");
	if (!axScreenConfig)
		return NULL;

	_envInfo *envinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
	DWORD tkColor = m_pwndView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), 4);
	return axScreenConfig(this, tkColor, (char*)envinfo, m_pcGDat, pInfo);
}

bool CMainWnd::CallStandardIndc(int kind)
{
	struct _cntInfo *cntInfo = (struct _cntInfo *)m_pcGDat;
	int	count = cntInfo->wMainCnt + cntInfo->wAidCnt;
	for (int jj = 0; jj < count; jj++)
	{
		struct _graph *pGrp = (struct _graph*)&m_pcGDat[SZ_CNTINFO + SZ_GRAPH*jj];
		if (kind == pGrp->wGKind)
		{
			CallEnvDlg((char *)pGrp, false);

			return true;
		}
	}

	return false;
}

bool CMainWnd::CallToolDlg(char *pInfo)
{
	if (!m_pApp->m_hGDlgLib)
	{
		m_pApp->m_hGDlgLib = LoadLibrary("axisGDlg.dll");
		if (!m_pApp->m_hGDlgLib)
		{
			AfxGetMainWnd()->MessageBox("axisGDlg.dll LoadLibrary error", COMPANYNAME);
			return false;
		}
	}

	bool	(APIENTRY *axToolConfig)(CWnd *, char *);
	axToolConfig = (bool (APIENTRY *)(CWnd *, char *)) 
		GetProcAddress(m_pApp->m_hGDlgLib, "axToolConfig");
	if (!axToolConfig)
		return false;

	return axToolConfig(this, pInfo);
}

void CMainWnd::InitGraph()
{
	// env
	CString	strEnvPathBasic;
	CString strGrpPathBasic;
	strEnvPathBasic.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_strDllName, ENV_B);
	strGrpPathBasic.Format("%s%s\\%s%s", m_pApp->GetGexPath(), m_pApp->GetUName(), m_strDllName, GRP_B);

	//char acBuffer[SZ_SAVEDHEAD + SZ_ENVINFO];
	DWORD dwReadLen;
	CSavedHead shEnv;
	char* pcEnv = shEnv.Read(strEnvPathBasic, dwReadLen);

	if (!pcEnv || dwReadLen < 1)
		return;

	if (shEnv.m_sh.dwVersion != VERSION_ENV || shEnv.m_sh.dwDataLength != SZ_ENVINFO)
		return;

	struct _envInfo envinfo;
	CopyMemory(&envinfo, pcEnv, SZ_ENVINFO);

	int iTotalSize = 0;
	for (int ii = 0; ii < MAX_INDEX; ii++)
		iTotalSize += envinfo.grpinfo[ii].wRgnCnt * SZ_REGION + envinfo.grpinfo[ii].wGrpCnt * SZ_GRAPH;

	// grp
	CSavedHead shGrp;
	char* pcGrp = shGrp.Read(strGrpPathBasic, dwReadLen);	
	if (!pcGrp || dwReadLen < 1)
		return;

	if (shGrp.m_sh.dwVersion != VERSION_GRP || iTotalSize != (int)shGrp.m_sh.dwDataLength)
	{
		return;
	}

	for (ii = 0; ii < MAX_INDEX; ii++)
	{
		if (m_pacRegion[ii])	BUF_DELETE(m_pacRegion[ii]);
		if (m_pacGraph[ii])	BUF_DELETE(m_pacGraph[ii]);
	}
	if (m_pcTemp)
		BUF_DELETE(m_pcTemp);

	CopyMemory(m_pEnvInfo, &envinfo, SZ_ENVINFO);
	m_pEnvInfo->datainfo.btUnit = m_iDtUnit;
	m_pEnvInfo->datainfo.btIndex = m_iDtIndex;
	m_pEnvInfo->datainfo.wMGap = m_iMGap;
	m_pEnvInfo->datainfo.wTGap = m_iTGap;

	int	len = 0;
	for (ii = 0; ii < MAX_INDEX; ii++)
	{
		int	rcnt = m_pEnvInfo->grpinfo[ii].wRgnCnt;
		int	gcnt = m_pEnvInfo->grpinfo[ii].wGrpCnt;
		m_pacRegion[ii] = new char[rcnt*SZ_REGION];
		m_pacGraph[ii] = new char[gcnt*SZ_GRAPH];
		CopyMemory(m_pacRegion[ii], &pcGrp[len], rcnt*SZ_REGION);
		len += rcnt*SZ_REGION;
		CopyMemory(m_pacGraph[ii], &pcGrp[len], gcnt*SZ_GRAPH);
		len += gcnt*SZ_GRAPH;
	}

	int	sIndex = m_iDtIndex - GI_DAY;
	int	rcnt = m_pEnvInfo->grpinfo[sIndex].wRgnCnt;
	int	gcnt = m_pEnvInfo->grpinfo[sIndex].wGrpCnt;
	int	bufSize = SZ_ENVINFO + rcnt*SZ_REGION + gcnt*SZ_GRAPH;
	char* pcBuf = new char[bufSize];
	CopyMemory(pcBuf, m_pEnvInfo, SZ_ENVINFO);
	CopyMemory(&pcBuf[SZ_ENVINFO], m_pacRegion[sIndex], rcnt*SZ_REGION);
	CopyMemory(&pcBuf[SZ_ENVINFO + rcnt*SZ_REGION], m_pacGraph[sIndex], gcnt*SZ_GRAPH);
	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, chartReload), long(pcBuf));
	if (m_bActive)
		m_pwndParent->SendMessage(GEV_CTRL, MAKEWPARAM(CTRL_ENV, ctrlMain), m_pEnvInfo->datainfo.wMainGrpKind);
	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, CHANGE_MAIN_GRP), m_pEnvInfo->datainfo.wMainGrpKind);

	CRect wRC;
	GetClientRect(wRC);
	ResizeWnd(wRC);

	BUF_DELETE(pcBuf);
}

void CMainWnd::SyncMainChart(char *pInfo)
{
	_interChart	*iChart = (_interChart*)pInfo;
	for (int ii = 0; ii < iChart->grpcnt; ii++)
	{
		_graph *graph = (_graph *)&pInfo[sz_INTERCHART + SZ_REGION*iChart->rgncnt + SZ_GRAPH*ii];
		switch (graph->wGKind)
		{
		case GK_JPN:	case GK_LIN:	case GK_BAR:	case GK_POLE:
		case GK_BALANCE:	case GK_AVOL:
		case GK_EQV:	case GK_CDV:	case GK_PV:	case GK_CLOCK:
		case GK_THREE:	case GK_PNF:	case GK_SWING:	case GK_KAGI:	case GK_RENKO:
			{
				struct _cntInfo *cntInfo = (struct _cntInfo *)m_pcGDat;
				int	count = cntInfo->wMainCnt + cntInfo->wAidCnt;
				for (int jj = 0; jj < count; jj++)
				{
					struct _graph *pGrp = (struct _graph*)&m_pcGDat[SZ_CNTINFO + SZ_GRAPH*jj];
					if (graph->wGKind == pGrp->wGKind)
					{
						CopyMemory(pGrp, graph, SZ_GRAPH);
						return;
					}
				}

			}
			break;
		default:
			break;
		}
	}
}

void CMainWnd::SyncMap(char *pScreen)
{
	_interChart	*iChart = (_interChart*)pScreen;
	int	bufSize = sz_INTERCHART + SZ_REGION*iChart->rgncnt + SZ_GRAPH*iChart->grpcnt;
	m_pcTemp = new char[bufSize];
	CopyMemory(m_pcTemp, pScreen, bufSize);

	SyncMainChart(m_pcTemp);
	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, changeMapInfo), long(m_pcTemp));
	BUF_DELETE(m_pcTemp);

	_envInfo *envinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
	switch (envinfo->datainfo.wMainGrpKind)
	{
	case GK_JPN:	case GK_BAR:	case GK_POLE:
	case GK_LIN:	case GK_AVOL:	case GK_BALANCE:
		{
			int	sIndex = m_iDtIndex - GI_DAY;				
			m_pEnvInfo->grpinfo[sIndex].wRgnCnt = iChart->rgncnt;
			m_pEnvInfo->grpinfo[sIndex].wGrpCnt = iChart->grpcnt;
			if (m_pacRegion[sIndex])	delete m_pacRegion[sIndex];
			if (m_pacGraph[sIndex])	delete m_pacGraph[sIndex];
			m_pacRegion[sIndex] = new char[iChart->rgncnt*SZ_REGION];
			m_pacGraph[sIndex] = new char[iChart->grpcnt*SZ_GRAPH];
			CopyMemory(m_pacRegion[sIndex], &pScreen[sz_INTERCHART], SZ_REGION*iChart->rgncnt);
			CopyMemory(m_pacGraph[sIndex], &pScreen[sz_INTERCHART+SZ_REGION*iChart->rgncnt], SZ_GRAPH*iChart->grpcnt);
		}
		break;
	default:
		break;
	}

	delete pScreen;
}

void CMainWnd::IndexChange(int index)
{
///////////// old info save
	struct _envInfo	*envinfo = NULL;
	if (m_pwndChart)
		envinfo = (_envInfo*)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);

	char *buf = (char *)m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_MAP), 0);
	if (!buf)	return;
		
	CopyMemory(m_pEnvInfo, envinfo, SZ_ENVINFO);

	int	sIndex = m_iDtIndex - GI_DAY;
	int	rcnt = m_pEnvInfo->grpinfo[sIndex].wRgnCnt;
	int	gcnt = m_pEnvInfo->grpinfo[sIndex].wGrpCnt;

	if (m_pacRegion[sIndex])	BUF_DELETE(m_pacRegion[sIndex]);
	if (m_pacGraph[sIndex])	BUF_DELETE(m_pacGraph[sIndex]);

	m_pacRegion[sIndex] = new char[rcnt*SZ_REGION];
	m_pacGraph[sIndex] = new char[gcnt*SZ_GRAPH];
	CopyMemory(m_pacRegion[sIndex], buf, rcnt*SZ_REGION);
	CopyMemory(m_pacGraph[sIndex], &buf[rcnt*SZ_REGION], gcnt*SZ_GRAPH);

///////////// new index info set
	m_iDtIndex = index;
	sIndex = m_iDtIndex - GI_DAY;
	rcnt = m_pEnvInfo->grpinfo[sIndex].wRgnCnt;
	gcnt = m_pEnvInfo->grpinfo[sIndex].wGrpCnt;

	int	totalsize = rcnt*SZ_REGION + gcnt*SZ_GRAPH + SZ_ENVINFO;
	char	*newBuf = new char[totalsize];

	CopyMemory(newBuf, m_pEnvInfo, SZ_ENVINFO);
	CopyMemory(&newBuf[SZ_ENVINFO], m_pacRegion[sIndex], rcnt*SZ_REGION);
	CopyMemory(&newBuf[SZ_ENVINFO + rcnt*SZ_REGION], m_pacGraph[sIndex], gcnt*SZ_GRAPH);

	m_pwndChart->SendMessage(GEV_CHART, MAKEWPARAM(CHART_SET_GRP, chartIReload), long(newBuf));
	delete newBuf;
}

#ifdef _DEBUG
void CMainWnd::WriteFile(CString strData)
{
	CFile		fileTrace;
	DWORD		dwPos;
	CString		strFileName, strTime;
	SYSTEMTIME	st;
	
	GetLocalTime(&st);
	strTime.Format("[%x] [%d년 %d월 %d 일% d시 %d분 %d초]\n" 
			, this, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	strFileName.Format("%s\\%s\\%s\\chart_debug%d%02d%02d.trc", m_pApp->GetRoot(), "USER", m_pApp->GetUName(), st.wYear, st.wMonth, st.wDay);
	BOOL bExist = fileTrace.Open(strFileName, CFile::modeReadWrite);//CFile::modeCreate|CFile::modeReadWrite);
	if (!bExist)
	{
		fileTrace.Open(strFileName, CFile::modeCreate|CFile::modeReadWrite);
		fileTrace.Write((char *) strTime.operator LPCTSTR(), strTime.GetLength());
		fileTrace.Write(strData.operator LPCTSTR(), strData.GetLength());
	}
	else
	{
		dwPos = fileTrace.SeekToEnd();
		fileTrace.Seek((long) dwPos, CFile::begin);
		fileTrace.Write((char *) strTime.operator LPCTSTR(), strTime.GetLength());
		fileTrace.Write(strData.operator LPCTSTR(), strData.GetLength());
	}

	char newline[] = "\r\n\r\n";
	fileTrace.Write(newline, strlen(newline));
	fileTrace.Flush();
	fileTrace.Close();
}
#endif


void CMainWnd::CheckUnit(int unit)
{
	if (unit < 0)
		unit = m_pwndParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeUnit), 0);
	if (unit == GU_FUTURE && m_strCode.GetLength() >= 8)
	{
		int	focode = WhichFOCode(m_strCode);
		switch (focode)
		{
			case foOption:	unit = GU_OPTION;	break;
			case foCoFut:	unit = GU_COFUT;	break;
			case foCoOpt:	unit = GU_COOPT;	break;
			case foFuture:
			default:
					unit = GU_FUTURE;	break;
		}
	}

	if (unit != m_iDtUnit)
	{
		m_iDtUnit = unit;
		SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), unit);
	}
}

void CMainWnd::OnActiveEvent(bool bNotice)
{
	if (m_bActive)	return;

	m_bActive = true;
	Invalidate();

	if (bNotice)
		m_pwndParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeView), int(this));
}

void CMainWnd::OnInActiveEvent()
{
	if (!m_bActive)	return;

	m_bActive = false;
	Invalidate();
}

void CMainWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (m_ChartRC.IsRectEmpty())
		return;

	CPen	*cPen = m_pApp->GetPen(m_pwndView, PS_SOLID, 4, RGB(240,240,240));
	CPen	*sPen = dc.SelectObject(cPen);

	dc.MoveTo(m_ChartRC.left, m_ChartRC.top);
	dc.LineTo(m_ChartRC.right, m_ChartRC.top);
	dc.LineTo(m_ChartRC.right, m_ChartRC.bottom);
	dc.LineTo(m_ChartRC.left, m_ChartRC.bottom);
	dc.LineTo(m_ChartRC.left, m_ChartRC.top);

	if (m_bActive)
	{
		CPen	*cPen2 = m_pApp->GetPen(m_pwndView, PS_SOLID, 4, RGB(0, 160, 0));
		dc.SelectObject(cPen2);

		dc.MoveTo(m_ChartRC.left, m_ChartRC.top);
		dc.LineTo(m_ChartRC.right, m_ChartRC.top);
		dc.LineTo(m_ChartRC.right, m_ChartRC.bottom);
		dc.LineTo(m_ChartRC.left, m_ChartRC.bottom);
		dc.LineTo(m_ChartRC.left, m_ChartRC.top);
	}
	else
	{
		CPen	*cPen2 = m_pApp->GetPen(m_pwndView, PS_SOLID, 2, RGB(128,128,128));
		dc.SelectObject(cPen2);
		dc.MoveTo(m_ChartRC.left, m_ChartRC.top);
		dc.LineTo(m_ChartRC.right, m_ChartRC.top);
		dc.LineTo(m_ChartRC.right, m_ChartRC.bottom);
		dc.LineTo(m_ChartRC.left, m_ChartRC.bottom);
		dc.LineTo(m_ChartRC.left, m_ChartRC.top);
	}

	dc.SelectObject(sPen);
}
