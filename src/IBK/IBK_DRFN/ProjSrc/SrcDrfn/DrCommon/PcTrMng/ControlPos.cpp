//------------------------------------------------------------------------------
// ControlPos.cpp
// 
//	CControlPos 
//	Position controls on a form's resize 
// 
//		Copyright (c) 2000 Paul Wendt
// 
//		VERSION#	DATE			NAME	DESCRIPTION OF CHANGE
//		--------	----------	----	---------------------
//		1.01  	07/11/2000	PRW	Original creation.
// 
#include "StdAfx.h"
#include "ControlPos.h"

//------------------------------------------------------------------------------
// CControlPos::CControlPos
// 
//	default constructor 
// 
//	Access: public
// 
//	Args:
//		CWnd* pParent				=	pointer to parent window
// 
//	Return:
//		none
// 
CControlPos::CControlPos(CWnd* pParent /* = NULL */)
{
	m_pParent = pParent;
	UpdateParentSize();

	m_nOldParentHeight = 0;
	m_nOldParentWidth = 0;
	
	SetNegativeMoves(FALSE);

	ResetControls();
}

//------------------------------------------------------------------------------
// CControlPos::~CControlPos
// 
//	default destructor -- It deletes all controls. 
// 
//	Access: public
// 
//	Args:
//		none
// 
//	Return:
//		none
// 
CControlPos::~CControlPos()
{
	ResetControls();
}

//------------------------------------------------------------------------------
// CControlPos::SetParent
// 
//	This sets the parent window. It should be called from a CWnd's 
//    post-constructor function, like OnInitdialog or InitialUpdate. 
// 
//	Access: public
// 
//	Args:
//		CWnd* pParent	=	parent window
// 
//	Return:
//		none
// 
void CControlPos::SetParent(CWnd* pParent, CSize* pSize)
{
	//////////////////////////////////////////////////////////////////////////
	// 2004.11.15 리사이즈 룰 수정(DefaultRect /ModifyRect 적용)
	CRect rcParentOriginalSize;
	if(pParent == m_pParent)
	{
		m_PaWRect.right = m_PaWRect.right + pSize->cx - m_PaRect.right;
		m_PaWRect.bottom = m_PaWRect.bottom + pSize->cy - m_PaRect.bottom;
		m_PaRect.SetRect(0, 0, pSize->cx, pSize->cy);

		m_nOriginalParentWidth = m_PaRect.Width();
		m_nOriginalParentHeight = m_PaRect.Height();
		m_nOldParentWidth = m_nOriginalParentWidth ;
		m_nOldParentHeight = m_nOriginalParentHeight;
	}
	else
	{
	
		m_pParent = pParent;
		if(pSize)
		{
			m_PaRect.SetRect(0, 0, pSize->cx, pSize->cy);
			m_PaWRect = m_PaRect;
			m_pParent->ClientToScreen(&m_PaWRect);
			m_nOriginalParentWidth = m_PaRect.Width();
			m_nOriginalParentHeight = m_PaRect.Height();
			m_nOldParentWidth = m_nOriginalParentWidth ;
			m_nOldParentHeight = m_nOriginalParentHeight;
		}
		else 
		{
			m_pParent->GetClientRect(rcParentOriginalSize);
			m_nOriginalParentWidth = rcParentOriginalSize.right;
			m_nOriginalParentHeight = rcParentOriginalSize.bottom;
			m_pParent->GetWindowRect(&m_PaWRect);
			m_pParent->GetClientRect(&m_PaRect);
			m_nOldParentWidth = m_nOriginalParentWidth ;
			m_nOldParentHeight = m_nOriginalParentHeight;
		}
	}	
	
	//CRect rcParentOriginalSize;
	//
	//m_pParent = pParent;
	//if(pSize)
	//{
	//	m_PaRect.SetRect(0, 0, pSize->cx, pSize->cy);
	//	m_PaWRect = m_PaRect;
	//	m_pParent->ClientToScreen(&m_PaWRect);
	//	m_nOriginalParentWidth = m_PaRect.Width();
	//	m_nOriginalParentHeight = m_PaRect.Height();
	//	m_nOldParentWidth = m_nOriginalParentWidth ;
	//	m_nOldParentHeight = m_nOriginalParentHeight;
	//}
	//else 
	//{
	//	m_pParent->GetClientRect(rcParentOriginalSize);
	//	m_nOriginalParentWidth = rcParentOriginalSize.right;
	//	m_nOriginalParentHeight = rcParentOriginalSize.bottom;
	//	m_pParent->GetWindowRect(&m_PaWRect);
	//	m_pParent->GetClientRect(&m_PaRect);
	//	m_nOldParentWidth = m_nOriginalParentWidth ;
	//	m_nOldParentHeight = m_nOriginalParentHeight;
	//}
	
	//////////////////////////////////////////////////////////////////////////
	

}

