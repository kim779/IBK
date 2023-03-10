// MarketPosition.cpp: implementation of the CMarketPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "indi_func.h"
#include "MarketPosition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMarketPosition::CMarketPosition()
{
	m_strName = "MARKETPOSITION";
}

CMarketPosition::~CMarketPosition()
{

}

CString CMarketPosition::GetInputs(long lType)
{
//	return "Numeric, Numeric=close";
	return "Numeric, Numeric";
}

/*-----------------------------------------------------------------------------
 Author		: Hui-Eun, Lee	Date :2005.7.20
 Modifier		: 
 Comments		: 
-----------------------------------------------------------------------------*/
double CMarketPosition::Func(CISTController *pIController , long lType, const VARIANT FAR& varArg1, const VARIANT FAR& varArg2, const VARIANT FAR& varArg3, const VARIANT FAR& varArg4, const VARIANT FAR& varArg5, const VARIANT FAR& varArg6, const VARIANT FAR& varArg7, const VARIANT FAR& varArg8, const VARIANT FAR& varArg9, const VARIANT FAR& varArg10)
{
	long lPeriod = 	_variant_t(varArg1);
	double dValue = _variant_t(varArg2);

	if(pIController->IsFirstInThisMem())	// init
	{
		pIController->SetVariables(0,"Value1",NumericSeries,dValue);
		pIController->SetVariables(1,"OptValue1",NumericSeries,0);
		pIController->SetVariables(2,"OptValue2",NumericSeries,0);
		pIController->SetVariables(3,"OptValue3",NumericSeries,0);
	}
	pIController->SetVarHolderData(0,0,dValue);
	return yesMarketPosition(pIController->IsUpdateData()
		,pIController->BarIndex()
		,lPeriod
		,pIController->GetVarHolderDataItem(0)
		,pIController->GetVarHolderDataItem(1)
		,pIController->GetVarHolderDataItem(2)
		,pIController->GetVarHolderDataItem(3)
		,pIController->GetITempMemMng());
}
