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
public:
	// [04/10/11] Packet Name으로 Packet Object를 구하는 Interface를 제공한다.
	virtual IPacket *	GetPacket( const char *p_szPacketName);
	// (2005/9/2 - Seung-Won, Bae) Get Packet Interface List for Packet Names
	virtual BOOL		GetPacketList( const char *p_szPacketNames, CTypedPtrList< CPtrList, IPacket *> *p_plIPackets);
	// [04/11/30] Packet Object의 Memory Address으로 Packet Object를 구하는 Interface를 제공한다.
	virtual IPacket *	GetPacketInterface( unsigned long p_ulPacketAddress);
	// (2006/1/9 - Seung-Won, Bae) Get Packet Interface List from CPacket List
	//					 ~ CObject * <= const CList<CPacket*, CPacket*> *
	virtual BOOL		GetIPacketListFromCPacketList( CObject *p_plCPacket, CList <IPacket *, IPacket *> *p_lIPacketList);

	// RQ별 Packet관리 : 복수종목 - ojtaso (20070112)
	virtual IPacket *	GetPacket(LPCTSTR lpszRQ, const char *p_szPacketName);
//	virtual BOOL		GetIPacketListFromCPacketList(LPCTSTR lpszRQ, CObject *p_plCPacket, IPacketList *p_lIPacketList);
	// PacketListManager Setting : 복수종목 - ojtaso (20070307)
	virtual void		SetPacketListManager(LPVOID lpPacketListManager);
// [04/10/13] 보조 Message를 검색하는 Interface를 제공한다. (최근에 수신된 TR에 제한된다.)
public:
	virtual BOOL		GetHelpMessageItem( const char *p_szMsgKey, CString &p_szMessage);
	// [05/09/29] Get Help Message List
	virtual const CMapStringToString *	GetHelpMessageMap( void);
	// PacketListManager : 복수종목 - ojtaso (20070110)
	CPacketListManager*		m_pPacketListManager;
};

#endif // !defined(AFX_IWPACKETMANAGER_H__5B20ECF2_9545_47B2_8A7A_0763FEF08F08__INCLUDED_)
