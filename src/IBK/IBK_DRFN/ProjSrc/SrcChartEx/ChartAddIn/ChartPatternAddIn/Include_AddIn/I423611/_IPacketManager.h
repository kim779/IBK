// IPacketManager.h: interface for the IPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPACKETMANAGER_H__BAD6BB66_01E4_46F1_8938_3A15A0B0048A__INCLUDED_)
#define AFX_IPACKETMANAGER_H__BAD6BB66_01E4_46F1_8938_3A15A0B0048A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>	// for CTypedPtrList
#include "_AddInVer.h"	// for AddIn Version Define

interface IPacket;
interface IPacketManager : public IUnknown  
{
protected:
	virtual ~IPacketManager()	{}

// [04/10/11] Packet Object�� Interface�� ���ϴ� Interface�� �����Ѵ�.
public:
	// [04/10/11] Packet Name���� Packet Object�� ���ϴ� Interface�� �����Ѵ�.
	virtual IPacket *	GetPacket( const char *p_szPacketName) = 0;
	// (2005/9/2 - Seung-Won, Bae) Get Packet Interface List for Packet Names
	virtual BOOL		GetPacketList( const char *p_szPacketNames, CTypedPtrList< CPtrList, IPacket *> *p_plIPackets) = 0;
	// [04/11/30] Packet Object�� Memory Address���� Packet Object�� ���ϴ� Interface�� �����Ѵ�.
	virtual IPacket *	GetPacketInterface( unsigned long p_ulPacketAddress) = 0;
	// (2006/1/9 - Seung-Won, Bae) Get Packet Interface List from CPacket List
	//					 ~ CObject * <= const CList<CPacket*, CPacket*> *
	virtual BOOL		GetIPacketListFromCPacketList( CObject *p_plCPacket, CList <IPacket *, IPacket *> *p_lIPacketList) = 0;
	// RQ�� Packet���� : �������� - ojtaso (20070112)
	virtual IPacket *	GetPacket(LPCTSTR lpszRQ, const char *p_szPacketName) = 0;
//	virtual BOOL		GetIPacketListFromCPacketList(LPCTSTR lpszRQ, CObject *p_plCPacket, IPacketList *p_lIPacketList) = 0;
	// PacketListManager Setting : �������� - ojtaso (20070307)
	virtual void		SetPacketListManager(LPVOID lpPacketListManager) = 0;
// [04/10/13] ���� Message�� �˻��ϴ� Interface�� �����Ѵ�. (�ֱٿ� ���ŵ� TR�� ���ѵȴ�.)
public:
	virtual BOOL						GetHelpMessageItem( const char *p_szMsgKey, CString &p_szMessage) = 0;
	// [05/09/29] Get Help Message List
	virtual const CMapStringToString *	GetHelpMessageMap( void) = 0;
};

#endif // !defined(AFX_IPACKETMANAGER_H__BAD6BB66_01E4_46F1_8938_3A15A0B0048A__INCLUDED_)