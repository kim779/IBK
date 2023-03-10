// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "ibksconnector.h"

/////////////////////////////////////////////////////////////////////////////
// CIBKSConnector

IMPLEMENT_DYNCREATE(CIBKSConnector, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CIBKSConnector properties

/////////////////////////////////////////////////////////////////////////////
// CIBKSConnector operations

BOOL CIBKSConnector::Initialize()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CIBKSConnector::Uninitialize()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CIBKSConnector::Login(LPCTSTR user_id, LPCTSTR user_pw, LPCTSTR cert_pw, LPCTSTR svr_ip, long svr_port)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		user_id, user_pw, cert_pw, svr_ip, svr_port);
	return result;
}

CString CIBKSConnector::GetLastErrMsg()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CIBKSConnector::GetUserName_()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CIBKSConnector::GetHome()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CIBKSConnector::GetUserID()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CIBKSConnector::Logout()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CIBKSConnector::TR1001(long key, LPCTSTR code)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code);
	return result;
}

BOOL CIBKSConnector::TR1201(long key, long mmgb, LPCTSTR acno, LPCTSTR pswd, long ojno, LPCTSTR code, long jqty, long jprc, long hogb, long mdgb)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, mmgb, acno, pswd, ojno, code, jqty, jprc, hogb, mdgb);
	return result;
}

BOOL CIBKSConnector::TR1211(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR code, long dsgb, long sygb, long dlgb, long sort, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, code, dsgb, sygb, dlgb, sort, nkey);
	return result;
}

BOOL CIBKSConnector::TR1221(long key, LPCTSTR acno, LPCTSTR pswd, long allf, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, allf, nkey);
	return result;
}

BOOL CIBKSConnector::TR1231(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR code, long mmgb, double jprc)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_R8;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, code, mmgb, jprc);
	return result;
}

BOOL CIBKSConnector::TR3001(long key, LPCTSTR code)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code);
	return result;
}

BOOL CIBKSConnector::TR3201(long key, long mmgb, LPCTSTR acno, LPCTSTR pswd, long ojno, LPCTSTR code, long jqty, long jprc, long hogb, long mdgb)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, mmgb, acno, pswd, ojno, code, jqty, jprc, hogb, mdgb);
	return result;
}

BOOL CIBKSConnector::TR3211(long key, LPCTSTR acno, LPCTSTR pswd, long dlgb, long sort, LPCTSTR code, long cpgb, long dsgb, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, dlgb, sort, code, cpgb, dsgb, nkey);
	return result;
}

BOOL CIBKSConnector::TR3221(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, nkey);
	return result;
}

BOOL CIBKSConnector::TR3231(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR code, long mmgb, double jprc, long hogb, long qtpy, double jamt, double jrat)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_R8 VTS_I4 VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, code, mmgb, jprc, hogb, qtpy, jamt, jrat);
	return result;
}

BOOL CIBKSConnector::TR1801(long key, LPCTSTR code)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code);
	return result;
}

BOOL CIBKSConnector::TR1802(long key, LPCTSTR code)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code);
	return result;
}

BOOL CIBKSConnector::TR1803(long key, LPCTSTR code)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code);
	return result;
}

BOOL CIBKSConnector::TR1804(long key, LPCTSTR jidx)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, jidx);
	return result;
}

CString CIBKSConnector::GetAccounts()
{
	CString result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CIBKSConnector::TR1002(long key, LPCTSTR code, LPCTSTR symb)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code, symb);
	return result;
}

BOOL CIBKSConnector::TR1003(long key, LPCTSTR code, long type, LPCTSTR symb, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code, type, symb, nkey);
	return result;
}

BOOL CIBKSConnector::TR3002(long key, LPCTSTR code, LPCTSTR symb)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code, symb);
	return result;
}

BOOL CIBKSConnector::TR3003(long key, LPCTSTR code, long type, LPCTSTR symb, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, code, type, symb, nkey);
	return result;
}

BOOL CIBKSConnector::GetCode(long key, LPCTSTR reqtype)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, reqtype);
	return result;
}

BOOL CIBKSConnector::TR1202(long key, long mmgb, LPCTSTR acno, LPCTSTR pswd, long ojno, LPCTSTR code, long jqty, long jprc, long hogb, long mdgb, long id)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, mmgb, acno, pswd, ojno, code, jqty, jprc, hogb, mdgb, id);
	return result;
}

BOOL CIBKSConnector::TR3202(long key, long mmgb, LPCTSTR acno, LPCTSTR pswd, long ojno, LPCTSTR code, long jqty, long jprc, long hogb, long mdgb, long id)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, mmgb, acno, pswd, ojno, code, jqty, jprc, hogb, mdgb, id);
	return result;
}

BOOL CIBKSConnector::TR4224(long key, LPCTSTR acno, LPCTSTR pswd, double zKpi200Idx)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_R8;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zKpi200Idx);
	return result;
}

BOOL CIBKSConnector::TR4223(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zSrtDt, LPCTSTR zEndDt)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zSrtDt, zEndDt);
	return result;
}

BOOL CIBKSConnector::TR4303(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zQrySrtDt, LPCTSTR zQryEndDt, long zQryTp, long zStnlnSeqTp, long zBalEvalTp, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zQrySrtDt, zQryEndDt, zQryTp, zStnlnSeqTp, zBalEvalTp, nkey);
	return result;
}

