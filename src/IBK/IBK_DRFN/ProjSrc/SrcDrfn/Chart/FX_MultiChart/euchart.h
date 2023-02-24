#if !defined(AFX_EUCHART_H__412D85CD_2BD4_4e53_AED5_CE2702E0AE32__INCLUDED_)
#define AFX_EUCHART_H__412D85CD_2BD4_4e53_AED5_CE2702E0AE32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CEuChart wrapper class

class CEuChart : public CWnd
{
protected:
	DECLARE_DYNCREATE(CEuChart)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xd770fcc4, 0x4cc2, 0x4cc0, { 0xa2, 0x64, 0x5a, 0x9b, 0xdf, 0x95, 0x25, 0x69 } };
		return clsid;
	}

	CEuChart();
	virtual ~CEuChart();


    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL);

	//===========================================================================================
	// 2007. 01. 05 추가
	// 입력 data를 binary로  처리
	BOOL SetBinTrHelpMsg(LPCTSTR p_szHelpMessage);
	BOOL SetBinTrDoubleData(LPCTSTR p_szPacketName, long p_nCount, double* p_pdData);
	BOOL SetBinTrStringData(LPCTSTR p_szPacketName, long p_nCount, long p_lData);
	BOOL SetBinTrEnd();

protected:
	DISPID *			m_pdID;
	static OLECHAR *	m_osInterfaceName[];

// Attributes
public:
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	OLE_HANDLE GetHWnd();
	void SetHWnd(OLE_HANDLE);
