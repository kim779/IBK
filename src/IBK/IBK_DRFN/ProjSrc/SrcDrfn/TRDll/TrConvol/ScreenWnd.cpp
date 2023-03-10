// ScreenWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWnd.h"

#include "../DR_Include/hana_typedef.h"

#include "../../inc/winhand_.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FORM_WIDTH		400
#define FORM_HEIGHT		493

/////////////////////////////////////////////////////////////////////////////
// CScreenWnd

//IMPLEMENT_DYNCREATE(CScreenWnd, CWnd)

CScreenWnd::CScreenWnd(CWnd *pParent)
{
	m_pwndModuleMain = pParent;
	m_pwndMainFrm = NULL;
	
	m_FnSet.SetInit(m_pwndModuleMain, this);
}

CScreenWnd::~CScreenWnd()
{
}


BEGIN_MESSAGE_MAP(CScreenWnd, CWnd)
	//{{AFX_MSG_MAP(CScreenWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
 	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_MANAGE, OnManage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenWnd message handlers


int CScreenWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	int nIndustry = -1;
	
	OnCreate_MainWnd(0);

	if(m_pwndMainFrm != NULL)
		m_pwndMainFrm->SetInit(FALSE);

	m_FnSet.Variant(titleCC, PROGRAM_TITLE);

	return 0;
}

void CScreenWnd::OnDestroy() 
{
	// 2012.4.20 박성경: PreTranslateMessage 호출 안되는 문제 수정
	RemovePermanentHandle(m_pwndMainFrm);

	if(m_pwndMainFrm)
	{
		m_pwndMainFrm->DestroyWindow();
	}

	CWnd::OnDestroy();	
}

void CScreenWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	m_pwndMainFrm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
}


void CScreenWnd::OnCreate_MainWnd(int nIndustry)
{
	int nWidth	= -1;
	int nHeight	= -1;
	if(nIndustry == 0)
	{
		nWidth	= FORM_WIDTH;
		nHeight = FORM_HEIGHT;
	}

	m_pwndMainFrm = new CMainFrmWnd;
	//m_pwndMainFrm->m_bIsFnUser = TRUE;

	BOOL bResult = m_pwndMainFrm->Create(
		NULL,
		_T("Main Frame Window"),
		WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CRect(0, 0, 0, 0),
		this,
		NULL);
	m_pwndMainFrm->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	
	if(bResult)
	{
		m_pwndMainFrm->ShowWindow(SW_SHOW);
		SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
		m_pwndMainFrm->SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
		m_FnSet.SetPalete();
	}
}

void CScreenWnd::ReceiveTR(LPCSTR szTR, LPVOID aTRData, long dwTRDateLen)
{
	m_pwndMainFrm->ReceiveData(szTR, aTRData, dwTRDateLen);
}

void CScreenWnd::SetPalete(COLORREF clrPalete, ST_TABCOLOR stTabColor)
{
	m_pwndMainFrm->ChangeSkinColor(clrPalete, stTabColor);
}

CWnd* CScreenWnd::GetModuleMainWnd()
{
	return m_pwndModuleMain;
}

LONG CScreenWnd::OnUser(WPARAM wParam, LPARAM lParam)
{
	LONG	ret = 0;
	switch(LOBYTE(LOWORD(wParam)))
	{
	case DLL_SETPAL:
		m_FnSet.SetPalete();
		break;
		
	case DLL_ALERTx:
		m_FnSet.ReceiveReal(wParam, lParam);
		break;
		
	case DLL_OUBx:
		{
#if(0)
			char* pBytes = (char *)lParam;
			struct _extTH* extTH = (struct _extTH *)pBytes;
			pBytes += L_extTH;

			int nKey = extTH->key;
			int nLen = extTH->size;

			wParam = MAKEWPARAM(MAKEWORD(DLL_OUB, nKey), nLen);
			lParam = (LPARAM)pBytes;
#else
		_extTHx* info = (_extTHx*)lParam;
		int nLen = info->size;
		char* pData = info->data;
		int nKey = info->key;

		wParam = MAKEWPARAM(MAKEWORD(DLL_OUB, nKey), nLen);
		lParam = (LPARAM)pData;
#endif
		}

	case DLL_OUB:
		m_FnSet.ReceiveTR(wParam, lParam);
		break;
		
	case DLL_TRIGGER:
		// 		if (m_bDestroy)
		// 			break;
		// 		ParseTrigger((char*)lParam, FALSE);
		break;
		
	case DLL_DOMINO:		//# Open Shard!
		/*ParseTrigger((char*)lParam, FALSE);*/
		break;
		
	default:
		;
	}
	
	return ret;
}

LONG CScreenWnd::OnManage(WPARAM wParam, LPARAM lParam)
{
	LONG	ret = 0;
	switch (LOWORD(wParam))
	{
	case MK_SETPAL:
		m_FnSet.m_clrPalete = (COLORREF)lParam;
		/*OperPallette();*/
		Invalidate(FALSE);
		break;
	case MK_GETROOT:
		/*ret = (LONG)(char*)m_home.operator LPCTSTR();*/
		break;
		
	default:
		;
	}
	
	return ret;
}

void CScreenWnd::ReceiveReal(WPARAM wParam, LPARAM lParam)
{
	m_pwndMainFrm->SendMessage(WM_BC_DATA_RECEIVED, wParam, lParam);
}

// 2012.4.20 박성경: PreTranslateMessage 호출 안되는 문제 수정 >>
void CScreenWnd::SetPermanentHandle(HANDLE h, CObject* permOb)
{
	AFX_MODULE_STATE* pState = AfxGetAppModuleState();
	if(!pState)		return;
	
	AFX_MODULE_THREAD_STATE* pThread = pState->m_thread.GetData();
	if(pThread && pThread->m_pmapHWND)
	{
		pThread->m_pmapHWND->SetPermanent(h, permOb);
	}
}

void CScreenWnd::RemovePermanentHandle(HANDLE h)
{
	AFX_MODULE_STATE* pState = AfxGetAppModuleState();
	if(!pState)		return;
	
	AFX_MODULE_THREAD_STATE* pThread = pState->m_thread.GetData();
	if(pThread && pThread->m_pmapHWND)
		pThread->m_pmapHWND->RemoveHandle(h);
}
// 2012.4.20 박성경: PreTranslateMessage 호출 안되는 문제 수정 <<