BOOL CControlPos::AddControl(const UINT& unId, const DWORD& dwStyle, CString csVBName)
{
	CWnd* pControl;

	if (m_pParent)
	{
		pControl = m_pParent->GetDlgItem(unId);
		return (AddControl(pControl, dwStyle, csVBName));
	}
	else
	{
		return (FALSE);
	}
}

BOOL CControlPos::AddControl(CWnd* pControl, const DWORD& dwStyle, CString csVBName)
{
	BOOL fReturnValue = TRUE;

	if (pControl && m_pParent)
	{

		LPCONTROLDATA pstControl = new CONTROLDATA;
		pstControl->hControl = pControl->GetSafeHwnd();
		pstControl->dwStyle = dwStyle;
		pControl->GetWindowRect(pstControl->m_ChRect);


		memcpy((LPSTR)pstControl->pCtrlName, (LPSTR)(LPCTSTR)csVBName, csVBName.GetLength());
		pstControl->pCtrlName[csVBName.GetLength()] = 0;
		
		
		m_awndControls.Add(((CObject*)pstControl));
	}
	else
	{
		fReturnValue = FALSE;
	}

	return (fReturnValue);
}

//------------------------------------------------------------------------------
// CControlPos::AddControl
// 
//	This adds a control to the internal list of controls in CControlPos.  
// 
//	Access: public
// 
//	Args:
//		CWnd* pControl				=	pointer to the control to be added
//		const DWORD& dwStyle		=  how the window should be moved -- see #define's
//                               in the header file
// 
//	Return:
//		BOOL 	=	TRUE if the control was added successfully, FALSE otherwise
// 
BOOL CControlPos::AddControl(CWnd* pControl, const DWORD& dwStyle /* = CP_MOVE_HORIZONTAL */)
{
	BOOL fReturnValue = TRUE;

	if (pControl && m_pParent)
	{

		LPCONTROLDATA pstControl = new CONTROLDATA;
		pstControl->hControl = pControl->GetSafeHwnd();
		pstControl->dwStyle = dwStyle;
		pControl->GetWindowRect(pstControl->m_ChRect);
//		pstControl->bControl = TRUE;
		m_awndControls.Add(((CObject*)pstControl));
	}
	else
	{
		fReturnValue = FALSE;
	}

	return (fReturnValue);
}

//------------------------------------------------------------------------------
// CControlPos::AddControl
// 
//	This adds a control the internal list of controls in CControlPos. 
// 
//	Access: public
// 
//	Args:
//		const UINT& unId			=	ID of the control to add
//		const DWORD& dwStyle		=	how the window should be moved -- see #define's
//                               in the header file
// 
//	Return:
//		BOOL 	=	TRUE if the control was added successfully, FALSE otherwise
// 
BOOL CControlPos::AddControl(const UINT& unId, const DWORD& dwStyle /* = CP_MOVE_HORIZONTAL */)
{
	CWnd* pControl;

	if (m_pParent)
	{
		pControl = m_pParent->GetDlgItem(unId);
		return (AddControl(pControl, dwStyle));
	}
	else
	{
		return (FALSE);
	}
}

