// PnInput.cpp : implementation file
//

#include "stdafx.h"
#include "AxisGMView.h"
#include "PnInput.h"
#include "PnWndCombo.h"
#include "PnWndEdit.h"
#include "CodeCtrl.h"
#include "PnTooltip.h"
#include "CheckBox.h"
#include "MultiGiganDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	sz2NameImgX	36
#define	sz2NameImgY	20
#define	sz3NameImgX	48
#define	sz3NameImgY	20
#define	sz4NameImgX	60
#define	sz4NameImgY	20
#define	szNewImgX	20
#define	szNewImgY	20

/////////////////////////////////////////////////////////////////////////////
// CPnInput
struct _info	infoInput[] = {
	{ BTN_CFG,		0, 1, 2, 0,	"지표바", "좌측메뉴 보이기/감추기" },
	{ BTN_UNIT,		0, 1, 2, 0, "주식", "주식"},
	{ CMB_CODE,		0, 0, 0, 0,	"", "" },
	{ BTN_CODE,		0, 1, 2, 0,	"", "종목 선택창" },
	{ BTN_MATRIX,	0, 1, 2, 0, "", "차트구성" },
	{ BTN_MERGE,	0, 1, 2, 0, "", "차트병합" },
	{ BTN_CHECK,    0, 1, 2, 0, "", "복수체크" },
	{ BTN_FOCUS,	0, 0, 0, 0, "집중분석", "집중분석" },
	{ BTN_DDAY,		0, 1, 2, 0,	"", "일간차트" },
	{ BTN_DWEEK,	0, 1, 2, 0,	"", "주간차트" },
	{ BTN_DMON,		0, 1, 2, 0,	"", "월간차트" },
	{ BTN_DMIN,		0, 1, 2, 0,	"", "분  차트" },
	{ BTN_DTICK,	0, 1, 2, 0,	"", "틱  차트" },
	{ CMB_TIME,		0, 0, 0, 0,	"", "" },
	{ STC_GIGAN,	0, 0, 0, 0,	"", "" },
	{ CMB_GIGAN,	0, 0, 0, 0,	"", "" },
	{ CHK_TODAY,	0, 0, 0, 0,	"", "" },
	{ BTN_GIGAN2,	0, 0, 0, 0,	"설정", "복수 기간 설정" },
	{ BTN_ORDER,	0, 0, 0, 0,	"주문", "주문 화면 열기" },
	{ BTN_INIT,		0, 0, 0, 0,	"초기화", "선택 차트 초기화" }
};

#define	GAP1	1
#define	GAP2	2
#define	GAP3	5
#define	GAP4	15
#define	GAP5	30

#define	rotateTimerID	1111
#define	triggerTimerID	1112

CPnInput::CPnInput(CWnd *pwndView, CWnd* pwndGView, CFont* pFont, int ctrlID, char* info)
: CPnBaseWnd(pwndView, pwndGView, pFont, ctrlID, info)
{
	m_pToolTip = NULL;
	m_pCodeCB = NULL;
	m_pGapCB = NULL;
	m_pGiganCB = NULL;

	m_pCodeImage = NULL;
	m_pCfgImage = NULL;
	m_pIUnitImage = NULL;
	m_pNTimeImage = NULL;
	m_pNBtnImage = NULL;

	m_p2NameImgDN = NULL;
	m_p2NameImgMV = NULL;
	m_p2NameImgUP = NULL;

	m_p3NameImgDN = NULL;
	m_p3NameImgMV = NULL;
	m_p3NameImgUP = NULL;

	m_p4NameImgDN = NULL;
	m_p4NameImgMV = NULL;
	m_p4NameImgUP = NULL;

	m_pIMatrix = NULL;
	m_pIMerge = NULL;
	m_pICheckOn = NULL;
	m_pICheckOff = NULL;

	m_bInitResize = true;
	m_bMouseIN = FALSE;
	m_bLButton = false;
	m_iMoveID = 0;
	m_bCheckOn = true;
	m_BtnOrgStatus = 0;

	struct _MultiChart	*MultiChart = (struct _MultiChart*)info;

	m_iOrgUnit = m_iDtUnit = MultiChart->btUnit;

	ReadEnv(MultiChart);

	m_strValidCode = _T("");
	m_strTrigger = _T("");
	m_strMultiCode = _T("");

	m_pfontButton = ((CAxisGMViewApp*)AfxGetApp())->GetFont(pwndView, 9, "돋움");
	m_lock = FALSE;

	m_table = NULL;
	m_merge = NULL;

	_MultiChart *pMultiInfo = (_MultiChart *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMultiInfo), 0);
	m_mType = pMultiInfo->btType;
}

CPnInput::~CPnInput()
{
}


BEGIN_MESSAGE_MAP(CPnInput, CPnBaseWnd)
	//{{AFX_MSG_MAP(CPnInput)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(GEV_INPUT, OnInputEvent)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_BN_CLICKED(CHK_TODAY, OnClickedToday)
	ON_MESSAGE(AXM_TABLE_NOTIFY, OnTableMake)
	ON_MESSAGE(AXM_CELL_NOTIFY,  OnCellMerge)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPnInput message handlers


LRESULT CPnInput::OnInputEvent(WPARAM wParam, LPARAM lParam)
{
	CString	strTemp;

	switch (LOWORD(wParam))
	{
	case INPUT_GET_POS_COMMENT:
		m_comment = GetPosComment(CPoint(LOWORD(lParam), HIWORD(lParam)));
		return (LRESULT)(LPCTSTR)m_comment;
	case INPUT_CHANGE:
		switch (HIWORD(wParam))
		{
		case ipUnit:
			ChangeUnit(lParam);

			OnChangeUnit();
			break;
		case IP_CODE:	// lParam:char*
			if (!CheckCode())
				m_pCodeCB->SetEditData("");
			else
				NotifyCodeChange();
			break;
		case ipGap:	// time button change
			ChangeGap(lParam, false);
			break;
		case IP_GIGAN:
			if (lParam > 0)
				NotifyGiganChange(lParam);
			break;
		case ipDisplay:		case ipRotate:
			break;
		case ipTab:
			ProcTab(lParam);
			break;
		case INPUT_BUTTON:
			break;
		case ipCEdit:
			ProcTab(-1);
			break;
		case ipUnitCode:
			ChangeUnitAndCode((LPCTSTR)lParam);
			break;
		}
		break;
	case INPUT_DATA:
		switch (HIWORD(wParam))
		{
		case GET_TOTAL_DAY:
		case SET_TOTAL_DAY:
		case setCodeInfo:
			break;
		case domminoCode:
			GetDominoCode((char*)lParam, strTemp, false);
			if (!m_strMultiCode.IsEmpty())
			{
				NotifyMultiCodeChange();
				return TRUE;
			}
			if (strTemp.IsEmpty())
				return TRUE;

			if (m_pCodeCB)
			{
				m_pCodeCB->SetEditData(strTemp);
				m_pCodeCB->SetFocus();
			}

			NotifyCodeChange();
			break;
		case triggerCode:
			GetDominoCode((char*)lParam, strTemp, true);
			if (!m_strMultiCode.IsEmpty())
			{
				NotifyMultiCodeChange();
				return TRUE;
			}
			if (strTemp.IsEmpty())
				return FALSE;

			if (m_pCodeCB)
				m_pCodeCB->SetEditData(strTemp);

			NotifyCodeChange();
			return TRUE;
		case GET_VALID_CODE:
			return long(m_strValidCode.operator LPCTSTR());
		case ONLY_SET_CODE:
			m_pCodeCB->SetEditData((char*)lParam);
			break;
		case GET_TODAY:
			return (LRESULT)m_pchbToday->GetCheck();
		case GET_SERIES_KIND:
			return m_iDtIndex;
		case getCurCode:
			{
				m_strTemp = m_pCodeCB->GetEditData();
				return long(m_strTemp.operator LPCTSTR());
			}
		}

		break;
	case inputEnv:
		switch (HIWORD(wParam))
		{
		case inputMain:
		case inputDisplay:
			break;
		}
		break;
	case inputViewFocus:
		if (m_pCodeCB)
			m_pCodeCB->SetFocus();
		break;
	case inputChgPalette:
		m_clrBack = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 64);
		m_clrInBack = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 66);
		Invalidate();
		m_pchbToday->SetColorBG(m_clrInBack);
		break;
	case InputMulti:
		return OnMultiEvent(wParam, lParam);
	default:
		break;
	}

	return TRUE;
}

