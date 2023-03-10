// MainWnd.cpp : implementation file
//IB100400 = 963 290 FixedEx	        ; 주식스탑로스
#include "stdafx.h"
#include "IB300800.h"
#include "MainWnd.h"
#include "../../h/MistakeStopOrder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString		m_sUnitText[] = {"틱", "%", "가격", "입력"};
#define		DEFCOLW				45
#define		DEFCOLW1			25
#define		DEFCOLW2			65
#define		UM_PASSWORD			WM_USER+1111
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))

/////////////////////////////////////////////////////////////////////////////
// CMainWnd
void CMainWnd::DebugLog(CString strText) 
{
	strText = "ML " + strText;
	//OutputDebugString( (LPTSTR)(LPCTSTR)strText);
}

CMainWnd::CMainWnd(CWnd*	pAxWnd)
{
	m_pAxMain = pAxWnd;
	m_pRemainGrid = NULL;
	m_pTestCbo = NULL;
	m_pTestBtn = NULL;
	m_pConfigBtn = NULL;
	m_pQueryModalWnd = NULL;

	m_strGuideMessage = "Start 반자동주문Mode";
	m_pClientRect = CRect(0, 0,0 ,0);

	m_bClose = FALSE;
	m_pLogDlg = NULL;
	m_arGridToggleList.RemoveAll();

	m_iSelectRow = -1;
	m_bExecMode = m_bNextList = FALSE;

	
#if _DEBUG
//	m_bDebugMode = TRUE;
#endif

	m_lSizeRate[0] = 0.16;
	m_lSizeRate[1] = 0.07;
//	m_bInit = FALSE;
	m_iOldSize[0] = m_iOldSize[1] = 0;
	m_bInit = FALSE;
	m_iCurFont = m_iOldFont = 9;
	m_igridRowHeight = GRIDROWHEIGHT;
	m_pAccnNameRect = CRect(0,0,0,0);
	m_iGuideHeight = GUIDE_HEIGHT;
	m_iGridHeadrHeight = GRIDHEADER_HEIGHT;
	m_iToolheight = TOOL_HEIGHT;

	m_bChangeFont = FALSE;
	m_bFirst = FALSE;
	m_pContentRect = CRect(0);

	m_nLogCount = 0;

	for(int i=0; i<4; i++) m_hRoundBitmap[i] = NULL;

	m_hiSha256 = NULL;

	//2015.09.09 KSJ 초기화해줌
	m_stAllconfig.iauto[0] = 0;
	m_stAllconfig.iauto[1] = 0;
}

CMainWnd::~CMainWnd()
{
	if (m_hiSha256)
	{
		AfxFreeLibrary(m_hiSha256);
		m_hiSha256 = NULL;
	}
}

BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser_Axis)
	ON_MESSAGE(WM_USER+1, OnUser)
	ON_MESSAGE(UM_PASSWORD, OnMyPassword)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers
LRESULT CMainWnd::SendAxisMessage(WPARAM wParam, LPARAM lPAram)
{	
	return m_pAxMain->SendMessage(WM_USER, wParam, lPAram);
}

int CMainWnd::getCodeType(CString strcode)
{
	return SendAxisMessage(MAKEWPARAM(codeTYPE, 0), (LPARAM)(LPCTSTR)strcode);
}

HBITMAP CMainWnd::getBitmap(CString path)
{
	path = m_strImgPath + path;

	CBitmap*	pBitmap = (CBitmap*)SendAxisMessage( getBITMAP, (LPARAM)path.operator LPCTSTR());
	return pBitmap->operator HBITMAP();
}

CFont* CMainWnd::getAxFont(CString fName, int point, bool bBold, bool bItalic)
{
	struct _fontR fontR;

	fontR.name = (LPSTR)fName.operator LPCTSTR();
	fontR.point = point;
	fontR.italic = bItalic; 
	fontR.bold = bBold ? FW_BOLD : FW_NORMAL;
	return (CFont*)SendAxisMessage( getFONT, (long)&fontR);
}

int CMainWnd::SendTransaction(CString strTrCode, CString strData, char cstate, char ckey)
{
	_userTH userth;
	FillMemory(&userth, sizeof(userth), ' ');
	CopyMemory(userth.trc, strTrCode, sizeof(userth.trc));

	userth.key = ckey;
	userth.stat = cstate;	

	CString strSend = CString((char*)&userth, L_userTH);
	strSend += strData;

	return SendAxisMessage(MAKEWPARAM(invokeTRx, strSend.GetLength()-L_userTH), (LPARAM)(LPCTSTR)strSend);	
}


LONG CMainWnd::OnUser_Axis(WPARAM wParam, LPARAM lParam)
{
	if(m_bClose) return 0;

	LONG	ret = 0;
	switch(LOBYTE(LOWORD(wParam)))
	{
		case DLL_OUB:
			SetOubData(wParam, lParam );
			break;
// 		case DLL_ALERT:
// 			if(m_pQueryModalWnd)
// 				m_pQueryModalWnd->SendMessage(WM_USER, wParam, lParam);
// 			ParseRealData((char *)lParam);
// 			break;
		case DLL_ALERTx:
			struct _alertR* alertR;
			alertR = (struct _alertR*)lParam;
			if(m_pQueryModalWnd)
				m_pQueryModalWnd->SendMessage(WM_USER, wParam, lParam);
			ParseRealData(alertR);
			break;
		case DLL_SETFCB:break;
		case DLL_SETFONT:break;
		case DLL_SETFONTx:
			ChangeFont( HIWORD(wParam), CString((char*)lParam) );
			break;

		case DLL_SETPAL:
			ResetPalleteColor(true);
			break;

		case DLL_TRIGGER:
			break;
		case DLL_DOMINO:
			break;
		case DLL_NOTICE:
			m_section.Lock();
			SetNoticeData((char *)lParam);
			m_section.Unlock();
			break;
		case DLL_GUIDE: return true; break;
		case DLL_INVOKE:break;
	}

	return 0;
}



LONG CMainWnd::OnUser(WPARAM wParam, LPARAM lParam)
{
	switch( LOBYTE(LOWORD(wParam)) )
	{
		case CHANGEACCOUNT:
			ChangeAccount((char *)lParam);
			break;

		case SENDTR:
			SendAxisMessage(MAKEWPARAM(invokeTRx, HIWORD(wParam)), lParam);
			break;
	}

	return 0;
}



void CMainWnd::ChangeAccount(char* szReceive)
{
	if(!m_bInit)
		return;

	CString sList[3];
	SplitString(szReceive, tabCHAR, sList, 3);
	m_strAccountName = sList[1];
	InvalidateRect(m_pAccnNameRect);
	m_pPassEdit->SetText(sList[2]);
	m_pPassEdit->SetSelectFocus();
	m_bExecMode = FALSE;

	CString sMessage;
	sMessage.Format("%s (%s)",  SetDataFormat(3, sList[0]), sList[1]);
	WriteLog("계좌변경", sMessage,"","", false);

	SetGuideMessage("[계좌 변경].잔고조회후 감시조건을 설정할수 있습니다.");
	EnableButtons(FALSE);
	for(int i=0; i<m_pRemainGrid->GetRowCount(); i++)
		ResetCaseValue(i);

	if(!m_bFirst)
	{
		CString sval;
		sval = ((CIB100400App*)AfxGetApp())->GetBuffer(_T("PASS"));
		if(!sval.IsEmpty())
		{
			m_pPassEdit->SetText(sval); 
			ExecJangoQuery();
			
		}
		m_bFirst = TRUE;
	}

}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetInitValue();
	CreateControl();

	::DeleteFile(m_strLogPath+".td");

	return 0;
}

void CMainWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	m_bClose = TRUE;

	//UploadLogData();
	
	ClearData();
}

void CMainWnd::ClearData()
{
	SaveConfigValue();
	if(m_pTestBtn)
	{
		delete m_pTestBtn;
		m_pTestBtn = NULL;
	}

	if(m_pTestCbo)
	{
		delete m_pTestCbo;
		m_pTestCbo = NULL;
	}

	if(m_pRemainGrid)
	{
		delete m_pRemainGrid;
		m_pRemainGrid = NULL;
	}

	if(m_pConfigBtn)
	{
		delete m_pConfigBtn;
		m_pConfigBtn = NULL;
	}

	if(m_pLogDlg)
	{
		m_pLogDlg->DestroyWindow();
		delete m_pLogDlg;
		m_pLogDlg = NULL;
	}

}

void CMainWnd::ResetPalleteColor(bool bInvalidate)
{
	LoadRoundBitmap();
	m_MaesuColor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAESU_BACKINDEX);
	m_MaesuColor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAESU_LINEINDEX);
	m_MaesuColor[2] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAESU_BOXBGINDEX1);
	m_MaesuColor[3] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAESU_BOXBGINDEX2);

	m_MaedoColor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAEDO_BACKINDEX);
	m_MaedoColor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAEDO_LINEINDEX);
	m_MaedoColor[2] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAEDO_BOXBGINDEX1);
	m_MaedoColor[3] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)MAEDO_BOXBGINDEX2);

	m_DangaColor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)DANGA_BGINDEX);
	m_DangaColor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)DANGA_TXTINDEX);

	m_clrConditionColor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)UPCOLOR_INDEX);
	m_clrConditionColor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)DOWNCOLOR_INDEX);
	m_clrConditionColor[2] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)TXTCOLOR_INDEX);
	
	m_bgcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)BACKCOLOR_INDEX);
	m_txtcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)TXTCOLOR_INDEX);

	m_toolcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)TOOLCOLOR_INDEX);
	m_bodycolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)BODYCOLOR_INDEX);
	m_guidecolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GUIDCOLOR_INDEX);
	m_guideTxtcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GUIDTXTCOLOR_INDEX);
	
	

	m_gridhdrbgcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDHDRCOLOR_INDEX);
	m_gridhdrtxtcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDHDRTXTCOLOR_INDEX);
	m_gridFocuscolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDFOCUSCOLOR_INDEX);

	m_gridLinecolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDLINECOLOR_INDEX/*GRIDLINECOLOR_INDEX*/);
	m_gridRowColor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDROWCOLOR1_INDEX);
	m_gridRowColor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)GRIDROWCOLOR2_INDEX);

	m_panelcolor[0] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)PANELBORDER_INDEX);
	m_panelcolor[1] = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)PANELBACK_INDEX);

	m_lbllinecolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)LABELBORDER_INDEX);
	m_lblbackcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)LABELBACK_INDEX);

	m_realcolor = SendAxisMessage(MAKEWPARAM(getPALETTE, 0), (LPARAM)REALBACK_INDEX);
	if(bInvalidate) 
	{
		ResetGridPalleteColor();
		RedrawWindow();
	}
}

void CMainWnd::ResetGridPalleteColor()
{
	if(!m_pRemainGrid) return;

	m_pRemainGrid->SetGridColor(m_gridLinecolor);
	m_pRemainGrid->SetBKSelColor(m_gridFocuscolor);

	SetGridPalletColor(0, true);
	for (int i=1; i<m_pRemainGrid->GetRowCount(); i++)
		SetGridPalletColor(i);

	m_pRemainGrid->Invalidate();
}


void CMainWnd::SetInitValue()
{
	SendAxisMessage(MAKEWPARAM(variantDLL, titleCC), (LPARAM)(LPCTSTR)MAPTITLE);

	m_stAllconfig.igubn = 0;
	m_stAllconfig.ivolval = 100;
	m_stAllconfig.iprctype = 6;//현재가
	m_stAllconfig.iprcval = 0;//tick

	m_strUserID = (char*)SendAxisMessage(MAKEWPARAM(variantDLL, userCC), NULL);
	m_strPass = (char*)SendAxisMessage(MAKEWPARAM(variantDLL, passCCx), NULL);
	m_strDeptCode = (char*)SendAxisMessage(MAKEWPARAM(variantDLL, deptCC), NULL);
	m_strRootDir = (char*)SendAxisMessage(MAKEWPARAM(variantDLL, homeCC), NULL);

	m_strUserName = (char*)SendAxisMessage(MAKEWPARAM(variantDLL, nameCC), NULL);
	m_strImgPath.Format("%s\\%s\\",m_strRootDir, IMAGEDIR) ;
	m_strLogPath.Format("%s\\%s\\%s\\%s",m_strRootDir, USRDIR, m_strUserName, LOGFILE) ;

	LoadConfigValue();
	m_pFont = getAxFont();
	ResetPalleteColor();
}

/***********************************************************************************
스탑로스 전체설정조건 읽기
*************************************************************************************/
void CMainWnd::LoadConfigValue()
{
	CString strConfigFile;
	strConfigFile.Format("%s\\%s\\%s\\%s",m_strRootDir, USRDIR, m_strUserName, CONFIGFILE) ;
	CString strApp = _T("CASE");
	CString strKey;
	for(int i=0; i<4; i++)
	{
		strKey.Format("EXEC%d", i+1); 
		m_stAllconfig.istopexe[i] = GetConfigFileInt(strConfigFile, strApp, strKey, 0);

		strKey.Format("UNIT%d", i+1); 
		m_stAllconfig.iunit[i] = GetConfigFileInt(strConfigFile, strApp, strKey, 0);

		strKey.Format("VALUE%d", i+1);
		m_stAllconfig.ival[i] = GetConfigFileInt(strConfigFile, strApp, strKey, 0);
	}

	strApp = _T("HOGAGUBN");
	m_stAllconfig.igubn = GetConfigFileInt(strConfigFile, strApp, _T("VALUE"), 0);

	
	strApp = _T("VOL");
	m_stAllconfig.ivoltype = GetConfigFileInt(strConfigFile, strApp, _T("TYPE"), 0);
	m_stAllconfig.ivolval = GetConfigFileInt(strConfigFile, strApp, _T("VALUE"), 100);

	strApp = _T("PRICE");
	m_stAllconfig.iprcval = GetConfigFileInt(strConfigFile, strApp, _T("UNIT"), 0);
	m_stAllconfig.iprctype = GetConfigFileInt(strConfigFile, strApp, _T("TYPE"), 6);

	strApp = _T("AUTO");
	m_stAllconfig.iauto[0] = GetConfigFileInt(strConfigFile, strApp, _T("PRICE/VOL"), 1);
	//m_stAllconfig.iauto[1] = GetConfigFileInt(strConfigFile, strApp, _T("NEWITEM_ADDCASE"), 0);
	m_stAllconfig.iauto[1] = 0;

	m_stAllconfig.inow = 0;

	m_bDebugMode = GetConfigFileInt(strConfigFile, _T("MAIN"), _T("DEBUG"), 0);
#if _DEBUG
	m_bDebugMode = TRUE;
#endif
	//CONFIGFILE
}

/***********************************************************************************
스탑로스 전체설정조건 저장
*************************************************************************************/
void CMainWnd::SaveConfigValue()
{
	CString strConfigFile;
	strConfigFile.Format("%s\\%s\\%s\\%s",m_strRootDir, USRDIR, m_strUserName, CONFIGFILE) ;
	CString strApp = _T("CASE");
	CString strKey;
	for(int i=0; i<4; i++)
	{
		strKey.Format("EXEC%d", i+1); 
		WriteConfigFileInt(strConfigFile, strApp, strKey, (int)m_stAllconfig.istopexe[i]);

		strKey.Format("UNIT%d", i+1); 
		WriteConfigFileInt(strConfigFile, strApp, strKey, (int)m_stAllconfig.iunit[i]);

		strKey.Format("VALUE%d", i+1);
		WriteConfigFileInt(strConfigFile, strApp, strKey, (int)m_stAllconfig.ival[i]);
	}

	strApp = _T("HOGAGUBN");
	WriteConfigFileInt(strConfigFile, strApp, _T("VALUE"), (int)m_stAllconfig.igubn);

	strApp = _T("VOL");
	WriteConfigFileInt(strConfigFile, strApp, _T("TYPE"), (int)m_stAllconfig.ivoltype);
	WriteConfigFileInt(strConfigFile, strApp, _T("VALUE"), (int)m_stAllconfig.ivolval);

	strApp = _T("PRICE");
	WriteConfigFileInt(strConfigFile, strApp, _T("UNIT"), (int)m_stAllconfig.iprcval);
	WriteConfigFileInt(strConfigFile, strApp, _T("TYPE"), (int)m_stAllconfig.iprctype);

	strApp = _T("AUTO");
	WriteConfigFileInt(strConfigFile, strApp, _T("PRICE/VOL"), (int)m_stAllconfig.iauto[0]);
	//WriteConfigFileInt(strConfigFile, strApp, _T("NEWITEM_ADDCASE"), m_stAllconfig.iauto[1]);
}

void CMainWnd::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);

	if(TIMER_QUERY == nIDEvent)
	{
		if(m_pToolBar[0])
			m_pToolBar[0]->EnableWindow(TRUE);
	}

	CWnd::OnTimer(nIDEvent);
}

