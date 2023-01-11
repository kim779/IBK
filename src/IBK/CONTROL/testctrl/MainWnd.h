#if !defined(AFX_MAINWND_H__012DD35A_3186_4393_8080_BDC091E08DA2__INCLUDED_)
#define AFX_MAINWND_H__012DD35A_3186_4393_8080_BDC091E08DA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainWnd window
struct	_uinfo {
	char	gubn[2];	// ��������
				// "MY" : ��������
				// "UL" : ����� ������ ��� 
				// "UD" : ����� ������
	char	dirt[1];	// ���۹��� 'U' : pc==>host, 'D' : host==>pc, 'X' : host==>pc (conversion), 'R' : ����ȸ
	char	cont[1];	// ���ӱ��� 'F':First, 'M':Middle, 'L':First&Last, 'C':Cancel
	char	name[80];	// file name
	char	nblc[5];	// ������, ����ũ��(max:64k)
	char	retc[1];	// return value 'O':���� 'E':����
	char	emsg[40];	// error message
};

struct	_ginfo {
	char	gnox[2];	// group number
	char	gnam[20];	// group name
	char	jrec[4];	// _jinfo count
	//	char	jptr[1];	// _jinfo pointer
};

struct	_jinfo {
	char	gubn[1];	// ���񱸺�	0:none, 1:����, 2:����, 3:�ɼ�, 4:�����ֽĿɼ�, 5:����
	char	code[12];	// �����ڵ�
	char	xprc[10];	// �����ܰ�
	char	xnum[10];	// ��������
};

struct	_updn {
	_uinfo	uinfo;
	_ginfo	ginfo;
};

const int sz_uinfo   = sizeof(struct _uinfo);
const int sz_ginfo   = sizeof(struct _ginfo);
const int sz_jinfo   = sizeof(struct _jinfo);
const int sz_updn    = sizeof(struct _updn);


class CParam
{
public:
	int			key;			// screen key
	CString		name;			// control symbol name
	CRect		rect;			// control rect
	CString		fonts;			// font name
	int			point;			// font point
	int			style;			// font style
	DWORD		tRGB;			// text color index
	DWORD		pRGB;			// paint color index
	CString		options;		// properties
};

class CMainWnd : public CWnd
{
// Construction
public:
	CMainWnd(CWnd* pWnd, _param* pInfo);
	CWnd* m_pParent;
	void Sendtest();
	void sendTR(CString name, CString data, BYTE type, int key, CString keyName, int uniqueKey);
	BOOL SendTR(CString strName, BYTE type, CString strData, BYTE key);
// Attributes
public:

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

	CStringArray m_arrGname;		//2020 10 �׷������(2�ڸ�) �׷�� ���� 
	CStringArray m_arrTmpGname;
	void	SearchGroupList(bool bInt = false);		//2020 10 ���ɱ׷츮��Ʈ��ȸ
	CParam m_param;
	void	SetParam(_param *pParam);
	void    sendTR_1(CString name, CString data, BYTE type, int key, CString keyName, int uniqueKey);
		CString Variant(int comm, CString data = "");
	// Generated message map functions
protected:
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LONG OnUser(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMainWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWND_H__012DD35A_3186_4393_8080_BDC091E08DA2__INCLUDED_)
