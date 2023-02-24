// DlgSTExOption.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgSTExOption.h"
#include "TabSystemTradingEx.h"
#include "StdDialog.h"

// CDlgSTExOption 대화 상자입니다.

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// IMPLEMENT_DYNAMIC(CDlgSTExOption, CDialog)
CDlgSTExOption::CDlgSTExOption(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSTExOption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSTExOption)
	//}}AFX_DATA_INIT

	m_pWndTrader = NULL;
	m_hTradeInst = NULL;
	m_bIsApplyBtn = FALSE;
	m_pDlgAnalysis = NULL;
}

CDlgSTExOption::~CDlgSTExOption()
{
}

void CDlgSTExOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSTExOption)
	DDX_Control(pDX, IDC_COMBO_REP, m_CtlComboRep);
	DDX_Control(pDX, IDC_COMBO_DIV, m_CtlComboDiv);
	DDX_Control(pDX, IDC_LIST_DAY, m_CtlList);
	DDX_Control(pDX, IDC_STAPPLY, m_BtnSTApply);
	DDX_Control(pDX, IDC_STSHOWOPTION, m_BtnOption);
	DDX_Control(pDX, IDC_STREPORT, m_BtnSTReport);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CDlgSTExOption, CDialog)
	//{{AFX_MSG_MAP(CDlgSTExOption)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_STREPORT, OnBnClickedStreport)
	ON_BN_CLICKED(IDC_STSHOWOPTION, OnBnClickedStshowoption)
	ON_COMMAND(IDC_STAPPLY, OnBnClickedStapply)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgSTExOption 메시지 처리기입니다.

BOOL CDlgSTExOption::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitColumn(&m_CtlList);

	// 리소스 수정 후 셋팅이 안되는 경우가 있어서..
	if(m_CtlComboDiv.GetCount()==0)
	{
		CString szKey;
		int i;
		for(i=1; i<=10; i++)
		{
			szKey.Format("%02d", i);
			m_CtlComboDiv.AddString(szKey);
		}
	}
	if(m_CtlComboRep.GetCount()==0)
	{
		m_CtlComboRep.AddString("0"),
		m_CtlComboRep.AddString("10%"),
		m_CtlComboRep.AddString("20%"),
		m_CtlComboRep.AddString("30%"),
		m_CtlComboRep.AddString("40%"),
		m_CtlComboRep.AddString("50%");
	}

	m_CtlComboDiv.SetCurSel(0);
	m_CtlComboRep.SetCurSel(0);

	CTabSystemTradingEx* pParentDlg = (CTabSystemTradingEx*)GetParent();

	m_BtnSTApply.FP_vSetImage( pParentDlg->m_pIL_W58H20, 0, 2, TRUE, "적용", FALSE);//KHD : 2006.11.16
	m_BtnSTApply.FP_vSetToolTipText("적용");
	//m_BtnOption.FP_vSetImage( pParentDlg->m_pIL_W20H20, 44, 46);KHD :사용 안함

	m_BtnSTReport.FP_vSetImage(pParentDlg->m_pIL_W58H20, 0, 2, TRUE, "보고서", FALSE);
	m_BtnSTReport.FP_vSetToolTipText("보고서");

	m_CtlList.GetWindowRect(m_rcList);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// 분할수
int CDlgSTExOption::GetDivCount()
{
	int nTmp = 0;
	int nSel = m_CtlComboDiv.GetCurSel();
	if(nSel<0) return nTmp;


	CString szTmp;
	m_CtlComboDiv.GetLBText(nSel, szTmp);

	nTmp = atoi(szTmp);
	return nTmp;
}

// 중첩율
double CDlgSTExOption::GetRepRate()
{
	int nSel = m_CtlComboRep.GetCurSel();
	if(nSel<0) return 0.0f;

	CString szTmp;
	m_CtlComboRep.GetLBText(nSel, szTmp);

	double rTmp = 0.00f;
	rTmp = atof(szTmp);
	return rTmp;
}