int CPnInput::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	m_clrBack = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 64);
	m_clrInBack = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 66);
	m_clrFrame = PALETTERGB(193, 213, 234); 

	m_userPath.Format("%s%s\\", m_pApp->GetUserPath(), m_pApp->GetUName());

	CString	path = m_pApp->GetImagePath(m_pwndView, NTIMEIMAGE);
	m_pNTimeImage = m_pApp->GetImage(imgNTime, path);
	path = m_pApp->GetImagePath(m_pwndView, NBTNIMAGE);
	m_pNBtnImage = m_pApp->GetImage(imgNBtn, path);
	path = m_pApp->GetImagePath(m_pwndView, CODEIMAGE);
	m_pCodeImage = m_pApp->GetImage(imgCode, path);
	path = m_pApp->GetImagePath(m_pwndView, ICFGIMAGE);
	m_pCfgImage = m_pApp->GetImage(imgICfg, path);

	path = m_pApp->GetImagePath(m_pwndView, IUNITIMAGE);
	m_pIUnitImage = m_pApp->GetImage(imgIUnit, path);

	path = m_pApp->GetImagePath(m_pwndView, "GTI_MATRIX.bmp");
	m_pIMatrix = m_pApp->GetImage(path, szNewImgX, szNewImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "GTI_MERGE.bmp");
	m_pIMerge = m_pApp->GetImage(path, szNewImgX, szNewImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "GTI_CHKON.BMP");
	m_pICheckOn = m_pApp->GetImage(path, szNewImgX, szNewImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "GTI_CHKOFF.BMP");
	m_pICheckOff = m_pApp->GetImage(path, szNewImgX, szNewImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	
	path = m_pApp->GetImagePath(m_pwndView, "2BTN_DN.BMP");
	m_p2NameImgDN = m_pApp->GetImage(path, sz2NameImgX, sz2NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "2BTN_EN.BMP");
	m_p2NameImgMV = m_pApp->GetImage(path, sz2NameImgX, sz2NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "2BTN.BMP");
	m_p2NameImgUP = m_pApp->GetImage(path, sz2NameImgX, sz2NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));

	path = m_pApp->GetImagePath(m_pwndView, "3BTN_DN.BMP");
	m_p3NameImgDN = m_pApp->GetImage(path, sz3NameImgX, sz3NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "3BTN_EN.BMP");
	m_p3NameImgMV = m_pApp->GetImage(path, sz3NameImgX, sz3NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "3BTN.BMP");
	m_p3NameImgUP = m_pApp->GetImage(path, sz3NameImgX, sz3NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));

	path = m_pApp->GetImagePath(m_pwndView, "4BTN_DN.BMP");
	m_p4NameImgDN = m_pApp->GetImage(path, sz4NameImgX, sz4NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "4BTN_EN.BMP");
	m_p4NameImgMV = m_pApp->GetImage(path, sz4NameImgX, sz4NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));
	path = m_pApp->GetImagePath(m_pwndView, "4BTN.BMP");
	m_p4NameImgUP = m_pApp->GetImage(path, sz4NameImgX, sz4NameImgY, ILC_COLOR24|ILC_MASK, RGB(255, 0, 255));

	CDC	*pDC = GetDC();
	CFont	*sFont = pDC->SelectObject(m_pFont);
	m_szHangul = pDC->GetOutputTextExtent("한");
	m_szNumeric = pDC->GetOutputTextExtent("9");
	m_szAlphabet = pDC->GetOutputTextExtent("K");
	pDC->SelectObject(sFont);
	ReleaseDC(pDC);

	CreateWndCtrl();

	return 0;
}

void CPnInput::CreateWndCtrl()
{
	int	cmbOption = WS_VISIBLE|WS_CHILD|WS_VSCROLL|CBS_DROPDOWNLIST;

	CString tmps;
	COLORREF bg, fg;
	tmps.Format("%s/%s/%s", ((CAxisGMViewApp *)AfxGetApp())->GetRoot(), TABDIR, PALETTE);
	bg = GetPrivateProfileInt(GENERALSN, "ComboBg", -1, tmps);
	fg = GetPrivateProfileInt(GENERALSN, "ComboFg", -1, tmps);
	bg = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), bg);
	fg = m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), fg);

	m_pCodeCB = new CCodeCtrl(this, m_pwndGView, m_pFont, CMB_CODE, m_userPath);
	m_pCodeCB->Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), this, 4);
	m_pCodeCB->SetComboPalette(bg, fg);

	cmbOption = WS_VISIBLE|WS_CHILD|WS_VSCROLL|CBS_DROPDOWN;
	m_pGapCB = new CPnWndCombo(this, m_pwndGView, CMB_TIME);
	m_pGapCB->Create(cmbOption, CRect(0, 0, 10, 10), this, 5);
	m_pGapCB->SetComboPalette(bg, fg);
	m_pGapCB->SetFont(m_pFont);
	m_pGapCB->AddString("1");
	m_pGapCB->AddString("2");
	m_pGapCB->AddString("5");
	m_pGapCB->AddString("10");
	m_pGapCB->AddString("15");
	m_pGapCB->AddString("30");

	m_pGiganCB = new CPnWndCombo(this, m_pwndGView, CMB_GIGAN);
	m_pGiganCB->Create(cmbOption, CRect(0, 0, 10, 10), this, 6);
	m_pGiganCB->SetComboPalette(bg, fg);
	m_pGiganCB->SetFont(m_pFont);
	m_pGiganCB->AddString("50");
	m_pGiganCB->AddString("100");
	m_pGiganCB->AddString("150");
	m_pGiganCB->AddString("200");
	m_pGiganCB->AddString("250");
	m_pGiganCB->AddString("500");
	m_pGiganCB->SetWindowText("300");

	m_pchbToday = new CCheckBox;
	m_pchbToday->Create("당일", NULL, CRect(0, 0, 10, 10), this, CHK_TODAY, m_pFont);
	m_pchbToday->SetColorBG(m_clrInBack);

	if (!m_pToolTip)
	{
		m_pToolTip = new CPnToolTip(m_pwndView, this, GEV_INPUT);
		m_pToolTip->Create(m_pFont);
	}

	// 테이블 콘트롤 생성
	m_table = new CAxMTableCtrl(TMAX_COL, TMAX_ROW, TMAX_COL, TMAX_ROW);
	// 셀병합 콘트롤 생성
	m_merge = new CAxMTableMergeCtrl();
}

void CPnInput::OnPaint() 
{
	CPaintDC dc(this);

	Draw(&dc);
}

void CPnInput::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cx == 0 && cy == 0)
		return;

	if (m_bInitResize)
	{
		m_bInitResize = false;
		SetInfo(CRect(0, 0, cx, cy));
		ArrangeCtrl(CRect(0, 0, cx, cy), false);

		ChangeIndex(m_iDtIndex, true, false, false);
		ChangeUnit(m_iDtUnit);
		TodayDisplay();

		if (m_iDtUnit == GU_FOREIGN && (m_iDtIndex == GI_MINUTE || m_iDtIndex == GI_TICK))
			ChangeIndex(GI_DAY, true, true, false);

		CheckComboSel();

		if (m_mType == MT_FOREIGN)
			m_pCodeCB->EnableWindow(false);

		return;
	}

	ArrangeCtrl(CRect(0, 0, cx, cy), false);	
}

void CPnInput::OnDestroy() 
{
	if (m_pCodeCB)		WND_DELETE(m_pCodeCB);
	if (m_pGapCB)		WND_DELETE(m_pGapCB);
	if (m_pGiganCB)		WND_DELETE(m_pGiganCB);
	if (m_pToolTip)		WND_DELETE(m_pToolTip);
	if (m_pchbToday)	WND_DELETE(m_pchbToday);

	if (m_p2NameImgDN)	IMG_DELETE(m_p2NameImgDN);
	if (m_p2NameImgMV)	IMG_DELETE(m_p2NameImgMV);
	if (m_p2NameImgUP)	IMG_DELETE(m_p2NameImgUP);

	if (m_p3NameImgDN)	IMG_DELETE(m_p3NameImgDN);
	if (m_p3NameImgMV)	IMG_DELETE(m_p3NameImgMV);
	if (m_p3NameImgUP)	IMG_DELETE(m_p3NameImgUP);

	if (m_p4NameImgDN)	IMG_DELETE(m_p4NameImgDN);
	if (m_p4NameImgMV)	IMG_DELETE(m_p4NameImgMV);
	if (m_p4NameImgUP)	IMG_DELETE(m_p4NameImgUP);

	if (m_pIMatrix)		IMG_DELETE(m_pIMatrix);
	if (m_pIMerge)		IMG_DELETE(m_pIMerge);
	if (m_pICheckOn)	IMG_DELETE(m_pICheckOn);
	if (m_pICheckOff)	IMG_DELETE(m_pICheckOff);

	if (m_table)
	{
		delete m_table;
		m_table = NULL;
	}
	if (m_merge)
	{
		delete m_merge;
		m_merge = NULL;
	}

	CPnBaseWnd::OnDestroy();
}

void CPnInput::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPnBaseWnd::OnLButtonDown(nFlags, point);

	struct _comp* comp = SearchCom(point);
	if (!comp)
		return;

	if (IsDisableButton(comp->cID))
		return;

	m_bLButton = true;
	m_iSelID = comp->cID;

	m_BtnOrgStatus = comp->status;
	InvalidateCom(comp, btnDown);
}

void CPnInput::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CPnBaseWnd::OnLButtonUp(nFlags, point);
	LButtonUp(point);
}

