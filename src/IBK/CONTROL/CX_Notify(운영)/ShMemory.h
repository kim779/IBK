#pragma once

class CShMemory
{
public:
	CShMemory();
	virtual ~CShMemory();

private:
	HANDLE	m_hKeyFile;
	char	*m_pKeyView;
	bool	m_bMaster;

public:
	CString	m_remainSHMEMNAME;

	void	Close();
	BOOL	InitSharedMemory(HWND hwnd);
	void	SendTrigger(CString Trigger);
	HWND	GetHandle(int Index);
	void	RemoveHandle(HWND hWnd);
	void	AddHandle(HWND hWnd);
	long	GetHandleCount();

};