#pragma once


// CUserSaveDlg 대화 상자입니다.

class CUserSaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserSaveDlg)

public:
	CUserSaveDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUserSaveDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_USERSAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
