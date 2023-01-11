// axisGMView.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "axisGMView.h"
#include "grpMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CAxisGMViewApp

BEGIN_MESSAGE_MAP(CAxisGMViewApp, CWinApp)
	//{{AFX_MSG_MAP(CAxisGMViewApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxisGMViewApp construction

CAxisGMViewApp::CAxisGMViewApp()
{
	m_root = m_uid = m_uname = m_tabDir = m_userDir = m_gexDir = _T("");

	m_hiGMTotalLib = NULL;
	m_hiGMThemeLib = NULL;
	m_hiGMInvestLib = NULL;

	m_pImgDate = NULL;
	m_pImgTime = NULL;
	m_pImgNTime = NULL;
	m_pImgNBtn = NULL;
	m_pImgCode = NULL;
	m_pImgIEtc = NULL;
	m_pImgIOpt = NULL;
	m_pImgICfg = NULL;
	m_pImgTool = NULL;
	m_pImgTool2 = NULL;
	m_pImgCtrl = NULL;
	m_pImgCtrl2 = NULL;
	m_pImgUnit = NULL;
}

CAxisGMViewApp::~CAxisGMViewApp()
{
	if (m_hiGMTotalLib)
		FreeLibrary(m_hiGMTotalLib);
	if (m_hiGMThemeLib)
		FreeLibrary(m_hiGMThemeLib);
	if (m_hiGMInvestLib)
		FreeLibrary(m_hiGMInvestLib);

	if (m_pImgDate)		IMG_DELETE(m_pImgDate);
	if (m_pImgTime)		IMG_DELETE(m_pImgTime);
	if (m_pImgNTime)	IMG_DELETE(m_pImgNTime);
	if (m_pImgNBtn)		IMG_DELETE(m_pImgNBtn);
	if (m_pImgCode)		IMG_DELETE(m_pImgCode);
	if (m_pImgIEtc)		IMG_DELETE(m_pImgIEtc);
	if (m_pImgIOpt)		IMG_DELETE(m_pImgIOpt);
	if (m_pImgICfg)		IMG_DELETE(m_pImgICfg);
	if (m_pImgTool)		IMG_DELETE(m_pImgTool);
	if (m_pImgTool2)	IMG_DELETE(m_pImgTool2);
	if (m_pImgCtrl)		IMG_DELETE(m_pImgCtrl);
	if (m_pImgCtrl2)	IMG_DELETE(m_pImgCtrl2);

	if (m_pImgUnit)		IMG_DELETE(m_pImgUnit);
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CAxisGMViewApp object

CAxisGMViewApp theApp;

CWnd* CAxisGMViewApp::Create(CWnd* pwndView, char* pcDllName)
{
	m_root =  (LPCTSTR)pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, homeCC));
	m_uname = (LPCTSTR)pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, nameCC));
	m_uid =   (LPCTSTR)pwndView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, userCC));
	
	m_tabDir.Format ("%s\\%s\\", m_root, TABDIR);
	m_userDir.Format("%s\\%s\\", m_root, USRDIR);
	m_gexDir.Format ("%s\\%s\\", m_root, GEXDIR);
	m_imgDir.Format ("%s\\%s\\", m_root, IMAGEDIR);

	CGrpMView* pGrpMView = new CGrpMView(pwndView, pcDllName);
	if (!pGrpMView->Create(NULL, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 
		CRect(0, 0, 1, 1), pwndView, 0))
	{
		delete pGrpMView;
		pGrpMView = NULL;
		return NULL;
	}

	return pGrpMView;
}

CFont* CAxisGMViewApp::GetFont(CWnd *pView, int point, CString name, int bold, bool italic)
{
	_fontR rFont;
	rFont.name = (LPSTR)(LPCTSTR)name;
	rFont.point = point;
	rFont.italic = italic;
	rFont.bold = bold;
	return (CFont*) pView->SendMessage(WM_USER, getFONT, long(&rFont));
}

CPen* CAxisGMViewApp::GetPen(CWnd *pView, int style, int width, COLORREF clr)
{
	_penR rPen;
	rPen.clr = clr;
	rPen.width = width;
	rPen.style = style;
	return (CPen*) pView->SendMessage(WM_USER, getPEN, long(&rPen));
}

CBrush* CAxisGMViewApp::GetBrush(CWnd *pView, COLORREF rColor)
{
	return (CBrush*) pView->SendMessage(WM_USER, getBRUSH, rColor);
}

UINT CAxisGMViewApp::MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption, UINT button)
{
	return AfxGetMainWnd()->MessageBox(lpszText, lpszCaption, button);
}

UINT CAxisGMViewApp::MessageBoxF(LPCTSTR lpszFormat, ...)
{
	char szTemp[4096];
	
	va_list argList;
	va_start(argList, lpszFormat);
	vsprintf(szTemp, lpszFormat, argList);
	va_end(argList);

	return MessageBox(szTemp, COMPANYNAME);
}

