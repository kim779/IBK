// PnInput.cpp : implementation file
//

#include "stdafx.h"
#include "axisGMTotal.h"
#include "PnInput.h"
#include "PnWndCombo.h"
#include "CheckBox.h"
#include "MainWnd.h"
#include "ExtraMsg.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPnInput
struct _info	infoInput[] = {
	{ CHK_SELECT,   0, 0, 0, 0, "", ""},	// check box
	{ STC_JNAME,	0, 0, 0, 0,	"", "" },	// name
	{ CMB_TIME,	0, 0, 0, 0,	"", "" },
	{ BTN_DDAY,	0, 1, 2, 0,	"", "" },
//	{ BTN_DWEEK,	0, 1, 2, 0,	"", "" },
//	{ BTN_DMON,	0, 1, 2, 0,	"", "" },
//	{ BTN_DMIN,	0, 1, 2, 0,	"", "" },
//	{ BTN_DTICK,	0, 1, 2, 0,	"", "" },
//	{ BTN_MENU,	0, 1, 2, 0,	"환경설정", "환경설정" },
};

#define	GAP1	1
#define	GAP2	5
#define	GAP3	10
#define	GAP4	30

CPnInput::CPnInput(CWnd *pView, CWnd* pParent, CFont* pFont, int ctrlID, char* info)
: CPnBaseWnd(pView, pParent, pFont, ctrlID, info)
{
	m_pNTimeImage = NULL;
	m_pIOptImage = NULL;

	m_pchbSelect = NULL;
	m_pGapCB = NULL;
	m_pToolTip = NULL;

	m_pMainWnd = (CMainWnd *)pParent;
	m_pApp = (CAxisGMTotalApp *)AfxGetApp();
	m_pBtnFont = m_pApp->GetFont(pView, 9, "돋움");

	m_bInitResize = true;
	m_bMouseIN = FALSE;
	m_bLButton = false;
	m_moveID = 0;
	m_selID = -1;

	struct _envInfo	*envinfo = (struct _envInfo*)info;
	SetGapValue(envinfo->datainfo.acIGap);
}

CPnInput::~CPnInput()
{
}


BEGIN_MESSAGE_MAP(CPnInput, CPnBaseWnd)
	//{{AFX_MSG_MAP(CPnInput)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(GEV_INPUT, OnInputEvent)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_BN_CLICKED(CHK_SELECT, OnClickedSelect)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPnInput message handlers
