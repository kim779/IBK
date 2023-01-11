// axisGMTotal.h : main header file for the AXISGMTOTAL DLL
//

#if !defined(AFX_AXISGMTOTAL_H__411C69D1_C010_496A_BF58_2897A46FE855__INCLUDED_)
#define AFX_AXISGMTOTAL_H__411C69D1_C010_496A_BF58_2897A46FE855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../../h/axisfire.h"
#include "../../h/axisvar.h"
#include "../../chart_dll/gMView/defInfo.h"
#include "../../h/axismgrp.h"

enum { imgDate = 1, imgNTime, imgIOpt, imgCtrl, imgCtrl2};

#define COLOR_PAL_BG	PALETTERGB(27, 79, 129)
#define COLOR_PAL_FG	PALETTERGB(255, 145, 2)
#define	COLOR_WHITE		PALETTERGB(255, 255, 255)	

/////////////////////////////////////////////////////////////////////////////
// CAxisGMTotalApp
// See axisGMTotal.cpp for the implementation of this class
//

class CAxisGMTotalApp : public CWinApp
{
public:
	CAxisGMTotalApp();
	~CAxisGMTotalApp();
private:
	CString		m_strRoot;
	CString		m_strUserID;
	CString		m_strUserName;
	CString		m_strTabDir;
	CString		m_strUserDir;
	CString		m_strGexDir;

	CImageList*	m_pImgDate;
	CImageList*	m_pImgNTime;
	CImageList*	m_pImgIOpt;
	CImageList*	m_pImgCtrl;
	CImageList*	m_pImgCtrl2;

public:
	HINSTANCE	m_hGMainLib;
	HINSTANCE	m_hGDlgLib;

public:
	CWnd*	Create(CWnd *pView, CWnd* pParent, struct _param *param, int mType);
	CFont*	GetFont(CWnd *pView, int point, CString name, int bold = 0, bool italic = false);
	CPen*	GetPen(CWnd *pView, int style, int width, COLORREF clr);
	CBrush*	GetBrush(CWnd *pView, COLORREF rColor);

	CImageList*	GetImage(int imgType, CString path);
	CString		GetImagePath(CWnd* pView, CString imgName);
	CImageList*	getImage(CString path, int Width, int Height, UINT flag, COLORREF crMask);

	CString GetRoot()	{ return m_strRoot; }
	CString	GetUID()	{ return m_strUserID; }
	CString	GetUName()	{ return m_strUserName; }
	CString	GetTabPath()	{ return m_strTabDir; }
	CString	GetUserPath()	{ return m_strUserDir; }
	CString	GetGexPath()	{ return m_strGexDir; }

	// 2008.09.26
	struct _param	m_param;
	int	m_mType;
	void	CopyParam(_param *pDest, _param *pSource);
	void	ReMakeFile(CWnd *pParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxisGMTotalApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAxisGMTotalApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISGMTOTAL_H__411C69D1_C010_496A_BF58_2897A46FE855__INCLUDED_)
