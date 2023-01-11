#if !defined(AFX_MAINWND_H__6E8C1897_6BC3_4FED_BD48_874CEE225A78__INCLUDED_)
#define AFX_MAINWND_H__6E8C1897_6BC3_4FED_BD48_874CEE225A78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainWnd.h : header file
//

#include "afxtempl.h"

struct _pninfo	{
	int	whsize;
	WORD	info;
};

/////////////////////////////////////////////////////////////////////////////
// CMainWnd window

class CMainWnd : public CWnd
{
// Construction
public:
	CMainWnd(CWnd *pView, CWnd* pParent, CString name, struct _param* pInfo, int mType);

// Attributes
public:
	int		m_iKey;		// TR Key && 멀티차트 화면의 위치(1~24)
	int		m_iType;	// 멀티차트 화면 type(1~4)
	int		m_iDtUnit;
	int		m_iDtIndex;
	int		m_iMGap;
	int		m_iTGap;
	bool		m_bForeign;
	int		m_AutoUnit;

	CWnd*		m_pwndChart;

	CString		m_strDay;
	CString		m_strCode;
	CString		m_strJName;
	CString		m_strNextCode;	//

	struct _ActiveChartInfo	m_ActiveChartInfo;
	bool		m_bHideMenuBtn;

	CString		m_sParam;

private:
	bool		m_bTransaction;
	bool		m_bTransactionS;
	bool		m_bExtrTr;
	CRect		m_ChartRC;

	int		m_iFPoint;
	int		m_iTRIndex;

	char*		m_pacRegion[MAX_INDEX];	// Map Region Info
	char*		m_pacGraph[MAX_INDEX];	// Map Graph Info
	char*		m_pcGDat;		// graph data info
	char*		m_pcTemp;	// temporary buffer


	CWnd*		m_pwndCtrl;
	CWnd*		m_pwndInput;
	CWnd*		m_pwndView;
	CWnd*		m_pwndParent;

	CFont*		m_pFont;

	CString		m_strDllName;
	CString		m_strIName;
	CString		m_strFName;
	CString		m_strEnvPath;	
	CString		m_strGrpPath;
	CString		m_strDatPath;


	CAxisGMTotalApp*	m_pApp;

	// file
	_envInfo*	m_pEnvInfo;	// Environment info

	CArray<char*, char*>	m_arData;
	CArray<int, int>	m_arLen;
	struct _trData		m_TrData;
	CMap <int, int, struct _pninfo *, struct _pninfo *> m_mapPanel;


public:
	class CExtraMsg*	m_pExtraMsg;
	bool	m_bActive;

	int	GetToken(char *pData, char token[]);
	void CheckUnit(int unit);
	void OnActiveEvent(bool bNotice);	// App->MainWnd
	void OnInActiveEvent();				// MGrpView->MainWnd

private:
	// components
	CWnd*	CreateWnd(int ctrlID, CWnd* pWnd);
	void	ResizeWnd(CRect wRC);

	int	WhichFOCode(LPCTSTR code);
	void	DelPanels();

	void	InitPnInfo(struct _panel *panel);
	void	CreatePn();
	struct _pninfo*	GetPnInfo(int localID);
	int	GetPnSize(int ctrlID);
	BOOL	IsAidAddable(LPARAM lParam);
	BOOL	MainChartIsVarType();
	
	// file IO
	bool	ReadEnv();
	bool	ReadGrp();
	bool	ReadData();
	bool	WriteEnv();
	void	WriteGrp();
	void	WriteDat();	
	void	ModifyEnv();
	bool	ReMakeFile();

	void	SavePanel(struct _panel *panel);

	char*	GetMapInfo(int ikey = -1);
	char*	GetDat();
	bool	GetGrpFromDat(char *info);
	bool	SetGrpAtDat(char *info);

	// i/o
	void	SendRequest();
	void	SendRequest2();
	void	SendRequestS();
	void	SendNextTR();
	void	EnvProc();
	bool	CallEnvDlg(char *pInfo, bool bTotal);
	char*	CallMapDlg(char *pInfo);
	bool	CallStandardIndc(int kind);
	bool	CallToolDlg(char *pInfo);
	void	InitGraph();
	void	SyncMainChart(char *pInfo);
	void	SyncMap(char *pScreen);
	void	IndexChange(int index);

	LRESULT	Oub(WPARAM wParam, LPARAM lParam);
	LRESULT OnMultiEvent(WPARAM wParam, LPARAM lParam);
#ifdef _DEBUG
void CMainWnd::WriteFile(CString strData);
#endif

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWnd)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMainWnd)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	afx_msg LRESULT	OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnViewEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChartEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInputEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSiseEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCtrlEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnToolEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTableEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWND_H__6E8C1897_6BC3_4FED_BD48_874CEE225A78__INCLUDED_)
