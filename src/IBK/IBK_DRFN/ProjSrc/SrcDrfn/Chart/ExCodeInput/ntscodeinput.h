#if !defined(AFX_NTSCODEINPUT_H__D07C732E_15EF_41A6_9026_9D57A65048B6__INCLUDED_)
#define AFX_NTSCODEINPUT_H__D07C732E_15EF_41A6_9026_9D57A65048B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CNtsCodeInput wrapper class

class CNtsCodeInput : public CWnd
{
protected:
	DECLARE_DYNCREATE(CNtsCodeInput)
public:
	~CNtsCodeInput();

	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xe2de771c, 0x6238, 0x435f, { 0x9d, 0xe8, 0x7b, 0xe, 0x60, 0x8f, 0xa9, 0x17 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL);
//	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL);
//	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
//		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	unsigned long GetBackColor();
	void SetBackColor(unsigned long);
	CString GetCodeChoice();
	void SetCodeChoice(LPCTSTR);
	CString GetCodeCtrlName();
	void SetCodeCtrlName(LPCTSTR);
	BOOL GetCodeDrop();
	void SetCodeDrop(BOOL);
	BOOL GetCodeHistory();
	void SetCodeHistory(BOOL);
	BOOL GetCodeTable();
	void SetCodeTable(BOOL);
	CString GetCustomFont();
	void SetCustomFont(LPCTSTR);
	short GetFireOnCharAtPos();
	void SetFireOnCharAtPos(short);
	unsigned long GetForeColor();
	void SetForeColor(unsigned long);
	CString GetImgDropD();
	void SetImgDropD(LPCTSTR);
	CString GetImgDropE();
	void SetImgDropE(LPCTSTR);
	CString GetImgHelpD();
	void SetImgHelpD(LPCTSTR);
	CString GetImgHelpE();
	void SetImgHelpE(LPCTSTR);
	CString GetImgHistoryD();
	void SetImgHistoryD(LPCTSTR);
	CString GetImgHistoryE();
	void SetImgHistoryE(LPCTSTR);
	short GetMaxHistoryCount();
	void SetMaxHistoryCount(short);
	short GetMaxLength();
	void SetMaxLength(short);
	short GetMinLength();
	void SetMinLength(short);
	BOOL GetMoveTab();
	void SetMoveTab(BOOL);
	CString GetOutCtrlName();
	void SetOutCtrlName(LPCTSTR);
	CString GetRootPath();
	void SetRootPath(LPCTSTR);
	CString GetTrCode();
	void SetTrCode(LPCTSTR);
	short GetUpperCase();
	void SetUpperCase(short);
	BOOL GetWhenEqual();
	void SetWhenEqual(BOOL);
	CString GetSGlobalSharedList();
	void SetSGlobalSharedList(LPCTSTR);
	CString GetSLocalSharedList();
	void SetSLocalSharedList(LPCTSTR);
	short GetUserBackColor();
	void SetUserBackColor(short);
	short GetUserForeColor();
	void SetUserForeColor(short);
	long GetCtlAddress();
	void SetCtlAddress(long);
	BOOL GetUseColorTable();
	void SetUseColorTable(BOOL);
	BOOL GetInputRequire();
	void SetInputRequire(BOOL);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	BOOL GetHide();
	void SetHide(BOOL);
	CString GetComment();
	void SetComment(LPCTSTR);
	CString GetControlID();
	void SetControlID(LPCTSTR);
	OLE_HANDLE GetHWnd();
	void SetHWnd(OLE_HANDLE);
	long GetTabKeyStop();
	void SetTabKeyStop(long);
	long GetUseDefaultFont();
	void SetUseDefaultFont(long);
	BOOL GetUseExtCode();
	void SetUseExtCode(BOOL);
	CString GetExtCodeProp();
	void SetExtCodeProp(LPCTSTR);
	CString GetExtCodeName();
	void SetExtCodeName(LPCTSTR);
	long GetCtlPtr();
	void SetCtlPtr(long);
	CString GetColName1();
	void SetColName1(LPCTSTR);
	CString GetColName2();
	void SetColName2(LPCTSTR);
	BOOL GetUseExtOption();
	void SetUseExtOption(BOOL);

// Operations
public:
	CString GetDataText();
	void SetDataText(LPCTSTR szText);
	BOOL SetAllProperties2(long dwData);
	void SetBaseDesk(long lKey);
	long GetBase(LPCTSTR szKey);
	void SetCodeKey(LPCTSTR szKey);
	void SetCurSel(short index);
	CString GetMaxHangSaGa();
	short GetGubunFromCode(LPCTSTR szCode);
	BOOL GetHistoryInfo(short nIndex, BSTR* bstrName, BSTR* bstrCode);
	CString GetDataTextRaw();
	void MakeSaveShortKey(LPCTSTR szFileName, long nFlag);
	CString GetDataFromPopupList(long nRow, long nColumn);
	long OnReceiveFetchData(long pData);
	void SetRscMng(long lKey);
	void SetDataText2(LPCTSTR szCode);
	void SetBasePath(LPCTSTR szPath);
	long GetAllProperties2(long lpData);
	long GetBasePropIf();
	CString GetHistoryAll();

//{{ Dispid 자동처리
public:
	// 1. Create 루틴 2개 Modify

