#if !defined(AFX_GRP_LINE1_H__DF133B14_26CE_4EE6_8EAC_4C5238B434D7__INCLUDED_)
#define AFX_GRP_LINE1_H__DF133B14_26CE_4EE6_8EAC_4C5238B434D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Grp_Base.h"
#include <afxtempl.h>
class CGrp_Line1 : public CGrp_Base  
{
public:
	CGrp_Line1(CWnd* pView, class CGrpWnd *pGrpWnd, char *pInfo);
	virtual ~CGrp_Line1();

	void	DrawGraph(CDC *pDC);
	bool	CalculateMinMax();
	bool	IsChangeMinMax(bool bShift = false);
	CString	GetDisplayPosData(CPoint pt);

private:
	void	DrawLine(CDC *pDC);
	void	DrawLegend(CDC* pDC);	

private:
	struct _cgIndex	m_MaxDayIndex, m_MinDayIndex;
	CPoint	m_MaxDayPos, m_MinDayPos;
	double	m_dispMaxVal, m_dispMinVal;
	CArray <COLORREF, COLORREF>	m_arColor;

	CWnd*	m_pView;
};

#endif // !defined(AFX_GRP_LINE1_H__DF133B14_26CE_4EE6_8EAC_4C5238B434D7__INCLUDED_)
