// ChartItem.h: interface for the CChartItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTITEM_H__11999AEF_8200_4DA5_B205_33C1402F54D5__INCLUDED_)
#define AFX_CHARTITEM_H__11999AEF_8200_4DA5_B205_33C1402F54D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>


#include "ChartItemData.h"

//#include "../Chart_common/KBChart_ocx/kbchart.h"
//#include "../Chart_common/HMCChart_ocx/hmcchart.h"
#include "../../DrCommon/DRChartOcx.h"
#include "../../inc/ExOCXDLL.h"

#define HEIGHTOFTITLEBUTTON		(15)
#define WIDTHOFTITLEBUTTON		(15)
#define POSXOFMAXMIZE			(18)
#define POSYOFMAXMIZE			(1)
#define POSXOFINIT				(2)
#define POSYOFINIT				(1)
//#define SIZEOFSIGNAL			(18)
#define SIZEOFSIGNAL			(18)
#define SIZEOFCHECK				(14)

typedef struct __STHIGHLIGHTCHARTINFO {
	CString			m_strJongmokCode;
	CChartItem*		m_pChartItem;
}stHighlightChartInfo;
typedef CList<stHighlightChartInfo,stHighlightChartInfo> CHighlightChartInfoList;

// 복수종목 관리 : 복수종목 - ojtaso
typedef struct _ST_CHARTITEM_REALDATA
{
	CString	m_strItemName;
	UINT m_nRefCount;

	char m_chSign;
	CString m_strPrice;
	CString m_strChange;
	CString m_strChrate;
	CString m_strVolume;

	CString m_strOpen;
	CString m_strHigh;
	CString m_strLow;

	BOOL	m_bIsRealJang;		// 장시작 여부 (TRUE : 장시간, FALSE : 시간외, 장전등..)
}ST_CHARTITEM_REALDATA;

//=============================================================================================================
//08.17 Real 처리....
//=============================================================================================================

//#include "../../COMMON_BASE/DrChart/BaseDesk2HW.h"
//#include "../../COMMON_BASE/DrChart/IRealTableMgr.h"
//#include "../../COMMON_BASE/DrChart/ISharedDataMgr.h"

//#include "../../../include/SharedBase.h" // By 두리 20050603

//신호등 공유 모듈 관련 추가 =========================================
//05. 08. 24
//#include "../chart_common/ShareManager.h"
#include "../chart_common/ILButton.h"
//====================================================================
#define CODE_LEN	6
struct stChartSign
{
	int  nSignal;
	char RepresentCode[CODE_LEN];
};


typedef BOOL ( WINAPI *FnGetRealRecordInfo)( long p_lRealDataAddress, WORD &p_wRealRecordID, CString &p_strRealKeyCode);
typedef BOOL ( WINAPI *FnGetData)( long p_lRealDataAddress, WORD p_wRealItemID, double &p_dData);

//=============================================================================================================
class CChartItem : public CDRChartOcx//, public ISharedDataMgr, public IRealTableMgr, public CSharedBase
{

public:	
	CShareInputData	*m_pShareInputData;

	// 비교차트의 타입설정.
	char m_chCompareChartType;	
	void SetCompareChartType(char cType);

	void	SetNew_BNormalizedMinuteTimeRule(BOOL bFakeCandle);

	const char* GetNextKey(BOOL bMarket=FALSE);  //현재 받는 데이터의 다음 연속 조회를 하기 위한 연속키를 리턴한다.

	void SetNew_OnePageDataCount(int nPCnt);

	void SetChartRequestType(char chType);

public:
	BOOL m_bReceivedDataChart; //차트에 데이터를 한번도 안 받는 경우 에는 FALSE;


	// 주식 스탑오더와 연동하기 위해...
	void* m_pStdDialog;

	void OpenSignalMapScr();

private:
	CString m_strOldCode, m_strNewRequestCode;
	int m_nCntCompare; //비교차트 추가된 항목갯수를 센다.
	
public:
	void	SetOldChartCode(CString strCode);
	CString GetOldChartCode() { return m_strOldCode; }
	//@.080730-001
	LPCSTR  GetNewRequestCode() {return (LPCSTR)m_strNewRequestCode;}
	//===============================================================================================

public:
	CChartItem();