void CPnInput::LButtonUp(CPoint point)
{
	if (!m_bLButton)
		return;

	m_iMoveID = -1;
	m_bLButton = false;

	struct _comp* pcompOld = SearchCom(m_iSelID);
	struct _comp* pcompNew = SearchCom(point);
	if (!pcompNew || pcompOld != pcompNew)
	{
		if (pcompOld)
		{
			if (m_BtnOrgStatus != btnDown)
				InvalidateCom(pcompOld, btnUp);
		}
		m_iSelID = -1;
		return;
	}

	switch (m_iSelID)
	{
	case BTN_DDAY:
	case BTN_DWEEK:
	case BTN_DMON:
	case BTN_DMIN:
	case BTN_DTICK:
		Invalidate();
		break;
	default:
		if (!pcompNew || m_iSelID != pcompNew->cID || !pcompNew->bshow)
		{
			if (pcompOld)
				InvalidateCom(pcompOld, btnUp);

			m_iSelID = -1;
			return;
		}
	}
	
	if (pcompOld)
	{
		switch (m_iSelID)
		{
		case BTN_UNIT:
			if (m_mType >= MT_MONITOR)
			{
				InvalidateCom(pcompOld, btnUp);
				break;
			}
			OnButtonUnitClick(pcompNew);
			InvalidateCom(pcompOld, btnUp);
			break;
		default:
			InvalidateCom(pcompOld, btnUp);
			break;
		}
	}

	int iIndex = -1;
	switch (m_iSelID)
	{// process etc button
	case BTN_DDAY:
		iIndex = GI_DAY;
		break;
	case BTN_DWEEK:
		iIndex = GI_WEEK;
		break;
	case BTN_DMON:
		iIndex = GI_MONTH;
		break;
	case BTN_DMIN:
		iIndex = GI_MINUTE;
		break;
	case BTN_DTICK:
		iIndex = GI_TICK;
		break;
	case BTN_CFG:
		m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewShowWindow, showCfg), 1);
		break;
	case BTN_CODE:	
		if (m_mType != MT_FOREIGN)
			OpenCodeDialog();
		break;
	case BTN_MATRIX:
		if (m_mType < MT_MONITOR)
			OnButtonTableClick(pcompNew);
		break;
	case BTN_MERGE:
		if (m_mType < MT_MONITOR)
			OnButtonCellClick(pcompNew);
		break;
	case BTN_CHECK:
		OnButtonCheckClick();
		break;
	case BTN_FOCUS:
		OnFocusClick();
		break;
	case BTN_GIGAN2:
		OnMultiGiganClick();
		break;
	case BTN_ORDER:
		OnOrderClick(pcompNew);
		break;
	case BTN_INIT:
		NotifyInit();
		break;
	}
	
	if (iIndex > 0)
	{
		ChangeIndex(iIndex, true, true, true);
		SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_CHANGE, INPUT_BUTTON), m_iSelID);
	}
}

void CPnInput::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CPnBaseWnd::OnRButtonUp(nFlags, point);
}

//#include <fstream.h>
void CPnInput::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPnBaseWnd::OnMouseMove(nFlags, point);

	if (!m_bMouseIN)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		m_bMouseIN = _TrackMouseEvent(&tme);
	}

//ofstream dFile ("C:\\dataG.trc", ios::app);
//dFile	<<"<"<<m_bMouseIN<<""<<endl;

	if (m_bLButton)
		return;

	CPoint	Orgpoint = point;
	struct _comp* mcomp = SearchCom(Orgpoint);
	if (!mcomp)
	{
		mcomp = SearchCom(m_iMoveID);
		if (mcomp)
			InvalidateCom(mcomp, btnUp);
		m_iMoveID = -1;

		return;
	}

	switch (mcomp->cID)
	{
	case BTN_UNIT:
	case BTN_CFG:		case BTN_CODE:
	case BTN_FOCUS:
	case BTN_GIGAN2:	case BTN_ORDER:	case BTN_INIT:
	case BTN_MATRIX: case BTN_MERGE: case BTN_CHECK:
		break;
	case BTN_DDAY:	case BTN_DWEEK:	case BTN_DMON:	case BTN_DMIN:	case BTN_DTICK:
		if (mcomp->status == btnDown)
		{
			mcomp = SearchCom(m_iMoveID);
			if (mcomp)
				InvalidateCom(mcomp, btnUp);
			m_iMoveID = -1;

			return;
		}
		break;
	default:
		mcomp = SearchCom(m_iMoveID);
		if (mcomp)
			InvalidateCom(mcomp, btnUp);
		m_iMoveID = -1;

		return;
	}

	if (m_iMoveID == mcomp->cID)
		return;

	struct _comp* ocomp = SearchCom(m_iMoveID);
	if (ocomp)
		InvalidateCom(ocomp, btnUp);

	m_iMoveID = mcomp->cID;
	if (!IsDisableButton(mcomp->cID))
		InvalidateCom(mcomp, btnMove);
}

void CPnInput::OnMouseLeave(UINT nFlags, CPoint point)
{
	if (m_bLButton)
	{
		LButtonUp(point);
	}
	else
	{
		struct _comp* mcomp = SearchCom(m_iMoveID);
		if (mcomp)
			InvalidateCom(mcomp, btnUp);
	}
	m_iMoveID = -1;
	m_bMouseIN = FALSE;

	if (m_pToolTip)
	{
		m_pToolTip->m_dispStr = _T("");
		m_pToolTip->hideToolTip();
	}
}

LRESULT CPnInput::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_MOUSELEAVE)
	{
		OnMouseLeave(0,CPoint(0,0));
		return TRUE;
	}

	if (m_pToolTip)
		m_pToolTip->RelayEvent(message);	
	
	return CPnBaseWnd::WindowProc(message, wParam, lParam);
}

void CPnInput::Draw(CDC *pDC)
{
	DrawBackground(pDC);

	CFont		*sFont = pDC->SelectObject(m_pFont);
	COLORREF	sColor = pDC->SetTextColor(RGB(0,0,0));
	COLORREF	sbkColor = pDC->SetBkColor(m_clrBack);

	struct _comp *pComp;
	for (int ii = 0; ii < m_arComs.GetSize(); ii++)
	{
		pComp = m_arComs.GetAt(ii);
		if (pComp->cID == STC_GIGAN)
		{
			pDC->DrawText("조회기간", pComp->cRC, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		else
		{
			DrawButton2(pDC, pComp);
		}
	}

	pDC->SetBkColor(sbkColor);
	pDC->SetTextColor(sColor);
	pDC->SelectObject(sFont);
}

void CPnInput::ArrangeCtrl(CRect rectC, bool bChgIndex)
{
	_MultiChart *pMultiInfo = (_MultiChart *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMultiInfo), 0);
	bool	bHide = (pMultiInfo->btType == MT_FOREIGN)? true:false;

	struct _comp *pcomp;
	rectC.DeflateRect(1, 1);
	int iLeft = rectC.right - (sz2NameImgX * 2 + sz3NameImgX + 3) - 5;

	int lastComp = CMB_GIGAN;

	int iGap;
	int iPos = 0;
	for (int ii = BTN_CFG; ii <= BTN_INIT; ii++)
	{
		if (ii >= m_arComs.GetSize())
			break;

		iGap = 0;
		pcomp = m_arComs.GetAt(ii);
		pcomp->bshow = true;

		if (pcomp->cID == lastComp) 
		{
			if (pcomp->cRC.right + 4 > iLeft)
				iLeft = pcomp->cRC.right + 4;
		}

		switch (pcomp->cID)
		{
		case BTN_DMIN:
		case BTN_DTICK:
			pcomp->bshow = (bHide)? false:true;
			break;
		case CMB_TIME:
			iGap = 1;
			break;
		case BTN_UNIT:
		case CMB_CODE:
		case STC_GIGAN:
		case CMB_GIGAN:
		case BTN_MATRIX:
		case BTN_MERGE:
		case BTN_CHECK:
			iGap = 1;
			break;		
		case BTN_FOCUS:
			iGap = 4;
			break;
		case BTN_DDAY:
			iGap = 4;
			break;

		case CHK_TODAY:
			iGap = 4;
			pcomp->bshow = (m_iDtIndex == GI_MINUTE || m_iDtIndex == GI_TICK);
			break;
		case BTN_GIGAN2:
		case BTN_ORDER:
			pcomp->cRC.left = iLeft;
			pcomp->cRC.right = iLeft + sz2NameImgX;
			iLeft += sz2NameImgX + 1;
			continue;
		case BTN_INIT:
			pcomp->cRC.left = iLeft;
			pcomp->cRC.right = iLeft + sz3NameImgX;
			iLeft += sz3NameImgX + 1;
			continue;
		default:
			break;
		}

		pcomp->cRC.OffsetRect(iPos - pcomp->cRC.left + iGap + 5, 0);
		iPos += pcomp->cRC.Width() + iGap;

		switch (pcomp->cID)
		{
		case CMB_CODE:
			m_pCodeCB->MoveWindow(pcomp->cRC);
			break;
		case CMB_TIME:
			m_pGapCB->MoveWindow(pcomp->cRC);
			break;
		case BTN_DDAY:
			m_rcIndex.left = pcomp->cRC.left;
			break;
		case BTN_DTICK:
			m_rcIndex.right = pcomp->cRC.right;
			break;
		case CHK_TODAY:
			m_pchbToday->MoveWindow(pcomp->cRC);
			m_pchbToday->ShowWindow(pcomp->bshow ? SW_SHOW : SW_HIDE);
			break;
		case CMB_GIGAN:
			m_pGiganCB->MoveWindow(pcomp->cRC);
			break;
		default:
			break;
		}
	}
}

void CPnInput::DrawButton(CDC* pDC, struct _comp *comp)
{
	CRect cRC = comp->cRC;
	CPoint imgPt = CPoint(cRC.left, cRC.top);

	CImageList* pImage = NULL;
	CString	tmpS = _T("");
	enum enmDrawType {bDraw, bTimeImgDraw, bBtnImgDraw} enmDarw = bDraw;

	switch (comp->cID)
	{
	case BTN_DDAY:	tmpS.Format("일");	enmDarw = bTimeImgDraw;	break;
	case BTN_DWEEK:	tmpS.Format("주");	enmDarw = bTimeImgDraw;	break;
	case BTN_DMON:	tmpS.Format("월");	enmDarw = bTimeImgDraw;	break;
	case BTN_DMIN:	tmpS.Format("분");	enmDarw = bTimeImgDraw;	break;
	case BTN_DTICK:	tmpS.Format("틱");	enmDarw = bTimeImgDraw;	break;
	default:
		break;
	}

	if (enmDarw == bTimeImgDraw)
	{
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pNTimeImage);
	}
	else if (enmDarw == bBtnImgDraw)
	{
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pNBtnImage);
	}
	else
	{
		if (!pImage)
		{
			switch (comp->status)
			{
			case btnDown:
				cRC.DeflateRect(1, 1, 1, 1);
				pDC->DrawFrameControl(&cRC, DFC_BUTTON, DFCS_BUTTONPUSH|DFCS_PUSHED);
				break;
			case btnMove:
				cRC.DeflateRect(1, 1, 1, 1);
				pDC->DrawEdge(&cRC, BDR_RAISEDINNER, BF_RECT);
				break;
			case btnUp:
			default:
				break;
			}
		}
		else
		{
			pImage->Draw(pDC, 0, imgPt, ILD_TRANSPARENT);
		}
	}

	cRC.DeflateRect(1, 1, 1, 1);
	int mode = pDC->SetBkMode(TRANSPARENT);
	CFont	*sFont = pDC->SelectObject(m_pfontButton);
	if (!tmpS.IsEmpty())
		pDC->DrawText(tmpS, cRC, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SetBkMode(mode);
	pDC->SelectObject(sFont);
}

