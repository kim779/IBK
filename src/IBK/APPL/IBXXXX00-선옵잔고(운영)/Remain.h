#pragma once
#include "afxtempl.h"

class CMapWnd;

class CRemain : public CWnd
{
public:
	CRemain();
	CRemain(CWnd* pMainWnd);

	virtual ~CRemain();

	//{{AFX_VIRTUAL(CRemain)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRemain)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	CMapWnd*	m_pParent;

	CString	m_code,			// 종목코드
		m_name,			// 종목명
		m_remain,		// 결제잔고(잔고수량)
		m_amt,			// 잔고수량
		m_pmaip,		// 평가매입, 평균단가
		m_pbep,			// BEP단가 20090527
		m_possible,		// 주문가능수량
		m_curr,			// 현재가(시세)
		m_rprice,		// 평가금액
		m_pgsonik,		// 평가손익
		m_psuik,		// 평가수익률
		m_maip,			// 매입금액
		m_date,			// 대출일
		m_symt,			// 신용대출금액
		m_creditS,		// 신용구분
		m_type,			// 잔고구분코드
		m_biyo,			// 수수료+세금
		m_omaip,		// 매입금액(원본)
		m_srate;		// 등락률(시세)

	char	m_system;
	bool m_betf, m_bchg;

	int m_dFee;//적용미적용
	double m_dMass;		//매체 수수료
	double m_dSave;		//SAVE 수수료
	int m_dCalcType;	//융자금 차감(0), 포함(1)
	int	m_iMcgb;		// 2015.04.22 KSJ 매체구분 0:HTS/MTS/홈페이지, 1:영업점/콜센터, 2:ARS
	bool m_b3RDCode;	// 2015.04.22 KSJ K-OTC인지 세팅
	double m_dTax;		// 2015.04.22 KSJ 세율
		
private:
	CMap <int, int, CString, CString>	m_mapCredit;
	CMap <int, int, CString, CString>	m_mapCreditX;

	double RoundDown(double data); //매체수수료(절삭)
	double Round(double data ); //0.003제세금(반올림)

public:
	double RoundDown2(double data);
	CString TotalData();
	void	ParsingRemainData(char *pData);
	void	ParsingAllaccnData(CString sData);
	int	CalRemainData(CMapStringToString &symbolMap, CString keyS, bool bNewCode);
	bool	CalPgsonik(CString currS, CString rateS, int noticeMode=FALSE);	//Notice에서 호출된건지
	void	FillString(CString& datS, int len);
private:
	CString parser(CString &srcstr, CString substr);
	CString getFormatData(CString src);
	CString	getCredit(CString creditS);
	CString	getCreditX(CString creditS);
public:
	void testSaveFile(CString strText);

};

