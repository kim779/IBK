// IRealReceiver.h: interface for the IRealReceiver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IREALRECEIVER_H__4E6768EB_BD1F_4493_87B9_2DCB96D51980__INCLUDED_)
#define AFX_IREALRECEIVER_H__4E6768EB_BD1F_4493_87B9_2DCB96D51980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
// Author		: Seung-Won, Bae	Date :2006/7/25
// Comments		: Real Receiving Interface of Real Receiver AddIn
// Using way	: 
// See			: 
//-----------------------------------------------------------------------------

//********************************************************************
// Caution! Do not update or delete or add in old interface
//	This header was released already.
//********************************************************************

interface IRealReceiver : public IUnknown
{
protected:
	virtual ~IRealReceiver()	{}

//////////////////////////////////////////////////////////////////////
// (2006/8/1 - Seung-Won, Bae) for DRDS Real
//////////////////////////////////////////////////////////////////////
//********************************************************************
// Caution! Do not update or delete or add in old interface
//	This header was released already.
//********************************************************************
// (2006/7/25 - Seung-Won, Bae) Support Real Requesting
public:
	// 1. XFM과 Script에서 지정되는 Real 설정 속성 String Data로 구성하는 Interface를 제공한다.
	virtual BOOL	ResetRealSettingInfo( const char *p_szRealSettingInfo)	{	return FALSE;	}
	// 2. 1개의 Real 설정 Data를 추가하는 Interface를 제공한다.
	//		특히, p_pstrShareName과 p_pstrSharedData가 주어지는 경우에는 별도의 Method(AddRealItem)를 통하여 지정되는 방식으로
	//			p_szRealSettingItem에는 Local Share Name이 없이 바로 Real Key Code가 주어진다. 
	//		적절한 Local Share Name을 생성하여 적용하고, 참조할 수 있도록 반환한다.
	//		(ResetRealSettingInfo()와 AddRealItem()가 공유할 수 있도록 하여 CString의 Pointer로 처리한다.)
	// (2006/4/28 - Seung-Won, Bae) with Separator
	virtual BOOL	AddRealSettingInfo( const char *p_szRealSettingItem, CString *p_pstrShareName = NULL, CString *p_pstrSharedData = NULL, char p_cSeparator = '.')	{	return FALSE;	}
	// 2. 별도의 Method(RemoveRealItem)를 통하여 지정되는 1개의 Real Setting Info를 삭제하는 Interface를 제공한다.
	//		특히, Local Share Name이 없이 바로 Real Key Code가 주어져,
	//			적절한 Local Share Name을 생성하여 적용하고, 참조할 수 있도록 반환해야 한다.
	//		참고로 더이상 해당 공유 Key로 설정된 Real이 없는 경우에만 공유명이 반환된다.
	//		(AddRealSettingInfo()와 Interface를 통일하도록 하여 CString의 Pointer로 처리한다.)
	// (2006/4/28 - Seung-Won, Bae) with Separator
	virtual BOOL	RemoveRealSettingInfo( const char *p_szRealSettingItem, CString *p_pstrShareName = NULL, char p_cSeparator = '.')	{	return FALSE;	}
public:
	virtual	BOOL	SetRealAdvise( BOOL p_bAdvise)							{	return FALSE;	}
	virtual BOOL	GetRealAdvisedInfo( CString &p_strAdvisedInfo)			{	return FALSE;	}

// (2006/7/25 - Seung-Won, Bae) Support DRDS Interface
public:
	virtual BOOL	SetDrdsData( UINT wParam, LPARAM lParam)				{	return FALSE;	}
	virtual BOOL	SetDrdsPacketEnd( UINT wParam, LPARAM lParam)			{	return FALSE;	}

//////////////////////////////////////////////////////////////////////
// (2006/8/1 - Seung-Won, Bae) for Direct Real
//////////////////////////////////////////////////////////////////////
//********************************************************************
// Caution! Do not update or delete or add in old interface
//	This header was released already.
//********************************************************************
public:
	virtual BOOL	SetRealData( const char *p_szPacketName, double p_dData)	{	return FALSE;	}
	virtual BOOL	SetRealPacketEnd( void)										{	return FALSE;	}
};

#endif // !defined(AFX_IREALRECEIVER_H__4E6768EB_BD1F_4493_87B9_2DCB96D51980__INCLUDED_)