void CPnInput::DrawButton2(CDC* pDC, struct _comp* comp)
{
	if (!comp->bshow)
		return;

	switch (comp->cID)
	{
	case BTN_CFG:
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pCfgImage);
		break;
	case BTN_UNIT:
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pIUnitImage);
		DrawUnitButton(pDC, comp->cRC);
		break;
	case BTN_DDAY:	case BTN_DWEEK:	case BTN_DMON:	case BTN_DMIN:	case BTN_DTICK:
		DrawButton(pDC, comp);	break;
	case BTN_CODE:	
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pCodeImage);	break;
	case BTN_MATRIX:
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pIMatrix); 
		break;
	case BTN_MERGE:
		CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pIMerge); 
		break;
	case BTN_CHECK:
		if (m_bCheckOn)
			CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pICheckOn); 
		else
			CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pICheckOff); 
		break;
	case BTN_FOCUS:	
	case BTN_GIGAN2:	case BTN_ORDER:	
	case BTN_INIT:
		DrawNameButton(pDC, comp);	break;
	}

	if (IsDisableButton(comp->cID))
		DrawDisableButton(pDC, comp->cRC);
}

void CPnInput::DrawNameButton(CDC* pDC, struct _comp *comp)
{
	CRect cRC = comp->cRC;
	CPoint imgPt = CPoint(cRC.left, cRC.top);

	CImageList* pImage = NULL;
	CString	tmpS;

	tmpS = comp->str;
	switch(comp->cID)
	{
	case BTN_FOCUS:
		switch (comp->status)
		{
		case btnDown:	pImage = m_p4NameImgDN;	break;
		case btnMove:	pImage = m_p4NameImgMV;	break;
		case btnUp:
		default:
				pImage = m_p4NameImgUP;	break;
		}
		break;
	case BTN_GIGAN2:
	case BTN_ORDER:
		switch (comp->status)
		{
		case btnDown:	pImage = m_p2NameImgDN;	break;
		case btnMove:	pImage = m_p2NameImgMV;	break;
		case btnUp:
		default:
				pImage = m_p2NameImgUP;	break;
		}
		break;
	case BTN_INIT:
		switch (comp->status)
		{
		case btnDown:	pImage = m_p3NameImgDN;	break;
		case btnMove:	pImage = m_p3NameImgMV;	break;
		case btnUp:
		default:
				pImage = m_p3NameImgUP;	break;
		}
		break;
	}

	if (!pImage)
	{
		switch (comp->status)
		{
		case btnDown:
			cRC.DeflateRect(1, 1, 1, 1);
			pDC->DrawFrameControl(&cRC, DFC_BUTTON, DFCS_BUTTONPUSH|DFCS_PUSHED);
			break;
		case btnMove:
			cRC.DeflateRect(1, 1, 1, 1);
			pDC->DrawEdge(&cRC, BDR_RAISEDINNER, BF_RECT);
			break;
		case btnUp:
		default:
			break;
		}
	}
	else
	{
		pImage->Draw(pDC, 0, imgPt, ILD_TRANSPARENT);
	}

	cRC.DeflateRect(1, 1, 1, 1);
	int mode = pDC->SetBkMode(TRANSPARENT);
	if (!tmpS.IsEmpty())
		pDC->DrawText(tmpS, cRC, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SetBkMode(mode);
}

void CPnInput::DrawDisableButton(CDC *pDC, CRect rc)
{
	CDC mdc;
	mdc.CreateCompatibleDC(pDC);
	CBitmap bmp, *oldBmp;

	bmp.CreateCompatibleBitmap(pDC, rc.Width()-1, rc.Height()-1);
	oldBmp = mdc.SelectObject(&bmp);

	CBrush	*cBrush = m_pApp->GetBrush(m_pwndView, RGB(192,192,192));
	if (cBrush)
	{
		mdc.FillRect(CRect(0, 0, rc.Width()-1, rc.Height()-1), cBrush);
		pDC->BitBlt(rc.left+1, rc.top+1, rc.Width()-1, rc.Height()-1, &mdc, 0, 0, SRCAND);
	}

	mdc.SelectObject(oldBmp);
	bmp.DeleteObject();
}

bool CPnInput::IsDisableButton(int id)
{
	if (m_mType >= MT_MONITOR)
	{
		switch (id)
		{
		case BTN_UNIT:
		case BTN_MATRIX:
		case BTN_MERGE:
		case BTN_FOCUS:
			return true;
		case BTN_CODE:
			if (m_mType == MT_FOREIGN)
				return true;
		}
	}

	return false;
}

void CPnInput::SetInfo(CRect wRC)
{
	int	size = sizeof(infoInput) / sz_INFO;

	wRC.DeflateRect(1, 1 + 4);
	int	left = wRC.left;
	int	top = wRC.top;
	int	bottom = wRC.bottom;
	int	Height = wRC.Height() - 2;

	m_rcIndex.SetRect(left, top, left, bottom);
	for (int ii = 0; ii < size; ii++)
	{
		_comp* pcomp = new _comp;
		ZeroMemory(pcomp, sz_COMP);

		pcomp->cID = infoInput[ii].kind;
		pcomp->status = btnUp;
		pcomp->bshow = true;
		pcomp->imggen = infoInput[ii].imggen;
		pcomp->imgmov = infoInput[ii].imgmov;
		pcomp->imgsel = infoInput[ii].imgsel;
		pcomp->imgdis = infoInput[ii].imgdis;
		CopyMemory(pcomp->str, infoInput[ii].disp, sizeof(infoInput[ii].disp));
		CopyMemory(pcomp->comment, infoInput[ii].com, sizeof(infoInput[ii].com));

		switch(pcomp->cID)
		{
		case BTN_CFG:
			pcomp->cRC.SetRect(left, top, left+szICfgImgX, bottom);
			left += szICfgImgX + 1;
			break;
		case BTN_UNIT:
			pcomp->cRC.SetRect(left, top, left+m_szHangul.cx*2+6+Height, bottom-1);
			break;
		case CMB_CODE:
			pcomp->cRC.SetRect(left, top, left+m_szHangul.cx*5+4+Height, bottom-1);
			left += m_szHangul.cx*5+4+Height + 1;
			break;
		case BTN_CODE:
			pcomp->cRC.SetRect(left, top+1, left+szCodeImgX, bottom-1);
			left += szCodeImgX + 1;
			m_ptCodeBtn = pcomp->cRC.BottomRight();
			break;
		case BTN_MATRIX:
		case BTN_MERGE:
			pcomp->cRC.SetRect(left, top, left+szNewImgX, bottom);
			left += szNewImgX + 1;
			break;
		case BTN_CHECK:
			pcomp->cRC.SetRect(left, top, left+szNewImgX, bottom);
			left += szNewImgX + 2;
			break;
		case BTN_FOCUS:
			pcomp->cRC.SetRect(left, top, left+sz4NameImgX, bottom);
			left += sz4NameImgX + 1;
			break;
		case BTN_DDAY:
			m_rcIndex.left = left;
			pcomp->cRC.SetRect(left, top+1, left+szDateImgX, bottom-1);
			left += szDateImgX;
			break;
		case BTN_DMON:
			pcomp->cRC.SetRect(left, top+1, left+szDateImgX, bottom-1);
			left += szDateImgX;
			break;
		case BTN_DWEEK:
		case BTN_DMIN:
			pcomp->cRC.SetRect(left, top+1, left+szDateImgX, bottom-1);
			left += szDateImgX;
			break;
		case BTN_DTICK:
			pcomp->cRC.SetRect(left, top+1, left+szDateImgX, bottom-1);
			left += szDateImgX + 1;
			m_rcIndex.right = left - 1;
			break;
		case CMB_TIME:
			pcomp->cRC.SetRect(left, top, left+m_szNumeric.cx*3+8+Height, bottom+200);
			left += m_szNumeric.cx*3+8+Height + 3;
			break;
		case STC_GIGAN:
			pcomp->cRC.SetRect(left, top+1, left+m_szHangul.cx * 4 + 4, bottom-1);
			left += m_szHangul.cx * 4 + 4 + 1;
			break;
		case CMB_GIGAN:
			pcomp->cRC.SetRect(left, top, left+m_szNumeric.cx*4+8+Height, bottom+120);
			left += m_szNumeric.cx*4+8+Height + 3;
			break;
		case CHK_TODAY:
			pcomp->cRC.SetRect(left, top + 3, left + m_szHangul.cx * 4, bottom - 1);
			left += m_szHangul.cx * 4 + 3;
			break;
		case BTN_GIGAN2:
		case BTN_ORDER:
			pcomp->cRC.SetRect(left, top, left+sz2NameImgX, bottom);
			left += sz2NameImgX + 1;
			break;
		case BTN_INIT:
			pcomp->cRC.SetRect(left, top, left+sz3NameImgX, bottom);
			left += sz3NameImgX + 1;
			break;
		default:
			continue;
		}
		m_arComs.Add(pcomp);
	}
}

void CPnInput::ChangeUnit(int unit, bool bTran)
{
	CString	code = m_pCodeCB->GetEditData();
	CString	indexCode;
	switch (m_iDtUnit)
	{
	case GU_CODE:
		switch (unit)
		{
		case GU_INDEX:
			SetIndexCode(code);
			break;
		case GU_FUTURE:	case GU_OPTION:	case GU_COFUT:	case GU_COOPT:
			unit = GU_FUTURE;	// 강제로 선물로 바꿔줌 2008.07.28
			code = GetHistory(unit);
			break;
		case GU_FOREIGN: 
			code = GetHistory(unit);
			break;
		case GU_CODE:
			m_pCodeCB->SetUnit(m_iDtUnit);
			return;
		}
		break;
	case GU_INDEX:
		switch (unit)
		{
		case GU_CODE:	case GU_FUTURE:	case GU_FOREIGN:
			code = GetHistory(unit);
			break;
		case GU_INDEX:
			SetIndexCode(code);
			break;
		}
		break;
	case GU_FUTURE:	
		switch (unit)
		{
		case GU_CODE: case GU_FOREIGN:
			code = GetHistory(unit);
			break;
		case GU_INDEX:
			SetIndexCode(code);
			break;
		case GU_FUTURE:
			if (unit == m_iDtUnit)
			{
				m_pCodeCB->SetUnit(m_iDtUnit);
				return;
			}

			m_iDtUnit = unit;
			m_pCodeCB->SetUnit(m_iDtUnit);
			m_strValidCode.Format("%s", code);
			m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);

			CRect	wrc;
			GetClientRect(&wrc);
			ArrangeCtrl(wrc, false);
			Invalidate(true);

			return;
		}
		break;
	case GU_FOREIGN:
		switch (unit)
		{
		case GU_INDEX:
			SetIndexCode(code);
			break;
		case GU_CODE:	case GU_FUTURE:	
			code = GetHistory(unit);
			break;
		case GU_FOREIGN:
			m_pCodeCB->SetUnit(unit);
			return;
		}
		break;
	}

	m_iDtUnit = unit;
	m_pCodeCB->SetUnit(m_iDtUnit);

	struct _comp* comp = SearchCom(BTN_UNIT);
	if (comp)
	{
		CString	comment = "";
		switch (m_iDtUnit)
		{
		case GU_CODE:		comment = "주식";	break;
		case GU_INDEX:		comment = "업종";	break;
		case GU_FUTURE:		comment = "선물옵션";	break;
		case GU_FOREIGN:	comment = "해외";	break;
		}

		if (!comment.IsEmpty())
			sprintf(comp->comment, "%s", comment);
	}

	m_strValidCode.Format("%s", code);
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);	// notify unit

	CRect	wrc;
	GetClientRect(&wrc);
	ArrangeCtrl(wrc, false);
	Invalidate(true);

	m_pCodeCB->SetEditData(_T(""));
	if (!code.IsEmpty())
	{
		m_pCodeCB->SetEditData(code);
		if (bTran)
			NotifyCodeChange();
	}

	m_pCodeCB->SetFocus();

	CheckComboSel();
	TodayDisplay();
}

