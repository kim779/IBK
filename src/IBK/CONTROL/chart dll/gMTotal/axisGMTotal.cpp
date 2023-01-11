// axisGMTotal.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DataChk.h"
#include "axisGMTotal.h"
#include "MainWnd.h"

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
// CAxisGMTotalApp

BEGIN_MESSAGE_MAP(CAxisGMTotalApp, CWinApp)
	//{{AFX_MSG_MAP(CAxisGMTotalApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxisGMTotalApp construction

CAxisGMTotalApp::CAxisGMTotalApp()
{
	m_strRoot = _T("");
	m_strUserID = _T("");
	m_strUserName = _T("");
	m_strTabDir = _T("");
	m_strUserDir = _T("");
	m_strGexDir = _T("");

	m_pImgDate = NULL;
	m_pImgNTime = NULL;
	m_pImgIOpt = NULL;
	m_pImgCtrl = NULL;
	m_pImgCtrl2 = NULL;

	m_hGMainLib = NULL;
	m_hGDlgLib = NULL;
}

CAxisGMTotalApp::~CAxisGMTotalApp()
{
	if (m_hGMainLib)	FreeLibrary(m_hGMainLib);
	if (m_hGDlgLib)		FreeLibrary(m_hGDlgLib);

	if (m_pImgDate)		IMG_DELETE(m_pImgDate);
	if (m_pImgNTime)	IMG_DELETE(m_pImgNTime);
	if (m_pImgIOpt)		IMG_DELETE(m_pImgIOpt);
	if (m_pImgCtrl)		IMG_DELETE(m_pImgCtrl);
	if (m_pImgCtrl2)	IMG_DELETE(m_pImgCtrl2);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAxisGMTotalApp object

CAxisGMTotalApp theApp;
BOOL CAxisGMTotalApp::InitInstance() 
{
	return CWinApp::InitInstance();
}

int CAxisGMTotalApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll();
	return S_OK;
}

CWnd* CAxisGMTotalApp::Create(CWnd *pView, CWnd* pParent, struct _param *param, int mType)
{
	if (m_strRoot.IsEmpty())
	{
		char* root = (char *)pView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, homeCC), 0);
		m_strRoot = CString(root);
	}
	if (m_strUserName.IsEmpty())
	{
		char* name = (char *)pView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, nameCC), 0);
		m_strUserName = CString(name);
	}
	if (m_strUserID.IsEmpty())
	{
		char* id = (char *)pView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, userCC), 0);
		m_strUserID = CString(id);
	}
	
	if (m_strTabDir.IsEmpty())
		m_strTabDir.Format("%s\\%s\\", m_strRoot, TABDIR);
	if (m_strUserDir.IsEmpty())
		m_strUserDir.Format("%s\\%s\\", m_strRoot, USRDIR);
	if (m_strGexDir.IsEmpty())
		m_strGexDir.Format("%s\\%s\\", m_strRoot, GEXDIR);

	CString	sName;
	CDataChk	dataChk(pView, param, sName, mType, true);

	m_mType = mType;		// 2008.09.26
	CopyParam(&m_param, param);	// 2008.09.26

	CMainWnd	*pMainWnd = new CMainWnd(pView, pParent, sName, param, mType);
	pMainWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, param->rect, pParent, 0);
	SetWindowPos(pMainWnd->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	return pMainWnd;
}

void CAxisGMTotalApp::CopyParam(_param *pDest, _param *pSource)
{
	pDest->key = pSource->key;
	pDest->name.Format("%s", pSource->name);
	pDest->rect = pSource->rect;
	pDest->fonts.Format("%s", pSource->fonts);
	pDest->point = pSource->point;
	pDest->style = pSource->style;
	pDest->tRGB = pSource->tRGB;
	pDest->pRGB = pSource->pRGB;
	pDest->options.Format("%s", pSource->options);
}

void CAxisGMTotalApp::ReMakeFile(CWnd *pParent)
{
	CString	sName;
	CDataChk	dataChk(pParent, &m_param, sName, m_mType, false);
	dataChk.ReMakeData();
}

CString CAxisGMTotalApp::GetImagePath(CWnd* pView, CString imgName)
{
	CString imgPath = _T("");
	imgPath.Format("%s\\%s\\%s", m_strRoot, IMAGEDIR, imgName);
	return imgPath;
}

CImageList* CAxisGMTotalApp::GetImage(int imgType, CString path)
{
	switch (imgType)
	{
	case imgDate:
		if (!m_pImgDate)
			m_pImgDate = getImage(path, szDateImgX, szDateImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgDate;
	case imgNTime:
		if (!m_pImgNTime)
			m_pImgNTime = getImage(path, szTimeImgX, szTimeImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgNTime;
	case imgIOpt:
		if (!m_pImgIOpt)
			m_pImgIOpt = getImage(path, szIOptImgX, szIOptImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgIOpt;
	case imgCtrl:
		if (!m_pImgCtrl)
			m_pImgCtrl = getImage(path, szCtrlImgX, szCtrlImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgCtrl;
	case imgCtrl2:
		if (!m_pImgCtrl2)
			m_pImgCtrl2 = getImage(path, szCtrl2ImgX, szCtrl2ImgY, 
			ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
		return m_pImgCtrl2;
	}
	return NULL;
}

CImageList* CAxisGMTotalApp::getImage(CString path, int Width, int Height, UINT flag, COLORREF crMask)
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

CFont* CAxisGMTotalApp::GetFont(CWnd *pView, int point, CString name, int bold, bool italic)
{
	_fontR rFont;
	rFont.name = (char *)name.operator LPCTSTR();
	rFont.point = point;
	rFont.italic = italic;
	rFont.bold = bold;
	return (CFont*) pView->SendMessage(WM_USER, getFONT, long(&rFont));
}

CPen* CAxisGMTotalApp::GetPen(CWnd *pView, int style, int width, COLORREF clr)
{
	_penR rPen;
	rPen.clr = clr;
	rPen.width = width;
	rPen.style = style;
	return (CPen*) pView->SendMessage(WM_USER, getPEN, long(&rPen));
}

CBrush* CAxisGMTotalApp::GetBrush(CWnd *pView, COLORREF rColor)
{
	return (CBrush*) pView->SendMessage(WM_USER, getBRUSH, rColor);
}

