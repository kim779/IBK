// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "dataio.h"

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

#include <AxStd.hpp>

extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>
#include "../../control/fx_grid/memdc.h"
#include "../../h/axisfire.h"
#include "../../h/axisvar.h"
#pragma comment (lib, "Msimg32.lib")
#include "../Share/index_com.h"


#define USES_CONVERSION_CONST int _convert = 0; (_convert); const UINT _acp = ATL::_AtlGetConversionACP() /*CP_THREAD_ACP*/; (_acp); LPCWSTR _lpw = NULL; (_lpw); LPCSTR _lpa = NULL; (_lpa)
#define USES_CONVERSION_CONST_CONVERT const int _convert = 0; (_convert); const UINT _acp = ATL::_AtlGetConversionACP() /*CP_THREAD_ACP*/; (_acp); LPCWSTR _lpw = NULL; (_lpw); LPCSTR _lpa = NULL; (_lpa)

#pragma warning(disable:26409)