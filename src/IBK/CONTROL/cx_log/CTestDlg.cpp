// CTestDlg.cpp: 구현 파일
//
#include "cx_test.h"
#include "StdAfx.h"
#include "CTestDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CTestDlg 대화 상자

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기
