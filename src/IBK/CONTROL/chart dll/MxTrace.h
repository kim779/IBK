#ifndef __MXTRACE_H__
#define __MXTRACE_H__

typedef struct {
	int pos;
	int cnt;
	int u_pos;
	int u_cnt;
} QHEADER, *PQHEADER;

typedef struct {
	char AppName[64];
	char DebugStr[256];
} DEBUGINFO, *PDEBUGINFO;

#define DEBUG_Q_COUNT  100
#define DEBUG_Q_HEADER "PO_DEBUG_Q_HEADER"
#define DEBUG_Q_BUFFER "PO_DEBUG_INFO_QUEUE"

/**
#ifdef _DEBUG
void M_DebugProc(LPCTSTR lpszFormat, ...);
#define Debug	::M_DebugProc
#else  // _DEBUG
inline void M_DebugProc(LPCTSTR lpszFormat, ...) {}
#define Debug   1 ? (void)0 : ::AfxTrace
#endif // _DEBUG
**/
void M_DebugProc(LPCTSTR lpszFormat, ...);
#define Debug ::M_DebugProc


#endif // __MXTRACE_H__