bool CAxisGMViewApp::ReadFile(CWnd *pView, CString path, char *pBytes, int nBytes)
{
	DWORD	dwAccess = GENERIC_READ;
	DWORD	dwShareMode = FILE_SHARE_READ;
	DWORD	dwDistribution = OPEN_EXISTING;

	HANDLE hFile = CreateFile(path.operator LPCTSTR(), dwAccess,
				dwShareMode, NULL, dwDistribution,
				FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACE("hFile Error [%d] on OpenHandle\n", GetLastError());
		AfxGetMainWnd()->MessageBox("오픈할 파일 생성에 실패했습니다.", "확인", MB_OK);

		return false;
	}

	char	*rWb = new char[nBytes + 1];
	DWORD	dwReadLen;

	BOOL bRc = ::ReadFile(hFile, rWb, nBytes, &dwReadLen, NULL);
	CloseHandle(hFile);
	if (dwReadLen != DWORD(nBytes))
	{
		BUF_DELETE(rWb);
		//delete rWb;
		return false;
	}
	CopyMemory(pBytes, rWb, nBytes);
	delete rWb;

	return true;
}

bool CAxisGMViewApp::WriteFile(CWnd *pView, CString path, char *pBytes, int nBytes)
{
	DWORD	dwAccess = GENERIC_WRITE;
	DWORD	dwShareMode = FILE_SHARE_WRITE;
	DWORD	dwDistribution = CREATE_ALWAYS;

	HANDLE hFile = CreateFile(path.operator LPCTSTR(), dwAccess,
				dwShareMode, NULL, dwDistribution,
				FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACE("hFile Error [%d] on OpenHandle\n", GetLastError());
		AfxGetMainWnd()->MessageBox("저장할 파일 생성에 실패했습니다.", "확인", MB_OK);

		return false;
	}

	DWORD	dwWriteLen;
	BOOL bRc = ::WriteFile(hFile, pBytes, nBytes, &dwWriteLen, NULL);
	CloseHandle(hFile);
	if (!bRc)
	{
		AfxGetMainWnd()->MessageBox("저장할 파일 생성에 실패했습니다.", "확인", MB_OK);
		return false;
	}
	return true;
}

CString CAxisGMViewApp::GetImagePath(CWnd* pwndView, CString imgName)
{
	CString imgPath = _T("");
	imgPath.Format("%s%s", m_imgDir, imgName);
	return imgPath;
}

CImageList* CAxisGMViewApp::GetImage(CString path, int Width, int Height, UINT flag, COLORREF crMask)
{
	CImageList* pImage = NULL;
	HBITMAP hbitmap = (HBITMAP) LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbitmap)
	{
		CBitmap	bitmap;
		bitmap.DeleteObject();
		bitmap.Attach(hbitmap);
		pImage = new CImageList();
		pImage->Create(Width, Height, flag, 0, 1);
		pImage->Add(&bitmap, crMask);
		bitmap.DeleteObject();
	}
	return pImage;
}

CImageList* CAxisGMViewApp::GetImage(int imgType, CString path)
{
	switch (imgType)
	{
	case imgDate:
		if (!m_pImgDate)
			m_pImgDate = GetImage(path, szDateImgX, szDateImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgDate;
	case imgTime:
		if (!m_pImgTime)
			m_pImgTime = GetImage(path, szTimeImgX, szTimeImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgTime;
	case imgNTime:
		if (!m_pImgNTime)
			m_pImgNTime = GetImage(path, szTimeImgX, szTimeImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgNTime;
	case imgNBtn:
		if (!m_pImgNBtn)
			m_pImgNBtn = GetImage(path, szIBtnImgX, szIBtnImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgNBtn;
	case imgCode:
		if (!m_pImgCode)
			m_pImgCode = GetImage(path, szCodeImgX, szCodeImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgCode;
	case imgIEtc:
		if (!m_pImgIEtc)
			m_pImgIEtc = GetImage(path, szIEtcImgX, szIEtcImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgIEtc;
	case imgIOpt:
		if (!m_pImgIOpt)
			m_pImgIOpt = GetImage(path, szIOptImgX, szIOptImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgIOpt;
	case imgICfg:
		if (!m_pImgICfg)
			m_pImgICfg = GetImage(path, szICfgImgX, szICfgImgY,
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgICfg;
	case imgTool:
		if (!m_pImgTool)
			m_pImgTool = GetImage(path, szToolImgX, szToolImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgTool;
	case imgTool2:
		if (!m_pImgTool2)
			m_pImgTool2 = GetImage(path, szTool2ImgX, szTool2ImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgTool2;
	case imgCtrl:
		if (!m_pImgCtrl)
			m_pImgCtrl = GetImage(path, szCtrlImgX, szCtrlImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgCtrl;
	case imgCtrl2:
		if (!m_pImgCtrl2)
			m_pImgCtrl2 = GetImage(path, szCtrl2ImgX, szCtrl2ImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgCtrl2;

	case imgIUnit:
		if (!m_pImgUnit)
			m_pImgUnit = GetImage(path, 49, 18, //szUnitImgX, szUnitImgY,
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgUnit;
	}
	return NULL;
}




__declspec(dllexport) CWnd* WINAPI axCreate(CWnd* pwndView, char* pcDllName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CAxisGMViewApp* pApp = (CAxisGMViewApp *)AfxGetApp();
	CWnd* result = pApp->Create(pwndView, pcDllName);

	return result;
}
