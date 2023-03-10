// setup.cpp : implementation file
//

#include "stdafx.h"
#include "IB210200.h"
#include "setup.h"
#include "item.hxx"

#include "../../h/axisvar.h"
#include "../../h/axisfire.h"

#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct	_dataR
{
	char*	title;
	DWORD	flag;
	DWORD	color;
	char*	maps;
};

struct	_dataR	c_news[] = {
	{ "종목뉴스",						S_NEWS|F_NEWS,		RGB(  0,   0,   0),	"IB200100"	},
	{ "공시",						S_NEWS|F_GONG,		RGB(  0,   0,   0),	"IB200100"	},
};
#define	L_news		sizeof(c_news)/sizeof(struct _dataR)


struct	_dataR	c_quote[] = {
	{ "전일고가갱신종목",					S_QUOTE|F_JUN_KOGA,	RGB(255,   0,   0),	"IB200100"	},
	{ "전일거래량갱신",					S_QUOTE|F_JUN_GVOL,	RGB(255,   0,   0),	"IB200100"	},
	{ "당일상한가진입",					S_QUOTE|F_DAN_SHGA,	RGB(255,   0,   0),	"IB200100"	},
	{ "당일하한가진입",					S_QUOTE|F_DAN_HHGA,	RGB(  0,   0, 255),	"IB200100"	},
	{ "최근5일 매물대돌파",					S_QUOTE|F_MAMUL_5D,	RGB(255,   0,   0),	"IB200100"	},
	{ "최근60일 매물대돌파",				S_QUOTE|F_MAMUL_60D,	RGB(255,   0,   0),	"IB200100"	},
	{ "최근5일 첫 상한가",					S_QUOTE|F_SHGA_5D,	RGB(255,   0,   0),	"IB200100"	},
	{ "52주 최고거래량 갱신",				S_QUOTE|F_GVOL_52M,	RGB(255,   0,   0),	"IB200100"	},
	{ "최근5일 최고거래량 갱신",				S_QUOTE|F_GVOL_5D,	RGB(255,   0,   0),	"IB200100"	},
	{ "최근 3일간 주가등락 15%이상",			S_QUOTE|F_3D_UP_15P,	RGB(  0,   0,   0),	"IB200100"	},
	{ "최근 5일간 주가등락 20%이상",			S_QUOTE|F_5D_UP_20P,	RGB(  0,   0,   0),	"IB200100"	},
	{ "최근 5일 신고가 갱신",				S_QUOTE|F_KOGA_5D,	RGB(255,   0,   0),	"IB200100"	},
	{ "최근 5일 신저가 갱신",				S_QUOTE|F_JEGA_5D,	RGB(  0,   0, 255),	"IB200100"	},
	{ "당일 최고/최저대비 등락폭5%이상",			S_QUOTE|F_UPDN_5P,	RGB(  0,   0,   0),	"IB200100"	},
	{ "시가대비 5%이상 등락",				S_QUOTE|F_SIGA_5P,	RGB(  0,   0,   0),	"IB200100"	},
	{ "연속 3일 상승",					S_QUOTE|F_UPXX_3D,	RGB(255,   0,   0),	"IB200100"	},
	{ "연속 3일 하락",					S_QUOTE|F_DOWN_3D,	RGB(  0,   0, 255),	"IB200100"	},
	{ "현재 매수비율 200%이상",				S_QUOTE|F_MASU_200P,	RGB(255,   0,   0),	"IB200100"	},
	{ "당일 거래량 회전율 20%이상",				S_QUOTE|F_RATE_20P,	RGB(  0,   0,   0),	"IB200100"	},
	{ "상한가 재진입",					S_QUOTE|F_RE_SHGA,	RGB(255,   0,   0),	"IB200100"	},
	{ "하한가 재진입",					S_QUOTE|F_RE_HHGA,	RGB(  0,   0, 255),	"IB200100"	},
	{ "당일 신고가 진입",					S_QUOTE|F_DAN_KOGA,	RGB(255,   0,   0),	"IB200100"	},
	{ "당일 신저가 진입",					S_QUOTE|F_DAN_JEGA,	RGB(  0,   0, 255),	"IB200100"	},

};
#define	L_quote		sizeof(c_quote)/sizeof(struct _dataR)


