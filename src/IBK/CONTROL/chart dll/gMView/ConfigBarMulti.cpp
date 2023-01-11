// ConfigBarMulti.cpp : implementation file
//

#include "stdafx.h"
#include "axisgmview.h"
#include "ConfigBarMulti.h"
#include "../../h/jmcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_MULTICOUNT (TMAX_COL * TMAX_ROW)
#define SEL_NONE	65535
/////////////////////////////////////////////////////////////////////////////
// CConfigBarMulti

CConfigBarMulti::CConfigBarMulti(CWnd* view, CWnd* parent, CFont* font, LPCTSTR info)
:CConfigBarPru(view, parent, font, info)
{
	m_multiCount = 0;
	m_autoPlay = FALSE;
	m_lastTimerID = 0;
}

CConfigBarMulti::~CConfigBarMulti()
{
}


BEGIN_MESSAGE_MAP(CConfigBarMulti, CConfigBarPru)
	//{{AFX_MSG_MAP(CConfigBarMulti)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigBarMulti message handlers

void CConfigBarMulti::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);
	switch (nIDEvent) 
	{
	case IDT_AUTOSTART:
		if (!SelectNextMultiItem())
			StopAutoPlay();
		else
			m_lastTimerID = IDT_AUTOPLAY;
		break;
	case IDT_AUTOPLAY:
		if (!SelectNextMultiItem())
			StopAutoPlay();
		else
			m_lastTimerID = nIDEvent;

		break;
	}
}

LRESULT CConfigBarMulti::OnAxAutoClick(WPARAM wParam, LPARAM lParam)
{
	CConfigBarPru::OnAxAutoClick(wParam, lParam);

	InitArray();
	return 0L;
}

LRESULT CConfigBarMulti::OnAxManualClick(WPARAM wParam, LPARAM lParam)
{
	LRESULT result = CConfigBarPru::OnAxManualClick(wParam, lParam);

	m_listKind->EnableWindow(TRUE);
	if (m_listKind->GetItemCount() > 0) {
		m_listKind->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_listKind->EnsureVisible(0, FALSE);
		m_listKind->SetItemState(0, 0, LVIS_SELECTED);
	}

	InitArray();

	return result;
}


LRESULT CConfigBarMulti::OnAxPlayButtonClick(WPARAM wParam, LPARAM lParam)
{
	if (m_btnPlay->GetDown()) {
		CConfigBarPru::OnAxPlayButtonClick(wParam, lParam);
		InitArray();
		m_autoPlay = TRUE;
	}
	else {
		if (m_arrSel.GetSize() == 0)
			InitArray();

		SelectNextMultiItem();
	}

	return 0L;
}

LRESULT CConfigBarMulti::OnAxReversePlayButtonClick(WPARAM wParam, LPARAM lParam)
{
	if (m_arrSel.GetSize() == 0)
		InitArray();

	SelectPrevMultiItem();
	return 0L;
}


LRESULT CConfigBarMulti::OnAxFFButtonClick(WPARAM wParam, LPARAM lParam)
{
	if (!SelectNextMultiItem()) {
		if (m_autoPlay) {
			StopAutoPlay();
		}
		else {
			InitArray();
		}
	}
	else {
		if (m_btnPause->GetDown()) {
			m_btnPause->SetDown(FALSE);
			ContinueAutoPlay();
		}
	}
	
	return 0L;
}

void CConfigBarMulti::InitArray()
{
	m_multiCount = m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getRotCnt));

	DWORD style = GetWindowLong(m_listKind->m_hWnd, GWL_STYLE);

	if (m_multiCount < 1)
		m_multiCount = 0;

	if (m_multiCount > 1)
		style &= ~LVS_SINGLESEL;
	else
		style |= LVS_SINGLESEL;
	SetWindowLong(m_listKind->m_hWnd, GWL_STYLE, style);

	m_codes.RemoveAll();
	UnselectListItem();
	m_arrSel.SetSize(MAX_MULTICOUNT);

	for (int i = 0; i < MAX_MULTICOUNT; i++) {
		m_arrSel[i] = SEL_NONE;
	}
}

void CConfigBarMulti::UnselectListItem()
{
	for (int i = 0; i < m_listKind->GetItemCount(); i++) {
		if (m_listKind->GetItemState(i, LVIS_SELECTED) & LVIS_SELECTED)
			m_listKind->SetItemState(i, 0, LVIS_SELECTED);
	}
}

