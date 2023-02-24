// ChartStockOpinionAddInImp.cpp: implementation of the CChartDragCandleAnalAddInImp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChartPeriodSummaryAddIn.h"
#include "ChartDragCandleAnalAddInImp.h"
#include "resource.h"

#include "./Include_AddIn/Include_AddIn.h"							// for Ixxxxxx.h
#include "./Include_Chart/MessageDefine.h"			// for UM_CURSOR_EXCHANGE
//#include "./Include_Chart/OutsideCommonInterface.h"		// for CMChartInterface
//#include "../../ChartOcx/Include_Chart/OutsideCommonInterface.h"
//#include "../../Contents/ChartDll/Chart_Common/OutsideCommonInterface.h"
#include "./Include_Chart/Dll_Load/IMetaTable.h"			// for g_iMetaTable
#include "../../ChartOCX/Include_Chart/OutsideCommonInterfaceFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChartDragCandleAnalAddInImp::CChartDragCandleAnalAddInImp( IChartOCX *p_pIChartOCX, IAddInDllBase *p_pIAddInDllBase)
	: CChartAddInBase( p_pIChartOCX, p_pIAddInDllBase)
{
	// save point for inflate when mouse drag & drop
	// 09.21.2001
	m_ptStartDragDrop = CPoint(-1, -1);
	m_ptCurrDragDrop = CPoint(-1, -1);

	m_ptStart = CPoint(-1, -1);
	m_ptEnd = CPoint(-1, -1);

	// (2006/2/6 - Seung-Won, Bae) Manage Mouse Action ID for Serial Action.
	m_dwMouseActionID = UINT_MAX;

	// ( 2006 / 11 / 27 - Sang-Woo, Cho ) ADDIN의 실행여부.
	m_bRun = TRUE;
	m_nStartIndex = -1;
	m_nEndIndex = -1;
}

CChartDragCandleAnalAddInImp::~CChartDragCandleAnalAddInImp()
{
}

// (2006/2/15 - Seung-Won, Bae) Multiple Item in DLL
CString CChartDragCandleAnalAddInImp::m_strAddInItemName = "DRAG_CANDLE_ANAL";

//////////////////////////////////////////////////////////////////////
// Define AddIn Event Map
//////////////////////////////////////////////////////////////////////
BEGIN_ADDIN_EVENT_MAP( CChartDragCandleAnalAddInImp)
	ONADDINEVENT( OnDrawAfterGraph)
	ONADDINEVENT( DrawCursor)
	ONADDINEVENT( OnMouseMove)
	ONADDINEVENT( OnLButtonDown)
	ONADDINEVENT( OnLButtonUp)
	ONADDINEVENT( OnPacketDataMultiItem)
	ONADDINEVENT( OnResetChart)
END_ADDIN_EVENT_MAP()

//////////////////////////////////////////////////////////////////////
// (2004.10.11, 배승원) 기본적인 Interface를 Default로 제공한다. (Derived Class에서 재정의하지 않아도 오류가 나지 않도록)
//////////////////////////////////////////////////////////////////////

// (2006/2/6 - Seung-Won, Bae) Draw Trace Rectangle
CRect CChartDragCandleAnalAddInImp::DrawDragRect(CDC * pdc, CPoint ptFirst, CPoint ptCurr, int nWeight)
{
	CRect rccurr;
	rccurr.SetRectEmpty();
	if( ptCurr == CPoint(-1, -1)) return rccurr;

	// 제대로 된 사각형 만들기
	CPoint ptStart, ptEnd;
	ptStart.x = ptFirst.x < ptCurr.x ? ptFirst.x : ptCurr.x;
	ptStart.y = ptFirst.y < ptCurr.y ? ptFirst.y : ptCurr.y;
	ptEnd.x = ptFirst.x > ptCurr.x ? ptFirst.x : ptCurr.x;
	ptEnd.y = ptFirst.y > ptCurr.y ? ptFirst.y : ptCurr.y;

	rccurr = CRect(ptStart, ptEnd);
	CRect rc = m_pIChartOCX->GetOcxRegion();
	rc = m_pIChartManager->GetGraphRegionSumInColumn(rc.CenterPoint());
	rccurr.top = rc.top;
	rccurr.bottom = rc.bottom;

	SIZE size;
	size.cx = nWeight; size.cy = nWeight;

	pdc->DrawDragRect(rccurr, size, NULL, size);
	
	return rccurr;
}