void CDlgSTExOption::OnBnClickedStshowoption()
{
	CTabSystemTradingEx* pParentDlg = (CTabSystemTradingEx*)GetParent();
	pParentDlg->HideStOptimaA();
}


#include ".\dlldlg.h"
#include ".\dlgstexoption.h"

// 성과분석 로딩...
void CDlgSTExOption::OpenRefort()
{
	OnBnClickedStreport();
}
void CDlgSTExOption::OnBnClickedStreport()
{
	CTabSystemTradingEx* pParentDlg = (CTabSystemTradingEx*)GetParent();

	if(pParentDlg->m_xSTAnalysisInput.m_InfoForAnalysis.szSTRData.CompareNoCase("사용자지표")==0 ||
		pParentDlg->m_xSTAnalysisInput.m_InfoForAnalysis.szSTRData.Find("강세약세")>=0)
	{
		AfxMessageBox("강세약세는 성과분석이 불가합니다.");
		return;
	}

	if(pParentDlg->m_xSTAnalysisInput.GetCount()==0)
	{
		AfxMessageBox("종목조회 후 가능합니다.");
		return;
	}

	if(pParentDlg->CanSTModule()==FALSE)	return;

	BOOL bSel = pParentDlg->IsSTSelected();
	if(!bSel)
	{
		AfxMessageBox("적용할 전략을 선택해주시기 바랍니다");
		return;
	}

	// 성과보고실행전에 TeeChart및 MSChart등록을 확인한다.
	if(!pParentDlg->CheckOcx())
	{
		AfxMessageBox("최적화에서 필요한 OCX(TeeChart7.ocx, MSChrt20.ocx)등록이 안되어있습니다.");
		return;
	}

	CChartItem* pCItem = ((CChartMng*)pParentDlg->m_pChartMng)->GetpChartItemSelected();
	if(pCItem)
	{
		// 현재 실행중인 전략명 얻어오기
		CString strSTPath;
		pCItem->InvokeAddInSTIndex("ChartSTIndexAddIn.dll", 8, (long)&strSTPath);
		if(strSTPath.GetLength() && strSTPath.Find(".ST") > 0)
		{
			CString strMsg("성과분석은 현재 운용중인 전략을 해제하여야 적용이 가능합니다.\n\n전략을 해제하시겠습니까?");
			if(IDYES == AfxMessageBox(strMsg, MB_YESNO))
			{
				pParentDlg->STClear();
			}
			else	// IDNO
			{
				return;
			}
		}
	}

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hOld = AfxGetResourceHandle();
	AfxSetResourceHandle(g_hInstance);

	CString szDllName;
	szDllName.Format("%s%s", pParentDlg->m_szRootDir, "\\Dev\\HWStrategyAnalysis");	// DLL명만 넣는다.
//	CDllDlg dlg(szDllName, "성과보고서", &pParentDlg->m_xSTInterface, NULL,this);	
//	dlg.m_strImageDir = pParentDlg->m_pParentDlg->m_szImageDir;
//	dlg.DoModal();

	if(m_pDlgAnalysis)
	{
		m_pDlgAnalysis->DestroyWindow();
		delete m_pDlgAnalysis;
		m_pDlgAnalysis = NULL;
	}
	m_pDlgAnalysis = new CDllDlg(szDllName, "성과보고서", &pParentDlg->m_xSTInterface, hOld,this);
	m_pDlgAnalysis->m_strImageDir = pParentDlg->m_pParentDlg->m_szImageDir;
	if(m_pDlgAnalysis)
	{
		if(!m_pDlgAnalysis->Create(CDllDlg::IDD))
		{
			AfxSetResourceHandle(hOld);
			return;
		}
		
		CRect rcChart;
		CChartMng* pChartMng = (CChartMng*)pParentDlg->m_pChartMng;
		if(pChartMng)
			pChartMng->GetWindowRect(&rcChart);
		
		m_pDlgAnalysis->SetWindowPos(NULL, rcChart.left, rcChart.top,0,0, SWP_NOSIZE);
		m_pDlgAnalysis->ShowWindow(SW_SHOW);
	}
	//<< KB투자증권 ISSUE#152 - vntsorl(20100305)
	
	AfxSetResourceHandle(hOld);


}