//BOOL CControlPos::AddControl2(LPRECT pRect, const DWORD& dwStyle /* = CP_MOVE_HORIZONTAL */)
//{
//	BOOL fReturnValue = TRUE;
//
//	if (m_pParent)
//	{
//		LPCONTROLDATA pstControl = new CONTROLDATA;
//		pstControl->hControl = NULL;
//		pstControl->dwStyle = dwStyle;
//		pstControl->m_ChRect = pRect;
//		pstControl->bControl = FALSE;
//		m_awndControls.Add(((CObject*)pstControl));
//	}
//	else
//	{
//		fReturnValue = FALSE;
//	}
//
//	return (fReturnValue);
//}

//------------------------------------------------------------------------------
// CControlPos::RemoveControl
// 
//	If a client ever wants to remove a control programmatically, this 
//    function will do it. 
// 
//	Access: public
// 
//	Args:
//		CWnd* pControl	=	pointer of the window who should be removed from 
//								the internal control list [ie: will not be repositioned]
// 
//	Return:
//		BOOL 	=	TRUE if the control was found [and deleted], FALSE otherwise
// 
BOOL CControlPos::RemoveControl(CWnd* pControl)
{
	BOOL fReturnValue = FALSE;

	for (int i = 0; i < m_awndControls.GetSize(); i++)
	{
		LPCONTROLDATA pstControl = ((LPCONTROLDATA)m_awndControls.GetAt(i));
		
		if (pstControl->hControl == pControl->GetSafeHwnd())
		{
			m_awndControls.RemoveAt(i);
			delete pstControl;
			fReturnValue = TRUE;
			break;
		}
	}

	return (fReturnValue);
}

//------------------------------------------------------------------------------
// CControlPos::RemoveControl
// 
//	If a client ever wants to remove a control programmatically, this 
//    function will do it. 
// 
//	Access: public
// 
//	Args:
//		const UINT& unId  =  ID of the control that should be removed from the
//                         internal control list [ie: will not be repositioned]
// 
//	Return:
//		BOOL 	=	TRUE if the control was found [and deleted], FALSE otherwise
// 
BOOL CControlPos::RemoveControl(const UINT& unId)
{
	CWnd* pControl;

	if (m_pParent)
	{
		pControl = m_pParent->GetDlgItem(unId);
		return (RemoveControl(pControl));
	}
	else
	{
		return (FALSE);
	}
}

//------------------------------------------------------------------------------
// CControlPos::ResetControls
// 
//	This function removes all controls from the CControlPos object 
// 
//	Access: public
// 
//	Args:
//		none
// 
//	Return:
//		none
// 
void CControlPos::ResetControls(void)
{
	while (m_awndControls.GetSize() > 0)
	{
		int   nHighIdx = m_awndControls.GetUpperBound();
		LPCONTROLDATA pstControl = ((LPCONTROLDATA)m_awndControls.GetAt(nHighIdx));
		if (pstControl)
		{
			m_awndControls.RemoveAt(nHighIdx);
			delete pstControl;
		}
	}
}