struct	_dataR	c_trend[] = {
	{ "외국인 순매수",					S_TREND|F_WMASU,	RGB(255,   0,   0),	"IB200100"	},
	{ "외국인 순매도",					S_TREND|F_WMADO,	RGB(  0,   0, 255),	"IB200100"	},
	{ "외국인 3일 연속 순매수",				S_TREND|F_WMASU_3D,	RGB(255,   0,   0),	"IB200100"	},
	{ "외국인 3일 연속 순매도",				S_TREND|F_WMADO_3D,	RGB(  0,   0, 255),	"IB200100"	},
	{ "외국계증권사 순매수 만주이상(당일은 상위5개사 기준)",S_TREND|F_TMASU_1,	RGB(255,   0,   0),	"IB200100"	},
	{ "외국계증권사 순매도 만주이상(당일은 상위5개사 기준)",S_TREND|F_TMADO_1,	RGB(  0,   0, 255),	"IB200100"	},
	{ "외국계 증권사 첫 매수거래 발생",			S_TREND|F_TMASU_F,	RGB(255,   0,   0),	"IB200100"	},
	{ "외국계 증권사 첫 매도거래 발생",			S_TREND|F_TMADO_F,	RGB(  0,   0, 255),	"IB200100"	},
};
#define	L_trend		sizeof(c_trend)/sizeof(struct _dataR)


struct	_dataR	c_chart[] = {
	{ "주가 골든크로스(5MA>20MA)",				S_CHART|F_JUGA_GC,	RGB(255,   0,   0),	"IB200100"	},
	{ "주가 데드크로스(5MA<20MA)",				S_CHART|F_JUGA_DC,	RGB(  0,   0, 255),	"IB200100"	},
	{ "거래량 골든크로스(5MA>20MA)",			S_CHART|F_GVOL_GC,	RGB(255,   0,   0),	"IB200100"	},
	{ "거래량 데드크로스(5MA<20MA) (12:00 부터 감시)",	S_CHART|F_GVOL_DC,	RGB(  0,   0, 255),	"IB200100"	},
	{ "삼선전환도 양전환",					S_CHART|F_3SUN_UP,	RGB(255,   0,   0),	"IB200100"	},
	{ "삼선전환도 음전환",					S_CHART|F_3SUN_DN,	RGB(  0,   0, 255),	"IB200100"	},
	{ "주가 5MA 상향돌파",					S_CHART|F_5MAJ_UP,	RGB(255,   0,   0),	"IB200100"	},
	{ "주가 5MA 하향돌파",					S_CHART|F_5MAJ_DN,	RGB(  0,   0, 255),	"IB200100"	},
	{ "거래량 5MA 상향돌파",				S_CHART|F_5MAG_UP,	RGB(255,   0,   0),	"IB200100"	},
};
#define	L_chart		sizeof(c_chart)/sizeof(struct _dataR)

/////////////////////////////////////////////////////////////////////////////
// Csetup dialog


Csetup::Csetup(CWnd* pParent, CString root, CString user, CWnd* pWnd)
	: CDialog(Csetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(Csetup)
	//}}AFX_DATA_INIT

	m_parent = pWnd;

	m_file.Format("%s/%s/%s/%s", root, USRDIR, user, S_FILE);
	for (int ii = 0; ii < 4; ii++)
		m_flags[ii] = 0;
	m_items.RemoveAll();

	m_ilist.Create(1, 15, ILC_COLOR4, 10, 10);

}

Csetup::~Csetup()
{
	m_ilist.DeleteImageList();
}

void Csetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Csetup)
	DDX_Control(pDX, IDC_EDITVOL, m_editVol);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_TREE, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Csetup, CDialog)
	//{{AFX_MSG_MAP(Csetup)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_ADD_ALL, OnAddAll)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_DEL_ALL, OnDelAll)
	ON_BN_CLICKED(IDC_BEEP, OnBeep)
	ON_BN_CLICKED(IDC_FILE, OnFile)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnDblclkTree)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(IDC_CHKVOL, OnChkvol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Csetup message handlers

BOOL Csetup::OnInitDialog() 
{
	int	check{};

	CDialog::OnInitDialog();

	addColumn(_T("선택신호"), 0, 219);
	addColumn(_T(""), 1, 22);
	addColumn(_T("화면"), 2, 36);

	loadfile();
	for (int ii = 0; ii < 8; ii++)
	{
		check = (m_state.GetAt(ii) == '1') ? 1 : 0;
		switch (ii)
		{
		case 0:	((CButton *)GetDlgItem(IDC_C1))->SetCheck(check);	break;
		case 1:	((CButton *)GetDlgItem(IDC_C2))->SetCheck(check);	break;
		case 2:	((CButton *)GetDlgItem(IDC_C3))->SetCheck(check);	break;
		case 3:	((CButton *)GetDlgItem(IDC_C4))->SetCheck(check);	break;
		case 4:	((CButton *)GetDlgItem(IDC_C5))->SetCheck(check);	break;
		case 5:	((CButton *)GetDlgItem(IDC_C6))->SetCheck(check);	break;
		case 6:	((CButton *)GetDlgItem(IDC_C7))->SetCheck(check);	break;
		case 7:	((CButton *)GetDlgItem(IDC_C8))->SetCheck(check);	break;
		}
	}

	if (!m_sound.IsEmpty())
	{
		GetDlgItem(IDC_FILEN)->SetWindowText(m_sound);
		GetDlgItem(IDC_FILE)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_FILE)->EnableWindow(FALSE);

	m_list.SetImageList(&m_ilist, LVSIL_SMALL);

	// 거래량
	((CButton *)GetDlgItem(IDC_CHKVOL))->SetCheck(m_chkVol);
	if (m_chkVol)
		m_editVol.EnableWindow(TRUE);
	else
		m_editVol.EnableWindow(FALSE);
	m_editVol.SetWindowText(m_vol);
	m_editVol.SetLimitText(4);

	// 거래소
	for (int ii = 0; ii < 4; ii++)
	{
		check = (m_gubn.GetAt(ii) == '1') ? 1 : 0;
		switch (ii)
		{
		case 0:	((CButton *)GetDlgItem(IDC_CHKKOSPI))->SetCheck(check);	break;
		case 1:	((CButton *)GetDlgItem(IDC_CHKKOSDAQ))->SetCheck(check);break;
		case 2:	((CButton *)GetDlgItem(IDC_CHKTHIRD))->SetCheck(check);	break;
		case 3:	((CButton *)GetDlgItem(IDC_CHKELW))->SetCheck(check);	break;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Csetup::OnDestroy() 
{
//	DWORD	key=0;
	Citem* item{};

//	for (POSITION pos = m_items.GetStartPosition(); pos; )
//	{
//		m_items.GetNextAssoc(pos, key, item);
//		delete item;
//	}

	m_items.RemoveAll();

	_vData.clear();

	for (int ii = 0; ii < m_list.GetItemCount(); ii++)
	{
		item = (Citem *)m_list.GetItemData(ii);
		delete item;
	}

	CDialog::OnDestroy();	
}

void Csetup::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnAdd();
	*pResult = 0;
}

void Csetup::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpitem;

	lpitem = (LPNMITEMACTIVATE)pNMHDR;
	if (lpitem->iSubItem == 0)
		OnDel();	
	*pResult = 0;
}

void Csetup::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	Citem* item{};
	LPNMITEMACTIVATE lpitem{};

	lpitem = (LPNMITEMACTIVATE)pNMHDR;
	item = (Citem *)m_list.GetItemData(lpitem->iItem);
	
	m_list.MouseUpEvent();	// notice

	switch (lpitem->iSubItem)
	{
	case 1:		// color
		if (item)
		{
			CColorDialog    dlg;

			dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
			dlg.m_cc.rgbResult = item->m_clr;
			if (dlg.DoModal() == IDOK)
			{
				item->m_clr = dlg.GetColor();
				m_list.Update(lpitem->iItem);
			}
		}
		break;

	case 2:		// map
		if (item)
		{
			CString	text;
			text = (char *)m_parent->SendMessage(WM_USER, MAKEWPARAM(menuDLL, 0), 0);
			if (!text.IsEmpty())
			{
				item->m_maps = text;
				m_list.SetItemText(lpitem->iItem, 2, text.Mid(2, 4));
				m_list.Update(lpitem->iItem);
			}
		}
		break;
	}
	*pResult = 0;
}

void Csetup::OnAdd() 
{
	CString	text;
	LVFINDINFO info{};

	for (HTREEITEM hitem = m_tree.GetFirstSelectedItem(); hitem; hitem = m_tree.GetNextSelectedItem(hitem))
	{
		text = m_tree.GetItemText(hitem);
		info.flags = LVFI_PARTIAL|LVFI_STRING;
		info.psz   = (LPCTSTR)text.operator LPCTSTR();
		if (m_list.FindItem(&info) == -1)
		{
			Citem	*item;
			if (m_items.Lookup(m_tree.GetItemData(hitem), item))
			{
				const int	index = m_list.GetItemCount();
				Citem*	itemx = item->Clone();
				addItem(m_tree.GetItemText(hitem), index, 0);
				m_list.SetItemData(index, (DWORD)itemx);
				addItem(itemx->m_maps.Mid(2, 4), index, 2);
			}
		}
	}
}

void Csetup::OnAddAll() 
{
	HTREEITEM root{}, citem{};
	const int	count = m_list.GetItemCount();

	for (int ii = 0; ii < count; ii++)
	{
		Citem*	item = (Citem *)m_list.GetItemData(0);
		m_list.DeleteItem(0);
		delete item;
	}

	for (root = m_tree.GetRootItem(); root != NULL; root = m_tree.GetNextSiblingItem(root))
	{
		if (m_tree.ItemHasChildren(root))
		{
			for (citem = m_tree.GetChildItem(root) ; citem != NULL; citem = m_tree.GetNextItem(citem, TVGN_NEXT))
			{
				Citem*	item;
				if (m_items.Lookup(m_tree.GetItemData(citem), item))
				{
					const int	index = m_list.GetItemCount();
					Citem*	itemx = item->Clone();
					addItem(m_tree.GetItemText(citem), index, 0);
					m_list.SetItemData(index, (DWORD)itemx);
					addItem(itemx->m_maps.Mid(2, 4), index, 2);
				}
			}
		}
	}
}

void Csetup::OnDel() 
{
	int	index{};
	Citem*	item=nullptr;
	CWordArray arr;

	for (POSITION pos = m_list.GetFirstSelectedItemPosition(); pos; )
	{
		index = m_list.GetNextSelectedItem(pos);
		arr.Add(index);
	}

	for (int ii = arr.GetUpperBound(); ii >= 0; ii--)
	{
		index = arr.GetAt(ii);
		item  = (Citem *)m_list.GetItemData(index);
		m_list.DeleteItem(index);
		delete item;
	}
}

void Csetup::OnDelAll() 
{
	Citem* item{};
	const int count = m_list.GetItemCount();

	for (int ii = 0; ii < count; ii++)
	{
		item = (Citem *)m_list.GetItemData(0);
		m_list.DeleteItem(0);
		delete item;
	}
	m_list.UpdateWindow();
}

void Csetup::OnBeep() 
{
	GetDlgItem(IDC_FILE)->EnableWindow(((CButton *)GetDlgItem(IDC_BEEP))->GetCheck() ? TRUE : FALSE);
}

void Csetup::OnFile() 
{
	CFileDialog fdlg(TRUE, "wav", NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
				"Wave Files(*.wav)|*.wav|All Files(*.*)|*.*|");
	if (fdlg.DoModal() == IDOK)
		GetDlgItem(IDC_FILEN)->SetWindowText(fdlg.GetPathName());
}

void Csetup::OnOK() 
{
	// 거래량 check
	CString volS;
	m_editVol.GetWindowText(volS);
	const int vol = atoi(volS);

	if (((CButton *)GetDlgItem(IDC_CHKVOL))->GetCheck())
	{
		if (vol <= 0 || vol > 9999)
		{
			AfxMessageBox("거래량은 0보다 큰값을 입력하셔야 합니다.");
			m_editVol.SetFocus();
			m_editVol.SetSel(0, -1);
			return;
		}
	}
	volS.Format("%d", vol);

	// 거래소check
	CString gubnS;
	gubnS.Empty();
	gubnS += (((CButton *)GetDlgItem(IDC_CHKKOSPI))->GetCheck() == 1) ? _T("1") : _T("0");
	gubnS += (((CButton *)GetDlgItem(IDC_CHKKOSDAQ))->GetCheck() == 1) ? _T("1") : _T("0");
	gubnS += (((CButton *)GetDlgItem(IDC_CHKTHIRD))->GetCheck() == 1) ? _T("1") : _T("0");
	gubnS += (((CButton *)GetDlgItem(IDC_CHKELW))->GetCheck() == 1) ? _T("1") : _T("0");
	gubnS += "0000";	// fill

	if (gubnS.Left(4) == "0000")
	{
		AfxMessageBox("검색대상이 한개 이상 check되어 있어야 합니다.");
		GetDlgItem(IDC_CHKKOSPI)->SetFocus();
		return;
	}


	Citem* item{};
	CString	keys, text;

	m_flags[0] = S_NEWS;
	m_flags[1] = S_QUOTE;
	m_flags[2] = S_TREND;
	m_flags[3] = S_CHART;
	WritePrivateProfileSection(_T("2102"), "", m_file);
	for (int ii = 0; ii < m_list.GetItemCount(); ii++)
	{
		item = (Citem *)m_list.GetItemData(ii);
		if (item)
		{
			if (item->m_flag & S_NEWS)
				m_flags[0] |= item->m_flag;
			else if (item->m_flag & S_QUOTE)
				m_flags[1] |= item->m_flag;
			else if (item->m_flag & S_TREND)
				m_flags[2] |= item->m_flag;
			else if (item->m_flag & S_CHART)
				m_flags[3] |= item->m_flag;

			keys.Format("%x", item->m_flag);
			text.Format("%x,%s", item->m_clr, item->m_maps);
			WritePrivateProfileString(_T("2102"), keys, text, m_file);
		}
	}
	text.Format("%x", m_flags[0]);
	WritePrivateProfileString(_T("2102"), "news",  text, m_file);
	text.Format("%x", m_flags[1]);
	WritePrivateProfileString(_T("2102"), "quote", text, m_file);
	text.Format("%x", m_flags[2]);
	WritePrivateProfileString(_T("2102"), "trend", text, m_file);
	text.Format("%x", m_flags[3]);
	WritePrivateProfileString(_T("2102"), "chart", text, m_file);

	text.Empty();
	text += (((CButton *)GetDlgItem(IDC_C1))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C2))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C3))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C4))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C5))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C6))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C7))->GetCheck() == 1) ? _T("1") : _T("0");
	text += (((CButton *)GetDlgItem(IDC_C8))->GetCheck() == 1) ? _T("1") : _T("0");
	WritePrivateProfileString(_T("2102"), "item", text, m_file);

	text.Empty();
	if (((CButton *)GetDlgItem(IDC_BEEP))->GetCheck() == 1)
		GetDlgItem(IDC_FILEN)->GetWindowText(text);
	WritePrivateProfileString(_T("2102"), "beep", text, m_file);

	// 거래량
	if (((CButton *)GetDlgItem(IDC_CHKVOL))->GetCheck())
		text = "1";
	else 
		text = "0";
	WritePrivateProfileString(_T("2102"), "chkVol", text, m_file);

	WritePrivateProfileString(_T("2102"), "Vol", volS, m_file);

	// 거래소
	WritePrivateProfileString(_T("2102"), "gubn", gubnS, m_file);

	CDialog::OnOK();
}