void CPnInput::ChangeIndex(int iIndex, bool bChgGap, bool bRedraw, bool bMessage)
{
	int iID = -1;

	struct _comp* pcomp;
	if (bRedraw)
	{
		switch(iIndex)
		{
		case GI_DAY:
			iID = BTN_DDAY;	
			break;
		case GI_WEEK:
			iID = BTN_DWEEK;
			break;
		case GI_MONTH:
			iID = BTN_DMON;
			break;
		case GI_MINUTE:
			iID = BTN_DMIN;
			break;
		case GI_TICK:
			iID = BTN_DTICK;
			break;
		default:
			iID = -1;
			break;
		}
		
		for (int ii = BTN_DDAY; ii <= BTN_DTICK; ii++)
		{
			pcomp = CPnBaseWnd::SearchCom(ii);
			if (pcomp)
			{
				if (ii == iID)
					pcomp->status = btnDown;
				else
					pcomp->status = btnUp;
			}
		}
		InvalidateRect(&m_rcIndex);

		m_iDtIndex = iIndex;
		TodayDisplay();

		UINT gaps[] = { 1, 2, 3, 5, 10, 15, 20, 30, 60};

		m_pGapCB->ResetContent();
		if (m_iDtIndex == GI_MINUTE)
			m_pGapCB->AddString("0.5");

		CString s;
		for (int i = 0; i < (sizeof(gaps) / sizeof(gaps[0])); i++) 
		{
			s.Format("%d", gaps[i]);
			m_pGapCB->AddString(s);
		}
	}

	// 보이기 안보이기 설정
	if (bChgGap)
	{
		switch(iIndex)
		{
		case GI_DAY:
		case GI_WEEK:
		case GI_MONTH:
			ChangeGap(0, !bMessage);
			m_pGapCB->ShowWindow(SW_HIDE);
			m_pchbToday->ShowWindow(SW_HIDE);
//			m_pGiganCB->EnableWindow(true);
			break;
		case GI_MINUTE:
			ChangeGap(m_iMGap, !bMessage);
			m_pGapCB->ShowWindow(SW_SHOW);
			m_pchbToday->ShowWindow(SW_SHOW);
//			if (m_pchbToday->GetCheck())
//				m_pGiganCB->EnableWindow(false);
//			else
//				m_pGiganCB->EnableWindow(true);

			break;
		case GI_TICK:
			ChangeGap(m_iTGap, !bMessage);
			m_pGapCB->ShowWindow(SW_SHOW);
			m_pchbToday->ShowWindow(SW_SHOW);
//			if (m_pchbToday->GetCheck())
//				m_pGiganCB->EnableWindow(false);
//			else 
//				m_pGiganCB->EnableWindow(true);

			break;
		default:
			break;
		}
	}
	else
	{
		if (bMessage)
			NotifyIndexChange();
	}
}

void CPnInput::ChangeGap(int gap, bool bOnlyChange)
{
	CString	sVal;
	if (gap == 930)
		sVal.Format("0.5");
	else
		sVal.Format("%d", gap);
	m_pGapCB->SetWindowText(sVal);

	if (!bOnlyChange)
	{
		if (m_iDtIndex == GI_MINUTE)	m_iMGap = gap;
		else if (m_iDtIndex == GI_TICK)	m_iTGap = gap;

		NotifyIndexChange();
	}
}

bool CPnInput::CheckCode()
{
	CString strCode = m_pCodeCB->GetEditData();
	if (strCode.IsEmpty())
		return false;

	switch (m_iDtUnit)
	{
	case GU_FUTURE:
	case GU_OPTION:
	case GU_COFUT:
	case GU_COOPT:
		{
			if (strCode.GetLength() != 8) return false;
		}
		break;
	case GU_CODE:
		{
			CString	name = (char*)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewDialog, dlgGubnFOSO), long(strCode.operator LPCTSTR()));
			if (name.IsEmpty())
				return false;
		}
		break;
	case GU_INDEX:
		if (strCode.GetLength() != sz_INDEX)
			return false;
		break;
	case GU_FOREIGN:
		break;
	}

	return true;
}

