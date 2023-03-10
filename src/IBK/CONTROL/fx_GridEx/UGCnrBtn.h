/*************************************************************************
				Class Declaration : CUGnrBtn
**************************************************************************
	Source file : UGCnrBtn.cpp
	Header file : UGCnrBtn.h
	Copyright Dundas Software Ltd. 1994 - 2002, All Rights Reserved

	Class
		CUGnrBtn
	Purpose
		The Ultimate Grid draws the corner button
		(CUGnrBtn) object in the area that neither
		top heading nor the side heading should be,
		this is normally on the top left.

		This class is a special kind of a grid's
		headings, its size is controled by the height
		of the top heading and the width of the side
		heading.

		Cells displayed on the corner button have
		coordinates with negative values for both
		the column and row numbers.

*************************************************************************/
#pragma once

class AFX_CLASS_EXPORT CUGCnrBtn : public CWnd
{
	// Construction
public:
	CUGCnrBtn();

	// Attributes
public:

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CUGCnrBtn)
protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGCnrBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGCnrBtn)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL ToolTipNeedText(UINT id, NMHDR* pTTTStruct, LRESULT* pResult);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

public:


	// internal information
	friend CUGCtrl;
	CUGCtrl* m_ctrl{};	//pointer to the main class
	CUGGridInfo* m_GI{};		//pointer to the grid information

	int				m_isSizing{};		//sizing flag
	int				m_canSize{};		//sizing flag
	int				m_sizingHeight{};	//sizing flag
	int				m_sizingWidth{};	//sizing flag

	//internal functions
	void Update();
	void Moved();
};

