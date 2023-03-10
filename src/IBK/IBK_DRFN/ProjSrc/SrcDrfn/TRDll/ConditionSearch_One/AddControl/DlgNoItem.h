#pragma once


// CDlgNoItem 대화 상자입니다.
#include "../resource.h"
class CDlgNoItem : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoItem)

public:
	CDlgNoItem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgNoItem();
	
	CFont	m_font;
	CStatic m_staticText;
	CRect	m_reParent;
	

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NO_ITEM };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