LRESULT CPnInput::OnInputEvent(WPARAM wParam, LPARAM lParam)
{
	CString	tmpS;
	switch (LOWORD(wParam))
	{
	case INPUT_GET_POS_COMMENT:
		m_comment = GetPosComment(CPoint(LOWORD(lParam), HIWORD(lParam)));
		return (LRESULT)(LPCTSTR)m_comment;
	case INPUT_CHANGE:
		switch (HIWORD(wParam))
		{
		case ipUnit:
			MakeInputSymbol();
			if (m_pMainWnd->m_iDtUnit == GU_FOREIGN && 
				(m_pMainWnd->m_iDtIndex == GI_MINUTE || m_pMainWnd->m_iDtIndex == GI_TICK))
				ChangeIndex(GI_DAY, true, true, true);
			else if ((m_pMainWnd->m_iDtUnit == GU_FUTURE || m_pMainWnd->m_iDtUnit == GU_OPTION || m_pMainWnd->m_iDtUnit == GU_COFUT || m_pMainWnd->m_iDtUnit == GU_COOPT) && 
				(m_pMainWnd->m_iDtIndex == GI_WEEK || m_pMainWnd->m_iDtIndex == GI_MONTH))
				ChangeIndex(GI_DAY, true, true, true);

			break;
		case ipGap:	// time button change
			ChangeGap(m_pMainWnd->m_iDtIndex, lParam);
			if (!m_pMainWnd->m_strCode.IsEmpty())
				m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewInterface, requestTR), 0);
			break;
		case INPUT_BUTTON:
			if (!m_pMainWnd->m_strCode.IsEmpty())
				m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewInterface, requestTR), 0);
			break;
		}

		break;
	case INPUT_DATA:
		switch (HIWORD(wParam))
		{
		case GET_TR_INFO:
			return GetTRInfo((char *)lParam);
		case getTRInfo2:
			return GetTRInfo2((char *)lParam);
		case GET_TOTAL_DAY:
			break;
		case getDispDay:
			{
				struct _envInfo	*envinfo = (_envInfo*)m_pParent->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);

				int	uIndex = 0;
				switch (m_pMainWnd->m_iDtUnit)
				{
				case GU_FUTURE:	case GU_OPTION:	case GU_COFUT:	case GU_COOPT:
					uIndex = GU_FUTURE - GU_CODE;
					break;
				case GU_CODE:	case GU_INDEX:	
					uIndex = m_pMainWnd->m_iDtUnit - GU_CODE;
					break;
				case GU_FOREIGN:
					uIndex = 3;
					break;
				default:
					break;
				}
				return envinfo->datainfo.aaDayInfo[uIndex][m_pMainWnd->m_iDtIndex-GI_DAY].dwDisCnt;
			}
			break;
		case getCalendar:
			sprintf((char*)lParam, "%s", m_pMainWnd->m_strDay);
			break;
		case getCurGapList:
			{
				char	*pVal = (char*)lParam;
				for (int ii = 0; ii < 4; ii++)	pVal[ii] = m_gap[ii];
			}
			break;
		case setCodeInfo:	break;
		case domminoCode:	break;
		case triggerCode:	break;
		case isDollarData:	return FALSE;
		case isTodayData:	return FALSE;
		case GET_VALID_CODE:	return (long)m_pMainWnd->m_strCode.operator LPCTSTR();
		}
		break;
	case inputEnv:		break;
	case inputViewFocus:	break;
	case inputChgPalette:
		m_clrBack = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 68);
		m_clrUpSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 94);
		m_clrDnSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 95);
		m_clrEqSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 97);
		Invalidate();
		break;
	case InputMulti:
		switch(HIWORD(wParam))
		{
		case getCheckBox:
			return m_pchbSelect->GetCheck();
		case setCheckBox:
			m_pchbSelect->SetCheck(lParam);
			break;
		case inputSiseUpdate:	// sise update
			InvalidateRect(&m_rcSise);
			break;
		case inputIndex:
			ChangeIndex(LOWORD(lParam), false, true, false);
			ChangeGap(LOWORD(lParam), HIWORD(lParam), false);
			break;
		}
	default:	
		break;
	}

	return FALSE;
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

int CPnInput::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPnBaseWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	m_clrBack = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 68);
	m_clrFrame = PALETTERGB(193, 213, 234); 

	m_clrUpSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 94);
	m_clrDnSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 95);
	m_clrEqSise = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), 97);

	m_pchbSelect = new CCheckBox;
	m_pchbSelect->Create("", NULL, CRect(0, 0, 10, 10), this, CHK_SELECT, m_pFont);
	m_pchbSelect->SetColorBG(m_clrBack);

	CString tmps;
	COLORREF bg, fg;
	tmps.Format("%s/%s/%s", ((CAxisGMTotalApp *)AfxGetApp())->GetRoot(), TABDIR, PALETTE);
	bg = GetPrivateProfileInt(GENERALSN, "ComboBg", -1, tmps);
	fg = GetPrivateProfileInt(GENERALSN, "ComboFg", -1, tmps);
	bg = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), bg);
	fg = m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMain, getPalette), fg);

	int	cmbOption = WS_VISIBLE|WS_CHILD|WS_VSCROLL|CBS_DROPDOWN;
	m_pGapCB = new CPnWndCombo(this, m_pParent, CMB_TIME);
	m_pGapCB->Create(cmbOption, CRect(0, 0, 10, 10), this, 5);
	m_pGapCB->SetComboPalette(bg, fg);
	m_pGapCB->SetFont(m_pFont);
	m_pGapCB->AddString("1");	m_pGapCB->AddString("2");
	m_pGapCB->AddString("5");	m_pGapCB->AddString("10");
	m_pGapCB->AddString("15");	m_pGapCB->AddString("30");

	m_pToolTip = new CPnToolTip(m_pView, this, GEV_INPUT);
	m_pToolTip->Create(m_pFont);
	
	CString	path = m_pApp->GetImagePath(m_pParent, NTIMEIMAGE);
	m_pNTimeImage = m_pApp->GetImage(imgNTime, path);
	path = m_pApp->GetImagePath(m_pParent, IOPTIMAGE);
	m_pIOptImage = m_pApp->GetImage(imgIOpt, path);

	CDC	*pDC = GetDC();
	CFont	*sFont = pDC->SelectObject(m_pFont);
	m_szHangul = pDC->GetOutputTextExtent("한");
	m_szNumeric = pDC->GetOutputTextExtent("9");
	pDC->SelectObject(sFont);
	ReleaseDC(pDC);

	MakeInputSymbol();

	if (m_pMainWnd->m_iType == MT_FOREIGN || m_pMainWnd->m_iDtUnit == GU_FOREIGN)	// type 4번은 일/주/월만 있다
		m_pGapCB->EnableWindow(FALSE);

	return 0;
}

