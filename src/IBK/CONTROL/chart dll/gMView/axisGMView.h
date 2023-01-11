// axisGMView.h : main header file for the AXISGMVIEW DLL
//

#if !defined(AFX_AXISGMVIEW_H__F92D6AFD_ADC0_4026_BBF7_6AB079A13F63__INCLUDED_)
#define AFX_AXISGMVIEW_H__F92D6AFD_ADC0_4026_BBF7_6AB079A13F63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../../h/axisgenv.h"
#include "../../h/axisgwin.h"
#include "../../h/axisvar.h"
#include "../../h/axisfire.h"
#include "../../h/axismgrp.h"
#include "defInfo.h"

#include <afxtempl.h>

#define WM_AXUSER		WM_USER+10000
#define	WM_AXDROPITEM	WM_AXUSER+1
#define	WM_AXSETCTRL	WM_AXUSER+2
#define	WM_AXGETCTRL	WM_AXUSER+3
#define	WM_AXDELKIND	WM_AXUSER+4
#define	WM_AXRELOAD		WM_AXUSER+5

#define	WM_AXRMOUSE		WM_AXUSER+6
#define	WM_AXADDUSER	WM_AXUSER+7
#define	WM_AXDELUSER	WM_AXUSER+8
#define	WM_AXGETUGRP	WM_AXUSER+9
#define	WM_AXADDGRP		WM_AXUSER+10

#define WM_AXITEMCLICK  WM_AXUSER+11
#define MAX_DATA_COUNT	500

enum { imgDate = 1, imgTime, imgNTime, imgNBtn, imgCode, imgIEtc, imgIOpt, imgICfg, imgTool, imgTool2, imgCtrl, imgCtrl2, 
		/** macho add **/imgIUnit, imgITable, imgICell, imgICheck };

#define COLOR_PAL_BG	PALETTERGB(27, 79, 129)
#define COLOR_PAL_FG	PALETTERGB(255, 145, 2)
#define	COLOR_WHITE		PALETTERGB(255, 255, 255)	

		
struct _DummyGraph
{
	struct _graph	graph;
	char			ulist[MAX_UGRP];	// ¡Ò∞‹√£±‚
};
#define	SZ_DUMMYGRAPH	sizeof(struct _DummyGraph)

/////////////////////////////////////////////////////////////////////////////
// CAxisGMViewApp
// See axisGMView.cpp for the implementation of this class
//

class CAxisGMViewApp : public CWinApp
{
public:
	CAxisGMViewApp();
	virtual ~CAxisGMViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxisGMViewApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAxisGMViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CWnd*	Create(CWnd* pParent, char* pcDllName);
	CString GetRoot()		const { return m_root; }
	CString	GetUID()		const { return m_uid; }
	CString	GetUName()		const { return m_uname; }
	CString	GetTabPath()	const { return m_tabDir; }
	CString	GetUserPath()	const { return m_userDir; }
	CString	GetGexPath()	const { return m_gexDir; }
	CString GetImgPath()	const { return m_imgDir; }
	CFont*	GetFont(CWnd *pView, int point, CString name, int bold = 0, bool italic = false);
	CPen*	GetPen(CWnd *pView, int style, int width, COLORREF clr);
	CBrush*	GetBrush(CWnd *pView, COLORREF rColor);

	bool	ReadFile(CWnd *pView, CString path, char *pBytes, int nBytes);
	bool	WriteFile(CWnd *pView, CString path, char *pBytes, int nBytes);
	CString		GetImagePath(CWnd* pwndView, CString imgName);
	CImageList*	GetImage(int imgType, CString path);
	CImageList*	GetImage(CString path, int Width, int Height, UINT flag, COLORREF crMask);

private:
	CString		m_root;
	CString		m_uid;
	CString		m_uname;
	CString		m_tabDir;
	CString		m_userDir;
	CString		m_gexDir;
	CString		m_imgDir;

	CImageList	*m_pImgDate;
	CImageList	*m_pImgTime;
	CImageList	*m_pImgNTime;
	CImageList	*m_pImgNBtn;
	CImageList	*m_pImgCode;
	CImageList	*m_pImgIEtc;
	CImageList	*m_pImgIOpt;
	CImageList	*m_pImgICfg;
	CImageList	*m_pImgCtrl;
	CImageList	*m_pImgCtrl2;
	CImageList	*m_pImgTool;
	CImageList	*m_pImgTool2;
	CImageList	*m_pImgUnit;

public:
	HINSTANCE	m_hiGMTotalLib;
	HINSTANCE	m_hiGMThemeLib;
	HINSTANCE	m_hiGMInvestLib;

public:
	UINT	MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = COMPANYNAME, UINT button = MB_OK | MB_ICONINFORMATION);
	UINT    MessageBoxF(LPCTSTR lpszFormat, ...);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISGMVIEW_H__F92D6AFD_ADC0_4026_BBF7_6AB079A13F63__INCLUDED_)
