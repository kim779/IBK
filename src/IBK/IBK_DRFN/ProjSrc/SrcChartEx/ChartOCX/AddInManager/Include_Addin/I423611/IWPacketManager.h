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

class CPacketListManager;			// PacketListManager : �������� - ojtaso (20070110)
// (2004.10.11, ��¿�) Packet Data List�� Interface Wrapper Class�� �����Ѵ�.
class CIWPacketManager : public CIWUnknown, public IPacketManager  
{
// (2004.10.07, ��¿�) Interface Wrapper�� �⺻ Interface (IUnknown��)�� �����Ѵ�.
protected:
	_IWRAPPER_IUNKNOWN_MANAGER( IPacketManager, CIWPacketManager, CPacketList, m_pPacketList)

// [04/10/11] Packet Object�� Interface�� ���ϴ� Interface�� �����Ѵ�.
public:
	// [04/10/11] Packet Name���� Packet Object�� ���ϴ� Interface�� �����Ѵ�.
	virtual IPacket *	GetPacket( const char *p_szPacketName);
	// (2005/9/2 - Seung-Won, Bae) Get Packet Interface List for Packet Names
	virtual BOOL		GetPacketList( const char *p_szPacketNames, CTypedPtrList< CPtrList, IPacket *> *p_plIPackets);
	// [04/11/30] Packet Object�� Memory Address���� Packet Object�� ���ϴ� Interface�� �����Ѵ�.
	virtual IPacket *	GetPacketInterface( unsigned long p_ulPacketAddress);
	// (2006/1/9 - Seung-Won, Bae) Get Packet Interface List from CPacket List
	//					 ~ CObject * <= const CList<CPacket*, CPacket*> *
	virtual BOOL		GetIPacketListFromCPacketList( CObject *p_plCPacket, CList <IPacket *, IPacket *> *p_lIPacketList);

	// RQ�� Packet���� : �������� - ojtaso (20070112)
	virtual IPacket *	GetPacket(LPCTSTR lpszRQ, const char *p_szPacketName);
//	virtual BOOL		GetIPacketListFromCPacketList(LPCTSTR lpszRQ, CObject *p_plCPacket, IPacketList *p_lIPacketList);
	// PacketListManager Setting : �������� - ojtaso (20070307)
	virtual void		SetPacketListManager(LPVOID lpPacketListManager);
// [04/10/13] ���� Message�� �˻��ϴ� Interface�� �����Ѵ�. (�ֱٿ� ���ŵ� TR�� ���ѵȴ�.)
public:
	virtual BOOL		GetHelpMessageItem( const char *p_szMsgKey, CString &p_szMessage);
	// [05/09/29] Get Help Message List
	virtual const CMapStringToString *	GetHelpMessageMap( void);
	// PacketListManager : �������� - ojtaso (20070110)
	CPacketListManager*		m_pPacketListManager;
};

#endif // !defined(AFX_IWPACKETMANAGER_H__5B20ECF2_9545_47B2_8A7A_0763FEF08F08__INCLUDED_)