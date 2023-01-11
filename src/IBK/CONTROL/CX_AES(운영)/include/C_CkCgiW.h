// This is a generated source file for Chilkat version 9.4.1.34
#ifndef _C_CkCgi_W_H
#define _C_CkCgi_W_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkCgiW CkCgiW_Create(void);
HCkCgiW CkCgiW_Create2(BOOL bForDso);
void CkCgiW_Dispose(HCkCgiW handle);
unsigned long CkCgiW_getAsyncBytesRead(HCkCgiW cHandle);
BOOL CkCgiW_getAsyncInProgress(HCkCgiW cHandle);
unsigned long CkCgiW_getAsyncPostSize(HCkCgiW cHandle);
BOOL CkCgiW_getAsyncSuccess(HCkCgiW cHandle);
void CkCgiW_getDebugLogFilePath(HCkCgiW cHandle, HCkStringW retval);
void CkCgiW_putDebugLogFilePath(HCkCgiW cHandle, const wchar_t *newVal);
int CkCgiW_getHeartbeatMs(HCkCgiW cHandle);
void CkCgiW_putHeartbeatMs(HCkCgiW cHandle, int newVal);
int CkCgiW_getIdleTimeoutMs(HCkCgiW cHandle);
void CkCgiW_putIdleTimeoutMs(HCkCgiW cHandle, int newVal);
void CkCgiW_getLastErrorHtml(HCkCgiW cHandle, HCkStringW retval);
void CkCgiW_getLastErrorText(HCkCgiW cHandle, HCkStringW retval);
void CkCgiW_getLastErrorXml(HCkCgiW cHandle, HCkStringW retval);
int CkCgiW_getNumParams(HCkCgiW cHandle);
int CkCgiW_getNumUploadFiles(HCkCgiW cHandle);
int CkCgiW_getReadChunkSize(HCkCgiW cHandle);
void CkCgiW_putReadChunkSize(HCkCgiW cHandle, int newVal);
unsigned long CkCgiW_getSizeLimitKB(HCkCgiW cHandle);
void CkCgiW_putSizeLimitKB(HCkCgiW cHandle, unsigned long newVal);
BOOL CkCgiW_getStreamToUploadDir(HCkCgiW cHandle);
void CkCgiW_putStreamToUploadDir(HCkCgiW cHandle, BOOL newVal);
void CkCgiW_getUploadDir(HCkCgiW cHandle, HCkStringW retval);
void CkCgiW_putUploadDir(HCkCgiW cHandle, const wchar_t *newVal);
BOOL CkCgiW_getVerboseLogging(HCkCgiW cHandle);
void CkCgiW_putVerboseLogging(HCkCgiW cHandle, BOOL newVal);
void CkCgiW_getVersion(HCkCgiW cHandle, HCkStringW retval);
void CkCgiW_AbortAsync(HCkCgiW cHandle);
BOOL CkCgiW_GetEnv(HCkCgiW cHandle, const wchar_t *varName, HCkStringW outStr);
BOOL CkCgiW_GetParam(HCkCgiW cHandle, const wchar_t *paramName, HCkStringW outStr);
BOOL CkCgiW_GetParamName(HCkCgiW cHandle, int index, HCkStringW outStr);
BOOL CkCgiW_GetParamValue(HCkCgiW cHandle, int index, HCkStringW outStr);
BOOL CkCgiW_GetRawPostData(HCkCgiW cHandle, HCkByteDataW outData);
BOOL CkCgiW_GetUploadData(HCkCgiW cHandle, int index, HCkByteDataW outData);
BOOL CkCgiW_GetUploadFilename(HCkCgiW cHandle, int index, HCkStringW outStr);
unsigned long CkCgiW_GetUploadSize(HCkCgiW cHandle, int index);
BOOL CkCgiW_IsGet(HCkCgiW cHandle);
BOOL CkCgiW_IsHead(HCkCgiW cHandle);
BOOL CkCgiW_IsPost(HCkCgiW cHandle);
BOOL CkCgiW_IsUpload(HCkCgiW cHandle);
BOOL CkCgiW_ReadRequest(HCkCgiW cHandle);
BOOL CkCgiW_SaveLastError(HCkCgiW cHandle, const wchar_t *path);
BOOL CkCgiW_SaveNthToUploadDir(HCkCgiW cHandle, int index);
void CkCgiW_SleepMs(HCkCgiW cHandle, int millisec);
BOOL CkCgiW_TestConsumeAspUpload(HCkCgiW cHandle, const wchar_t *path);
const wchar_t *CkCgiW__debugLogFilePath(HCkCgiW cHandle);
const wchar_t *CkCgiW__env(HCkCgiW cHandle, const wchar_t *varName);
const wchar_t *CkCgiW__getEnv(HCkCgiW cHandle, const wchar_t *varName);
const wchar_t *CkCgiW__getParam(HCkCgiW cHandle, const wchar_t *paramName);
const wchar_t *CkCgiW__getParamName(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__getParamValue(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__getUploadFilename(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__lastErrorHtml(HCkCgiW cHandle);
const wchar_t *CkCgiW__lastErrorText(HCkCgiW cHandle);
const wchar_t *CkCgiW__lastErrorXml(HCkCgiW cHandle);
const wchar_t *CkCgiW__param(HCkCgiW cHandle, const wchar_t *paramName);
const wchar_t *CkCgiW__paramName(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__paramValue(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__uploadDir(HCkCgiW cHandle);
const wchar_t *CkCgiW__uploadFilename(HCkCgiW cHandle, int index);
const wchar_t *CkCgiW__version(HCkCgiW cHandle);
#endif
