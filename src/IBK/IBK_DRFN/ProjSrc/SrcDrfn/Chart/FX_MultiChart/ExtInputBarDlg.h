#if !defined(AFX_EXTINPUTBARDLG_H__CEE4266F_0275_4708_8E48_E841F6293DB0__INCLUDED_)
#define AFX_EXTINPUTBARDLG_H__CEE4266F_0275_4708_8E48_E841F6293DB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtInputBarDlg.h : header file
//
#include "RscDlg.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CExtInputBarDlg dialog
//#include "./control/xSkinButton.h"
#include "./control/EditUsr.h"

#include "MatrixSelecterDlg.h"
#include "../../inc/ExOCXDLL.h"
//#include "../../COMMON_BASE/baseInfo/BaseInfo.h" //2005.06.01 add by sy, nam
//#include "../../../DrMLib/DrMiddleLib.h"
#include "./define/ChartMsgDef.h"				// 복수종목 - ojtaso (20070223)
#include "../../../SrcSite/include/AccountCtrl.h"


//컬러테이블을 쓸경우 /

//이미지 리스트를 쓸 경우 
#include "../chart_common/ILButton.h"


class CStdDialog;
class CExtInputBarDlg : public CRscDlg
{

// Construction
public:
	BOOL m_bReplayMode ;
	BOOL GetTimeSyncFlag();
	void SetTimeSyncFlag(BOOL bCheck);

	CImageList* m_pIL_W58H20;
//@유진삭제 CImageList* m_pIL_W34H20;
	CImageList* m_pIL_W46H20;
	CImageList* m_pIL_W20H20;
	CImageList* m_pIL_W20H20_Tool;
//@유진삭제 CImageList* m_pIL_W58H19;

//	CDrMLib_CBaseInfo2*	m_pCommonBaseInfo;
	CString		m_strCode;
	
	//------------------------------------------------------------------------
	//Author	:	Sang Yun Nam
	//Date		:	2005.08.18
	long OpenMap(LPCTSTR szMapName);
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	//Author	:	Sang Yun Nam
	//Date		:	2005.08.10
	//Color Table 적용시 호출 - 차트는 ColorTable 안 쓴다.
	void ChangeButtonColor();
	//------------------------------------------------------------------------

	BOOL	m_bEndDate;
	CString m_strStartDate, m_strEndDate;
	CExtInputBarDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_strCfgFile;

	enum { SCROLL_STOP, SCROLL_LEFT, SCROLL_RIGHT };
	int	m_nScrollState;

	int		m_nMarketType;
	void	SetMarketType(int nMarketType);

	// m_nYUnintType 변수에 현재 차트 Y축 눈금 단위 구분값을 저장한다.
	enum {WON_TICK, PERCENT_TICK, DOLLAR_TICK }; //원 단위, 백분율 단위, 달러 단위
	UINT m_nYUnitType; 
	//현재 선택된 차트의 타입을 저장한다.
	char m_chType; //2005. 05. 27 add by sy, nam
private:
	CDateTimeCtrl	m_datePicker;

	//<<< 2009124 by kmlee for account combo
	//HWND	m_hAccountCombo;
	CAccountCtrl*	m_pAccountCtrl;		// 계좌컨트롤	
	//>>>
	CString		m_strAccountNo;
	CString		m_strAccountName;
	//CString		m_strPassWord;

//	CStringArray	m_arrAccPW;

public:
// Dialog Data
	//{{AFX_DATA(CExtInputBarDlg)
	enum { IDD = IDD_EXTINPUTBAR };
	CEditUsr	m_edAccPW;
	CButton		m_chkOrderLine;
	CILButton	m_btScrollPre;
	CILButton	m_btScrollNext;
	CILButton	m_btScrollStop;
	CILButton	m_btnGwanSim;
	CILButton	m_btSub2;
	CILButton	m_btEtcMenu;
	CILButton 	m_btInitial;
	CILButton	m_btnPeriod;
	CILButton	m_chkUpdateIndex;
	CButton		m_chkEndSave;
	CILButton	m_btnBuyScreen;
	CILButton	m_btnSellScreen;
	CILButton	m_btnStartDate;
	CILButton	m_btnEndDate;
	CILButton	m_btFixPeriod;
	CILButton	m_btST;
	CILButton	m_btHist;
	CILButton	m_btChartGuideLine;
	CILButton	m_btAnalysisPattern;
	CILButton	m_btExPrev;
	CILButton	m_btExNext;
	CILButton	m_btShowMatrix;
	CILButton	m_btSetEnvir;
	CILButton	m_chkShowScale;
	CILButton	m_btAddIndex;
	CILButton	m_chkJongmokLink;
	CILButton	m_btPrint;
	CILButton	m_btLoad;
	CILButton	m_btSave;
	CILButton	m_chkTypeLink;
	CILButton	m_btInitSplit;
	CStatic		m_stBy;
	CStatic		m_stSetMatrix;
	CILButton	m_btIndex;
	CButton		m_chkFixPeriod;
	BOOL		m_bChkRevised;
	CILButton	m_btYUnit;
	CExComboBox	m_cmbScrollSpeed;
	CButton		m_chkQueryOpt;
	CILButton	m_btOrder;
	CString		m_strPassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtInputBarDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
public:
	void EnableWindowExtBar(BOOL bEnable = TRUE);
	void ChangeStatusDateControl(int nDataType);
	void SetCheckRevised(BOOL bRevised);
	void	SetpChartMng(CWnd *pWnd) { m_pChartMng = pWnd; }
	void	SetpLeftBar(CWnd *pWnd) { m_pLeftBar = pWnd; }
	// 복수종목에서 선택된 차트 정보 표시 : 복수종목 - ojtaso (20070223)
	void	InitChartMulitItem(ST_SELCHART* pSelChart);

