// IChartAddIn050116.h: interface for the IChartAddIn050116 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICHARTADDIN050116_H__1628D869_4373_4A7A_85B3_04D9026A7CE5__INCLUDED_)
#define AFX_ICHARTADDIN050116_H__1628D869_4373_4A7A_85B3_04D9026A7CE5__INCLUDED_

//////////////////////////////////////////////////////////////////////
// *. 주의!	050116 Version의 OCX에서 이용되는 AddIn측 Interface로 기능 추가만 가능합니다.
//		기능 삭제와 Type 변경은 허용하지 않습니다.
//		Interface 순서 변경 조차 허용되지 않습니다.
//		허용되지 않는 편집은 050116 Version의 모든 AddIn Module과 관련 Site OCX가
//			함께 수정되어 내려가는 것이 전제되어야 합니다.
// *. 050116 Version Info
//		AddIn Module				Site			Manager
//			ChartCustomAddIn			GZone			배승원
//			ChartPatternAddIn			GZone			정서정
//			ChartGuideLine				GZone			남상윤
//////////////////////////////////////////////////////////////////////

// (2004.10.08, 배승원) Chart AddIn Object의 Interface를 정의한다.
//		AddIn DLL 참조 Interface로 Macro Interface를 정의한다.
#if IChartAddInVer < 050116
	#define	IChartAddIn		IChartAddIn050116
	#undef	IChartAddInVer
	#define	IChartAddInVer	050116
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

interface IChartAddIn050116 : public IUnknown  
{
protected:
	virtual ~IChartAddIn050116()	{}

// (2004.10.13, 배승원) 기본 Manager가 등록되어 있는지 확인하는 Interface를 제공한다.
public:
	virtual BOOL	HasFullManager( void) = 0;

// [05/01/19] AddIn Object가 비정형 Interface를 제공할 수 있도록 제공한다.
public:
	virtual BOOL	InvokeAddIn( int p_nCommandType, long p_lData) = 0;

public:
	// [04/10/11] Global 공유를 전달하는 Interface를 제공한다.
	virtual void	OnGSharedDataChange( const char *p_szGShareKey, const char *p_szGShareValue, BOOL p_bStartShare) = 0;
	// [04/10/11] 외부 ToolBar의 Message를 전달하여 AddIn DLL에서도 처리할 수 있도록 한다.
	virtual void	OnExtTool( WPARAM wParam, LPARAM lParam) = 0;
	// [04/10/11] AddIn DLL들에게 ResetChart 상황을 알려 처리되도록 한다.
	virtual void	OnResetChart( void) = 0;
	// [04/10/11] Draw Event를 AddIn DLL에 알려 처리될 수 있도록 한다.
	virtual void	OnDrawBeforeGraph( CDC *p_pDC) = 0;
	// [04/12/25] Draw Event를 AddIn DLL에 알려 처리될 수 있도록 한다.
	virtual void	OnDrawAfterGraph( CDC *p_pDC) = 0;
	// [04/10/13] TR의 수신을 AddIn DLL들에게 알려 대응토록 한다.
	virtual void	OnPacketData( const char *p_szPacketNames, BOOL p_bWithReset) = 0;
	// [04/12/07] TR이나 Real의 수신에 의해 Packet Data가 Update되었음을 AddIn DLL들에 알려 지표등을 처리토록 한다.
	virtual void	OnUpdatePacketData( BOOL p_bTrUpdate) = 0;

// (2004.10.22, 배승원) AddIn DLL에게 Mouse Event를 전달한다.
//		Return Value가 FALSE인 경우에는 이후 처리 Routine을 진행하지 않는다.
public:
	// [04/10/11] Left Mouse Button Double Click Event를 처리하는 Interface를 제공한다.
	virtual BOOL	OnLButtonDblClk(	UINT nFlags, CPoint &point) = 0;
	// [04/10/22] Mouse Moving Event를 처리하는 Interface를 제공한다.
	virtual BOOL	OnMouseMove(		UINT nFlags, CPoint &point) = 0;
	// [04/10/25] Left Mouse Button Down Event를 처리하는 Interface를 제공한다.
	virtual BOOL	OnLButtonDown(		UINT nFlags, CPoint &point) = 0;
	// [04/10/25] Left Mouse Button Down Event를 처리하는 Interface를 제공한다.
	virtual BOOL	OnLButtonUp(		UINT nFlags, CPoint &point) = 0;
	// [04/10/29] Mouse Capture Release Event를 AddIn DLL에게 전달하도록 한다.
	//		주의! OnCaptureChanged()는 SetCapture()/RelaseCapture()에 의한 경우 외에도,
	//			Focus 나 Activate, ToolTip, TrackMenu등에 의해서도 수시로 (SetCapture없이)
	//			또한 자기 자신을 다시 SetCapture()하는 경우에도 호출됨을 유의한다.
	virtual void	OnCaptureChanged(	CWnd *pWnd) = 0;

// (2004.10.29, 배승원) AddIn DLL에게 그밖의 Windows Event를 전달한다.
public:
	// [04/10/29] Timer Event를 처리하는 Interface를 제공한다.
	virtual void	OnTimer( UINT p_uTimerID) = 0;
	// [04/11/09] KeyBoard Down Event를 처리하는 Interface를 제공한다.
	//		Return Value가 FALSE인 경우에는 이후 처리 Routine을 진행하지 않는다.
	virtual BOOL	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	// [04/11/09] KeyBoard Up Event를 처리하는 Interface를 제공한다.
	//		Return Value가 FALSE인 경우에는 이후 처리 Routine을 진행하지 않는다.
	virtual BOOL	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags) = 0;