		//비교차트에 추가된 종목을 삭제한다.	
	BOOL	RemoveGraphTitle(int nRow, int nCol, CString strCode, CString strJMName, BOOL bIsOnlyNoTRData);
	
	//===============================================================================================	
	void SetKorName(CString strKorName)		{ m_strKorName = strKorName;	}
	CString GetKorName()					{ return m_strKorName;			}
	//===============================================================================================	

	void SetAutoSaveToOutside(const bool bAutoSave);		// 자동 저장 여부
	//===============================================================================================
	BOOL SetPacketData(LPCTSTR szPacketName, long szData, long nLength, BOOL bReset); // added by gm0604 2005.10.10

private:
	// 시작 날짜 Flag 및 변경 저장 
	CString m_strStartDate, m_strEndDate;

public:
	//09.06	
	void SetEndDate(LPCTSTR endDate)     ;

	//08.25	
	void SetStartDate(LPCTSTR startDate)   { m_strStartDate = startDate; }	
	void SetStartDateFlag(BOOL bStartDate) { m_CfgInfo.bStartDate = bStartDate ? true : false;	}
	//===============================================================================================
	
	int m_nMarketType;

	CString				m_strImagePath;
	void				SetImagePath(CString strPath) { m_strImagePath.Format("%s\\Image", strPath); }
	
//	CShareManager		m_ShareManager;
	void				InitShareManager();
//	void				CloseShareManager();

	CImageList*			m_pIL_Symbol;			// Symbol Image List
	enum				e_SIGTYPE{ e_NKS = 1 , e_SAS = 2 , e_UAS = 3 };
	int					GetSignalImageIndex_FromSignalDegree(int nType, int nSignalDegree);
	void				SetSignalData(CString sShareName, BYTE* pData, int nLen);

	//==================================================================
	// 차트 모양 캔들 바, 삼선, 등등 
	CString m_strChartLineType;
	void	SetChartLineType(CString strLineType) {	m_strChartLineType = strLineType ;}

	//==================================================================
	// 차트 환경 적용 정보
	CHART_CONFIG_INFO	m_CfgInfo;
	void				Init_ChartCfgInfo();
	void				SetChartConfigInfo(CHART_CONFIG_INFO &ChartCfgInfo);
	CHART_CONFIG_INFO*	GetChartConfigInfo(){ return &m_CfgInfo;}
	//==================================================================

	//==================================================================
	// 차트의 원, %, $의 구분관련 
	int  m_nChartNumericValueType;
	void SetChart_NumericValueType(int nValue);
	int	 GetChart_NumericValueType(){return m_nChartNumericValueType;}
	void SetChartNumericValue(int nNumericValue);
	//==================================================================

	//==================================================================
	void	SetUseLogValue(BOOL bUse);
	//==================================================================

	BOOL Create(CWnd *pWnd,LPRECT lpRect,int nID,long lRow,long lCol, LPCTSTR lpImagePath, BOOL bUseInnerControl);
	void SetInit(long p_lDllWnd, long lKey, LPCTSTR strHtsPath, BOOL bNoToolBar =FALSE);
	long ReceiveInitalChartData(void* szData, long nLength);
	// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
	long ReceiveLoadingChartData(void* szData, long nLength);
	void ResetOCX(BOOL bNotCodeInputInit = TRUE); //bNotCodeInputInit 종목코드 부분을 초기화 하지 않는게 Default
	void DrawTitle(CRect rectIn,CDC* pDC,CFont *pFt,CFont *pFtNormal, COLORREF crBackIn);
	//void DrawTitle(CRect rectIn,CDC* pDC,CFont *pFt,COLORREF crBackIn);
	void SetButton(const LPRECT lpRect);

	//==========================================================================================
	//void SetCodeForQuery(LPCTSTR lpCode, UINT nQueryType, BOOL bIsPrimaryData);
	//2005. 05. 06 숫자형 TRCode를 안 쓴다.
	void SetCodeForQuery(LPCTSTR lpCode, CString strQueryType, BOOL bIsPrimaryData);
	//==========================================================================================
	
