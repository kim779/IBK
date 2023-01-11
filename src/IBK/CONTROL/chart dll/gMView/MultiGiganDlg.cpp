// MultiGiganDlg.cpp : implementation file
//

#include "stdafx.h"
#include "axisgmview.h"
#include "MultiGiganDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiGiganDlg dialog


CMultiGiganDlg::CMultiGiganDlg(struct _MultiChart *pMultiChart, CWnd* pParent /*=NULL*/)
	: CDialog(CMultiGiganDlg::IDD, pParent)
{
	m_pMultiChart = pMultiChart;
	//{{AFX_DATA_INIT(CMultiGiganDlg)
	//}}AFX_DATA_INIT
}


void CMultiGiganDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiGiganDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctrlDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiGiganDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiGiganDlg)
	ON_BN_CLICKED(IDINIT, OnInit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiGiganDlg message handlers

BOOL CMultiGiganDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString	sGigan;
	int	pID[5] = {IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5};
	for (int ii = 0; ii < 5; ii++)
	{
		CWnd	*pWnd = GetDlgItem(pID[ii]);
		sGigan.Format("%d", m_pMultiChart->acGigan[ii]);
		pWnd->SetWindowText(sGigan);
	}

	m_ctrlDay.SetFocus();
	m_ctrlDay.SetSel(0, -1);

	return false;
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMultiGiganDlg::OnOK() 
{
	CString	sGigan;
	int	pID[5] = {IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5};
	for (int ii = 0; ii < 5; ii++)
	{
		CWnd	*pWnd = GetDlgItem(pID[ii]);
		pWnd->GetWindowText(sGigan);

		if (sGigan.IsEmpty() || atoi(sGigan) <= 0)
		{
			pWnd->SetFocus();
			((CEdit*)pWnd)->SetSel(0, -1);
			return;
		}
		if (atoi(sGigan) > MAX_DATA_COUNT)
		{
			sGigan.Format("멀티차트에서 최대 기간은 %d개 입니다.", MAX_DATA_COUNT);
			CAxisGMViewApp	*pApp = (CAxisGMViewApp*)AfxGetApp();
			pApp->MessageBox(sGigan, COMPANYNAME);
			pWnd->SetFocus();
			((CEdit*)pWnd)->SetSel(0, -1);
			return;
		}
	}

	for (ii = 0; ii < 5; ii++)
	{
		CWnd	*pWnd = GetDlgItem(pID[ii]);
		pWnd->GetWindowText(sGigan);
		m_pMultiChart->acGigan[ii] = atoi(sGigan);
	}

	CDialog::OnOK();
}

void CMultiGiganDlg::OnInit() 
{
	CString	sGigan;
	int	pGigan[5] = {300, 200, 100, 400, 400};
	int	pID[5] = {IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5};
	for (int ii = 0; ii < 5; ii++)
	{
		CWnd	*pWnd = GetDlgItem(pID[ii]);
		sGigan.Format("%d", pGigan[ii]);
		pWnd->SetWindowText(sGigan);
	}
}
