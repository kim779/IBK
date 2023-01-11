#if !defined(AFX_MULTIGIGANDLG_H__0EC25500_7DD0_42EB_BFE1_03F887F6C03D__INCLUDED_)
#define AFX_MULTIGIGANDLG_H__0EC25500_7DD0_42EB_BFE1_03F887F6C03D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiGiganDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiGiganDlg dialog

class CMultiGiganDlg : public CDialog
{
// Construction
public:
	CMultiGiganDlg(struct _MultiChart *pMultiChart, CWnd* pParent = NULL);   // standard constructor

	struct _MultiChart	*m_pMultiChart;
// Dialog Data
	//{{AFX_DATA(CMultiGiganDlg)
	enum { IDD = IDD_MGIGAN };
	CEdit	m_ctrlDay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiGiganDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMultiGiganDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnInit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIGIGANDLG_H__0EC25500_7DD0_42EB_BFE1_03F887F6C03D__INCLUDED_)