// (2007/1/7 - Seung-Won, Bae) Support AddIn Cursor Operation.
RECT CChartDragCandleAnalAddInImp::DrawCursor( HDC p_hDC)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	CDC *pDC = CDC::FromHandle( p_hDC);
	return DrawDragRect( pDC, m_ptStartDragDrop, m_ptCurrDragDrop, 4);
}

BOOL CChartDragCandleAnalAddInImp::OnMouseMove( HDC p_hDC, UINT nFlags, POINT &point, const DWORD p_dwMouseActionID, const HBITMAP p_hbmpMainOSB)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	// ( 2006 / 11 / 27 - Sang-Woo, Cho ) 
	if( !m_bRun ) return FALSE;

	CDC *pDC = CDC::FromHandle( p_hDC);
	if( !pDC) return FALSE;

	// (2006/2/6 - Seung-Won, Bae) Manage Mouse Action ID for Serial Action.
	if( !m_pIAddInToolMgr->IsLButtonExclusive( m_pIAddInDllBase))
	{
		if( p_dwMouseActionID != m_dwMouseActionID) return FALSE;
		if( !m_pIAddInToolMgr->GetLButtonExclusive( m_pIAddInDllBase)) return FALSE;
		m_ptCurrDragDrop = m_ptStartDragDrop;
	}

	if( m_ptStartDragDrop == point)	return TRUE;

	// Drag중
	m_ptCurrDragDrop = point;
	return TRUE;
}

BOOL CChartDragCandleAnalAddInImp::OnLButtonDown( HDC p_hDC, UINT nFlags, POINT &point, const DWORD p_dwMouseActionID)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	// ( 2006 / 11 / 27 - Sang-Woo, Cho ) 
	if( !m_bRun )
		return FALSE;

	// (2006/2/13 - Seung-Won, Bae) Check Empty Chart!
	//if( !m_pIChartOCX->IsUseToolScrollBar() || m_pIChartOCX->IsOnSpecialChart() || m_pIChartManager->IsEmpty()) return FALSE;
	if( m_pIChartOCX->IsOnSpecialChart() || m_pIChartManager->IsEmpty()) return FALSE;
	CRect rctRegion = m_pIChartManager->GetGraphRegionSumInColumn( point);
	if( rctRegion.IsRectEmpty()) return FALSE;

	// (2006/2/6 - Seung-Won, Bae) Manage Mouse Action ID for Serial Action.
	m_dwMouseActionID = p_dwMouseActionID;

	m_ptStartDragDrop = point;
	m_ptCurrDragDrop = CPoint(-1, -1);

	//return TRUE;
	return 0L;
}