void CControlPos::ResizeControls(int oldwidth, int oldheight, int newwidth, int newheight)
{
//////////////////////////////////////////////////////////////////////////
// 2004.11.15 리사이즈 룰 수정(DefaultRect /ModifyRect 적용) - 추가삽입
	if(newwidth)
		mp_nSavedWidth = newwidth;
	else
		newwidth = mp_nSavedWidth;

	if(newheight)
		mp_nSavedHeight = newheight;
	else
		newheight = mp_nSavedHeight;
		

	if(m_pParent) 
	{
		CRect rect;
		double dWRate = (double)newwidth / (double)m_PaRect.right;
		double dHRate = (double)newheight / (double)m_PaRect.bottom;

		int topGap  = ( m_PaWRect.Height() - m_PaRect.Height() );
		int leftGap = ( m_PaWRect.Width() - m_PaRect.Width() );

		
//---------------------------------------------------------------------------------------------
// Resize Flag을 통한 컨트롤 리사이즈를 위해서.. 수정.... 최진원 2003.04.21
// 제한 : 이동이 고정되고, 사이즈가 변경되는 컨트롤의 경우, 이동이 고정되면서 발생한 오차만큼의 크기만큼
// 추가적인 리사이징이 일어난다.
		for(int i = 0; i < m_awndControls.GetSize(); i++) 
		{
			LPCONTROLDATA pstControl = ((LPCONTROLDATA)m_awndControls.GetAt(i));
			CWnd* pControl = m_pParent->FromHandle(pstControl->hControl);

			if ((pstControl->dwStyle & (CP_MOVE_VERTICAL)) == (CP_MOVE_VERTICAL))
				rect.top	= (int)(dHRate * (pstControl->m_ChRect.top-m_PaWRect.top-topGap) + 0.5);
			else
				rect.top	= pstControl->m_ChRect.top-m_PaWRect.top-topGap;

			if ((pstControl->dwStyle & (CP_MOVE_HORIZONTAL)) == (CP_MOVE_HORIZONTAL))
				rect.left	= (int)(dWRate * (pstControl->m_ChRect.left-m_PaWRect.left-leftGap) + 0.5);
			else
				rect.left	= pstControl->m_ChRect.left-m_PaWRect.left-leftGap;

			
			int nHeigtht = pstControl->m_ChRect.Height();
			if ((pstControl->dwStyle & (CP_RESIZE_VERTICAL)) == (CP_RESIZE_VERTICAL))
			{
				rect.bottom	= rect.top + (int)(dHRate * (pstControl->m_ChRect.Height()) + 0.5);
				// 이동이 고정되면서 발생한 오차 보정
				if( (pstControl->dwStyle & (CP_MOVE_VERTICAL)) != (CP_MOVE_VERTICAL) )
					rect.bottom += (int)((dHRate-1)*(pstControl->m_ChRect.top-m_PaWRect.top-topGap)+0.5);
			}
			else
				rect.bottom	= rect.top + pstControl->m_ChRect.Height();

			if ((pstControl->dwStyle & (CP_RESIZE_HORIZONTAL)) == (CP_RESIZE_HORIZONTAL))
			{
				rect.right	= rect.left + (int)(dWRate * (pstControl->m_ChRect.Width()) + 0.5);
				// 이동이 고정되면서 발생한 오차 보정
				if( (pstControl->dwStyle & (CP_MOVE_HORIZONTAL)) != (CP_MOVE_HORIZONTAL) )
					rect.right += (int)((dWRate-1)*(pstControl->m_ChRect.left-m_PaWRect.left-leftGap)+0.5);
			}
			else
				rect.right	= rect.left + pstControl->m_ChRect.Width();

			pControl->MoveWindow(rect);
		}
		m_pParent->InvalidateRect(NULL);
	}
//////////////////////////////////////////////////////////////////////////
// 2004.11.15 리사이즈 룰 수정(DefaultRect /ModifyRect 적용)  - 삭제	
//	if(newwidth)
//		mp_nSavedWidth = newwidth;
//	else
//		newwidth = mp_nSavedWidth;
//
//	if(newheight)
//		mp_nSavedHeight = newheight;
//	else
//		newheight = mp_nSavedHeight;
//	
//	if(m_pParent) {
//		CRect rect;
//		double dWRate = (double)newwidth / (double)m_PaRect.right;
//		double dHRate = (double)newheight / (double)m_PaRect.bottom;
//
//		int topGap  = ( m_PaWRect.Height() - m_PaRect.Height() );
//		int leftGap = ( m_PaWRect.Width() - m_PaRect.Width() );
//
//		for(int i = 0; i < m_awndControls.GetSize(); i++) {
//			LPCONTROLDATA pstControl = ((LPCONTROLDATA)m_awndControls.GetAt(i));
//			//if(pstControl->bControl)
//			//{
//				CWnd* pControl = m_pParent->FromHandle(pstControl->hControl);	
//
//				rect.left	= (int)(dWRate * (pstControl->m_ChRect.left-m_PaWRect.left-leftGap) + 0.5);
//				rect.right	= rect.left + (int)(dWRate * (pstControl->m_ChRect.Width()) + 0.5);
//
//				rect.top	= (int)(dHRate * (pstControl->m_ChRect.top-m_PaWRect.top-topGap) + 0.5);
//				rect.bottom	= rect.top + (int)(dHRate * (pstControl->m_ChRect.Height()) + 0.5);
//
//				pControl->MoveWindow(rect);
//			//}
//			//else
//			//{
//			//	rect.left	= (int)(dWRate * (pstControl->m_ChRect.left-m_PaWRect.left-leftGap) + 0.5);
//			//	rect.right	= rect.left + (int)(dWRate * (pstControl->m_ChRect.Width()) + 0.5);
//			//
//			//	rect.top	= (int)(dHRate * (pstControl->m_ChRect.top-m_PaWRect.top-topGap) + 0.5);
//			//	rect.bottom	= rect.top + (int)(dHRate * (pstControl->m_ChRect.Height()) + 0.5);
//			//
//			//	pControl->MoveWindow(rect);
//			//}
//		}
//		m_pParent->InvalidateRect(NULL);
//	}

}

