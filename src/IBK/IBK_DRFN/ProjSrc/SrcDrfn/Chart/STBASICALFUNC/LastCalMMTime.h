// LastCalMMTime.h: interface for the CLastCalMMTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASTCALMMTIME_H__FFECE878_98A4_407A_9F3C_9185770FF630__INCLUDED_)
#define AFX_LASTCALMMTIME_H__FFECE878_98A4_407A_9F3C_9185770FF630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Include_ST/InnerFunction.h"

class CLastCalMMTime   : public CInnerFunction
{
public:
	CLastCalMMTime();
	virtual ~CLastCalMMTime();
	CString GetName(long lType);
	CString GetInputs(long lType);
	double Func(CISTController *pIController , long lType,  const VARIANT FAR& varArg1, const VARIANT FAR& varArg2, const VARIANT FAR& varArg3, const VARIANT FAR& varArg4, const VARIANT FAR& varArg5, const VARIANT FAR& varArg6, const VARIANT FAR& varArg7, const VARIANT FAR& varArg8, const VARIANT FAR& varArg9, const VARIANT FAR& varArg10);
private:
	CString m_strName;

};

#endif // !defined(AFX_LASTCALMMTIME_H__FFECE878_98A4_407A_9F3C_9185770FF630__INCLUDED_)