void CPnInput::ProcTab(int id)
{
	switch (m_iDtUnit)
	{
	case GU_CODE:
		switch (id)
		{
		case CMB_UNIT:
			if (m_pCodeCB->IsWindowEnabled())
				m_pCodeCB->SetFocus();
			break;
		case CMB_CODE:
			break;
		case CMB_TIME:
			if (m_pGiganCB->IsWindowEnabled())
				m_pGiganCB->SetFocus();
			break;
		case CMB_GIGAN:
			break;
		case -1:
			break;
		}
		break;
	case GU_INDEX:
		switch (id)
		{
		case CMB_UNIT:
			break;
		case CMB_KKIND:
			if (m_pCodeCB->IsWindowEnabled())
				m_pCodeCB->SetFocus();
			break;
		case CMB_CODE:
			if (m_pGapCB->IsWindowVisible() && m_pGapCB->IsWindowEnabled())
				m_pGapCB->SetFocus();
			else if (m_pGiganCB->IsWindowEnabled())
				m_pGiganCB->SetFocus();
			break;
		case CMB_TIME:
			if (m_pGiganCB->IsWindowEnabled())
				m_pGiganCB->SetFocus();	break;
		case CMB_GIGAN:
			break;
		case -1:
			break;
		}
		break;
	case GU_FUTURE:
	case GU_OPTION:
	case GU_COFUT:
	case GU_COOPT: 
		switch (id)
		{
		case CMB_UNIT:
			if (m_pCodeCB->IsWindowEnabled())
				m_pCodeCB->SetFocus();
			break;
		case CMB_CODE:
			if (m_pGapCB->IsWindowVisible() && m_pGapCB->IsWindowEnabled())
				m_pGapCB->SetFocus();
			else if (m_pGiganCB->IsWindowEnabled())
				m_pGiganCB->SetFocus();
			break;
		case CMB_TIME:
			if (m_pGiganCB->IsWindowEnabled())
				m_pGiganCB->SetFocus();
			break;
		case CMB_GIGAN:
			break;
		case -1:
			break;
		}
		break;
	case GU_FOREIGN:
		switch (id)
		{
		case CMB_UNIT:
			if (m_pCodeCB->IsWindowEnabled())
				m_pCodeCB->SetFocus();
			break;
		case CMB_CODE:
			break;
		case CMB_GIGAN:
			break;
		case -1:
			break;
		}
		break;
	}
}

void CPnInput::OpenCodeDialog()
{
	int kind;
	switch (m_iDtUnit)
	{
	case GU_CODE:	kind = dlgJCode;	break;
	case GU_INDEX:	kind = dlgUCode;	break;
	case GU_FUTURE:	case GU_OPTION:	case GU_COFUT:	case GU_COOPT:
		kind = dlgFOCode;	break;
	default:	kind = 0;
	}

	CPoint	pt = m_ptCodeBtn;
	ClientToScreen(&pt);

	CString	sCode = (char*)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewDialog, kind), 
		MAKELPARAM(pt.x, pt.y));

	if (sCode.IsEmpty())
		return;

	int index = sCode.Find("\t");
	if (index > 0)
	{
		CString	code = sCode.Left(index);
		m_pCodeCB->SetEditData(code);
		m_pCodeCB->SetFocus();

		NotifyCodeChange();
	}
	else
	{
		m_pCodeCB->SetEditData(sCode);
		m_pCodeCB->SetFocus();

		NotifyCodeChange();
	}
}

void CPnInput::ReadEnv(struct _MultiChart *MultiChart)
{
	switch (MultiChart->btUnit)
	{
	case GU_INDEX:
	case GU_FUTURE:
	case GU_OPTION:
	case GU_COFUT:
	case GU_COOPT:
	case GU_FOREIGN:
		m_iDtUnit = MultiChart->btUnit;
		break;
	default:
		m_iDtUnit = GU_CODE;
		break;
	}

	m_iDtIndex = GI_DAY;
	
	m_iMGap = 1;
	m_iTGap = 1;
}

void CPnInput::TodayDisplay()
{
	switch (m_iDtIndex)
	{
	case GI_MINUTE:
	case GI_TICK:
		m_pchbToday->ShowWindow(SW_SHOW);
	default:
		m_pchbToday->ShowWindow(SW_HIDE);
		break;
	}
}

void CPnInput::GetDominoCode(char *dCode, CString &domino, bool bTrigger)
{
	m_strMultiCode = _T("");
	domino = _T("");
	CString	sData = dCode;
//	CString	sData = _T("IB7020\t000020000040000050000060000070000100000120000140000150");
	if (sData.IsEmpty()) 
		return;

	int	index;
	CString	name, symbol, val;
	CMapStringToString	rtmStore;
	rtmStore.RemoveAll();
	for (; !sData.IsEmpty(); )
	{
		index = sData.Find('\t');
		if (index < 0)
			break;

		symbol = sData.Left(index++);
		sData = sData.Mid(index);

		index = sData.Find('\n');
		if (index < 0)	index = sData.GetLength();
		val = sData.Left(index++);

		rtmStore.SetAt(symbol, val);

		if (sData.GetLength() <= index)	break;

		sData = sData.Mid(index);
	}

	if (rtmStore.GetCount() > 1)
	{
		switch(m_iDtUnit)
		{
		case GU_CODE:	name = JTRG;	break;
		case GU_FUTURE:	name = FTRG;	break;
		case GU_OPTION:	name = OTRG;	break;
		case GU_COFUT:	name = CFTRG;	break;
		case GU_COOPT:	name = COTRG;	break;
		default:
			return;
		}

		for (POSITION pos = rtmStore.GetStartPosition(); pos;)
		{
			rtmStore.GetNextAssoc(pos, symbol, val);
			if (name == symbol)
			{
				if (m_iDtUnit == GU_FOREIGN)
					domino = val.Mid(1);
				else
					domino = val;
				break;
			}
		}
		
		if (m_iDtUnit == GU_FUTURE || m_iDtUnit == GU_OPTION || m_iDtUnit == GU_COFUT || m_iDtUnit == GU_COOPT)
		{
			CString	symbol = FOTRG;
			CString history = (char *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getHistory), long(symbol.operator LPCTSTR()));
			if (!history.IsEmpty())
			{
				int index = history.Find("\t");
				if (index > 0)
				{
					CString	Str = history.Left(index);
					index = Str.Find(" ");
					if (index > 0)
					{
						domino = Str.Left(index);
					}
				}
			}
		}

		domino.TrimRight(" ");
		if (domino.IsEmpty())
		{
			rtmStore.RemoveAll();
			return;
		}
		else if (m_iDtUnit == GU_FUTURE || m_iDtUnit == GU_OPTION || m_iDtUnit == GU_COFUT || m_iDtUnit == GU_COOPT)
		{
			CString	code;
			code.Format("%s", domino);
			CString	name = (char*)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewDialog, dlgGubnFOSO), long(code.operator LPCTSTR()));
			if (!name.IsEmpty())
			{
				int	focode = WhichFOCode(code.operator LPCTSTR());
				switch (focode)
				{
				case foOption:
					if (m_iDtUnit != GU_OPTION)	
						ChangeUnit(GU_OPTION);	
					break;
				case foCoFut:
					if (m_iDtUnit != GU_COFUT)	
						ChangeUnit(GU_COFUT);	
					break;
				case foCoOpt:
					if (m_iDtUnit != GU_COOPT)	
						ChangeUnit(GU_COOPT);	
					break;
				case foFuture:
				default:
					if (m_iDtUnit != GU_FUTURE)	
						ChangeUnit(GU_FUTURE);	
					break;
				}
			}
		}
		else if (m_iDtUnit == GU_CODE)
		{
			if (m_strValidCode == domino)
			{
				domino = _T("");
			}
			else if (bTrigger)
			{
				m_strTrigger.Format("%s\t%s", JTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}
	}
	else if (rtmStore.GetCount() == 1)
	{
		POSITION pos = rtmStore.GetStartPosition();
		rtmStore.GetNextAssoc(pos, symbol, val);

		if (symbol == _T("IB7020"))	// 관심에서 복수멀티차트로 종목 9개 트리거
		{
			m_strMultiCode = val;
			if (m_strMultiCode.GetLength() < 6)
				m_strMultiCode = _T("");

			return;
		}

		if (m_strValidCode == val)
			return;

		if (symbol == JTRG)
		{
			if (m_iDtUnit == GU_CODE)
			{
				domino = val;
				domino.TrimRight(" ");
			}

			if (!domino.IsEmpty() && bTrigger)	// trigger
			{
				m_strTrigger.Format("%s\t%s", JTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}
		else if (symbol == FTRG)
		{
			if (m_iDtUnit == GU_OPTION || m_iDtUnit == GU_COFUT || m_iDtUnit == GU_COOPT)
			{
				domino = val;
				domino.TrimRight(" ");

				m_iDtUnit = GU_FUTURE;
				m_pCodeCB->SetUnit(m_iDtUnit);
				InvalidateRect(&m_rcIndex);

				m_strValidCode.Format("%s", domino);
				m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);
			}
			else if (m_iDtUnit == GU_FUTURE)
			{
				domino = val;
				domino.TrimRight(" ");
			}

			if (!domino.IsEmpty() && bTrigger)	// trigger
			{
				m_strTrigger.Format("%s\t%s", FOTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}
		else if (symbol == OTRG)
		{
			if (m_iDtUnit == GU_FUTURE || m_iDtUnit == GU_COFUT || m_iDtUnit == GU_COOPT)
			{
				domino = val;
				domino.TrimRight(" ");

				m_iDtUnit = GU_OPTION;
				m_pCodeCB->SetUnit(m_iDtUnit);
				InvalidateRect(&m_rcIndex);

				m_strValidCode.Format("%s", domino);
				m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);
			}
			else if (m_iDtUnit == GU_OPTION)
			{
				domino = val;
				domino.TrimRight(" ");
			}

			if (!domino.IsEmpty() && bTrigger)	// trigger
			{
				m_strTrigger.Format("%s\t%s", FOTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}
		else if (symbol == CFTRG)
		{
			if (m_iDtUnit == GU_FUTURE || m_iDtUnit == GU_OPTION || m_iDtUnit == GU_COOPT)
			{
				domino = val;
				domino.TrimRight(" ");

				m_iDtUnit = GU_COFUT;
				m_pCodeCB->SetUnit(m_iDtUnit);
				InvalidateRect(&m_rcIndex);

				m_strValidCode.Format("%s", domino);
				m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);
			}
			else if (m_iDtUnit == GU_COFUT)
			{
				domino = val;
				domino.TrimRight(" ");
			}

			if (!domino.IsEmpty() && bTrigger)	// trigger
			{
				m_strTrigger.Format("%s\t%s", FOTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}
		else if (symbol == COTRG)
		{
			if (m_iDtUnit == GU_FUTURE || m_iDtUnit == GU_OPTION || m_iDtUnit == GU_COFUT)
			{
				domino = val;
				domino.TrimRight(" ");

				m_iDtUnit = GU_COOPT;
				m_pCodeCB->SetUnit(m_iDtUnit);
				InvalidateRect(&m_rcIndex);

				m_strValidCode.Format("%s", domino);
				m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, unitInput), m_iDtUnit);
			}
			else if (m_iDtUnit == GU_COOPT)
			{
				domino = val;
				domino.TrimRight(" ");
			}

			if (!domino.IsEmpty() && bTrigger)	// trigger
			{
				m_strTrigger.Format("%s\t%s", FOTRG, domino);
				SetTimer(triggerTimerID, 10, NULL);
			}
		}

		if (domino.IsEmpty() && !strlen(m_strValidCode))
		{
			switch (m_iDtUnit)
			{
			case GU_CODE:
				domino = GetHistory(m_iDtUnit);
				break;
			default:
				{
					domino = GetHistory(m_iDtUnit);

					CString	code;
					code.Format("%s", domino);
					CString	name = (char*)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewDialog, dlgGubnFOSO), long(code.operator LPCTSTR()));
					if (!name.IsEmpty())
					{
						int	focode = WhichFOCode(code.operator LPCTSTR());
						switch (focode)
						{
						case foOption:
							if (m_iDtUnit != GU_OPTION)	
								ChangeUnit(GU_OPTION);	
							break;
						case foCoFut:
							if (m_iDtUnit != GU_COFUT)	
								ChangeUnit(GU_COFUT);	
							break;
						case foCoOpt:
							if (m_iDtUnit != GU_COOPT)	
								ChangeUnit(GU_COOPT);	
							break;
						case foFuture:
						default:
							if (m_iDtUnit != GU_FUTURE)	
								ChangeUnit(GU_FUTURE);	
							break;
						}
					}
				}
				break;
			}
		}
	}

	rtmStore.RemoveAll();
}

void CPnInput::SetTriggerCode()
{
	bool bFO = false;
	CString	trgSymbol, htySymbol;
	CString code = m_pCodeCB->GetEditData();
	switch(m_iDtUnit)
	{
	case GU_CODE:
		trgSymbol = JTRG;
		htySymbol = JTRG;
		break;
	case GU_FUTURE:	case GU_OPTION:	case GU_COFUT:	case GU_COOPT:	
		switch(WhichFOCode(code))
		{
		case foOption:
			trgSymbol = OTRG;
			htySymbol = OTRG;
			bFO = true;
			break;
		case foCoFut:
			trgSymbol = CFTRG;
			htySymbol = CFTRG;
			bFO = true;
			break;
		case foCoOpt:
			trgSymbol = COTRG;
			htySymbol = COTRG;
			bFO = true;
			break;
		case foFuture:
		default:
			trgSymbol = FTRG;
			htySymbol = FTRG;
			bFO = true;
			break;		
		}
		break;
	default:
		return;
	}

	CString	trgStr, htyStr;
	trgStr.Format("%s\t%s", trgSymbol, code);
	htyStr.Format("%s\t%s", htySymbol, code);

	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, setTrigger), long(trgStr.operator LPCTSTR()));
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, setHistory), long(htyStr.operator LPCTSTR()));

	if (bFO)	
	{
		htyStr.Format("%s\t%s", FOTRG, code);
		m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, setHistory), long(htyStr.operator LPCTSTR()));
	}
}