void CPnInput::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CMemDC	mdc(&dc);
	OnDraw(&mdc);
//	OnDraw(&dc);
}

const COLORREF	clrRED	= PALETTERGB(255, 0, 0);
const COLORREF	clrBLUE	= PALETTERGB(0, 0, 255);
const COLORREF	clrGREEN = PALETTERGB(10,142,0);
void CPnInput::OnDraw(CDC *pDC)
{
	DrawBackground(pDC);

	CString	str;
	CFont		*sFont = pDC->SelectObject(m_pFont);
	COLORREF	sColor = pDC->SetTextColor(m_clrEqSise);//RGB(0,0,0));
	COLORREF	sbkColor = pDC->SetBkColor(m_clrBack);

	COLORREF	color;
	pDC->DrawText(m_pMainWnd->m_strJName, m_pMainWnd->m_strJName.GetLength(), &m_rcSise, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	CSize sz = pDC->GetOutputTextExtent(m_pMainWnd->m_strJName);
	if (!m_pMainWnd->m_pExtraMsg->m_curr.IsEmpty() && !m_pMainWnd->m_pExtraMsg->m_udyl.IsEmpty())
	{
		CRect	rc = m_rcSise;
		rc.left += sz.cx + 5;
		rc.right = m_rcIndex.right;
		if (m_pMainWnd->m_pExtraMsg->m_curr.GetAt(0) == '+' || m_pMainWnd->m_pExtraMsg->m_curr.GetAt(0) == '-')
		{
			color = parseSymbol(m_pMainWnd->m_pExtraMsg->m_curr.GetAt(0));
			sColor = pDC->SetTextColor(color);
			str = editComma(atof(m_pMainWnd->m_pExtraMsg->m_curr.Mid(1)), 
				m_pMainWnd->m_iDtUnit == GU_CODE || m_pMainWnd->m_iDtUnit == GU_COFUT || m_pMainWnd->m_iDtUnit == GU_COOPT);
		}
		else
		{
			sColor = pDC->SetTextColor(m_clrEqSise);//clrGREEN);
			str = editComma(atof(m_pMainWnd->m_pExtraMsg->m_curr), 
				m_pMainWnd->m_iDtUnit == GU_CODE || m_pMainWnd->m_iDtUnit == GU_COFUT || m_pMainWnd->m_iDtUnit == GU_COOPT);
		}
		pDC->DrawText(str, str.GetLength(), &rc, DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		sz = pDC->GetOutputTextExtent(str);
		rc.left += sz.cx + 5;
		str = m_pMainWnd->m_pExtraMsg->m_udyl + "%";
		pDC->DrawText(str, str.GetLength(), &rc, DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		pDC->SetTextColor(sColor);
	}

	pDC->SetBkColor(sbkColor);
	pDC->SetTextColor(sColor);
	pDC->SelectObject(sFont);

	for (int ii = 0; ii < m_arComs.GetSize(); ii++)
	{
		_comp *comp = m_arComs.GetAt(ii);
		if (comp->cID == BTN_DDAY)
			DrawButton(pDC, comp);
	}
}

COLORREF CPnInput::parseSymbol(char sign)
{
	COLORREF color;
	switch (sign)
	{
	case 1:
	case '1':
		color = m_clrUpSise;//clrRED;
		break;
	case 2:
	case '2':
	case '+':
		color = m_clrUpSise;//clrRED;
		break;
	case 4:
	case '4':
		color = m_clrDnSise;//clrBLUE;
		break;
	case 5:
	case '5':
	case '-':
		color = m_clrDnSise;//clrBLUE;
		break;
	default:
		color = m_clrEqSise;//clrGREEN;
		break;
	}

	return color;
}

CString CPnInput::editComma(double dVal, bool bCode)
{
	CString tmpS = _T("");
	if (dVal == 0.0)
	{
		if (bCode)
			tmpS = _T("0");
		else
			tmpS = _T("0.00");
		return tmpS;
	}

	CString dotRight;
	
	bool bMinus = (dVal < 0) ? true : false;
	double val = (dVal > 0) ? dVal:-dVal;
	
	CString tmp;
	
	if (bCode)
		tmp.Format("%.0f", val);
	else
		tmp.Format("%.2f", val);

	int find = tmp.Find('.');
	if (find > 0)  {
		dotRight = tmp.Right(tmp.GetLength() - (find));
		tmp = tmp.Left(find);
	}
	else {
		dotRight.Empty();
	}

	int idx = 0, jj = 1;
	for (int ii = tmp.GetLength() - 1; ii >= 0 ;ii--, jj++)
	{
		tmpS.Insert(0, tmp.GetAt(ii));
		if (jj % 3 == 0 && ii > 0)
			tmpS.Insert(0, ",");
	}
	if (bMinus)
		tmpS = "-" + tmpS;

	tmpS += dotRight;
	return tmpS;
}

void CPnInput::DrawButton(CDC* pDC, struct _comp *comp)
{
	CRect cRC = comp->cRC;
	CPoint imgPt = CPoint(cRC.left, cRC.top);

	CString	tmpS = _T("");

	switch (m_pMainWnd->m_iDtIndex)
	{
	case GI_DAY:	tmpS.Format("일");	break;
	case GI_WEEK:	tmpS.Format("주");	break;
	case GI_MONTH:	tmpS.Format("월");	break;
	case GI_MINUTE:	tmpS.Format("분");	break;
	case GI_TICK:	tmpS.Format("틱");	break;
	default:
		break;
	}

	CPnBaseWnd::DrawButton(pDC, dtButton, comp, m_pNTimeImage);

	cRC.DeflateRect(1, 1, 1, 1);
	int mode = pDC->SetBkMode(TRANSPARENT);
	CFont	*sFont = pDC->SelectObject(m_pBtnFont);
	if (!tmpS.IsEmpty())
		pDC->DrawText(tmpS, cRC, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SetBkMode(mode);
	pDC->SelectObject(sFont);
}

void CPnInput::OnDestroy() 
{
	if (m_pchbSelect)	WND_DELETE(m_pchbSelect);
	if (m_pGapCB)		WND_DELETE(m_pGapCB);
	if (m_pToolTip)		WND_DELETE(m_pToolTip);

	CPnBaseWnd::OnDestroy();
}

void CPnInput::OnSize(UINT nType, int cx, int cy) 
{
	CPnBaseWnd::OnSize(nType, cx, cy);
	
	if (cx == 0 && cy == 0)
		return;

	if (m_bInitResize)
	{
		m_bInitResize = false;
		SetInfo(CRect(0, 0, cx, cy));
		arrangeCtrl(CRect(0, 0, cx, cy));

		ChangeIndex(m_pMainWnd->m_iDtIndex);
		ReadDisplay(m_pMainWnd->m_iDtIndex);

		if (m_pMainWnd->m_iDtUnit == GU_FOREIGN && (m_pMainWnd->m_iDtIndex == GI_MINUTE || m_pMainWnd->m_iDtIndex == GI_TICK))
			ChangeIndex(GI_DAY, true, true, true);
	}

	arrangeCtrl(CRect(0, 0, cx, cy), false);	
	if (m_pGapCB && !m_pGapCB->IsFocusWnd())
	{
		CString	str;
		m_pGapCB->GetWindowText(str);
		m_pGapCB->SetWindowText("");
		m_pGapCB->SetWindowText(str);
	}
}

void CPnInput::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeView), 1);

	CPnBaseWnd::OnLButtonDown(nFlags, point);

	struct _comp* comp = SearchCom(point);
	if (!comp)
	{
		return;
	}
	m_bLButton = true;
	m_selID = comp->cID;

	InvalidateCom(comp, btnDown);
}

void CPnInput::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CPnBaseWnd::OnLButtonUp(nFlags, point);
	lbuttonup(point);
}

