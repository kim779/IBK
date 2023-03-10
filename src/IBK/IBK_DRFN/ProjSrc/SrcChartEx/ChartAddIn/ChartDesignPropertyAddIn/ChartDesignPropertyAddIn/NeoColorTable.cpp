#include "stdafx.h"
#include "NeoColorTable.h"

COLORREF RGB_Color_Table[] = 
{
	RGB(238,238,238),	RGB(221,221,221),	RGB(204,204,204),	RGB(187,187,187),	
	RGB(170,170,170),	RGB(153,153,153),	RGB(136,136,136),	RGB(119,119,119),
	RGB(102,102,102),	RGB(85,85,85),		RGB(68,68,68),		RGB(51,51,51),
	RGB(34,34,34),		RGB(17,17,17),		RGB(0,0,0),			RGB(255,0,0),		
	RGB(238,0,0),		RGB(221,0,0),		RGB(204,0,0),		RGB(187,0,0),	//20-1	
	
	RGB(170,0,0),		RGB(153,0,0),		RGB(136,0,0),		RGB(119,0,0),	
	RGB(102,0,0),		RGB(85,0,0),		RGB(68,0,0),		RGB(51,0,0),		
	RGB(34,0,0),		RGB(17,0,0),		RGB(255,255,255),	RGB(255,255,204),
	RGB(255,255,153),	RGB(255,255,102),	RGB(255,255,51),	RGB(255,255,0),	
	RGB(204,255,255),	RGB(204,255,204),	RGB(204,255,153),	RGB(204,255,102),	//40-1

	RGB(204,255,51),	RGB(204,255,0),		RGB(153,255,255),	RGB(153,255,204),	
	RGB(153,255,153),	RGB(153,255,102),	RGB(153,255,51),	RGB(153,255,0),
	RGB(102,255,255),	RGB(102,255,204),	RGB(102,255,153),	RGB(102,255,102),
	RGB(102,255,51),	RGB(102,255,0),		RGB(51,255,255),	RGB(51,255,204),	
	RGB(51,255,153),	RGB(51,255,102),	RGB(51,255,51),		RGB(51,255,0),	//60-1

	RGB(0,255,255),		RGB(0,255,204),		RGB(0,255,153),		RGB(0,255,102),		
	RGB(0,255,51),		RGB(255,204,255),	RGB(255,204,204),	RGB(255,204,153),	
	RGB(255,204,102),	RGB(255,204,51),	RGB(255,204,0),		RGB(204,204,255),	
	RGB(204,204,153),	RGB(204,204,102),	RGB(204,204,51),	RGB(204,204,0),
	RGB(153,204,255),	RGB(153,204,204),	RGB(153,204,153),	RGB(153,204,102),	//80-1

	RGB(153,204,51),	RGB(153,204,0),		RGB(102,204,255),	RGB(102,204,204),	
	RGB(102,204,153),	RGB(102,204,102),	RGB(102,204,51),	RGB(102,204,0),
	RGB(51,204,255),	RGB(51,204,204),	RGB(51,204,153),	RGB(51,204,102),	
	RGB(51,204,51),		RGB(51,204,0),		RGB(0,204,255),		RGB(0,204,204),		
	RGB(0,204,153),		RGB(0,204,102),		RGB(0,204,51),		RGB(255,153,255),	//100-1

	RGB(255,153,204),	RGB(255,153,153),	RGB(255,153,102),	RGB(255,153,51),	
	RGB(255,153,0),		RGB(204,153,255),	RGB(204,153,204),	RGB(204,153,153),	
	RGB(204,153,102),	RGB(204,153,51),	RGB(204,153,0),		RGB(153,153,255),	
	RGB(153,153,204),	RGB(153,153,102),	RGB(153,153,51),	RGB(153,153,0),
	RGB(102,153,255),	RGB(102,153,204),	RGB(102,153,153),	RGB(102,153,102),	//120-1

	RGB(102,153,51),	RGB(102,153,0),		RGB(51,153,255),	RGB(51,153,204),	
	RGB(51,153,153),	RGB(51,153,102),	RGB(51,153,51),		RGB(51,153,0),
	RGB(0,153,255),		RGB(0,153,204),		RGB(0,153,153),		RGB(0,153,102),
	RGB(0,153,51),		RGB(255,102,255),	RGB(255,102,204),	RGB(255,102,153),	
	RGB(255,102,102),	RGB(255,102,51),	RGB(255,102,0),		RGB(204,102,255),	//140-1

	RGB(204,102,204),	RGB(204,102,153),	RGB(204,102,102),	RGB(204,102,51),
	RGB(204,102,0),		RGB(153,102,255),	RGB(153,102,204),	RGB(153,102,153),
	RGB(153,102,102),	RGB(153,102,51),	RGB(153,102,0),		RGB(102,102,255),	
	RGB(102,102,204),	RGB(102,102,153),	RGB(102,102,51),	RGB(102,102,0),
	RGB(51,102,255),	RGB(51,102,204),	RGB(51,102,153),	RGB(51,102,102),	//160-1

	RGB(51,102,51),		RGB(51,102,0),		RGB(0,102,255),		RGB(0,102,204),		
	RGB(0,102,153),		RGB(0,102,102),		RGB(0,102,51),		RGB(255,51,255),	
	RGB(255,51,204),	RGB(255,51,153),	RGB(255,51,102),	RGB(255,51,51),
	RGB(255,51,0),		RGB(204,51,255),	RGB(204,51,204),	RGB(204,51,153),
	RGB(204,51,102),	RGB(204,51,51),		RGB(204,51,0),		RGB(153,51,255),	//180-1
	
	RGB(153,51,204),	RGB(153,51,153),	RGB(153,51,102),	RGB(153,51,51),		
	RGB(153,51,0),		RGB(102,51,255),	RGB(102,51,204),	RGB(102,51,153),	
	RGB(102,51,102),	RGB(102,51,51),		RGB(102,51,0),		RGB(51,51,255),
	RGB(51,51,204),		RGB(51,51,153),		RGB(51,51,102),		RGB(51,51,0),
	RGB(0,51,255),		RGB(0,51,204),		RGB(0,51,153),		RGB(0,51,102),		//200-1

	RGB(0,51,51),		RGB(255,0,255),		RGB(255,0,204),		RGB(255,0,153),		
	RGB(255,0,102),		RGB(255,0,51),		RGB(204,0,255),		RGB(204,0,204),		
	RGB(204,0,153),		RGB(204,0,102),		RGB(204,0,51),		RGB(153,0,255),		
	RGB(153,0,204),		RGB(153,0,153),		RGB(153,0,102),		RGB(153,0,51),
	RGB(102,0,255),		RGB(102,0,204),		RGB(102,0,153),		RGB(102,0,102),		//220-1

	RGB(102,0,51),		RGB(51,0,255),		RGB(51,0,204),		RGB(51,0,153),		
	RGB(51,0,102),		RGB(51,0,51),		RGB(0,255,0),		RGB(0,238,0),	
	RGB(0,221,0),		RGB(0,204,0),		RGB(0,187,0),		RGB(0,170,0),		
	RGB(0,153,0),		RGB(0,136,0),		RGB(0,119,0),		RGB(0,102,0),		
	RGB(0,85,0),		RGB(0,65,0),		RGB(0,51,0),		RGB(0,34,0),		//240-1
	
	RGB(0,17,0),		RGB(0,0,255),		RGB(0,0,248),		RGB(0,0,221),		
	RGB(0,0,204),		RGB(0,0,187),		RGB(0,0,170),		RGB(0,0,153),		
	RGB(0,0,136),		RGB(0,0,119),		RGB(0,0,102),		RGB(0,0,85),		
	RGB(0,0,65),		RGB(0,0,51),		RGB(0,0,34),		RGB(0,0,11)			//256-1
};

CColorTableMgr::CColorTableMgr()
{
}

CColorTableMgr::~CColorTableMgr()
{
}



COLORREF CColorTableMgr::GetColor(int nIndex)
{
	if(nIndex >=255 || nIndex <0) return RGB(0,0,0);
		return RGB_Color_Table[nIndex];
}

int CColorTableMgr::GetColorIndex(COLORREF color)
{
	for(int i = 0;i<256;i++)
	{
		if(color == RGB_Color_Table[i]) return i;
	}
	return -1;
}

CString  CColorTableMgr::GetColorText(int nIndex)
{
	CString szReturn("RGB(0,0,0)");
	if(nIndex >= 255 || nIndex <0) return szReturn;

	COLORREF color = RGB_Color_Table[nIndex];
	szReturn.Format("RGB(%d,%d,%d)",GetRValue(color),GetGValue(color), GetBValue(color));
	return szReturn;
}
