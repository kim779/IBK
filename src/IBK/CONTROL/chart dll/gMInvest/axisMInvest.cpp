// axisMInvest.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "axisMInvest.h"

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
// CaxisMInvestApp

BEGIN_MESSAGE_MAP(CaxisMInvestApp, CWinApp)
	//{{AFX_MSG_MAP(CaxisMInvestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CaxisMInvestApp construction

CaxisMInvestApp::CaxisMInvestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CaxisMInvestApp object

CaxisMInvestApp theApp;

CBitmap* CaxisMInvestApp::GetBitmap(CWnd* pView, CString path)
{
	return (CBitmap*)pView->SendMessage(WM_USER, getBITMAP, (long)path.operator LPCTSTR());
}

COLORREF CaxisMInvestApp::GetColor(CWnd* pView, int index)
{
	if (index & 0x02000000)
		return index;
	return pView->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), (LPARAM)index);
}

CString CaxisMInvestApp::Variant(CWnd* pView, int comm, CString data)
{
	CString retvalue;

	char* dta = (char*)pView->SendMessage(WM_USER, MAKEWPARAM(variantDLL, comm), (LPARAM)(LPCTSTR)data);

	if ((long)dta > 1)
		retvalue = dta;
	else
		return "";

	return retvalue;
}

CImageList* CaxisMInvestApp::getImage(CString path, int Width, int Height, UINT flag, COLORREF crMask)
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

CFont* CaxisMInvestApp::GetFont(CWnd* pView, int point, CString name, int bold, bool italic)
{
	_fontR rFont;
	rFont.name = (char *)name.operator LPCTSTR();
	rFont.point = point;
	rFont.italic = italic;
	rFont.bold = bold;
	return (CFont*) pView->SendMessage(WM_USER, getFONT, long(&rFont));
}

CPen* CaxisMInvestApp::GetPen(CWnd* pView, int style, int width, COLORREF clr)
{
	_penR rPen;
	rPen.clr = clr;
	rPen.width = width;
	rPen.style = style;
	return (CPen*) pView->SendMessage(WM_USER, getPEN, long(&rPen));
}

CBrush* CaxisMInvestApp::GetBrush(CWnd* pView, COLORREF rColor)
{
	return (CBrush*) pView->SendMessage(WM_USER, getBRUSH, rColor);
}

CImageList* CaxisMInvestApp::GetImage(CWnd* pView, CString path, int Width, int Height, UINT flag, COLORREF crMask)
{
	CBitmap *pBitmap = (CBitmap*) pView->SendMessage(WM_USER, getBITMAP, long(path.operator LPCTSTR()));

	CImageList* pImage = NULL;
	if (pBitmap)
	{
		pImage = new CImageList();
		pImage->Create(Width, Height, flag, 0, 1);
		pImage->Add(pBitmap, crMask);
	}

	return pImage;
}

void CaxisMInvestApp::Init(CWnd* view)
{
	m_view   = view;
	m_sRoot	 = Variant(m_view, homeCC, "");
	m_sUser  = Variant(m_view, nameCC, "");
	m_font   = GetFont(m_view, 9, "±¼¸²", 0);
}

