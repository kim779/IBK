#if !defined(AFX_MESSAGEDEFINE_H__18754815_9512_11D2_AC26_00104B9E52FF__INCLUDED_)
#define AFX_MESSAGEDEFINE_H__18754815_9512_11D2_AC26_00104B9E52FF__INCLUDED_

const UINT RMSG_DBCLICK_WORKSPACE = ::RegisterWindowMessage("RMSG_DBCLICK_WORKSPACE");
const UINT RMSG_OPENFILE = ::RegisterWindowMessage("RMSG_OPENFILE");
const UINT RMSG_DELFILE = ::RegisterWindowMessage("RMSG_DELFILE");
const UINT RMSG_COMPILEDLL = ::RegisterWindowMessage("RMSG_COMPILEDLL");
const UINT RMSG_SINGLIECOMPILEDLLMAIN = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLL");
const UINT RMSG_SINGLIECOMPILEDLLFUNCTION = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLLFUNCTION");
const UINT RMSG_SINGLIECOMPILEDLLMAIN_YES = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLLMAIN_YES");
const UINT RMSG_SINGLIECOMPILEDLLFUNCTION_YES = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLLFUNCTION_YES");
const UINT RMSG_VIEWPROPERTY = ::RegisterWindowMessage("RMSG_VIEWPROPERTY");
const UINT RMSG_STCONFIGURENAME = ::RegisterWindowMessage("RMSG_STCONFIGURENAME");
const UINT RMSG_DBLCLICKOUTPUT = ::RegisterWindowMessage("RMSG_DBLCLICKOUTPUT");
const UINT RMSG_SYSTEMTRADING = ::RegisterWindowMessage("RMSG_SYSTEMTRADING");
const UINT RMSG_DBLCLICKFIND = ::RegisterWindowMessage("RMSG_DBLCLICKFIND");
const UINT RMSG_VERIFYSCRIPTNAME = ::RegisterWindowMessage("RMSG_VERIFYSCRIPTNAME");
const UINT RMSG_STARTDRAG = ::RegisterWindowMessage("RMSG_STARTDRAG");

const UINT RMSG_MAKEFILEDLL = ::RegisterWindowMessage("RMSG_MAKEFILEDLL");

const UINT RMSG_SINGLIECOMPILEDLLMAIN_TREE = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLLMAIN_TREE");
const UINT RMSG_SINGLIECOMPILEDLLFUNCTION_TREE = ::RegisterWindowMessage("RMSG_SINGLIECOMPILEDLLFUNCTION_TREE");

const UINT RMSG_MULTICOMPILEDLLMAIN_TREE = ::RegisterWindowMessage("RMSG_MULTICOMPILEDLLMAIN_TREE");
const UINT RMSG_MULTICOMPILEDLLFUNCTION_TREE = ::RegisterWindowMessage("RMSG_MULTICOMPILEDLLFUNCTION_TREE");

const UINT RMSG_GETCOMPILESTATE_TREE = ::RegisterWindowMessage("RMSG_GETCOMPILESTATE_TREE");

const UINT RMSG_STARTFILEWATCHER = ::RegisterWindowMessage("RMSG_STARTFILEWATCHER");//KHD
	
#define UMSG_LANGUAGE_RELOAD	WM_USER + 500
#endif // !defined(AFX_MESSAGEDEFINE_H__18754815_9512_11D2_AC26_00104B9E52FF__INCLUDED_)