//------------------------------------------------------------------------------
// CControlPos::MoveControls
// 
//	This function takes care of moving all controls that have been added to 
//    the object [see AddControl].  This function should be called from the 
//    WM_SIZE handler-function [typically OnSize]. 
// 
//	Access: public
// 
//	Args:
//		none
// 
//	Return:
//		none
// 
void CControlPos::MoveControls(void)
{
	AfxMessageBox("CControlPos::MoveControls 왜부르시나요?");
	if (m_pParent)
	{
		//--------------------------------------------------------------------
		// for each control that has been added to our object, we want to
		// check its style and move it based off of the parent control's
		// movements.
		// the thing to keep in mind is that when you resize a window, you
		// can resize by more than one pixel at a time. this is important
		// when, for example, you start with a width smaller than the
		// original width and you finish with a width larger than the
		// original width. you know that you want to move the control, but
		// by how much? that is why so mdts if's and calculations are made
		for (int i = 0; i < m_awndControls.GetSize(); i++)
		{
			LPCONTROLDATA pstControl = ((LPCONTROLDATA)m_awndControls.GetAt(i));
			CRect rcParentBounds;
			CRect rcBounds;
			CWnd* pControl = m_pParent->FromHandle(pstControl->hControl);

			pControl->GetWindowRect(rcBounds);
			m_pParent->GetClientRect(rcParentBounds);

			if ((pstControl->dwStyle & (CP_RESIZE_VERTICAL)) == (CP_RESIZE_VERTICAL))
			{
				if (!m_fNegativeMoves)
				{
					if (rcParentBounds.bottom > m_nOriginalParentHeight)
					{
						if (m_nOriginalParentHeight <= m_nOldParentHeight)
						{
							rcBounds.bottom += rcParentBounds.bottom - m_nOldParentHeight;
						}
						else
						{
							rcBounds.bottom += rcParentBounds.bottom - m_nOriginalParentHeight;
						}
					}
					else
					{
						if (m_nOldParentHeight > m_nOriginalParentHeight)
						{
							rcBounds.bottom += m_nOriginalParentHeight - m_nOldParentHeight;
						}
					}
				}
				else
				{
					rcBounds.bottom += rcParentBounds.bottom - m_nOldParentHeight;
				}
			}

			if ((pstControl->dwStyle & (CP_RESIZE_HORIZONTAL)) == (CP_RESIZE_HORIZONTAL))
			{
				if (!m_fNegativeMoves)
				{
					if (rcParentBounds.right > m_nOriginalParentWidth)
					{
						if (m_nOriginalParentWidth <= m_nOldParentWidth)
						{
							rcBounds.right += rcParentBounds.right - m_nOldParentWidth;
						}
						else
						{
							rcBounds.right += rcParentBounds.right - m_nOriginalParentWidth;
						}
					}
					else
					{
						if (m_nOldParentWidth > m_nOriginalParentWidth)
						{
							rcBounds.right += m_nOriginalParentWidth - m_nOldParentWidth;
						}
					}
				}
				else
				{
					rcBounds.right += rcParentBounds.right - m_nOldParentWidth;
				}
			}

			if ((pstControl->dwStyle & (CP_MOVE_VERTICAL)) == (CP_MOVE_VERTICAL))
			{
				if (!m_fNegativeMoves)
				{
					if (rcParentBounds.bottom > m_nOriginalParentHeight)
					{
						if (m_nOriginalParentHeight <= m_nOldParentHeight)
						{
							rcBounds.bottom += rcParentBounds.bottom - m_nOldParentHeight;
							rcBounds.top += rcParentBounds.bottom - m_nOldParentHeight;
						}
						else
						{
							rcBounds.bottom += rcParentBounds.bottom - m_nOriginalParentHeight;
							rcBounds.top += rcParentBounds.bottom - m_nOriginalParentHeight;
						}
					}
					else
					{
						if (m_nOldParentHeight > m_nOriginalParentHeight)
						{
							rcBounds.bottom += m_nOriginalParentHeight - m_nOldParentHeight;
							rcBounds.top += m_nOriginalParentHeight - m_nOldParentHeight;
						}
					}
				}
				else
				{
					rcBounds.bottom += rcParentBounds.bottom - m_nOldParentHeight;
					rcBounds.top += rcParentBounds.bottom - m_nOldParentHeight;
				}
			}

			if ((pstControl->dwStyle & (CP_MOVE_HORIZONTAL)) == (CP_MOVE_HORIZONTAL))
			{
				if (!m_fNegativeMoves)
				{
					if (rcParentBounds.right > m_nOriginalParentWidth)
					{
						if (m_nOriginalParentWidth <= m_nOldParentWidth)
						{
							rcBounds.right += rcParentBounds.right - m_nOldParentWidth;
							rcBounds.left += rcParentBounds.right - m_nOldParentWidth;
						}
						else
						{
							rcBounds.right += rcParentBounds.right - m_nOriginalParentWidth;
							rcBounds.left += rcParentBounds.right - m_nOriginalParentWidth;
						}
					}
					else
					{
						if (m_nOldParentWidth > m_nOriginalParentWidth)
						{
							rcBounds.right += m_nOriginalParentWidth - m_nOldParentWidth;
							rcBounds.left += m_nOriginalParentWidth - m_nOldParentWidth;
						}
					}
				}
				else
				{
					rcBounds.right += rcParentBounds.right - m_nOldParentWidth;
					rcBounds.left += rcParentBounds.right - m_nOldParentWidth;
				}
			}

			m_pParent->ScreenToClient(rcBounds);
			pControl->MoveWindow(rcBounds);
		}

		UpdateParentSize();
	}
}

