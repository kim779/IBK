/*************************************************************************
				Class Declaration : CUGHScroll
**************************************************************************
	Source file : ughscrol.cpp
	Header file : ughscrol.h
	Copyright ? Dundas Software Ltd. 1994 - 2002, All Rights Reserved

	This class is grid's horizontal scrollbar.

*************************************************************************/
#pragma once


class UG_CLASS_DECL CUGHScroll : public CScrollBar
{
// Construction
public:
	CUGHScroll();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGHScroll)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGHScroll();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGHScroll)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


protected:

	friend CUGCtrl;
	CUGCtrl* m_ctrl{};		//pointer to the main class
	CUGGridInfo* m_GI{};			//pointer to the grid information

	int	m_lastMaxLeftCol{};
	int m_lastNumLockCols{};

	int m_trackColPos{};

public:

	//internal functions
	void Update();
	void Moved();

	void HScroll(UINT nSBCode, UINT nPos);
};