void CMainWnd::LoadRoundBitmap()
{
	CString sFile;
	sFile.Format("%s\\tab\\PALETTE.INI", m_strRootDir);
	CString sPalette = GetConfigFileString(sFile, _T("General"), _T("Palette"), _T("Blue"));

	CString sImage;
	sImage.Format("%s\\image\\axpanel%s1_",  m_strRootDir, sPalette);
	for(int i=0; i<4; i++)
	{
		if(m_hRoundBitmap[i])
			DeleteObject(m_hRoundBitmap[i]);
	}

	CIB100400App* pApp = (CIB100400App*)AfxGetApp(); 
	m_hRoundBitmap[0] = (HBITMAP)::LoadImage( pApp->m_hInstance , sImage+"lt.bmp",
											IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	m_hRoundBitmap[1] = (HBITMAP)::LoadImage( pApp->m_hInstance, sImage+"rt.bmp",
											IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	m_hRoundBitmap[2] = (HBITMAP)::LoadImage( pApp->m_hInstance, sImage+"lb.bmp",
											IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	m_hRoundBitmap[3] = (HBITMAP)::LoadImage(pApp->m_hInstance, sImage+"rb.bmp",
											IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
}

void CMainWnd::CreateControl()
{
	m_bFirst = FALSE;
	LoadRoundBitmap();
//	m_hRoundBitmap[0] = getBitmap(_T("axpanelBlue1_lt.bmp"));
/*
	m_hRoundBitmap[0] = getBitmap(_T("axpanel1_lt.bmp"));
	m_hRoundBitmap[1] = getBitmap(_T("axpanel1_rt.bmp"));
	m_hRoundBitmap[2] = getBitmap(_T("axpanel1_lb.bmp"));
	m_hRoundBitmap[3] = getBitmap(_T("axpanel1_rb.bmp"));
*/
	m_hGuideBitmap = getBitmap(_T("알림_ic.bmp"));

	CRect	pRect, pRect1;
	GetClientRect(&pRect);

	int itopPanelH = 30;

	int ileft = HORI_GAP;
	int iright = pRect.Width() - (HORI_GAP);
	itopPanelH += HORI_GAP;

	int itop = VERT_GAP + VERT_GAP;
	pRect.DeflateRect(HORI_GAP-1, itop, 1, 2);
	CRect btnRect = pRect;
	btnRect.left = pRect.right - 100;
	btnRect.bottom = btnRect.top + 23;

//TOP BUTTON
	pRect1 = pRect;
	pRect1.bottom = pRect1.top + CONTROL_HEIGHT;
	m_pToolLblRect[0] = m_pToolLblRect[1] = m_pToolLblRect[2] = m_pToolLblRect[3] = pRect1;
	pRect1.left = 30;
	m_pToolLblRect[0].right = pRect1.left+GAP_WIDTH;
	m_strToolLblList[0] = " 계좌";
	m_pAccnNameRect = m_pToolLblRect[0];
	m_LblTxtFormat[0] = DT_LEFT|DT_SINGLELINE|DT_VCENTER;

	pRect1.right = pRect1.left + ACCOUNT_WIDTH;
	m_pAccnCtrl = new CAccountCtrl(m_pAxMain, this, m_strRootDir);
	m_pAccnCtrl->CreateEx(WS_EX_TOPMOST, NULL, "ACCN", WS_VISIBLE|WS_CHILD|WS_TABSTOP, pRect1, this, IDC_ACCN);
	m_pAccnCtrl->createAccountCtrl("AN20", KEY_ACCOUNT, 0xFFFFFF); //"AN21선물 ,AN11주식"
	m_pAccnCtrl->SetFont(m_pFont);
	

//	pRect1.left = pRect1.right + 1;
//	pRect1.right = pRect1.left + ACCNAME_WIDTH;
	ileft = pRect1.right + 1;
	m_pAccnNameRect.SetRect( ileft, pRect1.top,  ileft + ACCNAME_WIDTH, pRect1.bottom );
	m_pAccnNameRect.DeflateRect(0,1);

	m_strToolLblList[1] = "비밀번호";
	m_LblTxtFormat[1] = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;
	m_pToolLblRect[1].left = m_pAccnNameRect.right+HORI_GAP;//pRect1.right + GAP_WIDTH_L;//GAP_WIDTH ;
	m_pToolLblRect[1].right = m_pToolLblRect[1].left + 50;

	pRect1.left = m_pToolLblRect[1].right+HORI_GAP;
	pRect1.right = pRect1.left + 64;//lbl+edit

	CRect rc;
	rc = pRect1;
	rc.DeflateRect(0,1,0,0);
	m_pPassEdit = new CMxFlatEdit();
	m_pPassEdit->Create(IDC_PASSEDIT, rc, this, m_pFont, ES_PASSWORD);
	m_pPassEdit->SetBoxColor(m_lbllinecolor);

	pRect1.left = pRect1.right + TXTGAP_S;
	pRect1.right = pRect1.left + 14;//lbl+edit

	m_pAutoBtn = new CButton();
	rc =pRect1;
	rc.DeflateRect(0,3,1,4);
	m_pAutoBtn->Create("", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, rc, this, IDC_AUTOBUTTON);
	m_pAutoBtn->SetFont(m_pFont);
	m_pAutoBtn->ShowWindow(SW_SHOW);
	m_pAutoBtn->SetCheck(1);

	CString sval;
	sval = ((CIB100400App*)AfxGetApp())->GetBuffer(_T("AUTOCHK"));
	if(!sval.IsEmpty()) 
		m_pAutoBtn->SetCheck(CInt(sval));
	


	m_strToolLblList[2] = "주문확인창";
	m_LblTxtFormat[2] = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
	m_pToolLblRect[2].left = pRect1.right;
	pRect1.right = m_pToolLblRect[2].right = m_pToolLblRect[2].left + 65;

	m_strToolLblList[3] = "반자동";
	m_pToolLblRect[3].left = m_pToolLblRect[2].right+1;
	m_LblTxtFormat[3] = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
	m_pToolLblRect[3].right = m_pToolLblRect[3].left + 38;

	///toolbaar 버튼들 우측정렬
	int ibtncount = 7;
	int ilefts = pRect.right -(BUTTON_WIDTH/*버튼하나너비*/ * ibtncount) - ( HORI_GAP* (ibtncount-1) ) - (HORI_GAP+HORI_GAP);//pRect.right - ((56/*버튼하나너비*/ * ibtncount) + (2/*버튼사이*/*4) + 3) - GAP_WIDTH;
	pRect1.left = ilefts;//m_pToolLblRect[3].right + GAP_WIDTH;//ilefts;//pRect1.right + GAP_WIDTH + 40;/*자동?반자동*/;

	CString sCaption[] = {"잔고조회", "전체설정", "전체감시", "전체해제", "종목해제", "실행내역", "도움말"};
	int i4btnw = BUTTON_WIDTH;
	pRect1.right = pRect1.left + i4btnw;

	HBITMAP hbitmap[3];
	hbitmap[0] = getBitmap("4BTN.bmp");
	hbitmap[1] = getBitmap("4BTN_DN.bmp");
	hbitmap[2] = getBitmap("4BTN_EN.bmp");

	pRect1.bottom = pRect1.top + CONTROL_HEIGHT;
	for(int i=0; i<ibtncount; i++)
	{
		m_pToolBar[i] = new CfxImgButton;
		m_pToolBar[i]->Create(sCaption[i], pRect1, this, IDC_QUERYBUTTON+i, FALSE, TRUE);

		m_pToolBar[i]->SetImgBitmap(hbitmap[0], hbitmap[1], hbitmap[2]);
		m_pToolBar[i]->SetTextColor(m_txtcolor);
		m_pToolBar[i]->SetFont(m_pFont, TRUE);

		pRect1.left = pRect1.right + GAP_WIDTH_MIN;
		pRect1.right = pRect1.left + i4btnw;
	}

	
//	pRect1.SetRect(pRect.left,   m_pToolLblRect[3].bottom + GAP_WIDTH+m_iGridHeadrHeight, 
//						pRect.right,  pRect.bottom-m_iGuideHeight);
	m_pContentRect = pRect1;
	m_pContentRect.left = HORI_GAP;
	m_pContentRect.top = pRect1.bottom +VERT_GAP;

	pRect1.SetRect(pRect.left,   itopPanelH + VERT_GAP+m_iGridHeadrHeight+VERT_GAP, 
						pRect.right,  pRect.bottom-m_iGuideHeight);
	m_pContentRect.bottom = pRect.bottom - VERT_GAP;
	m_pContentRect.right = pRect1.right ;

	

	int iscrollType = GVSC_VERT;
	m_pRemainGrid = new CfxGrid;
	m_pRemainGrid->Create(pRect1, this, IDC_CONFIGGRID, iscrollType, GVDD_NONE);
	m_pRemainGrid->SetTitleTips(TRUE);
	m_pRemainGrid->Initial(0, JCOLCOUNT, 0, 0);
	m_pRemainGrid->ShowZeroData(TRUE);
	m_pRemainGrid->SetRowColResize(FALSE, FALSE);
	m_pRemainGrid->SetConditionColor(m_clrConditionColor[0], m_clrConditionColor[1], m_clrConditionColor[2]);
	m_pRemainGrid->SetGridColor(m_gridLinecolor);
	m_pRemainGrid->SetBKSelColor(m_gridFocuscolor);
	m_pRemainGrid->SetGridFocusLine(FALSE, TRUE);
	m_pRemainGrid->SetGridLine(GVLN_VERT);

	for (int ii = 0; ii < JCOLCOUNT; ii++)
		m_GridHdr[ii] = gridHdr[ii];
	insertGridRow(0);
	m_arGridHdrList.SetSize(JCOLCOUNT);
	InvalidateRect(CRect(0,0,m_pClientRect.right,m_iToolheight*3));

	if(!m_pLogDlg)
	{
		m_pLogDlg = new CLogDlg(m_strLogPath);
		m_pLogDlg->Create(IDD_LOGDIALOG, this);
	}


	SetFocus();
	EnableButtons(FALSE);

m_bDebugMode = FALSE;
	if(m_bDebugMode)
	{
		CRect trect = pRect;
		trect.top = m_pToolLblRect[3].top;
		trect.left = m_pToolLblRect[3].right + 5;//pRect.right - 200;

		m_pTestCbo = new CComboBox();
		m_pTestCbo->Create(WS_VISIBLE|CBS_DROPDOWNLIST, CRect(trect.left, trect.top, trect.left+110, trect.top+100), this, IDC_TEST+1);
		m_pTestCbo->SetFont(m_pFont);
		m_pTestCbo->ShowWindow(SW_SHOW);
		m_pTestCbo->InsertString(0, "002-10-000017");//위탁:
		m_pTestCbo->InsertString(1, "002-30-000017");//저축
		m_pTestCbo->InsertString(2, "002-20-000017");//파생
		m_pTestCbo->InsertString(3, "002-10-000002");//신용계좌
		m_pTestCbo->InsertString(4, "002-10-000014");
		m_pTestCbo->InsertString(5, "001-10-000026");
		m_pTestCbo->InsertString(6, "002-10-000420");
		m_pTestCbo->SetCurSel(3);

		m_pTestBtn = new CButton();
		m_pTestBtn->Create("↔", WS_VISIBLE, CRect(trect.left+110, trect.top+1, trect.left+123, trect.top+18), this, IDC_TEST);
		m_pTestBtn->SetFont(m_pFont);
		m_pTestBtn->ShowWindow(SW_SHOW);
	}

	m_bInit = TRUE;

}

int CMainWnd::insertGridRow(int row, bool binsert, bool bheader)
{
	if(!m_pRemainGrid) return -1;
	GVITEM	item;
	bool badd = binsert;
	if(!binsert)
	{
		if( m_pRemainGrid->GetRowCount() <= row) badd = true;
	}

	if(badd)
		row = m_pRemainGrid->InsertRow(_T(""), row);

	int ipoint = m_iOldFont * 10;
	LOGFONT	lf = GetLogFont(ipoint);
	item.row = row;
	int icolor = row % 2 ;
	CString sTxt = "";
	int iw = 0;

	for (int ii = 0; ii < JCOLCOUNT; ii++)
	{
		item.col    = ii;
		item.mask   = GVMK_FORMAT|GVMK_ATTR|GVMK_FONT|GVMK_FGCOLOR|GVMK_BKCOLOR;
		item.format = m_GridHdr[ii].format;
		item.attr   = m_GridHdr[ii].attr|m_GridHdr[ii].attrx|GVAT_ONLYROW;
		if(bheader)
		{
			item.format |= GVFM_HEADER;
			item.attr   = m_GridHdr[ii].attr;
			item.bkcol  = m_gridhdrbgcolor;
			item.fgcol  = m_gridhdrtxtcolor;
		}
		else
		{
			item.bkcol  = m_gridRowColor[icolor];
			item.fgcol  = m_txtcolor;
		}

		if(ii == colJNO) 
		{
			item.mask |= GVMK_PARAM;
			item.param = colJMSG;
		}
		
		CopyMemory(&item.font, &lf, sizeof(LOGFONT));
		m_pRemainGrid->SetItem(&item);

		iw = m_GridHdr[ii].width;
		if( m_GridHdr[ii].attr & GVAT_HIDDEN) iw = 0;

		if(m_GridHdr[ii].itogglecol > 0)
		{
			if(m_pRemainGrid->GetRowCount() > 1)
				iw = m_pRemainGrid->GetColumnWidth(ii);
		}

// 		CString s;
// 		s.Format("COLUMN : %d	WIDTH : %d\n",ii,iw);
// 		OutputDebugString(s);

		m_pRemainGrid->SetColumnWidth(ii, iw);
		sTxt = "";
		if(bheader) sTxt = m_GridHdr[ii].szhdr;
		
		m_pRemainGrid->SetItemText(row, ii, sTxt);
	}

	m_pRemainGrid->SetRowHeight(row, m_igridRowHeight);
	return row;
}

void CMainWnd::SetGridPalletColor(int row, bool bheader)
{
	if(!m_pRemainGrid) return;

	GVITEM	item;
	item.row = row;
	int icolor = row % 2 ;

	for (int ii = 0; ii < JCOLCOUNT; ii++)
	{
		item.col    = ii;
		m_pRemainGrid->GetItem(&item);

		if(bheader)
		{
			item.bkcol  = m_gridhdrbgcolor;
			item.fgcol  = m_gridhdrtxtcolor;
		}
		else
		{
			item.bkcol  = m_gridRowColor[icolor];
			item.fgcol  = m_txtcolor;
		}

		m_pRemainGrid->SetItem(&item);
	}
}

CString CMainWnd::GetCode(CString sRCode)
{
	if(sRCode.IsEmpty()) return sRCode;
	CString ctype = sRCode.Left(1) ;
	
	CString stypes[] = {"A", "E"};
	for(int i=0; i<2; i++)
	{
		if(stypes[i] == ctype) return sRCode.Right(sRCode.GetLength() -1);  
	}

	return sRCode;
}

/***********************************************************************************
레저 설정
*************************************************************************************/
CString CMainWnd::GetLedger(CString svcd, CString strAccount, char codrf, CString sNext, int iRowCnt, CString sPswd) //2013.12.23 KSJ 일방향암호화 추가
{
	struct	_ledgerH ledger;

	FillMemory(&ledger, L_ledgerH, _T(' '));
	SendAxisMessage(ledgerDLL, (LPARAM)&ledger);
	CopyMemory(&ledger.size, "000590", sizeof(ledger.size));
	CopyMemory(&ledger.svcd, svcd, sizeof(ledger.svcd));
	CopyMemory(&ledger.usid, (LPCTSTR)m_strUserID, m_strUserID.GetLength());

	if(!strAccount.IsEmpty())
	{
		CString sBrno = strAccount.Left(3);
		CopyMemory(&ledger.brno, sBrno, 3);
	}

	CString sCnt;
	sCnt.Format("%04d", iRowCnt); 
	CopyMemory(&ledger.rcnt, sCnt, sizeof(ledger.rcnt));
	
	//2013.12.23 KSJ 일방향암호화 추가
	if(!sPswd.IsEmpty())
	{
		CopyMemory(&ledger.hsiz, "44", sizeof(ledger.hsiz));
		CopyMemory(&ledger.epwd, sPswd, sPswd.GetLength());
	}

	ledger.fkey[0] = _T('C');
	ledger.mkty[0] = '2';
	ledger.odrf[0] = codrf;//화면dll-이게 조회키

	if (!sNext.IsEmpty())
	{
		CopyMemory(&ledger.next, "Y", 1);
		CopyMemory(&ledger.nkey, sNext, sNext.GetLength());
	}
	else
		CopyMemory(&ledger.next, " ", 1);
	CopyMemory(&ledger.brno, "000", 3);

	return CString( (char*)&ledger, L_ledgerH);
}

void CMainWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SetBkMode(TRANSPARENT); 
	CRect rect;
	if( m_pClientRect.Width() <= 0)
		GetClientRect(&m_pClientRect);

	rect = m_pClientRect;
	dc.FillSolidRect(rect, m_bgcolor); 

	rect.bottom = rect.top + m_iToolheight+1;

	
	if(m_pToolBar[0] && m_pRemainGrid)
	{
		CRect wrc, rc1;
		m_pToolBar[0]->GetWindowRect(&wrc);
		ScreenToClient(wrc);
		wrc.left = TOOLGAP;
		wrc.right = m_pClientRect.right - TOOLGAP;
		wrc.bottom = wrc.bottom + VERT_GAP;
		wrc.top = VERT_GAP;
		dc.FillSolidRect(wrc, m_toolcolor); 
		DrawCornerRoundBitmap(&dc, wrc);

		m_pRemainGrid->GetWindowRect(&rc1);
		ScreenToClient(rc1);

		wrc.top = wrc.bottom + VERT_GAP;
		wrc.bottom =  rc1.bottom + VERT_GAP;
		dc.FillSolidRect(wrc, m_bodycolor); 
		m_pContentRect = wrc;
		DrawCornerRoundBitmap(&dc, wrc);
	}


	dc.SetTextColor(m_txtcolor);
	CFont* pOldFont = dc.SelectObject(m_pFont); 
	DrawGuideBar(&dc, m_pClientRect);
	DrawGridHeader(&dc);

	for(int i=0; i<4; i++)
	{
		if(i == 3) dc.SetTextColor(0x0000FF);
		else dc.SetTextColor(m_txtcolor);

		dc.DrawText(m_strToolLblList[i], m_pToolLblRect[i], m_LblTxtFormat[i]); 
	}

	CBrush brush(m_lblbackcolor);
	CBrush* pOldBrush = dc.SelectObject(&brush); 
	CPen pen(PS_SOLID, 1, m_lbllinecolor );
	CPen* pOldPen = dc.SelectObject(&pen); 
	dc.Rectangle(m_pAccnNameRect);
	dc.SelectObject(pOldPen); 
	dc.SelectObject(pOldBrush); 
	DeleteObject(pOldPen);
	DeleteObject(pOldBrush);

	dc.SetTextColor(m_txtcolor);
	rect = m_pAccnNameRect;
	rect.left += 3;
	dc.DrawText(m_strAccountName, rect, DT_LEFT|DT_SINGLELINE|DT_VCENTER); 
	
	dc.SelectObject(pOldFont); 
	DeleteObject(pOldFont);
}

void CMainWnd::DrawGridHeader(CDC* pDC)
{
	if(!m_pRemainGrid) return;
	CRect rc;
	m_pRemainGrid->GetWindowRect(&rc);
	ScreenToClient(&rc);

	CBrush brush(m_gridhdrbgcolor);
	CBrush* pOldBrush = pDC->SelectObject(&brush); 
	CPen pen(PS_SOLID, 1, m_gridLinecolor );
	CPen* pOldPen = pDC->SelectObject(&pen); 

	int irowH = GRIDHEADER_HEIGHT;
	CRect grc = rc, trect;
	grc.top = m_pContentRect.top + VERT_GAP;//rc.top - irowH;
	grc.bottom = rc.top + 1;
	pDC->Rectangle(grc); 

	int ileft = HORI_GAP + HORI_GAP-1;
	int itop = grc.top;

	int ihalftop = grc.top + irowH/2;
	int ilinetop = grc.top;
	trect = CRect(1, itop,  ileft, rc.top-1);
	int row_merge, col_merge;
	int icolmergeleft = 0;
	int iw = 0;
	int ibottom = rc.top;

	bool bflag = false, badd = false;
	CPoint	pt[4];
	CRgn	rgn;
	int		igap = 2;
	if(m_arGridToggleList.GetSize() <= 0) badd = true;
	CString sText;

	pDC->SetTextColor(m_gridhdrtxtcolor);
	for (int ii = 0; ii < JCOLCOUNT; ii++)
	{
		row_merge = m_GridHdr[ii].r_merge;
		col_merge = m_GridHdr[ii].c_merge;
		
		iw = m_GridHdr[ii].width;
		if( m_GridHdr[ii].attr & GVAT_HIDDEN) 
		{
			iw = 0;
		}

		trect.left = ileft;
		trect.top = itop;
		itop = grc.top;
		if( m_GridHdr[ii].c_flag2 && icolmergeleft > 0)
		{
			pDC->DrawText(m_GridHdr[ii].szhdr0, CRect(icolmergeleft, itop, ileft+iw, ihalftop) , DT_SINGLELINE|DT_CENTER|DT_VCENTER); 
			icolmergeleft = 0;
		}

		if(!row_merge) 
		{
			trect.top = ihalftop;
			if( !(m_GridHdr[ii].c_flag1 + m_GridHdr[ii].c_flag2) ) itop = ihalftop;

			pDC->MoveTo(ileft,  ihalftop);
			pDC->LineTo(ileft+iw,  ihalftop);
		}
		
		
		ileft += iw;
		if(m_GridHdr[ii].c_flag1)	icolmergeleft = ileft;
		sText = m_GridHdr[ii].szhdr;

		if(m_GridHdr[ii].itogglecol > 0 && m_arGridHdrList[ii] != "") sText = m_arGridHdrList[ii];

		if(!col_merge)
		{
			pDC->MoveTo(ileft,  itop);
			pDC->LineTo(ileft,  ibottom);
			trect.right = ileft;
			pDC->DrawText(sText, trect, DT_SINGLELINE|DT_CENTER|DT_VCENTER); 
		}
		else
		{
			if(strlen(m_GridHdr[ii].szhdr) )
			{
				trect.right = (ileft-iw);
				for(int c=ii; c<JCOLCOUNT; c++)
				{
					if( !m_GridHdr[c].c_merge) break;

					iw =  m_GridHdr[c].width;

					if( m_GridHdr[c].attr & GVAT_HIDDEN) iw=0;
					trect.right += iw;
				}
				pDC->DrawText(sText, trect, DT_SINGLELINE|DT_CENTER|DT_VCENTER); 
			}
		}

		if(m_GridHdr[ii].itogglecol > 0)
		{
			pt[0] = pt[3] = CPoint(trect.right-1, trect.bottom-7);	
			pt[1] = CPoint(trect.right-1, trect.bottom);
			pt[2] = CPoint(trect.right-7, trect.bottom);

			rgn.CreatePolygonRgn(pt, 4, ALTERNATE);
			CBrush	tbrush(m_gridLinecolor );
			pDC->FillRgn(&rgn, &tbrush);
			rgn.DeleteObject();
			tbrush.DeleteObject();

			if(badd) m_arGridToggleList.Add(_List(trect, ii, m_GridHdr[ii].itogglecol));
		}
	}

	pDC->SelectObject(pOldPen); 
	pDC->SelectObject(pOldBrush); 

	DeleteObject(pOldPen);
	DeleteObject(pOldBrush);
}


void CMainWnd::DrawGuideBar(CDC* pDC, CRect rc)
{
	if(!m_pRemainGrid) return;

	CRect rc1;
	m_pRemainGrid->GetWindowRect(&rc1);
	ScreenToClient(rc1);
	CRect r = CRect(rc.left+TOOLGAP, rc1.bottom+VERT_GAP + VERT_GAP, rc.right-TOOLGAP, rc.bottom - VERT_GAP)   ;
	
//	int iguidetop = rc1.bottom+VERT_GAP + VERT_GAP;
//	CRect r = CRect(rc.left+HORI_GAP, iguidetop, rc.right-HORI_GAP, iguidetop+18)   ;
	
	CBrush brush(m_guidecolor);
	CBrush* pOldBrush = pDC->SelectObject(&brush); 
	CPen pen(PS_SOLID, 1, m_panelcolor[0] );
	CPen* pOldPen = pDC->SelectObject(&pen); 

//	r.DeflateRect(1, 0, 1, 0);
//	pDC->Rectangle(r); 

	pDC->SetTextColor( m_guideTxtcolor);
	pDC->FillSolidRect(r, m_guidecolor); 
	DrawCornerRoundBitmap(pDC, r);

	CRect alarmr = r;
	alarmr.DeflateRect(6, 1, 1, 1);
	int iw = 14; 
	if( alarmr.Height()  > 15)
	{
		int igap = (alarmr.Height() - iw) / 2; 
		if(igap > 0)
		{
			alarmr.top += igap;
		}
	}

	alarmr.right = alarmr.left + iw;
	alarmr.bottom = alarmr.top + iw;
	DrawBitmap(pDC, alarmr, m_hGuideBitmap);

	r.left = alarmr.right ;
	r.DeflateRect(3, 1, 1, 0);
	pDC->DrawText(m_strGuideMessage, r, DT_SINGLELINE|DT_LEFT|DT_VCENTER); 

	if(m_bDebugMode && !m_strDebugTxt[0].IsEmpty()) 
	{
		CString stxt;
		stxt.Format("매입금:%s |평가금:%s |평가손익:%s |수익률:%s", SetComma(m_strDebugTxt[0]), SetComma(m_strDebugTxt[1]), SetComma(m_strDebugTxt[2]), m_strDebugTxt[3]); 
		pDC->DrawText(stxt, r, DT_SINGLELINE|DT_RIGHT|DT_VCENTER); 
	}

	pDC->Rectangle( m_pAccnNameRect);
	pDC->SelectObject(pOldPen); 
	pDC->SelectObject(pOldBrush); 

	DeleteObject(pOldPen);
	DeleteObject(pOldBrush);
}

void CMainWnd::SetGuideMessage(CString sMessage)
{
	if( sMessage.Find("그룹계좌") > -1 && sMessage.Find("존재") > -1 )
		return;

	int iFind = 0;
	if( (iFind=sMessage.Find("&") ) > -1) sMessage.Insert(iFind, '&'); 

	m_strGuideMessage = sMessage;
	InvalidateRect(CRect(m_pClientRect.left, m_pClientRect.bottom - m_iGuideHeight, m_pClientRect.right, m_pClientRect.bottom) );
}

void CMainWnd::DeleteAllItem_RemainGrid()
{
	if(!m_pRemainGrid) return;

	int nRow = m_pRemainGrid->GetRowCount();
	for (; nRow > 0; nRow--)
		m_pRemainGrid->DeleteRow(nRow);

	m_pRemainGrid->Clear();
}

void CMainWnd::ResetData()
{
	for(int i=0; i<JCOLCOUNT;i++)
		m_arGridHdrList[i] = _T("");

	for(int i=0; i<m_arGridToggleList.GetSize(); i++)
		InvalidateRect(m_arGridToggleList.GetAt(i).rect);
	m_arGridToggleList.RemoveAll();

	DeleteAllItem_RemainGrid();
	m_arConfigList.RemoveAll();
}

void CMainWnd::EnableButtons(BOOL bEnable)
{
	for(int i=1; i<4; i++)
	{
		if(m_pToolBar[i])
			m_pToolBar[i]->EnableWindow(bEnable);
	}
}


void CMainWnd::OnTest()
{	
	int iw=1800;
	int ih=350;
	MoveWindow(0, 0, iw, ih);
	SendAxisMessage(MAKEWPARAM(sizeDLL, 0), MAKELPARAM(iw, ih) );	

//	ExecJangoQuery();
}

int CMainWnd::SetJangoFormat(CString sRows, CStringArray& arList)
{
	int iLes[] = {8,30,6,10,10,10,10,10,15,15,10,15};//struct f_rec

	for(int i=0; i<12; i++)
	{
		if(sRows.GetLength() <  iLes[i]) break;
		
		CString s;
// 		s.Format("[TEXT : %s]\n",sRows.Left( iLes[i]));
// 		OutputDebugString(s);

		CString strValue;
		strValue.Format("%s",sRows.Left( iLes[i]));
		strValue.TrimLeft();
		strValue.TrimRight();

		arList.Add( strValue ) ;
		sRows = sRows.Right( sRows.GetLength() -   iLes[i] );
	}

	return arList.GetSize(); 
}

void CMainWnd::SetOubData(WPARAM wParam, LPARAM lParam)
{
	int iKey = HIBYTE(LOWORD(wParam));
	if(iKey == LOGKEY) return;


	switch (iKey)
	{
	case 255: 
	case 254: 
		m_pAccnCtrl->m_pAccountCtrl->SendMessage(WM_USER, wParam, lParam);
		return;
	}

	struct _trkey* trkey = (struct _trkey*)&iKey;

	if(trkey->gubn == PASSKEY)
	{
		CString szReceive = CString((char *)lParam);
		CString sLedger = CString(szReceive, L_ledgerH);
		CString sMessage;
		bool bnext;
		bool berrcode = GetLedgerMessage(sLedger, sMessage, bnext);
		if(!berrcode)
		{
			DeleteAllItem_RemainGrid();
			SetGuideMessage(sMessage);
			AfxMessageBox(sMessage);
		}
		else ExecJangoQuery();


		return ;
	}

	//2015.09.09 KSJ 신규종목 편입시 자동조건 검사 적용 
	//첫번째만 걸리고 두번째 부터는 걸리지 않아 주석처리함.
//	m_stAllconfig.iauto[1] = 0;

	if(trkey->gubn == HOGALIST) 
	{
		if(m_pQueryModalWnd)
			m_pQueryModalWnd->SendMessage(WM_USER, wParam, lParam);
		return ;
	}
	
	CString emsg;
// 	emsg.Format("TRKEY(%d)(%d)- %s\n", trkey->gubn, HIWORD(wParam), (char*)lParam);
// 	OutputDebugString(emsg);

	int iLen = HIWORD(wParam);
	if(trkey->gubn == SJGOLIST || trkey->gubn == SJGOROW) 
		SetJangoData((char *)lParam, trkey->gubn, trkey->key);
	else if(trkey->gubn == POOPKEY  || trkey->gubn == GOOPKEY)
		SetSiseData((char *)lParam, iLen, trkey->gubn, trkey->key );
	else if(trkey->gubn == ORDERKEY)
	{
		if( iLen >= L_ledgerH )
			SetjumunData((char *)lParam, trkey->key);
	}
}


void CMainWnd::SetSiseData(char* szReceive, int iLen, int iKey, int irow)
{
	//OutputDebugString("[SetSiseData]\n");
	CString sReceiveData = szReceive;
	if(iKey == GOOPKEY)
	{
		int gridHoL = sizeof(struct _gridHo);
		sReceiveData = CString(&szReceive[gridHoL], iLen - gridHoL);
	}
CString slog;
// slog.Format("SetSiseData:%d-%s",  irow, szReceive);
// OutputDebugString(slog);

	CStringArray  arList, arDataList;
	SplitString(sReceiveData, newlineCHAR, arList);

	CString sRealCode, scurr;
	for(int i=0; i<arList.GetSize(); i++)
	{
		arDataList.RemoveAll(); 
		if( SplitString(arList[i], tabCHAR, arDataList) <= 0) continue;
		 
		sRealCode = Trim(arDataList[0]);
// 		slog.Format("SISEDATA : [%s]\n",sRealCode);
// 		OutputDebugString(slog);
		if( sRealCode != Trim(m_pRemainGrid->GetItemText(irow+i, colRCOD)) ) continue;

		arDataList.RemoveAt(0);
		for(int c=0; c<arDataList.GetSize(); c++)
		{
			m_pRemainGrid->SetItemText(irow+i,  colVolUNIT+c, arDataList[c]);
			if(c == 7)	scurr = arDataList[c]; //현재가
		}

		//SetCheckCase(irow+i, m_stAllconfig, TRUE);
	}

	if(arList.GetSize() > 0)
	{
		EnableButtons(TRUE);

		if(iKey ==  POOPKEY && irow >= 0)
		{
			m_pRemainGrid->SetItemText(irow, colCURR, scurr);
//			SetCheckCase(irow, m_arConfigList.GetAt(irow));
			SetCalcData(irow);
			CheckCase_changejangoVolume(irow);
		}
	}
}

bool CMainWnd::IsJusikCode(CString sCode)
{
	sCode.TrimRight();
	if(sCode.IsEmpty()) return false;
	
	char sType = sCode.GetAt(0); 
	if(sType == 'A' || sType == 'E' || ((sType=='J')&&(sCode.GetLength()==7))) return true;  //ELW종목도 매매하게끔 추가

	return false;
}

void CMainWnd::SetJangoData(char* szReceive, int iKey, int irow)
{
	//OutputDebugString("[SETJANGODATA]\n");
	if(m_pToolBar[0]) m_pToolBar[0]->EnableWindow(TRUE);

	if(!m_pRemainGrid) return;

	CString sLedger = CString(szReceive, L_ledgerH);
	CString sMessage;
	bool bnext=false;
	bool berrcode = GetLedgerMessage(sLedger, sMessage, bnext);
	SetGuideMessage(sMessage);

	if(!berrcode) 
	{
		//OutputDebugString("[BERRCODE FALSE]\n");
		EnableButtons(FALSE);
		return;
	}
	//신규종목 편입시 주문조건 자동적용 및 감시*********
	bool bnewcode = false;
	if(irow == 0 && iKey == SJGOROW)
	{
		if( m_pRemainGrid->GetItemText(irow,  colRCOD) == "")
			bnewcode = true;
	}

	f_mod* mo = (f_mod*)(&szReceive[L_ledgerH]);
	int iRowCnt = atoi(mo->nrec );
	CString sReceive = (char*)mo->rec;

	CString sRow, stmp;
	CStringArray arList;

	bool bAdd = true;
	CString sCode = _T("");
	int iType = 0;

	if(m_bNextList && iKey != SJGOROW)
	{
		irow = m_pRemainGrid->GetRowCount();
	}

	int RECLEN = sizeof(mo->rec)/100;

	for(int i=0; i<iRowCnt; i++)
	{
		if(sReceive.GetLength() <  RECLEN) break;

		arList.RemoveAll();
		bAdd = true;
		sRow = sReceive.Left(RECLEN); 

		sReceive = sReceive.Right(sReceive.GetLength() -  RECLEN);
		if( SetJangoFormat(sRow, arList) <= 0) break;

		CString code = Trim(arList[0]);

		CString type = code.Mid(1,2);

		int nType = atoi(type);

		//선물옵션만 보이게 수정
		if(nType >= 11 && nType <= 99)
		{
			continue;
		}

 		CString tmp;

// 		tmp.Format("JANGO DATA : [%s]\n",sRow);
// 		OutputDebugString(tmp);

// 		tmp.Format("JANGO KEY : [%d]	ROW : [%d]\n",iKey,irow);
// 		OutputDebugString(tmp);
		//AfxMessageBox(tmp);
		//if( !IsJusikCode(arList[0]) ) continue;

		arList[colJANTYPE-colRCOD-1].TrimRight();
		arList[colPOSSVOL-colRCOD-1].TrimRight();

// 		tmp.Format("JANGO DATA NAME : [%s]\n",arList[colPOSSVOL-colRCOD-1]);
// 		OutputDebugString(tmp);

		if( atof(arList[colPOSSVOL-colRCOD-1]) <= 0) continue;
		
		iType = CInt(arList[colJANTYPE-colRCOD-2]);//잔고유형

// 		tmp.Format("[%d][%s]\n", iType, GetCode( Trim(arList[0]) ));
//  		OutputDebugString(tmp);
		
		if(iType > 1) continue;

		arList[1].TrimRight();  //colNAME
		if( arList[1].IsEmpty() ) continue;


		if(iKey != SJGOROW) 
		{
			insertGridRow(irow, false);
			m_arConfigList.InsertAt(irow, m_stAllconfig);
		}

		m_pRemainGrid->SetItemText(irow,  colCODE, GetCode( Trim(arList[0]) ) );
		arList.InsertAt(colCRETYPE-colRCOD, "");

// 		tmp.Format("JANGO DATA LIST SIZE : [%d]\n",arList.GetSize());
// 		OutputDebugString(tmp);

		for(int j=0; j<arList.GetSize(); j++)
		{
			stmp = Trim(arList[j]);
// 			if(j == 15) //대출일자
// 				stmp = SetDataFormat(4, stmp, "/");

			int n = colRCOD+j;

			if(n >= colTMP0)
			{
				n = n + 1;
			}

			if(n == colJANTYPE)
			{
				//stmp.Remove('-');

				if(stmp.Find("매수") > -1)
				{
					m_pRemainGrid->SetItemFgColor(irow,n,PALETTERGB(255,0,0));
				}
				else
				{
					stmp = stmp.Mid(1);

					m_pRemainGrid->SetItemFgColor(irow,n,PALETTERGB(0,0,255));
				}
			}
			
// 			tmp.Format("[TEXT : %s]\n",stmp);
// 			OutputDebugString(tmp);
			m_pRemainGrid->SetItemText(irow,  n, stmp);
		}
		 

		SetJangoType(irow);
		if(iKey == SJGOROW) 
		{
			if(bnewcode) m_arConfigList.InsertAt(irow, m_stAllconfig);

			m_pRemainGrid->SetSelectRow(irow);
			sCode = m_pRemainGrid->GetItemText(irow,  colCODE) ;

			if( bnewcode && m_arConfigList.GetAt(irow).iauto[1])
			{
				//신규종목 편입시 주문조건 자동적용 및 감시*********
				SetCheckCase(irow, m_arConfigList.GetAt(irow));
			}
			
			break;
		}

	//	colCRTPRC2
//		SetCheckCase(irow, m_stAllconfig);
		irow++;
	}
	if(m_bDebugMode) CalculateTotolData();

	if(iKey == SJGOROW && !bnewcode) return;
	if(bnext && m_pRemainGrid->GetRowCount() < MAXROW)
	{
		m_bNextList = TRUE;
		ExecJangoQuery("", m_strNextKey);
		return;
	}

	m_bExecMode = TRUE;
	ExecPOOPQuery(sCode, irow);

}

void CMainWnd::SetJangoType(int irow)
{
	/*
주식 잔고유형 코드
====================
"00:보통
01:신용
02:코스피선물대용
03:코스닥선물대용
04:주식옵션선물대용
05:CD/CP/RP"
==================== 
*/
	int iType = CInt(m_pRemainGrid->GetItemText(irow, colJANTYPE));
	CString sText = "";
	if(iType == 1) 
	{
		sText =	GetCrtText( CInt(m_pRemainGrid->GetItemText(irow, colCRTCD)) );
	}

	if( iType> 1 && iType < 5) sText = _T("대용");
	if(iType == 5) sText = _T("CD/CP/RP");

	m_pRemainGrid->SetItemText(irow,  colCRETYPE, sText);
}

CString CMainWnd::GetCrtText(int iCode)
{
	if(iCode <= 0) return _T("");

	CString sResult = _T("신용");
	switch(iCode)
	{
		case 1:
			sResult = _T("유통융자");
			break;
		case 3:
			sResult = _T("자기융자");
			break;
		case 5:
			sResult = _T("유통대주");
			break;
		case 7:
			sResult = _T("자기대주");
			break;
	}

	if(iCode > 31) sResult=_T("대출");
	return sResult;

	/*
	=========대출상세분류코드=========
	01:유통융자
	03:자기융자
	05:유통대주
	07:자기대주
	31:금융기관담보대출(제일화재)
	32:금융기관담보대출(신동아화재)
	33:금융기관담보대출(토마토상호저축)
	34:금융기관담보대출(메리츠화재)
	35:금융기관담보대출(그린화재)
	40:예탁담보자동대출
	51:증권금융예탁담보신용대출
	52:증권금융예탁담보자동대출
	55:증권금융미수담보대출
	60:수익증권담보대출
	70:매도대금담보대출
	80:예탁주식담보신용대출
	82:예탁채권담보신용대출
	90:매입자금담보대출
	95:자기공모주청약대출
	97:유통공모주청약대출
	91:자기유상청약대출
*/
}

bool CMainWnd::GetLedgerMessage(CString sLedger, CString& sMessage, bool& bNext)
{
	struct	_ledgerH ledger;
	CopyMemory(&ledger, sLedger, L_ledgerH);

	//	char	emsg[99];	// 241	오류메세지	코드(4)+메시지(94)(9999 오류입니다 !)
	sMessage = CString(ledger.emsg, 99) ;
	int iErrCode = CInt(sMessage.Left(4)); 
	sMessage = Trim( sMessage.Right(sMessage.GetLength() -4) );

	bNext = false;
	if( CString(ledger.next, 1) == "Y" ) 
	{
		bNext = true;
		m_strNextKey = ledger.nkey ;
	}

	if(iErrCode > 999) return false;
	return true;
}

void CMainWnd::SetjumunData(char* szdata, int irow)
{
	//OutputDebugString("SETJUMUNDATA\n");
	if( irow < 0) return;
	CString sMessage;
	bool bnext;
	bool berrcode = GetLedgerMessage(CString(szdata, L_ledgerH), sMessage, bnext);
	CString state = m_pRemainGrid->GetItemText(irow, colSTATE);
	if( state != SENDJUMUN) return;

	m_pRemainGrid->SetItemText(irow,  colJMSG, sMessage);

// 	if(!berrcode)
// 	{
// 		m_pRemainGrid->SetItemText(irow,  colJNO, "미실행");
// 		SetGuideMessage(sMessage);
// 	}

	if(!berrcode)	
    {
        {
            _ledgerH *ledger = (_ledgerH*)szdata;
			
            if (CString(ledger->ecod, sizeof(ledger->ecod))=="9997")
				
                MessageBox(sMessage, "IBK투자증권");
			
        }
		
        m_pRemainGrid->SetItemText(irow,  colJNO, "미실행");
		
        SetGuideMessage(sMessage);	
    }

	WriteLog("주문접수수신", sMessage, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow,  colNAME), berrcode);
}

void CMainWnd::ParseRealData(char* szdata)
{
	if(!m_pRemainGrid) return;
	
	CStringArray arRowList;
	SplitString(szdata, "\n", arRowList);
	if(arRowList.GetSize() <= 0) return;

	CString s;
	s.Format("3008 DATA [%s]\n",szdata);
	OutputDebugString(s);
	
	//CString strData = arRowList.GetAt(0); 
	CString strData = arRowList.GetAt(arRowList.GetSize()-1); 
	CString sRealCode = Trim( SplitString(strData, tabCHAR) );
	if(sRealCode.IsEmpty()) return; 

// 	CString s;
// 	s.Format("REAL DATA : [%s]	[%s]\n",sRealCode,strData);
// 	OutputDebugString(s);

	CMapStringToString arTabList;
	if (SplitString_MAP(strData, "\t", arTabList) <= 1) return;
//	if (SplitString_MAP(strData, tabCHAR, arTabList) <= 1) return;

	SetRealData(sRealCode, arTabList);
}

void CMainWnd::ParseRealData(struct _alertR* alertR)
{
	if(!m_pRemainGrid) return;
	
	DWORD* data;
	
	for (int i = alertR->size - 1; i > -1; --i)
	{	
		data = (DWORD*)alertR->ptr[i];
		
		SetRealData(alertR->code, data);
	}
}

void CMainWnd::SetRealData(CString sRealCode, CMapStringToString& arRealList)
{
	int igridrows = m_pRemainGrid->GetRowCount();

	CString sval = "";
	CString sTmp, sSiseList[JCOLCOUNT];
	bool bcurchnage = false;
	for(int i=0; i<igridrows; i++)
	{
		bcurchnage = false;
		if( Trim( m_pRemainGrid->GetItemText(i, colRCOD) ) == sRealCode)
		{
			if( arRealList.Lookup("023", sval) )
			{
				sval = Trim(sval);
			//	m_pRemainGrid->Blink(i, colCURR, m_realcolor);
				if( m_pRemainGrid->GetItemText(i, colCURR) != sval)
				{
					bcurchnage = true;
					m_pRemainGrid->SetItemText(i, colCURR, sval);
				}
			}
			
			

			for (int ii = colSISE; ii < JCOLCOUNT; ii++)
			{
				if( strlen(m_GridHdr[ii].symbol) <= 3 ) continue;
				sTmp = CString(m_GridHdr[ii].symbol).Right(3); 
				
// 				CString emsg;
// 				emsg.Format("%s -> key(%s) : %s\n", sRealCode, sTmp, arRealList.Lookup(sTmp, sval) ? "TRUE" : "FALSE");
// 				OutputDebugString(emsg);

				if( arRealList.Lookup(sTmp, sval) )
				{
// 					emsg.Format("%s -> key(%s) : %s\n", sRealCode, sTmp, sval);
// 					OutputDebugString(emsg);

					m_pRemainGrid->SetItemText(i, ii, sval);
				//	if(m_bDebugMode)
				//		m_pRemainGrid->Blink(i, ii, m_realcolor);
				}
				else
				{
					if(sTmp == "023")
					{
						m_pRemainGrid->SetItemText(i, ii, m_pRemainGrid->GetItemText(i, colCURR));
					}
				}
			}

			if( m_pRemainGrid->GetItemData(i, colCHECK) )
				CheckStopLossValue(i);
			
			if(!bcurchnage) continue;
			SetCalcData(i);
			
			
		}
	}
}

void CMainWnd::SetRealData(CString sRealCode, DWORD* data)
{
	int igridrows = m_pRemainGrid->GetRowCount();
	
	CString sval = "";
	CString sTmp, sSiseList[JCOLCOUNT];
	bool bcurchnage = false;
	for(int i=0; i<igridrows; i++)
	{
		bcurchnage = false;
		if( Trim( m_pRemainGrid->GetItemText(i, colRCOD) ) == sRealCode)
		{
			if( data[23] )
			{
				sval = (char*)data[23];
				sval = Trim(sval);
				//	m_pRemainGrid->Blink(i, colCURR, m_realcolor);
				if( m_pRemainGrid->GetItemText(i, colCURR) != sval)
				{
					bcurchnage = true;
					m_pRemainGrid->SetItemText(i, colCURR, sval);
				}
			}
			
			for (int ii = colSISE; ii < JCOLCOUNT; ii++)
			{
				if( strlen(m_GridHdr[ii].symbol) <= 3 ) continue;
				sTmp = CString(m_GridHdr[ii].symbol).Right(3); 
				
				// 				CString emsg;
				// 				emsg.Format("%s -> key(%s) : %s\n", sRealCode, sTmp, arRealList.Lookup(sTmp, sval) ? "TRUE" : "FALSE");
				// 				OutputDebugString(emsg);
				
				if( data[atoi(sTmp)] )
				{
					m_pRemainGrid->SetItemText(i, ii, (char*)data[atoi(sTmp)]);
					//	if(m_bDebugMode)
					//		m_pRemainGrid->Blink(i, ii, m_realcolor);
				}
			}
			
			if( m_pRemainGrid->GetItemData(i, colCHECK) )
				CheckStopLossValue(i);
			
			if(!bcurchnage) continue;
			SetCalcData(i);
			
			
		}
	}
}

void CMainWnd::SetCalcData(int irow)
{
//	return;
	 //===================================================================
	 // 평가금액 = 현재가 * 잔고 - 신용금액
	 // 평가손익 = 평가금액 - 매입가
	 // 수익률 = 평가손익 * 100 / 매입가
	 //===================================================================

	CString code = m_pRemainGrid->GetItemText(irow, colCODE);
	CString smtype = m_pRemainGrid->GetItemText(irow, colCRTCD);
	if(smtype == "50"/*대용*/ || smtype == "40"/*40:채권*/) return;

	CString text = m_pRemainGrid->GetItemText(irow, colCURR);
	text.TrimLeft("-"); text.TrimLeft("+");

	double curr = atof(text);//현재가
	double lval3 = atof( m_pRemainGrid->GetItemText(irow, colVOL) ); //수량
	if(lval3 <= 0) 
	{
		m_pRemainGrid->SetItemText(irow, colAMOUNT, "0");// 매입금액
		m_pRemainGrid->SetItemText(irow, colPROFITPRC, "0");// 평가금액
		m_pRemainGrid->SetItemText(irow, colPROFIT, "0");// 평가손익
		m_pRemainGrid->SetItemText(irow, colRATE, "");//평가수익률
		return;
	}

	double lval1 = atof( m_pRemainGrid->GetItemText(irow, colCOST) ); //단가
	if(lval1 <= 0) return;
	CString s;

	double lcrtprice = atof(m_pRemainGrid->GetItemText(irow, colCRTPRC) ); //신용금액

	int m_dBase = getBase(code);

	if(m_dBase < 0)
	{
		OutputDebugString("m_dBase Value is -1.\n");
		return;
	}

	double lbal1 = curr * lval3 * m_dBase;// 평가금액 

	s.Format("[CURR : %f 단가 : %f 수량 : %f]\n",curr,lval1,lval3);
	OutputDebugString(s);
	if(lcrtprice < lbal1)	lbal1 -= lcrtprice;
	text.Format("%.0f",  lbal1);
	s.Format("[평가금액 : %f 신용금액 : %f]\n",lbal1,lcrtprice);
	OutputDebugString(s);
	m_pRemainGrid->SetItemText(irow, colPROFITPRC, text);// 평가금액

	double lbuy1 = atof( m_pRemainGrid->GetItemText(irow, colAMOUNT) );//매입금액

	s.Format("[평가금액 : %f 매입가 : %f]\n",lbal1,lbuy1);
	OutputDebugString(s);

	double lbal2;

	if(m_pRemainGrid->GetItemText(irow, colJANTYPE).Find("매도") > -1)
		lbal2 = lbuy1 - lbal1;// 평가손익:매입가 - 평가금액
	else
		lbal2 = lbal1 - lbuy1;// 평가손익:평가금액 - 매입가

	if(smtype == "05") lbal2 *= (-1);

	if(lbal2 == 0)
	{
		text = "0";
	}
	else
	{
		text.Format("%+.0f",  lbal2);
	}

	m_pRemainGrid->SetItemText(irow, colPROFIT, text);// 평가손익

	if(lbal2 == 0) lbal2 = 0;
	else lbal2 = lbal2 / lbuy1 * 100.f;
	if(lbal2 != 0.f)
		text = CFStr(lbal2, 2, true);
	else text="0.00";

	s.Format("[수익률 : %f]\n",lbal2);
	OutputDebugString(s);

	m_pRemainGrid->SetItemText(irow, colRATE, text);//평가수익률
//	m_pRemainGrid->Blink(irow, colPROFITPRC, m_realcolor);
//	m_pRemainGrid->Blink(irow, colPROFIT, m_realcolor);
//	m_pRemainGrid->Blink(irow, colRATE, m_realcolor);

	if(m_bDebugMode) CalculateTotolData();

}

int CMainWnd::getBase(CString m_code)
{
	int m_dBase;

	if (m_code.IsEmpty())
		return -1;
	
	CString scode;
	int	nkind = getJKind(m_code);
	
	m_dBase = 100000;
	
	switch (nkind)
	{
	case JK_CALLOPT:
	case JK_PUTOPT:
		scode = m_code.Mid(1, 4);
		if (scode<="01G6")	m_dBase = 100000;
		else				m_dBase = 250000;
		break;
	case JK_JCALLOPT:
	case JK_JPUTOPT:
		m_dBase = 1;
		break;
	case JK_SFUTURE:
	case JK_SFSPREAD:
		m_dBase = -1;
		//		m_dBase = 10;
		break;
	case JK_FUTURE:
	case JK_SPREAD:
		m_dBase = 250000;
		break;
	case JK_STAR:
		m_dBase = 10000;
		break;
	case JK_KTBFUTURE:
		m_dBase = 1000000;
		break;
	case JK_USDFUTURE:
		m_dBase = 10000;
		break;
	case JK_MINIGOLDFUTURE:
		m_dBase = 100;
		break;
	case JK_GOLDFUTURE:
		m_dBase = 1000;
		break;
	case JK_PIGFUTURE:
		m_dBase = 1000;
		break;
	}

	return m_dBase;
}

int CMainWnd::getJKind(CString m_code)
{
	if (m_code.GetLength() != 8)
		return -1;
	TCHAR	ch1 = m_code.GetAt(0);
	TCHAR	ch2 = m_code.GetAt(1);
	TCHAR	ch3 = m_code.GetAt(2);
	
	switch (ch1)
	{
	case '1':	// future
	case 'A':	 //파생상품 코드개편
		{
			if (ch2 == '0')
			{
				if (ch3 == '1')
					return JK_FUTURE;
				else
					return JK_STAR;
			}
			else if (ch2 == '6') 
				return JK_KTBFUTURE;
			else if (ch2 == '7')
				return JK_USDFUTURE;
			else if (ch2 == '8' && ch3 == '5')
				return JK_GOLDFUTURE;
			else if (ch2 == '8' && ch3 == '6')
				return JK_PIGFUTURE;
			else if (ch2 == '8' && ch3 == '7')
				return JK_MINIGOLDFUTURE;
			else
				return JK_SFUTURE;			
		}
	case '4':	// future spread
	case 'D':	 //파생상품 코드개편
		if (ch2 == '0')
			return JK_SPREAD;
		else
			return JK_SFSPREAD;
	case '2':	// call option
	case 'B':	 //파생상품 코드개편
		if (m_code.GetAt(1) == '0')
			return JK_CALLOPT;
		else
			return JK_JCALLOPT;
		break;
	case '3':	// put option
	case 'C':	 //파생상품 코드개편
		if (m_code.GetAt(1) == '0')
			return JK_PUTOPT;
		else
			return JK_JPUTOPT;
		break;
	}
	return -1;
}

void CMainWnd::CalculateTotolData()
{
	double val1=0.f, val2=0.f;
	for(int i=0; i<m_pRemainGrid->GetRowCount(); i++)
	{
//		if( CInt(m_pRemainGrid->GetItemText(i, colVOL) ) == 0) continue;

		val1 += atof( m_pRemainGrid->GetItemText(i, colAMOUNT) );
		val2 += atof( m_pRemainGrid->GetItemText(i, colPROFITPRC) );
	}

	m_strDebugTxt[0] = CFStr(val1, 0, true);
	m_strDebugTxt[1] = CFStr(val2, 0, true);
	val2 -= val1;
	if(val1 == 0 || val2 ==0 ) return;

	m_strDebugTxt[2] = CFStr(val2, 0, true);
	val2 = val2 / val1 * 100.f;
	m_strDebugTxt[3].Format("%.3f",  val2);//= CFStr(val2, 2, true);
	InvalidateRect(CRect(m_pClientRect.left, m_pClientRect.bottom - m_iGuideHeight, m_pClientRect.right, m_pClientRect.bottom) );
    
}

void CMainWnd::SendCodeTrigger(int irow)
{
	if(m_pRemainGrid->GetRowCount() <= irow) return;
	CString sCode = m_pRemainGrid->GetItemText(irow, colCODE);

	char ch = sCode.GetAt(0);

	CString strCodeSym;
	//파생상품 코드개편
	if      (ch=='1' || ch=='4' || ch=='A' || ch=='D') { strCodeSym = "30301"; }
	else if (ch=='2' || ch=='3' || ch=='B' || ch=='C') { strCodeSym = "40301"; }

	CString sdata;
	sdata.Format("%s\t%s", strCodeSym, sCode);
	SendAxisMessage( MAKEWPARAM(variantDLL, triggerCC), (LPARAM)sdata.operator LPCTSTR());

	sdata.Format("ed_focod\t%s", sCode);
	SendAxisMessage( MAKEWPARAM(variantDLL, triggerCC), (LPARAM)sdata.operator LPCTSTR());
}

BOOL CMainWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	NM_GVITEM* nmgv = (NM_GVITEM*) lParam;
	if( wParam != IDC_CONFIGGRID) return 0;

	m_iSelectRow = nmgv->row;
	switch (nmgv->hdr.code)
	{
		case GVNM_DBLCLICKED:
			if(nmgv->col == colNAME)
				SendCodeTrigger(nmgv->row);

			break;
		case GVNM_BEGINEDIT:
			break;
		case GVNM_LMOUSEDOWN:
			if(nmgv->col == colSET)
			{
				if(!m_bExecMode)
				{
					MessageBox("감시설정할수 없습니다.[계좌및잔고 재확인]", MAPTITLE, MB_ICONINFORMATION|MB_OK);
					return 0;
				}

			}

			break;

		case GVNM_LMOUSEUP:

			if(nmgv->col == colSET)
			{
				if (!m_pRemainGrid->GetItemText(nmgv->row, colCODE).IsEmpty())
				{
					if( !ExecSetup(1, nmgv->row)) return 0;
				}
			}

			if(nmgv->col == colCHECK || nmgv->col == colSET) SetGamsi(nmgv->row);
			
			/*
			if( m_pRemainGrid->GetItemData(nmgv->row, colCHECK) )
			{
				if(!m_bExecMode)
				{
					MessageBox("감시설정할수 없습니다.[계좌및잔고 재확인]", MAPTITLE, MB_ICONINFORMATION|MB_OK);
					m_pRemainGrid->SetItemData(nmgv->row, colCHECK, 0);
					return 0;
				}

				if( !IsvalidateSetupCase(nmgv->row) )
				{
					m_pRemainGrid->SetItemData(nmgv->row, colCHECK, 0);
				}
				else
				{
					ResetJumunValue(nmgv->row);
					CString sMessage;
					sMessage.Format("감시설정 종목 : %s[%s]", m_pRemainGrid->GetItemText(nmgv->row, colNAME), m_pRemainGrid->GetItemText(nmgv->row, colCODE));
					SetGuideMessage(sMessage);

					_config cfgval = m_arConfigList.GetAt(nmgv->row);
					CString sLog;
					sLog.Format("%s", GetCaseTextLog(cfgval) );
					WriteLog("감시설정", sLog, m_pRemainGrid->GetItemText(nmgv->row, colCODE), m_pRemainGrid->GetItemText(nmgv->row, colNAME));
				}
			}
			*/
			break;
	}	

	return CWnd::OnNotify(wParam, lParam, pResult);
}

void CMainWnd::SetGamsi(int irow)
{
	if( m_pRemainGrid->GetItemData(irow, colCHECK) )
	{
		m_pRemainGrid->SetItemData(irow, colCHECK, 0);
		if(!m_bExecMode)
		{
			MessageBox("감시설정할수 없습니다.[계좌및잔고 재확인]", MAPTITLE, MB_ICONINFORMATION|MB_OK);
			//m_pRemainGrid->SetItemData(irow, colCHECK, 0);
			return ;
		}
/*
		if( !IsvalidateSetupCase(irow) )
		{
			//m_pRemainGrid->SetItemData(irow, colCHECK, 0);
		}
		*/
		if( IsvalidateSetupCase(irow) )
		{
			m_pRemainGrid->SetItemData(irow, colCHECK, 1);
			ResetJumunValue(irow);
			CString sMessage;
			sMessage.Format("감시설정 종목 : %s[%s]", m_pRemainGrid->GetItemText(irow, colNAME), m_pRemainGrid->GetItemText(irow, colCODE));
			SetGuideMessage(sMessage);

			_config cfgval = m_arConfigList.GetAt(irow);
			CString sLog;
			sLog.Format("%s", GetCaseTextLog(cfgval) );
			WriteLog("감시설정", sLog, m_pRemainGrid->GetItemText(irow, colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
		}
	}
}

#include "ConfigDlg.h"
void CMainWnd::OnAddCase()
{
	CConfigDlg	pDlg(1, "", this);
	if( pDlg.DoModal() == IDOK)
	{
		m_pQueryModalWnd = NULL;
	}
	//
}



BOOL CMainWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString sMessage;
	switch (LOWORD(wParam))
	{
		case IDC_TEST:
			OnTest();
			break;

		case IDC_ADDCASE:
			OnAddCase();
			break;

		case IDC_AUTOBUTTON:
			sMessage = _T("Start 반자동주문 Mode");
			if( m_pAutoBtn->GetCheck() ) m_strToolLblList[3]="반자동";
			else 
			{
				m_strToolLblList[3]="자  동";
				sMessage = _T("Start 자 동 Mode");
			}

			SetGuideMessage(sMessage);
			InvalidateRect(m_pToolLblRect[3]);
			((CIB100400App*)AfxGetApp())->SaveBuffer(_T("AUTOCHK"),  CStr(m_pAutoBtn->GetCheck()));
			break;

		case IDC_PASSEDIT:
			if( HIWORD(wParam) == VK_RETURN )
			{
				if(m_pPassEdit->GetText() != "")
					CheckPassword();
//					ExecJangoQuery();
			}
			break;

		case IDC_QUERYBUTTON:
			CheckPassword();
			//ExecJangoQuery();
			break;
		case IDC_ALLAPPLY:
			{
				if(m_stAllconfig.istopexe[0] || m_stAllconfig.istopexe[1] || m_stAllconfig.istopexe[2])
				{
					for(int i=0; i< m_pRemainGrid->GetRowCount(); i++)
					{
						m_pRemainGrid->SetItemData(i, colCHECK, 1);
					}
				}
				else
				{
					MessageBox("전체주문조건이 없습니다.", MAPTITLE, MB_ICONINFORMATION|MB_OK);
				}
			}
			break;
		case IDC_ALLSETUPBUTTON:
			ExecSetup();
			break;
		case IDC_ALLFREEBUTTON:
			ExecResetSetup();
			break;
		case IDC_ITEMFREEBUTTON:
			ExecResetSetup(1);
			break;
		case IDC_VIEWLOGBUTTON:
			ExecViewLog();
			break;
		case IDC_HELPBUTTON:
			ExecHelp();
			break;
	}

	return CWnd::OnCommand(wParam, lParam);
}

void CMainWnd::ExecHelp()
{
	CString	file, HomePage, dat;
	HomePage = "http://www.ibks.com/HTSHELP/helptrnum.ids?trnum=3008";

	VARIANT vFlags = {0},
	vTargetFrameName = {0},
	vPostData = {0},
	vHeaders = {0};

	HRESULT hr;
	_bstr_t	bstr(HomePage);
	UINT	nFlag = SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW;
	WINDOWPLACEMENT	pl{};

	if (FAILED(hr = CoInitialize(NULL)))	return;

	struct	IWebBrowserApp* pWEBApp;
	HWND	hWEB;
	if (FAILED(hr = CoCreateInstance(CLSID_InternetExplorer,
			NULL, CLSCTX_SERVER, IID_IWebBrowserApp,
			(LPVOID*)&pWEBApp)))
	{
		return;
	}

	int	cx = 840;
	int	cy = 740;
	cx += GetSystemMetrics(SM_CXFRAME) * 2;
	cx += GetSystemMetrics(SM_CXBORDER) * 4;
	cy += GetSystemMetrics(SM_CYFRAME) * 2;
	cy += GetSystemMetrics(SM_CYBORDER) * 4;
	cy += GetSystemMetrics(SM_CYCAPTION);

	pWEBApp->put_Width(cx);
	pWEBApp->put_Height(cy);
	pWEBApp->put_Left(VARIANT_TRUE);
	pWEBApp->put_Top(VARIANT_TRUE);
	pWEBApp->put_ToolBar(VARIANT_FALSE);
	pWEBApp->put_StatusBar(VARIANT_FALSE);
	hr = pWEBApp->Navigate(bstr, &vFlags, &vTargetFrameName, &vPostData, &vHeaders);
	if (HomePage.IsEmpty())	pWEBApp->GoHome();
	pWEBApp->put_Visible(VARIANT_TRUE);
	VariantClear(&vPostData);

	pWEBApp->get_HWND((long *)&hWEB);
	::GetWindowPlacement(hWEB, &pl);
	if (pl.showCmd & SW_SHOWMINIMIZED)
	{
		pl.showCmd = SW_RESTORE;
		::SetWindowPlacement(hWEB, &pl);
	}
	else	::SetWindowPos(hWEB, HWND_TOPMOST, 0, 0, 0, 0, nFlag);
	CoUninitialize();
}

void CMainWnd::ExecPOOPQuery(CString strCode, int irow)
{
	m_bNextList = FALSE;
	int isymbolscnt = 18;
	CString sendS = _T(""), strTmp, sendsymbols = _T("");

	char ctoken = '\r';// newlineCHAR;
	if (!strCode.IsEmpty()) ctoken = '\t';// tabCHAR;

	char ch = strCode.GetAt(0);

	CString strHead,strCodeSym;
	
	strTmp.Format("%s%c", CString(m_GridHdr[colRCOD].symbol), ctoken);
	
	//sendsymbols += strTmp;
   //파생상품 코드개편
	if      (ch=='1' || ch=='4' || ch=='A' || ch=='D') { strCodeSym = "30301" ; strHead = "31"; strTmp.Format("%s%c", "30021", ctoken);sendsymbols += strTmp;}
	else if (ch=='2' || ch=='3' || ch=='B' || ch=='C') { strCodeSym = "40301"; strHead = "41"; strTmp.Format("%s%c", "40021", ctoken);sendsymbols += strTmp;}

	for (int ii = colVolUNIT; ii < colVolUNIT+isymbolscnt; ii++)
	{
		strTmp.Format("%s%c", CString(m_GridHdr[ii].symbol), ctoken);
		strTmp = strHead + strTmp.Mid(1);
		sendsymbols += strTmp;
	}

	char	key;
	_trkey* trkey = (struct _trkey*)&key;

	if(strCode.IsEmpty())
	{
		sendS.Format("%s%c", "$90303", 0x7f);
		struct	_gridHi gridHi;
		CString	codeS, sendCodeS = "";

		int irowCnt = m_pRemainGrid->GetRowCount();
		for (int row = 0; row <irowCnt ; row++)
		{
			codeS = m_pRemainGrid->GetItemText(row, colCODE);
			if (codeS.IsEmpty())	continue;

			strTmp.Format("%s%c", codeS, 0x7f);
			sendCodeS += strTmp;
		}

		memset(&gridHi, ' ', sizeof(struct _gridHi));
		CopyMemory(gridHi.visible, "99", sizeof(gridHi.visible));
		strTmp.Format("%04d", irowCnt);
		CopyMemory(gridHi.rows, strTmp, sizeof(gridHi.rows));

		gridHi.type = '0';
		gridHi.dir  = '1';
		gridHi.sort = '0';

		sendS += CString((char *)&gridHi, sizeof(struct _gridHi));
		sendS += sendsymbols;

		strTmp.Format("%s%c", strCodeSym, 0x7f);	// 종목코드
		sendS += strTmp;
		sendS += sendCodeS;

		strTmp.Format("%c%c", 0x0A, 0x09);
		sendS += strTmp;
		trkey->gubn = GOOPKEY;
		trkey->key = 0;
	}
	else
	{
		strTmp.Format("%s%c%s%c", strCodeSym,0x7f, strCode, tabCHAR);
		sendS += strTmp;
		sendS += sendsymbols;
		trkey->gubn = POOPKEY;
		trkey->key = irow;
	}

	SendTransaction(POOPQUERY, sendS, US_OOP, key);
}

/***********************************************************************************
계좌별잔고조회
*************************************************************************************/
void CMainWnd::CheckPassword()
{
	if(m_pToolBar[0]) 
	{
		if(!m_pToolBar[0]->IsWindowEnabled() ) return;
	}
		

	CString strAccount = "";
	CString strPass = m_pPassEdit->GetText();

	if(m_bDebugMode)
	{
		if(m_pTestCbo)
		{
			int isel = m_pTestCbo->GetCurSel();
			if(isel > -1)
				m_pTestCbo->GetLBText(isel, strAccount);
			strAccount = RemoveToken(strAccount, "-");
		}

		if(strAccount.IsEmpty()) strAccount = "00210000017";
		if(strPass.IsEmpty()) strPass = "0423";
		m_pPassEdit->SetText(strPass);
	}
	else
	{
		if(m_pAccnCtrl)
		{
			strAccount = Trim(m_pAccnCtrl->GetAccNo());
			if(strAccount.IsEmpty()) 
			{
				MessageBox("계좌번호가 입력되지 않았습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
				return;
			}
		}

		if(strPass.IsEmpty()) 
		{
			MessageBox("비밀번호가 입력되지 않았습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
			m_pPassEdit->SetSelectFocus();
			return;
		}

		CheckPassWord(strAccount, strPass) ;
	}
	
}

void CMainWnd::ExecJangoQuery(CString strCode, CString sNext, int irow)
{
	if(m_pToolBar[0]) 
	{
		if(!m_pToolBar[0]->IsWindowEnabled() ) return;
	}
		

	if(strCode.IsEmpty() && !m_bNextList) ResetData();

	CString strAccount = "";
	CString strPass = m_pPassEdit->GetText();

	if(m_bDebugMode)
	{
		if(m_pTestCbo)
		{
			int isel = m_pTestCbo->GetCurSel();
			if(isel > -1)
				m_pTestCbo->GetLBText(isel, strAccount);
			strAccount = RemoveToken(strAccount, "-");
		}

		if(strAccount.IsEmpty()) strAccount = "00210000017";
		if(strPass.IsEmpty()) strPass = "0423";
		m_pPassEdit->SetText(strPass);
	}
	else
	{
		if(m_pAccnCtrl)
		{
			strAccount = Trim(m_pAccnCtrl->GetAccNo());
			if(strAccount.IsEmpty()) 
			{
				MessageBox("계좌번호가 입력되지 않았습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
				return;
			}
		}

		if(strPass.IsEmpty()) 
		{
			MessageBox("비밀번호가 입력되지 않았습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
			m_pPassEdit->SetSelectFocus();
			return;
		}

	}
	

	((CIB100400App*)AfxGetApp())->SaveBuffer(_T("PASS"), strPass);
	
	if(m_pToolBar[0]) m_pToolBar[0]->EnableWindow(FALSE);

// 	struct _ledgerH ledger;
// 	
// 	FillMemory(&ledger, L_ledgerH, ' ');
// 	
// 	CWnd*	pView = (CWnd*)m_pMainWnd->SendMessage(WM_MANAGE, MAKEWPARAM(MK_GETWND, MO_VIEW));
// 	pView->SendMessage(WM_USER, ledgerDLL, (LPARAM)&ledger);
// 	
// 	CopyMemory(&ledger.svcd, FutureService, sizeof(ledger.svcd));
// 	CString strUser = CString((char*)m_pMainWnd->SendMessage(WM_MANAGE, MK_GETID));
// 	CopyMemory(&ledger.usid, (LPCTSTR)strUser, strUser.GetLength());
// 	
// 	CString strBrno = (char*)pView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, deptCC), 0L);
// 	CopyMemory(&ledger.brno, strBrno.Left(3), 3);
// 	CopyMemory(&ledger.rcnt, _T("0000"), sizeof(ledger.rcnt));
// 	
// 	ledger.fkey[0] = 'C';
// 	ledger.mkty[0] = '2';
// 	ledger.odrf[0] = '1';
// 	
// 	CString strLedger = CString((char*)&ledger, L_ledgerH);

	CString strSend = _T("");
	m_strLedger = GetLedger("SONBQ021", strAccount, '1', sNext) ;
	char	key;
	_trkey* trkey = (struct _trkey*)&key;

	if(strCode.IsEmpty() ) 
	{
		trkey->gubn = SJGOLIST;
		trkey->key=0;
	}
	else 
	{
		trkey->gubn = SJGOROW;
		trkey->key= irow;
		strCode = GetCode(strCode);
	}

	CString sData = m_strLedger;
	f_mid input;
	FillMemory(&input, sizeof(f_mid), ' ');
	CopyMemory(input.accn, filltoken(strAccount, 11, " ", 0), sizeof(input.accn));
	CopyMemory(input.pswd, filltoken(strPass, 8, " ", 0), sizeof(input.pswd));
	CopyMemory(input.date, "", sizeof(input.date));
	CopyMemory(input.cod2 , filltoken(strCode, 12, " ", 0), sizeof(input.cod2));
	//input.allf[0] = '1';// ALL

	sData += CString((char*)&input, sizeof(f_mid));
	SendTransaction("PIBOFJGO", sData, US_ENC, key);
	SetTimer(TIMER_QUERY, 10000, NULL);
}

CString CMainWnd::GetCaseTextLog(_config cfg)
{
	CString scase = "", stmp;
	CString sTxt[] = {"감시손실", "감시이익", "감시보존"};
	for(int c=0; c<3; c++)
	{
		if(cfg.istopexe[c])  
		{
			stmp.Format("[%s : %.2f %s ", sTxt[c], cfg.ival[c], m_sUnitText[ cfg.iunit[c]]); 
			if(c == 2)
			{
				scase += stmp;
				stmp.Format(" / %.2f %s ", cfg.ival[3], m_sUnitText[ cfg.iunit[3]]); 
			}
			
			stmp += "]";
			scase += stmp;
		}
	}
	
	//구분:0-지정가, 1-시장가, 2-조건부, 3-최유리
	CString strGubn,strVolType;
	switch (cfg.igubn)
	{
	case 0:
		strGubn = "지정가";
		break;
	case 1:
		strGubn = "시장가";
		break;
	case 2:
		strGubn = "조건부";
		break;
	case 3:
		strGubn = "최유리";
		break;
	}
	
	switch (cfg.ivoltype)
	{
	case 0:
		strVolType = "%";
		break;
	case 1:strVolType = "주";
		break;
	}
	
	stmp.Format("[주문 : %s %d%s %s %d틱]",strGubn,cfg.ivolval,strVolType,cfg.sprctype,cfg.iprcval);
	
	scase += stmp;
	
	return scase;
}

/***********************************************************************************
전체설정/종목별 설정
*************************************************************************************/
int CMainWnd::ExecSetup(int itype, int irow)
{
	CString sCrtType = "";
	if(irow >= 0) sCrtType = m_pRemainGrid->GetItemText(irow, colCRETYPE);

	CConfigDlg	pDlg(itype, sCrtType, this);
	CString sCode;

	CString setupchk = m_pRemainGrid->GetItemText(irow, colSET);
	if(!itype) pDlg.m_stConfig = m_stAllconfig;
	else
	{
		if(irow < 0) return 0;
		_config cfgval = m_arConfigList.GetAt(irow);
		pDlg.m_stConfig = cfgval;
		sCode = m_pRemainGrid->GetItemText(irow, colCODE);

		//if( m_pRemainGrid->GetItemText(irow, colCRTCD) == "05")
		if(m_pRemainGrid->GetItemText(irow, colJANTYPE).Find("매도") > -1)
			pDlg.SetJumunType("매 수");
		else
			pDlg.SetJumunType("매 도");

		pDlg.SetCode(sCode, m_pRemainGrid->GetItemText(irow, colNAME));
		pDlg.SetPossvol(m_pRemainGrid->GetItemText(irow, colPOSSVOL));
		pDlg.m_stConfig = m_arConfigList.GetAt(irow);
		m_pRemainGrid->SetItemText(irow, colSET, B_SETUP);
	}
	
	int iResult = 0;
	if( pDlg.DoModal() == IDOK)
	{
		m_pQueryModalWnd = NULL;
		CString sLog, sItem;

		if(itype)
		{
			_config cfgval = pDlg.m_stConfig;
			bool bmatch = true;
			if( m_pRemainGrid->GetItemText(irow, colSET) != B_SETUP)
			{
				bmatch = false;
				for(int i=irow+1; i< m_pRemainGrid->GetRowCount(); i++)
				{
					if( m_pRemainGrid->GetItemText(irow, colSET) == B_SETUP)
					{
						irow = i;
						break;
					}
				}
			}
				
			if(bmatch)
			{
				OutputDebugString("BMATCH================\n");
				SetCheckCase(irow, cfgval);

				m_arConfigList.SetAt(irow, cfgval);

				if( IsvalidateSetupCase(irow) )
				{
					ResetJumunValue(irow);

					m_pRemainGrid->SetItemData(irow, colCHECK, 1);
					m_pRemainGrid->SetItemText(irow, colSET, S_SETUP);
					sItem = m_pRemainGrid->GetItemText(irow, colNAME);
					sLog.Format("%s", GetCaseTextLog(cfgval) );
					WriteLog("개별설정", sLog, sCode, sItem);

					CString sMessage;
					sMessage.Format("감시설정 종목 : %s[%s]", m_pRemainGrid->GetItemText(irow, colNAME), m_pRemainGrid->GetItemText(irow, colCODE));
					SetGuideMessage(sMessage);
				}
				else ResetCaseValue(irow);
			}
		}
		else
		{
			m_stAllconfig = pDlg.m_stConfig;
			for(int i=0; i< m_pRemainGrid->GetRowCount(); i++)
			{
				if(	m_pRemainGrid->GetItemText(i, colSET) != S_SETUP)
				{
					SetCheckCase(i, m_stAllconfig);
					if (m_arConfigList.GetSize()>0)  //1보다 작은 경우인데 초기에 비어있는 라인때문에 참조에러뜸  따라서 예외처리 함  
						m_arConfigList.SetAt(i, m_stAllconfig);
				}
				
				if(m_stAllconfig.inow)
				{
					if((m_stAllconfig.istopexe[0] || m_stAllconfig.istopexe[1] || m_stAllconfig.istopexe[2]) && (CInt( m_pRemainGrid->GetItemText(i, colPOSSVOL) ) > 0))
						m_pRemainGrid->SetItemData(i, colCHECK, 1);
					else
						m_pRemainGrid->SetItemData(i, colCHECK, 0);
				}
			}

			sItem = "전체";
			sLog.Format("%s",  GetCaseTextLog(m_stAllconfig) );

			WriteLog("전체설정", sLog, "", "");
		}

		iResult = 1;
	}
	else
		m_pRemainGrid->SetItemText(irow, colSET, setupchk);

	return iResult;
}

/***********************************************************************************
전체설정해제/종목별 설정해제
*************************************************************************************/
void CMainWnd::ExecResetSetup(int itype)//설정해제
{
	if(!itype)
	{
		//전체해제
		for(int i=0; i<4; i++)
		{
			m_stAllconfig.istopexe[i] = 0;
			m_stAllconfig.iunit[i] = 0;
			m_stAllconfig.ival[i] = 0;
		}

		for(int i=0; i<m_pRemainGrid->GetRowCount(); i++)
			ResetCaseValue(i);
	}
	else
	{
		//선택로우만 해제
		if(m_iSelectRow >= 0)
			ResetCaseValue(m_iSelectRow);
	}
}

/***********************************************************************************
실행내역보기
*************************************************************************************/
void CMainWnd::ExecViewLog()
{
	if(!m_pLogDlg)
	{
		m_pLogDlg = new CLogDlg(m_strLogPath);
		m_pLogDlg->Create(IDD_LOGDIALOG, this);
	}

	m_pLogDlg->ShowWindow(SW_SHOW);
}

CString CMainWnd::GetPrice_SetupValue(int irow, int iunitType, int istopType, double iconfigval, int iCodeType, CString type)
{
	
	//iunitType- {"틱", "%", "원", "입력"};
	////istopType 0-손실목표, 1-이익, 2-보존, 3-고점대비
	CString sResult = _T("");
	double icostval = atof( m_pRemainGrid->GetItemText(irow, colCOST) );
	
	int iAddType = istopType;

	if(type.Find("매 도") > -1)
	{
		if(istopType == 0) istopType = -1;
		else istopType = 1;
	}
	else
	{
		if(istopType == 0) istopType = 1;
		else istopType = -1;
	}
	
	//icostval = getPrice(icostval, iCodeType, istopType);

	CString s;
	s.Format("COST : [%f]\n",icostval);
	OutputDebugString(s);

	s.Format("TYPE : [%s] UNITTYPE : [%d]	iSTOPTYPE : [%d]	CFGVAL : [%.2f]\n",type,iunitType,iAddType,iconfigval);
	OutputDebugString(s);

	double iprice = icostval;

	if(iunitType == 2)//가격
	{
		if(iAddType < 3) 
		{
			iconfigval *= istopType;
			iprice = icostval + iconfigval;
		}
		else iprice = iconfigval;
	}
	else if(iunitType == 1)//%
	//if(iunitType == 1)//%
	{
		iprice = (icostval * iconfigval) / 100;
		iprice *= istopType;
		if(iAddType < 3) iprice = icostval + iprice;
	}
	else if(iunitType == 0)//TICK
	{
		if(iAddType < 3) 
			iprice = getTickPrice(icostval, (int)iconfigval, (int)iCodeType, (int)istopType);
		else
		{
			if(type.Find("매 수") > -1)
			{
				iconfigval = iconfigval * -1;
			}

			CString s;
			s.Format("CONFIG VALUE : [%f]\n",iconfigval);
			OutputDebugString(s);
			iprice = getTickValue(icostval, (int)iconfigval, (int)iCodeType);
		}
	}

	sResult.Format("%.2f",  iprice);
	OutputDebugString("********\n");
	OutputDebugString(sResult);
	OutputDebugString("********\n");
	return sResult;
}

//주문조건설정
void CMainWnd::SetCheckCase(int irow, _config cfg, BOOL bFirst)
{
	////0-손실목표, 1-이익, 2-보존, 3-고점대비
	CString s;
	s.Format("SETCHECKCASE 주문 가능 수량 : [%d]\n",CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL) ));
	OutputDebugString(s);
	
	CString strtype = m_pRemainGrid->GetItemText(irow, colJANTYPE);

	if( CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL) ) <= 0)
	{
		MessageBox("주문 가능 수량이 없습니다.", MAPTITLE, MB_ICONINFORMATION|MB_OK);
		return;
	}

	int iCodeType;
	iCodeType = getCodeType(m_pRemainGrid->GetItemText(irow, colCODE) );
	
	s.Format("CODE : %s		CODETYPE : %d\n",m_pRemainGrid->GetItemText(irow, colCODE),iCodeType);
	OutputDebugString(s);
	m_pRemainGrid->SetItemText(irow, colCDTYPE, CStr(iCodeType));
	
	if( iCodeType == elwType)
	{
		if( cfg.iprctype == 0 || cfg.iprctype == 12)
		{
			if(!bFirst)
				MessageBox("ELW종목인경우 상하한가 적용이 안됩니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
			return;
		}
	}

	s.Format("CFG TYPE : [%s]\n",cfg.type);
	OutputDebugString(s);
	if(cfg.type == "청 산")
	{
		CString type = m_pRemainGrid->GetItemText(irow, colJANTYPE);
		s.Format("JANTYPE TYPE : [%s]\n",type);
		OutputDebugString(s);

		if(type.Find("매수") > -1)
		{
			cfg.type = "매 도";
		}
		else
		{
			cfg.type = "매 수";
		}
	}

	CString sVal, sCase;
	int icol = colLOSS;
	bool bexec = false;

	double icostval;
	for(int i=0; i<4; i++)
	{
		sVal = sCase = _T("");
		if( cfg.istopexe[i])
		{
			s.Format("조건설정 : [%d]	[%d]	[%f]	[%d]	[%s]\n",cfg.iunit[i],i,cfg.ival[i],iCodeType,cfg.type);
			OutputDebugString(s);
			if(cfg.iunit[i] == 3) sVal.Format("%.2f",cfg.ival[i]);
			else sVal = GetPrice_SetupValue(irow, cfg.iunit[i], i, cfg.ival[i], iCodeType,cfg.type);
			icostval = atof( RemoveToken(m_pRemainGrid->GetItemText(irow, colCOST), ",") ) ;

			if(i==0)
			{
				if(cfg.type.Find("매 도") > -1)
				{
					if(icostval < atof(sVal) )
					{
						if(!bFirst)
							MessageBox("매도시 손실목표금액은  매입단가보다 낮게 설정되야 합니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
						return;
					}
				}
				else
				{
					if(icostval > atof(sVal) )
					{
						if(!bFirst)
							MessageBox("매수시 손실목표금액은  매입단가보다 높게 설정되야 합니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
						return;
					}
				}
			}

			if(i==1 || i==2)
			{
				if(cfg.type.Find("매 도") > -1)
				{
					if(icostval > atof(sVal) )
					{
						if(!bFirst)
							MessageBox("매도시 이익목표금액은 매입단가보다 낮게 설정할수 없습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
						return;
					}
				}
				else
				{
					if(icostval < atof(sVal) )
					{
						if(!bFirst)
							MessageBox("이익목표금액은 매입단가보다 높게 설정할수 없습니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
						return;
					}
				}
			}

			if(i == 2)
				sCase.Format("%.2f%s/%.2f%s",  cfg.ival[2], m_sUnitText[ cfg.iunit[2] ],  cfg.ival[3], m_sUnitText[ cfg.iunit[3] ]);
			else sCase.Format("%.2f %s",  cfg.ival[i], m_sUnitText[ cfg.iunit[i] ]);
				//sCase.Format("%s",  m_sUnitText[ cfg.iunit[i] ]);
			bexec = true;
		}

		m_pRemainGrid->SetItemText(irow, icol++, sVal);
		m_pRemainGrid->SetItemText(irow, icol++, sCase );

		CString s;
		s.Format("VALUE :%s \n",sVal);

		OutputDebugString(s);

		s.Format("CASE : %s \n",sCase);

		OutputDebugString(s);
	}
	
	if(!bexec)  sCase = _T("");
	else sCase.Format( "%d%%", cfg.ivolval);
	OutputDebugString("OK =====\n");
	m_pRemainGrid->SetItemText(irow, colJVOLCASE, sCase);

	//수량
	int icvol = 0;
	double ipossvol = 0.f;
	if(cfg.ivoltype)
		ipossvol = cfg.ivolval;
	else
	{
		ipossvol = atof( m_pRemainGrid->GetItemText(irow, colPOSSVOL)) * cfg.ivolval;
		ipossvol /= 100.0f;
	}
	
	int ivol = (int)ipossvol;
	
	int idiv = CInt(m_pRemainGrid->GetItemText(irow, colVolUNIT));//getAmountType(CInt(m_pRemainGrid->GetItemText(irow, colCDTYPE)), m_pRemainGrid->GetItemText(irow, colPCUR) );
	//CString tmp; tmp.Format("%d | %d", ivol, idiv);
	//AfxMessageBox(tmp);
	if(ivol > idiv )
	{
		if (idiv != 0)
		{
			int iq = ivol % idiv;
			if(iq > 0) ivol -= iq;
		}
	}
	
	m_pRemainGrid->SetItemText(irow, colCVOL, CStr(ivol));
	
	OutputDebugString("SETCHECKCASE =====\n");
	//가격-입력
}	

/***********************************************************************************
리얼타임데이타 수신시 설정조건 확인후 주문접수
*************************************************************************************/
void CMainWnd::CheckStopLossValue(int irow)
{
CString slog;
slog.Format("IB300800 start irow=%d\n", irow);
OutputDebugString(slog);

	if( m_pRemainGrid->GetItemText(irow, colSET) == B_SETUP ) return; //설정중인거는 스킵
	if( CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL) ) <= 0) return;

	_config cfgval = m_arConfigList.GetAt(irow);
	double icurrPrice = atof( RemoveToken( m_pRemainGrid->GetItemText(irow, colCURR), "-") ); //현재가
	bool bjumunExec = false;
	CString sExec = "", sLogExec, sCase;

	CString type = m_pRemainGrid->GetItemText(irow, colJANTYPE);

	//손실목표
	if(cfgval.istopexe[0] )
	{
		double ichkprice = atof( m_pRemainGrid->GetItemText(irow, colLOSS) );

		if(type.Find("매수") > -1)
		{
slog.Format("IB300800 start irow=%d\n", irow);
//OutputDebugString(slog);
			if (icurrPrice <= ichkprice)
			{
slog.Format("IB300800 start irow=%d\n", irow);
//OutputDebugString(slog);
				bjumunExec = true;
				//exec
				sExec = _T("S");

				sCase.Format("(현재가)%.2f <= %.2f(설정액)", icurrPrice,  ichkprice);
				sLogExec = _T("손실조건도달");
			}
		}
		else
		{
			if (icurrPrice >= ichkprice)
			{
				bjumunExec = true;
				//exec
				sExec = _T("S");
				
				sCase.Format("(현재가)%.2f >= %.2f(설정액)", icurrPrice,  ichkprice);
				sLogExec = _T("손실조건도달");
			}
		}

// 		CString s;
// 		s.Format("CURR PRICE : [%f]		CHKPRICE : [%f]\n",icurrPrice,ichkprice);
// 		OutputDebugString(s);
	}

	//이익목표
	if(cfgval.istopexe[1] )
	{
		double ichkprice = atof( m_pRemainGrid->GetItemText(irow, colMIT) );

		if(type.Find("매수") > -1)
		{
			if (icurrPrice >= ichkprice)
			{
				bjumunExec = true;
				sExec = _T("M");
				sCase.Format("(현재가)%.2f >= %.2f(설정액)", icurrPrice,  ichkprice);
				sLogExec = _T("이익조건도달");
				//exec
			}
		}
		else
		{
			if (icurrPrice <= ichkprice)
			{
				bjumunExec = true;
				sExec = _T("M");
				sCase.Format("(현재가)%.2f <= %.2f(설정액)", icurrPrice,  ichkprice);
				sLogExec = _T("이익조건도달");
				//exec
			}
		}
	}

	//이익보존
	if(cfgval.istopexe[2] )
	{
		double ichkprice = atof( m_pRemainGrid->GetItemText(irow, colTS) );
		double imaxprice = atof( m_pRemainGrid->GetItemText(irow, colTSMAX) );
		CString s;
		s.Format("이익보존 ICHKPRICE : [%f]		IMAXPRICE : [%f]\n",ichkprice,imaxprice);
		OutputDebugString(s);

		CString strCurr;
		strCurr.Format("%.2f",icurrPrice);

		if(type.Find("매수") > -1)
		{
			if( imaxprice >= ichkprice)
			{
				double idnprice = atof( m_pRemainGrid->GetItemText(irow, colTSDIF) ); 
				double icomprice = imaxprice - idnprice;

				s.Format("이익보존 DNPRICE : [%.2f]		COMPRICE : [%.2f]\n",idnprice,icomprice);
				OutputDebugString(s);

				if (icurrPrice <= icomprice) 
				{
					bjumunExec = true;
					m_pRemainGrid->SetItemText(irow, colTSMAX, "");
					sExec = _T("T");

					sCase.Format("현재가:%.2f <= (고점:%.2f-고점대비하락액:%.2f) ",  icurrPrice, imaxprice, idnprice);
					sLogExec = _T("이익보존도달");
					//exec
				}
			}
			
// 			s.Format("매수 현재가 : [%f]\n",icurrPrice);
// 			OutputDebugString(s);

			if (!bjumunExec && icurrPrice > imaxprice )
				m_pRemainGrid->SetItemText(irow, colTSMAX, strCurr );
		}
		else
		{
			if( imaxprice > 0 && imaxprice <= ichkprice)
			{
				double idnprice = atof( m_pRemainGrid->GetItemText(irow, colTSDIF) ); 
				double icomprice = imaxprice - idnprice;

				s.Format("이익보존 DNPRICE : [%.2f]		COMPRICE : [%.2f]\n",idnprice,icomprice);
				OutputDebugString(s);

				if (icurrPrice >= icomprice) 
				{
					bjumunExec = true;
					m_pRemainGrid->SetItemText(irow, colTSMAX, "");
					sExec = _T("T");
					
					sCase.Format("현재가:%.2f >= (고점:%.2f-고점대비하락액:%.2f) ",  icurrPrice, imaxprice, idnprice);
					sLogExec = _T("이익보존도달");
					//exec
				}
			}

// 			s.Format("매도현재가 : [%f]\n",icurrPrice);
// 			OutputDebugString(s);
			
			if (!bjumunExec && (icurrPrice < imaxprice || imaxprice == 0) )
				m_pRemainGrid->SetItemText(irow, colTSMAX, strCurr );
		}
	}

	if(!bjumunExec) return;

	CString sText, sLog, sTmp;
	sLog += sCase;
	WriteLog(sLogExec, sLog, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));

	//호가구분 00: 지정가 03: 시장가 05: 조건부지정가 06: 최유리지정가
	sText="00";
	switch(cfgval.igubn )
	{
		case 1:
			sText="03";
			break;
		case 2:
			sText="05";
			break;
		case 3:
			sText="06";
			break;
	}
	m_pRemainGrid->SetItemText(irow, colHOGATYPE,sText);
	m_pRemainGrid->SetItemText(irow, colJVOL, m_pRemainGrid->GetItemText(irow, colCVOL) );

	CString s;
// 	s.Format("JVOL : %s		CVOL : %s\n",m_pRemainGrid->GetItemText(irow,colJVOL),m_pRemainGrid->GetItemText(irow,colCVOL));
// 	OutputDebugString(s);

	//주문가격
	CString sPrice = "";
	CString tmp;

	if(cfgval.igubn == 0 || cfgval.igubn == 2)
	{
		if(cfgval.iprctype == 16) //입력
		{
			sPrice.Format("%.2f",cfgval.iprcval );

// 			s.Format("JPRICE $: %f\n",cfgval.iprcval);
// 			OutputDebugString(s);
		}
		else
		{
			double ijprice = atof( RemoveToken(m_pRemainGrid->GetItemText(irow, colSISE+cfgval.iprctype), '-') );
			s.Format("ijprice @: %f\n",ijprice);
			OutputDebugString(s);

			if(cfgval.iprcval > 0)
			{
				double iCodeType = iCodeType = atof(m_pRemainGrid->GetItemText(irow, colCDTYPE) );
				ijprice = getTickPrice(ijprice, (int)cfgval.iprcval, (int)iCodeType, 1);
			}

			//sPrice = CStr(ijprice);
			sPrice.Format("%.2f",ijprice);
			s.Format("JPRICE @: %f\n",ijprice);
			OutputDebugString(s);
		}
	}
	
	m_pRemainGrid->SetItemText(irow, colJPRICE, sPrice);
	m_pRemainGrid->SetItemText(irow, colEXEC, sExec);
	
	ExecJumunQuery(irow);
}

CString CMainWnd::GetHogaType(int itype)
{
	//시장가{"00", "03", "05", "06"};
	switch(itype)
	{
		case 3: return "시장가";
		case 5: return "조건부";
		case 6: return "최유리";
	}

	return "보통";
}

/***********************************************************************************
주문접수
*************************************************************************************/
CString CMainWnd::GetJumunCrtCode(CString sCrtCode, CString& sTxtValue)
{
	CString sCodeList[] = {"101", " 02", "103", " 22", "107", "180"};
	CString sCodeTxtList[] = {"유통융자상환", "단기신용융자", "자기융자상환", "단기신용상환", "자기대주상환", "예탁담보대출상환"};
	for(int i=0; i<6; i++)
	{
		if(sCrtCode == sCodeList[i].Right(2) ) 
		{
			sTxtValue = sCodeTxtList[i];
			return  sCodeList[i];
		}
	}

	return filltoken( sCrtCode, 3, " ", 0);
	
}

#include "JumunConfirmDlg.h"
void CMainWnd::ExecJumunQuery(int irow)
{
// 	CString s;
// 
// 	//본사직원 주문 안나가도록 예외 처리 [ Start ]
// 	if (!(long)m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, orderCC), 0L))
// 	{
// 		if (!(long)m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, orderCCx), 0L))
// 		{
// 			MessageBox("본사직원은 주문이 불가합니다.","IBK투자증권");
// 			return;
// 		}	
// 	}
// 	//본사직원 주문 안나가도록 예외 처리 [ End ]
// 	//계좌번호
// 	CString strAccount = "";
// 	if(m_bDebugMode)
// 	{
// 		if(m_pTestCbo)
// 		{
// 			int isel = m_pTestCbo->GetCurSel();
// 			if(isel > -1)
// 				m_pTestCbo->GetLBText(isel, strAccount);
// 			strAccount = RemoveToken(strAccount, "-");
// 		}
// 	}
// 	else
// 	{
// 		if(m_pAccnCtrl)
// 			strAccount = Trim(m_pAccnCtrl->GetAccNo());
// 	}
// 
// 	if(strAccount.IsEmpty()) return;
// 
// 	int iCodeType = CInt(m_pRemainGrid->GetItemText(irow, colCDTYPE) );
// 	s.Format("CODETYPE : %d\n",iCodeType);
// 	OutputDebugString(s);
// 	CString sCode = m_pRemainGrid->GetItemText(irow, colCODE);
// 	struct	_orderR orderR;
// 	FillMemory(&orderR, sizeof(orderR), ' ');
// 	CString shoga = m_pRemainGrid->GetItemText(irow, colHOGATYPE);//호가구분
// 	s.Format("HOGAGUBN : %s\n",shoga);
// 	OutputDebugString(s);
// 	//처리건수
// 	CopyMemory(orderR.nrec, "0001", nREC);
// 	//주문유형:1-현물, 2선물옵션, 3예약주문
// 	//	char	odgb;//주문유형 1: 일반(위탁,저축)  2: 선물옵션 3. 단주매매 4: 신용매매 5: 채권매매
// 	int iGubn = CInt( m_pRemainGrid->GetItemText(irow, colCRTCD) );
// 	orderR.odgb = '2';
// 	if((iGubn > 0) && (iGubn != 80)) orderR.odgb = '4';
// 
// 	//시장구분1: 거래소 2: 코스닥 3: 프리보드  5: 장외
// // 	orderR.mkgb = '1';
// // 	switch (iCodeType)
// // 	{
// // 		case kospiType:
// // 			orderR.mkgb = '1';
// // 			break;
// // 		case kosdaqType:
// // 			orderR.mkgb = '2';
// // 			break;
// // 		case etfType:
// // 			orderR.mkgb = '1';
// // 			break;
// // 		case elwType:
// // 			orderR.mkgb = '1';
// // 			break;
// // 		default:
// // 			return;
// // 	}
// 
// 	//매매구분:매도1, 2매수,3정정, 4추시고
// 	int ijumunType = 0;
// 	bool bCrtType = false;
// // 	orderR.mmgb = '1';
// // 	if(iGubn ==  5)
// // 	{
// // 		//신용중 05:유통대주인경우만
// // 		orderR.mmgb = '2';
// // 		ijumunType = 1;
// // 	}
// 	CString jngoType = m_pRemainGrid->GetItemText(irow, colJANTYPE);
// 
// 	if(jngoType == "매수")
// 	{
// 		orderR.mmgb = '1';
// 	}
// 	else
// 	{
// 		orderR.mmgb = '2';
// 	}
// 
// 	//계좌번호
// 	CopyMemory(orderR.accn, filltoken(strAccount, sizeof(orderR.accn), " "), sizeof(orderR.accn));
// 	//비밀번호
// 	CopyMemory(orderR.pswd, filltoken(m_pPassEdit->GetText(), sizeof(orderR.pswd), " "), sizeof(orderR.pswd));
// 	//원주문번호
// 	//종목코드
// 	CopyMemory(orderR.code, filltoken(sCode, sizeof(orderR.code), " "), sizeof(orderR.code));
// 	
// 	//주문수량
// 	CString strvol = m_pRemainGrid->GetItemText(irow, colJVOL);
// 	strvol.Remove(','); 
// 	CopyMemory(orderR.jmsr, filltoken(strvol, sizeof(orderR.jmsr), "0", 1), sizeof(orderR.jmsr));
// 
// 	//주문단가
// 	CString sPrice = m_pRemainGrid->GetItemText(irow, colJPRICE);
// 	sPrice.Remove(','); 
// 	int nPrc = atoi(sPrice) * 100;
// 	sPrice.Format("%d",nPrc);
// 	CopyMemory(orderR.jprc, filltoken(sPrice, sizeof(orderR.jprc), "0", 1), sizeof(orderR.jprc));
// 
// 	//호가구분
// 	CString sHogaType = m_pRemainGrid->GetItemText(irow, colHOGATYPE);
// 	CopyMemory(orderR.hogb, sHogaType, 2);//시장가{"00", "03", "05", "06"};
// 	//주문조건
// 	CopyMemory(orderR.jmgb, "00" , 2);//주문조건 01: IOC 02: FOK
// 	//정정취소
// 
// 	//처리구분-
// 	CString sLogType = "주문접수";
// 	CString sCrtText = "";
// 	int icrtType = CInt(m_pRemainGrid->GetItemText(irow, colCRTCD));
// 
// 	if( !icrtType || ijumunType == 1) //신용매수는 처리안함
// 	{
// 		//처리구분-일반
// 		CopyMemory(orderR.crgb, "X", sizeof(orderR.crgb));
// 	}
// 	else
// 	{
// 		//처리구분-신용:
// 		bCrtType = true;
// 		sLogType = "신용주문접수";
// 		
// 		CopyMemory(orderR.crgb, "B", sizeof(orderR.crgb));
// 		CString sTmp = GetJumunCrtCode(m_pRemainGrid->GetItemText(irow, colCRTCD), sCrtText);
// 		CString sDate = m_pRemainGrid->GetItemText(irow, colCRTDATE);
// 		sDate.Remove('/');		filltoken(sDate, 8, " ", 0);
// 
// 		sTmp += sDate;
// 		for(int i=sTmp.GetLength() ; i<sizeof(orderR.fill); i++)
// 			sTmp += _T(" ");
// 		
// 		CopyMemory(orderR.fill, sTmp, sizeof(orderR.fill));
// 	}
// 	
// 	if( m_pAutoBtn->GetCheck())
// 	{
// 		COLORREF color[5];
// 		if(!ijumunType)
// 		{
// 			for(int i=0; i<5; i++) color[i] = m_MaedoColor[i];
// 		}
// 		else
// 		{
// 			for(int i=0; i<5; i++) color[i] = m_MaesuColor[i];
// 		}
// 		/*
// 		//======================주문착오방지 Start ===========================
// 		CString jstrCode, jstrName, jstrQty, jstrPrc;
// 		jstrCode = m_pRemainGrid->GetItemText(irow,  colCODE);
// 		jstrName = m_pRemainGrid->GetItemText(irow,  colNAME);
// 		jstrQty  = strvol;
// 		jstrPrc  = sPrice;
// 		jstrQty.Remove(_T(','));
// 		jstrPrc.Remove(_T(','));
// 
// 		BOOL bRet = multiCheckupMistakeOrder(this, atoi((LPCTSTR)jstrPrc), atoi((LPCTSTR)jstrQty), jstrCode, "0", jstrName);
// 		if (!bRet)
// 		{
// 			m_pRemainGrid->SetItemData(irow, colCHECK, 0);
// 			WriteLog("주문취소", "반자동주문취소", m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
// 			return;
// 		}
// 		//======================주문착오방지 End ===========================
// 		*/
// 
// 		CJumunConfirmDlg pdlg(ijumunType, m_pFont, color, m_txtcolor, m_bgcolor, m_DangaColor, bCrtType, this);
// 		pdlg.SetValue(strAccount, m_strAccountName, m_pRemainGrid->GetItemText(irow, colNAME), GetHogaType(CInt(sHogaType)), sCrtText, strvol, sPrice);
// 		
// 		if(pdlg.DoModal() != IDOK )
// 		{
// 			m_pRemainGrid->SetItemData(irow, colCHECK, 0);
// 			WriteLog("주문취소", "반자동주문취소", m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
// 			return;
// 		}
// 		
// 	}
// 
// 	m_strLedger = GetLedger("PIBOFODR", strAccount, '1') ;
// 	CString strSend = m_strLedger;
// 	strSend += CString( (char*)&orderR, sizeof(orderR));
// 
// 	char	key;
// 	_trkey* trkey = (struct _trkey*)&key;
// 	trkey->gubn = ORDERKEY;
// 	trkey->key = irow;
// 
// 	m_pRemainGrid->SetItemText(irow, colSTATE, SENDJUMUN);
// 	SendTransaction("PIBOFODR", strSend, 0, key);
// 
// 	m_pRemainGrid->SetItemData(irow, colCHECK, 0);
// 	m_pRemainGrid->SetItemText(irow, colJNO, "접수");
// 	
// 	CString slog;
// 	slog.Format("[계좌%s] 주문단가:%s, 주문수량:%s, 호가구분:%s", SetDataFormat(3, strAccount), sPrice, strvol, sHogaType); 
// 	OutputDebugString(slog);
// 	WriteLog(sLogType, slog, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
	if (!(long)m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, orderCC), 0L))
	{
		if (!(long)m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, orderCCx), 0L))
		{
			MessageBox("본사직원은 주문이 불가합니다.","IBK투자증권");
			return;
		}	
	}

	vector< vector<char> > orders;

	LPCSTR code = (LPCSTR)m_pRemainGrid->GetItemText(irow, colCODE);

	CString strvol = (LPCSTR)m_pRemainGrid->GetItemText(irow, colJVOL);
	strvol.Remove(','); 

	int jqty = atoi(strvol);

	int cdgb = 0;

	CString s;
// 	s.Format("JPRICE : [%s]\n",m_pRemainGrid->GetItemText(irow, colJPRICE));
// 	OutputDebugString(s);
	int oprc = (int)(atof(m_pRemainGrid->GetItemText(irow, colJPRICE))*100);

	CString strAccount = Trim(m_pAccnCtrl->GetAccNo());

// 	s.Format("[ORDER ACCOUNT : %s]\n",strAccount);
// 	OutputDebugString(s);
	CString pswd = Trim(m_pPassEdit->GetText());
	//oprc = pOdr->oprc;	// 여기서 주문가격 초기화 안하면 계좌별로 계속 가격 누적된다!
// 	s.Format("[ORDER PSWD : %s]\n",pswd);
// 	OutputDebugString(s);
	
	CString sHogaType = m_pRemainGrid->GetItemText(irow, colHOGATYPE);

	int odgb = 0;

	CString jngoType = m_pRemainGrid->GetItemText(irow, colJANTYPE);
	int ijumunType = 0;

	if(jngoType == "매도")
	{
		odgb = 2;

		ijumunType = 1;
	}
	else
	{
		odgb = 1;

		ijumunType = 0;
 	}

	orders.push_back(vector<char>());
	make_fodr(orders.back(), odgb, (LPCSTR)strAccount, (LPCSTR)pswd, 0, code, jqty, oprc, cdgb,(LPCSTR)sHogaType);
	
	if (orders.empty()) return;

	vector<char> data;
	merge_order(data, orders);

	LPCSTR acno = strAccount;

	MistakeOrder misOdr;
	
	misOdr.strAccn.Format("%.3s-%.2s-%.6s", acno, acno+3, acno+5);
	misOdr.strCode = code;
	misOdr.lPrice = oprc * 0.01;
	misOdr.lQuantity = jqty;
	misOdr.nMmgb = odgb;
	misOdr.strHogb.Format("%s", sHogaType);
	misOdr.strCurPrc.Format("%f", atof( RemoveToken( m_pRemainGrid->GetItemText(irow, colCURR), "-")) * 0.01);
	misOdr.strStdPrc.Format("%f", atof(RemoveToken( m_pRemainGrid->GetItemText(irow, 57), "-")) * 0.01);
	
// 	s.Format("GJGA [%s]\n",m_pRemainGrid->GetItemText(irow, 57));
// 	OutputDebugString(s);
	
	bool bRet = CheckupMistakeOrder(this, misOdr);

	if( m_pAutoBtn->GetCheck())
	{
		COLORREF color[5];
		if(!ijumunType)
		{
			for(int i=0; i<5; i++) color[i] = m_MaedoColor[i];
		}
		else
		{
			for(int i=0; i<5; i++) color[i] = m_MaesuColor[i];
		}
		/*
		//======================주문착오방지 Start ===========================
		CString jstrCode, jstrName, jstrQty, jstrPrc;
		jstrCode = m_pRemainGrid->GetItemText(irow,  colCODE);
		jstrName = m_pRemainGrid->GetItemText(irow,  colNAME);
		jstrQty  = strvol;
		jstrPrc  = sPrice;
		jstrQty.Remove(_T(','));
		jstrPrc.Remove(_T(','));

		BOOL bRet = multiCheckupMistakeOrder(this, atoi((LPCTSTR)jstrPrc), atoi((LPCTSTR)jstrQty), jstrCode, "0", jstrName);
		if (!bRet)
		{
			m_pRemainGrid->SetItemData(irow, colCHECK, 0);
			WriteLog("주문취소", "반자동주문취소", m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
			return;
		}
		//======================주문착오방지 End ===========================
		*/

		CJumunConfirmDlg pdlg(ijumunType, m_pFont, color, m_txtcolor, m_bgcolor, m_DangaColor, false, this);
		pdlg.SetValue(strAccount, m_strAccountName, m_pRemainGrid->GetItemText(irow, colNAME), GetHogaType(CInt(sHogaType)), "", strvol, m_pRemainGrid->GetItemText(irow, colJPRICE));
		
		if(pdlg.DoModal() != IDOK )
		{
			m_pRemainGrid->SetItemData(irow, colCHECK, 0);
			WriteLog("주문취소", "반자동주문취소", m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
			return;
		}
		
	}

	char	key;
	_trkey* trkey = (struct _trkey*)&key;
	trkey->gubn = ORDERKEY;
	trkey->key = irow;

	m_pRemainGrid->SetItemText(irow, colSTATE, SENDJUMUN);
	SendTR("pibofodr", US_ENC|US_CA, &data[0], data.size(), key);

	m_pRemainGrid->SetItemData(irow, colCHECK, 0);
	m_pRemainGrid->SetItemText(irow, colJNO, "접수");
	
	CString slog;
	slog.Format("[계좌%s] 주문단가:%s, 주문수량:%s, 호가구분:%s", SetDataFormat(3, strAccount), m_pRemainGrid->GetItemText(irow, colJPRICE), strvol, sHogaType); 
	OutputDebugString(slog);
	WriteLog("주문접수", slog, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow, colNAME));
}

