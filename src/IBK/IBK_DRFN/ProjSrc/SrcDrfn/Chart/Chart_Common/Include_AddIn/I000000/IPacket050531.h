// IPacket050531.h: interface for the IPacket050531 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPACKET050531_H__33499AC4_ED71_4247_AB51_30A908195E29__INCLUDED_)
#define AFX_IPACKET050531_H__33499AC4_ED71_4247_AB51_30A908195E29__INCLUDED_

//////////////////////////////////////////////////////////////////////
// *. 주의!	050531 Version의 AddIn에서 이용되는 OCX측 Interface로 기능 추가만 가능합니다.
//		기능 삭제와 Type 변경은 허용하지 않습니다.
//		Interface 순서 변경 조차 허용되지 않습니다.
//		허용되지 않는 편집은 050531 Version의 모든 AddIn Module과 관련 Site OCX가
//			함께 수정되어 내려가는 것이 전제되어야 합니다.
// *. 050531 Version Info
//		AddIn Module				Site			Manager
//		ChartCustomAddIn			한화			배승원
//		ChartAssistIndexAddIn		한화			오근문
//////////////////////////////////////////////////////////////////////

// (2004.10.11, 배승원) Packet Data Object의 Interface를 정의한다.
//		AddIn DLL 참조 Interface로 Macro Interface를 정의한다.
#if IPacketVer < 050531
	#define	IPacket		IPacket050531
	#undef	IPacketVer
	#define	IPacketVer	050531
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>		// for CList

class IPacket050531 : public IUnknown  
{
protected:
	virtual ~IPacket050531()	{}

// [04/10/11] Packet의 정보를 조회하는 Interface를 제공한다.
public:
	// [04/10/11] Packet의 Type을 String으로 조회하는 Interface를 제공한다.
	virtual BOOL		GetPacketTypeString( CString &p_strPacketType) = 0;
	// [04/10/26] Packet의 Type을 Unit Value(Double)로 조회하는 Interface를 제공한다.
	virtual double		GetPacketTypeUnitValue( void) = 0;
	// [04/11/30] Packet Name을 구하는 Interface를 제공한다.
	virtual BOOL		GetPacketName( CString &p_strPacketName) = 0;

// [04/10/11] 주어지는 값의 Data Index, 또는 그 Data 값이 있어야할 위치 이전의 Index를 구한다. (Sort 전제)
//			TRUE	-> 범위 안인 경우
//			FALSE	-> 범위를 벗어나거나 같은 값이 없는 경우
public:
	virtual BOOL		GetCurOrPrevIndexFromData( const double dData, int& nCurOrPrevIndex, double& dCurOrPrevIndexData) = 0;

// (2004.10.15, 배승원) Data를 조회 및 설정하는 Interface를 제공한다.
public:
	// [04/10/15] Data의 수를 확인하는 Interface를 제공한다.
	virtual int							GetDataCount( void) = 0;
	// [04/10/11] 해당 Index의 Data를 조회하는 Interface를 제공한다. (Zero Base)
	virtual double						GetData( int p_nIndex) = 0;
	// [04/10/15] 해당 Index의 Data를 설정하는 Interface를 제공한다. (Zero Base)
	virtual BOOL						SetData( int p_nIndex, double p_dData) = 0;
	// [04/12/07] Double Data List를 조회하는 Interface를 제공한다.
	virtual CList< double, double> *	GetDataList( void) = 0;
	// (2005/9/2 - Seung-Won, Bae) Get String Data List
	virtual CList< CString, CString> *	GetStrDataList( void) = 0;
	
	// 종찬(05/07/26) Data를 추가하는 Interface를 제공한다.
	virtual void						AppendData(double dData) = 0;
	
	// 종찬(05/07/28) Data를 클리어한다. true일경우는 기본데이타도 Clear.(true는 ST.에서는 사용할 필요없을듯)
	virtual void						ClearData(const bool bBaseDataClear = false) = 0;
	// 종찬(05/08/29) 타입을 설정하는 Interface를 제공한다.
	virtual void						SetType(const CString& strType, const CString& strExpressionType) = 0;
	// 종찬(05/08/29) 타입값을 가져오는 Interface를 제공한다.
	virtual CString						GetType(const bool bIsFullType = true) = 0;
	// 종찬(05/09/01) 해당 Index의 데이타를 조회하는 Interface를 제공한다.
	virtual bool						GetData(const int nIndex, double& dData) = 0;

};

#endif // !defined(AFX_IPACKET050531_H__33499AC4_ED71_4247_AB51_30A908195E29__INCLUDED_)
