// IWPacketListManager.cpp: implementation of the CIWPacketListManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IWPacketListManager.h"

#include "../../../Include_Chart/DLL_Load/PacketList.h"		// for CPacketList
#include "../../../Include_Chart/DLL_Load/PacketBase.h"		// for CPacket
#include "IWPacket.h"										// for CIWPacket
#include "IWStringList.h"									// for CIWStringList
#include "IWPacketManager.h"								// for CIWPacketManager


//////////////////////////////////////////////////////////////////////
// _IWRAPPER_IUNKNOWN_MANAGER_IMP
//////////////////////////////////////////////////////////////////////
_IWRAPPER_IUNKNOWN_MANAGER_IMP( CIWPacketListManager)


// (2008/10/14 - Seung-Won, Bae) Retrieve PacketManager
IPacketManager *CIWPacketListManager::GetPacketManager( const char *p_szRQ)
{
	if( !m_pPacketListManager) return NULL;
	
	CPacketList* pPacketList = m_pPacketListManager->GetPacketList( p_szRQ);
	if( !pPacketList) return NULL;

	return CIWPacketManager::CreateObject( pPacketList);
}


// RQ�� Packet���� : �������� - ojtaso (20070112)
IPacket *CIWPacketListManager::GetPacket( LPCTSTR lpszRQ, const char *p_szPacketName)
{
	if( !m_pPacketListManager) return NULL;
	
	CPacketList* pPacketList = m_pPacketListManager->GetPacketList( lpszRQ);
	if( !pPacketList) return NULL;

	CPacket *pPacket = pPacketList->GetBaseData( p_szPacketName);
	if( !pPacket) return NULL;

	return CIWPacket::CreateObject( pPacket);
}

IStringList *CIWPacketListManager::GetRQByItemCode( LPCTSTR lpszItemCode)
{
	if( !m_pPacketListManager) return NULL;

	CIWStringList::CStringTList *pStringTList = new CIWStringList::CStringTList;
	m_pPacketListManager->GetRQByItemCode( lpszItemCode, *pStringTList);

	if( pStringTList->IsEmpty())
	{
		delete pStringTList;
		return NULL;
	}

	return CIWStringList::CreateObject( pStringTList, TRUE);
}

// 2008.08.07 ������ ���� Ratio chart ��� RQ�� �̸��� ���ؿ´�		<<
void CIWPacketListManager::GetAllRQ(CStringArray& arRQ)
{
	if( !m_pPacketListManager) return;

	CList < CString, CString> slStringTList;
	m_pPacketListManager->GetAllRQ( slStringTList);
	POSITION psn = slStringTList.GetHeadPosition();
	while( psn) arRQ.Add( slStringTList.GetNext( psn));
}

// 2008.08.07 ������ ���� Ratio chart ��� RQ�� �̸��� ���ؿ´�		<<
void CIWPacketListManager::GetItemCode(LPCTSTR lpszRQ, LPCTSTR& lpszItemCode, LPCTSTR& lpszItemName)
{
	if(m_pPacketListManager)
		m_pPacketListManager->GetItemCode(lpszRQ, lpszItemCode, lpszItemName);
}

// ���簡 ����� - ojtaso (20080602)
void CIWPacketListManager::OffsetPacketData(LPCTSTR lpszRQ, double dData, CString strPacketName/* = _T("")*/)
{
	if( !m_pPacketListManager) return;

	if(dData == 0.)
		return;

	m_pPacketListManager->OffsetPacketData(lpszRQ, dData, strPacketName);
}