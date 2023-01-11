#include "stdafx.h"
#include "axisGMTotal.h"

__declspec(dllexport) CWnd* WINAPI axCreate(CWnd *pView, CWnd* pParent, void* cInfo, int mType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CAxisGMTotalApp* pMapApp = (CAxisGMTotalApp *)AfxGetApp();

	struct _param	*pParam = (struct _param *)cInfo;
	return pMapApp->Create(pView, pParent, pParam, mType);
}