BOOL CIBKSConnector::TR4201(long key, LPCTSTR acno, LPCTSTR pswd, long zFnoClssCode, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zFnoClssCode, nkey);
	return result;
}

BOOL CIBKSConnector::TR4101(long key, LPCTSTR acno, LPCTSTR pswd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd);
	return result;
}

BOOL CIBKSConnector::TR4221(long key, LPCTSTR acno, LPCTSTR pswd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd);
	return result;
}

BOOL CIBKSConnector::TR4401(long key, LPCTSTR acno, LPCTSTR pswd, long zQryTp, LPCTSTR zQrySrtDt, LPCTSTR zQryEndDt, LPCTSTR zIsuNo, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zQryTp, zQrySrtDt, zQryEndDt, zIsuNo, nkey);
	return result;
}

BOOL CIBKSConnector::TR4202(long key, LPCTSTR acno, LPCTSTR pswd, long zBalEvalTp, long zPrcEvalTp, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zBalEvalTp, zPrcEvalTp, nkey);
	return result;
}

BOOL CIBKSConnector::TR4003(long key, LPCTSTR acno, LPCTSTR pswd, long zMprcOrdTp, LPCTSTR zRoopData)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zMprcOrdTp, zRoopData);
	return result;
}

BOOL CIBKSConnector::TR4004(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zRoopData)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zRoopData);
	return result;
}

void CIBKSConnector::SetPTS()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CIBKSConnector::TR4501(long key, LPCTSTR zMnyoutAcntno, LPCTSTR zMnyoutPswd, long zlMnyoutAmt, LPCTSTR zMnyinBnkCode, LPCTSTR zMnyinBnkAcntNo, LPCTSTR zAskpsnNm, LPCTSTR zTelExno, LPCTSTR zTelRgno, LPCTSTR zTelSeqno)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, zMnyoutAcntno, zMnyoutPswd, zlMnyoutAmt, zMnyinBnkCode, zMnyinBnkAcntNo, zAskpsnNm, zTelExno, zTelRgno, zTelSeqno);
	return result;
}

BOOL CIBKSConnector::TR4502(long key, LPCTSTR acno, LPCTSTR pswd, long lBkeepAmt, LPCTSTR zMnyinAcntNo)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, lBkeepAmt, zMnyinAcntNo);
	return result;
}

BOOL CIBKSConnector::TR4503(long key, LPCTSTR zMnyinAcntNo, LPCTSTR zBnkCode, LPCTSTR zBnkAcntNo, LPCTSTR zBnkPwd, long zMnyinAmt)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, zMnyinAcntNo, zBnkCode, zBnkAcntNo, zBnkPwd, zMnyinAmt);
	return result;
}

BOOL CIBKSConnector::TR4511(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zQrySrtDt, LPCTSTR zQryEndDt, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zQrySrtDt, zQryEndDt, nkey);
	return result;
}

BOOL CIBKSConnector::TR4512(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zQrySrtDt, LPCTSTR zQryEndDt, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zQrySrtDt, zQryEndDt, nkey);
	return result;
}

BOOL CIBKSConnector::TR4521(long key)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key);
	return result;
}

BOOL CIBKSConnector::TR4522(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR zBankCode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zBankCode);
	return result;
}

BOOL CIBKSConnector::TR4523(long key, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, nkey);
	return result;
}

BOOL CIBKSConnector::TR4524(long key)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key);
	return result;
}

BOOL CIBKSConnector::TR4525(long key, LPCTSTR zMnyoutAcntno)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, zMnyoutAcntno);
	return result;
}

BOOL CIBKSConnector::TR4526(long key, LPCTSTR acno, LPCTSTR pswd, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, nkey);
	return result;
}

BOOL CIBKSConnector::TR4527(long key, LPCTSTR acno)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno);
	return result;
}

void CIBKSConnector::SaveConfig(LPCTSTR sSendName, LPCTSTR sKey, LPCTSTR sValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sSendName, sKey, sValue);
}

BOOL CIBKSConnector::TR8001(long key, LPCTSTR acno)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno);
	return result;
}

void CIBKSConnector::GoURL(long nType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nType);
}

BOOL CIBKSConnector::TR1222(long key, LPCTSTR acno, LPCTSTR pswd, long allf)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, allf);
	return result;
}

BOOL CIBKSConnector::TR3222(long key, LPCTSTR acno, LPCTSTR pswd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd);
	return result;
}

BOOL CIBKSConnector::TR4403(long key, LPCTSTR acno, LPCTSTR pswd, long zFnoClssCode, LPCTSTR zCmsnAmtAddupCode, LPCTSTR zStrDt, LPCTSTR zEndDt, LPCTSTR nkey)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, zFnoClssCode, zCmsnAmtAddupCode, zStrDt, zEndDt, nkey);
	return result;
}

BOOL CIBKSConnector::TR3411(long key, LPCTSTR mymd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, mymd);
	return result;
}

CString CIBKSConnector::GetGreeksData(LPCTSTR sData)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		sData);
	return result;
}

BOOL CIBKSConnector::TR3232(long key, LPCTSTR acno, LPCTSTR pswd, long fstp, long ertp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, acno, pswd, fstp, ertp);
	return result;
}
