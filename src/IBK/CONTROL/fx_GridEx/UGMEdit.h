/*************************************************************************
				Class Declaration : CUGMaskedEdit
**************************************************************************
	Source file : UGMEdit.cpp
	Header file : UGMEdit.h
	Copyright ? Dundas Software Ltd. 1994 - 2002, All Rights Reserved

    Purpose
		This class is the standard Masked edit control for Ultimate Grid
	Details

		Mask strings consist of the following characters and can be 
		conbined with any literal character:
 
		0	Digit (0 through 9), entry required; plus and minus signs not allowed. 
		9	Digit or space (entry optional; plus and minus signs not allowed) 
		L	Letter (A through Z, entry required) 
		?	Letter (A through Z, entry optional) 
		A	Letter or Digit (Entry required) 
		a	Letter or Digit (Entry optional) 
		&	Any character or a space (Entry required) 
		C	Any character or a space (Entry optional) 
		. , : ; - /		Decimal placeholder and thousands, date, and time 
						separators. (The actual character used will depend on 
						the regional settings specified in the Windows Control 
						Panel) 
		\		Causes the character that follows to be displayed as a literal 
				character. Used to display any of the characters listed in this 
				table as literal characters. (For example, \A is displayed as 
				just A, \& is displayed as just &, etc.) 
*************************************************************************/
#pragma once


//CUGMaskedEdit declaration
class UG_CLASS_DECL CUGMaskedEdit : public CUGEditBase
{
// Construction
public:
	CUGMaskedEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGMaskedEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGMaskedEdit();


	// Generated message map functions
protected:
	//{{AFX_MSG(CUGMaskedEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


protected:

	int			m_MaskKeyInProgress;

	int			m_useMask;
	TCHAR		m_blankChar;
	BOOL		m_storeLiterals;
	TCHAR*		m_maskChars;
	
	CString		m_origMask;
	CString		m_mask;
	CString		m_literals;

	int  MaskKeyStrokes(UINT *vKey);
	void ShowInvalidEntryMessage();


	BOOL m_cancel;
	BOOL m_continueFlag;
	int  m_continueCol;
	int  m_continueRow;

public:


	int SetMask(LPCTSTR string);
	int MaskString(CString *string);	
};

