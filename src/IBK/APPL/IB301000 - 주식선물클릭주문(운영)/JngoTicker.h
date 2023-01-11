#pragma once

#include "Common.h"
#include "AxisExt.h"
#include "grid/GridCtrl.h"

class CJngoTicker : public CGridCtrl, public CAxisExt
{
// Construction
public:
	CJngoTicker(CWnd *pParent);

public:
	BOOL Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE , DWORD dwExStyle = 0);
	void ChangeTheme();
	void Clear();
protected:
	void SetGrid();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJngoTicker)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJngoTicker();

	// Generated message map functions
protected:
	//{{AFX_MSG(CJngoTicker)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnRefresh( WPARAM wParam, LPARAM lParam );
};

