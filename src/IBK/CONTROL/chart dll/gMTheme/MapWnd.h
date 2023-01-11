#if !defined(AFX_MAPWND_H__643FA7A9_A2B2_49F6_9593_DEB3708EE232__INCLUDED_)
#define AFX_MAPWND_H__643FA7A9_A2B2_49F6_9593_DEB3708EE232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "axisMTheme.h"

// MapWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapWnd window

class CMapWnd : public CWnd
{
// Construction
public:
	CMapWnd(CWnd* view, CWnd* parent, int trKey);

// Attributes
public:
	CWnd*		m_view;
	CWnd*		m_parent;
	int		m_trKey;
	CaxisMThemeApp*	m_app;

	CComboBox*	m_pCboTheme;
	class CGrpWnd*	m_pGrpWnd;

	COLORREF	m_clrBk;
	CBrush		m_brBk;
	char*		m_pcTemp;

	CString		m_code;
	CString		m_theme;
	CString		m_codeName;
	bool		m_bReqTheme;
	CStringArray	m_themeCode;
	int			m_iTimerID;

// Operations
public:
	BOOL		Create();
	void		resize();
	void		updatePalette();

	void		setCode(char* code);
	void		requestTheme(CString code);
	void		requestChart(CString themeCode, CString code);
	void		oub(WPARAM wParam, LPARAM lParam);
	void		oubTheme(WPARAM wParam, LPARAM lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapWnd)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapWnd();

	// Generated message map functions
protected:
	afx_msg long OnViewEvent(WPARAM wParam, LPARAM lParam);
	afx_msg long OnUser(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CMapWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPWND_H__643FA7A9_A2B2_49F6_9593_DEB3708EE232__INCLUDED_)
