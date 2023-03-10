// Tendency.cpp: implementation of the CTendency class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tendency.h"
#include  <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTendency::CTendency(CWnd *pView, CWnd *pParent, CRect toolRC, CRect drawRC, int bgColor, CIndcBase* pIndcBase, int tkname)
: CToolBase(pView, pParent, toolRC, drawRC, bgColor, pIndcBase, tkname)
{
	m_bDrawPosiAngle = true;	// added by schbang 2006.03.30

	m_MaxPoint = 0;
	m_MinPoint = 0;

	m_UpDn = -1;
}

CTendency::CTendency(const CTendency* rhs) : CToolBase(rhs)
{
	m_bDrawPosiAngle = true;	// added by schbang 2006.03.30
}

CTendency::~CTendency()
{
}

void CTendency::DrawTool(CDC* pDC)
{
	if (m_pointStart.x == m_pointEnd.x && m_pointStart.y == m_pointEnd.y)
		return;

	CPen* ppenCur;
	CPoint pointStart;
	CPoint pointEnd;

	if (!m_bMove)
	{
		m_pIndcBase->GetValueToPoint(pointStart, m_dPosStart, m_dValueStart);
		m_pIndcBase->GetValueToPoint(pointEnd, m_dPosEnd, m_dValueEnd);
		m_pointStart = pointStart;
		m_pointEnd = pointEnd;

		ppenCur = GetPen(m_pwndView, m_btLStyle, m_btLWidth, m_rgbText);

		ChangeStartEnd(pDC);
	}
	else
	{
		pointStart = m_pointStart;
		pointEnd = m_pointEnd;
		m_pIndcBase->GetPtToPosValue(pointStart, m_dPosStart, m_dValueStart);
		m_pIndcBase->GetPtToPosValue(pointEnd, m_dPosEnd, m_dValueEnd);

		ppenCur = GetPen(m_pwndView, PS_DOT, 1, m_rgbMove);
	}

	int iOldMode = pDC->SetBkMode(TRANSPARENT);
	CPen* ppenOld = pDC->SelectObject(ppenCur);
	int iOldRop = pDC->SetROP2(R2_XORPEN);
	
	if (m_bClipRegion)
		pDC->IntersectClipRect(&m_rectGrp);

	if (!m_bMove)
	{
		// 두점이 모두 영역 밖이면
		if (!m_rectChart.PtInRect(m_pointStart) && !m_rectChart.PtInRect(m_pointEnd))
		{
			// 양쪽이 왼쪽에
			if (m_rectChart.left > m_pointStart.x && m_rectChart.left > m_pointEnd.x)
			{
				if ((m_dwToolOption & TO_END_EXT))
					CalculateDrawingPositionEnd(pointEnd);
			}
			// 양쪽이 오른쪽에
			else if (m_rectChart.right < m_pointStart.x && m_rectChart.right < m_pointEnd.x)
			{
				if ((m_dwToolOption & TO_START_EXT))
					CalculateDrawingPositionStart(pointStart);
			}
		}
		else
		{
			if ((m_dwToolOption & TO_START_EXT))
				CalculateDrawingPositionStart(pointStart);
			
			if ((m_dwToolOption & TO_END_EXT))
				CalculateDrawingPositionEnd(pointEnd);
		}

		pDC->MoveTo(pointStart.x, pointStart.y);
		pDC->LineTo(pointEnd.x, pointEnd.y);
	}

	else
	{
		if ((m_dwToolOption & TO_START_EXT) && (m_dwToolOption & TO_END_EXT))
		{
//			CalculateDrawingPositionStart(pointStart);
//			CalculateDrawingPositionEnd(pointEnd);
			// 두점이 모두 영역 밖이면
			if (!m_rectChart.PtInRect(m_pointStart) && !m_rectChart.PtInRect(m_pointEnd))
			{
				// 양쪽이 왼쪽에
				if (m_rectChart.left > m_pointStart.x && m_rectChart.left > m_pointEnd.x)
				{
					if ((m_dwToolOption & TO_END_EXT))
						CalculateDrawingPositionEnd(pointEnd);
				}
				// 양쪽이 오른쪽에
				else if (m_rectChart.right < m_pointStart.x && m_rectChart.right < m_pointEnd.x)
				{
					if ((m_dwToolOption & TO_START_EXT))
						CalculateDrawingPositionStart(pointStart);
				}
			}
			else
			{
				if ((m_dwToolOption & TO_START_EXT))
					CalculateDrawingPositionStart(pointStart);
				
				if ((m_dwToolOption & TO_END_EXT))
					CalculateDrawingPositionEnd(pointEnd);
			}
			
			pDC->MoveTo(pointStart.x, pointStart.y);
			pDC->LineTo(pointEnd.x, pointEnd.y);
		}
		else if ((m_dwToolOption & TO_START_EXT) || (m_dwToolOption & TO_END_EXT))
		{
			switch (m_eChgUpDn)
			{
			case enumUD::chgDN:
				if ((m_dwToolOption & TO_START_EXT))
				{
					if (pointStart.x > pointEnd.x)
					{
						CalculateDrawingPositionEnd(pointEnd);
						
						pDC->MoveTo(pointStart.x, pointStart.y);
						pDC->LineTo(pointEnd.x, pointEnd.y);
					}
					else
					{
						CalculateDrawingPositionStart(pointStart);
						
						pDC->MoveTo(pointEnd.x, pointEnd.y);
						pDC->LineTo(pointStart.x, pointStart.y);
					}
				}
				
				if ((m_dwToolOption & TO_END_EXT))
				{
					if (pointStart.x > pointEnd.x)
					{
						CalculateDrawingPositionStart(pointStart);
						
						pDC->MoveTo(pointEnd.x, pointEnd.y);
						pDC->LineTo(pointStart.x, pointStart.y);
					}
					else
					{
						CalculateDrawingPositionEnd(pointEnd);
						
						pDC->MoveTo(pointStart.x, pointStart.y);
						pDC->LineTo(pointEnd.x, pointEnd.y);
					}
				}
				break;
			case enumUD::chgUP:
				if ((m_dwToolOption & TO_START_EXT))
				{
					if (pointStart.x < pointEnd.x)
					{
						CalculateDrawingPositionStart(pointStart);
						
						pDC->MoveTo(pointEnd.x, pointEnd.y);
						pDC->LineTo(pointStart.x, pointStart.y);
					}
					else
					{
						CalculateDrawingPositionEnd(pointEnd);
						
						pDC->MoveTo(pointStart.x, pointStart.y);
						pDC->LineTo(pointEnd.x, pointEnd.y);
					}
				}
				
				if ((m_dwToolOption & TO_END_EXT))
				{
					if (pointStart.x < pointEnd.x)
					{
						CalculateDrawingPositionEnd(pointEnd);
						
						pDC->MoveTo(pointStart.x, pointStart.y);
						pDC->LineTo(pointEnd.x, pointEnd.y);
					}
					else
					{
						CalculateDrawingPositionStart(pointStart);
						
						pDC->MoveTo(pointEnd.x, pointEnd.y);
						pDC->LineTo(pointStart.x, pointStart.y);
					}
				}
				break;
			}
		}

		else
		{
			pDC->MoveTo(pointStart.x, pointStart.y);
			pDC->LineTo(pointEnd.x, pointEnd.y);
		}
	}

	if (m_bDrawPosiAngle && ((m_dwToolOption & TO_SHOW_POSI) || (m_dwToolOption & TO_SHOW_ANGLE)))
		DrawPosiAngle(pDC, (m_dwToolOption & TO_SHOW_POSI), (m_dwToolOption & TO_SHOW_ANGLE));

	pDC->SetROP2(iOldRop);
	pDC->SelectObject(ppenOld);
	pDC->SetBkMode(iOldMode);

	CToolBase::InflateHolder();

	if (m_bShowHolder)
		CToolBase::DrawHolder(pDC, true);

	if (m_bClipRegion)
		pDC->SelectClipRgn(NULL);
}

