/*************************************************************************
				Class Implementation : CUGDropTarget
**************************************************************************
	Source file : UGDrgDrp.cpp
	Copyright ? Dundas Software Ltd. 1994 - 2002, All Rights Reserved
*************************************************************************/
#include "stdafx.h"
#include "UGCtrl.h"

#ifdef UG_ENABLE_DRAGDROP

/***************************************************
	Standard construction/desrtuction
***************************************************/
CUGDropTarget::CUGDropTarget()
{
}

CUGDropTarget::~CUGDropTarget()
{
}

/***************************************************
OnDragEnter
	Called by the framework when the cursor is first dragged
	into the window.  The return value determines if the
	drag-drop operation is allowed to continue.
Params:
	pWnd		- please see MSDN for explanation of individual
	pDataObject	  parameter passed in
	dwKeyState
	point
Returns:
	DROPEFFECT, please see the MSDN for list of possible
	values.
*****************************************************/
DROPEFFECT CUGDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	UNREFERENCED_PARAMETER(pWnd);
	UNREFERENCED_PARAMETER(dwKeyState);
	UNREFERENCED_PARAMETER(point);

	return m_ctrl->OnDragEnter(pDataObject);
}

/***************************************************
OnDragOver
	Called by the framework when the cursor is dragged over
	the window.  The return value determines if the
	drag-drop operation is allowed to continue.
Params:
	pWnd		- please see MSDN for explanation of individual
	pDataObject	  parameter passed in
	dwKeyState
	point
Returns:
	DROPEFFECT, please see the MSDN for list of possible
	values.
*****************************************************/
DROPEFFECT CUGDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	UNREFERENCED_PARAMETER(pWnd);
	UNREFERENCED_PARAMETER(dwKeyState);

	int col;
	long row;

	m_ctrl->GetCellFromPoint(point.x,point.y,&col,&row);

	return m_ctrl->OnDragOver(pDataObject,col,row);
}

/***************************************************
OnDropEx
	Called by the framework when a drop operation is to occur.
Params:
	pWnd		- please see MSDN for explanation of individual
	pDataObject	  parameter passed in
	dropDefault
	dropList
	point
Returns:
	DROPEFFECT, please see the MSDN for list of possible
	values.
*****************************************************/
DROPEFFECT CUGDropTarget::OnDropEx( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point )
{
	UNREFERENCED_PARAMETER(pWnd);
	UNREFERENCED_PARAMETER(dropDefault);
	UNREFERENCED_PARAMETER(dropList);

	int col{};
	long row{};
	int rt{};
	m_ctrl->GetCellFromPoint(point.x,point.y,&col,&row);
	rt = m_ctrl->OnDragDrop(pDataObject,col,row);

	CString string;
	HGLOBAL global{};

#ifdef _UNICODE
	// ask for CF_UNICODETEXT if we can and should handle it.
	if(rt != DROPEFFECT_NONE){
		if(pDataObject->IsDataAvailable(CF_UNICODETEXT,nullptr))
			m_ctrl->GotoCell(col,row);
			LPTSTR   bufu;
			global = pDataObject->GetGlobalData(CF_UNICODETEXT,nullptr);
			bufu = (LPTSTR)GlobalLock(global);
			string = bufu;
			
			m_ctrl->Paste(string);
			return rt;				// no need to go further..
	}
#endif

	// ask for CF_TEXT.  Assignment to CString should
	// convert if we have compiled for _UNICODE - leave
	// the LPSTR declarations!
	if(rt != DROPEFFECT_NONE){
		if(pDataObject->IsDataAvailable(CF_TEXT,nullptr))
			m_ctrl->GotoCell(col,row);
			LPSTR   buf;
			global = pDataObject->GetGlobalData(CF_TEXT,nullptr);
			buf = (LPSTR)GlobalLock(global);
			string = buf;
			
			m_ctrl->Paste(string);
	}

	return rt;
}

/***************************************************
OnDragScroll
	Called by the framework before calling OnDragEnter or
	OnDragOver to determine whether point is in the scrolling 
	region.  The Ultimate Grid will scroll its view when
	user moves mouse within few pixels of the edge of
	the window (defined by nScrollBorder)
Params:
	pWnd		- please see MSDN for explanation of individual
	dwKeyState	  parameter passed in
	point
Returns:
	DROPEFFECT, please see the MSDN for list of possible
	values.
*****************************************************/
DROPEFFECT CUGDropTarget::OnDragScroll( CWnd* pWnd, DWORD dwKeyState, CPoint point )
{
	UNREFERENCED_PARAMETER(pWnd);
	UNREFERENCED_PARAMETER(dwKeyState);

	// establish scroll border (in pixels)
#ifdef UG_DRAGDROP_SCROLL_BORDER
	const int nScrollBorder = UG_DRAGDROP_SCROLL_BORDER;
#else
	int nScrollBorder = 10;
#endif

	CRect rect;
	// get rect of the grid area
	m_ctrl->m_CUGGrid->GetClientRect(&rect);

	if ( point.x < nScrollBorder )
	{	// scroll to the feft
		m_ctrl->SetLeftCol( m_ctrl->GetLeftCol() - 1 );
	}
	else if ( point.x > ( rect.right - nScrollBorder ))
	{	// scroll to the right
		m_ctrl->SetLeftCol( m_ctrl->GetLeftCol() + 1 );
	}
	else if ( point.y < nScrollBorder )
	{	// scroll to the top
		m_ctrl->SetTopRow( m_ctrl->GetTopRow() - 1 );
	}
	else if ( point.y > ( rect.bottom - nScrollBorder ))
	{	// scroll to the bottom
		m_ctrl->SetTopRow( m_ctrl->GetTopRow() + 1 );
	}

	return DROPEFFECT_NONE;
}

#endif	//UG_ENABLE_DRAGDROP