	BOOL IsEmpty() { return	(!m_bInitalChart);}
	BOOL AddChartBlock(LPCTSTR lpChartName);
	BOOL DestroyWindow();
	void SetSmallChartMode(INT nSmallChartMode) { m_nSmallChartMode = nSmallChartMode;}
	
	void SetType(char chType);
	char GetTypeRequested();
	char GetType();

	void	SetTickMinDayNumber(UINT nNumber);
	CString GetTickMinDayNumberRequested() {return m_strTickMinDayForRequest;}
	

	//=======================================================================
	//2005. 05. 24 add by sy, nam
	//별도로 틱분일 값을 가져야 하므로 새로이 추가했음.
	//CString GetTickMinDayNumber() {return m_strTickMinDay;} //각 기간별 값을 리턴해야 하므로 
	//기존의 하나의 값을 가지는 함수는 주석처리하고 새로이 정의 한다.
	CString m_strTick,m_strMin,m_strDay, m_strHour;

	CString GetTickMinDayNumber(int nChartType = -1);

	CString GetTickNumber()	;
	CString GetMinNumber()	;	
	CString GetDayNumber()	;	
	CString GetHourNumber()	;
	
	void SetTickNumber	(CString strValue);
	void SetMinNumber	(CString strValue);
	void SetDayNumber	(CString strValue);
	void SetHourNumber	(CString strValue);


	void LoadTickMinDayInfo(CString stCfgFile);
	//=======================================================================

	void	SetEndDateRequested(LPCTSTR lpDate);
	CString GetEndDateRequested();
	CString GetEndDate();
	CString GetStartDate() { return m_strStartDate;	}

	void SetCntForRequest(UINT nCntForRequest);
	long GetCntForRequest();
	long GetAllCnt() { return m_lAllCnt;}
	UINT GetID() { return m_nID;}
	// 복수종목 추가 : 복수종목 - ojtaso (20070118)
	CString GetQueryData(BOOL bChangeType = FALSE);
	CString GetDataCode(int nIndex = 0);
	CString GetDataTRCode(int nIndex = 0);
	BOOL HasGraph(LPCTSTR p_szGraphName);

	// 비교중첩 스타일의 리얼처리
	void SetRealPriceData(void *pData, long lDataKind);

	// 등락률 스타일의 리얼처리
	void SetRealPriceDataFluct(void *pData, long lDataKind);

	BOOL IsOnDrdsAdvise() { return m_bOnAdvise;}
	CString GetTrCodeForQuery();
	
	//2005. 06. 13 sy, nam   
	//		==>	bSetChartTick =현재 조회 단위를 차트저장 파일에서 읽지 않고자 할때 False로 한다.
	//2005. 09. 05 sy, nam   
	//		==>	bNotCodeInputInit = 종목코드 부분의 문자열을 초기화 하지 않고자 할때 FALSE로 한다.
	BOOL LoadChartInfo(LPCTSTR lpTitle, BOOL bSetChartTick =  TRUE, BOOL bNotCodeInputInit = TRUE);
	
	BOOL SaveChartInfo(LPCTSTR lpTitle, BOOL bOnlyJongmok =FALSE);
	BOOL LoadChartSetting(LPCTSTR lpTitle);
	BOOL SaveChartSetting(LPCTSTR lpTitle);
	BOOL ResetChart();
	BOOL IsPrimaryChartItemData(CChartItemData *pChartItemData);
	//BOOL HasChartItemData(LPCTSTR lpCode, UINT nQueryType, BOOL bFindWithPrimaryData, BOOL bAutoRemoveUselessData = TRUE);
	//BOOL RemoveChartItemData(LPCTSTR lpCode, UINT nQueryType);
	//한화에서 TR Code는 문자열로 해서....
	BOOL HasChartItemData(LPCTSTR lpCode, CString strQueryType, BOOL bFindWithPrimaryData, BOOL bAutoRemoveUselessData = TRUE);
	BOOL RemoveChartItemData(LPCTSTR lpCode, CString strQueryType);
	
