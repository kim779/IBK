// NthHighest.cpp: implementation of the CNthHighest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "indi_func.h"
#include "NthHighest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNthHighest::CNthHighest()
{
	m_strName = "NTHHIGHEST";
}

CNthHighest::~CNthHighest()
{

}

CString CNthHighest::GetInputs(long lType)
{
	return "Numeric,Numeric,Numeric";
}

double CNthHighest::Func(CISTController *pIController , long lType, const VARIANT FAR& varArg1, const VARIANT FAR& varArg2, const VARIANT FAR& varArg3, const VARIANT FAR& varArg4, const VARIANT FAR& varArg5, const VARIANT FAR& varArg6, const VARIANT FAR& varArg7, const VARIANT FAR& varArg8, const VARIANT FAR& varArg9, const VARIANT FAR& varArg10)
{
	long lNth = _variant_t(varArg1);
	double dValue = _variant_t(varArg2);
	long lPeriod = _variant_t(varArg3);


	if(pIController->IsFirstInThisMem())	// init
	{
		pIController->SetVariables(0,"value",NumericSeries, dValue);
	}
	pIController->SetVarHolderData(0,0,dValue);

	return yesNthHighest(pIController->IsUpdateData()
		,pIController->BarIndex(), lNth, lPeriod,
		pIController->GetVarHolderDataItem(0),pIController->GetITempMemMng());

}

