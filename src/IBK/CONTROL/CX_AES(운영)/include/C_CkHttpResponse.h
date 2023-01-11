// This is a generated source file for Chilkat version 9.4.1.34
#ifndef _C_CkHttpResponse_H
#define _C_CkHttpResponse_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkHttpResponse CkHttpResponse_Create(void);
void CkHttpResponse_Dispose(HCkHttpResponse handle);
void CkHttpResponse_getBody(HCkHttpResponse cHandle, HCkByteData retval);
void CkHttpResponse_getBodyQP(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getBodyStr(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getCharset(HCkHttpResponse cHandle, HCkString retval);
unsigned long CkHttpResponse_getContentLength(HCkHttpResponse cHandle);
__int64 CkHttpResponse_getContentLength64(HCkHttpResponse cHandle);
void CkHttpResponse_getDate(HCkHttpResponse cHandle, SYSTEMTIME *retval);
void CkHttpResponse_getDateStr(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getDebugLogFilePath(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_putDebugLogFilePath(HCkHttpResponse cHandle, const char *newVal);
void CkHttpResponse_getDomain(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getFullMime(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getHeader(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getLastErrorHtml(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getLastErrorText(HCkHttpResponse cHandle, HCkString retval);
void CkHttpResponse_getLastErrorXml(HCkHttpResponse cHandle, HCkString retval);
int CkHttpResponse_getNumCookies(HCkHttpResponse cHandle);
int CkHttpResponse_getNumHeaderFields(HCkHttpResponse cHandle);
int CkHttpResponse_getStatusCode(HCkHttpResponse cHandle);
void CkHttpResponse_getStatusLine(HCkHttpResponse cHandle, HCkString retval);
BOOL CkHttpResponse_getUtf8(HCkHttpResponse cHandle);
void CkHttpResponse_putUtf8(HCkHttpResponse cHandle, BOOL newVal);
BOOL CkHttpResponse_getVerboseLogging(HCkHttpResponse cHandle);
void CkHttpResponse_putVerboseLogging(HCkHttpResponse cHandle, BOOL newVal);
void CkHttpResponse_getVersion(HCkHttpResponse cHandle, HCkString retval);
BOOL CkHttpResponse_GetCookieDomain(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetCookieExpires(HCkHttpResponse cHandle, int index, SYSTEMTIME *outSysTime);
BOOL CkHttpResponse_GetCookieExpiresStr(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetCookieName(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetCookiePath(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetCookieValue(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetHeaderField(HCkHttpResponse cHandle, const char *fieldName, HCkString outStr);
BOOL CkHttpResponse_GetHeaderFieldAttr(HCkHttpResponse cHandle, const char *fieldName, const char *attrName, HCkString outStr);
BOOL CkHttpResponse_GetHeaderName(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_GetHeaderValue(HCkHttpResponse cHandle, int index, HCkString outStr);
BOOL CkHttpResponse_SaveBodyBinary(HCkHttpResponse cHandle, const char *path);
BOOL CkHttpResponse_SaveBodyText(HCkHttpResponse cHandle, BOOL bCrlf, const char *path);
BOOL CkHttpResponse_SaveLastError(HCkHttpResponse cHandle, const char *path);
BOOL CkHttpResponse_UrlEncParamValue(HCkHttpResponse cHandle, const char *encodedParams, const char *paramName, HCkString outStr);
const char *CkHttpResponse_bodyQP(HCkHttpResponse cHandle);
const char *CkHttpResponse_bodyStr(HCkHttpResponse cHandle);
const char *CkHttpResponse_charset(HCkHttpResponse cHandle);
const char *CkHttpResponse_cookieDomain(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_cookieExpiresStr(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_cookieName(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_cookiePath(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_cookieValue(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_dateStr(HCkHttpResponse cHandle);
const char *CkHttpResponse_debugLogFilePath(HCkHttpResponse cHandle);
const char *CkHttpResponse_domain(HCkHttpResponse cHandle);
const char *CkHttpResponse_fullMime(HCkHttpResponse cHandle);
const char *CkHttpResponse_getCookieDomain(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getCookieExpiresStr(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getCookieName(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getCookiePath(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getCookieValue(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getHeaderField(HCkHttpResponse cHandle, const char *fieldName);
const char *CkHttpResponse_getHeaderFieldAttr(HCkHttpResponse cHandle, const char *fieldName, const char *attrName);
const char *CkHttpResponse_getHeaderName(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_getHeaderValue(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_header(HCkHttpResponse cHandle);
const char *CkHttpResponse_headerField(HCkHttpResponse cHandle, const char *fieldName);
const char *CkHttpResponse_headerFieldAttr(HCkHttpResponse cHandle, const char *fieldName, const char *attrName);
const char *CkHttpResponse_headerName(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_headerValue(HCkHttpResponse cHandle, int index);
const char *CkHttpResponse_lastErrorHtml(HCkHttpResponse cHandle);
const char *CkHttpResponse_lastErrorText(HCkHttpResponse cHandle);
const char *CkHttpResponse_lastErrorXml(HCkHttpResponse cHandle);
const char *CkHttpResponse_statusLine(HCkHttpResponse cHandle);
const char *CkHttpResponse_urlEncParamValue(HCkHttpResponse cHandle, const char *encodedParams, const char *paramName);
const char *CkHttpResponse_version(HCkHttpResponse cHandle);
#endif