	// 복수종목 저장 : 복수종목 - ojtaso (20070118)
	void SaveRQInfo(LPCTSTR lpszAppName, LPCTSTR lpszTitle);
	// 복수종목 로드 : 복수종목 - ojtaso (20070118)
	void LoadRQInfo(LPCTSTR lpszAppName, LPCTSTR lpszTitle);
	
	CChartItemData *FindChartItemDataForQuery();
	long GetCntOfItemData() { return m_arrayChartItemData.GetSize();}
	BOOL	ClearData();
	BOOL	ClearDataExceptPrimaryData();
	BOOL GetNext() {return m_bNext;}
	void SetNext(BOOL bNext);
	BOOL SaveandOpenFromFile(LPCTSTR strOpenFileName, LPCTSTR strSaveFileName, BOOL bOpenOption, BOOL bSaveOption);
	CChartItemData *GetPrimaryChartItemData();
	void SetUseRevisedValue(BOOL bUse);	
	BOOL GetUseRevisedValue();
//	void SetUseRateValue(BOOL bUse);
	void SetBNormalizedMinuteTimeRule(BOOL bUse);
	//BOOL GetUseRateValue() {return m_bRateValue;}
	
	

	void SetRowNCol(long lRowIndex, long lColIndex);
	void HideScale(BOOL bHide);
	void HideInnerToolBar(BOOL bHide);
	void InvalidateType();
	BOOL PtInRectJongmokTitle(POINT point) const;
	void ResetChartCfgWith(short p_nIndex);
//	BOOL GetCheck() { return m_Check.GetCheck();}
//	void SetCheck(BOOL bCheck) { m_Check.SetCheck(bCheck); }
	long GetTempOnePageDataCount();
	CString GetQueryDataForGuideLine(const CUIntArray* pAryAvgForChartGuideLine);
	void ShowLock(BOOL bShow);
	BOOL SendMessageToInvoke(short nCommandType, long lData, long lSize);

private:	
	//==================================================================
	// 2005. 05. 18 add by sy, nam
	int		m_nCntOverLap;  // 중첩된 종목 Cnt;
	BOOL	m_bOverLapping; // 중첩 모드 Flag
	BOOL	m_bLogPrice;	// LOG 사용
	//==================================================================
	
private:
	/// System Trading gm0604	2005.7.21
	long m_lPtrST;
	CString m_strName;	// System Trading Module Name
	CStringArray m_strArrayNameBySystemTradingTab;
	/// System Trading gm0604	2005.7.21
	BOOL DestoryItemData();
	BOOL BuildChart();
	BOOL SetAllProperties(BOOL bNoToolbar =FALSE);
	BOOL SetDrdsAdvise(long lOnAdvise);
	void ResetData();
	void InitialStartDate();
	//CChartItemData *GetChartItemDataNew(long lTrCode,LPCTSTR lpCodeForQuery, BOOL bCreateIfNoExist=TRUE,BOOL bIsPrimaryData = FALSE);
	//long GetPosChartItemData(long lTrCode,LPCTSTR lpCodeForQuery);
	CChartItemData *GetChartItemDataNew(CString strTRCode,LPCTSTR lpCodeForQuery, BOOL bCreateIfNoExist=TRUE,BOOL bIsPrimaryData = FALSE);
	long GetPosChartItemData(CString strTRCode,LPCTSTR lpCodeForQuery);
	
	CArray <CChartItemData*,CChartItemData*> m_arrayChartItemData;
	CArray <CChartItemData*,CChartItemData*> m_arrayChartItemDataBackup;
	BOOL	m_bUseInnerControl;
	BOOL	m_bBuild;	// 조회 후 차트가 구성되었는지를 의미 (ResetOCX 하면 False)
	BOOL	m_bOnAdvise;
	BOOL	m_bInitalChart;
	BOOL	m_nSmallChartMode;	// 0:NONE 1:No Volume Graph&No Scroll Graph 2:No Scroll Graph
	long	m_lNOnePageDataCount;

	char	m_chTypeForRequest;	// 데이터조회하기전 틱(0)/분(1)/일(2)/주(3)/월(4)
	char	m_chType;		// 틱(0)/분(1)/일(2)/주(3)/월(4)
	CString m_strDateForRequest;
	//CString m_strDate;		// 8Byte 검색 시작일
	long	m_lCntForRequest;
	long	m_lAllCnt;

