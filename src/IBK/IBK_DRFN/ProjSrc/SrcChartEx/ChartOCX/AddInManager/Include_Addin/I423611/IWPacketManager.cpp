// IWPacketManager.cpp: implementation of the CIWPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IWPacketManager.h"

#include "Packetbase.h"		// for CPacket
#include "IWPacket.h"		// for CIWPacket
// PacketListManager : 복수종목 - ojtaso (20070110)
#include "PacketListManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// _IWRAPPER_IUNKNOWN_MANAGER_IMP
//////////////////////////////////////////////////////////////////////
_IWRAPPER_IUNKNOWN_MANAGER_IMP( CIWPacketManager)

//////////////////////////////////////////////////////////////////////
// [04/10/11] Packet Object의 Interface를 구하는 Interface를 제공한다.
//////////////////////////////////////////////////////////////////////

// [04/10/11] Packet Name으로 Packet Object를 구하는 Interface를 제공한다.
IPacket *CIWPacketManager::GetPacket( const char *p_szPacketName)
{
	if( !m_pPacketList) return NULL;
	CPacket *pPacket = m_pPacketList->GetBaseData( p_szPacketName);
	if( !pPacket) return NULL;
	return CIWPacket::CreateObject( pPacket);
}

// RQ별 Packet관리 : 복수종목 - ojtaso (20070112)
IPacket *CIWPacketManager::GetPacket(LPCTSTR lpszRQ, const char *p_szPacketName)
{
	if(!m_pPacketListManager)
		return GetPacket(p_szPacketName);

	CPacketList* pPacketList = m_pPacketListManager->GetPacketList(lpszRQ);
	if( !pPacketList) return NULL;

	CPacket *pPacket = pPacketList->GetBaseData( p_szPacketName);
	if( !pPacket) return NULL;
	return CIWPacket::CreateObject(lpszRQ, pPacket);
}

// (2005/9/2 - Seung-Won, Bae) Get Packet Interface List for Packet Names
BOOL CIWPacketManager::GetPacketList( const char *p_szPacketNames, CTypedPtrList< CPtrList, IPacket *> *p_plIPackets)
{
	if( !m_pPacketList) return FALSE;

	CList<CPacket*, CPacket*> lPackets;
	if( !m_pPacketList->GetPacketList( p_szPacketNames, ";", lPackets)) return FALSE;

	CPacket *pPacket = NULL;
	IPacket *pIPacket = NULL;
	POSITION posPacket = lPackets.GetHeadPosition();
	while( posPacket)
	{
		pPacket = lPackets.GetNext( posPacket);
		p_plIPackets->AddTail( CIWPacket::CreateObject( pPacket));
	}

	return TRUE;
}

// [04/11/30] Packet Object의 Memory Address으로 Packet Object를 구하는 Interface를 제공한다.
IPacket *CIWPacketManager::GetPacketInterface( unsigned long p_ulPacketAddress)
{
	if( !m_pPacketList) return NULL;
	if( !p_ulPacketAddress) return NULL;
	return CIWPacket::CreateObject( ( CPacket *)p_ulPacketAddress);
}

// (2006/1/9 - Seung-Won, Bae) Get Packet Interface List from CPacket List
//					 ~ CObject * <= const CList<CPacket*, CPacket*> *
BOOL CIWPacketManager::GetIPacketListFromCPacketList( CObject *p_plCPacket, CList <IPacket *, IPacket *> *p_lIPacketList)
{
	const CList<CPacket*, CPacket*> *plCPacketList = ( const CList<CPacket*, CPacket*> *)p_plCPacket;
	if( !plCPacketList || !p_lIPacketList) return FALSE;
	POSITION pos = plCPacketList->GetHeadPosition();
	if( !pos) return FALSE;
	CPacket *pPacket = NULL;
	IPacket *pIPacket = NULL;
	while( pos)
	{
		pPacket = plCPacketList->GetNext(pos);
		p_lIPacketList->AddTail( CIWPacket::CreateObject( pPacket));
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// [04/10/13] 보조 Message를 검색하는 Interface를 제공한다. (최근에 수신된 TR에 제한된다.)
//////////////////////////////////////////////////////////////////////
BOOL CIWPacketManager::GetHelpMessageItem( const char *p_szMsgKey, CString &p_szMessage)
{
	if( !m_pPacketList) return FALSE;
	return m_pPacketList->GetHelpMessageItem( p_szMsgKey, p_szMessage);
}
// [05/09/29] Get Help Message List
const CMapStringToString *CIWPacketManager::GetHelpMessageMap( void)
{
	if( !m_pPacketList) return NULL;
	return m_pPacketList->GetHelpMessageMap();
}

// PacketListManager Setting : 복수종목 - ojtaso (20070307)
void CIWPacketManager::SetPacketListManager(LPVOID lpPacketListManager)
{
	m_pPacketListManager = (CPacketListManager*)lpPacketListManager;
}

