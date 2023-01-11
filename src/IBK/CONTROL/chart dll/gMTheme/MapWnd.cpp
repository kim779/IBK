// MapWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MapWnd.h"
#include "GrpWnd.h"
#include "../../h/axisgwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	SPACE		2
#define	CTRL_HEIGHT	18
#define	PNL_HEIGHT	22
#define	CBO_WIDTH	200

#define	CLR_BK		7

#define	ID_CBOTHEME	200

#define	TR_THEME	"pibg7030"
#define	TR_CHART	"piho7030"

// 종목에 대한 테마목록조회 TR
#define MAX_TM          300

// TR_THEME
struct _midTheme {
        char    cod2[6];                // 종목코드
};
#define	L_midTheme	sizeof(struct _midTheme)

struct  _gridTheme {
        char    tmcd[3];	// 테마코드
        char    name[30];	// 테마명
};
#define	L_gridTheme sizeof(struct _gridTheme);

struct _modTheme {
        char    hnam[18];	// 종목명
        char    nrec[4];	// # of records
        struct  _gridTheme    grid[MAX_TM];
};
#define	L_modTheme sizeof(struct _modTheme);

// TR_CHART
#define MAX_1MIN        (8*60)

struct _midThemeChart {
        char tmcd[4];		// 테마코드
        char code[7];		// 종목코드
};

#define	L_midThemeChart	sizeof(struct _midThemeChart)

/////////////////////////////////////////////////////////////////////////////
// CMapWnd

CMapWnd::CMapWnd(CWnd* view, CWnd* parent, int trKey)
{
	m_view = view;
	m_parent = parent;
	m_trKey = trKey;

	m_iTimerID = 0;

	m_pCboTheme = NULL;
	m_pGrpWnd = NULL;
	m_pcTemp = NULL;
	m_bReqTheme = true;
}

CMapWnd::~CMapWnd()
{
}


BEGIN_MESSAGE_MAP(CMapWnd, CWnd)
	//{{AFX_MSG_MAP(CMapWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(GEV_VIEW, OnViewEvent)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapWnd message handlers

int CMapWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_app = (CaxisMThemeApp *)AfxGetApp();
	m_app->Init(m_view);
	updatePalette();

	struct _param	param;
	param.name  = "CONTROL0";
	param.rect  = CRect(0, 0, 0, 0);
	param.fonts = "굴림";
	param.point = 9;
	param.style = 0;
	param.tRGB  = PALETTERGB(0, 0, 0);
	param.pRGB  = PALETTERGB(255, 255, 255);
	param.options = "/w/d480/r480/c/u1/t2/p0/n"; // "/c" ctrl

	m_pCboTheme = new CComboBox();
	m_pCboTheme->Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST, CRect(0, 0, 0, 0), this, ID_CBOTHEME);
	m_pCboTheme->SetFont(m_app->m_font);
	

	m_pGrpWnd = new CGrpWnd(m_view, this, &param);
	m_pGrpWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 0);

	resize();	

	return 0;
}

BOOL CMapWnd::Create()
{
	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), m_parent, 100, NULL);

	return TRUE;
}

void CMapWnd::OnDestroy() 
{
	m_themeCode.RemoveAll();
	if (m_iTimerID)	
	{
		KillTimer(m_iTimerID);
		m_iTimerID = 0;
	}

	if (m_pcTemp)
	{
		delete [] m_pcTemp;
		m_pcTemp = NULL;
	}

	if (m_pGrpWnd)
	{
		m_pGrpWnd->DestroyWindow();
		delete m_pGrpWnd;
		m_pGrpWnd = NULL;
	}

	if (m_pCboTheme)
	{
		m_pCboTheme->DestroyWindow();
		delete m_pCboTheme;
		m_pCboTheme = NULL;
	}

	CWnd::OnDestroy();
}

void CMapWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cx == 0 || cy == 0)
		return;

	resize();	
}


long CMapWnd::OnUser(WPARAM wParam, LPARAM lParam)
{
	switch(LOBYTE(LOWORD(wParam)))
	{
	case DLL_OUB:
		oub(wParam, lParam);
		break;
	case DLL_ALERT:
		break;
	case DLL_SETPAL:
		if (m_pGrpWnd)
			m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);
		updatePalette();
		Invalidate();
		break;
	default:
		if (m_pGrpWnd)
			m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);
		break;
	}

	return 0;
}

long CMapWnd::OnViewEvent(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case viewMulti:
		switch (HIWORD(wParam))
		{
		case codeInput:			// code change by Input
			{
				setCode((char*)lParam);
			}
			break;
		}
		break;
	}

	return 0;
}

void CMapWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcCtrl;
	GetClientRect(rcCtrl);
	rcCtrl.bottom = PNL_HEIGHT;
	dc.FillSolidRect(rcCtrl, m_clrBk);
}

void CMapWnd::resize()
{
	CRect rcClient, rcTmp;
	GetClientRect(rcClient);

	rcTmp = CRect(SPACE, SPACE, SPACE + CBO_WIDTH, SPACE + CTRL_HEIGHT * 5);
	m_pCboTheme->MoveWindow(rcTmp);

	rcTmp = CRect(0, PNL_HEIGHT, rcClient.right, rcClient.bottom);
	m_pGrpWnd->MoveWindow(rcTmp);
}

void CMapWnd::updatePalette()
{
	m_clrBk = m_app->GetColor(m_view, CLR_BK);
	m_brBk.DeleteObject();
	m_brBk.CreateSolidBrush(m_app->GetColor(m_view, CLR_BK));
}