int CPnInput::WhichFOCode(LPCTSTR code)
{
	CString cd(code);
	if (cd.GetLength() != 8) return foNone;

	if ((cd[0] == '2' || cd[0] == '3'))
	{
		return foOption;
	}
	else if (cd[0] == '1')	// 1xxxxxxx
	{
		if (cd[1] >= '1')	// 11xxxxxx
			return foCoFut;
		else if (cd[2] == '3')
			return foStar;

		return foFuture;
	}
	else	// "4xxxxxxx	spread
	{
		return foFuture;
	}

	return foFuture;
}

CString CPnInput::GetHistory(int unit)
{
	CString	history = _T("");
	CString	symbol = _T("");
	switch (unit)
	{
	case GU_CODE:	
		symbol = JTRG;	break;
	case GU_INDEX:
		symbol = ITRG;	break;
	case GU_FUTURE:	case GU_OPTION:	case GU_COFUT:	case GU_COOPT:
		symbol = FOTRG;	break;
	case GU_FOREIGN:	
		symbol = STRG;	break;
	}

	if (unit == GU_FOREIGN) {
		history = m_pCodeCB->GetHistory(symbol);
		if (history.IsEmpty()) {
			history = "DJI@DJI ";
		}
	}
	else {
		history = (char *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getHistory), long(symbol.operator LPCTSTR()));
	}


	if (history.IsEmpty())
		return history;

	int	index = history.Find("\t");
	if (index <= 0)	return history;

	CString	Str = history.Left(index);

	index = Str.Find(" ");
	if (index > 0)
	{
		CString	code = Str.Left(index);
		return code;
	}

	return _T("");
}

void CPnInput::OnClickedToday()
{	// click today
	NotifyToday(m_pchbToday->GetCheck()? true:false);
}

void CPnInput::DrawUnitButton(CDC* dc, CRect rc)
{
	dc->SetBkMode(TRANSPARENT);

	CString	sName = "";
	switch (m_iDtUnit)
	{
	case GU_CODE:		sName = "주식";	break;
	case GU_INDEX:		sName = "업종";	break;
	case GU_FUTURE:		sName = "선옵";	break;
	case GU_FOREIGN:	sName = "해외";	break;
	}
	dc->DrawText(sName, -1, rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

void CPnInput::OnChangeUnit()
{
	if (m_iDtUnit == GU_FOREIGN && (m_iDtIndex == GI_MINUTE || m_iDtIndex == GI_TICK))
		ChangeIndex(GI_DAY, true, true, false);
}

CString CPnInput::GetIndexCode(int indexCode)
{
	CString format, code;
	format.Format("%%0%dd", sz_INDEX);
	code.Format(format, indexCode);
	return code;			
}

CString CPnInput::GetSiseName()
{
	CString name = (LPCTSTR)
		m_pwndGView->SendMessage(GEV_SISE, MAKEWPARAM(siseData, siseName));

	return name;
}

void CPnInput::SetIndexCode(CString& code)
{
	code = GetIndexCode(1);
}

void CPnInput::SetIndexTrigger(CString& domino)
{
	domino = domino.Right(sz_INDEX);

	int	kkind = atoi(domino);
	m_pCodeCB->SetKkind(kkind);
}


LRESULT CPnInput::OnMultiEvent(WPARAM wParam, LPARAM lParam)
{
	switch(HIWORD(wParam))
	{
	case GetMergeCtrl:
		return int(m_merge);
	case GetTodayCheck:
		return m_pchbToday->GetCheck();
	case SetTodayCheck:
		m_pchbToday->SetCheck(lParam);
		break;
	case ChangeChart:
		OnChangeChart();
		break;
	}

	return 0L;
}

void CPnInput::NotifyToday(bool bSet)
{	// 당일 체크 변경
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, todayInput), bSet);
}

void CPnInput::NotifyIndexChange()
{	// 일주월분틱..갭 변경
	int	gap = 0;
	switch(m_iDtIndex)
	{
	case GI_MINUTE:	gap = m_iMGap;	break;
	case GI_TICK:	gap = m_iTGap;	break;
	default:	break;
	}
	
	// Notify Index(ChangeIndex, ChangeGap)
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, indexInput), MAKELPARAM(m_iDtIndex, gap));
}

void CPnInput::NotifyMultiCodeChange()
{	// 복수코드 변경
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeMultiInput), int(m_strMultiCode.operator LPCTSTR()));
}

void CPnInput::NotifyCodeChange()
{	// 코드 변경
	CString	code = m_pCodeCB->GetEditData();
	SetTriggerCode();
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, codeInput), int(code.operator LPCTSTR()));
}

void CPnInput::NotifyGiganChange(int iGigan)
{	// 기간 변경
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, totalInput), iGigan);
}

void CPnInput::NotifyGiganChange2(int *pGigan)
{	// 기간 변경 창에서 변경할 경우
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, total2Input), int(pGigan));
}

void CPnInput::NotifyMatrixChange(LPARAM lParam)
{	// 신규 메트릭스
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, matrixInput), lParam);
}

void CPnInput::NotifyMatrixChange2(char *pMatrix)
{	// 메트릭스 병합
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, matrix2Input), int(pMatrix));
}

void CPnInput::NotifySelect(bool bSelect)
{	// 체크 박스
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, selectInput), bSelect);
}

void CPnInput::NotifyFocus()
{	// 집중분석
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, focusInput), 0);
}