void CTendency::HideTool()
{
	CWnd* pwnd = m_pwndParent;
	if (pwnd)
	{
		CClientDC ClientDC(pwnd);
		DrawTool(&ClientDC);
	}
}

void CTendency::CreateToolLBDN(CPoint pt, bool &bMouseCapture)
{
	m_pointStart = pt;
	m_pointEnd = pt;

	bMouseCapture = TRUE;
	m_bMove = TRUE;
	m_bClipRegion = FALSE;

	InflateHolder();
}

void CTendency::CreateToolLBMV(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);

	m_bDrawPosiAngle = false;
	DrawTool(&ClientDC);
	m_pointEnd = pt;

	CToolBase::InflateHolder();
	DrawTool(&ClientDC);
	m_bDrawPosiAngle = true;
}

void CTendency::CreateToolLBUP(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);
	CToolBase::DrawHolder(&ClientDC, true);
	DrawTool(&ClientDC);

	bMouseCapture = FALSE;
	m_bMove = FALSE;
	m_bClipRegion = TRUE;

	DrawTool(&ClientDC);
}

void CTendency::ChangeToolLBDN(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);
	CToolBase::DrawHolder(&ClientDC, false);

	DrawTool(&ClientDC);
	m_bClipRegion = FALSE;
	DrawTool(&ClientDC);

	if (m_rectDownHolder.PtInRect(pt))
	{
		m_eChgUpDn = enumUD::chgDN;
		m_pointStart = pt;
	}
	else if (m_rectUpHolder.PtInRect(pt))
	{
		m_eChgUpDn = enumUD::chgUP;
		m_pointEnd = pt;
	}

	::SetCapture(m_pwndParent->m_hWnd);
	bMouseCapture = TRUE;

	m_bMove = TRUE;
	m_bClipRegion = FALSE;

	DrawTool(&ClientDC);
}

