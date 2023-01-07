#if !defined(AFX_RSCINFO_H__B1CC4D1B_1044_4391_8876_99A68A0A9816__INCLUDED_)
#define AFX_RSCINFO_H__B1CC4D1B_1044_4391_8876_99A68A0A9816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSCinfo.h : header file
//

#include "../dll/ctrl/ExListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CRSCinfo dialog

class CRSCinfo : public CDialog
{
// Construction
public:
	CRSCinfo(CString home, CWnd* pParent = NULL);   // standard constructor
	~CRSCinfo();

// Dialog Data
	//{{AFX_DATA(CRSCinfo)
	enum { IDD = IDC_INFOLIST };
	CExListCtrl	m_list;
	//}}AFX_DATA

	CString		m_home;
	CStringArray	m_arFolder;
	CStringArray	m_arDelRsc;
	CStringArray	m_arDelAxis;

	int		m_sRes;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCinfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	initList();
	void	loadInfo(int selectN = 0);
	BOOL	addColumn(CListCtrl& list, LPCTSTR columns, int col, int width = 0);
	BOOL	addItem(CListCtrl& list, CString items, int item, int subi = 0);
	void	fit();
	void	delRsc();
	void	UpdateInfo(bool rsc = true);
	// Generated message map functions
	//{{AFX_MSG(CRSCinfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSCINFO_H__B1CC4D1B_1044_4391_8876_99A68A0A9816__INCLUDED_)
