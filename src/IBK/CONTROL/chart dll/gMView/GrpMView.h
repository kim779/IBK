#if !defined(AFX_GRPMVIEW_H__70D008A9_D753_4C0E_8FC4_F1B6CDF60CD5__INCLUDED_)
#define AFX_GRPMVIEW_H__70D008A9_D753_4C0E_8FC4_F1B6CDF60CD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrpMView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrpMView window

#include <afxtempl.h>

class CGrpMView : public CWnd
{
// Construction
public:
	CGrpMView(CWnd* pwndView, char* pcDllName);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrpMView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGrpMView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGrpMView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT	OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnViewEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChartEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInputEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCtrlEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCfgEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFromMain(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnViewSendTR(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	char		m_acDllName[9];
	CRect		m_rcOrgChart;
	CRect		m_rcChart;

	CAxisGMViewApp*	m_pApp;

	_DummyGraph	m_DummyGraph;
	_MultiChart	*m_pMultiChartInfo;
	bool		m_bAutotran;
	bool		m_bTransaction;
	int			m_iAutoTRCnt;
	bool		m_bDominoExist;
	CFont*		m_pFont;
	int			m_idUnit;
	int			m_timerID;

	CWnd*		m_pwndView;	// Parent
	CWnd*		m_pwndInput;
	CWnd*		m_pwndCtrl;
	CMap	<int, int, CWnd *, CWnd*> m_mapChart;
	CStringArray	m_arHistory;

	CWnd*		m_pActiveChart;

	class CConfigBarMulti* m_pCfg;
	CWnd* m_trSender;				// control TR Sender

	void InitView();
	void CreateWnd();
	void CreateChart(bool bFirst);
	CWnd* CreateMTotal(int Key);
	void ResizeWnd(CRect wRC);
	void ResizeChart();
	bool GetControlShow(int iID);
	bool ControlShow(int iID, bool bShow);
	char*	OpenCodeDlg(int kind, UINT lParam);
	void	OnDrop(WPARAM wParam, LPARAM lParam);
	LRESULT	Oub(WPARAM wParam, LPARAM lParam);
	void	SetParam(struct _param *param, CString fName, int key);
	void	Stay(DWORD dwGap);
public:
	void SendTR(CWnd* sender, CString strCode, LPCTSTR strData, int nSize, char stat = NULL);

	LRESULT OnNotifyEvent(WPARAM wParam, LPARAM lParam);
	LRESULT OnMultiEvent(WPARAM wParam, LPARAM lParam);
	void MultiAidAdd(LPARAM lParam);
	void MultiAidDel(LPARAM lParam);
	void MultiIndex(LPARAM lParam);
	void MultiMain(LPARAM lParam);
	void MultiCode(LPARAM lParam);
	void PluralMultiCode(LPARAM lParam);
	void MultiGigan(LPARAM lParam);
	void MultiChkMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void MultiAllMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void MultiEnableChart(bool bEnable);
	void MultiGigan2(LPARAM lParam);
	void MultiMatrix(LPARAM lParam);
	void MultiMatrix2(LPARAM lParam);
	void MultiCheck(LPARAM lParam);
	void MultiFocus(LPARAM lParam);
	void MultiToday(LPARAM lParam);
	int MultiOub(WPARAM wParam, LPARAM lParam);
	void MultiAlert(WPARAM wParam, LPARAM lParam);
	int  GetRotChartCnt();
	void InitMultiCode();
	void InitMConfig();
	void ClearChart();
	void SaveMultiInfo();
	void SaveChart();
	void CheckActiveChart();
	int ReadHistory();
	void DefaultMap(int x, int y, CString curCode = _T(""));
	char* FindIndexCode(char*);
	void OnSetMultiCode(LPARAM lParam);
	void OnAutoTran(BOOL bSet);
	void OnAutoComplete(LPARAM lParam);
	void OnInitAllChart();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPMVIEW_H__70D008A9_D753_4C0E_8FC4_F1B6CDF60CD5__INCLUDED_)
