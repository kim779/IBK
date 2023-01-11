#include "stdafx.h"
#include "libmap.h"
#include "mapWnd.h"

__declspec(dllexport) CWnd* APIENTRY axCreate(CWnd *view, CWnd* parent, int trKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CMapWnd* mapWnd = new CMapWnd(view, parent, trKey);
	mapWnd->Create();
	return mapWnd;
}