void CPnInput::lbuttonup(CPoint point)
{
	if (!m_bLButton)
		return;

	m_moveID = -1;
	m_bLButton = false;

	struct _comp* comp = SearchCom(point);
	if (comp)
		InvalidateCom(comp, btnUp);
	if (comp && comp->cID == BTN_DDAY)
		TrackingIndexMenu(point);

	comp = SearchCom(m_selID);
	if (comp)
		InvalidateCom(comp, btnUp);
}

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

	if (m_bLButton)
		return;

	CPoint	Orgpoint = point;
	struct _comp* mcomp = SearchCom(Orgpoint);
	if (!mcomp)
	{
		mcomp = SearchCom(m_moveID);
		if (mcomp)
			InvalidateCom(mcomp, btnUp);
		m_moveID = -1;
		return;
	}

	if (m_moveID == mcomp->cID)
		return;

	struct _comp* ocomp = SearchCom(m_moveID);
	if (ocomp)
		InvalidateCom(ocomp, btnUp);

	m_moveID = mcomp->cID;
	InvalidateCom(mcomp, btnMove);
}

void CPnInput::OnMouseLeave(UINT nFlags, CPoint point)
{
	if (m_bLButton)
	{
		lbuttonup(point);
	}
	else
	{
		struct _comp* mcomp = SearchCom(m_moveID);
		if (mcomp)
			InvalidateCom(mcomp, btnUp);
	}
	m_moveID = -1;
	m_bMouseIN = FALSE;

	if (m_pToolTip)
	{
		m_pToolTip->m_dispStr = _T("");
		m_pToolTip->hideToolTip();
	}
}