BOOL CMainWnd::SendTR(LPCSTR name, char type, LPCSTR data, int dlen, char key)
{
	if (strlen(name)!=8) return FALSE;
	
	char buff[1024*16];
	
	// Header setting
	struct _userTH *udat = (struct _userTH*)buff;
	CopyMemory(udat->trc, name, 8);
	udat->key  = key;
	udat->stat = 0;
	
	// Data setting
	CopyMemory(&buff[L_userTH], data, dlen);
	CString s;
// 	s.Format("ORDER : [%s]\n",CString(data,dlen));
// 	OutputDebugString(s);
	
	return m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, dlen), (LPARAM)buff);
}

struct _ledgerH* CMainWnd::GetLedger( struct _ledgerH *ledger )
{
	m_pAxMain->SendMessage(WM_USER, ledgerDLL, (LPARAM)ledger);
	
	LPCSTR usid = Variant(userCC, (LPCSTR)NULL);
	CopyMemory(ledger->usid, usid, strlen(usid));
	CopyMemory(ledger->fkey, "C", 1);
	CopyMemory(ledger->mkty, "1", 1);
	
	return ledger;
}

LPCTSTR CMainWnd::Variant( int cmd, LPCTSTR data )
{
	return (LPCTSTR)m_pAxMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, cmd), (LPARAM)data);
}

