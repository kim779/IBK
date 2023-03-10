#if !defined(AFX_CHARTREALCONVERTER_H__A82B8802_19BA_49a7_AA4C_94E1AA76C9D5__INCLUDED_)
#define AFX_CHARTREALCONVERTER_H__A82B8802_19BA_49a7_AA4C_94E1AA76C9D5__INCLUDED_

class CRealData_Common
{
public:
	CString m_strCode;
	CString m_strTime;
	CString m_strSign;
	CString m_strPrice;
	CString m_strChange;
	CString m_strChrate;
	CString m_strVolume;

	CString m_strOpen;
	CString m_strHigh;
	CString m_strLow;
};

class CChartRealConverter
{
public:
	//	FX 시세
	static BOOL Convert_a(LPCSTR pRealStruct, CRealData_Common& realData_Common, short nTime);

	// 주식
	static BOOL Convert_KXS3(LPCSTR pRealStruct, CRealData_Common& realData_Common);

	// 업종
	static BOOL Convert_IXIJ(LPCSTR pRealStruct, CRealData_Common& realData_Common);

	// 선물
	static BOOL Convert_FFC0(LPCSTR pRealStruct, CRealData_Common& realData_Common);

	// 옵션
	static BOOL Convert_OOC0(LPCSTR pRealStruct, CRealData_Common& realData_Common);

	// 해외
	static BOOL Convert_HWFJ(LPCSTR pRealStruct, CRealData_Common& realData_Common);
};

#endif //AFX_CHARTREALCONVERTER_H__A82B8802_19BA_49a7_AA4C_94E1AA76C9D5__INCLUDED_