void CTendency::ChangeToolLBMV(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);

	if (m_bShowHolder)
		CToolBase::DrawHolder(&ClientDC, false);

	m_bDrawPosiAngle = false;	// added by schbang 2006.03.31
	DrawTool(&ClientDC);
	
	switch (m_eChgUpDn)
	{
	case enumUD::chgDN:
		m_pointStart = pt;
		break;
	case enumUD::chgUP:
		m_pointEnd = pt;
		break;
	case enumUD::chgNO:
	default:
		return;
	}   

	DrawTool(&ClientDC);
	m_bDrawPosiAngle = true;	// added by schbang 2006.03.31
	CToolBase::InflateHolder();
}

void CTendency::ChangeToolLBUP(CPoint pt, bool &bMouseCapture)
{
	MoveToolLBUP(pt, bMouseCapture);
}

void CTendency::MoveToolLBDN(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);
	m_pointCur = pt;

	::SetCapture(m_pwndParent->m_hWnd); 
	bMouseCapture = TRUE;

	if (!m_bShowHolder)
		//CToolBase::DrawHolder(&ClientDC, true);
		CToolBase::DrawHolder(&ClientDC, false);
	m_bShowHolder = false;

	DrawTool(&ClientDC);
	m_bClipRegion = FALSE;
	DrawTool(&ClientDC);

	m_bMove = TRUE;
	DrawTool(&ClientDC);
	m_bShowHolder = true;
}

void CTendency::MoveToolLBMV(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);

	if (m_bShowHolder)
		CToolBase::DrawHolder(&ClientDC, false);

	m_bDrawPosiAngle = false;	// added by schbang 2006.03.30
	DrawTool(&ClientDC);
	
	m_pointStart.x += pt.x - m_pointCur.x;
	m_pointStart.y += pt.y - m_pointCur.y;
	m_pointEnd.x += pt.x - m_pointCur.x;
	m_pointEnd.y += pt.y - m_pointCur.y;
//#include "../../h/axisgwin.h"
//	m_pwndParent->SendMessage(GEV_CHART, MAKEWPARAM(chartCtrl, chartUpdate), 0);
	DrawTool(&ClientDC);
	m_bDrawPosiAngle = true;	// added by schbang 2006.03.30

	m_pointCur = pt;
	CToolBase::InflateHolder();
}

void CTendency::MoveToolLBUP(CPoint pt, bool &bMouseCapture)
{
	CClientDC ClientDC(m_pwndParent);

	::ReleaseCapture();
	bMouseCapture = FALSE;
	m_bMove = FALSE;
	m_bClipRegion = TRUE;
	m_bShowHolder = true;

	m_pwndParent->Invalidate();
}

