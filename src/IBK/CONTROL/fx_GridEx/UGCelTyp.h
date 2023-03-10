/*************************************************************************
				Class Declaration : CUGCellType
**************************************************************************
	Source file : UGCelTyp.cpp
	Header file : UGCelTyp.h
	Copyright ? Dundas Software Ltd. 1994 - 2002, All Rights Reserved

	Purpose
		The CUGCellType class is the default (normal) cell type
		its main function is to provide the grid with ability
		to draw cell value.

		The CUGCellType is also the class that all custom
		cell types have to derive from.

	Details
		To set this cell type to a cell you need to call SetCellType
		with UGCT_NORMAL as parameter.  This cell type is default.

		The normal cell type also provides 3 cell type extensions:
			UGCT_NORMALMULTILINE
				this style is used when word wrapping
				and/or multiple lines are needed within
				one cell
			UGCT_NORMALELLIPSIS
				this style shows three periods at the
				right of the cell if the text is too wide.
			UGCT_NORMALLABELTEXT
				this style causes the cells label property
				to be drawn instead of its text property
*************************************************************************/
#pragma once

// MACROs used in printing bitmap
#define IS_WIN30_DIB(lpbi) ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect) ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect) ((lpRect)->bottom - (lpRect)->top)
// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.
#ifndef WIDTHBYTES
#define WIDTHBYTES(bits) ((unsigned)((bits + 31) & (~31)) / 8) /* ULONG aligned ! */
#endif

class UG_CLASS_DECL CUGCellType : public CObject
{

protected:
	BOOL m_canTextEdit{};	// allow inline editing
	BOOL m_drawLabelText{}; // draw the label instead of the string
	BOOL m_canOverLap{};	// can the cell overlap over cells
	double m_dScaleFactor{};

	CUGCtrl* m_ctrl{}; // pointer to the main class

	friend CUGCtrl;

	int m_ID{}; // ID which is the index in the celltype list
		    // once it is registered (see CUGCtrl::AddCellType)

protected:
	// Functions used in printing bitmap
	HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);
	DWORD PaletteSize(LPSTR lpDIB);
	WORD DIBNumColors(LPSTR lpDIB);

public:
	// general purpose routines
	virtual int DrawBitmap(CDC* dc, CBitmap* bitmap, RECT* rect, COLORREF backcolor);
	virtual void DrawBorder(CDC* dc, RECT* rect, RECT* rectout, CUGCell* cell);
	virtual void DrawText(CDC* dc, RECT* rect, int offset, int col, long row, CUGCell* cell, int selected, int current);
	virtual void DrawBackground(CDC* dc, RECT* rect, COLORREF backcolor);
	virtual int GetCellOverlapInfo(CDC* dc, int col, long row, int* overlapCol, CUGCell* cell);

public:
	CUGCellType();
	virtual ~CUGCellType();

	inline CUGCtrl* GetGridCtrl() const { return m_ctrl; }

	// cell type information
	int GetID();
	void SetID(int ID);

	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();

	// text editing functions
	BOOL CanTextEdit();
	int SetTextEditMode(int mode); // TRUE and FALSE

	// cell overlapping
	BOOL CanOverLap(CUGCell* cell);

	// drawing setup functions
	int DrawTextOrLabel(int mode); // 0-text 1-label
	int SetDrawScale(float scale);

	// virtual functions
	virtual int GetEditArea(RECT* rect);

	virtual int SetOption(long option, long param);
	virtual int GetOption(long option, long* param);

	virtual BOOL OnLClicked(int col, long row, int updn, RECT* rect, POINT* point);
	virtual BOOL OnRClicked(int col, long row, int updn, RECT* rect, POINT* point);
	virtual BOOL OnDClicked(int col, long row, RECT* rect, POINT* point);

	virtual BOOL OnKeyDown(int col, long row, UINT* vcKey);
	virtual BOOL OnKeyUp(int col, long row, UINT* vcKey);
	virtual BOOL OnCharDown(int col, long row, UINT* vcKey);

	virtual BOOL OnMouseMove(int col, long row, POINT* point, UINT nFlags);

	virtual void OnDraw(CDC* dc, RECT* rect, int col, long row, CUGCell* cell, int selected, int current);
	virtual BOOL OnDrawFocusRect(CDC* dc, RECT* rect, int col, int row);

#ifdef UG_ENABLE_PRINTING
	virtual void OnDrawPrint(CDC* dc, RECT* rect, int col, long row, CUGCell* cell, int selected, int current);
	virtual void OnPrint(CDC* dc, RECT* rect, int col, long row, CUGCell* cell);
#endif

	virtual void OnSetFocus(int col, long row, CUGCell* cell);
	virtual void OnKillFocus(int col, long row, CUGCell* cell);

	virtual void OnChangedCellWidth(int col, long row, int* width);
	virtual void OnChangingCellWidth(int col, long row, int* width);
	virtual void OnChangedCellHeight(int col, long row, int* height);
	virtual void OnChangingCellHeight(int col, long row, int* height);

	virtual void GetBestSize(CDC* dc, CSize* size, CUGCell* cell);

	virtual void OnScrolled(int col, long row, CUGCell* cell);
	virtual int OnSystemChange();

	virtual long OnMessage(LPARAM lParam);

	virtual int OnCellTypeNotify(long ID, int col, long row, long msg, long param);
};
