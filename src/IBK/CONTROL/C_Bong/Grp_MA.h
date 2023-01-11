// Grp_MA.h: interface for the CGrp_MA class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Grp_Base.h"
#include <afxtempl.h>

#define	maxMA	4
struct	_maData
{
	double	nmav[maxMA]{ -999999, -999999 ,-999999 ,-999999 };
};

class CGrp_MA : public CGrp_Base  
{
public:
	CGrp_MA(CWnd *pView, class CGrpWnd *pGrpWnd, char *pInfo);
	virtual ~CGrp_MA();

	void	DrawGraph(CDC *pDC);
	bool	CalculateMinMax();
	bool	IsChangeMinMax(bool bShift);
	CString	GetDisplayPosData(CPoint pt);
	CString	GetExcelData(int idx);

private:
	void	DrawMA(CDC* pDC);
	bool	DrawLineMA(CDC* pDC, int nDay, int style, int width, COLORREF color);
	int	CalculatePMA(int idx, int nDay);
	void	CalculateLastPMA();
	int	CalculateVMA(int idx, int nDay);
	void	CalculateLastVMA();

protected:
	//CArray	<_maData *, _maData *> m_maQue;
	std::vector<std::unique_ptr<_maData>> _vMA;
	std::vector<double*>		      m_pMAV;

	int	m_maCnt{};
	int	m_pMA[maxMA]{};
};