/*
bool CTendency::PtInToolRegion(CPoint pt)
{
	if (!m_rectGrp.PtInRect(pt))
		return false;

	CPoint	point[5];

	CPoint pointStart = (m_dwToolOption & TO_START_EXT) ? m_pointExtStart : m_pointStart;
	CPoint pointEnd = (m_dwToolOption & TO_END_EXT) ? m_pointExtEnd : m_pointEnd;
	
	if (m_pointStart.x == m_pointEnd.x)	// 수직으로 일자인 경우 
	{
		point[0].x = pointStart.x - szREGION;
		point[0].y = pointStart.y;
		point[1].x = pointStart.x + szREGION;
		point[1].y = pointStart.y;
		point[2].x = pointEnd.x + szREGION;
		point[2].y = pointEnd.y;
		point[3].x = pointEnd.x - szREGION;
		point[3].y = pointEnd.y;
		point[4].x = pointStart.x - szREGION;
		point[4].y = pointStart.y;
	}
	else
	{
		point[0].x = pointStart.x;
		point[0].y = pointStart.y - szREGION;
		point[1].x = pointEnd.x;
		point[1].y = pointEnd.y - szREGION;
		point[2].x = pointEnd.x;
		point[2].y = pointEnd.y + szREGION;
		point[3].x = pointStart.x;
		point[3].y = pointStart.y + szREGION;
		point[4].x = pointStart.x;
		point[4].y = pointStart.y - szREGION;
	}

	CRgn rgnTend;
	rgnTend.CreatePolygonRgn(point, 5, WINDING);
	BOOL bInRgn = rgnTend.PtInRegion(pt); 		
	rgnTend.DeleteObject();	

	return (bInRgn ? true : false);
}
*/
bool CTendency::PtInToolRegion(CPoint pt)
{
	if (!m_rectGrp.PtInRect(pt))
		return false;

	CPoint	point[5];

	CPoint pointStart = m_pointStart;
	CPoint pointEnd = m_pointEnd;

	// 두점이 모두 영역 밖이면
	if (!m_rectChart.PtInRect(m_pointStart) && !m_rectChart.PtInRect(m_pointEnd))
	{
		// 양쪽이 왼쪽에
		if (m_rectChart.left > m_pointStart.x && m_rectChart.left > m_pointEnd.x)
		{
			if (m_pointStart.x > m_pointEnd.x)
			{
				if ((m_dwToolOption & TO_START_EXT))
					pointStart = m_pointExtStart;
			}
			else
				if ((m_dwToolOption & TO_END_EXT))
					pointEnd = m_pointExtEnd;
		}
		// 양쪽이 오른쪽에
		else if (m_rectChart.right < m_pointStart.x && m_rectChart.right < m_pointEnd.x)
		{
			if (m_pointStart.x < m_pointEnd.x)
			{
				if ((m_dwToolOption & TO_START_EXT))
					pointStart = m_pointExtStart;
			}
			else
				if ((m_dwToolOption & TO_END_EXT))
					pointEnd = m_pointExtEnd;
		}
	}
	else
	{
		pointStart = (m_dwToolOption & TO_START_EXT) ? m_pointExtStart : m_pointStart;
		pointEnd = (m_dwToolOption & TO_END_EXT) ? m_pointExtEnd : m_pointEnd;
	}
	
	if (m_pointStart.x == m_pointEnd.x)	// 수직으로 일자인 경우 
	{
		point[0].x = pointStart.x - szREGION;
		point[0].y = pointStart.y;
		point[1].x = pointStart.x + szREGION;
		point[1].y = pointStart.y;
		point[2].x = pointEnd.x + szREGION;
		point[2].y = pointEnd.y;
		point[3].x = pointEnd.x - szREGION;
		point[3].y = pointEnd.y;
		point[4].x = pointStart.x - szREGION;
		point[4].y = pointStart.y;
	}
	else
	{
		point[0].x = pointStart.x;
		point[0].y = pointStart.y - szREGION;
		point[1].x = pointEnd.x;
		point[1].y = pointEnd.y - szREGION;
		point[2].x = pointEnd.x;
		point[2].y = pointEnd.y + szREGION;
		point[3].x = pointStart.x;
		point[3].y = pointStart.y + szREGION;
		point[4].x = pointStart.x;
		point[4].y = pointStart.y - szREGION;
	}

	CRgn rgnTend;
	rgnTend.CreatePolygonRgn(point, 5, WINDING);
	BOOL bInRgn = rgnTend.PtInRegion(pt); 		
	rgnTend.DeleteObject();	

	return (bInRgn ? true : false);
}

