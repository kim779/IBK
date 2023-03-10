// IWPacketManager.h: interface for the CIWPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IWPACKETMANAGER_H__5B20ECF2_9545_47B2_8A7A_0763FEF08F08__INCLUDED_)
#define AFX_IWPACKETMANAGER_H__5B20ECF2_9545_47B2_8A7A_0763FEF08F08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../Include_Chart/Dll_Load/PacketList.h"			// for CPacketList
#include "../_IWUnknown.h"
#include "_IPacketManager.h"
#include "_IChartOCX.h"											// for IChartOCX

class CPacketListManager;			// PacketListManager : 복수종목 - ojtaso (20070110)
// (2004.10.11, 배승원) Packet Data List의 Interface Wrapper Class를 정의한다.
class CIWPacketManager : public CIWUnknown, public IPacketManager  
{
// (2004.10.07, 배승원) Interface Wrapper의 기본 Interface (IUnknown용)를 제공한다.
protected:
	_IWRAPPER_IUNKNOWN_MANAGER( IPacketManager, CIWPacketManager, CPacketList, m_pPacketList)

// [04/10/11] Packet Object의 Interface를 구하는 Interface를 제공한다.
protected:
	// [04/10/11] Packet Name으로 Packet Object를 구하는 Interface를 제공한다.
	virtual IPacket *	GetPacket( const char *p_szPacketName);
	// (2005/9/2 - Seung-Won, Bae) Get Packet Interface List for Packet Names
	virtual BOOL		GetPacketList( const char *p_szPacketNames, IPacketList *p_lIPacketList);

// [04/10/13] 보조 Message를 검색하는 Interface를 제공한다. (최근에 수신된 TR에 제한된다.)
protected:
	virtual BOOL				GetHelpMessageItem( const char *p_szMsgKey, ILPCSTR &p_pszMessage);
	// [05/09/29] Get Help Message List
	virtual IHelpMessageMap *	GetHelpMessageMap( void);

// (2006/6/22 - Seung-Won, Bae) Retrieve Packet Infos
protected:
	// (2006/6/22 - Seung-Won, Bae) Get RealUpdated Data Index
	virtual int			GetLastestRealIndex( void);
	// (2006/6/22 - Seung-Won, Bae) Get Maximum Data Count
	virtual long		GetMaximumDataCount( void);
	virtual long		GetMaximumDataCount( const char *p_szPacketNames, const char *p_szCompartString);
	// (2006/6/26 - Seung-Won, Bae) Get the BaseTime Info
	virtual CScaleBaseData::HORZSCALEDRAWERTYPE	GetBaseTimeDataType( void);
	virtual int									GetBaseTimeUnit( void);
	// (2006/7/26 - Seung-Won, Bae) Retrieve the flag of Real Usage
	virtual BOOL		IsInUseRealData( void);
	// (2006/8/15 - Seung-Won, Bae) Retrieve Main Item Type
	virtual ICOMMODITY_BOND_NAME	GetCommodityBondNameInBase( void);
	//>> Gap Revision - vntsorl(20090213)
	virtual ILPCSTR		GetTRPacketNames(const char *p_szCompart = ";");
	// (2008/11/3 - Seung-Won, Bae) Support User TimeScale Setting.
	virtual int			GetCalcDataTimeDifference( void);
	virtual int			GetBaseTimeDifference( void);
	// (2009/10/21 - Seung-Won, Bae) Comment. 실시간 Data의 Packet Type을 관리한다.
	virtual ILPCSTR		GetRealTimeType( void);
	// (2009/11/12 - Seung-Won, Bae) Get NMTR Info
	virtual BOOL		GetLastClockAndRealTime( __int64 &p_nLastClockTime, __int64 &p_nLastRealTime);
	// (2009/11/12 - Seung-Won, Bae) for NMTR Step Width
	virtual __int64		GetTimeIntervalWithSecond( void);
};

#endif // !defined(AFX_IWPACKETMANAGER_H__5B20ECF2_9545_47B2_8A7A_0763FEF08F08__INCLUDED_)
