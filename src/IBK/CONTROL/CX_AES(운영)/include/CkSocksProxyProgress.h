// CkSocksProxyProgress.h: interface for the CkSocksProxyProgress class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CKSOCKSPROXYPROGRESS_H
#define _CKSOCKSPROXYPROGRESS_H



#ifndef __sun__
#pragma pack (push, 8)
#endif
 

class CkSocksProxyProgress  
{
    public:
	CkSocksProxyProgress() { }
	virtual ~CkSocksProxyProgress() { }

	// Called periodically to check to see if the method call should be aborted.
	virtual void AbortCheck(bool *abort) { }
	virtual void ProgressInfo(const char *name, const char *value) { }

};
#ifndef __sun__
#pragma pack (pop)
#endif


#endif
