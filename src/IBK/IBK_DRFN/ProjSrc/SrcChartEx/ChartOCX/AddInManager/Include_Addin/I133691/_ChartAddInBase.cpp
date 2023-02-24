// ChartAddInBase.cpp: implementation of the CChartAddInBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_ChartAddInBase.h"

#include "../_IAddInDllBase.h"		// for IAddInDllBase
#include "_IAddInToolMgr.h"			// for IAddInToolMgr
#include "_IChartManager.h"			// for IChartManager
#include "_IPacketManager.h"		// for IPacketManager
#include "_IPacketListManager.h"	// for IPacketListManager
#include "_IGraphInfoManager.h"		// for IGraphInfoManager
#include "_IChartOCX.h"				// for IChartOCX

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChartAddInBase::CChartAddInBase( IChartOCX *p_pIChartOCX, IAddInDllBase *p_pIAddInDllBase)
{
	// (2006/2/10 - Seung-Won, Bae) Manage State for CWnd::FromHandle()
	AFX_MANAGE_STATE( AfxGetStaticModuleState());

	// (2006/2/12 - Seung-Won, Bae) Manage Over Exclusive Flag for Registering AddIn Event Map
	m_bOverExclusive = FALSE;

	// (2004.10.15, ��¿�) OCX Interface�� NULL�� ��츦 ����Ͽ�, Member�� �̸� NULL �ʱ�ȭ�� ó���Ѵ�.
	m_pIPacketListManager		= NULL;
	m_pIDefaultPacketManager	= NULL;
	m_pIChartManager			= NULL;
	m_pIGraphInfoManager		= NULL;
	m_pChartCWnd				= NULL;
	m_pIAddInToolMgr			= NULL;
	// (2006/1/17 - Seung-Won, Bae) Manage IAddInDll for AddIn Tool Exclusive
	m_pIAddInDllBase		= p_pIAddInDllBase;

	// (2004.10.08, ��¿�) Chart OCX Interface�� �����Ͽ�, ���� Ÿ Object�� ��ȸ�� �� �ֵ��� �Ѵ�.
	m_pIChartOCX = p_pIChartOCX;
	if( !m_pIChartOCX)
	{
		AfxMessageBox( "CChartAddInBase" _AIVERS " Null Wrapping Error!");
		return;
	}
	m_pIChartOCX->AddRef();

	// (2004.10.11, ��¿�) OCX�κ��� �ֿ� Manager�� Interface�� ���Ͽ� �����Ѵ�.
	m_pIDefaultPacketManager	= m_pIChartOCX->GetIDefaultPacketManager();
	m_pIPacketListManager		= m_pIChartOCX->GetIPacketListManager();
	m_pIChartManager			= m_pIChartOCX->GetIChartManager();
	m_pIGraphInfoManager		= m_pIChartOCX->GetIGraphInfoManager();
	m_pIAddInToolMgr			= m_pIChartOCX->GetIAddInToolMgr();

	// (2004.10.25, ��¿�) Chart OCX Control Window Pointer�� �����Ͽ� Windows Interface�� �̿��� �� �ֵ��� �Ѵ�.
	m_pChartCWnd = CWnd::FromHandle( m_pIChartOCX->GetOcxHwnd());

	// (2007/3/4 - Seung-Won, Bae) Notify OCX Destroying to Addin for Reset OCX's Interface
	m_bOcxDestroyed = FALSE;

	// (2008/1/22 - Seung-Won, Bae) for Multi-Language
	m_hOcxWnd = p_pIChartOCX->GetOcxHwnd();

	// (2009/9/14 - Seung-Won, Bae) for World-On
	m_eChartMode = p_pIChartOCX->GetChartMode();
}

CChartAddInBase::~CChartAddInBase()
{
	// (2004.10.08, ��¿�) Chart OCX Interface�� �����Ͽ�, ���� Ÿ Object�� ��ȸ�� �� �ֵ��� �Ѵ�.
	if( m_pIChartOCX)
	{
		m_pIChartOCX->Release();
		m_pIChartOCX = NULL;
	}

	// (2004.10.11, ��¿�) OCX�κ��� �ֿ� Manager�� Interface�� ���Ͽ� �����Ѵ�.
	if( m_pIPacketListManager)
	{
		m_pIPacketListManager->Release();
		m_pIPacketListManager = NULL;
	}
	if( m_pIDefaultPacketManager)
	{
		m_pIDefaultPacketManager->Release();
		m_pIDefaultPacketManager = NULL;
	}
	if( m_pIChartManager)
	{
		m_pIChartManager->Release();
		m_pIChartManager = NULL;
	}
	if( m_pIGraphInfoManager)
	{
		m_pIGraphInfoManager->Release();
		m_pIGraphInfoManager = NULL;
	}
	if( m_pIAddInToolMgr)
	{
		m_pIAddInToolMgr->Release();
		m_pIAddInToolMgr = NULL;
	}
}

// (2004.10.13, ��¿�) �⺻ Manager�� ��ϵǾ� �ִ��� Ȯ���ϴ� Interface�� �����Ѵ�.
BOOL CChartAddInBase::HasFullManager( void)
{
	return m_pIChartOCX && m_pIPacketListManager && m_pIDefaultPacketManager && m_pIChartManager && m_pIGraphInfoManager && m_pIAddInToolMgr;
}

// (2006/2/12 - Seung-Won, Bae) Register AddIn Event Map
int CChartAddInBase::RegisterEventMap( const BOOL p_bOverExclusive)
{
	m_bOverExclusive = p_bOverExclusive;

	const EAddInEventType *pRegisteredEventMap = GetRegisteredEventMap();

	int nRegisteredCount = 0;
	for( int i = 0; pRegisteredEventMap[ i] != EAE_END; i++)
		if( m_pIAddInToolMgr->RegisterEventMap( pRegisteredEventMap[ i], m_pIAddInDllBase, m_bOverExclusive)) nRegisteredCount++;

	return nRegisteredCount;
}

// (2006/2/12 - Seung-Won, Bae) Unregister AddIn Event Map
int CChartAddInBase::UnregisterEventMap( void)
{
	if( !m_pIAddInToolMgr) return 0;

	const EAddInEventType *pRegisteredEventMap = GetRegisteredEventMap();

	int nUnregisteredCount = 0;
	for( int i = 0; pRegisteredEventMap[ i] != EAE_END; i++)
		if( m_pIAddInToolMgr->UnregisterEventMap( pRegisteredEventMap[ i], m_pIAddInDllBase, m_bOverExclusive)) nUnregisteredCount++;

	return nUnregisteredCount;
}
