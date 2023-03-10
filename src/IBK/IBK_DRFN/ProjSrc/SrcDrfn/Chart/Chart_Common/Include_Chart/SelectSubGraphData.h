// SelectSubGraphData.h: interface for the CSelectSubGraphData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTSUBGRAPHDATA_H__CB0433E3_FDE0_4978_85E3_7222193FDA25__INCLUDED_)
#define AFX_SELECTSUBGRAPHDATA_H__CB0433E3_FDE0_4978_85E3_7222193FDA25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseData.h"

class CIndicatorInfo;

// subGraph를 찾는거에 대한 data
class CSelectSubGraphData
{
public:
	CSelectSubGraphData();

	void SetDrawingOrderType(const CDrawingOption::DRAWINGORDER eDrawingOrderType);
	void SetGraphFunctionName(const CString& functionName);
	void SetVertScaleLogType(const bool bIsVertScaleLogType);
	void SetVertScaleInvertType(const bool bIsVertScaleInvertType);
	void SetGraphRegions(const CGraphRegions& graphRegions);
	void SetSubGraphType(const CGraphBaseData::GRAPHTYPE subGraphType);
	void SetSubGraphStyle(const CGraphStyle& subGraphStyle);
	void SetSubGraphDrawStyle(const CGraphDrawStyle& subGraphDrawStyle);
	void SetDisplayDataHorzMinMax(const CDisplayDataMinMax& displayDataMinMax);
	void SetDisplayDataVertMinMax(const CDisplayDataMinMax& displayDataMinMax);
	void SetDisplayAttributes(const CDisplayAttributes& displayAttributes);
	void SetSubGraphPacketList(CSubGraphPacketList* pSubGraphPacketList);
	void SetIndicatorInfo(CIndicatorInfo* pIndicatorInfo);

	CDrawingOption::DRAWINGORDER GetDrawingOrderType() const;
	CString GetGraphFunctionName() const;
	bool GetVertScaleLogType() const;
	bool GetVertScaleInvertType() const;
	CGraphRegions GetGraphRegions() const;
	CGraphBaseData::GRAPHTYPE GetSubGraphType() const;
	CGraphStyle GetSubGraphStyle() const;
	CGraphDrawStyle GetSubGraphDrawStyle() const;
	CDisplayDataMinMax GetDisplayDataHorzMinMax() const;
	CDisplayDataMinMax GetDisplayDataVertMinMax() const;
	CDisplayAttributes GetDisplayAttributes() const;
	CSubGraphPacketList* GetSubGraphPacketList() const;
	CIndicatorInfo* GetIndicatorInfo() const;

private:
	CDrawingOption::DRAWINGORDER m_eDrawingOrderType;
	CString m_strFunctionName;		// 함수명
	bool m_bIsVertScaleLogType;		// 세로 scale log type 유무
	bool m_bIsVertScaleInvertType;	// 세로 scale 뒤집기(기본값 = false)
	CGraphRegions m_graphRegions;	// graph 그리는 영역들
	CGraphBaseData::GRAPHTYPE m_TYPESubGraphType; // subGraph type
	CGraphStyle m_nSubGraphStyle;	// subGraph style
	CGraphDrawStyle m_nSubGraphDrawStyle;	// subGraph draw style
	CDisplayDataMinMax m_displayDataHorzMinMax;	// 가로 min/max
	CDisplayDataMinMax m_displayDataVertMinMax;	// 세로 min/max
	CDisplayAttributes m_displayAttributes;		// 화면에 그릴 시작/끝
	CSubGraphPacketList* m_pSubGraphPacketList;
	CIndicatorInfo* m_pIndicatorInfo;
};


#endif // !defined(AFX_SELECTSUBGRAPHDATA_H__CB0433E3_FDE0_4978_85E3_7222193FDA25__INCLUDED_)
