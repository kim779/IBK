// CxSkinButton.cpp : implementation file
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

#include "stdafx.h"
#include "xSkinButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CxSkinButton
CxSkinButton::CxSkinButton()
{
	m_DrawMode = 1;			// normal drawing mode
	m_FocusRectMargin = 0;		// disable focus dotted rect
	hClipRgn = nullptr;		// no clipping region
	m_Border = 0;			// 0=flat; 1=3D;
	m_nType = 0;
	m_Style = 0;			// radio & check buttons
	m_TextColor = GetSysColor(COLOR_BTNTEXT); // default button text color
	m_button_down = m_tracking = m_Checked = false;
}
/////////////////////////////////////////////////////////////////////////////
CxSkinButton::~CxSkinButton()
{
	if (hClipRgn) 
		DeleteObject(hClipRgn);	// free clip region
}
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CxSkinButton, CButton)
	//{{AFX_MSG_MAP(CxSkinButton)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KILLFOCUS()
	//ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_CXSHADE_RADIO , OnRadioInfo)
	ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
	ON_MESSAGE(BM_GETCHECK , OnBMGetCheck)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CxSkinButton message handlers
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::PreSubclassWindow() 
{
	m_Style=GetButtonStyle();	///get specific BS_ styles
	if ((m_Style & BS_AUTOCHECKBOX)==BS_AUTOCHECKBOX)
//		||((m_Style & BS_CHECKBOX)==BS_CHECKBOX))
		m_Style=BS_CHECKBOX;
	else if ((m_Style & BS_AUTORADIOBUTTON)==BS_AUTORADIOBUTTON)
//			||((m_Style & BS_RADIOBUTTON)==BS_RADIOBUTTON))
		m_Style=BS_RADIOBUTTON;
	else { m_Style=BS_PUSHBUTTON; }

	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}
/////////////////////////////////////////////////////////////////////////////
BOOL CxSkinButton::OnEraseBkgnd(CDC* pDC) 
{	return 1; }	// doesn't erase the button background