	CString m_strTickMinDayForRequest;	// 2005. 05. 23 add by nam 틱/분/일의 요청 단위 를 저장하고 있다.
	CString m_strTickMinDay;			// 2005. 05. 23 add by nam 틱/분/일의 요청되어 받은 단위 를 저장하고 있다.2Byte Tick Min Number
	//CString m_strTickMinForRequest;	// 2Byte Tick Min Number
	//CString m_strTickMinDay;			// 2Byte Tick Min Number
	
	UINT	m_nNum;			// 검색할 데이터 갯수
	BOOL	m_bRevisedPrice;


//	BOOL	m_bRateValue;



	CString m_strKorName;		// 종목명
	CString m_strPrice;			// 현재가
	CString m_strChange;		// 대비
	CString m_strChrate;		// 대비율
	CString m_strVolume;		// 거래량
	//2006.10.09 by LYH 시가, 고가, 저가 추가
	CString m_strOpen;			// 시가
	CString m_strHigh;			// 고가
	CString m_strLow;			// 저가
	char	m_chSign;
	long m_lColIndex;
	long m_lRowIndex;
//	CILButton m_btMaxmize;
	CILButton m_btInit;
	
//	CButton	m_Check;
	UINT	m_nID;	// ID For Chart Component
	BOOL	m_bNext;
	CRect	m_rectTitleJongmok;
	CRect	m_rectTitleType;
	CRect	m_rectTitlePos;
	CRect	m_rectTitleJongmokPast;
	CRect	m_rectTitleTypePast;
	CRect	m_rectTitlePosPast;
	BOOL	m_bShowLock;

	long	m_plDllWnd;
	CStringList m_listAddIn;


// Operations
public:

	
// Overrides
// Implementation
public:
	
	void Add_OverLappedCnt();
	void Init_OverLapped();
	virtual ~CChartItem();	

//	//{{AFX_MSG(CTOcx)
//	afx_msg void OnOnLButtonDownTocxctrl1(short p_n, short p_sz);
//	DECLARE_EVENTSINK_MAP()
//	//}}AFX_MSG


//===================================================================================================================
// 2005. 08. 17 added by 배승원 
// 차트 리얼 신규 처리 
// >>>>>>>>> Start ==================================================================================================
	// * CBaseDesk의 구현
	class CXIBaseDesk : public CBaseDesk2
	{
	public:
		LPDISPATCH m_pDisp;
		CXIBaseDesk() : m_pDisp(NULL) {}
		~CXIBaseDesk() { if(m_pDisp) m_pDisp->Release(); }

//		void Initialize();

		// * CBaseDesk Virtual 구현
		virtual LPCSTR GetBasePath() ;
		virtual HWND  GetDeskHwnd() ;
		virtual LPDISPATCH GetUnknown();
		virtual LPUNKNOWN GetCtrlUnknown(LPCTSTR szName) ;
		virtual HWND GetCtrlHwnd(LPCTSTR szName);
		virtual LPVOID GetSharedInterface();
		virtual BOOL InvokeEvent(HWND _hWnd, LPCSTR _szEventName, LPCSTR _szParam);
		virtual BOOL InvokeEvent2(LPCSTR _szCtrlName, LPCSTR _szEventName, LPCSTR _szParam);
		virtual BOOL SendKey(HWND _hWnd, UINT nChar, BOOL _bIsShift, BOOL _bIsCtrl);
		virtual LPVOID GetLSharedData();
		virtual void CallCommand(LPCSTR _szCmd);

		// CBaseDesk2에서 추가되는 내용들
		virtual OLE_COLOR GetUserColor(short nIndex, LPCTSTR szName, short nFlag);
		virtual long GetDeskInfo(LPCSTR szKey);
		virtual long GetUserInfo(LPCSTR szKey);
		virtual long GetFrameInfo(LPCSTR szKey);
		virtual long GetMainInfo(LPCSTR szKey);

//* 수정 시작 (2002.8.22 001) 모니터링 툴 추가
		virtual BOOL FP_vAdviseDebug(LPCSTR sName, UINT pMonitoringCommand);
		virtual void FP_vUnadviseDebug(LPCSTR sName, UINT pMonitoringCommand);
		virtual LPCSTR FP_sGetMyVBName(HWND hWnd);
		virtual void FP_vSendDebug(LPCSTR csSection, LPCSTR csKey, LPCSTR csValue);
//* 수정 끝 (2002.8.22 001) 