BOOL CConfigBarMulti::SelectNextMultiItem()
{
	int lastIndex = -1;
	for (int i = 0; i < m_multiCount; i++) {
		if (m_arrSel[i] != SEL_NONE) {
			m_listKind->SetItemState(m_arrSel[i], 0, LVIS_SELECTED);
			lastIndex = m_arrSel[i];
		}
		else
			break;
	}

	m_multiCount = m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getRotCnt));

	int index = lastIndex, count = 0;

	m_codes.RemoveAll();
	for (i = 0; i < m_multiCount; i++) {
		index = GetNextCheckItem(index);
		if (index >= 0) {
			m_arrSel[i] = index;
			m_listKind->SetItemState(m_arrSel[i], LVIS_SELECTED, LVIS_SELECTED);
			m_listKind->EnsureVisible(index, FALSE);
			m_codes.Add(m_listKind->GetItemText(index, 0));
			Debug("(%s) %s %s", FindIndexCode((LPSTR)(LPCTSTR)m_listKind->GetItemText(index, 0)),
				m_listKind->GetItemText(index, 0), m_listKind->GetItemText(index, 1));
			count++;
		}
		else {
			m_arrSel[i] = SEL_NONE;
			break;
		}
	}

	if (count > 0) {
		m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, setMultiCode), (LPARAM)&m_codes);
	}

	return count;
}

void CConfigBarMulti::StopAutoPlay()
{
	CConfigBarPru::StopAutoPlay();

	if (m_auto->GetCheck() && !m_btnPlay->GetDown()) {
		if (m_autoPlay) {
			m_codes.RemoveAll();
			m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, inputAutotran), FALSE);

		}
		m_listKind->EnableWindow(TRUE);
		m_autoPlay = FALSE;

		if (!m_btnPause->GetDown())
			m_lastTimerID = 0;
	}
}

void CConfigBarMulti::StartAutoPlay()
{
	CConfigBarPru::StartAutoPlay();
	m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewNotify, inputAutotran), TRUE);
	m_listKind->EnableWindow(FALSE);
}

CString CConfigBarMulti::FindIndexCode(LPSTR code)
{
	struct hjcode* hj = m_group->GetHJCode();
	int count = m_group->GetHJCount();
	static	CString cd;
	int up = -1;

	for (int i = 0; i < count; i++) 
	{
		cd = &hj[i].code[1];
		if (!strcmp(code, cd)) 
		{
			switch (hj[i].kosd) 
			{
			case 0:		// KOSPI
				up = 0;
				break;
			case 10:	// KOSDAQ
				up = 200;
				break;
			case 30:	// FREEBOARD
				up = 600;
				break;
			default:
				break;
			}

			if (hj[i].ucds > 0 && hj[i].ucds != 99)
				up += hj[i].ucds;
			else
				up += hj[i].ucdm;
			break;
		}
	}

	if (up > 0) 
	{
		cd.Format("%03d", up);
		return cd;
	}
	else 
	{
		return "";
	}
}

void CConfigBarMulti::ContinueAutoPlay()
{
	Debug("Continue = AUTO(%d, %d), PAUSE(%d), TIMER(%d)", 
		m_auto->GetCheck(), m_autoPlay, m_btnPause->GetDown(), m_lastTimerID);
	if (m_auto->GetCheck() && !m_btnPause->GetDown() && m_autoPlay && m_lastTimerID) {
		SetTimer(m_lastTimerID, m_autoPlayInterval, NULL);
	}
}

BOOL CConfigBarMulti::SelectPrevMultiItem()
{
	int lastIndex = m_listKind->GetItemCount();

	for (int i = 0; i < m_multiCount; i++) {
		if (m_arrSel[i] != SEL_NONE) {
			m_listKind->SetItemState(m_arrSel[i], 0, LVIS_SELECTED);
			if (m_arrSel[i] == SEL_NONE || m_arrSel[i] < lastIndex)
				lastIndex = m_arrSel[i];
		}
		else {
			lastIndex = m_listKind->GetItemCount();
			break;
		}
	}

	m_multiCount = m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, getRotCnt));

	int index = lastIndex, count = 0;

	m_codes.RemoveAll();
	for (i = m_multiCount - 1; i >= 0; i--) {
		index = GetPrevCheckItem(index);
		if (index >= 0) {
			m_arrSel[i] = index;
			m_listKind->SetItemState(m_arrSel[i], LVIS_SELECTED, LVIS_SELECTED);
			m_listKind->EnsureVisible(index, FALSE);
			m_codes.InsertAt(0, m_listKind->GetItemText(index, 0));
			count++;
		}
		else {
			m_arrSel[i] = SEL_NONE;
			break;
		}
	}

	if (count > 0) {
		m_parent->SendMessage(GEV_VIEW, MAKEWPARAM(viewMulti, setMultiCode), (LPARAM)&m_codes);
	}

	return count;
}

LRESULT CConfigBarMulti::OnAxListKindItemClick(WPARAM wParam, LPARAM lParam)
{
	LRESULT result = CConfigBarPru::OnAxListKindItemClick(wParam, lParam);

	if (HIWORD(wParam)) {
		if (!m_autoPlay) {
			if (m_listKind->GetItemCount() > 0) {
				for (int i = 0; i < m_multiCount; i++) {
					m_arrSel[i] = LOWORD(wParam);
				}
			}
		}
	}

	return result;
}

