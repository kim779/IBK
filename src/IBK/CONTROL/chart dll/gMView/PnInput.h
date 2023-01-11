#if !defined(AFX_PNINPUT_H__6860AB15_72AA_498F_AAC3_3405A7D60B4E__INCLUDED_)
#define AFX_PNINPUT_H__6860AB15_72AA_498F_AAC3_3405A7D60B4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PnInput.h : header file
//
#include "PnBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPnInput window

class CPnInput : public CPnBaseWnd
{
// Construction
public:
	CPnInput(CWnd *pwndView, CWnd* pwndGView, CFont* pFont, int ctrlID, char* info);

// Attributes
public:


private:
	bool	m_bInitResize;
	BOOL	m_bMouseIN;
	int		m_BtnOrgStatus;

	int	m_mType;
	int	m_iDtUnit;
	int	m_iDtIndex;
	int	m_iOrgUnit;
	int	m_iMGap;	// 碟除問
	int	m_iTGap;	// す除問
	bool	m_bCheckOn;

	int		m_iTimerID;
	CRect		m_rcIndex;
	CPoint		m_ptCodeBtn;

	CSize		m_szHangul;
	CSize		m_szNumeric;
	CSize		m_szAlphabet;

	CString		m_strTrigger;
	CString		m_strValidCode;
	CString		m_strMultiCode;
	CString		m_strTemp;

	CFont*		m_pfontButton;

	CImageList*	m_pCfgImage;
	CImageList*	m_pNTimeImage;
	CImageList*	m_pNBtnImage;
	CImageList*	m_pCodeImage;
	CImageList* m_pIUnitImage;

	CImageList*	m_p2NameImgDN;
	CImageList*	m_p2NameImgMV;
	CImageList*	m_p2NameImgUP;

	CImageList*	m_p3NameImgDN;
	CImageList*	m_p3NameImgMV;
	CImageList*	m_p3NameImgUP;

	CImageList*	m_p4NameImgDN;
	CImageList*	m_p4NameImgMV;
	CImageList*	m_p4NameImgUP;

	CImageList* m_pIMatrix;
	CImageList* m_pIMerge;
	CImageList* m_pICheckOn;
	CImageList* m_pICheckOff;

	class CCodeCtrl*	m_pCodeCB;
	class CPnWndCombo*	m_pGapCB;
	class CPnWndCombo*	m_pGiganCB;
	class CPnToolTip*	m_pToolTip;
	class CCheckBox*	m_pchbToday;

// Operations
public:


private:
	void	Draw(CDC *pDC);
	void	CreateWndCtrl();
	void	ArrangeCtrl(CRect rectC, bool bChgIndex = true);
	void	DrawButton(CDC* pDC, struct _comp* comp);
	void	DrawButton2(CDC* pDC, struct _comp* comp);
	void	DrawNameButton(CDC* pDC, struct _comp* comp);
	void	DrawDisableButton(CDC *pDC, CRect rc);
	bool	IsDisableButton(int id);
	void	SetInfo(CRect wRC);

	void	ChangeUnit(int unit, bool bTran = true);
	void	ChangeIndex(int index, bool bChgGap = true, bool bRedraw = true, bool bMessage = true);
	void	ChangeGap(int gap = 0, bool bOnlyChange = false);
	bool	CheckCode();
	void	ProcTab(int id);
	void	OpenCodeDialog();
	void	ReadEnv(struct _MultiChart *MultiChart);
	void	TodayDisplay();
	void	GetDominoCode(char *dCode, CString &domino, bool bTrigger);
	void	SetTriggerCode();
	int	WhichFOCode(LPCTSTR code);
	CString	GetHistory(int unit);
	void	LButtonUp(CPoint point);

	LRESULT OnMultiEvent(WPARAM wParam, LPARAM lParam);
	void	NotifyToday(bool bSet);
	void	NotifyIndexChange();
	void	NotifyCodeChange();
	void	NotifyMultiCodeChange();
	void	NotifyGiganChange(int iGigan);
	void	NotifyGiganChange2(int *pGigan);
	void	NotifyMatrixChange(LPARAM lParam);
	void	NotifyMatrixChange2(char *pMatrix);
	void	NotifySelect(bool bSelect);
	void	NotifyFocus();
	void	NotifyOrder(int mIndex, _ActiveChartInfo *pActiveChartInfo);
	void	NotifyInit();


public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPnInput)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPnInput();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPnInput)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT	OnInputEvent(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseLeave(UINT nFlags, CPoint point);
	afx_msg void OnClickedToday();
	afx_msg LRESULT OnTableMake(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCellMerge(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


//** macho add
private:
	BOOL	m_lock;
	CString m_userPath;
	CString GetCurrentUnit();
	void	DrawUnitButton(CDC* dc, CRect rc);
	void	OnChangeUnit();
	CString GetIndexCode(int indexCode);
	void	ChangeUnitAndCode(LPCTSTR);
	CString GetSiseName();
	int		FindUnit(int index);
	void	CheckComboSel();

	void SetIndexCode(CString& code);
	void SetIndexTrigger(CString& domino);
	void SetIndexKind(LPCTSTR code);
private:
	CAxMTableCtrl		*m_table;
	CAxMTableMergeCtrl  *m_merge;

	void OnButtonTableClick(_comp* comp);
	void OnButtonCellClick(_comp* comp);
	void OnButtonCheckClick();
	void OnFocusClick();
	void OnButtonUnitClick(_comp* comp);
	void OnMultiGiganClick();
	void OnOrderClick(_comp *comp);
	void OnChangeChart();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PNINPUT_H__6860AB15_72AA_498F_AAC3_3405A7D60B4E__INCLUDED_)