	int GetQueryOpt();
	void EnableQueryOpt(BOOL bEnable);
	void ChangeSkinColor();
	void SaveExtInputBar();

	//<<< 20091221 by kmlee
	BOOL GetChkOrder ();
	//>>>

	void GetAccountInfo(CString& strAccNo, CString& strAccName, CString& strAccPW);
	void SendAccountToPlatform(CString strAccountNo, CString strPassWord);
	void InitAccountCtrl(WPARAM wParam, LPARAM lParam);

	// 2011.01.31 by SYS >> 분차트 YYYY(년) 추가 및 분석툴 공유 기능 추가
	void ChangeAnalToolFile(BOOL bSave);

private:
	int	m_nDataType;
	CMatrixSelecterDlg m_MatrixSelecter;
	CBrush	m_brBkColor;
	COLORREF m_crBk;
	CString m_strImageChartPath;
	long m_lRows;
	long m_lCols;
	CWnd *m_pChartMng;
	CWnd *m_pLeftBar;
	void SetExt(int nAct);
	INT		m_nSave;	// 0: disable, 1: true, 2: false
	enum	{SAVE_DISABLE, SAVE_TRUE, SAVE_FALSE};
	BOOL	m_bNormalizedMinuteTimeRule;
	BOOL	m_bUseNormalizedMinuteTimeRule;
	
	// 분석툴 개별 저장 - ojtaso (20080723)
	BOOL	m_bChkSaveAnalTool;

	// 2011.01.12 by SYS >> 분차트 YYYY(년) 추가 및 분석툴 공유 기능 추가
	BOOL	m_bChkShareAnalTool;
	// 2011.01.12 by SYS <<


	INT		m_nDragModeType; // DragModeType  0: CrossLine, 1:Drag&Drop Zooming, 2:Period Analysis
	BOOL	m_bChkPeriod;
	BOOL	m_bChkSaveJipyoOneFile;
	BOOL	m_bChkRegGwansimUp;

	BOOL	m_bChangeTool;	//S01 2006.09.07	{{T: Tool,	F:연동}}
	void	ClearLink();
// Implementation 
protected:
//001 2006.06.22 {{
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	//EUGENE컨트롤의 이벤트를 받는다
//001 2006.06.22 }}
	// Generated message map functions
	//{{AFX_MSG(CExtInputBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtScrollPre();
	afx_msg void OnBtScrollNext();
	afx_msg void OnBtScrollStop();
	afx_msg void OnBtaddindex();
	afx_msg void OnBtinitsplit();
	afx_msg void OnBtindex();
	afx_msg void OnChkjongmoklink();
	afx_msg void OnChktypelink();
	afx_msg void OnBtload();
	afx_msg void OnBtsave();
	afx_msg void OnBtinitial();
	afx_msg void OnDestroy();
	afx_msg void OnChkshowscale();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtprint();
	afx_msg void OnBtsetenvir();
	afx_msg void OnBtshowmatrix();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtexnext();
	afx_msg void OnBtexprev();
	afx_msg void OnBtanalysispattern();
	afx_msg void OnBtchartguideline();
	afx_msg void OnBthist();
	afx_msg void OnBtst();
	afx_msg void OnBtnSdate();
	afx_msg void OnBtnEdate();
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSellscr();
	afx_msg void OnBtnBuyscr();
	afx_msg void OnBtfixperiod();
	afx_msg void OnChkEndsave();
	afx_msg void OnChkupdateindex();
	afx_msg void OnBtnAnalizePeriod();
	afx_msg void OnChkRevised();
	afx_msg void OnBtnPeriod();
	afx_msg void OnBtetcmenu();
	afx_msg void OnBtSub2();
	afx_msg void OnBtnChangeunit();
	afx_msg void OnChkfixperiod();
	afx_msg void OnBtnGwansim();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSelchangeCmbScrollSpeed();
	afx_msg void OnChkQueryOpt();
	afx_msg void OnBtOrder();
	//<<< 20091111 by kmlee
	afx_msg void OnCheckOrderLink();
	//>>>
	afx_msg void OnSelendokAccCtrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTINPUTBARDLG_H__CEE4266F_0275_4708_8E48_E841F6293DB0__INCLUDED_)