void CPnInput::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, activeView), 1);

	CPnBaseWnd::OnRButtonUp(nFlags, point);
}

void CPnInput::SetInfo(CRect wRC)
{
	int	size = sizeof(infoInput) / sz_INFO;

	wRC.DeflateRect(1, 1);
	int	left = wRC.left;
	int	top = wRC.top;
	int	bottom = wRC.bottom;
	int	Height = wRC.Height() - 2;

	int	right = wRC.right - (m_szNumeric.cx*3+8+Height + 1 + szDateImgX + 1);

	m_rcIndex = wRC;
	for (int ii = 0; ii < size; ii++)
	{
		_comp *comp = new _comp;
		ZeroMemory(comp, sz_COMP);

		comp->cID = infoInput[ii].kind;
		comp->status = btnUp;
		comp->bshow = true;
		comp->imggen = infoInput[ii].imggen;
		comp->imgmov = infoInput[ii].imgmov;
		comp->imgsel = infoInput[ii].imgsel;
		comp->imgdis = infoInput[ii].imgdis;
		CopyMemory(comp->str, infoInput[ii].disp, sizeof(infoInput[ii].disp));
		CopyMemory(comp->comment, infoInput[ii].com, sizeof(infoInput[ii].com));

		switch(comp->cID)
		{
		case CHK_SELECT:
			comp->cRC.SetRect(left, top + 3, left + m_szHangul.cx, bottom - 1);
			left += m_szHangul.cx + 3;
			break;
		case STC_JNAME:
			comp->cRC.SetRect(left, top, left+m_szHangul.cx*6, bottom);
			left += m_szHangul.cx*6 + 3;
			m_rcSise = comp->cRC;
			m_rcSise.right = right-1;
			break;
		case CMB_TIME:
			comp->cRC.SetRect(right, top, right+m_szNumeric.cx*3+8+Height, bottom+200);
			right += m_szNumeric.cx*3+8+Height + 1;
			break;
		case BTN_DDAY:
			m_rcIndex.left = right;
			comp->cRC.SetRect(right, top+1, right+szDateImgX, bottom-1);
			m_rcDAY = comp->cRC;
			break;
		case BTN_MENU:
			break;
		default:
			delete comp;
			continue;
		}
		m_arComs.Add(comp);
	}
}