void CTendency::ChangeMemberValue()
{
	const int offset = 50;

	m_pointStart.Offset(0, offset);
	m_pointEnd.Offset(0, offset);

	if (!CheckValidPoint(m_pointStart) || !CheckValidPoint(m_pointEnd))
	{
		m_pointStart.Offset(0, (offset * 2 * -1));
		m_pointEnd.Offset(0, (offset * 2 * -1));
	}

	InflateHolder();
	CClientDC ClientDC(m_pwndParent);
	m_bMove = true;
	DrawTool(&ClientDC);
	DrawTool(&ClientDC);
	m_bMove = false;
	DrawTool(&ClientDC);
	CToolBase::DrawHolder(&ClientDC, false);
}

void CTendency::DrawPosiAngle(CDC* pDC, BOOL bPosi, BOOL bAngle)
{
	CString strTextS;
	CString strTextE;
	CRect rectS;
	CRect rectE;

	if (bPosi)
	{
		strTextS.Format("%s (%s)", m_pIndcBase->GetYposValue(m_pointStart, false), m_pIndcBase->GetXposValue(m_pointStart));
		CSize size = pDC->GetTextExtent(strTextS);
		rectS.SetRect(m_pointStart.x, m_pointStart.y, m_pointStart.x + size.cx + 4, m_pointStart.y + size.cy + 4);

		strTextE.Format("%s (%s)", m_pIndcBase->GetYposValue(m_pointEnd, false), m_pIndcBase->GetXposValue(m_pointEnd));
		size = pDC->GetTextExtent(strTextE);
		rectE.SetRect(m_pointEnd.x, m_pointEnd.y, m_pointEnd.x + size.cx + 4, m_pointEnd.y + size.cy + 4);
	}
	
	if (bAngle)
	{
		double dX = abs(m_pointEnd.x - m_pointStart.x);
		double dY = abs(m_pointEnd.y - m_pointStart.y);

		if (dX > 0)
		{
			CString strAngle;
			strAngle.Format(" %0.2f°", atan2(dY, dX) * 180 / 3.141592); 

			strTextS += strAngle;
			CSize size = pDC->GetTextExtent(strTextS);
			rectS.SetRect(m_pointStart.x, m_pointStart.y, m_pointStart.x + size.cx + 4, m_pointStart.y + size.cy + 4);
		}
	}

	if (strTextS.IsEmpty() && strTextE.IsEmpty())
		return;

	COLORREF rgbOld;
	rgbOld = pDC->SetTextColor(m_rgbMove);
	CFont* pfontCur = GetFont(m_pwndView, 9, "굴림");
	CFont* pfontOld = pDC->SelectObject(pfontCur);
	pDC->DrawText(strTextS, rectS, DT_SINGLELINE |  DT_LEFT | DT_VCENTER);
	pDC->DrawText(strTextE, rectE, DT_SINGLELINE |  DT_LEFT | DT_VCENTER);

	pDC->SelectObject(pfontOld);
	pDC->SetTextColor(rgbOld);
}
/*
bool CTendency::CalculateDrawingPositionStart(CPoint& pointStart)
{
	enum enumWhichArea {noneAREA = 0, firstAREA, secondAREA, thirdAREA, fourthAREA};

	CPoint pointBase;
	enumWhichArea eWhichArea = noneAREA;

	if (m_pointStart.x <= m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = thirdAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y) 
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.top;
			eWhichArea = secondAREA;
		}
	}
	else
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = fourthAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.top;
			eWhichArea = firstAREA;
		}
	}

	if (eWhichArea == noneAREA)
		return false;

	int iWidth = abs(m_pointStart.x - m_pointEnd.x);
	int iHeight = abs(m_pointStart.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dGannRate = double(double(iHeight) / double(iWidth));

	iWidth  = abs(pointBase.x - m_pointEnd.x);
	iHeight = abs(pointBase.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dBaseRate = double(iHeight) / double(iWidth);

	if (dGannRate == 0)
		dGannRate = 1;

	switch (eWhichArea)
	{
	case firstAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.top);
			pointStart.x = m_pointStart.x + int(iHeight / dGannRate);
			pointStart.y = m_rectChart.top;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.right);
			pointStart.x = m_rectChart.right;
			pointStart.y = m_pointStart.y - int(iWidth * dGannRate);
		}
		break;
	case secondAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.top);
			pointStart.x = m_pointStart.x - int(iHeight / dGannRate);
			pointStart.y = m_rectChart.top;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.left);
			pointStart.x = m_rectChart.left;
			pointStart.y = m_pointStart.y - int(iWidth * dGannRate);

		}
		break;
	case thirdAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.bottom);
			pointStart.x = m_pointStart.x - int(iHeight / dGannRate);
			pointStart.y = m_rectChart.bottom;
TRACE("(%d, %d), (%d, %d)\n", m_pointStart.x, m_pointStart.y, pointStart.x, pointStart.y);
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.left);
			pointStart.x = m_rectChart.left;
			pointStart.y = m_pointStart.y + int(iWidth * dGannRate);

		}
		break;
	case fourthAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.bottom);
			pointStart.x = m_pointStart.x + int(iHeight / dGannRate);
			pointStart.y = m_rectChart.bottom;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.right);
			pointStart.x = m_rectChart.right;
			pointStart.y = m_pointStart.y + int(iWidth * dGannRate);
		}
		break;
	}

	m_pointExtStart = pointStart;

	return true;
}

bool CTendency::CalculateDrawingPositionEnd(CPoint& pointEnd)
{
	enum enumWhichArea {noneAREA = 0, firstAREA, secondAREA, thirdAREA, fourthAREA};

	CPoint pointBase;
	enumWhichArea eWhichArea = noneAREA;

	if (m_pointStart.x <= m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.top;
			eWhichArea = firstAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y) 
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = fourthAREA;
		}
	}
	else
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.top;
			eWhichArea = secondAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = thirdAREA;
		}
	}

	if (eWhichArea == noneAREA)
		return false;	

	int iWidth = abs(m_pointStart.x - m_pointEnd.x);
	int iHeight = abs(m_pointStart.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dGannRate = double(double(iHeight) / double(iWidth));

	iWidth  = abs(pointBase.x - m_pointStart.x);
	iHeight = abs(pointBase.y - m_pointStart.y);
	if (iWidth < 1)
		iWidth = 1;

	double dBaseRate = double(iHeight) / double(iWidth);

	if (dGannRate == 0)
		dGannRate = 1;

	switch (eWhichArea)
	{
	case firstAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.top);
			pointEnd.x = m_pointStart.x + int(iHeight / dGannRate);
			pointEnd.y = m_rectChart.top;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.right);
			pointEnd.x = m_rectChart.right;
			pointEnd.y = m_pointStart.y - int(iWidth * dGannRate);
		}
		break;
	case secondAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.top);
			pointEnd.x = m_pointStart.x - int(iHeight / dGannRate);
			pointEnd.y = m_rectChart.top;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.left);
			pointEnd.x = m_rectChart.left;
			pointEnd.y = m_pointStart.y - int(iWidth * dGannRate);

		}
		break;
	case thirdAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.bottom);
			pointEnd.x = m_pointStart.x - int(iHeight / dGannRate);
			pointEnd.y = m_rectChart.bottom;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.left);
			pointEnd.x = m_rectChart.left;
			pointEnd.y = m_pointStart.y + int(iWidth * dGannRate);

		}
		break;
	case fourthAREA:
		if (dGannRate > dBaseRate)
		{
			iHeight = abs(m_pointStart.y - m_rectChart.bottom);
			pointEnd.x = m_pointStart.x + int(iHeight / dGannRate);
			pointEnd.y = m_rectChart.bottom;
		}
		else
		{
			iWidth = abs(m_pointStart.x - m_rectChart.right);
			pointEnd.x = m_rectChart.right;
			pointEnd.y = m_pointStart.y + int(iWidth * dGannRate);
		}
		break;
	}

	m_pointExtEnd = pointEnd;

	return true;
}
*/
bool CTendency::CalculateDrawingPositionStart(CPoint& rpointStart)
{
	enum enumWhichArea {noneAREA = 0, firstAREA, secondAREA, thirdAREA, fourthAREA};

	CPoint pointBase;
	enumWhichArea eWhichArea = noneAREA;

	if (m_pointStart.x < m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = thirdAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y) 
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.top;
			eWhichArea = secondAREA;
		}
		else
		{
			rpointStart.x = m_rectChart.left;
			rpointStart.y = m_pointStart.y;
			m_pointExtStart = rpointStart;
			return true;
		}
	}
	else if (m_pointStart.x > m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = fourthAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.top;
			eWhichArea = firstAREA;
		}
		else
		{
			rpointStart.x = m_rectChart.right;
			rpointStart.y = m_pointStart.y;
			m_pointExtStart = rpointStart;
			return true;
		}
	}
	else
	{
		rpointStart.x = m_pointStart.x;
		if (m_pointStart.y > m_pointEnd.y)
		{
			rpointStart.y = m_rectChart.bottom;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			rpointStart.y = m_rectChart.top;
		}
		else
		{
			rpointStart.y = m_pointStart.y;
		}
		m_pointExtStart = rpointStart;
		return true;
	}

	if (eWhichArea == noneAREA)
		return false;

	int iWidth = abs(m_pointStart.x - m_pointEnd.x);
	int iHeight = abs(m_pointStart.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dGannRate = double(double(iHeight) / double(iWidth));

	iWidth  = abs(pointBase.x - m_pointEnd.x);
	iHeight = abs(pointBase.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dBaseRate = double(iHeight) / double(iWidth);

	if (dGannRate == 0)
		dGannRate = 1;

	switch (eWhichArea)
	{
	case firstAREA:
		if (dGannRate > dBaseRate)
		{
			rpointStart.x = m_pointEnd.x + int(iHeight / dGannRate);
			rpointStart.y = m_rectChart.top;
		}
		else
		{
			rpointStart.x = m_rectChart.right;
			rpointStart.y = m_pointEnd.y - int(iWidth * dGannRate);
		}
		break;
	case secondAREA:
		if (dGannRate > dBaseRate)
		{
			rpointStart.x = m_pointEnd.x - int(iHeight / dGannRate);
			rpointStart.y = m_rectChart.top;
		}
		else
		{
			rpointStart.x = m_rectChart.left;
			rpointStart.y = m_pointEnd.y - int(iWidth * dGannRate);

		}
		break;
	case thirdAREA:
		if (dGannRate > dBaseRate)
		{
			rpointStart.x = m_pointEnd.x - int(iHeight / dGannRate);
			rpointStart.y = m_rectChart.bottom;
		}
		else
		{
			rpointStart.x = m_rectChart.left;
			rpointStart.y = m_pointEnd.y + int(iWidth * dGannRate);

		}
		break;
	case fourthAREA:
		if (dGannRate > dBaseRate)
		{
			rpointStart.x = m_pointEnd.x + int(iHeight / dGannRate);
			rpointStart.y = m_rectChart.bottom;
		}
		else
		{
			iWidth = abs(m_pointEnd.x - m_rectChart.right);
			rpointStart.x = m_rectChart.right;
			rpointStart.y = m_pointEnd.y + int(iWidth * dGannRate);
		}
		break;
	}

	m_pointExtStart = rpointStart;

	return true;
}

bool CTendency::CalculateDrawingPositionEnd(CPoint& rpointEnd)
{
	enum enumWhichArea {noneAREA = 0, firstAREA, secondAREA, thirdAREA, fourthAREA};

	CPoint pointBase;
	enumWhichArea eWhichArea = noneAREA;

	if (m_pointStart.x < m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.top;
			eWhichArea = firstAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y) 
		{
			pointBase.x = m_rectChart.right;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = fourthAREA;
		}
		else
		{
			rpointEnd.x = m_rectChart.right;
			rpointEnd.y = m_pointEnd.y;
			m_pointExtEnd = rpointEnd;
			return true;
		}
	}
	else if (m_pointStart.x > m_pointEnd.x)
	{
		if (m_pointStart.y > m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.top;
			eWhichArea = secondAREA;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			pointBase.x = m_rectChart.left;
			pointBase.y = m_rectChart.bottom;
			eWhichArea = thirdAREA;
		}
		else
		{
			rpointEnd.x = m_rectChart.left;
			rpointEnd.y = m_pointEnd.y;
			m_pointExtEnd = rpointEnd;
			return true;
		}
	}
	else
	{
		rpointEnd.x = m_pointEnd.x;
		if (m_pointStart.y > m_pointEnd.y)
		{
			rpointEnd.y = m_rectChart.top;
		}
		else if (m_pointStart.y < m_pointEnd.y)
		{
			rpointEnd.y = m_rectChart.bottom;
		}
		else
		{
			rpointEnd.y = m_pointEnd.y;
		}
		m_pointExtEnd = rpointEnd;
		return true;
	}

	if (eWhichArea == noneAREA)
		return false;

	int iWidth = abs(m_pointStart.x - m_pointEnd.x);
	int iHeight = abs(m_pointStart.y - m_pointEnd.y);
	if (iWidth < 1)
		iWidth = 1;

	double dGannRate = double(double(iHeight) / double(iWidth));

	iWidth  = abs(pointBase.x - m_pointStart.x);
	iHeight = abs(pointBase.y - m_pointStart.y);
	if (iWidth < 1)
		iWidth = 1;

	double dBaseRate = double(iHeight) / double(iWidth);

	if (dGannRate == 0)
		dGannRate = 1;

	switch (eWhichArea)
	{
	case firstAREA:
		if (dGannRate > dBaseRate)
		{
			rpointEnd.x = m_pointStart.x + int(iHeight / dGannRate);
			rpointEnd.y = m_rectChart.top;
		}
		else
		{
			rpointEnd.x = m_rectChart.right;
			rpointEnd.y = m_pointStart.y - int(iWidth * dGannRate);
		}
		break;
	case secondAREA:
		if (dGannRate > dBaseRate)
		{
			rpointEnd.x = m_pointStart.x - int(iHeight / dGannRate);
			rpointEnd.y = m_rectChart.top;
		}
		else
		{
			rpointEnd.x = m_rectChart.left;
			rpointEnd.y = m_pointStart.y - int(iWidth * dGannRate);

		}
		break;
	case thirdAREA:
		if (dGannRate > dBaseRate)
		{
			rpointEnd.x = m_pointStart.x - int(iHeight / dGannRate);
			rpointEnd.y = m_rectChart.bottom;
		}
		else
		{
			rpointEnd.x = m_rectChart.left;
			rpointEnd.y = m_pointStart.y + int(iWidth * dGannRate);

		}
		break;
	case fourthAREA:
		if (dGannRate > dBaseRate)
		{
			rpointEnd.x = m_pointStart.x + int(iHeight / dGannRate);
			rpointEnd.y = m_rectChart.bottom;
		}
		else
		{
			rpointEnd.x = m_rectChart.right;
			rpointEnd.y = m_pointStart.y + int(iWidth * dGannRate);
		}
		break;
	}

	m_pointExtEnd = rpointEnd;

	return true;
}

