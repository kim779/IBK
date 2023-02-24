// VROC.h: interface for the CVROC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VROC_H__DD57B27F_43EE_44E3_A4FF_F3CCF7021ABA__INCLUDED_)
#define AFX_VROC_H__DD57B27F_43EE_44E3_A4FF_F3CCF7021ABA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Include_ST/InnerFunction.h"

class CVROC   : public CInnerFunction
{
public:
	CVROC();
	virtual ~CVROC();
	CString GetName(long lType) {return m_strName;}
	CString GetInputs(long lType);
	double Func(CISTController *pIController , long lType, const VARIANT FAR& varArg1, const VARIANT FAR& varArg2, const VARIANT FAR& varArg3, const VARIANT FAR& varArg4, const VARIANT FAR& varArg5, const VARIANT FAR& varArg6, const VARIANT FAR& varArg7, const VARIANT FAR& varArg8, const VARIANT FAR& varArg9, const VARIANT FAR& varArg10);
private:
	CString m_strName;


};

#endif // !defined(AFX_VROC_H__DD57B27F_43EE_44E3_A4FF_F3CCF7021ABA__INCLUDED_)
