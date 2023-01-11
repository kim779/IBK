// Grp_MA.cpp: implementation of the CGrp_MA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "C_Bong.h"
#include "Grp_MA.h"

#include "GrpWnd.h"
#include "Grp_Data.h"

#include <float.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define	GD_UNUSED	-999999

CGrp_MA::CGrp_MA(CWnd *pView, class CGrpWnd *pGrpWnd, char *pInfo)
: CGrp_Base(pView, pGrpWnd, pInfo)
{
	_maData* maData = nullptr;
	if (_vMA.size() == 0)
	{
		for (int ii = 0; ii < m_pGrpWnd->m_totalDay; ii++)
			_vMA.emplace_back(std::make_unique<_maData>());
	}

	if (m_gKind == CGK_PMA)
	{
		m_maCnt = m_pGrpWnd->m_PMACnt;
		for (int ii = 0; ii < m_maCnt; ii++)
		{
			m_pMA[ii] = m_pGrpWnd->m_PMA[ii];
			CalculatePMA(ii, m_pMA[ii]);
		}
	}
	else
	{
		m_maCnt = m_pGrpWnd->m_VMACnt;
		for (int ii = 0; ii < m_maCnt; ii++)
		{
			m_pMA[ii] = m_pGrpWnd->m_VMA[ii];
			CalculateVMA(ii, m_pMA[ii]);
		}
	}

	CalculateMinMax();
}

CGrp_MA::~CGrp_MA()
{
	_vMA.clear();
}

void CGrp_MA::DrawGraph(CDC *pDC)
{
	struct _MinMaxChk *pMinMaxChk;
	if (pMinMaxChk = m_pGrpWnd->GetMinMaxChk(m_rKey))
	{
		if (pMinMaxChk->coMinMax)
		{
			m_Max = pMinMaxChk->Max;
			m_Min = pMinMaxChk->Min;
			if (m_Max == DBL_MIN || m_Min == DBL_MAX)
				return;
		}
	}

//	if (m_pGrpWnd->m_pRgnInfo[m_rKey]->tick[tkLEFT].bDraw)	DrawTickLeft(pDC, m_Max, m_Min);
//	if (m_pGrpWnd->m_pRgnInfo[m_rKey]->tick[tkRIGHT].bDraw)	DrawTickRight(pDC, m_Max, m_Min);
//	DrawTickBottom(pDC);

	DrawMA(pDC);
}

void CGrp_MA::DrawMA(CDC* pDC)
{
	const int	dispPos = m_pGrpWnd->m_dispPos;
	const int	dispEnd = m_pGrpWnd->m_dispEnd;
	const int	dispDay = m_pGrpWnd->m_dispDay;
	const int	totalDay = m_pGrpWnd->m_totalDay;

	const DWORD	cIndex[maxMA] = {RGB(0,202,2), RGB(255,144,0), RGB(191,169,218), RGB(126,26,77)};
	const CPoint		pt = CPoint(0, 0);
	CString		dispText;
	const int		width = 1;
	const int		style = PS_SOLID;
	COLORREF	color{};
	const int		idx = 0;
	struct	_maData* maData{};

	m_pMAV.resize(totalDay, nullptr);
	for (int ii = 0; ii < maxMA; ii++)
	{
		if (m_pMA[ii] <= 0)
			continue;

		color = cIndex[ii];
		for (int kk = 0; kk < totalDay; kk++)
		{
			maData = _vMA.at(kk).get();
			m_pMAV[kk] = &maData->nmav[ii];
		}

		if (DrawLineMA(pDC, m_pMA[ii], style, width, color))
		{
			dispText.Format("ÀÌÆò(%d)", m_pMA[ii]);
			DrawTickIndex(pDC, dispText, color, true, false, false);
		}
	}
}

