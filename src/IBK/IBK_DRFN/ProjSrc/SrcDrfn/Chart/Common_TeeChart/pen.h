// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CPen1 wrapper class

class CPen1 : public COleDispatchDriver
{
public:
	CPen1() {}		// Calls COleDispatchDriver default constructor
	CPen1(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPen1(const CPen1& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetEndStyle();
	void SetEndStyle(long nNewValue);
	void ShowEditor();
};