// ---------------------------------------------------------------------------------
// void CDlgSTExOption::OnBnClickedStapply()
// 성과분석을 로드하고 성과분석에서 차트에 분할을 적용하도록 호출합니다.
// Start : 06.07.28 alzio
// ---------------------------------------------------------------------------------
// 성과분석에 있는 루틴을 콜하는 루틴이다. 전략설정창에서 전략적용을 콜할 때 불리는 부분이다.
// 이 부분을 콜하는 루틴은 ChartSTIndexAddin에서 전략을 실행하는 루틴으로 변경하면서
// 이제는 사용하지 않는다. 06.09.25
typedef	CWnd* (FPSA_ApplyChart)(LONG dwChartOcx, CListCtrl* pDivList, LONG dwInfo, LONG dwReserved1, LONG dwReserved2);
void CDlgSTExOption::OnBnClickedStapply()
{
	CTabSystemTradingEx* pParentDlg = (CTabSystemTradingEx*)GetParent();
	if(pParentDlg->m_xSTAnalysisInput.m_InfoForAnalysis.szSTRData.CompareNoCase("사용자지표")==0 ||
		pParentDlg->m_xSTAnalysisInput.m_InfoForAnalysis.szSTRData.Find("강세약세")>=0)
	{
		AfxMessageBox("사용자지표,사용자강세약세는 성과분석이 불가합니다.");
		return;
	}

	if(pParentDlg->m_xSTAnalysisInput.GetCount()==0)
	{
		AfxMessageBox("종목조회 후 가능합니다.");
		return;
	}
	//KHD 
	BOOL bSel = pParentDlg->IsSTSelected();
	if(!bSel)
	{
		AfxMessageBox("적용할 전략을 선택해주시기 바랍니다");
		return;
	}
	//END 

	if(pParentDlg->CanSTModule()==FALSE) return;

	CChartItem* pCItem = ((CChartMng*)pParentDlg->m_pChartMng)->GetpChartItemSelected();
	if(pCItem)
	{
		// 현재 실행중인 전략명 얻어오기
		CString strSTPath;
		pCItem->InvokeAddInSTIndex("ChartSTIndexAddIn.dll", 8, (long)&strSTPath);
		
		if(strSTPath.GetLength() && strSTPath.Find(".ST") > 0)
		{
			CString strMsg("성과분석은 현재 운용중인 전략을 해제하여야 적용이 가능합니다.\n\n전략을 해제하시겠습니까?");
			if(IDYES == AfxMessageBox(strMsg, MB_YESNO))
			{
				pParentDlg->STClear();
			}
			else	// IDNO
			{
				return;
			}
		}
	
	}

	m_bIsApplyBtn = TRUE;
	LPCSTR strTradingName = "HWStrategyAnalysis.dll";
	CString szDllName;
	szDllName.Format("%s%s", pParentDlg->m_szRootDir, "\\Dev\\HWStrategyAnalysis");	// DLL명만 넣는다.

	if(m_hTradeInst!=NULL)
	{
		FreeLibrary(m_hTradeInst);
		m_hTradeInst = NULL;
	}
	m_hTradeInst = LoadLibrary(szDllName);
	if(m_hTradeInst == NULL)
	{
		#ifdef _DEBUG
			CString strError;
			strError.Format(_T("%s File Load Faile"),strTradingName);
			MessageBox(strError);
		#endif
		
	}

	FPSA_ApplyChart* pFunc = (FPSA_ApplyChart*)GetProcAddress(m_hTradeInst,_T("SA_ApplyChart"));
	if(pFunc == NULL)
	{
		#ifdef _DEBUG
			CString strError;
			strError.Format(_T("%s[%s] Load Error!"), strTradingName, "SA_ApplyChart");
			MessageBox(strError);
		#endif
		return ;
	}

	LONG pChartOcx = (LONG)pCItem;
	LONG dwReserved1 = 0, dwReserved2 = 0;

	//if(!m_pWndTrader) :KHD : 중첩률 적용시 한 번 밖에 적용 안되서 주석처리..
		m_pWndTrader = pFunc(pChartOcx, &m_CtlList, (LONG)&pParentDlg->m_xSTAnalysisInput.m_InfoForAnalysis, (LONG)&pParentDlg->m_xSTInterface, dwReserved2);
//	FreeLibrary(hTradeInst);
}


