// cx_THtmlEx.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "cx_THtmlEx.h"

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
// Ccx_THtmlExApp

BEGIN_MESSAGE_MAP(Ccx_THtmlExApp, CWinApp)
	//{{AFX_MSG_MAP(Ccx_THtmlExApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Ccx_THtmlExApp construction

Ccx_THtmlExApp::Ccx_THtmlExApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only Ccx_THtmlExApp object

Ccx_THtmlExApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Ccx_THtmlExApp initialization

BOOL Ccx_THtmlExApp::InitInstance()
{
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

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

CFont* Ccx_THtmlExApp::GetFont(CWnd* pView, int point, CString name, int bold, bool italic)
{
	struct	_fontR	rFont {};

	rFont.name = (char*)name.GetString();
	rFont.point = point;
	rFont.italic = italic;
	rFont.bold = bold;

	return (CFont*) pView->SendMessage(WM_USER, getFONT, (LPARAM)&rFont);
}

CPen* Ccx_THtmlExApp::GetPen(CWnd* pView, int style, int width, COLORREF clr)
{
	struct	_penR	rPen {};

	rPen.clr = clr;
	rPen.width = width;
	rPen.style = style;

	return (CPen*) pView->SendMessage(WM_USER, getPEN, (LPARAM)&rPen);
}

CBrush* Ccx_THtmlExApp::GetBrush(CWnd* pView, COLORREF rColor)
{
	return (CBrush*) pView->SendMessage(WM_USER, getBRUSH, rColor);
}