void CPnInput::arrangeCtrl(CRect wRC, bool bChgIndex)
{
	struct _comp	*comp;
	wRC.DeflateRect(1, 1);
	int	left = wRC.left;
	int	top = wRC.top;
	int	bottom = wRC.bottom;
	int	Height = wRC.Height() - 2;

	int	right = wRC.right - (m_szNumeric.cx*3+8+Height + 1 + szDateImgX + 1);
	m_rcIndex = wRC;
	m_rcSise.right = right-1;
	int	size = m_arComs.GetSize();
	for (int ii = 0; ii < size; ii++)
	{
		comp = m_arComs.GetAt(ii);
		switch (comp->cID)
		{
		case CHK_SELECT:
			m_pchbSelect->MoveWindow(comp->cRC);
			break;
		case CMB_TIME:	
			comp->cRC.SetRect(right, top, right+m_szNumeric.cx*3+8+Height, bottom+200);
			right += m_szNumeric.cx*3+8+Height + 1;
			m_pGapCB->MoveWindow(comp->cRC);	break;
		case BTN_DDAY:
			comp->cRC.SetRect(right, top+1, right+szDateImgX, bottom-1);
			m_rcDAY = comp->cRC;
			break;
		case BTN_MENU:
			comp->cRC.left = left;
			comp->cRC.right = left + szIOptImgX;
			left += szIOptImgX + 1;
			break;
		default:
			break;
		}
	}
}

int CPnInput::GetTRInfo(char *pHeader)
{
	CString	codeS = _T("");
	switch (m_pMainWnd->m_iDtUnit)
	{
	case GU_CODE:	
		codeS = IJ_CODE;	break;
	case GU_INDEX:	
		codeS = II_CODE;	break;
	case GU_FUTURE:	
		codeS = IF_CODE;	break;
	case GU_OPTION:	
		codeS = IO_CODE;	break;
	case GU_FOREIGN: 
		codeS = IS_CODE;	break;
	case GU_COFUT:
		codeS = ICF_CODE;	break;
	case GU_COOPT:	
		codeS = ICO_CODE;	break; 
	default:	
		return 0;
	}
	sprintf(pHeader, "%s%c%s\t%s", codeS, 0x7F, m_pMainWnd->m_strCode, m_outSymbol);

	return strlen(pHeader);
}

int CPnInput::GetTRInfo2(char *pHeader)
{
	CString	codeS = _T("");
	switch (m_pMainWnd->m_iDtUnit)
	{
	case GU_CODE:	
		codeS = IJ_CODE;	break;
	case GU_INDEX:	
		codeS = II_CODE;	break;
	case GU_FUTURE:	
		codeS = IF_CODE;	break;
	case GU_OPTION:	
		codeS = IO_CODE;	break;
	case GU_FOREIGN: 
		codeS = IS_CODE;	break;
	case GU_COFUT:
		codeS = ICF_CODE;	break;
	case GU_COOPT:	
		codeS = ICO_CODE;	break; 
	default:	
		return 0;
	}
	sprintf(pHeader, "%s%c%s\t", codeS, 0x7F, m_pMainWnd->m_strCode);

	return strlen(pHeader);
}