void CMainWnd::make_fodr( vector<char> &buff, int mmgb, LPCSTR acno, LPCSTR pswd, int ojno, LPCSTR code, int jqty, int jprc, int cdgb,LPCSTR hogb)
{
	CString s;
// 	s.Format("MMGB [%d] ACCNT [%s] PSWD [%s] OJNO [%d] CODE [%s] JQTY [%d] JPRC [%d] CDGB [%d] HOGB [%s]\n",mmgb,acno,pswd,ojno,code,jqty,jprc,cdgb,hogb);
// 	OutputDebugString(s);

	if (mmgb<1 || mmgb>4) return;
	if (!acno || !pswd || !code) return;
	if (mmgb>2 && ojno<1) return;
	
	int lsize = L_ledgerH;
	int dsize = sizeof(pibofodr_mid);
	buff.resize(L_ledgerH + sizeof(pibofodr_mid));
	FillMemory(&buff[0], buff.size(), ' ');
	
	struct _ledgerH *ledger = (struct _ledgerH *)&buff[0];
	pibofodr_mid *mid = (pibofodr_mid*)&buff[L_ledgerH];
	
	// Ledger 세팅
	GetLedger(ledger);
	CopyMemory(ledger->odrf, "1", 1);
	CopyMemory(ledger->rcnt, "0000", 4);

	//2013.12.23 KSJ 일방향암호화 추가
	if(strlen(pswd) > 0)
	{
		CString sPswd;
		sPswd = GetEncPassword(pswd);
		CopyMemory(ledger->hsiz, "44", sizeof(ledger->hsiz));
		CopyMemory(ledger->epwd, sPswd, sPswd.GetLength());
	}

	ledger->mkty[0] = '2';
	ledger->odrf[0] = '1';
	
	// 데이터 세팅
	CopyMemory(mid->nrec, "0001", 4);
	mid->odgb[0] = '2';
	mid->mmgb[0] = '0' + mmgb;
	sprintf(mid->accn, "%11s", acno);
// 	sprintf(mid->pswd, "%-8s", pswd);
	sprintf(mid->pswd, "%-8s", "HEAD");		//2013.12.23 KSJ 일방향암호화 추가
	sprintf(mid->ojno, "%12d", ojno);
	sprintf(mid->cod2, "%s", code);
	sprintf(mid->jqty, "%8d", jqty);
	
	sprintf(mid->jprc, "%10d", jprc);

	CopyMemory(mid->hogb, hogb, 2);
	sprintf(mid->cdgb, "%d", cdgb);
	
	mid->mdgb[0] = '2';
	mid->prgb[0] = 'X';
	FillMemory(mid->usrf, sizeof(mid->usrf), ' ');
}