BOOL CChartDragCandleAnalAddInImp::OnLButtonUp( HDC p_hDC, UINT nFlags, POINT &point, const DWORD p_dwMouseActionID)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	// ( 2006 / 11 / 27 - Sang-Woo, Cho ) 
	if( !m_bRun )
		return FALSE;

	CDC *pDC = CDC::FromHandle( p_hDC);
	if( !pDC) return FALSE;

	// (2006/2/6 - Seung-Won, Bae) Manage Mouse Action ID for Serial Action.
	if( !m_pIAddInToolMgr->ReleaseLButtonExclusive( m_pIAddInDllBase)) return FALSE;

	// save point & draw for inflate when mouse drag & drop
	// 09.21.2001	
	// MODIFY: 종찬(04/04/18) DoubleClick-Drag시 ZoomIn기능을 제거.
	// (2006/3/4 - Seung-Won, Bae) Make Real Effect Gap 5 Pixcel.
	//if( 0 <= abs(m_ptStartDragDrop.x - point.x))
	{

		//nami 8.30
		m_pChartCWnd->SendMessage( UM_CURSOR_EXCHANGE, ( WPARAM)CCursorShape::OBJECT_NONE, NULL);

		//m_ptStart.x = m_ptStartDragDrop.x < m_ptCurrDragDrop.x ? m_ptStartDragDrop.x : m_ptCurrDragDrop.x;
		//m_ptEnd.x = m_ptStartDragDrop.x > m_ptCurrDragDrop.x ? m_ptStartDragDrop.x : m_ptCurrDragDrop.x;
		m_ptStart.x = m_ptStartDragDrop.x;
		m_ptEnd.x = m_ptCurrDragDrop.x;

		// 차트의 기본정보 --------------------------------------------------------------------->>
		int nStartIndex = 0, nEndIndex = 0;
		int		nR, nC;									// 가격차트가 포함된 Block의 Index
		CRect	rctBlockRegion, rctGraphRegion;			// Frame 영역, Graph 영역
		GetChartBasicData( nStartIndex, nEndIndex, nR, nC, rctBlockRegion, rctGraphRegion);
		m_nStartIndex = GetIndexFromPoint(m_ptStart.x, nStartIndex, nEndIndex, rctGraphRegion);
		m_nEndIndex = GetIndexFromPoint(m_ptEnd.x, nStartIndex, nEndIndex, rctGraphRegion);


		if(m_nStartIndex <= m_nEndIndex)
		{
			if(m_nEndIndex - m_nStartIndex >= 5)
				m_nEndIndex = m_nStartIndex + 4;
		}
		else
		{	
			if(m_nStartIndex - m_nEndIndex >= 5)
				m_nEndIndex = m_nStartIndex - 4;

			int nTemp = m_nStartIndex;
			m_nStartIndex = m_nEndIndex;
			m_nEndIndex = nTemp;
		}

//		IPacket *pIPacket = m_pIPacketManager->GetPacket( "자료일자");
		IPacket *pIPacket = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_DATE_TIME));
		if(pIPacket)
		{
			if(m_nEndIndex >= pIPacket->GetDataCount())
				m_nEndIndex = pIPacket->GetDataCount() -1;
		}

		m_pIChartOCX->InvalidateControl();

		//20100408 SJ_KIM 구간검색 관련 !!Start!!
		COutsideCommonInterface *pOutsideI = m_pIChartOCX->GetMChartInterface();
		
		if(pOutsideI)
		{
			COutsideCommonInterfaceFunction outsideIF;
			ILPCSTR szDataPath = m_pIChartOCX->GetDefaultPathString();
			outsideIF.SetOutsideCommonInterface(pOutsideI, CString( szDataPath));
			
			if(AddData(m_nStartIndex, m_nEndIndex))
				outsideIF.MChart_SetDataWindowData(&m_listDataWindow);
			
		}
		//20100408 SJ_KIM 구간검색 관련 !!End!!
	}

	m_ptStartDragDrop = CPoint(-1, -1);
	m_ptCurrDragDrop = CPoint(-1, -1);
	//return TRUE;
	return 0L;
}
void CChartDragCandleAnalAddInImp::OnDrawAfterGraph(HDC p_hDC)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	CDC *pDC = CDC::FromHandle( p_hDC);

//	if(m_nStartIndex == m_nEndIndex)
//		return;
	if(m_nStartIndex == -1 || m_nEndIndex == -1)
		return;

	// 차트의 기본정보 --------------------------------------------------------------------->>
	int nStartIndex = 0, nEndIndex = 0;
	int		nR, nC;									// 가격차트가 포함된 Block의 Index
	CRect	rctBlockRegion, rctGraphRegion;			// Frame 영역, Graph 영역
	GetChartBasicData( nStartIndex, nEndIndex, nR, nC, rctBlockRegion, rctGraphRegion);

	int		nDataOnePage = nEndIndex - nStartIndex + 1;								// 현 Data View의 Data 갯수
	double	dCandleWidth = double( rctGraphRegion.Width()) / double( nDataOnePage);	// 봉의 폭을 구한다

	m_ptStart.x = long( GetXPositoin(m_nStartIndex-nStartIndex, dCandleWidth, rctGraphRegion)-dCandleWidth/2 + 1);
	m_ptEnd.x = long( GetXPositoin(m_nEndIndex-nStartIndex, dCandleWidth, rctGraphRegion)+dCandleWidth/2);

	if(m_ptStart.x<m_ptEnd.x)
	{
		m_ptEnd.x +=1;
		CRect rc = m_pIChartOCX->GetOcxRegion();
		rc = m_pIChartManager->GetGraphRegionSumInColumn(rc.CenterPoint());
		m_ptStart.y = rc.top;
		m_ptEnd.y = rc.bottom;
		DrawFill(pDC, m_ptStart, m_ptEnd, CRect(m_ptStart, m_ptEnd));
	}
}