		// CControlPos의 m_awndControls 맴버변수의 포인터를 리턴한다.
		// 이 변수는 리사이즈 될 컴포넌트의 정보를 들고 있다.
		virtual long FP_nGetCtrlPos();

		// 컴포넌트를 리사이즈 시킨다.
		virtual void FP_vResizeCtrl();

		// {{ OCX에서 DESK로 메세지 보낼 수 있도록 요청(김용식) 2003.05.19
		virtual void SetMapMessage(long lType, LPCSTR lpData);
		// }}

		// 데스크에게 정수형 리턴값을 원하는 명령을 보내는 함수
		// nCommand
		// 100 : Socket 헨들을 요청한다.
		virtual int FP_nGetDataInt(int nCommand);

		friend class CChartItem;

	} m_xIBaseDesk;
	friend class CXIBaseDesk;
	CXIBaseDesk *m_pBaseDesk2;

// (2005/8/10 - Seung-Won, Bae) Shared Data Manager Routine for SkcChart OCX
protected:
	// Flag, if on Shared Data Transfering
	BOOL			m_bSharedOn;
//protected:
//	virtual long	ChangeSharedData(CString sSharedName, BYTE* pData, int nLen, int nStock);
//protected:
//	virtual BOOL	AdviseSharedData( const char *p_szShareName, int p_nShareType, int p_nShareArea);
//	virtual BOOL	UnadviseSharedData( const char *p_szShareName);
//	virtual BOOL	GetSharedData( const char *p_szShareName, CString &p_strSharedData);
//	virtual BOOL	FireSharedData( const char *p_szShareName, const char *p_szSharedData, long p_lCodeFilter);

// (2005/8/13 - Seung-Won, Bae) Support Real Table Manager Interface
// 1. Init Real Table Tree Control
//protected:
//	virtual BOOL	InitRealTableTreeControl( CTreeCtrl *p_pTreeCtrl);
// 2. Retreive the Record and Item Info
//protected:
//	virtual BOOL	GetRealIDs( const char *p_szRecordName, const char *p_szItemName, WORD &p_wRecordID, WORD &p_wItemID);
//	virtual BOOL	GetRealNames( WORD p_wRecordID, WORD p_wItemID, const char *&p_szRecordName, const char *&p_szItemName);
// 3. Advise & Unadvise Real Update
//public:
//	virtual BOOL	AddRealUpdate( WORD p_wRealRecordID, const char *p_szRealKeyCode);
//	virtual BOOL	ResetRealUpdate( WORD p_wRealRecordID, const char *p_szRealKeyCode);
// 4. Retreive the Real Data
protected:
	// To make a Library DLL for Real Data Fatch Code
	HMODULE				m_hmCtlDrChart;
	FnGetRealRecordInfo	m_fnGetRealRecordInfo;
	FnGetData			m_fnGetData;

	CString				m_strRealItemCode;		// 실시간 수신받은 종목코드 : 복수종목 - ojtaso (20070108)
	CString				m_strSelectedItemCode;	// 현재 선택된 종목코드 : 복수종목 - ojtaso (20070108)
public:	
	void InitChartItem_FromExtToolBar();
//	DWORD GetCodeType_By_DBMgr(CString strCode);
	BOOL			AddInEvent_FromChart(LPCSTR _szParam);
//	virtual BOOL	GetRealRecordInfo( long p_lRealDataAddress, WORD &p_wRealRecordID, CString &p_strRealKeyCode);
//	virtual BOOL	GetData( long p_lRealDataAddress, WORD p_wRealItemID, double &p_dData);
//<<<<<<<<<<<<<< End =======================================================================================================
	//2006.01.23 추가 by LYH
	void PrintChart();
	void SetExcelData();

//2006.04.04 추가 by LYH
	int m_nSaveAllCount;
	void SetSaveAllCount(int nAllCnt);