	// 2. 변수선언. m_pdID, m_osInterfaceName[]
	DISPID*			m_pdID;
	static OLECHAR *	m_osInterfaceName[];
	
	// 3. enum 추가
	typedef enum {
	// Attributes
		IIx_BackColor = 0,
		IIx_CodeChoice,
		IIx_CodeCtrlName,
		IIx_CodeDrop,
		IIx_CodeHistory,
		IIx_CodeTable,
		IIx_CustomFont,
		IIx_FireOnCharAtPos,
		IIx_ForeColor,
		IIx_ImgDropD,
		IIx_ImgDropE,
		IIx_ImgHelpD,
		IIx_ImgHelpE,
		IIx_ImgHistoryD,
		IIx_ImgHistoryE,
		IIx_MaxHistoryCount,
		IIx_MaxLength,
		IIx_MinLength,
		IIx_MoveTab,
		IIx_OutCtrlName,
		IIx_RootPath,
		IIx_TrCode,
		IIx_UpperCase,
		IIx_WhenEqual,
		IIx_SGlobalSharedList,
		IIx_SLocalSharedList,
		IIx_UserBackColor,
		IIx_UserForeColor,
		IIx_CtlAddress,
		IIx_UseColorTable,
		IIx_InputRequire,
		IIx_Enabled,
		IIx_Hide,
		IIx_Comment,
		IIx_ControlID,
		IIx_HWnd,
		IIx_TabKeyStop,
		IIx_UseDefaultFont,
		IIx_UseExtCode,
		IIx_ExtCodeProp,
		IIx_ExtCodeName,
		IIx_CtlPtr,
		IIx_ColName1,
		IIx_ColName2,
		IIx_UseExtOption,
	// Operations
		IIx_GetDataText,
		IIx_SetDataText,
		IIx_SetAllProperties2,
		IIx_SetBaseDesk,
		IIx_GetBase,
		IIx_SetCodeKey,
		IIx_SetCurSel,
		IIx_GetMaxHangSaGa,
		IIx_GetGubunFromCode,
		IIx_GetHistoryInfo,
		IIx_GetDataTextRaw,
		IIx_MakeSaveShortKey,
		IIx_GetDataFromPopupList,
		IIx_OnReceiveFetchData,
		IIx_SetRscMng,
		IIx_SetDataText2,
		IIx_SetBasePath,
		IIx_GetAllProperties2,
		IIx_GetBasePropIf,
		IIx_GetHistoryAll
	};
//}} Dispid자동처리
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTSCODEINPUT_H__D07C732E_15EF_41A6_9026_9D57A65048B6__INCLUDED_)