CRect CChartDragCandleAnalAddInImp::DrawFill(CDC *pDC, const CPoint &Startpt, const CPoint &Endpt, const CRect& drawingRegion)
{
	CDC dcCompatible;
    CBitmap bm;
	//비트맵, DC 생성.
    dcCompatible.CreateCompatibleDC(pDC);
    bm.CreateCompatibleBitmap(pDC, Endpt.x - Startpt.x, Endpt.y - Startpt.y);
    CBitmap *pBitmapOld = dcCompatible.SelectObject(&bm);

    //dcCompatible.FillSolidRect(CRect(0, 0, Endpt.x - Startpt.x, Endpt.y - Startpt.y), RGB(230,230,230)); //RGB(0,200,255));//RGB(0x7F, 0x7F, 0x7F)
	dcCompatible.FillSolidRect(CRect(0, 0, Endpt.x - Startpt.x, Endpt.y - Startpt.y), RGB(188,218,244)); //RGB(0,200,255));//RGB(0x7F, 0x7F, 0x7F)

	//dcCompatible.Draw3dRect(0, 0, Endpt.x - Startpt.x, Endpt.y - Startpt.y, RGB(0,0,0),RGB(0,0,0));

    SelectClipRegion(pDC, drawingRegion);
    pDC->BitBlt(Startpt.x, Startpt.y, Endpt.x - Startpt.x, Endpt.y - Startpt.y, &dcCompatible, 0, 0, SRCAND);

	dcCompatible.SelectObject(pBitmapOld);
	bm.DeleteObject();
	dcCompatible.DeleteDC();

	return CRect(Startpt.x, Startpt.y, Endpt.x, Endpt.y);
}

