// XTNotify.h : notification handlers
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
#if !defined(__XTNOTIFY_H__)
#define __XTNOTIFY_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//{{AFX_CODEJOCK_PRIVATE
const UINT WM_XTP_CONTROLS_BASE = (WM_USER + 9000);
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_SELCHANGE notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_SELCHANGE notification message is sent to inform
//     the owner window that the current color selection has changed.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_SELCHANGE(IDC_CTRL_ID, OnSelChange)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnSelChange()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_DROPDOWN, CPN_XT_CLOSEUP, CPN_XT_SELENDOK, CPN_XT_SELENDCANCEL, CPN_XT_SELNOFILL
// --------------------------------------------------------------------
const UINT CPN_XT_SELCHANGE = (WM_XTP_CONTROLS_BASE + 1);
//<ALIAS CPN_XT_SELCHANGE>
#define ON_CPN_XT_SELCHANGE(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_SELCHANGE
#define ON_CPN_XT_SELCHANGE(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELCHANGE, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_DROPDOWN notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_DROPDOWN notification message is sent to inform the
//     owner window that the color selection window is has been displayed.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_DROPDOWN(IDC_CTRL_ID, OnDropDown)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnDropDown()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_SELCHANGE, CPN_XT_CLOSEUP, CPN_XT_SELENDOK, CPN_XT_SELENDCANCEL, CPN_XT_SELNOFILL
// --------------------------------------------------------------------
const UINT CPN_XT_DROPDOWN = (WM_XTP_CONTROLS_BASE + 2);
//<ALIAS CPN_XT_DROPDOWN>
#define ON_CPN_XT_DROPDOWN(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_DROPDOWN
#define ON_CPN_XT_DROPDOWN(id, memberFxn) \
	ON_CONTROL(CPN_XT_DROPDOWN, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_CLOSEUP notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_CLOSEUP notification message is sent to inform the
//     owner window that the color selection window has closed.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_CLOSEUP(IDC_CTRL_ID, OnCloseUp)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnCloseUp()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_SELCHANGE, CPN_XT_DROPDOWN, CPN_XT_SELENDOK, CPN_XT_SELENDCANCEL, CPN_XT_SELNOFILL
// --------------------------------------------------------------------
const UINT CPN_XT_CLOSEUP = (WM_XTP_CONTROLS_BASE + 3);
//<ALIAS CPN_XT_CLOSEUP>
#define ON_CPN_XT_CLOSEUP(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_CLOSEUP
#define ON_CPN_XT_CLOSEUP(id, memberFxn) \
	ON_CONTROL(CPN_XT_CLOSEUP, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_SELENDOK notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_SELENDOK notification message is sent to inform the
//     owner window that a color selection has been made.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_SELENDOK(IDC_CTRL_ID, OnSelEndOk)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnSelEndOk()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_SELCHANGE, CPN_XT_DROPDOWN, CPN_XT_CLOSEUP, CPN_XT_SELENDCANCEL, CPN_XT_SELNOFILL
// --------------------------------------------------------------------
const UINT CPN_XT_SELENDOK = (WM_XTP_CONTROLS_BASE + 4);
//<ALIAS CPN_XT_SELENDOK>
#define ON_CPN_XT_SELENDOK(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_SELENDOK
#define ON_CPN_XT_SELENDOK(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELENDOK, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_SELENDCANCEL notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_SELENDCANCEL notification message is sent to inform the
//     owner window that a color selection has been canceled.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_SELENDCANCEL(IDC_CTRL_ID, OnSelEndCancel)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnSelEndCancel()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_SELCHANGE, CPN_XT_DROPDOWN, CPN_XT_CLOSEUP, ON_CPN_XT_SELENDOK, CPN_XT_SELNOFILL
// --------------------------------------------------------------------
const UINT CPN_XT_SELENDCANCEL = (WM_XTP_CONTROLS_BASE + 5);
//<ALIAS CPN_XT_SELENDCANCEL>
#define ON_CPN_XT_SELENDCANCEL(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_SELENDCANCEL
#define ON_CPN_XT_SELENDCANCEL(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELENDCANCEL, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     CPN_XT_SELNOFILL notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The CPN_XT_SELNOFILL notification message is sent to inform the
//     owner window that a "No Fill" or "Automatic Color" selection has been made.
//     The owner window of the color picker receives this notification
//     through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CColorDialog, CDialog
//     //{{AFX_MSG_MAP(CColorDialog)
//     ON_CPN_XT_SELNOFILL(IDC_CTRL_ID, OnSelNoFill)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CColorDialog::OnSelNoFill()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTColorPicker, CXTColorSelectorCtrl, CPN_XT_SELCHANGE, CPN_XT_DROPDOWN, CPN_XT_CLOSEUP, ON_CPN_XT_SELENDOK, CPN_XT_SELENDCANCEL
// --------------------------------------------------------------------
const UINT CPN_XT_SELNOFILL = (WM_XTP_CONTROLS_BASE + 6);
//<ALIAS CPN_XT_SELNOFILL>
#define ON_CPN_XT_SELNOFILL(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_CPN_XT_SELNOFILL
#define ON_CPN_XT_SELNOFILL(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELNOFILL, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------
// Summary:
//     BEN_XT_LABELEDITEND notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The BEN_XT_LABELEDITEND notification message is sent when
//     the user performs a browse operation successfully. It indicates
//     the user's selection is to be processed. The owner window of the
//     browse edit receives this notification through the WM_COMMAND
//     message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CBrowseDialog, CDialog
//     //{{AFX_MSG_MAP(CBrowseDialog)
//     ON_BEN_XT_LABELEDITEND(IDC_CTRL_ID, OnLabelEditEnd)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CBrowseDialog::OnLabelEditEnd()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTBrowseEdit, BEN_XT_LABELEDITCANCEL
// --------------------------------------------------------------------
const UINT BEN_XT_LABELEDITEND = (WM_XTP_CONTROLS_BASE + 7);
//<ALIAS BEN_XT_LABELEDITEND>
#define ON_BEN_XT_LABELEDITEND(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_BEN_XT_LABELEDITEND
#define ON_BEN_XT_LABELEDITEND(id, memberFxn) \
	ON_CONTROL(BEN_XT_LABELEDITEND, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     BEN_XT_LABELEDITCANCEL notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The BEN_XT_LABELEDITCANCEL notification message is sent
//     when the user performs a browse operation, but then selects
//     another control or closes the dialog box. It indicates the user's
//     initial operation was ignored. The owner window of the browse edit
//     receives this notification through the WM_COMMAND message.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CBrowseDialog, CDialog
//     //{{AFX_MSG_MAP(CBrowseDialog)
//     ON_BEN_XT_LABELEDITCANCEL(IDC_CTRL_ID, OnLabelEditCancel)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CBrowseDialog::OnLabelEditCancel()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTBrowseEdit, BEN_XT_LABELEDITEND
// ----------------------------------------------------------------------
const UINT BEN_XT_LABELEDITCANCEL = (WM_XTP_CONTROLS_BASE + 8);
//<ALIAS BEN_XT_LABELEDITCANCEL>
#define ON_BEN_XT_LABELEDITCANCEL(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_BEN_XT_LABELEDITCANCEL
#define ON_BEN_XT_LABELEDITCANCEL(id, memberFxn) \
	ON_CONTROL(BEN_XT_LABELEDITCANCEL, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_LABELEDITEND notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_LABELEDITEND notification message is sent
//     to inform the owner whenever the label edit operation has ended.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_LABELEDITEND(IDC_CTRL_ID, OnLabelEditEnd)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnLabelEditEnd()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const DWORD LBN_XT_LABELEDITEND = BEN_XT_LABELEDITEND;
//<ALIAS LBN_XT_LABELEDITEND>
#define ON_LBN_XT_LABELEDITEND(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_LABELEDITEND
#define ON_LBN_XT_LABELEDITEND(id, memberFxn) \
	ON_CONTROL(LBN_XT_LABELEDITEND, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_LABELEDITCANCEL notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_LABELEDITCANCEL notification message is sent
//     to inform the owner whenever the label edit operation has been canceled.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_LABELEDITCANCEL(IDC_CTRL_ID, OnLabelEditCancel)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnLabelEditCancel()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const DWORD LBN_XT_LABELEDITCANCEL = BEN_XT_LABELEDITCANCEL;
//<ALIAS LBN_XT_LABELEDITCANCEL>
#define ON_LBN_XT_LABELEDITCANCEL(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_LABELEDITCANCEL
#define ON_LBN_XT_LABELEDITCANCEL(id, memberFxn) \
	ON_CONTROL(LBN_XT_LABELEDITCANCEL, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_NEWITEM notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_NEWITEM notification message is sent
//     to inform the owner whenever the new item button has been pressed.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_NEWITEM(IDC_CTRL_ID, OnNewItem)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnNewItem()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const UINT LBN_XT_NEWITEM = (WM_XTP_CONTROLS_BASE + 9);
//<ALIAS LBN_XT_NEWITEM>
#define ON_LBN_XT_NEWITEM(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_NEWITEM
#define ON_LBN_XT_NEWITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_NEWITEM, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_PREDELETEITEM notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_PREDELETEITEM notification message is sent
//     to inform the owner just before an item is deleted.  This is
//     useful for retrieving information about the selected item, such
//     as item data, before it is removed from the edit list control.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_PREDELETEITEM(IDC_CTRL_ID, OnPreDeleteItem)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnPreDeleteItem()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const UINT LBN_XT_PREDELETEITEM = (WM_XTP_CONTROLS_BASE + 10);
//<ALIAS LBN_XT_PREDELETEITEM>
#define ON_LBN_XT_PREDELETEITEM(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_PREDELETEITEM
#define ON_LBN_XT_PREDELETEITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_PREDELETEITEM, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_DELETEITEM notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_DELETEITEM notification message is sent
//     to inform the owner whenever the delete item button has been pressed.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_DELETEITEM(IDC_CTRL_ID, OnDeleteItem)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnDeleteItem()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const UINT LBN_XT_DELETEITEM = (WM_XTP_CONTROLS_BASE + 11);
//<ALIAS LBN_XT_DELETEITEM>
#define ON_LBN_XT_DELETEITEM(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_DELETEITEM
#define ON_LBN_XT_DELETEITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_DELETEITEM, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_MOVEITEMUP notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_MOVEITEMUP notification message is sent
//     to inform the owner whenever the move item up button has been pressed.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_MOVEITEMUP(IDC_CTRL_ID, OnMoveItemUp)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnMoveItemUp()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMDOWN, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const UINT LBN_XT_MOVEITEMUP = (WM_XTP_CONTROLS_BASE + 12);
//<ALIAS LBN_XT_MOVEITEMUP>
#define ON_LBN_XT_MOVEITEMUP(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_MOVEITEMUP
#define ON_LBN_XT_MOVEITEMUP(id, memberFxn) \
	ON_CONTROL(LBN_XT_MOVEITEMUP, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_MOVEITEMDOWN notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_MOVEITEMDOWN notification message is sent
//     to inform the owner whenever the move item down button has been pressed.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_MOVEITEMDOWN(IDC_CTRL_ID, OnMoveItemDown)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnMoveItemDown()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_PRENEWITEM
// ----------------------------------------------------------------------
const UINT LBN_XT_MOVEITEMDOWN = (WM_XTP_CONTROLS_BASE + 13);
//<ALIAS LBN_XT_MOVEITEMDOWN>
#define ON_LBN_XT_MOVEITEMDOWN(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_MOVEITEMDOWN
#define ON_LBN_XT_MOVEITEMDOWN(id, memberFxn) \
	ON_CONTROL(LBN_XT_MOVEITEMDOWN, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_PRENEWITEM notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_PRENEWITEM notification message is sent
//     to inform the owner whenever that a new item is about to be
//     edited in EditListBox.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_LBN_XT_PRENEWITEM(IDC_CTRL_ID, OnPreNewItem)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnPreNewItem()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN
// ----------------------------------------------------------------------
const UINT LBN_XT_PRENEWITEM = (WM_XTP_CONTROLS_BASE + 14);
//<ALIAS LBN_XT_PRENEWITEM>
#define ON_LBN_XT_PRENEWITEM(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_PRENEWITEM
#define ON_LBN_XT_PRENEWITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_PRENEWITEM, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     LBN_XT_ONBROWSE notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The LBN_XT_ONBROWSE notification message is sent
//     to inform the owner when the browse button is pressed.
// See Also:
//     CXTEditListBox, LBN_XT_LABELEDITEND, LBN_XT_LABELEDITCANCEL, LBN_XT_NEWITEM, LBN_XT_PREDELETEITEM, LBN_XT_DELETEITEM, LBN_XT_MOVEITEMUP, LBN_XT_MOVEITEMDOWN
// ----------------------------------------------------------------------
const UINT LBN_XT_ONBROWSE = (WM_XTP_CONTROLS_BASE + 27);
//<ALIAS LBN_XT_ONBROWSE>
#define ON_LBN_XT_ONBROWSE(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_LBN_XT_ONBROWSE
#define ON_LBN_XT_ONBROWSE(id, memberFxn) \
	ON_CONTROL(LBN_XT_ONBROWSE, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     SON_XT_ITEMEXPANDING notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The SON_XT_ITEMEXPANDING notification message is sent
//     to inform the owner whenever the search options control is expanding.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_SON_XT_ITEMEXPANDING(IDC_CTRL_ID, OnItemExpanding)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnItemExpanding()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTSearchOptionsCtrl, SON_XT_ITEMEXPAND, SON_XT_ITEMCONTRACTING, SON_XT_ITEMCONTRACT
// ----------------------------------------------------------------------
const UINT SON_XT_ITEMEXPANDING = (WM_XTP_CONTROLS_BASE + 15);
//<ALIAS SON_XT_ITEMEXPANDING>
#define ON_SON_XT_ITEMEXPANDING(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_SON_XT_ITEMEXPANDING
#define ON_SON_XT_ITEMEXPANDING(id, memberFxn) \
	ON_CONTROL(SON_XT_ITEMEXPANDING, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     SON_XT_ITEMEXPAND notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The SON_XT_ITEMEXPAND notification message is sent
//     to inform the owner whenever the search options control has expanded.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_SON_XT_ITEMEXPAND(IDC_CTRL_ID, OnItemExpand)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnItemExpand()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTSearchOptionsCtrl, SON_XT_ITEMEXPANDING, SON_XT_ITEMCONTRACTING, SON_XT_ITEMCONTRACT
// ----------------------------------------------------------------------
const UINT SON_XT_ITEMEXPAND = (WM_XTP_CONTROLS_BASE + 16);
//<ALIAS SON_XT_ITEMEXPAND>
#define ON_SON_XT_ITEMEXPAND(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_SON_XT_ITEMEXPAND
#define ON_SON_XT_ITEMEXPAND(id, memberFxn) \
	ON_CONTROL(SON_XT_ITEMEXPAND, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     SON_XT_ITEMCONTRACTING notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The SON_XT_ITEMCONTRACTING notification message is sent
//     to inform the owner whenever the search options control is contracting.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_SON_XT_ITEMCONTRACTING(IDC_CTRL_ID, OnItemContracting)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnItemContracting()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTSearchOptionsCtrl, SON_XT_ITEMEXPANDING, SON_XT_ITEMEXPAND, SON_XT_ITEMCONTRACT
// ----------------------------------------------------------------------
const UINT SON_XT_ITEMCONTRACTING = (WM_XTP_CONTROLS_BASE + 17);
//<ALIAS SON_XT_ITEMCONTRACTING>
#define ON_SON_XT_ITEMCONTRACTING(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_SON_XT_ITEMCONTRACTING
#define ON_SON_XT_ITEMCONTRACTING(id, memberFxn) \
	ON_CONTROL(SON_XT_ITEMCONTRACTING, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     SON_XT_ITEMCONTRACT notification message handler.
// Parameters:
//     id -         Resource ID for the control.
//     memberFxn -  Name of member function to handle the message.
// Remarks:
//     The SON_XT_ITEMCONTRACT notification message is sent
//     to inform the owner whenever the search options control has contracted.
// Example:
//     Here is an example of how an application would handle this message.
// <code>
// BEGIN_MESSAGE_MAP(CAppDialog, CDialog
//     //{{AFX_MSG_MAP(CAppDialog)
//     ON_SON_XT_ITEMCONTRACT(IDC_CTRL_ID, OnItemContract)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CAppDialog::OnItemContract()
// {
//     // TODO: Handle command.
// }
// </code>
// See Also:
//     CXTSearchOptionsCtrl, SON_XT_ITEMEXPANDING, SON_XT_ITEMEXPAND, SON_XT_ITEMCONTRACTING
// ----------------------------------------------------------------------
const UINT SON_XT_ITEMCONTRACT = (WM_XTP_CONTROLS_BASE + 18);
//<ALIAS SON_XT_ITEMCONTRACT>
#define ON_SON_XT_ITEMCONTRACT(id, memberFxn)
//{{AFX_CODEJOCK_PRIVATE
#undef ON_SON_XT_ITEMCONTRACT
#define ON_SON_XT_ITEMCONTRACT(id, memberFxn) \
	ON_CONTROL(SON_XT_ITEMCONTRACT, id, memberFxn)
//}}AFX_CODEJOCK_PRIVATE

// --------------------------------------------------------------------------------------------
// Summary:
//     The XTWM_OUTBAR_NOTIFY message is sent to the outlook bar
//     owner window whenever an action occurs within the control.
// Parameters:
//     nBarAction -  (int) wParam; - value of <i>wParam</i> specifies an Outlook bar
//                   value that indicates the users request. This parameter can be
//                   one of the values listed in the Remarks section.
//     pOBInfo -     pOBInfo (XT_OUTBAR_INFO*) lParam; - value of <i>lParam</i>
//                   points to an XT_OUTBAR_INFO structure that contains
//                   information for the specified item. The item can either be a
//                   folder group or icon item, depending on the value of the <i>nBarAction</i>
//                   parameter. This pointer should never be NULL.
// Remarks:
//     When the user performs an action in the Outlook bar, the XTWM_OUTBAR_NOTIFY
//     message is sent to the Outlook bar's owner window. nBarAction can be one of
//     the following values:<p/>
//
//     * <b>OBN_XT_ITEMCLICK</b> The user has selected an item in the
//       Outlook bar.
//     * <b>OBN_XT_ONLABELENDEDIT</b> The user has completed editing an
//       item's label.
//     * <b>OBN_XT_ONGROUPENDEDIT</b> The user has completed editing a
//       folder's label.
//     * <b>OBN_XT_DRAGITEM</b> The user has dragged an item to a new
//       location in the Outlook bar.
//     * <b>OBN_XT_FOLDERCHANGE</b> The user has selected a new folder
//       item.
//     * <b>OBN_XT_ITEMHOVER</b> The user's mouse is hovering over an
//       item in the Outlook bar.
//     * <b>OBN_XT_DELETEITEM</b> The user has chosen to delete an item
//       from the Outlook bar.
//     * <b>OBN_XT_DELETEFOLDER</b> The user has chosen to delete a
//       folder from the Outlook bar.
//     * <b>OBN_XT_ITEMRCLICK</b> The user has right clicked on the
//       Outlook bar folder.
// Returns:
//     If the application is to process this message, the return value
//     should be TRUE. If the return value is FALSE, the user's action is
//     ignored.
// Example:
//     Here is an example of how an application would process the XTWM_OUTBAR_NOTIFY
//     message.
// <code>
// int nBarAction = (int)wParam;
//
// // Cast the lParam to an XT_OUTBAR_INFO* struct pointer.
// XT_OUTBAR_INFO* pOBInfo = (XT_OUTBAR_INFO*)lParam;
// ASSERT(pOBInfo);
//
// switch (nBarAction)
// {
//     case OBN_XT_ITEMCLICK:
//     case OBN_XT_FOLDERCHANGE:
//     case OBN_XT_ONLABELENDEDIT:
//     case OBN_XT_ONGROUPENDEDIT:
//     case OBN_XT_DRAGITEM:
//     case OBN_XT_ITEMHOVER:
//     case OBN_XT_ITEMRCLICK:
//         TRACE2("Index: %d, Name: %s.\\n", pOBInfo-\>nIndex, pOBInfo-\>lpszText);
//         break;
//
//     case OBN_XT_DELETEITEM:
//         if (AfxMessageBox(_T("Remove this folder shortcut?"),
//             MB_ICONWARNING | MB_YESNO) == IDNO)
//         {
//             return FALSE; // Return FALSE to abort the action.
//         }
//         break;
//
//     case OBN_XT_DELETEFOLDER:
//         if (AfxMessageBox(_T("Remove the specified folder?"),
//             MB_ICONWARNING | MB_YESNO) == IDNO)
//         {
//             return FALSE; // Return FALSE to abort the action.
//         }
//         break;
// }
// return TRUE;
// </code>
// See Also:
//     CXTMenuListBox, CXTOutBarCtrl
// --------------------------------------------------------------------------------------------
const UINT XTWM_OUTBAR_NOTIFY = (WM_XTP_CONTROLS_BASE + 19);
const int OBN_XT_ITEMCLICK        = 1; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_ONLABELENDEDIT   = 2; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_ONGROUPENDEDIT   = 3; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_DRAGITEM         = 4; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_FOLDERCHANGE     = 5; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_ITEMHOVER        = 6; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_DELETEITEM       = 7; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_DELETEFOLDER     = 8; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_BEGINDRAG        = 9; //<ALIAS XTWM_OUTBAR_NOTIFY>
const int OBN_XT_ITEMRCLICK       =10; //<ALIAS XTWM_OUTBAR_NOTIFY>

// ----------------------------------------------------------------------------------------------------
// Summary:
//     The XTWM_SHELL_NOTIFY message is sent to the CXTShellTreeCtrl
//     or CXTShellListCtrl owner whenever an action occurs within
//     the control.
// Parameters:
//     nShellAction -  (int) wParam; - value of <i>wParam</i> specifies a shell tree
//                     value that indicates the users request. See Remarks section for a list of values.
//     pItemData -     (XT_TVITEMDATA*) lParam; - value of <i>lParam</i> points to an XT_TVITEMDATA
//                     structure that contains information for the specified item.
//                     Depending on the action, this pointer can be NULL.
// Remarks:
//     When the user performs an action in the shell tree, the XTWM_SHELL_NOTIFY
//     message is sent to the shell tree's owner window.<p/>
//
//     The nShellAction parameter can be one of the following values:<p/>
//
//      * <b>SHN_XT_SHELLMENU</b> Shell context menu selection made.
//      * <b>SHN_XT_TREESELCHANGE</b> Tree selection made.
//      * <b>SHN_XT_SELECTCHILD</b> Child tree node selected.
//      * <b>SHN_XT_NOFOLDER</b> Item selected was not a folder.
//      * <b>SHN_XT_INETFOLDER</b> Item selected was the Internet
//        folder.
//      * <b>SHN_XT_CONTENTSCHANGED</b> Indicates the folder's contents
//        have changed.
//      * <b>SHN_XT_REFRESHFOLDER</b> Indicates the folder needs to be
//        updated.
//      * <b>SHN_XT_REFRESHTREE</b> Indicates the tree needs to be
//        updated.
// Returns:
//     If the application is to process this message, the return value
//     should be 0.
// Example:
//     Here is an example of how an application would process the XTWM_SHELL_NOTIFY
//     message.
// <code>
// int nShellAction = (int)wParam;
//
// // Cast the lParam to an XT_TVITEMDATA* struct pointer.
// XT_TVITEMDATA* pItemData = (XT_TVITEMDATA*)lParam;
// ASSERT(pItemData);
//
// switch (nShellAction)
// {
//     case SHN_XT_SHELLMENU:
//     case SHN_XT_TREESELCHANGE:
//     case SHN_XT_SELECTCHILD:
//     case SHN_XT_NOFOLDER:
//     case SHN_XT_INETFOLDER:
//     case SHN_XT_CONTENTSCHANGED:
//     case SHN_XT_REFRESHFOLDER:
//     case SHN_XT_REFRESHTREE:
//         // TODO: Handle shell notification message.
//         TRACE0("Shell notification was sent.n");
//         break;
// }
// return 0;
// </code>
// See Also:
//     CXTShellTreeCtrl, CXTShellListCtrl, CXTShellListBase,
//     CXTDirWatcher
// ----------------------------------------------------------------------------------------------------
const UINT XTWM_SHELL_NOTIFY = (WM_XTP_CONTROLS_BASE + 20);
const int SHN_XT_SHELLMENU       = 1; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_TREESELCHANGE   = 2; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_SELECTCHILD     = 3; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_NOFOLDER        = 4; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_INETFOLDER      = 5; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_CONTENTSCHANGED = 6; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_REFRESHFOLDER   = 7; //<ALIAS XTWM_SHELL_NOTIFY>
const int SHN_XT_REFRESHTREE     = 8; //<ALIAS XTWM_SHELL_NOTIFY>

// -------------------------------------------------------------------------------------
// Summary:
//     The TIN_XT_TRAYICON message is sent to the CXTTrayIcon
//     window's owner whenever a mouse event occurs in the CXTTrayIcon.
// Parameters:
//     uID -        (UINT) wParam; - value of <i>wParam</i> specifies the
//                  resource ID of the icon associated with the CXTTrayIcon
//                  object.
//     uMouseMsg -  (UINT) lParam; - value of <i>lParam</i> specifies the mouse
//                  or keyboard message associated with the event.
// Remarks:
//     When a mouse or keyboard event occurs on a tray icon, the TIN_XT_TRAYICON
//     message is sent to the tray icon's owner window.
// Returns:
//     If the application is to process this message, the return value
//     should be 0.
// Example:
//     Here is an example of how an application would process the TIN_XT_TRAYICON
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//     //{{AFX_MSG_MAP(CMainFrame)
//     ON_MESSAGE(TIN_XT_TRAYICON, OnTrayIconNotify)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// LRESULT CMainFrame::OnTrayIconNotify(WPARAM wParam, LPARAM lParam)
// {
//     UINT uID = (UINT) wParam;        // resource ID of the tray icon.
//     UINT uMouseMsg = (UINT) lParam;  // mouse message that was sent.
//
//     switch (uMouseMsg)
//     {
//         case WM_RBUTTONUP:
//         {
//             CMenu menu;
//             VERIFY(menu.LoadMenu(IDR_MAINFRAME));
//
//             CMenu* pPopup = menu.GetSubMenu(0);
//             ASSERT(pPopup != NULL);
//             CWnd* pWndPopupOwner = this;
//
//             // Insert the restore menu command into the popup.
//             if (m_bIsVisible == false)
//             {
//                 pPopup-\>InsertMenu(0, MF_BYPOSITION,
//                     IDR_RESTORE, _T("&Restore Window..."));
//
//                 pPopup-\>InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR,
//                     IDR_RESTORE);
//
//                 // Make restore command bold.
//                 \::SetMenuDefaultItem(pPopup-\>m_hMenu, IDR_RESTORE, FALSE);
//             }
//             else
//             {
//                 // Make the exit command bold.
//                 \::SetMenuDefaultItem(pPopup-\>m_hMenu, ID_APP_EXIT, FALSE);
//             }
//
//             // Display the menu at the current mouse location. There's a "bug"
//             // (Microsoft calls it a feature) in Windows 95 that requires calling
//             // SetForegroundWindow. To find out more, search for Q135788 in MSDN.
//             //
//             CPoint point;
//             GetCursorPos(&point);
//             \::SetForegroundWindow(m_hWnd);
//
//             while (pWndPopupOwner-\>GetStyle() & WS_CHILD)
//                 pWndPopupOwner = pWndPopupOwner-\>GetParent();
//
//             int iCmd = pPopup-\>TrackPopupMenu(
//                 TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON,
//                 point.x, point.y, pWndPopupOwner);
//
//             // at this point we want to make sure that the app is visible
//             // after the user makes a menu selection - this is just one way
//             // of doing so:
//
//             switch (iCmd)
//             {
//                 case 0:
//                     // user canceled menu - do nothing
//                     break;
//
//                 // these are commands for which we don't need to make the
//                 // main app window visible
//                 case ID_APP_EXIT:
//                     PostMessage(WM_COMMAND, iCmd, 0);  // just post the command
//                     break;
//
//                 // for all other menu commands - make sure the window is
//                 // visible before we continue
//                 default:
//                     // make main window visible
//                     OnRestore();
//                     PostMessage(WM_COMMAND, iCmd, 0); // post the command
//                     break;
//             }
//
//             return 1; // let the tray icon know that we handled this message.
//         }
//
//         case WM_LBUTTONDBLCLK:
//             OnRestore();
//             return 1; // let the tray icon know that we handled this message.
//     }
//
//     return 0;
// }
// </code>
// See Also:
//     CXTTrayIcon
// -------------------------------------------------------------------------------------
const UINT TIN_XT_TRAYICON = (WM_XTP_CONTROLS_BASE + 21);

// ----------------------------------------------------------------------
// Summary:
//     The CPWN_XT_PUSHPINBUTTON message is sent to the owner of a CXTCaptionPopupWnd whenever
//     the push pin button selection has been made.
// Remarks:
//     When the user makes a selection of the push pin button, the CPWN_XT_PUSHPINBUTTON message is
//     sent to the caption popup window's owner window.
// Example:
//     Here is an example of how an application would process the TCN_XT_SELCHANGE
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//     //{{AFX_MSG_MAP(CMainFrame)
//     ON_MESSAGE_VOID(CPWN_XT_PUSHPINBUTTON, OnPushPinButton)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CMainFrame::OnPushPinButton()
// {
//     // TODO: Add your message handler code here and/or call default
//     m_wndSplitter2.ShowColumn();
//     m_nColumn = 1;
// }
// </code>
// See Also:
//     CXTCaption, CXTCaptionPopupWnd
// ----------------------------------------------------------------------
const UINT CPWN_XT_PUSHPINBUTTON = (WM_XTP_CONTROLS_BASE + 22);

// ----------------------------------------------------------------------
// Summary:
//     The CPWN_XT_PUSHPINCANCEL message is sent to the owner of a CXTCaptionPopupWnd whenever
//     the push pin button selection has been canceled.
// Remarks:
//     When the user cancels a selection of the push pin button, the CPWN_XT_PUSHPINCANCEL message is
//     sent to the caption popup window's owner window.
// Example:
//     Here is an example of how an application would process the TCN_XT_SELCHANGE
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//     //{{AFX_MSG_MAP(CMainFrame)
//     ON_MESSAGE_VOID(CPWN_XT_PUSHPINCANCEL, OnPushPinCancel)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// void CMainFrame::OnPushPinCancel()
// {
//     // TODO: Add your message handler code here and/or call default
// }
// </code>
// See Also:
//     CXTCaption, CXTCaptionPopupWnd
// ----------------------------------------------------------------------
const UINT CPWN_XT_PUSHPINCANCEL = (WM_XTP_CONTROLS_BASE + 23);

//{{AFX_CODEJOCK_PRIVATE
const UINT TCN_XT_SELCHANGE   = (WM_XTP_CONTROLS_BASE + 24); // deprecated, use TCN_SELCHANGE instead.
const UINT TCN_XT_SELCHANGING = (WM_XTP_CONTROLS_BASE + 25); // deprecated, use TCN_SELCHANGING instead.
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     The XTWM_UPDATECOLOR message is used to send notification that
//     the color selection has changed.
// Parameters:
//     crNew - (COLORREF) wParam; - newly selected RGB color.
// Remarks:
//     This message is sent to notify the owner that a color selection has changed.
// Example:
//     Here is an example of how an application would process the XTWM_UPDATECOLOR
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CXTColorPageCustom, CXTThemePropertyPage)
//     //{{AFX_MSG_MAP(CMainFrame)
//      ON_MESSAGE(XTWM_UPDATECOLOR, OnUpdateColor)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// LRESULT CXTColorPageCustom::OnUpdateColor(WPARAM wParam, LPARAM lParam)
// {
//     UNUSED_ALWAYS(lParam);
//     COLORREF crNew = (COLORREF)wParam;
// }
// </code>
// See Also:
//     CXTColorDialog, CXTColorBase, CXTColorLum, CXTColorPageCustom, CXTColorHex, CXTColorPageStandard
// ----------------------------------------------------------------------
const DWORD XTWM_UPDATECOLOR = (WM_XTP_CONTROLS_BASE + 26);

// ----------------------------------------------------------------------
// Input:   bHorz - TRUE if horizontally oriented, FALSE otherwise.
//          pRBBI - A pointer to a BARBANDINFO structure, the window can modify its parameters as appropriate.
//
// Returns: If the application is to process this message, the return value should be TRUE.
//
// Remarks: When a window is added to a rebar, the XTWM_ADDREBAR message is sent to the window.
//
// Example: Here is an example of how an application would process the XTWM_ADDREBAR
//          message.
//
//          <pre>BEGIN_MESSAGE_MAP(CWidget, CWnd)
//              //{{AFX_MSG_MAP(CWidget)
//              ON_MESSAGE(XTWM_ADDREBAR, OnAddReBar)
//              //}}AFX_MSG_MAP
//          END_MESSAGE_MAP()</pre>
//
//          <pre>LRESULT CWidget::OnAddReBar(WPARAM wParam, LPARAM lParam)
//          {
//              BOOL bHorz = (BOOL) wParam;
//
//              REBARBANDINFO* pRBBI = (REBARBANDINFO*) lParam;
//                  // TODO: Handle message.
//
//              return TRUE;
//          }</pre>
// Summary: The XTWM_ADDREBAR message is sent to a window whenever it is added
//          to a CXTReBar control.
//
//          <pre>XTWM_ADDREBAR
//          bHorz = (BOOL) wParam;            // TRUE if horizontal.
//          pRBBI = (REBARBANDINFO*) lParam;  // Points to a REBARBANDINFO structure.</pre>
// ----------------------------------------------------------------------
const UINT XTWM_ADDREBAR = (WM_XTP_CONTROLS_BASE + 27);

// ----------------------------------------------------------------------
// Input:   pNMTB - Value of wParam specifies a NMTOOLBAR structure that represents the toolbar
//          Button where the dropdown event occurred.
//
//          pRect - Value of lParam points to a CRect object that represents the size and location
//          of the toolbar button where the dropdown event occurred.
//
// Returns: Dropdown is displaying a modal window, the return value should be 0, otherwise
//          return 1 for menu style displays.
//
// Remarks: When the user clicks on a dropdown arrow for a toolbar button, the CBRN_XT_DROPDOWN
//          message is sent to the toolbar's owner window.
//
// Example: Here is an example of how an application would process the CBRN_XT_DROPDOWN
//          message.
//
//          <pre>BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//              //{{AFX_MSG_MAP(CMainFrame)
//              ON_MESSAGE(CBRN_XT_DROPDOWN, OnDropDown)
//              //}}AFX_MSG_MAP
//          END_MESSAGE_MAP()</pre>
//
//          <pre>LRESULT CMainFrame::OnDropDown(WPARAM wParam, LPARAM lParam)
//          {
//              NMTOOLBAR* pNMTB = (NMTOOLBAR*)wParam;
//              ASSERT(pNMTB != NULL);
//
//              CRect* pRect = (CRect*)lParam;
//              ASSERT(pRect != NULL);
//
//              // TODO: Handle toolbar dropdown notification (click on REDO drop arrow).
//
//              return 0;
//          }</pre>
// Summary: The CBRN_XT_DROPDOWN message is sent to the CXTToolBar window
//          whenever a dropdown event occurs in the CXTToolBar.
//
//          <pre>CBRN_XT_DROPDOWN
//          pNMTB = (NMTOOLBAR*)wParam;  // pointer to a NMTOOLBAR struct
//          pRect = (CRect*)lParam;      // pointer to a CRect object</pre>
// ----------------------------------------------------------------------
const UINT CBRN_XT_DROPDOWN = (WM_XTP_CONTROLS_BASE + 28);

// ----------------------------------------------------------------------
// Input:   bHorz - TRUE if horizontally oriented, FALSE otherwise.
//          pRBSCI - A pointer to an XT_REBARSIZECHILDINFO structure, the window can modify its parameters as appropriate.
//
// Returns: If the application is to process this message, the return value should be TRUE.
//
// Remarks: When a window is added to a rebar, the XTWM_REBAR_SIZECHILD message is sent to the window.
//
// Example: Here is an example of how an application would process the XTWM_REBAR_SIZECHILD
//          message.
//
//          <pre>BEGIN_MESSAGE_MAP(CWidget, CWnd)
//              //{{AFX_MSG_MAP(CWidget)
//              ON_MESSAGE(XTWM_REBAR_SIZECHILD, OnReBarSizeChild)
//              //}}AFX_MSG_MAP
//          END_MESSAGE_MAP()</pre>
//
//          <pre>LRESULT CWidget::OnReBarSizeChild(WPARAM wParam, LPARAM lParam)
//          {
//              BOOL bHorz = (BOOL) wParam;
//
//              XT_REBARSIZECHILDINFO* pRBSCI = (XT_REBARSIZECHILDINFO*) lParam;
//                  // TODO: Handle message.
//
//              return TRUE;
//          }</pre>
// Summary: The XTWM_REBAR_SIZECHILD message is sent when CXTReBar control has resized
//          the band in which the recipient resides.
//
//          <pre>XTWM_REBAR_SIZECHILD
//          bHorz = (BOOL) wParam; // TRUE if horizontal.
//          pRBSCI = (XT_REBARSIZECHILDINFO*) lParam;  // Points to an XT_REBARSIZECHILDINFO structure.</pre>
// ----------------------------------------------------------------------
const UINT XTWM_REBAR_SIZECHILD = (WM_XTP_CONTROLS_BASE + 29);

// ----------------------------------------------------------------------
// Returns: TRUE if the control bar shall be fully visualized, FALSE if just a wire frame must be rendered.
//
// Remarks: When a control bar is dragged the XTWM_QUERYVISUALIZE message is sent to the control bar.
//
// Example: Here is an example of how an application would process the XTWM_QUERYVISUALIZE
//          message.
//
//          <pre>BEGIN_MESSAGE_MAP(CWidget, CXTControlBar)
//              //{{AFX_MSG_MAP(CWidget)
//              ON_MESSAGE(XTWM_QUERYVISUALIZE, OnQueryVisualize)
//              //}}AFX_MSG_MAP
//          END_MESSAGE_MAP()</pre>
//
//          <pre>LRESULT CWidget::OnQueryVisualize(WPARAM wParam, LPARAM lParam)
//          {
//              UNREFERENCED_PARAMETER(wParam);
//              UNREFERENCED_PARAMETER(lParam);
//              // Allow full visualizations.
//              return TRUE;
//          }</pre>
// Summary: CXTDockContext sends the XTWM_QUERYVISUALIZE message to a control bar to
//          check if the control bar shall be visualized while dragging or just a wire
//          frame shall be rendered.
//
//          <pre>XTWM_QUERYVISUALIZE
//          wParam - not used, must be zero
//          lParam - not used, must be zero</pre>
// ----------------------------------------------------------------------
const UINT XTWM_QUERYVISUALIZE = (WM_XTP_CONTROLS_BASE + 30);

// ----------------------------------------------------------------------
// Returns: TRUE if control bar has a hot spot, FALSE if it does not.
//
// Remarks: CXTDockContext sends the XTWM_QUERYHOTSPOT message the control bar to check
//          for a hot spot.
//
// Example: Here is an example of how an application would process the XTWM_QUERYHOTSPOT
//          message.
//
//          <pre>BEGIN_MESSAGE_MAP(CWidget, CXTControlBar)
//              //{{AFX_MSG_MAP(CWidget)
//              ON_MESSAGE(XTWM_QUERYHOTSPOT, OnQueryHotSpot)
//              //}}AFX_MSG_MAP
//          END_MESSAGE_MAP()</pre>
//
//          <pre>LRESULT CWidget::OnQueryHotSpot(WPARAM wParam, LPARAM lParam)
//          {
//              UNREFERENCED_PARAMETER(wParam);
//              LPSIZE lpSize = (LPSIZE) lParam;  // Points to a LPSIZE structure.
//              // TODO: Handle message.
//              return TRUE;
//          }</pre>
// Summary: CXTDockContext sends the XTWM_QUERYHOTSPOT message to a control bar to
//          check if the control bar has a hot spot, a point that must match the position
//          of the cursor.
//
//          <pre>XTWM_QUERYHOTSPOT
//          wParam - not used, must be zero
//          lpSize = (LPSIZE) lParam;  // IN  - Extent of the rectangle in which
//                                     //       hot spot is to be defined
//                                     // OUT - Offset of the hot spot location
//                                     //       within the rectangle.</pre>
// ----------------------------------------------------------------------
const UINT XTWM_QUERYHOTSPOT = (WM_XTP_CONTROLS_BASE + 31);

//{{AFX_CODEJOCK_PRIVATE
// ----------------------------------------------------------------------
// used internally - notifies rebar control that the ideal size of the
// embedded control has changed.
// wParam - control's handle, HWND
// lParam - new ideal size, UINT
// Return value is ignored.
// ----------------------------------------------------------------------
const UINT XTWM_IDEALSIZECHANGED = (WM_XTP_CONTROLS_BASE + 32);
//}}AFX_CODEJOCK_PRIVATE

// ----------------------------------------------------------------------
// Summary:
//     The XTWM_EYEDROPPER_MOVING message is sent to the owner of a CXTEyeDropper
//     control whenever the mouse moves over a color on the screen.
// Example:
//     Here is an example of how an application would process the XTWM_EYEDROPPER_MOVING
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//     //{{AFX_MSG_MAP(CMainFrame)
//     ON_MESSAGE(XTWM_EYEDROPPER_MOVING, OnEyeDropperMoving)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// LRESULT CTestDialogDlg::OnEyeDropperMoving(WPARAM wParam, LPARAM lParam)
// {
//     COLORREF color = (WPARAM)wParam;
//
//     CPoint pt;
//     pt.x = LOWORD(lParam);
//     pt.y = HIWORD(lParam);
//
//     return 0;
// }
// </code>
// See Also:
//     CXTEyeDropper, CXTColorDialog, XTWM_EYEDROPPER_SELECT
// ----------------------------------------------------------------------
const UINT XTWM_EYEDROPPER_MOVING = (WM_XTP_CONTROLS_BASE + 33);

// ----------------------------------------------------------------------
// Summary:
//     The XTWM_EYEDROPPER_SELECT message is sent to the owner of a CXTEyeDropper
//     control whenever the user selects a color on the screen.
// Example:
//     Here is an example of how an application would process the XTWM_EYEDROPPER_SELECT
//     message.
// <code>
// BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
//     //{{AFX_MSG_MAP(CMainFrame)
//     ON_MESSAGE(XTWM_EYEDROPPER_SELECT, OnEyeDropperSelect)
//     //}}AFX_MSG_MAP
// END_MESSAGE_MAP()
//
// LRESULT CTestDialogDlg::OnEyeDropperSelect(WPARAM wParam, LPARAM lParam)
// {
//     COLORREF color = (WPARAM)wParam;
//
//     CPoint pt;
//     pt.x = LOWORD(lParam);
//     pt.y = HIWORD(lParam);
//
//     return 0;
// }
// </code>
// See Also:
//     CXTEyeDropper, CXTColorDialog, XTWM_EYEDROPPER_MOVING
// ----------------------------------------------------------------------
const UINT XTWM_EYEDROPPER_SELECT = (WM_XTP_CONTROLS_BASE + 34);

//////////////////////////////////////////////////////////////////////

#endif // #if !defined(__XTNOTIFY_H__)