//#include "MapDlg.h"
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (lpDrawItemStruct == nullptr)
		return;

	//Check if the button state in not in inconsistent mode...
	POINT	mouse_position{};

	if ((m_button_down) && (::GetCapture() == m_hWnd) && (::GetCursorPos(&mouse_position)))
	{
		if (::WindowFromPoint(mouse_position) == m_hWnd)
		{
			if ((GetState() & BST_PUSHED) != BST_PUSHED)
			{
				//TRACE("* Inconsistency up detected! Fixing.\n");
				SetState(TRUE);
				return;
			}
		}
		else
		{
			if ((GetState() & BST_PUSHED) == BST_PUSHED)
			{
				//TRACE("* Inconsistency up detected! Fixing.\n");
				SetState(FALSE);
				return;
			}
		}
	}
	
	CString sCaption;
	CDC	*pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	// get device context
	RECT	r=lpDrawItemStruct->rcItem;					// context rectangle
	const	int	cx = r.right  - r.left ;						// get width
	const	int	cy = r.bottom - r.top  ;						// get height
	// get text box position
	RECT	tr={r.left+m_FocusRectMargin+2,r.top,r.right-m_FocusRectMargin-2,r.bottom};

	GetWindowText(sCaption);							// get button text
	pDC->SetBkMode(TRANSPARENT);

	// Select the correct skin 
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{	// DISABLED BUTTON
		if (m_bDisabled.m_hObject==NULL)
			 // no skin selected for disabled state -> standard button
			pDC->FillSolidRect(&r,GetSysColor(COLOR_BTNFACE));
		else // paint the skin
			DrawBitmap(pDC,(HBITMAP)m_bDisabled,r,m_DrawMode);
		// if needed, draw the standard 3D rectangular border
		if (m_Border)
			pDC->DrawEdge(&r,EDGE_RAISED,BF_RECT);
		// paint the etched button text
		pDC->SetTextColor(GetSysColor(COLOR_3DHILIGHT));
		pDC->DrawText(sCaption,&tr,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		OffsetRect(&tr,-1,-1);
		pDC->DrawText(sCaption,&tr,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}
	else
	{										// SELECTED (DOWN) BUTTON
		if ((lpDrawItemStruct->itemState & ODS_SELECTED)||m_Checked)
		{
			if (m_bDown.m_hObject==NULL)
				 // no skin selected for selected state -> standard button
				pDC->FillSolidRect(&r,GetSysColor(COLOR_BTNFACE));
			else
			{ // paint the skin
				DrawBitmap(pDC,(HBITMAP)m_bDown,r,m_DrawMode);
			}
			OffsetRect(&tr,1,1);  //shift text
			// if needed, draw the standard 3D rectangular border
			if (m_Border)
				pDC->DrawEdge(&r,EDGE_SUNKEN,BF_RECT);
			if (m_nType)
			{
			}
		}
		else
		{											// DEFAULT BUTTON
			if (m_bNormal.m_hObject==NULL)
				 // no skin selected for normal state -> standard button
				pDC->FillSolidRect(&r,GetSysColor(COLOR_BTNFACE));
			else // paint the skin
				if ((m_tracking)&&(m_bOver.m_hObject!=NULL))
				{
					DrawBitmap(pDC,(HBITMAP)m_bOver,r,m_DrawMode);
				}
				else
				{
					if ((lpDrawItemStruct->itemState & ODS_FOCUS)&&(m_bFocus.m_hObject!=NULL))
					{
						DrawBitmap(pDC,(HBITMAP)m_bFocus,r,m_DrawMode);
					}
					else
					{
						DrawBitmap(pDC,(HBITMAP)m_bNormal,r,m_DrawMode);
					}
				}
				// if needed, draw the standard 3D rectangular border
				if (m_Border)
					pDC->DrawEdge(&r,EDGE_RAISED,BF_RECT);
				if (m_nType)
				{
				}
		}
		// paint the focus rect
		if ((lpDrawItemStruct->itemState & ODS_FOCUS)&&(m_FocusRectMargin>0))
		{
			r.left   += m_FocusRectMargin ;
			r.top    += m_FocusRectMargin ;
			r.right  -= m_FocusRectMargin ;
			r.bottom -= m_FocusRectMargin ;
			DrawFocusRect (lpDrawItemStruct->hDC, &r) ;
		}
		// paint the enabled button text
		pDC->SetTextColor(m_TextColor);
		pDC->DrawText(sCaption,&tr,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}
}
/////////////////////////////////////////////////////////////////////////////
int CxSkinButton::GetBitmapWidth (HBITMAP hBitmap)
{ BITMAP bm; GetObject(hBitmap,sizeof(BITMAP),(PSTR)&bm); return bm.bmWidth;}
/////////////////////////////////////////////////////////////////////////////
int CxSkinButton::GetBitmapHeight (HBITMAP hBitmap)
{ BITMAP bm; GetObject(hBitmap,sizeof(BITMAP),(PSTR)&bm); return bm.bmHeight;}
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, int DrawMode)
{
//	DrawMode: 0=Normal; 1=stretch; 2=tiled fill
	if (DrawMode==2)
	{
		FillWithBitmap(dc,hbmp,r);
		return;
	}
	if (!hbmp) return;	//safe check

	const	int	cx = r.right  - r.left;
	const	int	cy = r.bottom - r.top;
	CDC	dcBmp,dcMask;

	dcBmp.CreateCompatibleDC(dc);
	dcBmp.SelectObject(hbmp);
	
	if (m_bMask.m_hObject!=NULL)
	{
		dcMask.CreateCompatibleDC(dc);
		dcMask.SelectObject(m_bMask);

		CDC hdcMem;
		hdcMem.CreateCompatibleDC(dc);
		CBitmap hBitmap;
		hBitmap.CreateCompatibleBitmap(dc,cx,cy);
		hdcMem.SelectObject(hBitmap);
		
		hdcMem.BitBlt(r.left,r.top,cx,cy,dc,0,0,SRCCOPY);
		if (!DrawMode)
		{
			hdcMem.BitBlt(r.left,r.top,cx,cy,&dcBmp,0,0,SRCINVERT);
			hdcMem.BitBlt(r.left,r.top,cx,cy,&dcMask,0,0,SRCAND);
			hdcMem.BitBlt(r.left,r.top,cx,cy,&dcBmp,0,0,SRCINVERT);
		}
		else
		{
			const	int	bx = GetBitmapWidth(hbmp);
			const	int	by = GetBitmapHeight(hbmp);
			hdcMem.StretchBlt(r.left,r.top,cx,cy,&dcBmp,0,0,bx,by,SRCINVERT);
			hdcMem.StretchBlt(r.left,r.top,cx,cy,&dcMask,0,0,bx,by,SRCAND);
			hdcMem.StretchBlt(r.left,r.top,cx,cy,&dcBmp,0,0,bx,by,SRCINVERT);
		}
		dc->BitBlt(r.left,r.top,cx,cy,&hdcMem,0,0,SRCCOPY);

		hdcMem.DeleteDC();
		hBitmap.DeleteObject();

		DeleteDC(dcMask);
	}
	else
	{
		if (!DrawMode)
		{
			dc->BitBlt(r.left,r.top,cx,cy,&dcBmp,0,0,SRCCOPY);
		}
		else
		{
			const	int	bx = GetBitmapWidth(hbmp);
			const	int	by = GetBitmapHeight(hbmp);
			dc->StretchBlt(r.left,r.top,cx,cy,&dcBmp,0,0,bx,by,SRCCOPY);
		}
	}
	DeleteDC(dcBmp);
}

/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::FillWithBitmap(CDC* dc, HBITMAP hbmp, RECT r)
{
	if (!hbmp)
		return;

	CDC	memdc;
	memdc.CreateCompatibleDC(dc);
	memdc.SelectObject(hbmp);

	const	int	w = r.right - r.left;
	const	int	h = r.bottom - r.top;
	int	x = 0, y = 0, z = 0;
	const	int	bx = GetBitmapWidth(hbmp);
	int	by = GetBitmapHeight(hbmp);
	for (y = r.top ; y < h ; y += by)
	{
		if ((y + by) > h)
			by = h - y;
		z = bx;
		for (x = r.left ; x < w ; x += z)
		{
			if ((x + z) > w)
				z = w - x;
			dc->BitBlt(x, y, z, by, &memdc, 0, 0, SRCCOPY);
		}
	}
	DeleteDC(memdc);
}

void CxSkinButton::SetSkin(CString normal,CString down,CString over,UINT type,
				  short drawmode, short border, short margin)
{
	m_nType = type;
	m_bNormal.DeleteObject();	//free previous allocated bitmap
	m_bDown.DeleteObject();
	m_bOver.DeleteObject();
	m_bDisabled.DeleteObject();
	m_bMask.DeleteObject();
	m_bFocus.DeleteObject();

	HBITMAP hBitmap = NULL;
	
	if (normal != "")
	{
		hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), normal,
			IMAGE_BITMAP,0,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			m_bNormal.Attach(hBitmap);
	}
	if (down != "")
	{
		hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), down,
			IMAGE_BITMAP,0,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			m_bDown.Attach(hBitmap);
	}
	if (over != "")
	{
		hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), over,
			IMAGE_BITMAP,0,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			m_bOver.Attach(hBitmap);
	}

	if (normal!="")
	{
		hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), normal,
			IMAGE_BITMAP,0,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			m_bDisabled.Attach(hBitmap);
	}		
	
	m_DrawMode=max(0,min(drawmode,2));
	m_Border=border;
	m_FocusRectMargin=max(0,margin);
}
/////////////////////////////////////////////////////////////////////////////
COLORREF CxSkinButton::SetTextColor(COLORREF new_color)
{
	const	COLORREF tmp_color=m_TextColor;
	m_TextColor=new_color;
	return tmp_color;			//returns the previous color
}
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::SetToolTipText(CString s)
{
	if (m_tooltip.m_hWnd==NULL)
	{
		if (m_tooltip.Create(this))	//first assignment
			if (m_tooltip.AddTool(this, (LPCTSTR)s))
				m_tooltip.Activate(1);
	}
	else
	{
		m_tooltip.UpdateTipText((LPCTSTR)s,this);
	}
}
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::RelayEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
// This function will create a MSG structure, fill it in a pass it to
// the ToolTip control, m_ttip.  Note that we ensure the point is in window
// coordinates (relative to the control's window).
	if (NULL != m_tooltip.m_hWnd)
	{
		MSG msg{};

		msg.hwnd = m_hWnd;
		msg.message = message;
		msg.wParam = wParam;
		msg.lParam = lParam;
		msg.time = 0;
		msg.pt.x = LOWORD(lParam);
		msg.pt.y = HIWORD(lParam);

		m_tooltip.RelayEvent(&msg);
	}
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnLButtonDblClk
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NONE
//Parameters..: Used only to be forwarded as WM_LBUTTONDOWN message parameters
//Exceptions..: NONE
//------------
//Description :
//
//  > We do not care about doublelicks - handle this event
//    like an ordinary left-button-down event
//
//---------------------------------------------------------
void CxSkinButton::OnLButtonDblClk(UINT flags, CPoint point) 
{
	SendMessage(WM_LBUTTONDOWN, flags, MAKELPARAM(point.x, point.y));
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnLButtonDown
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NONE
//Parameters..: As follows
//    > [in] nFlags: not used
//    > [in] point: coordinates of the mouse pointer when this event was spawned
//Exceptions..: NONE
//------------
//Description :
//
//  > Handle event when left button is pressed down
//
//---------------------------------------------------------
void CxSkinButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Pass this message to the ToolTip control
	RelayEvent(WM_LBUTTONDOWN,(WPARAM)nFlags,MAKELPARAM(LOWORD(point.x),LOWORD(point.y)));

	//If we are tracking this button, cancel it
	if (m_tracking)
	{
		TRACKMOUSEEVENT t = {
					sizeof(TRACKMOUSEEVENT),
					TME_CANCEL | TME_LEAVE,
					m_hWnd,
					0
					};
		if (::_TrackMouseEvent(&t))
		{
			m_tracking = false;
		}
	}

	//Default-process the message
	CButton::OnLButtonDown(nFlags, point);
	m_button_down = true;
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnLButtonUp
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NONE
//Parameters..: As follows
//    > [in] nFlags: not used
//    > [in] point: coordinates of the mouse pointer when this event was spawned
//Exceptions..: NONE
//------------
//Description :
//
//  > Handle event when left button is released (goes up)
//
//---------------------------------------------------------
void CxSkinButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Style){ //track mouse for radio & check buttons
		POINT p2 = point;
		::ClientToScreen(m_hWnd, &p2);
		HWND mouse_wnd = ::WindowFromPoint(p2);
		if (mouse_wnd == m_hWnd)
		{ // mouse is in button
			if (m_Style==BS_CHECKBOX) SetCheck(m_Checked ? 0 : 1);
			if (m_Style==BS_RADIOBUTTON) SetCheck(1);
		} 
	}
	//Pass this message to the ToolTip control
	RelayEvent(WM_LBUTTONUP,(WPARAM)nFlags,MAKELPARAM(LOWORD(point.x),LOWORD(point.y)));

    //Default-process the message
	m_button_down = false;
	CButton::OnLButtonUp(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnMouseMove
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NONE
//Parameters..: As follows
//    > [in] nFlags: not used
//    > [in] point: coordinates of the mouse pointer when this event was spawned
//Exceptions..: NONE
//------------
//Description :
//
//  > Handle change of mouse position: see the comments in the
//    method for further info.
//
//---------------------------------------------------------
void CxSkinButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//Pass this message to the ToolTip control
	RelayEvent(WM_MOUSEMOVE,(WPARAM)nFlags,MAKELPARAM(LOWORD(point.x),LOWORD(point.y)));

	//If we are in capture mode, button has been pressed down
	//recently and not yet released - therefore check is we are
	//actually over the button or somewhere else. If the mouse
	//position changed considerably (e.g. we moved mouse pointer
	//from the button to some other place outside button area)
	//force the control to redraw
	//
	if (m_button_down && ::GetCapture() == m_hWnd)
	{
		POINT p2 = point;
		::ClientToScreen(m_hWnd, &p2);
		HWND mouse_wnd = ::WindowFromPoint(p2);

		const	bool	pressed = ((GetState() & BST_PUSHED) == BST_PUSHED);
		const	bool	need_pressed = (mouse_wnd == m_hWnd);
		if (pressed != need_pressed)
		{
			//TRACE("* %08X Redraw\n", GetTickCount());
			SetState(need_pressed ? TRUE : FALSE);
			Invalidate();
		}
	}
	else
	{
		//Otherwise the button is released. That means we should
		//know when we leave its area - and so if we are not tracking
		//this mouse leave event yet, start now!
		//
		if (!m_tracking)
		{
			TRACKMOUSEEVENT t = {
						sizeof(TRACKMOUSEEVENT),
						TME_LEAVE,
						m_hWnd,
						0
						};
			if (::_TrackMouseEvent(&t))
			{
				//TRACE("* Mouse enter\n");
				m_tracking = true;
				Invalidate();
			}
		}
	}

	//Forward this event to superclass
	CButton::OnMouseMove(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnMouseLeave
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NULL
//Parameters..: NOT USED
//Exceptions..: NONE
//------------
//Description :
//
//  > Handle situation when mouse cursor leaves area of this
//    window (button). This event might be generated ONLY
//    if we explicitely call 'TrackMouseEvent'. This is
//    signalled by setting the m_tracking flag (see the assert
//    precondition) - in 'OnMouseMove' method
//
//  > When a mouse pointer leaves area of this button (i.e.
//    when this method is invoked), presumably the look of
//    the button changes (e.g. when hover/non-hover images are set)
//    and therefore we force the control to redraw.
//
//---------------------------------------------------------
LRESULT CxSkinButton::OnMouseLeave(WPARAM, LPARAM)
{
	ASSERT (m_tracking);
	//TRACE("* Mouse leave\n");
	m_tracking = false;
	Invalidate();
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnKillFocus
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: NONE
//Parameters..: See superclass documentation
//Exceptions..: NONE
//------------
//Description :
//
//  > If focus is killed during capture, we may no longer
//    have the exclusive access to user input and therefore
//    release it.
//
//  > Such a situation might happens when the user left-clicks
//    this button, keeps the button down and simultaneously
//    presses TAB key.
//
//---------------------------------------------------------
void CxSkinButton::OnKillFocus(CWnd *new_wnd)
{
	if (::GetCapture() == m_hWnd)
	{
		::ReleaseCapture();
		ASSERT (!m_tracking);
		m_button_down = false;
	}
	CButton::OnKillFocus(new_wnd);
}


/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnClicked
//Class.......: CxSkinButton
//
//Author......: Milan Gardian
//Created.....: MAR-2001
//
//Return value: FALSE (do not stop in this handler - forward to parent)
//Parameters..: NONE
//Exceptions..: NONE
//------------
//Description :
//
//  > Keep consistency of attributes of this instance before
//    submitting click event to the parent.
//
//  > Currently NOT used. To use, umcomment line
//    "ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)" in message map
//    at the beginning of this file.
//
//---------------------------------------------------------
BOOL CxSkinButton::OnClicked() 
{
	if (::GetCapture() == m_hWnd)
	{
		::ReleaseCapture();
		ASSERT (!m_tracking);
	}
	m_button_down = false;
	//Invalidate();
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//
//Method......: OnRadioInfo
//Class.......: CxSkinButton
//
//Author......: Rainer Mangold
//Created.....: JUN-2001
//
//Return value: NULL
//Parameters..: WPARAM and LPARAM (LPARAM not used)
//Exceptions..: NONE
//------------
//Description :
//
//  > Handle notification, that a Button in the same group was pushed
//
//---------------------------------------------------------
LRESULT CxSkinButton::OnRadioInfo(WPARAM wparam, LPARAM)
{
	if (m_Checked)	//only checked buttons need to be unchecked
	{
		m_Checked = false;
		Invalidate();
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
void CxSkinButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((m_Style)&&(nChar==' '))	//needed stuff for check & radio buttons
	{
		if (m_Style==BS_CHECKBOX) SetCheck(m_Checked ? 0 : 1);
		if (m_Style==BS_RADIOBUTTON) SetCheck(1);
	}
	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}
/////////////////////////////////////////////////////////////////////////////
//
//Method......: SetCheck
//Class.......: CxSkinButton
//
//Author......: Rainer Mangold
//Created.....: JUN-2001
//
//Return value: NONE
//Parameters..: bool
//Exceptions..: NONE
//------------
//Description :
//
//  > Set the state of this button (pushed or not). 
//    Works for both, Radio and CheckBox - Buttons
//
//---------------------------------------------------------
LRESULT CxSkinButton::OnBMSetCheck(WPARAM wparam, LPARAM)
{
	m_Checked=wparam!=0;
	switch (m_Style)
	{
	case BS_RADIOBUTTON:
		if (m_Checked)	//uncheck the other radio buttons (in the same group)
		{
			HWND	hpwnd = GetParent()->GetSafeHwnd();		//get button parent handle
			HWND	hwnd2 = GetSafeHwnd(), hthis=GetSafeHwnd();	//get this button handle
			if (hthis && hpwnd)					//consistency check
			{
				for ( ;; )	//scan the buttons within the group
				{
					hwnd2=::GetNextDlgGroupItem(hpwnd,hwnd2,0);
					//until we reach again this button
					if (hwnd2==hthis || hwnd2==NULL)
						break;
					//post the uncheck message
					::PostMessage(hwnd2, WM_CXSHADE_RADIO, 0, 0);
				}
			}
		}
		break;
	case BS_PUSHBUTTON:
		m_Checked=false;
		ASSERT(false); // Must be a Check or Radio button to use this function
	}

	Invalidate();
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
LRESULT CxSkinButton::OnBMGetCheck(WPARAM wparam, LPARAM)
{ return m_Checked; }	//returns the state for check & radio buttons
/////////////////////////////////////////////////////////////////////////////
//EOF