	BOOL m_bAddInLoadPattern;
	BOOL InvokeAddInPattern(LPCTSTR p_szAddInDllName, short p_nCommandType, long p_lData);
	BOOL m_bAddInLoadPeriod;
	BOOL InvokeAddInPeriod(LPCTSTR p_szAddInDllName, short p_nCommandType, long p_lData);
	BOOL m_bAddInLoadSTIndex;
	BOOL InvokeAddInSTIndex(LPCTSTR p_szAddInDllName, short p_nCommandType, long p_lData);
//	BOOL m_bAddInLoadNews;
//	BOOL InvokeAddInNews(LPCTSTR p_szAddInDllName, short p_nCommandType, long p_lData);

	// 수정주가 클릭시 전체수 고정시키기 위해 추가 by LYH 2007.01.11
	int m_nTotCountForRevised;

	//2007.01.17 add by LYH  툴바버튼 동기화
	BOOL m_bDrawAutoTrendLine;
	BOOL m_bDrawAutoPattern;
	BOOL m_bDrawCandlePattern;
	BOOL m_bDrawNews;

	// 복수종목 관리 : 복수종목 - ojtaso
	CMapStringToPtr		m_mapChartItem;
	CMapStringToPtr		m_mapChartItemRealData;

	// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
	BOOL m_bLoadRQ;
	BOOL IsLoadingRQ() { return m_bLoadRQ; }

	CString GetSelectedRQ() { return m_strSelectedRQ; };

	POSITION m_posLoadingRQ;
	CString m_strKey;
	ST_SELCHART* m_lpSelChart;

	CString m_strSelectedRQ;

	BOOL m_bLoadDefaultRQ;

	// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
	CString GetLoadedQueryData();

	//2007.01.25 add by LYH  코드로 시장구분 읽어오기
	int GetMarketType(CString strCode);
//@유진삭제
//	CString GetLastKey(int iKeyType);
//@유진삭제
//@유진추가
	CString GetLastHistoryCode(int nMarketType);
	CString GetQueryOpt();
//@유진추가

	// 복수종목 추가 모드인지 : 복수종목 - ojtaso (20070119)
	BOOL IsAddMode();

	// 복수종목 선택 : 복수종목 - ojtaso (20080215)
	void OnSelectChartItem(ST_SELCHART* pSelChart, BOOL bInitKey = TRUE);
	// 복수종목 삭제 : 복수종목 - ojtaso (20080215)
	void OnDeleteChartItem(LPCTSTR lpszRQ, ST_SELCHART*& pSelChart);

	// 선택된 차트 정보는 외부dll에서 관리토록 수정 : 복수종목 - ojtaso (20070504)
	void AddChartItem (CChartItemData* pChartItemData, LPCTSTR lpszItemCode, LPCTSTR lpszItemName, char cType, LPCTSTR lpszTickMinDayNumber, long lCount, long lChartNumericValueType, BOOL bBuiltChart);
	BOOL GetSelChart(LPCTSTR lpszRQ, ST_SELCHART*& pSelChart);

	// 종목코드로 RQ를 찾고 선택 : 복수종목 - ojtaso (20070705)
	BOOL FindSelectChartByItemCode(LPCTSTR lpszItemCode, BOOL bSelect = TRUE);
	
	// RQ Count리턴
	int GetRQCount();

	CString GetSelectedItemCode() { return m_strSelectedItemCode; };
	BOOL IsAvailibleCode(LPCTSTR lpszCodeName);

	void ResetRQ();

	// 분차트 마지막 키인 경우 - ojtaso (20071226)
	void EnableRequestMoreButton(BOOL bEnable);

#ifdef _WRITELOG
	// Log - ojtaso (20080107)
	void WriteToStringLog( const char *p_szSection, const char *p_szData, int p_nDataLen);
#endif

	void SaveRQInfo(LPCTSTR lpszAppName, LPCTSTR lpszTitle, int cType);
	void fnChartFluct(int nType);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_CHARTITEM_H__11999AEF_8200_4DA5_B205_33C1402F54D5__INCLUDED_)