bool CGrp_MA::DrawLineMA(CDC* pDC, int nDay, int style, int width, COLORREF color)
{
	const int	dispPos = m_pGrpWnd->m_dispPos;
	const int	dispEnd = m_pGrpWnd->m_dispEnd;
	const int	dispDay = m_pGrpWnd->m_dispDay;

	const int DrawHeight = m_DrawRect.Height();
	const int DrawWidth  = m_DrawRect.Width();

	double ValueHeight = m_Max - m_Min;
	if (!ValueHeight) ValueHeight = 1;

	const int drawShift = int((double(DrawWidth)/ double(dispDay)) / 2);

	int	start = 0;
	if (dispPos < nDay)
		start = nDay - dispPos - 1;
	const int	cnt = 0;
	double	dVal{};
	int ii = 0;
	for (ii = start; ii < dispEnd - dispPos; ii++)
	{
		if (m_pMAV[ii + dispPos] && *m_pMAV[ii+dispPos] != GD_UNUSED)
			break;
	}
	const int	nPoint = (dispEnd - dispPos) - start;
	if (nPoint <= 0)
		return false;
	
	CPen	*cPen = m_pApp->GetPen(m_pView, style, width, color);
	CPen	*sPen = pDC->SelectObject(cPen);

	double	dbTemp{};
	CPoint	pointMAV;
	
	bool	bInit = true;
	for (; ii < dispEnd - dispPos; ii++)
	{
		dVal = *m_pMAV[ii+dispPos];
		if (dVal < m_Min)	dVal = m_Min;
		if (dVal > m_Max)	dVal = m_Max;

		pointMAV.x = m_DrawRect.left + drawShift;
		dbTemp = double(DrawWidth * ii) / double(dispDay);
		pointMAV.x += int(dbTemp);

		pointMAV.y = m_DrawRect.top;
		dbTemp = double((DrawHeight) * (m_Max - dVal));
		dbTemp /= ValueHeight;
		pointMAV.y += int(dbTemp+0.5);

		if (bInit)
		{
			pDC->MoveTo(pointMAV);
			bInit = false;
		}
		else
			pDC->LineTo(pointMAV);
	}

	pDC->SelectObject(sPen);

	if (bInit)
		return false;

	return true;
}

bool CGrp_MA::CalculateMinMax()
{
	m_Max = INT_MIN;
	m_Min = INT_MAX;

	if (_vMA.size() == 0)
		return false;

	const int	start = m_pGrpWnd->m_dispPos;
	const int	end = m_pGrpWnd->m_dispEnd;

	double dVal{};
	for_each(_vMA.begin() + start, _vMA.begin() + end, [&](auto& item)
	{
		for (int jj = 0; jj < m_maCnt; jj++)
		{
			if (item->nmav[jj] == GD_UNUSED)
				continue;

			dVal = item->nmav[jj];
			if (dVal > m_Max)	m_Max = dVal;
			if (dVal < m_Min)	m_Min = dVal;
		}
	});

	if (m_Max == INT_MIN || m_Min == INT_MAX)
		return false;

	double gap = m_Max - m_Min;
	if (gap == 0)
	{
		if (m_Max != DBL_MIN)
		{
			gap = m_Max;
			m_Max += gap / 10;
			m_Min -= gap / 10;
		}
	}
	else
	{
		m_Min -= gap / 10;
	}

	if (m_gKind == CGK_VMA)
		m_Min = 0;

	return true;
}

bool CGrp_MA::IsChangeMinMax(bool bShift)
{
	const double	sMax = m_Max;
	const double  sMin = m_Min;

	if (bShift)
	{
		auto& maData = _vMA.emplace_back(std::make_unique<_maData>());
		for (int jj = 0; jj < maxMA; jj++)
			maData->nmav[jj] = GD_UNUSED;

		_vMA.erase(_vMA.begin());
	}

	if (m_gKind == CGK_PMA)
		CalculateLastPMA();
	else
		CalculateLastVMA();

	if (!CalculateMinMax())
		return false;

	if ((sMax != m_Max) || (sMin != m_Min))
		return true;

	return false;
}