//Dlg 전체초기화 : by KHD : 2007.01.26
void CDlgSTExOption::SetInitDlg()
{
	m_bIsApplyBtn = FALSE;
	m_CtlList.DeleteAllItems();
	m_CtlComboDiv.SetCurSel(0);
	m_CtlComboRep.SetCurSel(0);
}


// ---------------------------------------------------------------------------------
// void CDlgSTExOption::InitColumn(CListCtrl* pListCtrl)
// 리스트컨트롤을 초기화하는 루틴입니다. OnInitDialog에서 호출합니다.
// Start : 06.07.28 alzio
// ---------------------------------------------------------------------------------
void CDlgSTExOption::InitColumn(CXListCtrl* pListCtrl)
{
	int colwidthsType0[3] = { 14, 70, 70};	// KHD : 스킨적용 sixty-fourths

	TCHAR *	lpszHeadersType0[] = { _T(" "), _T("시작"), _T("끝"),NULL };
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int total_cx = 0;
	LV_COLUMN lvcolumn;
	memset(&lvcolumn, 0, sizeof(lvcolumn));
	// add columns
	for (int i = 0; ; i++)
	{
		if (lpszHeadersType0[i] == NULL)
			break;
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = lpszHeadersType0[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = colwidthsType0[i];
		total_cx += lvcolumn.cx;
		pListCtrl->InsertColumn(i, &lvcolumn);
	}
}

HBRUSH CDlgSTExOption::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	switch(nCtlColor) 
	{
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
		return hbr;
	default:
		{
			CTabSystemTradingEx* pParentDlg = (CTabSystemTradingEx*)GetParent();
			pDC->SetBkColor(pParentDlg->GetBkColor());
			return pParentDlg->GetBkColorBrush();
		}		
		break;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDlgSTExOption::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(m_CtlList.GetSafeHwnd())
	{		
		m_CtlList.SetWindowPos(NULL, 0, 0, cx, m_rcList.Height(), SWP_NOACTIVATE|SWP_NOMOVE);
	}
}

typedef	void (FPSA_Delete)(CWnd *pWnd);
void CDlgSTExOption::OnDestroy()
{
	CDialog::OnDestroy();

	if(m_pDlgAnalysis)
	{
		m_pDlgAnalysis->DestroyWindow();
		delete m_pDlgAnalysis;
		m_pDlgAnalysis = NULL;
	}

	if(m_hTradeInst!=NULL)
	{
		if(m_pWndTrader)
		{
			FPSA_Delete* pDeleteFunc = (FPSA_Delete*)GetProcAddress(m_hTradeInst,_T("DESTROY_TRADING"));
			pDeleteFunc(m_pWndTrader);
		}
		FreeLibrary(m_hTradeInst);
	}
	//if(m_pWndTrader)
	//{
	//	LPCSTR strTradingName = "HWStrategyAnalysis.dll";

	//	HINSTANCE hTradeInst = LoadLibrary(strTradingName);

	//	FPSA_Delete* pDeleteFunc = (FPSA_Delete*)GetProcAddress(hTradeInst,_T("DESTROY_TRADING"));
	//	pDeleteFunc(m_pWndTrader);
	//	FreeLibrary(hTradeInst);
	//}
	m_CtlList.DeleteAllItems();
}