void CPnInput::MakeInputSymbol()
{
	switch (m_pMainWnd->m_iDtUnit)
	{
	case GU_CODE:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OJ_TIME, OJ_NAME, OJ_JGGA, OJ_DIFF, OJ_RATE, OJ_GVOL, OJ_MDHG, OJ_MSHG, 
			OJ_SIGA, OJ_KOGA, OJ_JEGA,
			OJ_CODE, OJ_CDAY, OJ_SAHG, OJ_HAHG, OJ_JJGA, OJ_STCK);
		break;
	case GU_INDEX:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OI_TIME, OI_NAME, OI_JGGA, OI_DIFF, OI_RATE, OI_GVOL, OI_MDHG, OI_MSHG, 
			OI_SIGA, OI_KOGA, OI_JEGA,
			OI_CODE, OI_CDAY, OI_SAHG, OI_HAHG, OI_JJGA, OI_STCK);
		break;
	case GU_FUTURE:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OF_TIME, OF_NAME, OF_JGGA, OF_DIFF, OF_RATE, OF_GVOL, OF_MDHG, OF_MSHG, 
			OF_SIGA, OF_KOGA, OF_JEGA, OF_MGJY,
			OF_CODE, OF_CDAY, OF_SAHG, OF_HAHG, OF_JJGA, OF_STCK);
		break;
	case GU_OPTION:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OO_TIME, OO_NAME, OO_JGGA, OO_DIFF, OO_RATE, OO_GVOL, OO_MDHG, OO_MSHG, 
			OO_SIGA, OO_KOGA, OO_JEGA, OO_MGJY,
			OO_CODE, OO_CDAY, OO_SAHG, OO_HAHG, OO_JJGA, OO_STCK);
		break;
	case GU_FOREIGN:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OS_TIME, OS_NAME, OS_JGGA, OS_DIFF, OS_RATE, OS_GVOL, OS_MDHG, OS_MSHG,
			OS_SIGA, OS_KOGA, OS_JEGA, 
			OS_CODE, OS_CDAY, OS_SAHG, OS_HAHG, OS_JJGA, OS_STCK);
		break;
	case GU_COFUT:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OCF_TIME, OCF_NAME, OCF_JGGA, OCF_DIFF, OCF_RATE, OCF_GVOL, OCF_MDHG, OCF_MSHG, 
			OCF_SIGA, OCF_KOGA, OCF_JEGA, OCF_MGJY,
			OCF_CODE, OCF_CDAY, OCF_SAHG, OCF_HAHG, OCF_JJGA, OCF_STCK);
		break;
	case GU_COOPT:
		m_outSymbol.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			OCO_TIME, OCO_NAME, OCO_JGGA, OCO_DIFF, OCO_RATE, OCO_GVOL, OCO_MDHG, OCO_MSHG, 
			OCO_SIGA, OCO_KOGA, OCO_JEGA, OCO_MGJY,
			OCO_CODE, OCO_CDAY, OCO_SAHG, OCO_HAHG, OCO_JJGA, OCO_STCK);
		break;
	}
}

void CPnInput::ReadDisplay(int index)
{
	struct _envInfo	*envinfo = (_envInfo*)m_pParent->SendMessage(GEV_CHART, MAKEWPARAM(CHART_DATA, REQUEST_CUR_ENV), 0);
}

