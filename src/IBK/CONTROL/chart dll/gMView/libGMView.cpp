#include "stdafx.h"
#include "axisGMView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//__declspec(dllexport) CWnd* WINAPI axCreate(CWnd* parent, CString dllName)
__declspec(dllexport) CWnd* WINAPI axCreate(CWnd* parent, char* dllName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAxisGMViewApp* pApp = (CAxisGMViewApp *)AfxGetApp();
	return pApp->Create(parent, dllName);
}

