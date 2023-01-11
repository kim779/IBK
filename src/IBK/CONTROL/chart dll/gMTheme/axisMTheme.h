// axisMTheme.h : main header file for the axisMTheme DLL
//

#if !defined(AFX_axisMTheme_H__38EB7F21_A442_4742_AF7D_3FF4E0412FDB__INCLUDED_)
#define AFX_axisMTheme_H__38EB7F21_A442_4742_AF7D_3FF4E0412FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../../h/axisfire.h"
#include "../../h/axisvar.h"
#include "../../h/axiscgrp.h"
#include "../../h/axisgenv.h"

#define UNUSED_VALUE	-9999999.999

struct _multi_lineD
{
	char	index[14];
	char	data[1][10];
};

struct _multi_line
{
	struct _cgIndex	index;
	double	data[1];
};

/////////////////////////////////////////////////////////////////////////////
// CaxisMThemeApp
// See axisMTheme.cpp for the implementation of this class
//

class CaxisMThemeApp : public CWinApp
{
public:
	CaxisMThemeApp();

public:
	CWnd*		m_view;
	CString		m_sRoot;
	CString		m_sUser;
	CFont*		m_font;

public:
	CBitmap*	GetBitmap(CWnd* pView, CString path);
	COLORREF	GetColor(CWnd* pView, int index);
	CString		Variant(CWnd* pView, int comm, CString data);

	CImageList*	getImage(CString path, int Width, int Height, UINT flag, COLORREF crMask);
	CFont*		GetFont(CWnd* pView, int point, CString name = "±¼¸²", int bold = 0, bool italic = false);
	CPen*		GetPen(CWnd* pView, int style, int width, COLORREF clr);
	CBrush*		GetBrush(CWnd* pView, COLORREF rColor);
	CImageList*	GetImage(CWnd* pView, CString path, int Width, int Height, UINT flag, COLORREF crMask);

	void		Init(CWnd* view);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CaxisMThemeApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CaxisMThemeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_axisMTheme_H__38EB7F21_A442_4742_AF7D_3FF4E0412FDB__INCLUDED_)