void CPnInput::ChangeIndex(int index, bool bChgGap, bool bRedraw, bool bMessage)
{
	int	id = -1;

	if (bRedraw)
	{
		InvalidateRect(&m_rcDAY);

		ReadDisplay(index);
		if (index == GI_MINUTE)
		{
			m_pGapCB->ResetContent();
			m_pGapCB->AddString("0.5");
			m_pGapCB->AddString("1");	m_pGapCB->AddString("2");
			m_pGapCB->AddString("3");	m_pGapCB->AddString("5");
			m_pGapCB->AddString("10");	m_pGapCB->AddString("15");
			m_pGapCB->AddString("20");	m_pGapCB->AddString("30");
			m_pGapCB->AddString("60");
		}
		else
		{
			m_pGapCB->ResetContent();
			m_pGapCB->AddString("1");	m_pGapCB->AddString("2");
			m_pGapCB->AddString("3");	m_pGapCB->AddString("5");
			m_pGapCB->AddString("10");	m_pGapCB->AddString("15");
			m_pGapCB->AddString("20");	m_pGapCB->AddString("30");
			m_pGapCB->AddString("60");
		}
	}

	if (bChgGap)
	{
		switch(index)
		{
		case GI_DAY:	case GI_WEEK:	case GI_MONTH:	
				ChangeGap(index, 0, false);	break;
		case GI_MINUTE:	ChangeGap(index, m_pMainWnd->m_iMGap, !bRedraw);	break;
		case GI_TICK:	ChangeGap(index, m_pMainWnd->m_iTGap, !bRedraw);	break;
		default:	break;
		}
	}
	else
	{
		if (bMessage)	NotifyIndexChange(index);
	}
}

void CPnInput::ChangeGap(int index, int gap, bool bOnlyChange)
{
	CString	sVal;
	if (gap == 930)
		sVal.Format("0.5");
	else
		sVal.Format("%d", gap);

	if (gap == 0)	sVal = "1";
	m_pGapCB->SetWindowText(sVal);

	if (gap > 0 && (index != GI_MINUTE && index != GI_TICK))
		index = GI_MINUTE;

	if (!bOnlyChange)
	{
		if (index == GI_MINUTE)		m_pMainWnd->m_iMGap = gap;
		else if (index == GI_TICK)	m_pMainWnd->m_iTGap = gap;

		NotifyIndexChange(index);
	}
}

void CPnInput::NotifyIndexChange(int index)
{
	int	gap = 0;
	switch(index)
	{
	case GI_MINUTE:	gap = m_pMainWnd->m_iMGap;	break;
	case GI_TICK:	gap = m_pMainWnd->m_iTGap;	break;
	default:	break;
	}
	
	m_pParent->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, indexInput), MAKELPARAM(index, gap));
	InvalidateRect(&m_rcDAY);
}

void CPnInput::SetGapValue(char *pGap)
{
	char	reserve[4] = { GAP1, GAP2, GAP3, GAP4};
	for (int ii = 0; ii < 4; ii++)
	{
		if (pGap[ii] <= 0 || pGap[ii] > 90)
			m_gap[ii] = reserve[ii];
		else
			m_gap[ii] = pGap[ii];
	}
}

const char *indexs[] = { "일", "주", "월", "분", "틱" };
void CPnInput::TrackingIndexMenu(CPoint pt)
{
	int index = m_pMainWnd->m_iDtIndex - GI_DAY;

	CMenu menu;
	menu.CreatePopupMenu();

	int	end = (sizeof(indexs) / sizeof(indexs[0]));
	if (m_pMainWnd->m_iType == MT_FOREIGN || m_pMainWnd->m_iDtUnit == GU_FOREIGN)
		end = 3;
	for (int i = 0; i < end; i++) 
	{
		menu.AppendMenu(MF_STRING | (i == index ? MF_CHECKED: 0), i + 1, indexs[i]);
	}

	ClientToScreen(&pt);

	int choice = -1 + menu.TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, this, NULL);

	if (choice >= 0 && choice < (sizeof(indexs) / sizeof(indexs[0]))) 
	{
		if (choice != index) 
		{
			ChangeIndex(choice+GI_DAY, true, true, true);
			SendMessage(GEV_INPUT, MAKEWPARAM(INPUT_CHANGE, INPUT_BUTTON), 0);
		}
	}
}

void CPnInput::OnClickedSelect()
{
}