// Operations
public:
	typedef enum {
		IIx_SetBaseDesk,
		IIx_GetBase,
		IIx_AddGraph,
		IIx_AddPacket,
		IIx_RemovePacket,
		IIx_GetIndicatorNameList,
		IIx_SetContainerDllInfo,
		IIx_SetChartData,
		IIx_SetPacketData,
		IIx_AddChartBlock,
		IIx_ResetChart,
		IIx_SetBackgroundColors,
		IIx_SetDrdsAdvise,
		IIx_AddRealItem,
		IIx_ShowIndicatorConfigDlg,
		IIx_NOnePageDataCount,
		IIx_StrStartDateOfData,
		IIx_ResetChartCfgWith,
		IIx_EmptyChart,
		IIx_HasGraph,
		IIx_RemoveRealItem,
		IIx_SaveandOpenFromFile,
		IIx_ClearChartData,
		IIx_ShowInnerToolBar,
		IIx_ChangeVertScalePosition,
		IIx_GetRowBlockCount,
		IIx_GetColumnBlockCount,
		IIx_ChangeHorzScalePosition,
		IIx_RemoveChart,
		IIx_SetStartPeriodOfPacket,
		IIx_GetStartPeriodOfPacket,
		IIx_StrUserIndicatorListFileName,
		IIx_StrUserEnvironmentFileName,
		IIx_GetStartEndDateOnView,
		IIx_SetStartEndDateOfView,
		IIx_ScrollToDataOfEnd,
		IIx_ZoomToWithRightFix,
		IIx_ClearTimeMark,
		IIx_ShowEnvironmentDlg,
		IIx_SetTimeMark,
		IIx_BOcxAreaNumericalInquiry,
		IIx_OnRunningOneChart,
		IIx_EnableBoundMark,
		IIx_EnableReceivingTimeShare,
		IIx_ChangePacketType,
		IIx_ChangePriceGraphDrawingData,
		IIx_NUseInquiryWithCrossline,
		IIx_BShowPriceRateInquiry,
		IIx_BNormalizedMinuteTimeRule,
		IIx_HasGraphInSpecialBack,
		IIx_InvokeAddIn,
		IIx_LoadAddIn,
		IIx_SetDragModeType,
		IIx_SetHtsPath,
		IIx_SetAllLogScale,
		IIx_GetListViewerData,
		IIx_SetDataIndexByDate,
		IIx_SetRunTimeMode,				//2005. 07. 15 이후 추가 
		IIx_GetPacketOption,
		IIx_SetPacketOption,
		IIx_SetOutsideCommonInterface,
		IIx_RemoveGraph_Title,
		IIx_RemoveGraph,
		IIx_GetGraphPacketName,
		IIx_ChangeGraphTitle2,
		IIx_PartitionAllGraph,
		IIx_JoinAllGraph,
		IIx_SetBSelectTitle,
		IIx_ChangeAllFunctionName,
		IIx_ChangeIndicatorPacketName,
		IIx_RunEnvironmentDlg,
		IIx_SetIndicatorCondition,
		IIx_SetLogScale,
		IIx_GetLogScale,
		IIx_SetHelpMessageRealDataRate,
		IIx_InvokeAddInStr,
		IIx_SetGraphHide3,
		IIx_SetOnePageDataCount2,
		IIx_SetPacketDataInAdditionPacket,
		IIx_SetOnePageDataCount,
		IIx_SetPacketHelpMessage,
		IIx_SetRealData,
		IIx_PrintChatImage,
		IIx_ExportToExcel,
		IIx_LoadAddInWithOverExclusive,
		IIx_GetAllProperties2,
		IIx_SetAllProperties2,
		IIx_GetAllProperties3,
		IIx_SetAllProperties3,
		IIx_GetAddInCustomInterface,
		IIx_SetBinTrHelpMsg,
		IIx_SetBinTrDoubleData,
		IIx_SetBinTrStringData,
		IIx_SetBinTrEnd,
		IIx_ShowIndicatorConfigDlgWithName,
		IIx_BEnableIndicatorCalculation,
		IIx_StrChartList,
		IIx_BWholeView,
		IIx_EmptyChart2,
		IIx_AddChartItem,		// 복수종목에 사용되는 인터페이스 : 복수종목 - ojtaso (20070206)
		IIx_SetRealDataCode,	// 복수종목에 사용되는 인터페이스 : 복수종목 - ojtaso (20070206)
		IIx_AddPacketRQ,		// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
		IIx_SetPacketDataRQ,	// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
		IIx_AddChartItemRQ,		// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
		IIx_SetCurrentRQ,		// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
		IIx_RemoveGraphRQ,		// RQ로 차트제거.
		IIx_SetResetTotalCountWhileDraw,		// xScaleManager : xScaleManager - ojtaso (20070529)
		IIx_SetMultiItemMode,	//복수종목을 사용할지 : 복수종목 - ojtaso (20070904)
		IIx_ChangeGraphDrawingData,
		IIx_ChangeGraphTitle,
		IIx_AddChartAllBlock,	// 모든 RQ의 그래프의 차트 변경 - ojtaso (20080516)
		IIx_ChangeGraphPropertyAtOnce,	// 차트속성변경.
		IIx_ShowGraphDataDrawingData,	// 현재가표시여부 속성변경.
		IIx_ShowSelEnvironmentDlg,
		IIx_GetVertScaleGroupCount		// 현재 마지막 VertScaleGroup Index
	};
	// 가로 scale 위치
	enum HORZSCALEPOSITION
	{
		HORZ_TOP,
		HORZ_BOTTOM,
		HORZ_BOTH,
		HORZ_HIDE,
		HORZ_NONE
	};
	
	// 세로 scale 위치
	enum VERTSCALEPOSITION
	{
		VERT_LEFT,
		VERT_RIGHT,
		VERT_BOTH,
		VERT_NONE
	};

	long GetNNumericalInquiryOption();
	void SetNNumericalInquiryOption(long);
	CString GetStrGlobalSharedList();
	void SetStrGlobalSharedList(LPCTSTR);
	void SetStrStartDateOfData(LPCTSTR);
	
	void SetOnRunningOneChart(BOOL);
	BOOL GetBDoesUseSkinColor();
	void SetBDoesUseSkinColor(BOOL);

