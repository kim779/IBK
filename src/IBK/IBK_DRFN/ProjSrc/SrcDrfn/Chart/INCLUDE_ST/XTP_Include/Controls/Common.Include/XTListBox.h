// XTListBox.h interface for the CXTListBox class.
//
// This file is a part of the XTREME CONTROLS MFC class library.
// (c)1998-2009 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTLISTBOX_H__)
#define __XTLISTBOX_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum XTListBoxStyle
{
	xtListBoxStandard,
	xtListBoxOfficeXP,
	xtListBoxOffice2007,
};

//===========================================================================
// Summary:
//     CXTListBox is a CListBox derived class. CXTListBox extends the standard
//     list box control to enable flicker free drawing.
//===========================================================================
class _XTP_EXT_CLASS CXTListBox : public CListBox
{
	DECLARE_DYNAMIC(CXTListBox)

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTListBox object
	//-----------------------------------------------------------------------
	CXTListBox();

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTListBox object, handles cleanup and deallocation
	//-----------------------------------------------------------------------
	virtual ~CXTListBox();

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to initialize the list box.  This method
	//     should be called directly after creating or sub-classing the control.
	// Parameters:
	//     bAutoFont - True to enable automatic font initialization.
	//-----------------------------------------------------------------------
	virtual void Initialize(bool bAutoFont = true);

	//-----------------------------------------------------------------------
	// Summary:
	//     This method is called to get background color of listbox
	//-----------------------------------------------------------------------
	virtual COLORREF GetBackColor();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this method to set list style
	// Input:
	//     style - XTListBoxStyle  style of the ListBox (xtListBoxStandard, xtListBoxOfficeXP, xtListBoxOffice2007)
	// See Also: XTListBoxStyle, GetListStyle
	//-----------------------------------------------------------------------
	void SetListStyle(XTListBoxStyle style);

	//-----------------------------------------------------------------------
	// Summary: Call this method to get style of the ListBox
	// Returns: XTListBoxStyle value contains style of listbox
	// See Also: XTListBoxStyle, SetListStyle
	//-----------------------------------------------------------------------
	XTListBoxStyle GetListStyle() const;

protected:

//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	bool m_bPreSubclassInit;

	//{{AFX_VIRTUAL(CXTListBox)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual bool Init();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTListBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnPrintClient(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE

protected:
	XTListBoxStyle m_nStyle;    // Listbox style.
	int m_nItemHeight;          // Height of the items.
	int m_nTextPadding;         // Text padding.
	int m_nHotItem;             // Hot item index.
};

AFX_INLINE void CXTListBox::SetListStyle(XTListBoxStyle style) {
	m_nStyle = style;
	if (m_hWnd) Invalidate(FALSE);
}
AFX_INLINE XTListBoxStyle CXTListBox::GetListStyle() const {
	return m_nStyle;
}


#endif // #if !defined(__XTLISTBOX_H__)