BOOL CMapWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(LOWORD(wParam))
	{
	case ID_CBOTHEME:
		switch (HIWORD(wParam))
		{
		case CBN_SELENDOK:
			if (m_pCboTheme->GetCurSel() >= 0)
			{
				CString sThemeName, sSeriesName;
				m_theme = m_themeCode.GetAt(m_pCboTheme->GetCurSel());

				m_pCboTheme->GetLBText(m_pCboTheme->GetCurSel(), sThemeName);
				sSeriesName.Format("^w%s,%s", sThemeName, m_codeName);
				m_pGrpWnd->SetProperty(sSeriesName);

				requestChart(m_theme, m_code);
			}
			break;
		}
		break;
	}
	
	return CWnd::OnCommand(wParam, lParam);
}

HBRUSH CMapWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
	case CTLCOLOR_BTN:
		pDC->SetBkColor(m_clrBk);
		hbr = (HBRUSH)m_brBk;
		break;
	}

	return hbr;
}

void CMapWnd::requestTheme(CString code)
{
	m_bReqTheme = true;

	struct _midTheme*	pmid;

	if (m_pcTemp) delete [] m_pcTemp;
	m_pcTemp  = new char[L_midTheme + L_userTH];
	ZeroMemory(m_pcTemp, L_midTheme + L_userTH);

	pmid = (struct _midTheme *)&m_pcTemp[L_userTH];
	CopyMemory(pmid->cod2, code, (code.GetLength() < sizeof(pmid->cod2)) ? code.GetLength() : sizeof(pmid->cod2)); // 종목코드

	_userTH* puserTH = (_userTH *)m_pcTemp;
	CopyMemory(puserTH->trc, TR_THEME, 8);
	puserTH->stat = 0;
	puserTH->key = (char)m_trKey;

	m_view->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, L_midTheme), (long)m_pcTemp);
}

void CMapWnd::requestChart(CString themeCode, CString code)
{
	m_bReqTheme = false;
	if (!m_pGrpWnd)
		return;
	
	CString sCode;
	sCode.Format("A%s", code);

	struct _midThemeChart*	pmid;

	if (m_pcTemp) delete [] m_pcTemp;
	m_pcTemp  = new char[L_midThemeChart + L_userTH];
	ZeroMemory(m_pcTemp, L_midThemeChart + L_userTH);

	pmid = (struct _midThemeChart *)&m_pcTemp[L_userTH];
	sprintf(pmid->tmcd, "%s", themeCode);		// 테마코드
	CopyMemory(pmid->code, sCode, (sCode.GetLength() < sizeof(pmid->code)) ? sCode.GetLength() : sizeof(pmid->code)); // 종목코드

	_userTH* puserTH = (_userTH *)m_pcTemp;
	CopyMemory(puserTH->trc, TR_CHART, 8);
	puserTH->stat = 0;
	puserTH->key = (char)m_trKey;

	m_view->SendMessage(WM_USER, MAKEWPARAM(invokeTRx, L_midThemeChart), (long)m_pcTemp);
}

void CMapWnd::setCode(char* code)
{
	//if (m_pGrpWnd)
	//	m_pGrpWnd->SendMessage(WM_USER, wParam, lParam);

	m_code.Format("%s", code);
	m_code.TrimRight();

	m_theme = _T("");

	m_pCboTheme->ResetContent();
	m_themeCode.RemoveAll();

	requestTheme(m_code);
}

void CMapWnd::oub(WPARAM wParam, LPARAM lParam)
{
	if (m_bReqTheme)
	{
		m_bReqTheme = false;
		oubTheme(wParam, lParam);	
	}
	else
	{
		if (m_pGrpWnd)
		{
			DWORD data = lParam;
			int   nRemoveData = 32 + 20;

			data += nRemoveData; // 테마명 + 종목명
			wParam = MAKEWPARAM(LOWORD(wParam), HIWORD(wParam) - nRemoveData);
			m_pGrpWnd->SendMessage(WM_USER, wParam, data);
		}
	}
}

void CMapWnd::oubTheme(WPARAM wParam, LPARAM lParam)
{
	struct _modTheme* pmod = (struct _modTheme*)lParam;

	int nCnt = atoi(CString(pmod->nrec, sizeof(pmod->nrec)));

	m_pCboTheme->ResetContent();
	m_themeCode.RemoveAll();

	if (m_iTimerID > 0)	KillTimer(m_iTimerID);
	if (nCnt == 0)
	{
		if (m_pGrpWnd)	m_pGrpWnd->ClearGraph("연관된 테마가 없습니다.");
		m_theme = _T("");

		return;
	}

	CString sThemeName, sSeriesName;
	m_codeName = CString(pmod->hnam, sizeof(pmod->hnam));
	m_codeName.TrimLeft(); m_codeName.TrimRight();

	struct _gridTheme* pgrid;
	for (int ii = 0; ii < nCnt; ii++)
	{
		pgrid = &pmod->grid[ii];
	
		sThemeName = CString(pgrid->name, sizeof(pgrid->name));
		sThemeName.TrimLeft(); sThemeName.TrimRight();

		m_pCboTheme->AddString(sThemeName);
		m_themeCode.Add(CString(pgrid->tmcd, sizeof(pgrid->tmcd)));

	}
	m_pCboTheme->SetCurSel(0);
	m_theme = m_themeCode.GetAt(m_pCboTheme->GetCurSel());

	m_pCboTheme->GetLBText(m_pCboTheme->GetCurSel(), sThemeName);
	sSeriesName.Format("^w%s,%s", sThemeName, m_codeName);
	m_pGrpWnd->SetProperty(sSeriesName);

	requestChart(m_theme, m_code);
	m_iTimerID = 1001;
	SetTimer(m_iTimerID, 30000, NULL);
}

void CMapWnd::OnTimer(UINT nIDEvent) 
{
	requestChart(m_theme, m_code);
	CWnd::OnTimer(nIDEvent);
}
