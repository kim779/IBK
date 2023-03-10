/*************************************************************************
				Class Declaration : CUGAdvProgressType
**************************************************************************
	Source file : UGCTpro1.cpp
	Header file : UGCTpro1.h
	Copyright ? Dundas Software Ltd. 1994 - 2002, All Rights Reserved

    Purpose
		Creates an advanced progress bar that gives more detail over 
		a simple progres bar. Such as multiple colors (based on value),
		tick marks 

	Details
		The progress bar is displayed based on a 0-100% value
		The value is retrieved from the cells text field
		The cells label field can be used to display a label
		When created one of the following values can be passed to 
		the constructor to setup a default display style for the 
		progress bar: 
			UGCT_PROGRESS_NORMAL - single color bar (green)
			UGCT_PROGRESS_ALERT - three color bar (green, yellow, red)
			UGCT_PROGRESS_RAINBOW - a randow colored bar
*************************************************************************/

#pragma once


//style that can be used in the constructor
#define UGCT_PROGRESS_NORMAL	0
#define UGCT_PROGRESS_ALERT		1
#define UGCT_PROGRESS_RAINBOW	255

// defines for direction (see SetDirection)
#define UGCT_PROGRESS_TOP		1		// paint from top to bottom
#define UGCT_PROGRESS_LEFT		2		// paint from left to right (default)
#define UGCT_PROGRESS_RIGHT		3		// paint from right to left
#define UGCT_PROGRESS_BOTTOM	4		// paint from bottom to top

//CUGAdvProgressType declaration
class UG_CLASS_DECL CUGAdvProgressType: public CUGCellType
{
private:

	int m_lbuttondown;
	int m_canAdjust;
	int m_row;
	int m_col;
	RECT m_rect;
	int m_numberSections;
	std::unique_ptr<int[]>	     m_sectionPercent;
	std::unique_ptr<COLORREF[]>  m_sectionColor;
	int m_gradlinePercent;
	int m_direction;
	int m_margin;
	
public:

	CUGAdvProgressType();
	CUGAdvProgressType(int adjust, int gridlines, int type);
	~CUGAdvProgressType();

	int SetCanAdjust(BOOL adjust);
	int CalcPointFromValue(int percent, POINT *point);
	int SetNumberSections(int sections);
	int SetSectionPercent(int section, int percent);
	int SetSectionColor(int section, COLORREF color);
	int SetGraduationLinePercent(int percent);
	int SetDirection(int direction);
	int SetMargin(int margin);
	
	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnMouseMove(int col,long row,POINT *point, UINT flags);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

