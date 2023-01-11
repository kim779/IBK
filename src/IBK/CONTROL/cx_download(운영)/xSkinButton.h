#pragma once
// CxSkinButton.h : header file
/** 15/03/2001 v1.00
 * ing.davide.pizzolato@libero.it
 ** 29/03/2001 v1.10
 * Milan.Gardian@LEIBINGER.com
 * - mouse tracking
 ** 02/04/2001 v1.20
 * ing.davide.pizzolato@libero.it
 * - new CreateRgnFromBitmap
 ** 14/04/2001 v1.21
 * - OnMouseLeave cast fixed
 * - Over bitmap consistency check
 ** 25/04/2001 v1.30
 * Fable@aramszu.net
 * - ExtCreateRegion replacement
 ** 24/06/2001 v1.40
 * - check & radio button add on
 * - added "focus" bitmap
 * - fixed CreateRgnFromBitmap bug
 * - fixed shortcut bug
 ** 27/10/2001 v1.41
 * - fixed memory leakage in CreateRgnFromBitmap
 */

#define WM_CXSHADE_RADIO WM_USER+0x100
/////////////////////////////////////////////////////////////////////////////
// CxSkinButton window
class CxSkinButton : public CButton
{
// Construction
public:
	CxSkinButton();

// Attributes
private:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxSkinButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
public:
	void SetToolTipText(CString s);
	COLORREF SetTextColor(COLORREF new_color);
	void SetSkin(CString normal,CString down,CString over,UINT type=1,
				short drawmode=1,short border=0,short margin=0);
	

	virtual ~CxSkinButton();
	// Generated message map functions
protected:
	int	m_nType;
	bool	m_Checked;			//radio & check buttons
	DWORD	m_Style;			//radio & check buttons
	bool	m_tracking;
	bool	m_button_down;
	CToolTipCtrl m_tooltip;
	CBitmap m_bNormal, m_bDown, m_bDisabled, m_bMask, m_bOver, m_bFocus; //skin bitmaps
	short	m_FocusRectMargin;		//dotted margin offset
	COLORREF m_TextColor;			//button text color
	HRGN	hClipRgn;			//clipping region
	int	m_Border;			//0=flat; 1=3D;
	short	m_DrawMode;			//0=normal; 1=stretch; 2=tiled;

	void	RelayEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void	FillWithBitmap(CDC* dc, HBITMAP hbmp, RECT r);
	void	DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, int DrawMode);
	int	GetBitmapWidth (HBITMAP hBitmap);
	int	GetBitmapHeight (HBITMAP hBitmap);

	//{{AFX_MSG(CxSkinButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnClicked();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg LRESULT OnRadioInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};