CString CGrp_MA::GetDisplayPosData(CPoint pt)
{
	CString	dispStr = _T("");

	if (m_DrawRect.left > pt.x || m_DrawRect.right <= pt.x)
		return dispStr;

	if (!m_pGrpWnd->m_pDataInfo[m_dKey] || 
		m_pGrpWnd->m_pDataInfo[m_dKey]->GetDataCount() <= 0)
		return dispStr;

	const int	dispPos = m_pGrpWnd->m_dispPos;
	const int	dispEnd = m_pGrpWnd->m_dispEnd;
	const int	dispDay = m_pGrpWnd->m_dispDay;

	const int	xPosition = pt.x - m_DrawRect.left;
	const double	szOneDay = double(m_DrawRect.Width()) / double(dispDay);
	int	dataPos = int(double(xPosition) / szOneDay);
	dataPos += dispPos;

	CString	stmp, stmp2;

	bool	bInit = true;
	int	digit = m_pGrpWnd->m_digit;
	if (m_gKind == CGK_VMA)	digit = 0;

	const struct _maData	*maData = _vMA.at(dataPos).get();
	if (m_gKind == CGK_VMA)
	{
		for (int ii = 0; ii < m_maCnt; ii++)
		{
			if (maData->nmav[ii] == GD_UNUSED)
				continue;

			if (bInit)
			{
				FormatVariableComma(stmp, maData->nmav[ii], digit);
				stmp2.Format("VMA%d", m_pMA[ii]);
				dispStr = stmp2 + "\t" + stmp;
				bInit = false;
			}
			else
			{
				FormatVariableComma(stmp, maData->nmav[ii], digit);
				stmp2.Format("VMA%d", m_pMA[ii]);
				dispStr = dispStr + "\n" + stmp2 + "\t" + stmp;
			}
		}
	}
	else
	{
		for (int ii = 0; ii < m_maCnt; ii++)
		{
			if (maData->nmav[ii] == GD_UNUSED)
				continue;

			if (bInit)
			{
				FormatVariableComma(stmp, maData->nmav[ii], digit);
				stmp2.Format("PMA%d", m_pMA[ii]);
				dispStr = stmp2 + "\t" + stmp;
				bInit = false;
			}
			else
			{
				FormatVariableComma(stmp, maData->nmav[ii], digit);
				stmp2.Format("PMA%d", m_pMA[ii]);
				dispStr = dispStr + "\n" + stmp2 + "\t" + stmp;
			}
		}
	}
	
	return dispStr;
}

CString CGrp_MA::GetExcelData(int idx)
{
	CString	dispStr = __T("");

	if (!m_pGrpWnd->m_pDataInfo[m_dKey] || 
		m_pGrpWnd->m_pDataInfo[m_dKey]->GetDataCount() <= 0)
		return dispStr;

	CString	stmp;
	if (idx < 0)
	{
		if (m_gKind == CGK_VMA)
		{
			for (int ii = 0; ii < m_maCnt; ii++)
			{
				stmp.Format("VMA%d", m_pMA[ii]);
				if (dispStr.IsEmpty())
					dispStr += stmp;
				else
					dispStr += "\t" + stmp;
			}
		}
		else
		{
			for (int ii = 0; ii < m_maCnt; ii++)
			{
				stmp.Format("PMA%d", m_pMA[ii]);
				if (dispStr.IsEmpty())
					dispStr += stmp;
				else
					dispStr += "\t" + stmp;
			}
		}
	}
	else
	{
		int	digit = m_pGrpWnd->m_digit;
		if (m_gKind == CGK_VMA)	digit = 0;
		const struct _maData	*maData = _vMA.at(idx).get();
		for (int ii = 0; ii < m_maCnt; ii++)
		{
			if (maData->nmav[ii] == GD_UNUSED)
				stmp = "0";
			else
				FormatVariableComma(stmp, maData->nmav[ii], digit);
			if (dispStr.IsEmpty())
				dispStr += stmp;
			else
				dispStr += "\t" + stmp;
		}
	}

	return dispStr;
}

int CGrp_MA::CalculatePMA(int idx, int nDay)
{
	if (idx < 0 || nDay <= 0)
		return -1;

	int	ii{};
	struct	_cgBong* gBong{};
	struct	_maData* maData{};
	class CGrp_Data	*pGrpData = m_pGrpWnd->m_pDataInfo[m_dKey].get();
	
	const int totalCnt = m_pGrpWnd->m_totalDay;
	std::vector<double> pvDBL;

	for (ii = 0; ii < totalCnt; ii++)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		pvDBL.emplace_back(double(gBong->epr));
	}

	double	valTOT{};
	for (ii = nDay - 1; ii < totalCnt; ii++)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		maData = _vMA.at(ii).get();

		valTOT = 0.0;
		for (int jj = ii; jj > ii - nDay; jj--)
		{
			if (pvDBL[jj] == GD_UNUSED)
			{
				valTOT = GD_UNUSED;
				break;
			}
			valTOT += pvDBL[jj];
		}

		if (valTOT == GD_UNUSED)
		{
			maData->nmav[idx] = GD_UNUSED;
			continue;
		}
		maData->nmav[idx] = valTOT/double(nDay);
	}

	return idx;
}