void CMainWnd::merge_order( vector<char> &buff, vector< vector<char> > &orders )
{
	buff.clear();
	if (orders.empty()) return;

	int cnt = orders.size();
	int offset = L_ledgerH + offsetof(pibofodr_mid, odgb);
	int size = L_ledgerH + sizeof(pibofodr_mid);
	CString s;
// 	s.Format("MERGE ODR : %d ORDERSIZE : %d		SIZE : %d\n",cnt,orders[0].size(),size);
// 	OutputDebugString(s);
	char tmp[32];
	buff.reserve(1024*16);

	// Ledger 삽입
	if (orders[0].size()<L_ledgerH) return;
	buff.insert(buff.end(), orders[0].begin(), orders[0].begin() + L_ledgerH);

	// 레코드갯수 조정
	sprintf(tmp, "%04d", cnt);
	buff.insert(buff.end(), tmp, tmp+4);
	
	// 주문데이터 연결
	for(int n=0; n<cnt; ++n)
	{
		if (orders[n].size()==size)
			buff.insert(buff.end(), orders[n].begin() + offset, orders[n].end());
	}
}

void CMainWnd::ResetCaseValue(int irow)
{
	m_pRemainGrid->SetItemText(irow, colSET, "");
	m_pRemainGrid->SetItemText(irow, colJVOLCASE,""); //수량조건

	m_pRemainGrid->SetItemText(irow, colLOSS,""); //손실목표20
	m_pRemainGrid->SetItemText(irow, colLSCFG,""); //
	m_pRemainGrid->SetItemText(irow, colMIT,""); //이익목표
	m_pRemainGrid->SetItemText(irow, colMTCFG,""); //
	m_pRemainGrid->SetItemText(irow, colTS,""); //이익보존
	m_pRemainGrid->SetItemText(irow, colTSCFG,""); //
	m_pRemainGrid->SetItemText(irow, colTSDIF,""); //고점대비하락
	m_pRemainGrid->SetItemText(irow, colTSDIFCFG,""); //
	m_pRemainGrid->SetItemText(irow, colTSMAX,""); //고점

	m_pRemainGrid->SetItemData(irow, colCHECK, 0);
	m_pRemainGrid->SetItemText(irow, colJNO, "");
	m_pRemainGrid->SetItemText(irow, colJMSG, "");
}