// (2005/2/4 - Seung-Won, Bae) Real 관련 Event를 전달한다.
public:
	// [04/10/14] Real의 수신을 전달한다.
	//				속도 관계로 DRDS의 Data를 그대로 Pass한다.
	//				또한 FALSE를 Return할 경우 다음 Module에게 (PacketData에게도) 더 이상 Real을 전달하지 않는다.
	virtual BOOL	OnDrdsData( WPARAM p_wParam, LPARAM p_lParam) = 0;
	// [04/10/15] Real Packet의 수신이 끝났음을 AddIn DLL에게 알려 처리토록 한다.
	virtual void	OnDrdsPacketEnd( WPARAM p_wParam, LPARAM p_lParam) = 0;

//////////////////////////////////////////////////////////////////////
// 050116 Version, 전용 Interface
//		AddIn Module				Site			Manager
//			ChartCustomAddIn			GZone			배승원
//////////////////////////////////////////////////////////////////////

// Temp Interface I	: TimeMark Interface ~ 현 버전에서만 제공하도록 하는 Interface이다.
public:
	// [04/10/11] TimeMark를 Clear시키는 Interface를 제공한다.
	virtual	void	OnClearTimeMark( void) = 0;
	// [04/10/11] TimeMark를 설정하는 Interface를 제공한다.
	virtual	void	OnSetTimeMark( const char *p_szMarkTime, BOOL p_bWithScroll) = 0;
	// [04/10/11] 시간공유의 수신을 허용하는 Flag을 두어 제한할 수 있도록 한다.
	//				발신은 제한하지 않는다.
	virtual void	OnEnableReceivingTimeShare(BOOL p_bEnable) = 0;

// Temp Interface II	: BoundMark Interface ~ 현 버전에서만 제공하도록 하는 Interface이다.
public:
	// [04/10/13] 상한/하한한 표시를 활성화시키는 Interface를 제공한다.
	virtual void	OnEnableBoundMark( BOOL p_bEnable) = 0;

// Temp Interface III	: 사장되는 Option 기능의 Interface를 제공한다.
public:
	// [04/10/18] Image로 저장하는 Interface를 제공한다.
	virtual BOOL	OnSaveToImage( void) = 0;
};

#endif // !defined(AFX_ICHARTADDIN050116_H__1628D869_4373_4A7A_85B3_04D9026A7CE5__INCLUDED_)
