// Grp_Base.h: interface for the CGrp_Base class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRP_BASE_H__FE8A4317_D994_495D_BC6C_4E7C373D5FE8__INCLUDED_)
#define AFX_GRP_BASE_H__FE8A4317_D994_495D_BC6C_4E7C373D5FE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../h/axiscgrp.h"
#define	VOLUNIT	1000000
class CGrp_Base  
{
public:
	CGrp_Base(CWnd* pView, class CGrpWnd *pGrpWnd, char *pInfo);
	virtual ~CGrp_Base();
	
public:
	CRect DisplayRect(CDC *pDC, int idx, CString dispStr, CPoint dispPt);
	virtual void	DrawGraph(CDC *pDC) {}
	virtual bool	CalculateMinMax() { return false; }
	virtual bool	IsChangeMinMax(bool bShift = false) { return false; }
	virtual void	GetMinMaxValue(double& dMin, double& dMax);
	virtual CString	GetDisplayPosHead(CPoint pt);
	virtual CString	GetDisplayPosData(CPoint pt)	{ return ""; }
	void	Resize();

	void	DrawTickHorizon(CDC* pDC, double Max, double Min, int tickinfo);
	void	DrawTickBottom(CDC *pDC);
	int	DrawTickIndex(CDC* pDC, CString dispText, COLORREF tColor, bool bColor, bool bIndex = false, CPoint pt = CPoint(-1,-1));
	void	FormatVariableComma(CString &dispTxt, double dVal, int point, int maxDigit = 10);
	int	GetTickCount(int dir);
	bool	calculateDisplay(double div, double Max, double Min, double& drawMinValue, 
			int dispTICK, double* dispValue, int& dispCount);

	int	GetRgnKey() { return m_rKey; }
	int	GetGrpKind() { return m_gKind; }

protected:
	class CGrpWnd	*m_pGrpWnd;

	int	m_gKind;
	int	m_rKey;
	int	m_dKey;
	int	m_dKind;
	int	m_dIndex;

	CRect	m_DrawRect;
	CRect	m_RgnRect;
	COLORREF	m_tRGB;
	COLORREF	m_pRGB;

	double	m_Max;
	double	m_Min;
	CaxisMInvestApp*	m_pApp;
	CWnd*	m_pView;
};

#endif // !defined(AFX_GRP_BASE_H__FE8A4317_D994_495D_BC6C_4E7C373D5FE8__INCLUDED_)
