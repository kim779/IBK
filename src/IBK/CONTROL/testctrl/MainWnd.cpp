// MainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "testctrl.h"
#include "MainWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainWnd

CMainWnd::CMainWnd(CWnd* pWnd, _param* pInfo)
{
	EnableAutomation();
	m_pParent = pWnd;
	SetParam(pInfo);

}

CMainWnd::~CMainWnd()
{
}

void CMainWnd::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CMainWnd, CWnd)
	//{{AFX_DISPATCH_MAP(CMainWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMainWnd to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F8C1F100-01F1-4BA3-BE39-2A0048303755}
static const IID IID_IMainWnd =
{ 0xf8c1f100, 0x1f1, 0x4ba3, { 0xbe, 0x39, 0x2a, 0x0, 0x48, 0x30, 0x37, 0x55 } };

BEGIN_INTERFACE_MAP(CMainWnd, CWnd)
	INTERFACE_PART(CMainWnd, IID_IMainWnd, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	AfxEnableControlContainer();
	SetTimer(9999, 2000, NULL);

	return 0;
}


LONG CMainWnd::OnUser(WPARAM wParam, LPARAM lParam)
{
	CString s = "";
	LONG	ret = 0;
	switch(LOBYTE(LOWORD(wParam)))
	{
		case DLL_OUB:
			{
				_extTH *extTH =(_extTH*)lParam;
				int key = extTH->key;
				char* pdata = (char*)lParam;
			}
			break;
	}

	return ret;
}
#define TRKEY_GROUP			255
void CMainWnd::Sendtest()
{
	CString strData;
	strData = "";
	SendTR(_T("PIDOSETa"), NULL, "1"  , (BYTE)TRKEY_GROUP);
}

void CMainWnd::sendTR_1(CString name, CString data, BYTE type, int key, CString keyName, int uniqueKey)
{ 
	//CString suser;
	//suser = Variant(nameCC);
	//
	//CString trData = ""; 
	//CString tempdata = "";
	//CString pass;
	//
	//struct _userTH udat;
	//memset((void*)&udat, 0, sizeof(udat));
	//
	//strcpy(udat.trc, name);
	//udat.key = key;
	//udat.stat = type;
	//
	//trData = uniqueKey;	
	//trData += keyName;
	//trData += '\t';
	//trData += CString((char *)&udat, L_userTH);
	//trData += data;
	//
	////	m_pWnd->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, strlen(data)), (LPARAM)(LPCTSTR)trData);
	//
	//LRESULT RESULT = m_pParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, trData.GetLength() - L_userTH - m_param.name.GetLength() - 1), (LPARAM)trData.operator LPCTSTR());
}

void CMainWnd::sendTR(CString name, CString data, BYTE type, int key, CString keyName, int uniqueKey)
{
//	// 	OutputDebugString("[KSJ] SEndTR");
//	
//	CString trData = ""; 
//	CString pass;
//	
//	struct _userTH udat;
////	memset((void*)&udat, 0, sizeof(udat));
//	
//	strcpy(udat.trc, name);
//	udat.key = m_param.key;
//	udat.stat = type;
//	
//	trData = (BYTE)uniqueKey;
//	trData += keyName;
//	trData += _T("\t");
//
//	trData += CString((char *)&udat, L_userTH);
//	trData += data;
//	
//	
//	
//	//	m_pWnd->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, strlen(data)), (LPARAM)(LPCTSTR)trData);
//	int nnn = trData.GetLength() - L_userTH - m_param.name.GetLength() - 1;
//
//	LRESULT RESULT = m_pParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, data.GetLength() ), (LPARAM)trData.operator LPCTSTR());

}

BOOL CMainWnd::SendTR(CString strName, BYTE type, CString strData, BYTE key)
{
	//CString trData = "";
	//
	//struct _userTH udat;
	//
	//memset((void*)&udat, 0, sizeof(udat));	
	//strcpy(udat.trc, strName);
	//udat.stat = type | US_KEY;
	//
	//udat.key = m_param.key;

	//trData = (BYTE)key;//*/TRKEY_GROUP;
	//trData += m_param.name;
	//trData += _T("\t");

	//trData += CString((char *)&udat, L_userTH);
	//trData += strData;
	//
	//int nRet = m_pParent->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, strData.GetLength()), (LPARAM)(LPCTSTR)trData);
	//return nRet;
	return 0;
}

void CMainWnd::SearchGroupList(bool bInit)  //최초 열때 조회, 설정창으로 그룹등 변경후 조회 두가지로 나뉨
{
	
	CString strSendData;
	struct _updn updn;
	
	FillMemory(&updn, sizeof(_updn), ' ');
	ZeroMemory(&updn, sizeof(_updn));
	
	CopyMemory(&updn.uinfo.gubn, "MY", sizeof(updn.uinfo.gubn));
	updn.uinfo.dirt[0] = 'U';
	updn.uinfo.cont[0] = 'G';
	CopyMemory(updn.uinfo.nblc, _T("00001"), sizeof(updn.uinfo.nblc));
	updn.uinfo.retc[0] = 'U';
	
	strSendData = CString((char*)&updn, sizeof(_updn));
//endTR(_T("pidomyst"), NULL, strSendData  , (BYTE)TRKEY_GROUP);
	sendTR_1(_T("pidomyst"), strSendData , US_KEY, m_param.key, m_param.name, 0x11);
}

CString CMainWnd::Variant(int comm, CString data)
{
	CString retvalue = _T("");
	char* dta = (char*)m_pParent->SendMessage(WM_USER, MAKEWPARAM(variantDLL, comm), (LPARAM)(LPCTSTR)data);
	
	if ((long)dta > 1)
		retvalue = CString(dta);
	
	return retvalue;
}


void CMainWnd::SetParam(_param *pParam)
{
	m_param.key = pParam->key;
	m_param.name = CString(pParam->name, pParam->name.GetLength());
	m_param.rect = CRect(pParam->rect.left, pParam->rect.top, pParam->rect.right, pParam->rect.bottom);
	m_param.fonts = CString(pParam->fonts, pParam->fonts.GetLength());
	m_param.point = pParam->point;
	m_param.style = pParam->style;
	// 	m_clrForeColor = m_Param.tRGB = pParam->tRGB;
	// 	m_clrBackColor = m_Param.pRGB = pParam->pRGB;
	m_param.options = CString(pParam->options, pParam->options.GetLength());

}

void CMainWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 9999:
		{
			KillTimer(nIDEvent);
			SearchGroupList(true);
			Sendtest();
		}
		break;
	}
	CWnd::OnTimer(nIDEvent);
}