void CChartDragCandleAnalAddInImp::SelectClipRegion(CDC* pDC, const CRect& rect)
{
	CRgn rgn;
	rgn.CreateRectRgn((int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom);
	pDC->SelectClipRgn(&rgn);
}

// 그리는 영역기본값으로 돌린다.
void CChartDragCandleAnalAddInImp::SelectClipRegion(CDC* pDC)
{
	pDC->SelectClipRgn(NULL);
}

BOOL CChartDragCandleAnalAddInImp::GetChartBasicData(int &p_nStartIndex, int &p_nEndIndex, int &p_nR, int &p_nC, CRect &p_rctBlockRegion, CRect &p_rctGraphRegion)
{
	// 현 Data View의 Start/End Index를 구한다.
	if( !m_pIChartOCX->GetViewStartEndIndex( p_nStartIndex, p_nEndIndex)) return FALSE;
	int nV, nG;
	

	// 가격차트가 포함된 Block의 Index를 구한다.
	if( !m_pIChartManager->GetIndexOfGraph(  _MTEXT(C2_PRICE_CHART), p_nR, p_nC, nV, nG)) return FALSE;
	
	// Block의 Log/뒤집기 설정을 확인하여 정확하게 Data를 변환한다. (가격<->Y Pos)
	IBlock *pIBlock = m_pIChartManager->GetBlock(p_nR, p_nC);
	if( pIBlock)
		{
			//20100407 SJ_KIM 함수 변경!!Start!!
			//pIBlock->GetLogAndReverseScaleFlag( m_bLog, m_bReverse);
			m_bLog     = pIBlock->IsLogScale();
			m_bReverse = pIBlock->IsVScaleInvert(nV);
			//20100407 SJ_KIM !!End!!	
			pIBlock->GetVScaleGroupMinMax(nV, m_dViewMin, m_dViewMax);
	   		pIBlock->GetGraphRegions(p_rctGraphRegion, p_rctBlockRegion );

			// Scale에 따른 offset 얻기//////////////////////////////////
			p_rctGraphRegion = pIBlock->GetGraphDrwingRegion();
			//////////////////////////////////////////////////////

			pIBlock->Release();
			pIBlock = NULL;

		}
	return TRUE;
}

int CChartDragCandleAnalAddInImp::GetIndexFromPoint(int x, int nStartIndex, int nEndIndex, CRect rctBlockRegion)
{
	int nBlockWidth = rctBlockRegion.Width();
	int nRet = nStartIndex + ( ( x - rctBlockRegion.left) * ( nEndIndex - nStartIndex + 1)) / nBlockWidth;
	if(nRet > nEndIndex)
		nRet = nEndIndex;
	if(nRet < nStartIndex)
		nRet = nStartIndex;
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
// 데이터로부터 인넥스 얻기
int CChartDragCandleAnalAddInImp::GetIndexFromValue(CString strTime, int nStartIndex, int nEndIndex)
{
	IPacket *pIPacket = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_DATE_TIME));
//	IPacket *pIPacket = m_pIPacketManager->GetPacket( "자료일자");
	int lx = 0;
	try
	{
		ILPCSTR is = pIPacket->GetType();
		CString s = is;
		if(s == "YYYYMMDD")
		{
			lx = atol(strTime.Left(8));
		}
		else if(s == "YYYYMM")
		{
			lx = atol(strTime.Left(6));
		}
		else if(s == "MMDDHHMM")
		{
			if(strTime.GetLength()>=12)
				lx = atol(strTime.Mid(4,8));
		}
		double dTime;
		for(int i=0; i <= nEndIndex ;i++)
		{
			if( !pIPacket->GetData( i, dTime)) throw this;
			if(s == "YYYYMM" && dTime >= 1000000)
			{
				dTime = dTime/100;
			}
			if(lx == ( long)dTime)	// 있으면...
			{
				pIPacket->Release();
				return (i);
			}
			else if(lx < ( long)dTime)
			{
				pIPacket->Release();
				return -1;
			}
		}
		
	}
	catch( CChartDragCandleAnalAddInImp *)
	{
		pIPacket->Release();
		return -1;
	}

	pIPacket->Release();
	return -1; 
}

//////////////////////////////////////////////////////////////////////////
// 주어진 index 가 유효한 것인지 여부 판단
BOOL CChartDragCandleAnalAddInImp::AddData(int nStart, int nEnd)
{
	IPacket *pIPacketForOpen = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_OPEN));
	IPacket *pIPacketForHigh = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_HIGH));
	IPacket *pIPacketForLow = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_LOW));
	IPacket *pIPacketForCur = m_pIDefaultPacketManager->GetPacket( _MTEXT( C0_CLOSE));

// 	IPacket *pIPacketForOpen = m_pIPacketManager->GetPacket( "시가");
// 	IPacket *pIPacketForHigh = m_pIPacketManager->GetPacket( "고가");
// 	IPacket *pIPacketForLow = m_pIPacketManager->GetPacket( "저가");
// 	IPacket *pIPacketForCur = m_pIPacketManager->GetPacket( "종가");
	if(pIPacketForCur == NULL)
		return FALSE;
	try
	{
		m_listDataWindow.RemoveAll();
		double dOpen, dHigh, dLow, dCur=0;
		CString strOpen, strHigh, strLow, strClose;
		for(int i=nStart; i<=nEnd; i++)
		{
			pIPacketForOpen->GetData( i, dOpen);
			strOpen.Format("%.0f", dOpen);
			m_listDataWindow.AddTail(strOpen);

			pIPacketForHigh->GetData( i, dHigh);
			strHigh.Format("%.0f", dHigh);
			m_listDataWindow.AddTail(strHigh);

			pIPacketForLow->GetData( i, dLow);
			strLow.Format("%.0f", dLow);
			m_listDataWindow.AddTail(strLow);

			pIPacketForCur->GetData( i, dCur);
			strClose.Format("%.0f", dCur);
			m_listDataWindow.AddTail(strClose);
		}
	}
	catch( CChartDragCandleAnalAddInImp *)
	{
		pIPacketForOpen->Release();
		pIPacketForHigh->Release();
		pIPacketForLow->Release();
		pIPacketForCur->Release();
		return FALSE;
	}
	pIPacketForOpen->Release();
	pIPacketForHigh->Release();
	pIPacketForLow->Release();
	pIPacketForCur->Release();
	return TRUE;
}