void CGrp_MA::CalculateLastPMA()
{
	struct _cgBong* gBong{};
	const int totalCnt = m_pGrpWnd->m_totalDay;
	class CGrp_Data	*pGrpData = m_pGrpWnd->m_pDataInfo[m_dKey].get();
	int ii = 0;
	for (ii = totalCnt - 1; ii >= 0; ii--)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		if (gBong->epr != GD_UNUSED)
			break;
	}

	if (ii < 0)
		return;

	const int	lastIDX = ii;
	const int	validCnt = lastIDX + 1;

	int	jj{};
	double	valTOT{};

	if (_vMA.size() == 0)
		return;

	struct _maData	*maData = _vMA.rbegin()->get();
	for (ii = 0; ii < m_maCnt; ii++)
	{
		if (m_pMA[ii] <= 0)
			break;
		if (m_pMA[ii] > validCnt)
		{
			maData->nmav[ii] = GD_UNUSED;
			continue;
		}

		gBong = (struct _cgBong *)pGrpData->GetGraphData(lastIDX - m_pMA[ii] + 1);
		if (gBong->epr == GD_UNUSED)
		{
			maData->nmav[ii] = GD_UNUSED;
			continue;
		}

		valTOT = 0;
		for (jj = lastIDX - m_pMA[ii] + 1; jj <= lastIDX; jj++)
		{
			gBong = (struct _cgBong *)pGrpData->GetGraphData(jj);
			valTOT += gBong->epr;
		}
		maData->nmav[ii] = valTOT / m_pMA[ii];
	}
}

int CGrp_MA::CalculateVMA(int idx, int nDay)
{
	if (idx < 0 || nDay <= 0)
		return -1;

	int	ii{};
	struct	_cgBong* gBong{};
	struct	_maData* maData{};
	class CGrp_Data	*pGrpData = m_pGrpWnd->m_pDataInfo[m_dKey].get();
	
	const int totalCnt = m_pGrpWnd->m_totalDay;
	std::vector<double> pvDBL;
	for (ii = 0; ii < totalCnt; ii++)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		pvDBL.emplace_back(double(gBong->trn));
	}

	double	valTOT{};
	for (ii = nDay - 1; ii < totalCnt; ii++)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		maData = (struct _maData *)_vMA.at(ii).get();

		valTOT = 0.0;
		for (int jj = ii; jj > ii - nDay; jj--)
		{
			if (pvDBL[jj] == GD_UNUSED)
			{
				valTOT = GD_UNUSED;
				break;
			}
			valTOT += pvDBL[jj];
		}

		if (valTOT == GD_UNUSED)
		{
			maData->nmav[idx] = GD_UNUSED;
			continue;
		}
		maData->nmav[idx] = valTOT/double(nDay);
	}
	return idx;
}

void CGrp_MA::CalculateLastVMA()
{
	struct _cgBong* gBong{};
	const int totalCnt = m_pGrpWnd->m_totalDay;
	class CGrp_Data	*pGrpData = m_pGrpWnd->m_pDataInfo[m_dKey].get();
	int ii = 0;
	for (ii = totalCnt - 1; ii >= 0; ii--)
	{
		gBong = (struct _cgBong *)pGrpData->GetGraphData(ii);
		if (gBong->trn != GD_UNUSED)
			break;
	}

	if (ii < 0)
		return;

	const int	lastIDX = ii;
	const int	validCnt = lastIDX + 1;

	int	jj{};
	double	valTOT{};

	if (_vMA.size() == 0)
		return;

	struct _maData* maData = _vMA.rbegin()->get();
	for (ii = 0; ii < m_maCnt; ii++)
	{
		if (m_pMA[ii] <= 0)
			break;
		if (m_pMA[ii] > validCnt)
		{
			maData->nmav[ii] = GD_UNUSED;
			continue;
		}

		gBong = (struct _cgBong *)pGrpData->GetGraphData(lastIDX - m_pMA[ii] + 1);
		if (gBong->trn == GD_UNUSED)
		{
			maData->nmav[ii] = GD_UNUSED;
			continue;
		}

		valTOT = 0;
		for (jj = lastIDX - m_pMA[ii] + 1; jj <= lastIDX; jj++)
		{
			gBong = (struct _cgBong *)pGrpData->GetGraphData(jj);
			valTOT += gBong->trn;
		}
		maData->nmav[ii] = valTOT / m_pMA[ii];
	}
}