//------------------------------------------------------------------------------
// CControlPos::SetNegativeMoves
// 
//	This sets the NegativeMoves boolean parameter of the object. When the 
//    parent window becomes smaller than it started, setting this to FALSE 
//    will not allow controls to be moved; the parent size may change, but 
//    it'll just force the controls to go off of the 
//    This parameter defaults to FALSE on object creation.
// 
//	Access: public
// 
//	Args:
//		const BOOL& fNegativeMoves /* = TRUE */	=	value to set
// 
//	Return:
//		none
// 
void CControlPos::SetNegativeMoves(const BOOL& fNegativeMoves /* = TRUE */)
{
	m_fNegativeMoves = fNegativeMoves;
}

//------------------------------------------------------------------------------
// CControlPos::GetNegativeMoves
// 
//	This function returns whether or not negative moves are enabled. 
// 
//	Access: public
// 
//	Args:
//		none
// 
//	Return:
//		BOOL 	=	TRUE if negative moves are enabled, FALSE otherwise
// 
BOOL CControlPos::GetNegativeMoves(void) const
{
	return (m_fNegativeMoves);
}

//------------------------------------------------------------------------------
// CControlPos::UpdateParentSize
// 
//	Since CControlPos keeps track of the parent's size, it gets updated 
//    every time it tells us to size the controls. We keep track so we know 
//    how much it changed from the last WM_SIZE message. 
// 
//	Access: protected
// 
//	Args:
//		none
// 
//	Return:
//		none
// 
void CControlPos::UpdateParentSize(void)
{
	return;

	if (m_pParent)
	{
		CRect rcBounds;
		m_pParent->GetClientRect(rcBounds);

		m_nOldParentWidth = rcBounds.Width();
		m_nOldParentHeight = rcBounds.Height();
	}
}