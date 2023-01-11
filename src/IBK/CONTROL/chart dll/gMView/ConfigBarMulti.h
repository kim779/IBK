#if !defined(AFX_CONFIGBARMULTI_H__D3CC6EEA_4F15_4FD8_9833_817074A1736C__INCLUDED_)
#define AFX_CONFIGBARMULTI_H__D3CC6EEA_4F15_4FD8_9833_817074A1736C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigBarMulti.h : header file
//
#include "../AxMCtrl/ConfigBar_Pru.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigBarMulti window

class CConfigBarMulti : public CConfigBarPru
{
// Construction
public:
	CConfigBarMulti(CWnd* view, CWnd* parent, CFont* font, LPCTSTR info);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigBarMulti)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigBarMulti();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigBarMulti)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	virtual LRESULT OnAxAutoClick(WPARAM, LPARAM);
	virtual LRESULT OnAxManualClick(WPARAM, LPARAM);
	virtual LRESULT OnAxPlayButtonClick(WPARAM, LPARAM);
	virtual LRESULT OnAxReversePlayButtonClick(WPARAM, LPARAM);
	virtual LRESULT OnAxFFButtonClick(WPARAM, LPARAM);
	virtual LRESULT OnAxListKindItemClick(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	int	m_multiCount;
	BOOL m_autoPlay;
	void InitArray();
	CWordArray m_arrSel;
	CStringArray m_codes;
	
	void UnselectListItem();
	BOOL SelectNextMultiItem();
	BOOL SelectPrevMultiItem();
protected:
	UINT	m_lastTimerID;
	virtual void StopAutoPlay();
	virtual void StartAutoPlay();
public:
	CString FindIndexCode(LPSTR code);
	void 	ContinueAutoPlay();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGBARMULTI_H__D3CC6EEA_4F15_4FD8_9833_817074A1736C__INCLUDED_)
