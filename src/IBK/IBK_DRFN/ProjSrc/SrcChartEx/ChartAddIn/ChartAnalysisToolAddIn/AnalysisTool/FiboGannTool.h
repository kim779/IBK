// FiboGannTool.h: interface for the CFiboGannTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIBOGANNTOOL_H__08A88409_A0E8_4E0B_A613_7C19334DBB4F__INCLUDED_)
#define AFX_FIBOGANNTOOL_H__08A88409_A0E8_4E0B_A613_7C19334DBB4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PointTool.h"
#include "FiboGannDrawer.h"

class CAnalysisData;


// 피보나치 반원
class CFiboSemicircleTool : public CTwoPointDownTool
{
public:
	CFiboSemicircleTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);
	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CTwoPointDrawer& GetTwoPointDrawer();
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();
private:
	CTextShowPosition m_textPosition;
	CFiboSemicircleDrawer m_fiboSemicircleDrawer;
};

// 피보나치 원
class CFiboCircleTool : public CTwoPointDownTool
{
public:
	CFiboCircleTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);
	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);
protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CTwoPointDrawer& GetTwoPointDrawer();
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();

private:
	CTextShowPosition m_textPosition;
	CFiboCircleDrawer m_fiboCircleDrawer;
};

// 피보나치 펜라인
class CFiboPenLineTool : public CTwoPointDownTool
{
public:
	CFiboPenLineTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);
	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);
protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CTwoPointDrawer& GetTwoPointDrawer();
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();
private:
	CTextShowPosition m_textPosition;
	CFiboPenLineDrawer m_fiboPenLineDrawer;
};

// 피보나치 되돌림(조정대)
class CFiboRetraceTool : public CTwoPointDownTool
{
public:
	CFiboRetraceTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);
	void SetTextEnvironment(const CTextEnvironment& textEnvironment);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();
	virtual CTwoPointDrawer& GetTwoPointDrawer();
	bool IsMakeElement(const CPoint& point) const;

private:
	CTextShowPosition m_textPosition;
	CFiboRetraceDrawer m_fiboRetraceDrawer;
};

// 피보나치 시간대
class CFiboTimeTool : public COnePointMoveTool
{
public:
	CFiboTimeTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

	// 2008.08.20 김진순 피보나치 확장
	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);

public:
	virtual void OnLButtonUp(CDC* pDC, const CPoint& point);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual COnePointDrawer& GetOnePointDrawer();
	// 2008.08.20 김진순 피보나치 확장
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();

private:	
	// 2008.08.20 김진순 피보나치 확장
	CTextShowPosition m_textPosition;
	CFiboTimeDrawer m_fiboTimeDrawer;
};

// ----------------------------------------------------------------------------
// 갠
class CGannTool : public CTwoPointMoveTool
{
public:
	CGannTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

public:
	virtual void OnLButtonUp(CDC* pDC, const CPoint& point);

protected:
	virtual CPoints GetTwoPoints() const;

	virtual const CGannDrawer& GetGannDrawer() const = 0;
};

// 갠라인
class CGannLineTool : public CGannTool
{
public:
	CGannLineTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CTwoPointDrawer& GetTwoPointDrawer();

	virtual const CGannDrawer& GetGannDrawer() const;

private:
	CGannLineDrawer m_gannLineDrawer;
};

// 45도 갠라인
class CGannLine45Tool : public CGannLineTool
{
public:
	CGannLine45Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
};

// 315(-45)도 갠라인
class CGannLine315Tool : public CGannLineTool
{
public:
	CGannLine315Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CPoints GetTwoPoints() const;
};

// 갠펜
class CGannFanTool : public CGannTool
{
public:
	CGannFanTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);
	void SetTextPosition(const CTextShowPosition& position);
	void SetTextPosition(const bool bShow);
protected:
	virtual CTwoPointDrawer& GetTwoPointDrawer();
	virtual const CTextPosition* GetTextPosition() const;
	virtual CTextPosition* GetTextPosition();
	virtual const CGannDrawer& GetGannDrawer() const;

private:
	CTextShowPosition m_textPosition;
	CGannFanDrawer m_gannFanDrawer;
};

// 45도 갠펜
class CGannFan45Tool : public CGannFanTool
{
public:
	CGannFan45Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
};

// 135도 갠펜
class CGannFan135Tool : public CGannFanTool
{
public:
	CGannFan135Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CPoints GetTwoPoints() const;
};

// 225도 갠펜
class CGannFan225Tool : public CGannFanTool
{
public:
	CGannFan225Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CPoints GetTwoPoints() const;
};

// 315(-45)도 갠펜
class CGannFan315Tool : public CGannFanTool
{
public:
	CGannFan315Tool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CPoints GetTwoPoints() const;
};

// 갠그리드
class CGannGridTool : public CGannTool
{
public:
	CGannGridTool(CAnalysisData* pAnalysisData = NULL, const CAnalysis::COORDINATETYPE eCoordinateType = CAnalysis::RELATIVE_POINT);

protected:
	virtual CAnalysis::TOOLTYPE GetToolType() const;
	virtual CTwoPointDrawer& GetTwoPointDrawer();

	virtual const CGannDrawer& GetGannDrawer() const;

private:
	CGannGridDrawer m_gannGridDrawer;
};

#endif // !defined(AFX_FIBOGANNTOOL_H__08A88409_A0E8_4E0B_A613_7C19334DBB4F__INCLUDED_)