void CMainWnd::ResetJumunValue(int irow)
{
	m_pRemainGrid->SetItemText(irow, colHOGATYPE,"");
	m_pRemainGrid->SetItemText(irow, colSTATE,"");
	m_pRemainGrid->SetItemText(irow, colEXEC,"");
	m_pRemainGrid->SetItemText(irow, colJPRICE,"");
	
	m_pRemainGrid->SetItemText(irow, colJVOL,"");
	m_pRemainGrid->SetItemText(irow, colJNO, "");
	m_pRemainGrid->SetItemText(irow, colJMSG, "");
}

/***********************************************************************************
체결데이타 수신처리
*************************************************************************************/
//state : S-접수, C-접수 수신, 
void CMainWnd::SetNoticeData(char* szReceive)
{
 	CString s;
// 	s.Format("NOTICE DATA : [%s]\n",szReceive);
// 	OutputDebugString(s);

	if(!m_bExecMode) return;
	if(!m_pAccnCtrl) return;
	CString selAcc = Trim(m_pAccnCtrl->GetAccNo());

	//OutputDebugString("OK 1\n");
	if(m_bDebugMode)
	{
		if(m_pTestCbo)
		{
			int isel = m_pTestCbo->GetCurSel();
			if(isel > -1)
				m_pTestCbo->GetLBText(isel, selAcc);
			selAcc = RemoveToken(selAcc, "-");
		}
	}

	
	if( selAcc == "") return;
	CString sAccount, sRealCode, sName, sJvol, sJumun, sCredt,  sCredtDate, sjumunNo, sJangoType;
	CString sTmp = CString(szReceive), stmp;
	stmp = SplitString(sTmp, "\n");
	SplitString(stmp, tabCHAR);
	sAccount = SplitString(stmp, tabCHAR);//계좌
	sAccount = Trim(sAccount);
	//OutputDebugString("PARSING 1\n");
	if(selAcc != sAccount) return;
	//OutputDebugString("OK 2\n");
	SplitString(stmp, "\r"); //usid
	sjumunNo = SplitString(stmp, "\n");
	sjumunNo = SplitString(stmp, tabCHAR);
	sjumunNo = stmp;
	

	CMapStringToString arTabList;
	if( SplitString_MAP(sTmp, tabCHAR, arTabList) <= 1) return;
	CString sType;
	if( !arTabList.Lookup("996", sType) ) return;
	sType = Trim(sType);//접수?체결

// 	s.Format("NOTICE TYPE [%s]\n",sType);
// 	OutputDebugString(s);
	
// 	if(sType != "11")
// 	{
// 		return;
// 	}

	arTabList.Lookup("912", sJumun); //매도?매수
	arTabList.Lookup("908", sName); //매도?매수
	int ijType = 0; //매도
	if(sJumun.Find("매수") > -1) ijType = 1;
	
	CString sMessage;
	if(m_pTestCbo)
	{
		int isel = m_pTestCbo->GetCurSel();
		if(isel > -1)
			m_pTestCbo->GetLBText(isel, sTmp);
		sTmp = Trim(sTmp);
		sTmp = RemoveToken(sTmp, "-");
		if(sAccount != sTmp) return;
	}
	
	arTabList.Lookup("907", sRealCode);
	arTabList.Lookup("911", sCredt); //신용코드
	arTabList.Lookup("994", sCredtDate); //신용일자
	arTabList.Lookup("993", sJangoType); //잔고유형

	int ijangotype = CInt(sJangoType);
	if(ijangotype > 1) return;

	sRealCode = Trim(sRealCode);

	CString type = sRealCode.Mid(1,2);
	
	int nType = atoi(type);

	if(nType >= 11 && nType <= 99)
	{
		return;
	}

	int irow = -1, icodrow=-1;
	int i = 0;
	for(i=0; i<m_pRemainGrid->GetRowCount(); i++)
	{
		sTmp = Trim( m_pRemainGrid->GetItemText(i, colRCOD) );
		
		CString strCode;
		strCode.Format("%s",sTmp);

		if(strCode == sRealCode)
		{
			icodrow = i;
			CString tmp; tmp.Format("%d) %s", icodrow, sTmp); 	
			//OutputDebugString(tmp);
			sTmp = Trim(m_pRemainGrid->GetItemText(i, colCRTDATE) );
			sTmp.Remove('/'); 

			irow = i;
			break;
		}
	}

// 	s.Format("SELECT ROW : %d\n",irow);
// 	OutputDebugString(s);

	arTabList.Lookup("909", sJvol);//접수수량
	int ijvol = CInt(sJvol);
	int ivol2 = CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능9

	s.Format("POSSVOL : [%d] 접수수량 : [%d]\n",ivol2,ijvol);
	OutputDebugString(s);

	CString strtype = m_pRemainGrid->GetItemText(irow, colJANTYPE);

	if(strtype.FindOneOf("+-") == 0)
		strtype = strtype.Mid(1);

	CString state, sLogType;
	
	if(sType == "1") //접수
	{
		if(irow < 0) 
		{
			return;
			insertGridRow(0,false);

			irow = 0;
		}

		state = m_pRemainGrid->GetItemText(irow, colSTATE);
		if(state == SENDJUMUN)
		{
			arTabList.Lookup("924", sLogType);
			sLogType = RemoveSign(sLogType, "+", "-");

			sMessage.Format("[%s] %s주문이 접수되었습니다[주문번호:%s]", sName, sLogType, sjumunNo);
			SetGuideMessage(sMessage);

			m_pRemainGrid->SetItemText(irow, colSTATE, RECVJUMUN);//C-접수 수신, 
			m_pRemainGrid->SetItemText(irow, colJNO, sjumunNo);

			sJumun += "주문#:" + sjumunNo;
			sJumun += ", 수량:" + CStr(ijvol);

			WriteLog(sLogType+"접수", sJumun, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow,  colNAME));
		}

// 		if(!ijType) //매도
// 		{
// 			ivol2 -= ijvol;	max(ivol2, 0);//가능수량
// 			m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );//접수시 가능수량만 계산적용
// //			m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
// 			if(m_arConfigList.GetAt(irow).iauto[0] )
// 			{
// 				//잔고변동시 설정된 주문가격/수량 자동 계산----
// 				CheckCase_changejangoVolume(irow);
// 				SetCalcData(irow);
// 			}
// 		}
		if(sJumun != strtype)
		{
			ivol2 -= ijvol;	ivol2 = max(ivol2, 0);//가능수량
			m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );//접수시 가능수량만 계산적용
			//			m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
			if(m_arConfigList.GetAt(irow).iauto[0] )
			{
				//잔고변동시 설정된 주문가격/수량 자동 계산----
				//CheckCase_changejangoVolume(irow);
				SetCalcData(irow);
			}
		}

		return;
	}

	if(sType == "14") //거부
	{
		if(irow < 0) return;

		sLogType = "주문거부";
		if( m_pRemainGrid->GetItemText(irow, colSTATE) == RECVJUMUN)
		{
			WriteLog(sLogType, sJumun, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow,  colNAME));
			ivol2 = CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능9

// 			if(!ijType) //매도
// 			{
// 				ivol2 += ijvol;	//가능수량
// 				m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );
// //				m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
// 
// 				if(m_arConfigList.GetAt(irow).iauto[0] )
// 				{
// 					//잔고변동시 설정된 주문가격/수량 자동 계산----
// 					CheckCase_changejangoVolume(irow);
// 					SetCalcData(irow);
// 				}
// 				SetGuideMessage(sLogType + m_pRemainGrid->GetItemText(irow,  colNAME) );
// 			}

			if(sJumun != strtype)
			{
				ivol2 += ijvol;	//가능수량
				m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );
				//				m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
				
				if(m_arConfigList.GetAt(irow).iauto[0] )
				{
					//잔고변동시 설정된 주문가격/수량 자동 계산----
					CheckCase_changejangoVolume(irow);
					SetCalcData(irow);
				}
				SetGuideMessage(sLogType + m_pRemainGrid->GetItemText(irow,  colNAME) );
			}
		}
		return; 
	}

	if(sType == "13") //취소
	{
		if(irow < 0) return;
		
		sLogType = "취소";

		
		//if( m_pRemainGrid->GetItemText(irow, colSTATE) == RECVJUMUN)
		{
			WriteLog(sLogType, sJumun, m_pRemainGrid->GetItemText(irow,  colCODE), m_pRemainGrid->GetItemText(irow,  colNAME));
			ivol2 = CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능9
			
// 			if(!ijType) //매도
// 			{
// 				ivol2 += ijvol;	//가능수량
// 				m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );
// 				//				m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
// 				
// 				if(m_arConfigList.GetAt(irow).iauto[0] )
// 				{
// 					//잔고변동시 설정된 주문가격/수량 자동 계산----
// 					CheckCase_changejangoVolume(irow);
// 					SetCalcData(irow);
// 				}
// 				SetGuideMessage(sLogType + m_pRemainGrid->GetItemText(irow,  colNAME) );
// 			}

			if(sJumun != strtype)
			{
				ivol2 += ijvol;	//가능수량
				m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );
				//				m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
				
				if(m_arConfigList.GetAt(irow).iauto[0] )
				{
					//잔고변동시 설정된 주문가격/수량 자동 계산----
					CheckCase_changejangoVolume(irow);
					SetCalcData(irow);
				}
				SetGuideMessage(sLogType + m_pRemainGrid->GetItemText(irow,  colNAME) );
			}
		}
		return; 
	}

	//////////////////////////////////////////////체결//////////////////////////////////
	if(sType != "11")
	{
		return;
	}

	CString sCrtPrice, sPrice;
	arTabList.Lookup("933", sCrtPrice);
	int iCrtPrice = CInt(sCrtPrice); //신용금액
	arTabList.Lookup("908", sName);
	arTabList.Lookup("931", sJvol);//체결수량
	arTabList.Lookup("916", sPrice);//체결가격

	if(CInt(sJvol) <= 0 || CInt(sPrice) <= 0) return;

	double nPrice = atof(sPrice);

	double pricef = nPrice/100;

	int m_dBase = getBase(sRealCode);

	s.Format("체결수량 : [%s]	체결가격 : [%s]		델타 : [%d]\n",sJvol,sPrice, m_dBase);
	OutputDebugString(s);

	double lOrderPrice = atof(sJvol) * pricef * m_dBase; //체결매입금액
	double lvol = atof(sJvol);//잔고
	double lpossvol = lvol;//가능
	double lOldOrderPrice = 0;

