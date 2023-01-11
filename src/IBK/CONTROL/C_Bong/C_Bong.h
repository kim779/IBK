// C_Bong.h : main header file for the C_BONG DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../../h/axisfire.h"

/////////////////////////////////////////////////////////////////////////////
// CC_BongApp
// See C_Bong.cpp for the implementation of this class
//

class CC_BongApp : public CWinApp
{
public:
	CC_BongApp();
	virtual ~CC_BongApp();

	void	SetView(CWnd *pView)	{ m_pView = pView; }
	bool	CreateImage();
	CImageList* GetCtrlImage() { return m_pImgCtrl.get(); }

	std::shared_ptr<CImageList> getImage(CString path, int Width, int Height, UINT flag, COLORREF crMask);

	CFont*		GetFont(CWnd *pView, int point, CString name, int bold = 0, bool italic = false);
	CPen*		GetPen(CWnd *pView, int style, int width, COLORREF clr);
	CBrush*		GetBrush(CWnd *pView, COLORREF rColor);
	COLORREF	GetColor(CWnd *pView, int index);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CC_BongApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CC_BongApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CWnd* m_pView{};
	std::shared_ptr<CImageList>	m_pImgCtrl;
};