// Operations
public:
	void SetBaseDesk(long lKey);
	long GetBase(LPCTSTR szKey);
	void AddGraph(short nRow, short nColumn, short nVertScaleGroup, LPCTSTR szGraphOption, BOOL bCreateBlock, BOOL bCreateVertScaleGroup, BOOL bUseAutoScale);
	void AddPacket(LPCTSTR szPacketOption);
	void RemovePacket(LPCTSTR szPacketName);
	CString GetIndicatorNameList(LPCTSTR p_strGroup);
	void SetContainerDllInfo(long p_lDllWnd, short p_nID);
	short SetChartData(long pChartData, short nCount, short nType);
	BOOL SetPacketData(LPCTSTR szPacketName, long szData, long nLength, BOOL bReset);
	BOOL AddChartBlock(LPCTSTR strChartName);
	// 모든 RQ의 그래프의 차트 변경 - ojtaso (20080516)
	BOOL AddChartAllBlock(LPCTSTR strChartName);
	void ChangeGraphPropertyAtOnce(LPCTSTR lpszRQ, LPCTSTR lpszTargetTitle, LPCTSTR lpszNewTitle, short nGraphType, short nGraphStyle, short nDrawStyle, LPCTSTR lpszColors, short nThickness1, short nThickness2, short nThickness3);

	BOOL ResetChart();
	void SetBackgroundColors(unsigned long p_rgbBlockArea, unsigned long p_rgbScaleArea);
	BOOL SetDrdsAdvise(BOOL bOnAdvise);
	void AddRealItem(LPCTSTR szRealInfo);
	void ShowIndicatorConfigDlg();
	long GetNOnePageDataCount();
	void SetNOnePageDataCount(long propVal);
	CString GetStrStartDateOfData();
	void ResetChartCfgWith(short p_nIndex);
	BOOL EmptyChart(BOOL bIsDeleteAllPacket, BOOL bIsDefault);	// JSR 20060119 Modify (From ResetOCX())
	BOOL HasGraph(LPCTSTR p_szGraphName);
	void RemoveRealItem(LPCTSTR szRealInfo);
	BOOL SaveandOpenFromFile(LPCTSTR strOpenFileName, LPCTSTR strSaveFileName, BOOL bOpenOption, BOOL bSaveOption);
	short ClearChartData(short nOption);
	void ShowInnerToolBar(BOOL p_bShow);
	BOOL ChangeVertScalePosition(short nScalePosition, short nRowIndex, short nColumnIndex, short nVSGroupIndex);
	short GetRowBlockCount();
	short GetColumnBlockCount();
	BOOL ChangeHorzScalePosition(short nScalePosition, short nRowIndex, short nColumnIndex);
	BOOL RemoveChart(LPCTSTR strChartName);
	BOOL SetStartPeriodOfPacket(LPCTSTR p_szPacketName, long p_lStartPeriod, long p_bAddSpace);
	long GetStartPeriodOfPacket(LPCTSTR p_szPacketName);
	void SetStrUserIndicatorListFileName(LPCTSTR propVal);
	void SetStrUserEnvironmentFileName(LPCTSTR propVal);
	BOOL GetStartEndDateOnView(double* p_pStartDate, double* p_pEndDate);
	BOOL SetStartEndDateOfView(double p_dStartDate, double p_dEndDate);
	BOOL ScrollToDataOfEnd(double p_dData);
	short ZoomToWithRightFix(short p_nZoomValue, BOOL p_bWithRightFix);
	void ClearTimeMark();
	void ShowEnvironmentDlg();
	void ShowSelEnvironmentDlg(short nPage);
	void SetTimeMark(LPCTSTR p_szMarkTime, BOOL p_bWithScroll);
	void SetBOcxAreaNumericalInquiry(BOOL propVal);
	BOOL GetOnRunningOneChart();
	void EnableBoundMark(BOOL p_bEnable);
	void EnableReceivingTimeShare(BOOL p_bEnable);
	BOOL ChangePacketType(LPCTSTR p_szPacketName, LPCTSTR p_szPacketType);  
	BOOL ChangePriceGraphDrawingData(BOOL p_bLowHigh, BOOL p_bLowCur, BOOL p_bHighCur, BOOL p_bPrevCur, short p_nCurData, short p_nDefaultType);
	void SetNUseInquiryWithCrossline(short propVal);
	short GetNUseInquiryWithCrossline();
	BOOL GetBShowPriceRateInquiry();
	void SetBShowPriceRateInquiry(BOOL propVal);
	BOOL GetBNormalizedMinuteTimeRule();
	void SetBNormalizedMinuteTimeRule(BOOL);
	BOOL HasGraphInSpecialBack(LPCTSTR p_szGraphName);
	BOOL InvokeAddIn(LPCTSTR p_szAddInDllName, short p_nCommandType, long p_lData);
	BOOL LoadAddIn(LPCTSTR p_szAddInDllName);
	void SetDragModeType(short p_nDragModeType);
	void SetHtsPath(LPCTSTR pcszHtsPath);	
	void SetAllLogScale(BOOL bLogScale);

	//2005. 06. 28 add ===================================================================
	//데이터 리스트 뷰에 보일 값을 조회한다.
	void GetListViewerData(	BSTR* bstrTitle,
							BSTR* bstrHorzScale,
							BSTR* bstrPacketNamesPerBlock,
							BSTR* bstrPacketNames, 
							BSTR* bstrSaveFilePath,
							BOOL* bViewPacketSequence,
							long* lpPacketList); 
	//chart에 보이는 범위를 해당 매개변수의 값으로 셋한다. YYYYMMDDHHMMSS 형태로 넘긴다.
	void SetDataIndexByDate(LPCTSTR pcszStartDate, LPCTSTR pcszEndDate); 

	//2005. 07. 15 추가 =========================================================================		
	void	SetRunTimeMode(BOOL bRunTimeMode);
	CString GetPacketOption();
	void	SetPacketOption(LPCTSTR strPacketOption);
	void	SetOutsideCommonInterface(long lpOutsideCommonInterface);
	//===========================================================================================
	void	SetBSelectTitle(BOOL);


	//2005. 07. 19 추가 =========================================================================	
	BOOL	RemoveGraph_Title(short nRowIndex, short nColumnIndex, LPCTSTR szGraphTitle, BOOL bIsOnlyNoTRData, BOOL bIsAutoHorzScalePosition);
	BOOL	RemoveGraph(short nRowIndex, short nColumnIndex, LPCTSTR strGraphTitle);

	CString GetGraphPacketName(short nRowIndex, short nColumnIndex, LPCTSTR szGraphTitle);
	BOOL	ChangeGraphTitle2(LPCTSTR szTargetTitle, LPCTSTR szSourceTitle);
	BOOL	PartitionAllGraph();
	BOOL	JoinAllGraph(BOOL bIsOneVertScaleGroup);
	//===========================================================================================


	//2005. 07. 27 추가 =========================================================================
	// 비교차트 분할비교<->중첩비교<->누적등락률 중첩비교 간 전환을 알리는 Method
	BOOL ChangeAllFunctionName(LPCTSTR szTargetFunctionName, LPCTSTR szSourceFunctionName, BOOL bKeepOldGraphColor);
	//===========================================================================================

	//2005. 08. 11 추가 =========================================================================	
	BOOL ChangeIndicatorPacketName(LPCTSTR strIndicatorName, short nSubGraphIndex, LPCTSTR strNewPacketName);
	void RunEnvironmentDlg(short nOption);// 환경 설정 창 띄우는 
	BOOL SetIndicatorCondition(LPCTSTR strIndicatorName, short nConditionType, short nConditionIndex, short dValue, BOOL bReCalculate);
	//===========================================================================================
	


	//2005. 08. 23 추가 =========================================================================	
	BOOL SetLogScale(LPCTSTR strIndicatorName, BOOL bLogScale);
	BOOL GetLogScale(LPCTSTR strIndicatorName);	
	//===========================================================================================


	//2005. 09. 06 추가 =========================================================================
	//비교차트에 리얼 처리 방식이 바뀌어서 호출되는 메소드 
	// 나누기 100을 하라는 의미
	BOOL SetHelpMessageRealDataRate(LPCTSTR strHelpMessageData, BOOL bIsRemove);
	//===========================================================================================

	//2005. 09. 08 추가 =========================================================================
	BOOL InvokeAddInStr(LPCTSTR p_szAddInDllName, LPCTSTR p_szCommandName, LPCTSTR p_szData);
	//===========================================================================================

	//2005. 09. 14 추가 =========================================================================
	//비교차트에서 체크박스로 종목 해제시 화면에만 안 보이도록 처리.
	BOOL SetGraphHide3(LPCTSTR strTitle, BOOL bIsHide);
	//===========================================================================================


	//2005. 11. 02 추가 =========================================================================
	//주 차트에서 차트 여백을 포함한 형태(bIncludeRightMargin로 판단)로 보이게 하기위해..
	void SetOnePageDataCount2(long nOnePageDataCount, BOOL bIncludeRightMargin);
	//===========================================================================================

	//2005. 11. 09 추가 =========================================================================
	//시장 지표 TR을 차트에 보내기 위해 추가 
	BOOL SetPacketDataInAdditionPacket(LPCTSTR szPacketName, long szData, long nLength, BOOL bReset);
	//===========================================================================================

	//2005. 11. 09 추가 =========================================================================
	//페이지 데이터 카운트 수를 변경시킨다.
	//기존 SetNOnePageDataCount를 SetOnePageDataCount로 적용
	void SetOnePageDataCount(long nOnePageDataCount);
	//===========================================================================================


	//2005. 12. 06 추가 =========================================================================
	//복기 리얼 처리 
	BOOL SetPacketHelpMessage(LPCTSTR strHelpMsg, BOOL bIsAllRemove);
	void SetRealData(LPCTSTR strPacketName, double dData, short nOption);	
	//===========================================================================================
	//2006. 04. 05 추가 =========================================================================
	void PrintChatImage();
	void ExportToExcel();
	//===========================================================================================

	//===========================================================================================
	// 2006. 08. 24 추가
	BOOL LoadAddInWithOverExclusive(LPCTSTR p_szAddInName);
	long GetAllProperties2(long lpData);
	long SetAllProperties2(long lpData);	
	long GetAllProperties3(long p_lIPropertyMap);
	long SetAllProperties3(long p_lIPropertyMap);
	LPUNKNOWN GetAddInCustomInterface(LPCTSTR p_szAddInName);
	//===========================================================================================

	//===========================================================================================
	// 2006. 10. 27 추가
	BOOL ShowIndicatorConfigDlgWithName(LPCTSTR p_szIndicatorName);
	//===========================================================================================

	//===========================================================================================
	// 2006. 12. 12 추가
	BOOL GetBEnableIndicatorCalculation();
	void SetBEnableIndicatorCalculation(BOOL propVal);
	CString GetStrChartList();
	void SetStrChartList(LPCTSTR);
	BOOL GetBWholeView();
	void SetBWholeView(BOOL propVal);
	//===========================================================================================
	BOOL EmptyChart2(LPCTSTR p_szChartList, BOOL p_bIsDeleteAllPacket, BOOL p_bIsDefault);
	// 복수종목에 사용되는 인터페이스 : 복수종목 - ojtaso (20070206)
	CString AddChartItem(LPCTSTR lpszItemCode, LPCTSTR lpszItemName, BOOL bBuiltChart);
	void SetRealDataCode(LPCTSTR strCode, LPCTSTR strPacketName, double dData, short nOption);

	// 복수종목 불러오기 : 복수종목 - ojtaso (20070514)
	void AddPacketRQ(LPCTSTR lpszRQ, LPCTSTR lpszPacketOption);
	BOOL SetPacketDataRQ(LPCTSTR lpszRQ, LPCTSTR lpszPacketName, long nData, long nLength, BOOL bReset);
	BOOL AddChartItemRQ(LPCTSTR lpszRQ, LPCTSTR lpszItemCode, LPCTSTR lpszItemName);
	void SetCurrentRQ(LPCTSTR lpszRQ);
	BOOL RemoveGraphRQ(LPCTSTR lpszRQ, LPCTSTR lpszTitle);
	// xScaleManager : xScaleManager - ojtaso (20070529)
	void SetResetTotalCountWhileDraw(BOOL bReset);
	// 차트DLL에서 복수종목을 사용할지 : 복수종목 - ojtaso (20070904)
	void SetMultiItemMode(BOOL bMultiItem);

	BOOL ChangeGraphDrawingData(LPCTSTR p_szGraphName, BOOL p_bLowHigh, BOOL p_bLowCur, BOOL p_bHighCur, BOOL p_bPrevCur, short p_nCurData);
	BOOL ChangeGraphTitle(short nRowIndex, short nColumnIndex, short nGraphIndex, LPCTSTR strNewTitle);

	void SetBAddGraphMenuShow(BOOL);	//Menu셋팅

	// 현재가 표시여부 변경
	// bShow : LC/HC/LH 보여줄지 여부
	// nShowType : 그래프 yScal관련 보여줄지 여부.
	//		0 - Hide
	//		1 - 현재가 + 전일종가대비
	//		2 - 현재가 + 이전종가대비
	//		3 - 현재가
	//		4 - 화면상 종가
	BOOL ShowGraphDataDrawingData(LPCTSTR lpszRQ, LPCTSTR lpszIndicatorName, BOOL bShow, short nShowType);

	// 현재 마지막 VertScaleGroup Index
	long GetVertScaleGroupCount(short nRow, short nColumn);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EUCHART_H__412D85CD_2BD4_4e53_AED5_CE2702E0AE32__INCLUDED_)