void Csetup::loadfile()
{
	char	wb[128]{};
	Citem* item{}, * itemx{};
	CString	keys, text;
	HTREEITEM hitem{}, hitem1{};

	GetPrivateProfileString(_T("2102"), "news",  "0x01ffffff", wb, sizeof(wb), m_file);
	m_flags[0] = hexs2int(wb);
	GetPrivateProfileString(_T("2102"), "quote", "0x02ffffff", wb, sizeof(wb), m_file);
	m_flags[1] = hexs2int(wb);
	GetPrivateProfileString(_T("2102"), "trend", "0x04ffffff", wb, sizeof(wb), m_file);
	m_flags[2] = hexs2int(wb);
	GetPrivateProfileString(_T("2102"), "chart", "0x08ffffff", wb, sizeof(wb), m_file);
	m_flags[3] = hexs2int(wb);

	// load informations & initialize tree & initialize list
	int	pos=0, idx = 0;
	hitem = m_tree.InsertItem(_T("뉴스/공시"), 0, 0);
	m_tree.SetItemData(hitem, 0);
	for (int ii = 0; ii < L_news; ii++)
	{
//		item = new Citem;

		auto& item = _vData.emplace_back(std::make_unique<Citem>());

		item->m_flag = c_news[ii].flag;
		item->m_maps = c_news[ii].maps;
		item->m_clr  = c_news[ii].color;
		m_items.SetAt(item->m_flag, item.get());

		hitem1 = m_tree.InsertItem(c_news[ii].title, 0, 0, hitem);
		m_tree.SetItemData(hitem1, item->m_flag);

		if (m_flags[0] & item->m_flag & ~S_NEWS)
		{
			itemx = item->Clone();
			keys.Format("%x", c_news[ii].flag);
			text.Format("%x,%s", c_news[ii].color, c_news[ii].maps);
			GetPrivateProfileString(_T("2102"), keys, text, wb, sizeof(wb), m_file);
			text = wb;
			pos  = text.Find(',');
			if (pos != -1)
			{
				keys = text.Left(pos++);
				text = text.Mid(pos);
				keys.TrimLeft(); keys.TrimRight();
				text.TrimLeft(); text.TrimRight();
				if (!keys.IsEmpty())
					itemx->m_clr = hexs2int(keys);
				if (!text.IsEmpty())
					itemx->m_maps = text;
			}
			addItem(c_news[ii].title, idx, 0);
			addItem(itemx->m_maps.Mid(2, 4), idx, 2);
			m_list.SetItemData(idx++, (DWORD)itemx);
		}
	}

	hitem = m_tree.InsertItem("시세분석", 0, 1);
	m_tree.SetItemData(hitem, 0);
	for (int ii = 0; ii < L_quote; ii++)
	{
		auto& item = _vData.emplace_back(std::make_unique<Citem>());
//		item = new Citem;

		item->m_flag = c_quote[ii].flag;
		item->m_maps = c_quote[ii].maps;
		item->m_clr  = c_quote[ii].color;
		m_items.SetAt(item->m_flag, item.get());

		hitem1 = m_tree.InsertItem(c_quote[ii].title, 0, 0, hitem);
		m_tree.SetItemData(hitem1, item->m_flag);

		if (m_flags[1] & item->m_flag & ~S_QUOTE)
		{
			itemx = item->Clone();
			keys.Format("%x", c_quote[ii].flag);
			text.Format("%x,%s", c_quote[ii].color, c_quote[ii].maps);
			GetPrivateProfileString(_T("2102"), keys, text, wb, sizeof(wb), m_file);
			text = wb;
			pos  = text.Find(',');
			if (pos != -1)
			{
				keys = text.Left(pos++);
				text = text.Mid(pos);
				keys.TrimLeft(); keys.TrimRight();
				text.TrimLeft(); text.TrimRight();
				if (!keys.IsEmpty())
					itemx->m_clr = hexs2int(keys);
				if (!text.IsEmpty())
					itemx->m_maps = text;
			}
			addItem(c_quote[ii].title, idx, 0);
			addItem(itemx->m_maps.Mid(2, 4), idx, 2);
			m_list.SetItemData(idx++, (DWORD)itemx);
		}
	}

	hitem = m_tree.InsertItem("매매동향", 0, 1);
	m_tree.SetItemData(hitem, 0);
	for (int ii = 0; ii < L_trend; ii++)
	{
//		item = new Citem;
		auto& item = _vData.emplace_back(std::make_unique<Citem>());

		item->m_flag = c_trend[ii].flag;
		item->m_maps = c_trend[ii].maps;
		item->m_clr  = c_trend[ii].color;
		m_items.SetAt(item->m_flag, item.get());

		hitem1 = m_tree.InsertItem(c_trend[ii].title, 0, 0, hitem);
		m_tree.SetItemData(hitem1, item->m_flag);

		if (m_flags[2] & item->m_flag & ~S_TREND)
		{
			itemx = item->Clone();
			keys.Format("%x", c_trend[ii].flag);
			text.Format("%x,%s", c_trend[ii].color, c_trend[ii].maps);
			GetPrivateProfileString(_T("2102"), keys, text, wb, sizeof(wb), m_file);
			text = wb;
			pos  = text.Find(',');
			if (pos != -1)
			{
				keys = text.Left(pos++);
				text = text.Mid(pos);
				keys.TrimLeft(); keys.TrimRight();
				text.TrimLeft(); text.TrimRight();
				if (!keys.IsEmpty())
					itemx->m_clr = hexs2int(keys);
				if (!text.IsEmpty())
					itemx->m_maps = text;
			}
			addItem(c_trend[ii].title, idx, 0);
			addItem(itemx->m_maps.Mid(2, 4), idx, 2);
			m_list.SetItemData(idx++, (DWORD)itemx);
		}
	}
/*
	hitem = m_tree.InsertItem("차트신호", 0, 1);
	m_tree.SetItemData(hitem, 0);
	for (ii = 0; ii < L_chart; ii++)
	{
		item = new Citem;
		item->m_flag = c_chart[ii].flag;
		item->m_maps = c_chart[ii].maps;
		item->m_clr  = c_chart[ii].color;
		m_items.SetAt(item->m_flag, item);

		hitem1 = m_tree.InsertItem(c_chart[ii].title, 0, 0, hitem);
		m_tree.SetItemData(hitem1, item->m_flag);

		if (m_flags[3] & item->m_flag & ~S_CHART)
		{
			itemx = item->Clone();
			keys.Format("%x", c_chart[ii].flag);
			text.Format("%x,%s", c_chart[ii].color, c_chart[ii].maps);
			GetPrivateProfileString(_T("2102"), keys, text, wb, sizeof(wb), m_file);
			text = wb;
			pos  = text.Find(',');
			if (pos != -1)
			{
				keys = text.Left(pos++);
				text = text.Mid(pos);
				keys.TrimLeft(); keys.TrimRight();
				text.TrimLeft(); text.TrimRight();
				if (!keys.IsEmpty())
					itemx->m_clr = hexs2int(keys);
				if (!text.IsEmpty())
					itemx->m_maps = text;
			}
			addItem(c_chart[ii].title, idx, 0);
			addItem(itemx->m_maps.Mid(2, 4), idx, 2);
			m_list.SetItemData(idx++, (DWORD)itemx);
		}
	}
*/
	GetPrivateProfileString(_T("2102"), "item", "00000000", wb, sizeof(wb), m_file);
	m_state = wb;
	m_state += CString('0', 8-m_state.GetLength());

	GetPrivateProfileString(_T("2102"), "beep", "", wb, sizeof(wb), m_file);
	m_sound = wb;

	// 거래량 200701029
	m_chkVol = GetPrivateProfileInt(_T("2102"), "chkVol", 0, m_file);
	GetPrivateProfileString(_T("2102"), "vol", "0", wb, sizeof(wb), m_file);
	m_vol = wb;

	// 거래소
	GetPrivateProfileString(_T("2102"), "gubn", "11100000", wb, sizeof(wb), m_file);
	m_gubn = wb;
}