void CPnInput::NotifyOrder(int mIndex, _ActiveChartInfo *pActiveChartInfo)
{	// 주문버튼(팝업메뉴 매도,매수,정정,취소,번개), 주식,선물/옵션에 대해 각각 처리
	CString	sMap = "";
	CString	sSymbol = "";
	CString	sCode = pActiveChartInfo->acCode;
	switch (pActiveChartInfo->iUnit)
	{
	case GU_CODE:	
		sSymbol = JTRG;		// 주식심볼
		switch (mIndex)
		{
		case 0:	sMap = "IB101100";	break;	
		case 1:	sMap = "IB101200";	break;	
		case 2:	sMap = "IB101300";	break;	
		case 3:	sMap = "IB101400";	break;	
		case 4:	sMap = "IB100300";	break;	
		}
		break;
	default:
		if (sCode == "99999999")	// 연결선물이므로...선물 최근월을 가져옴
			sCode = (char*) m_pwndView->SendMessage(WM_USER, MAKEWPARAM(codeDLL, getCODEfuture), 0);

		sSymbol = "ed_focod";		// 선물옵션 심볼
		switch (mIndex)
		{
		case 0:	sMap = "IB301100";	break;
		case 1:	sMap = "IB301200";	break;
		case 2:	sMap = "IB301300";	break;
		case 3:	sMap = "IB301400";	break;
		case 4:	sMap = "IB300200";	break;
		}
		break;
	}

	CString	msg;
	msg.Format("%s/s/p5/d%s\t%s", sMap, sSymbol, sCode);
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, openView), int(msg.operator LPCTSTR()));
}

void CPnInput::NotifyInit()
{	// 전체 차트 초기화
	m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, initAllChart), 0);
}

LRESULT CPnInput::OnTableMake(WPARAM wParam, LPARAM lParam)
{
	m_merge->Initialize();
	m_merge->SetSize(LOWORD(wParam), HIWORD(wParam));
	NotifyMatrixChange(wParam);
	return 0L;
}

LRESULT CPnInput::OnCellMerge(WPARAM wParam, LPARAM lParam)
{
	CString	sTable = m_merge->GetMergeString();
	NotifyMatrixChange2((char*)sTable.operator LPCTSTR());
	return 0L;
}

void CPnInput::OnButtonTableClick(_comp* comp)
{
	CRect rc = comp->cRC;
	ClientToScreen(rc);

	m_table->Create(this, rc.left, rc.bottom);
}

void CPnInput::OnButtonCellClick(_comp* comp)
{
	CRect rc = comp->cRC;
	ClientToScreen(rc);

	_MultiChart *pMultiInfo = (_MultiChart *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMultiInfo), 0);
	m_merge->SetMergeString(pMultiInfo->acMatrix);
	m_merge->Create(this, rc.left, rc.bottom);
}

void CPnInput::OnButtonCheckClick()
{
	m_bCheckOn = !m_bCheckOn;
	NotifySelect(m_bCheckOn);
}

void CPnInput::OnFocusClick()
{
	int	pID[5] = { BTN_DDAY, BTN_DWEEK, BTN_DMON, BTN_DMIN, BTN_DTICK};
	for (int ii = 0; ii < 5; ii++)
	{
		struct _comp* comp = SearchCom(pID[ii]);
		if (comp && comp->status != btnUp)
			InvalidateCom(comp, btnUp);
	}

	NotifyFocus();
}

void CPnInput::OnMultiGiganClick()
{
	_MultiChart *pMultiChart = (_MultiChart *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getMultiInfo), 0);
	if (!pMultiChart)	return;

	CMultiGiganDlg	dlg(pMultiChart);
	if (dlg.DoModal() == IDOK)
		NotifyGiganChange2(pMultiChart->acGigan);
}

void CPnInput::OnOrderClick(_comp *comp)
{
	_ActiveChartInfo	*pActiveChartInfo = 
		(_ActiveChartInfo *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeInfo), 0);

	if (!pActiveChartInfo || (pActiveChartInfo->iUnit == GU_INDEX || pActiveChartInfo->iUnit == GU_FOREIGN) ||
		(strlen(pActiveChartInfo->acCode) <= 3))	
		return;

	const char *orders[] = { "매도주문", "매수주문", "정정주문", "취소주문", "클릭주문"};

	CMenu menu;
	menu.CreatePopupMenu();
	for (int i = 0; i < (sizeof(orders) / sizeof(orders[0])); i++) 
		menu.AppendMenu(MF_STRING, i + 1, orders[i]);

	CRect rc = comp->cRC;
	ClientToScreen(rc);

	int choice = -1 + menu.TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RETURNCMD, rc.left, rc.bottom, this, NULL);
	if (choice >= 0 && choice < (sizeof(orders) / sizeof(orders[0]))) 
		NotifyOrder(choice, pActiveChartInfo);
}

void CPnInput::OnChangeChart()
{
	_ActiveChartInfo	*pActiveChartInfo = 
		(_ActiveChartInfo *)m_pwndGView->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeInfo), 0);

	if (!pActiveChartInfo)
		return;

	if (m_mType <= MT_MULTI || pActiveChartInfo->iUnit == GU_CODE)
	{
		int	unit = pActiveChartInfo->iUnit;
		if (pActiveChartInfo->iUnit == GU_OPTION)	unit = GU_FUTURE;

		m_pCodeCB->SetEditData("");
		if (unit != m_iDtUnit)
			ChangeUnit(unit, false);

		if (strlen(pActiveChartInfo->acCode) > 3)
		{
			m_pCodeCB->SetEditData(pActiveChartInfo->acCode);
			m_pCodeCB->SetFocus();
			m_strValidCode.Format("%s", pActiveChartInfo->acCode);
		}
	}

	m_iMGap = pActiveChartInfo->iMGap;
	m_iTGap = pActiveChartInfo->iTGap;
	ChangeIndex(pActiveChartInfo->iIndex, true, true, false);
	if (pActiveChartInfo->iRCnt > 0)
	{
		int	rcnt = (pActiveChartInfo->iRCnt > MAX_DATA_COUNT)? MAX_DATA_COUNT:pActiveChartInfo->iRCnt;
		CString	str;
		str.Format("%d", rcnt);
		m_pGiganCB->SetWindowText(str);
	}
}

extern struct _combo CUnit[4];
const char *units[] = { "주식", "선옵"};

int UnitIndex(int unit)
{
	switch (unit) {
	case GU_CODE: return 0;
	case GU_FUTURE: return 1;
	}
	return -1;
}

int IndexUnit(int index)
{
	switch (index) {
	case 0: return GU_CODE;
	case 1: return GU_FUTURE;
	}
	return 0;
}

int CPnInput::FindUnit(int index)
{
	return CUnit[index].val;
}

void CPnInput::ChangeUnitAndCode(LPCTSTR param)
{
	CString str(param);

	int find = str.Find(';');
	if (find < 0) return;

	int choice, unit = atoi(str.Left(find));
	CString code = str.Right(str.GetLength() - (find + 1));

	code.TrimRight();
	if (unit != 1 && unit != 2)
	{
		if (code.IsEmpty())
			return;

		char	pCode[128];
		sprintf(pCode, "%s", code);
		CString	name = (char*)m_pwndView->SendMessage(WM_USER, nameDLL, long(pCode));
		if (name.IsEmpty())
			return;
	}

	if (code.GetLength() == 6 && atoi(code) > 0) 
		choice = 0;
	else if (code.GetLength() == 8 && atoi(code.Left(3)) > 0) 
		choice = 1;
	else 
		return;

	if (m_mType == MT_FOREIGN || (m_mType == MT_MONITOR && choice != 0))
		return;
	
	unit = FindUnit(choice);

	if (choice >= 0 && choice < (sizeof(units) / sizeof(units[0]))) 
	{
		if (choice != UnitIndex(m_iDtUnit)) 
		{
			int unit = FindUnit(choice);
			ChangeUnit(unit);
		}
	}

	m_pCodeCB->SetEditData(code);
	m_pCodeCB->SetFocus();

	m_strValidCode.Format("%s", code);

	NotifyCodeChange();
}


void CPnInput::OnButtonUnitClick(_comp* comp)
{
	int index = UnitIndex(m_iDtUnit);

	CMenu menu;
	menu.CreatePopupMenu();
	for (int i = 0; i < (sizeof(units) / sizeof(units[0])); i++) 
		menu.AppendMenu(MF_STRING | (i == index ? MF_CHECKED: 0), i + 1, units[i]);

	CRect rc = comp->cRC;
	ClientToScreen(rc);

	int choice = -1 + menu.TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RETURNCMD, rc.left, rc.bottom, this, NULL);
	if (choice >= 0 && choice < (sizeof(units) / sizeof(units[0]))) 
	{
		if (choice != index) 
			ChangeUnit(IndexUnit(choice));
	}
}

CString CPnInput::GetCurrentUnit()
{
	int index = UnitIndex(m_iDtUnit);
	if (index >= 0 && index < ARRAY_SIZE(units)) 
		return units[index];
	else
		return "";
}

void CPnInput::CheckComboSel()
{
	if (m_pGapCB && !m_pGapCB->IsFocusWnd())
	{
		CString	str;
		m_pGapCB->GetWindowText(str);
		m_pGapCB->SetWindowText("");
		m_pGapCB->SetWindowText(str);
	}
	if (m_pGiganCB && !m_pGiganCB->IsFocusWnd())
	{
		CString	str;
		m_pGiganCB->GetWindowText(str);
		m_pGiganCB->SetWindowText("");
		m_pGiganCB->SetWindowText(str);
	}
}
