#if !defined(AFX_PNINPUT_H__F7BA824E_3459_4B6D_838E_573E16FB32EB__INCLUDED_)
#define AFX_PNINPUT_H__F7BA824E_3459_4B6D_838E_573E16FB32EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PnInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPnInput window
#include "PnBaseWnd.h"

class CPnInput : public CPnBaseWnd
{
// Construction
public:
	CPnInput(CWnd *pView, CWnd* pParent, CFont* pFont, int ctrlID, char* info);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPnInput)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPnInput();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPnInput)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT	OnInputEvent(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseLeave(UINT nFlags, CPoint point);
	afx_msg void OnClickedSelect();
	DECLARE_MESSAGE_MAP()

private:
	CAxisGMTotalApp		*m_pApp;
	class CMainWnd		*m_pMainWnd;
	CString				m_outSymbol;
	int			m_gap[4];
	bool			m_bInitResize;
	bool			m_bLButton;
	int			m_selID;

	CImageList		*m_pNTimeImage;
	CImageList		*m_pIOptImage;

	class CCheckBox*	m_pchbSelect;
	class CPnWndCombo	*m_pGapCB;
	class CPnToolTip	*m_pToolTip;

	CFont			*m_pBtnFont;
	COLORREF		m_clrFrame;
	COLORREF		m_clrUpSise;
	COLORREF		m_clrDnSise;
	COLORREF		m_clrEqSise;

	CSize			m_szNumeric;
	CSize			m_szHangul;
	BOOL			m_bMouseIN;

	CRect			m_rcSise;
	CRect			m_rcDAY;
	CRect			m_rcIndex;

private:
	
	void	OnDraw(CDC *pDC);
	COLORREF parseSymbol(char sign);
	CString editComma(double dVal, bool bCode);
	void	DrawButton(CDC* pDC, struct _comp* comp);

	void	SetInfo(CRect wRC);
	void	arrangeCtrl(CRect wRC, bool bChgIndex = true);
	int	GetTRInfo(char *pHeader);
	int	GetTRInfo2(char *pHeader);
	void	MakeInputSymbol();
	void	ReadDisplay(int index);
	void	ChangeIndex(int index, bool bChgGap = true, bool bRedraw = true, bool bMessage = true);
	void	ChangeGap(int index, int gap, bool bOnlyChange = false);
	void	NotifyIndexChange(int index);
	void	SetGapValue(char *pGap);
	void	lbuttonup(CPoint point);
	void	TrackingIndexMenu(CPoint pt);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PNINPUT_H__F7BA824E_3459_4B6D_838E_573E16FB32EB__INCLUDED_)
