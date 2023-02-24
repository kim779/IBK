// Qstick.h: interface for the CQstick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSTICK_H__0D481F17_E98B_4488_8E38_0B961E119465__INCLUDED_)
#define AFX_QSTICK_H__0D481F17_E98B_4488_8E38_0B961E119465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Include_ST/InnerFunction.h"

class CQstick  : public CInnerFunction
{
public:
	CQstick();
	virtual ~CQstick();
	CString GetName(long lType) {return m_strName;}
	CString GetInputs(long lType);
	double Func(CISTController *pIController , long lType, const VARIANT FAR& varArg1, const VARIANT FAR& varArg2, const VARIANT FAR& varArg3, const VARIANT FAR& varArg4, const VARIANT FAR& varArg5, const VARIANT FAR& varArg6, const VARIANT FAR& varArg7, const VARIANT FAR& varArg8, const VARIANT FAR& varArg9, const VARIANT FAR& varArg10);
private:
	CString m_strName;
};

#endif // !defined(AFX_QSTICK_H__0D481F17_E98B_4488_8E38_0B961E119465__INCLUDED_)