int CChartDragCandleAnalAddInImp::GetXPositoin(double dDataOffset, double dCandleWidth, CRect rctGraphRegion)
{
	int	nLeftBorder, nRightBorder, nDataOffset, nXPos, nAdd;
	double dDecimalFrac;

	nDataOffset = int(dDataOffset);
	dDecimalFrac = dDataOffset - nDataOffset;

	if((int)dCandleWidth > 2)
	{
		// 봉의 좌경계를 구한다. (실 봉의 영역보다 1 Pixcel(여백) 이후이다.)
		nLeftBorder = rctGraphRegion.left + int( dCandleWidth * double( nDataOffset) + 0.5) + 1;
		
		// 봉의 우경계를 구한다. (다음 실 봉의 좌경계보다 1 Pixcel(여백) 이전이다.)
		nRightBorder = rctGraphRegion.left + int( dCandleWidth * double( nDataOffset + 1) + 0.5) - 1;
		// 소수점에 의해 추가될 Pixel
		nAdd = int(dDecimalFrac * dCandleWidth);

		// 봉의 중심을 잡는다. (버림으로 계산한다.)
		nXPos = ( nLeftBorder + nRightBorder) / 2 + nAdd;
	}
	else
	{
		nXPos = rctGraphRegion.left + int( dCandleWidth * double( nDataOffset + 1) + 0.5);
	}

	if( nXPos > rctGraphRegion.right)
		nXPos = rctGraphRegion.right;
	if( nXPos < rctGraphRegion.left)
		nXPos = rctGraphRegion.left;
	return nXPos;
}

void CChartDragCandleAnalAddInImp::OnResetChart()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());

	//////////////////////////////////////////////////////////////////////////
	m_nStartIndex = -1;
	m_nEndIndex = -1;
	//////////////////////////////////////////////////////////////////////////
}
void CChartDragCandleAnalAddInImp::OnPacketDataMultiItem(LPCTSTR lpszRQ, const char *p_szPacketNames, BOOL p_bWithReset)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());

	//////////////////////////////////////////////////////////////////////////
	m_nStartIndex = -1;
	m_nEndIndex = -1;
	//////////////////////////////////////////////////////////////////////////
}

BOOL CChartDragCandleAnalAddInImp::InvokeAddInStr( LPCTSTR p_szCommandName, LPCTSTR p_szData)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	
	int nCommandType = atoi(p_szCommandName);
	
	switch(nCommandType)
	{
	case 0:	// 날짜 세팅
		{
			CString strData = p_szData;
			strData += ":";
			int iStart = 0;
			CString strStartDate = TokenizeEx(strData, ":",iStart);		// 시작날짜
			CString strEndDate = TokenizeEx(strData, ":",iStart);	// 끝날짜
			int nStartIndex, nEndIndex;
			if( !m_pIChartOCX->GetViewStartEndIndex( nStartIndex, nEndIndex))
				return 0;
			m_nStartIndex = GetIndexFromValue(strStartDate, nStartIndex, nEndIndex);
			m_nEndIndex = GetIndexFromValue(strEndDate, nStartIndex, nEndIndex);
			m_bRun = FALSE;
		}
		break;
	case 1:	// draw
		{
		}
		break;
	}

	return TRUE;
}

CString CChartDragCandleAnalAddInImp::TokenizeEx(CString strSrc/*IN*/, const char* pszTokens/*IN*/, int& iStart/*IN, OUT*/)
{
	CString strRes = _T("");
	int iCur = iStart;
	iStart = strSrc.Find(pszTokens, iCur);
	if(iStart != -1)
	{
		strRes = strSrc.Mid(iCur, iStart-iCur);
		iStart++;
		return strRes;
	}
	return strRes;
}