int Csetup::hexs2int(CString hexs)
{
	struct	_hexmap {
		char	ch;
		int	value;
	} hexmap [] = {
		{ '0', 0 },	{ '1', 1 },	{ '2', 2 },	{ '3', 3 },	{ '4', 4 },
		{ '5', 5 },	{ '6', 6 },	{ '7', 7 },	{ '8', 8 },	{ '9', 9 },
		{ 'a', 10 },	{ 'b', 11 },	{ 'c', 12 },	{ 'd', 13 },	{ 'e', 14 },
		{ 'f', 15 },	{ NULL, NULL }
	};
	bool	first = true;
	int	value=0, result = 0;
	CMap	< TCHAR, TCHAR, int, int& > hmap;

	hexs.MakeLower();
	if (hexs.Find("0x") == 0)
		hexs = hexs.Mid(2);

	for (int ii = 0; hexmap[ii].ch != NULL; ii++)
		hmap.SetAt(hexmap[ii].ch, hexmap[ii].value);

	for (int ii = 0; ii < hexs.GetLength(); ii++)
	{
		if (hmap.Lookup(hexs.GetAt(ii), value))
		{
			if (!first)
				result <<= 4;
			result |= value;
			first = false;
			continue;
		}
		break;
	}

	return result;
}

BOOL Csetup::addColumn(CString heads, int col, int width)
{
	LV_COLUMN lvc{};

	lvc.mask     = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvc.fmt      = LVCFMT_LEFT;
	lvc.pszText  = (LPTSTR)heads.operator LPCTSTR();
	lvc.cx       = width;
	lvc.iSubItem = -1;

	return m_list.InsertColumn(col, &lvc);
}

BOOL Csetup::addItem(CString items, int item, int subi)
{
	LV_ITEM lvi{};

	lvi.mask     = LVIF_TEXT;
	lvi.iItem    = item;
	lvi.iSubItem = subi;
	lvi.pszText  = (LPTSTR)items.operator LPCTSTR();

	if (!subi)
		return m_list.InsertItem(&lvi);
	return m_list.SetItem(&lvi);
}

void Csetup::OnChkvol() 
{
	if (((CButton *)GetDlgItem(IDC_CHKVOL))->GetCheck())
	{
		m_editVol.EnableWindow(TRUE);
		m_editVol.SetFocus();
		m_editVol.SetSel(0, -1);
	}
	else
		m_editVol.EnableWindow(FALSE);
}