// 	if(irow >= 0) 
// 	{
// 		lOldOrderPrice = atof( m_pRemainGrid->GetItemText(irow,colAMOUNT) );//매입금액
// 
// 		if(sJumun == strtype)
// 		{
// 			s.Format("OLD ORDERPRICE : [%f]		ORDERPRICE : [%f]\n",lOldOrderPrice,lOrderPrice);
// 			OutputDebugString(s);
// 			
// 			//if(iCrtPrice > 0) lOrderPrice -= iCrtPrice;//매입금액:
// 			lOrderPrice += lOldOrderPrice;
// 		}
// 		else
// 		{
// 			s.Format("OLD ORDERPRICE : [%f]		ORDERPRICE : [%f]\n",lOldOrderPrice,lOrderPrice);
// 			OutputDebugString(s);
// 			lOrderPrice = lOldOrderPrice - lOrderPrice;
// 		}
// 	}

	arTabList.Lookup("908", sName);//종목명

	//////////////////////////////////////////////매수체결/////////////////////////////////
// 	if(ijType)
// 	{
	s.Format("타입 : [%s] [%s]\n",sJumun,strtype);
	OutputDebugString(s);
		
// 		s.Format("SELECT ROW 2 : %d\n",irow);
// 		OutputDebugString(s);
		sPrice.Format("%.2f",pricef);

		s.Format("NOTICE COST2 : [%s]\n",sPrice);
		OutputDebugString(s);

		if(irow >= 0) 
		{
			if(sJumun == strtype)
				lvol += atof( m_pRemainGrid->GetItemText(irow, colVOL));//잔고
			else
				lvol = atof( m_pRemainGrid->GetItemText(irow, colVOL)) - lvol;//잔고

			if(lvol == 0)
			{
				m_pRemainGrid->DeleteRow(irow);
				return;
			}
			else if(lvol < 0)
			{
				lvol = abs(lvol);

				if(sJumun.Find("매도") > -1)
					m_pRemainGrid->SetItemText(irow, colJANTYPE, "매수");
				else
					m_pRemainGrid->SetItemText(irow, colJANTYPE, "매도");
			}

			lOldOrderPrice = atof( m_pRemainGrid->GetItemText(irow,colAMOUNT) );//매입금액
			
			if(sJumun == strtype)
			{
				s.Format("OLD ORDERPRICE : [%f]		ORDERPRICE : [%f]\n",lOldOrderPrice,lOrderPrice);
				OutputDebugString(s);
				
				//if(iCrtPrice > 0) lOrderPrice -= iCrtPrice;//매입금액:
				lOrderPrice += lOldOrderPrice;
			}
			else
			{
				s.Format("OLD ORDERPRICE : [%f]		ORDERPRICE : [%f]\n",lOldOrderPrice,lOrderPrice);
				OutputDebugString(s);

				if(lvol > 0)
				{
					lOrderPrice = lOldOrderPrice * lvol / (lvol + atof(sJvol));
				}
				//lOrderPrice = lOldOrderPrice - lOrderPrice;
			}

			m_pRemainGrid->SetItemText(irow, colVOL, CFStr(lvol));
			
			if(sJumun == strtype)
			{
				lpossvol += atof( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능

				if(lpossvol < 0)
				{
					lpossvol = 0;
				}

				m_pRemainGrid->SetItemText(irow, colPOSSVOL, CFStr(lpossvol));

				double lprc = (lOrderPrice) / (double)(lvol*m_dBase)  ; //매입평균가

				s.Format("ORDERPRICE : [%f]		LVOL : [%.2f]\n",lOrderPrice,lvol);
				OutputDebugString(s);
				s.Format("NOTICE COST : [%f]\n",lprc);
				OutputDebugString(s);
				
				sPrice.Format("%.2f",lprc);
				m_pRemainGrid->SetItemText(irow, colCOST,sPrice );
			}
			else
			{
				//lOrderPrice = lvol * atof(m_pRemainGrid->GetItemText(irow,colCOST)) * m_dBase;

				s.Format("주문 ORDERPRICE : [%f]		LVOL : [%.2f]\n",lOrderPrice,lvol);
				OutputDebugString(s);
			}

			m_pRemainGrid->SetItemText(irow,colAMOUNT, CFStr(lOrderPrice)); //매입금액:
			
			//lpossvol += atof( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능

			s.Format("가능수량 : [%f]\n",lpossvol);
			OutputDebugString(s);
	
// 			if(iCrtPrice > 0)
// 			{
// 				//신용금액
// 				iCrtPrice = CInt( m_pRemainGrid->GetItemText(irow, colCRTPRC) ) + iCrtPrice;
// 				m_pRemainGrid->SetItemText(irow, colCRTPRC, CStr(iCrtPrice) );
// 			}

			SetCalcData(irow);

			if(CInt(m_pRemainGrid->GetItemText(irow, colPOSSVOL)) > 0)
				CheckCase_changejangoVolume(irow);
		}
		else
		{
			_config pconfig = m_stAllconfig;
			if(!m_stAllconfig.iauto[1] )
			{
				//NOT 신규종목편입시 주문조건 자동적용및감시
				pconfig.istopexe[i] = 0;
				pconfig.iunit[i] = 0;
				pconfig.ival[i] = 0;
			}
			
			irow = insertGridRow(0);
			
			m_arConfigList.InsertAt(irow, pconfig);

			m_pRemainGrid->SetItemText(irow, colRCOD, sRealCode );
			CString sCode = GetCode(sRealCode);
			s.Format("SCODE : [%s]\n",sCode);
			OutputDebugString(s);
			
			m_pRemainGrid->SetItemText(irow, colCODE, sCode );
			m_pRemainGrid->SetItemText(irow, colNAME, sName);

			m_pRemainGrid->SetItemText(irow, colCRETYPE, GetCrtText(CInt(sCredt))); 
			m_pRemainGrid->SetItemText(irow, colCRTCD, sCredt);
			
			m_pRemainGrid->SetItemText(irow, colCRTDATE, SetDataFormat(4, sCredtDate, "/"));
			//m_pRemainGrid->SetItemText(irow, colJANTYPE, sJangoType);

			if(sJumun.Find("매수") > -1)
			{
				m_pRemainGrid->SetItemFgColor(irow,colJANTYPE,PALETTERGB(255,0,0));
			}
			else
			{
				//stmp = sJumun.Mid(1);
				
				m_pRemainGrid->SetItemFgColor(irow,colJANTYPE,PALETTERGB(0,0,255));
			}
			
			m_pRemainGrid->SetItemText(irow, colJANTYPE, sJumun);

			m_pRemainGrid->SetItemText(irow, colCRTPRC, sCrtPrice);//신용금액

			m_pRemainGrid->SetItemText(irow, colVOL, sJvol);//잔고
			m_pRemainGrid->SetItemText(irow, colPOSSVOL, sJvol);//가능
			m_pRemainGrid->SetItemText(irow, colCOST, sPrice);//가격

			m_pRemainGrid->SetItemText(irow,colAMOUNT, CFStr(lOrderPrice)); //매입금액:

			if(m_stAllconfig.iauto[1])
			{
				m_pRemainGrid->SetItemData(irow, colCHECK, 1);
 			}
//			DebugLog(sCode);
			
			if(icodrow > -1)
			{
				
				m_pRemainGrid->SetItemText(irow,  colCURR, m_pRemainGrid->GetItemText(icodrow+1, colCURR) );
				
				for(int c=colSISE; c<m_pRemainGrid->GetColumnCount(); c++)
					m_pRemainGrid->SetItemText(irow,  c, m_pRemainGrid->GetItemText(icodrow+1, c) );
				
				SetCalcData(irow);
				
				CheckCase_changejangoVolume(irow);				
			}
			else ExecPOOPQuery(sCode, irow);
		}

		m_pRemainGrid->SetSelectRow(irow);
		return;
	//}

	//////////////////////////////////////////////매도체결/////////////////////////////////

// 	m_pRemainGrid->SetSelectRow(irow);
// 	lvol = atof( m_pRemainGrid->GetItemText(irow, colVOL)) - lvol;//체결시 잔고수량 적용
// 	m_pRemainGrid->SetItemText(irow, colVOL, CFStr(lvol) ); 
// 
// 	lOrderPrice = atof(m_pRemainGrid->GetItemText(irow, colCOST)) * lvol;
// 	iCrtPrice = (int)atof(m_pRemainGrid->GetItemText(irow, colCRTPRC));
// 
// 	if( iCrtPrice > 0) lOrderPrice -= iCrtPrice;
// 	m_pRemainGrid->SetItemText(irow,colAMOUNT, CFStr(lOrderPrice)); //매입금액:
// 
// 
 	SetCalcData(irow);
// //	m_pRemainGrid->Blink(irow, colVOL, m_realcolor);
// //	m_pRemainGrid->Blink(irow, colPOSSVOL, m_realcolor);
// 	CheckCase_changejangoVolume(irow);

	state = m_pRemainGrid->GetItemText(irow, colSTATE);
	if(state != RECVJUMUN) return;//C-접수 수신일때만

	m_pRemainGrid->SetItemText(irow, colJNO, sjumunNo);
	sMessage.Format("[%s] %s주문이 체결되었습니다", sName, sJumun);
	SetGuideMessage( sMessage);
	m_pRemainGrid->SetItemText(irow, colSTATE, "");

	sJumun += "주문#:" + sjumunNo;
	sJumun += ", 체결수량:" + sJvol;
	WriteLog("주문체결", sJumun, sRealCode, sName);
	m_pRemainGrid->SetItemText(irow, colSTATE, CONTJUMUN);
}


void CMainWnd::CheckCase_changejangoVolume(int irow)
{
	CString s;
	s.Format("CONFIG LIST : [%d]	ROW : [%d]\n",m_arConfigList.GetSize(),irow);
	OutputDebugString(s);

	bool bflag = false;

	for(int i=0;i<3;i++)
	{
		if(m_arConfigList.GetAt(irow).istopexe[i])
		{
			bflag = true;
		}
	}
	
	if(bflag)
	{
		if(m_arConfigList.GetAt(irow).iauto[0] )
			SetCheckCase(irow, m_arConfigList.GetAt(irow));
	}
}

void CMainWnd::ResetVolumn(int irow, int ijumunvol)
{
	int ivol1 = CInt( m_pRemainGrid->GetItemText(irow, colVOL) );//잔고8
	int ivol2 = CInt( m_pRemainGrid->GetItemText(irow, colPOSSVOL));//가능9
	ivol1 -= ijumunvol; max(ivol1, 0);
	ivol2 -= ijumunvol;	max(ivol2, 0);

	m_pRemainGrid->SetItemText(irow, colVOL, CStr(ivol1) );
	m_pRemainGrid->SetItemText(irow, colPOSSVOL, CStr(ivol2) );
}

void CMainWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_List pList;
	int iw, itoggle, icol;

	bool bmatch = false;
	for(int i=0; i<m_arGridToggleList.GetSize(); i++)
	{
		pList = m_arGridToggleList.GetAt(i);
		if(pList.rect.PtInRect(point) )
		{
			iw = m_pRemainGrid->GetColumnWidth(pList.icol);
			icol = pList.itoggleIdx;
			itoggle = pList.icol;
			m_arGridHdrList[icol] = m_arGridHdrList[itoggle] = gridHdr[icol].szhdr; 

			m_pRemainGrid->SetColumnWidth(pList.itoggleIdx, iw);
			m_pRemainGrid->SetColumnWidth(pList.icol, 0);

			pList.itoggleIdx = itoggle;
			pList.icol = icol;
			
			m_arGridToggleList.SetAt(i, pList);
			bmatch = true;
			break;
		}
	}	

	if(bmatch)
	{
		InvalidateRect(pList.rect );
		m_pRemainGrid->Invalidate();
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

/***********************************************************************************
설정된 수량조건 확인
*************************************************************************************/
bool CMainWnd::CheckSetupVol(int irow)
{
	_config cfgval = m_arConfigList.GetAt(irow);
	int ivol = cfgval.ivol = 0;
	if(!cfgval.ivoltype )
		ivol = cfgval.ivol = int( atof(m_pRemainGrid->GetItemText(irow, colPOSSVOL) ) * ((double)cfgval.ivolval/100.0) );
	else  ivol = cfgval.ivol = cfgval.ivolval;

	int idiv = CInt(m_pRemainGrid->GetItemText(irow, colVolUNIT));//getAmountType(CInt(m_pRemainGrid->GetItemText(irow, colCDTYPE)), m_pRemainGrid->GetItemText(irow, colPCUR) );
	if(ivol < idiv) return false;

	int ipossvol = CInt(m_pRemainGrid->GetItemText(irow, colPOSSVOL)); //가능수량
	int ijvol = CInt(m_pRemainGrid->GetItemText(irow, colVolUNIT));//getAmountType(CInt(m_pRemainGrid->GetItemText(irow, colCDTYPE)), m_pRemainGrid->GetItemText(irow, colPCUR) );//수량주문단위
	if(ipossvol >= ijvol) return true;

	return false;
}

/***********************************************************************************
설정된 모든조건 확인
*************************************************************************************/
bool CMainWnd::IsvalidateSetupCase(int irow)
{
	CString schkval1 = Trim(m_pRemainGrid->GetItemText(irow, colLOSS));//손실목표
	CString schkval2 = Trim(m_pRemainGrid->GetItemText(irow, colMIT));//이익목표
	CString schkval3 = Trim(m_pRemainGrid->GetItemText(irow, colTS));//이익보존

	//OutputDebugString(schkval1+"\n");

	if( schkval1.IsEmpty() &&  schkval2.IsEmpty() && schkval3.IsEmpty() )
	{
		MessageBox("주문조건이 없습니다.", MAPTITLE, MB_ICONINFORMATION|MB_OK);
		return false;
	}

	if( !CheckSetupVol(irow))
	{
		MessageBox("설정하신 주문수량조건으로 주문이 불가합니다. \r\n주문수량조건을 확인하십시오.", MAPTITLE, MB_ICONINFORMATION|MB_OK);
		return false;
	}

	double iprice1 = atof(m_pRemainGrid->GetItemText(irow, colTSDIF));//고점대비하락액
	double iprice = atof(m_pRemainGrid->GetItemText(irow, colTS));//이익보존액

	CString s;
	s.Format("VALID CASE : [%.2f]	[%.2f]\n",iprice1,iprice);
	OutputDebugString(s);

	CString type = m_pRemainGrid->GetItemText(irow, colJANTYPE);

	_config cfgval = m_arConfigList.GetAt(irow);

	if(type.Find("매수") > -1)
	{
		if(iprice < iprice1)
		{
			MessageBox( "하락가격이 최고가설정액보다 작거나 같아야 합니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
			return false;
		}
	}
	else
	{
		if(cfgval.iunit[3] == 3)
		{
			if(iprice > iprice1)
			{
				MessageBox( "하락가격이 최고가설정액보다 크거나 같아야 합니다", MAPTITLE, MB_ICONINFORMATION|MB_OK);
				return false;
			}
		}
	}

	return true;
}

/***********************************************************************************
로그 저장 : 로컬및, 서버
*************************************************************************************/
void CMainWnd::WriteLog(CString sType, CString sLog, CString sCode, CString sItem, bool bsend)
{
	CFile pFile;

	if (pFile.Open(m_strLogPath, CFile::modeReadWrite | CFile::shareDenyRead))
	{
		DWORD	pos = (DWORD)pFile.SeekToEnd();
		pFile.Seek((long) pos, CFile::begin);
	}
	else
		pFile.Open(m_strLogPath, CFile::modeCreate|CFile::modeReadWrite);

	CString strDate, strTime;
	SYSTEMTIME	tm;
	GetLocalTime(&tm);
	strDate.Format("%04d%02d%02d", tm.wYear, tm.wMonth, tm.wDay);    
	strTime.Format("%02d%02d%02d", tm.wHour, tm.wMinute, tm.wSecond);    

	CString sWrite,sSendLog;
	sWrite.Format("%s%c%s%c%s%c%s%c%s%c%s%c", strDate,  tabCHAR, strTime, tabCHAR, sType, tabCHAR, sCode, tabCHAR, sItem, tabCHAR, sLog, newlineCHAR);
	sSendLog.Format("%s     %s     %s     %s     %s     %s%c", strDate, strTime, sType, sCode, sItem, sLog, newlineCHAR);
	pFile.Write(sWrite, sWrite.GetLength() );
	pFile.Close();

	CFile pNowFile;

	if(pNowFile.Open(m_strLogPath+".td", CFile::modeReadWrite | CFile::shareDenyWrite | CFile::shareDenyRead))
	{
		DWORD pos = (DWORD)pNowFile.SeekToEnd();
		pNowFile.Seek((long)pos, CFile::begin);
	}
	else
	{
		pNowFile.Open(m_strLogPath+".td", CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite | CFile::shareDenyRead);
	}

	pNowFile.Write(sSendLog,sSendLog.GetLength());
	pNowFile.Close();

	//m_nLogCount++;

	//if(bsend) SendLog(sWrite);  //test 서버에 로그 남기기
	if(bsend) 
		SendLog(sWrite);  //test 서버에 로그 남기기

	if(m_pLogDlg)
		m_pLogDlg->InsertLog(strDate, strTime, sType, GetCode(sCode), sItem, sLog);
}

/***********************************************************************************
로그 저장 : 서버
TR : pidologm
static  struct  mid {
    char    func[1];        /* 'Q' : 조회 'I' 입력  
	char    mapn[8];        /* 화면번호             
    char    kind[1];        /* 로그종류             
                            /* 화면별 세부구분      
    char    data[1];        /* 로그 데이타(MAX 1024)
}
*************************************************************************************/
void CMainWnd::SendLog(CString sData)
{
	CString strSend;
	strSend.Format("I%s1%s",  MAPNAME,sData);
	
	SendTransaction(LOGQUERY, strSend, US_OOP, LOGKEY);
}

void CMainWnd::SendLargeLog(int count,CString sData)
{
	CString strSend;
	strSend.Format("A%04d%s",count,sData);

	CString s;
// 	s.Format("3008 SEND LARGE LOG [%s]\n",strSend);
// 	OutputDebugString(s);
	
	SendTransaction(LOGQUERY, strSend, US_OOP, LOGKEY);
}

void CMainWnd::UploadLogData()
{
	CStdioFile pFile;
	if (!pFile.Open(m_strLogPath+".td", CFile::modeRead|CFile::shareDenyNone)) return;
	
	CString strResult,strRead, strTmp;
	
	strRead = "";
	strResult = "";

	int nCount = 0;		//2015.03.04

	m_nLogCount = 0;

	while(pFile.ReadString(strRead))
	{
		pidologm_mid mid;

		FillMemory(&mid,sizeof(pidologm_mid), ' ');
		//CopyMemory(&mid.func,"I",1);
		CopyMemory(&mid.mapn,MAPNAME,sizeof(mid.mapn));
		//CopyMemory(&mid.kind,"1",1);
		CopyMemory(&mid.data,strRead,strRead.GetLength());

		mid.func[0] = 'I';
		mid.kind[0] = '2';

		//strTmp.Format("I%s1%s",  MAPNAME,strRead);

		strTmp = CString((char*)&mid,sizeof(pidologm_mid));

		CString s;
// 		s.Format("3008 SEND LOG [%s]\n",strTmp);
// 		OutputDebugString(s);

		strResult += strTmp;

		m_nLogCount++;

		if(strlen(strResult) > 61440)
		{
			nCount++;

			SendLargeLog(m_nLogCount,strResult);
			
			m_nLogCount = 0;
			strResult = "";
		}
	}
	
	pFile.Close();

	if(nCount < 4)	SendLargeLog(m_nLogCount,strResult);	//2015.03.04 로그올리는 쵯수 제한

	::DeleteFile(m_strLogPath+".td");
}


LRESULT CMainWnd::OnMyPassword(WPARAM wParam, LPARAM lParam)
{
	//CString rcb = (char*)lParam;
	//MessageBox((char*)lParam);
	//CString tmp = (char*)lParam;
	//m_pPassEdit->SetWindowText(tmp);

	m_pPassEdit->SetText((char*)lParam);
	//m_pPassEdit->SetSelectFocus();
	m_pPassEdit->SetFocus();
	
	//MessageBox("Received: "+rcb);
	return 1;
}

bool CMainWnd::IsNumber(CString str)
{
    BOOL bRet = TRUE;
    int nLen = str.GetLength();
    for( int i=0 ; i < nLen ; ++i)
    {
        if( isdigit(str.GetAt(i)) == FALSE)
        {
            bRet = FALSE;
            break;
        }
    }
    return bRet;
}

void CMainWnd::ChangeFont(int ifontsize, CString sFont)
{
	if(m_iOldFont == ifontsize) return;

	double ldif = float(ifontsize - 9);
	int iWndWidth = MAP_WIDTH + (int)(m_lSizeRate[0] * (float)MAP_WIDTH * ldif);
	int iWndHeight = MAP_HEIGHT + (int)(m_lSizeRate[1] * (float)MAP_HEIGHT * ldif);

	m_pFont = getAxFont(sFont, ifontsize);
	
	m_iCurFont = ifontsize;
	m_bChangeFont = TRUE;
	SetWindowPos(NULL, 0, 0, iWndWidth, iWndHeight, SWP_NOZORDER | SWP_NOMOVE);
	SendAxisMessage(MAKEWPARAM(sizeDLL, 0), MAKELPARAM(iWndWidth, iWndHeight) );
}

void CMainWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GetClientRect(&m_pClientRect);
	CRect rc;
	if(!m_bInit) return;
	if(m_iOldSize[0] == 0 && m_iOldSize[1] == 0)
	{
		m_iOldSize[0] = cx ;
		m_iOldSize[1] = cy ;
	}

	if(m_iOldSize[0] == cx && m_iOldSize[1] == cy) return;

	CRect wrc;
	m_pRemainGrid->GetWindowRect(&wrc);
	ScreenToClient(&wrc);
	double lgridw = (double)(wrc.Width()) ;
	
	wrc.right = cx - 1;
	wrc.bottom = cy - m_iGuideHeight;
	m_pRemainGrid->MoveWindow(wrc);
	
	Resize(cx, cy);
//	ResizeGridColumnWidth();
//	ShowWindow(SW_HIDE);
}

void CMainWnd::ResizeGridColumnWidth()
{
	CRect wrc;
	m_pRemainGrid->GetWindowRect(&wrc);
	ScreenToClient(&wrc);

	int iw = 0;
	double lgridw = (double)(wrc.Width()-18);
	for (int ii = 0; ii < JCOLCOUNT; ii++)
	{
		if( m_pRemainGrid->GetColumnWidth(ii) <= 0) continue;

		iw = (int)(m_GridHdr[ii].lcolrate * lgridw);
		m_GridHdr[ii].width = iw;

		m_pRemainGrid->SetColumnWidth(ii, iw);
	}
}

void CMainWnd::Resize(int cx, int cy)
{
	if(m_pAccnNameRect.Width() <= 0) return;
	if(!m_pAccnCtrl) return;

	if(m_iOldSize[0] == cx && m_iOldSize[1] == cy) return;
	double lcalcrate[2] = {( (float)cx - (float)m_iOldSize[0] ) / (float)m_iOldSize[0], 
							( (float)cy - (float)m_iOldSize[1] ) /(float)m_iOldSize[1]};
	
	if(m_iCurFont == 9)
		lcalcrate[0] = lcalcrate[1] = 0.f;

	m_iOldSize[0] = cx ;
	m_iOldSize[1] = cy ;
	
	CRect wrc;
	int iw, ih, itop;
	int igap = GAP_WIDTH;
	iw = m_pToolLblRect[0].Width(), ih = m_pToolLblRect[0].Height() ;
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	ih = ih + (int)(lcalcrate[1] * (float)ih);
	if(m_iCurFont == 9) ih = CONTROL_HEIGHT;

	//계좌 텍스트
	m_pToolLblRect[0].right = m_pToolLblRect[0].left + iw;
	m_pToolLblRect[0].bottom = m_pToolLblRect[0].top + ih;
	itop = m_pToolLblRect[0].top;
	int ileft = m_pToolLblRect[0].right + igap;


	//계좌컨트롤
	m_pAccnCtrl->GetWindowRect( &wrc);
	ScreenToClient(&wrc);
//	ih = wrc.Height(); 
//	ih = ih + (int)(lcalcrate[1] * (float)ih);

	iw = wrc.Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	if(m_iCurFont == 9) iw = ACCOUNT_WIDTH;

	wrc.left = ileft;
	wrc.right = ileft + iw;
	wrc.top = itop;
	wrc.bottom = itop + ih;
	m_pAccnCtrl->MoveWindow(wrc); 
	m_pAccnCtrl->ChangeFont(m_iOldFont, _T("굴림"));

	//계좌명
	iw = m_pAccnNameRect.Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );

	ih = m_pAccnNameRect.Height() ;
	ih = ih + (int)(lcalcrate[1] * (float)ih);
	
	m_pAccnNameRect.left = wrc.right + igap;
	m_pAccnNameRect.right = m_pAccnNameRect.left + iw;
	m_pAccnNameRect.top = itop+1;
	m_pAccnNameRect.bottom = m_pAccnNameRect.top + ih;
	

	//비밀번호
	iw = m_pToolLblRect[1].Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	iw = max(50, iw);

	m_pToolLblRect[1].left = m_pAccnNameRect.right+igap;
	m_pToolLblRect[1].right = m_pToolLblRect[1].left + iw;

	//패스워드 입력에디티
	m_pPassEdit->GetWindowRect( &wrc);
	ScreenToClient(&wrc);
	iw = wrc.Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	wrc.left = m_pToolLblRect[1].right + igap;
	wrc.right = wrc.left + iw;
	wrc.bottom = wrc.top + ih;
	m_pPassEdit->MoveWindow(wrc); 
	m_pPassEdit->ChangeFont(m_pFont, m_iCurFont);
	

	ileft = wrc.right + igap;
	//주문확인창
	int iright = wrc.right + igap;
	m_pAutoBtn->GetWindowRect( &wrc);
	ScreenToClient(&wrc);
	iw = wrc.Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	

	wrc.left = ileft;
	wrc.right = wrc.left + iw;
	m_pAutoBtn->MoveWindow(wrc); 
	ileft = wrc.right + igap;
	
	iw = m_pToolLblRect[2].Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	iw = max(65, iw);
	m_pToolLblRect[2].left = ileft;
	m_pToolLblRect[2].right = ileft + iw;

	//반자동
	ileft = m_pToolLblRect[2].right + igap;
	iw = m_pToolLblRect[3].Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	iw = max(38, iw);

	m_pToolLblRect[3].left = ileft;
	m_pToolLblRect[3].right = ileft + iw;

	//버튼틀
	m_pToolBar[0]->GetWindowRect( &wrc);
	ScreenToClient(&wrc);

	iw = wrc.Width();
	iw = iw + (int)(lcalcrate[0] * (float)iw );
	ih = wrc.Height() ;
	ih = ih + (int)(lcalcrate[1] * (float)ih);

	if(m_iCurFont == 9) 
	{
		ih = CONTROL_HEIGHT;
		iw = BUTTON_WIDTH;
	}

	wrc.bottom = wrc.top  + ih;
//int ilefts = pRect.right -(BUTTON_WIDTH/*버튼하나너비*/ * ibtncount) - ( HORI_GAP* (ibtncount-1) ) - (HORI_GAP+HORI_GAP);
	int ibtngap = 3;
	ileft = cx - (iw * 7) - (ibtngap * 5) -(HORI_GAP+HORI_GAP) ;
	wrc.left = ileft;//m_pToolLblRect[3].right + igap;
	wrc.right = wrc.left + iw;

	for(int i=0; i<7; i++)
	{
		m_pToolBar[i]->MoveWindow(wrc); 
		m_pToolBar[i]->SetFont(m_pFont, TRUE);

		wrc.left = wrc.right + GAP_WIDTH_MIN;
		wrc.right = wrc.left + iw;
	}

	m_igridRowHeight = m_igridRowHeight  + (int)(lcalcrate[1] * (float)m_igridRowHeight);
	m_iToolheight = m_iToolheight + (int)(lcalcrate[1] * (float)m_iToolheight);
	if( m_pRemainGrid)
	{
		m_iGridHeadrHeight = m_iGridHeadrHeight + (int)(lcalcrate[1] * (float)m_iGridHeadrHeight);
		m_iGuideHeight = m_iGuideHeight + (int)(lcalcrate[1] * (float)m_iGuideHeight);

		itop = wrc.bottom + VERT_GAP + VERT_GAP + VERT_GAP;
		m_pRemainGrid->GetWindowRect(&wrc);
		ScreenToClient(&wrc);

		int ixgap = HORI_GAP + HORI_GAP;
		int iygap = VERT_GAP + BOT_GAP;
		wrc.right = cx - ixgap;

		wrc.left = ixgap;
		wrc.top = itop + m_iGridHeadrHeight;
		wrc.bottom = cy - m_iGuideHeight -iygap ;
		m_pRemainGrid->MoveWindow(wrc);

		for(int i=0; i<m_pRemainGrid->GetRowCount(); i++)
		{
			m_pRemainGrid->SetRowHeight(i, m_igridRowHeight);
		}
	}

	InvalidateRect(CRect(wrc.left, 0, wrc.right, m_iToolheight+m_iGridHeadrHeight  ));
	m_iOldFont = m_iCurFont;

}

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonDown(nFlags, point);
}


HBITMAP CMainWnd::CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor)
{
	HBITMAP		hMask		= NULL;
	CDC *pDC = GetDC(), maskDC, memDC;
	CBitmap maskBitmap, *pOldBmp, *oldmaskBitmap;
	maskDC.CreateCompatibleDC(pDC);
	maskBitmap.CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);
	oldmaskBitmap = maskDC.SelectObject(&maskBitmap);

	memDC.CreateCompatibleDC(pDC);
	memDC.FillSolidRect(0, 0, dwWidth, dwHeight, crTransColor);
	pOldBmp = memDC.SelectObject(CBitmap::FromHandle(hSourceBitmap));
	maskDC.BitBlt(0, 0, dwWidth, dwHeight, &memDC, 0, 0, SRCCOPY);
	maskDC.BitBlt(0, 0, dwWidth, dwHeight, &memDC, 0, 0, SRCAND);

	hMask = (HBITMAP)maskBitmap.Detach();
	maskDC.SelectObject(oldmaskBitmap);
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	maskDC.DeleteDC();
	ReleaseDC(pDC);
	return hMask;
}

void CMainWnd::DrawBitmap(CDC* pDC, CRect rc, HBITMAP hBitmap)
{
	HDC hDC = ::CreateCompatibleDC (NULL);
	SelectObject (hDC, hBitmap); //icon
//	::BitBlt( pDC->m_hDC, rc.left, rc.top, rc.Width(), rc.Height(),	hDC, 0, 0, SRCCOPY);
	::TransparentBlt(pDC->m_hDC, rc.left, rc.top, rc.Width(), rc.Height(), hDC, 0, 0, rc.Width(), rc.Height(), 0xFF00FF);
	::DeleteDC (hDC);

}

void CMainWnd::DrawCornerRoundBitmap(CDC* pDC, CRect rc)
{
	int iPoint = 5;
	
	DrawBitmap(pDC, CRect(rc.left, rc.top, rc.left+iPoint, rc.top +iPoint), m_hRoundBitmap[0]);
	DrawBitmap(pDC, CRect(rc.right-iPoint, rc.top, rc.right, rc.top +iPoint), m_hRoundBitmap[1]);
	DrawBitmap(pDC, CRect(rc.left, rc.bottom-iPoint, rc.left+iPoint, rc.bottom), m_hRoundBitmap[2]);
	DrawBitmap(pDC, CRect(rc.right-iPoint, rc.bottom-iPoint, rc.right, rc.bottom), m_hRoundBitmap[3]);
}


void CMainWnd::CheckPassWord(CString sAcc, CString sPass) 
{
	CString sTRCode = _T("SACMQ901");
	sTRCode = _T("SACMT238");
	/*
	CString sUser = (char*)m_pWizard->SendMessage(WM_USER, MAKEWPARAM(variantDLL, userCC), NULL);
	struct	_ledgerH ledger;
	FillMemory(&ledger, L_ledgerH, ' ');
	m_pWizard->SendMessage(WM_USER, ledgerDLL, (LPARAM)&ledger);

//	CopyMemory(&ledger.size, "000374", sizeof(ledger.size));
	CopyMemory(&ledger.svcd, sTRCode, sizeof(ledger.svcd));
	CopyMemory(&ledger.usid, (LPCTSTR)sUser, sUser.GetLength());
	CopyMemory(&ledger.brno, sAcc.Left(3), 3);
	CopyMemory(&ledger.rcnt, _T("0000"), sizeof(ledger.rcnt));

	ledger.fkey[0] = 'C';
	ledger.mkty[0] = '1';
	ledger.odrf[0] = '1';
	*/
//00

	CString sLedger = GetLedger(sTRCode, sAcc, '1', "", 10, GetEncPassword(sPass));	//2013.12.23 KSJ 일방향암호화 추가
	//sAcc = sAcc.Left(3) + "00" +  sAcc.Mid(5, 6);  //종합잔고로 변경
	for(int i=sAcc.GetLength() ; i<20;i++) sAcc += _T(" ");
	
	sPass = "HEAD";	//2013.12.23 KSJ 일방향암호화 추가
	for(int i=sPass.GetLength() ; i<8;i++) sPass += _T(" ");
	CString sChkPass = _T("00001");
	sChkPass += sAcc;
	sChkPass += sPass;
	//sChkPass += _T("1");

	CString strSendData = sLedger;
	strSendData += sChkPass;

	CString sTmp;
	sTmp.Format("[%d]%s",  strSendData.GetLength(), strSendData);

	SendTransaction(_T("piboPBxQ"), strSendData, 0, PASSKEY);
//	SendTR(_T("piboPBxQ"), strSendData, KEY_CHKPASSWORD, 0);
}

CString CMainWnd::GetEncPassword(CString sPswd)
{
	CString dllPath;
	dllPath.Format(_T("%s%s"), m_strRootDir, _T("\\dev\\CX_SHA256.DLL"));
	CString strRetrun;
	
	if(m_hiSha256 == NULL)
	{
		m_hiSha256 = LoadLibrary(dllPath);
		
		if (!m_hiSha256)
		{
			TRACE("CX_SHA256 컨트롤 생성 실패1");
			return "";
		}
	}
	
	if(m_hiSha256)
	{
		typedef long (WINAPI *GETSHAFUNC)(char*, int);	
		GETSHAFUNC func = (GETSHAFUNC)GetProcAddress(m_hiSha256, "axEncrypt");
		
		if (func)
		{
			strRetrun =  (char*)func(sPswd.GetBuffer(sPswd.GetLength()),sPswd.GetLength());
		}
	}	
	return strRetrun;
}