void CTendency::ChangeStartEnd(CDC *pDC)
{	
	double oldsPosStart;
	double oldePosEnd;
	
	double oldsdValueStart;
	double oldedValueEnd;
	
	CPoint oldsPoint;
	CPoint oldePoint;

	oldsPosStart = m_dPosStart;
	oldePosEnd   = m_dPosEnd;
	
	oldsdValueStart = m_dValueStart;
	oldedValueEnd   = m_dValueEnd;
	
	oldsPoint = m_pointStart;
	oldePoint = m_pointEnd;
	
	
	if (m_pointStart.x > m_pointEnd.x)
	{
		m_dPosStart   = oldePosEnd;
		m_dPosEnd     = oldsPosStart;
		
		m_dValueStart = oldedValueEnd;
		m_dValueEnd   = oldsdValueStart;
		
		m_pointStart  = oldePoint;
		m_pointEnd    = oldsPoint;
		
		if ((m_dwToolOption & TO_END_EXT) && (m_dwToolOption & TO_START_EXT))
			return;
		else if ((m_dwToolOption & TO_END_EXT) || (m_dwToolOption & TO_START_EXT))
		{
			pDC->MoveTo(m_pointStart.x, m_pointStart.y);
			pDC->LineTo(m_pointEnd.x, m_pointEnd.y);
		}
	}
}
