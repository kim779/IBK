// This is a generated source file for Chilkat version 9.4.1.34
#ifndef _C_CkMht_W_H
#define _C_CkMht_W_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkMhtW CkMhtW_Create(void);
HCkMhtW CkMhtW_Create2(BOOL bForDso);
void CkMhtW_Dispose(HCkMhtW handle);
void CkMhtW_getBaseUrl(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putBaseUrl(HCkMhtW cHandle, const wchar_t *newVal);
int CkMhtW_getConnectTimeout(HCkMhtW cHandle);
void CkMhtW_putConnectTimeout(HCkMhtW cHandle, int newVal);
void CkMhtW_getDebugHtmlAfter(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putDebugHtmlAfter(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getDebugHtmlBefore(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putDebugHtmlBefore(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getDebugLogFilePath(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putDebugLogFilePath(HCkMhtW cHandle, const wchar_t *newVal);
BOOL CkMhtW_getDebugTagCleaning(HCkMhtW cHandle);
void CkMhtW_putDebugTagCleaning(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getEmbedImages(HCkMhtW cHandle);
void CkMhtW_putEmbedImages(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getEmbedLocalOnly(HCkMhtW cHandle);
void CkMhtW_putEmbedLocalOnly(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getFetchFromCache(HCkMhtW cHandle);
void CkMhtW_putFetchFromCache(HCkMhtW cHandle, BOOL newVal);
int CkMhtW_getHeartbeatMs(HCkMhtW cHandle);
void CkMhtW_putHeartbeatMs(HCkMhtW cHandle, int newVal);
BOOL CkMhtW_getIgnoreMustRevalidate(HCkMhtW cHandle);
void CkMhtW_putIgnoreMustRevalidate(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getIgnoreNoCache(HCkMhtW cHandle);
void CkMhtW_putIgnoreNoCache(HCkMhtW cHandle, BOOL newVal);
void CkMhtW_getLastErrorHtml(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_getLastErrorText(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_getLastErrorXml(HCkMhtW cHandle, HCkStringW retval);
BOOL CkMhtW_getNoScripts(HCkMhtW cHandle);
void CkMhtW_putNoScripts(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getNtlmAuth(HCkMhtW cHandle);
void CkMhtW_putNtlmAuth(HCkMhtW cHandle, BOOL newVal);
int CkMhtW_getNumCacheLevels(HCkMhtW cHandle);
void CkMhtW_putNumCacheLevels(HCkMhtW cHandle, int newVal);
int CkMhtW_getNumCacheRoots(HCkMhtW cHandle);
BOOL CkMhtW_getPreferMHTScripts(HCkMhtW cHandle);
void CkMhtW_putPreferMHTScripts(HCkMhtW cHandle, BOOL newVal);
void CkMhtW_getProxy(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putProxy(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getProxyLogin(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putProxyLogin(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getProxyPassword(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putProxyPassword(HCkMhtW cHandle, const wchar_t *newVal);
int CkMhtW_getReadTimeout(HCkMhtW cHandle);
void CkMhtW_putReadTimeout(HCkMhtW cHandle, int newVal);
void CkMhtW_getSocksHostname(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putSocksHostname(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getSocksPassword(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putSocksPassword(HCkMhtW cHandle, const wchar_t *newVal);
int CkMhtW_getSocksPort(HCkMhtW cHandle);
void CkMhtW_putSocksPort(HCkMhtW cHandle, int newVal);
void CkMhtW_getSocksUsername(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putSocksUsername(HCkMhtW cHandle, const wchar_t *newVal);
int CkMhtW_getSocksVersion(HCkMhtW cHandle);
void CkMhtW_putSocksVersion(HCkMhtW cHandle, int newVal);
BOOL CkMhtW_getUnpackUseRelPaths(HCkMhtW cHandle);
void CkMhtW_putUnpackUseRelPaths(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getUpdateCache(HCkMhtW cHandle);
void CkMhtW_putUpdateCache(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getUseCids(HCkMhtW cHandle);
void CkMhtW_putUseCids(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getUseFilename(HCkMhtW cHandle);
void CkMhtW_putUseFilename(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getUseIEProxy(HCkMhtW cHandle);
void CkMhtW_putUseIEProxy(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getUseInline(HCkMhtW cHandle);
void CkMhtW_putUseInline(HCkMhtW cHandle, BOOL newVal);
BOOL CkMhtW_getVerboseLogging(HCkMhtW cHandle);
void CkMhtW_putVerboseLogging(HCkMhtW cHandle, BOOL newVal);
void CkMhtW_getVersion(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_getWebSiteLogin(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putWebSiteLogin(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getWebSiteLoginDomain(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putWebSiteLoginDomain(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_getWebSitePassword(HCkMhtW cHandle, HCkStringW retval);
void CkMhtW_putWebSitePassword(HCkMhtW cHandle, const wchar_t *newVal);
void CkMhtW_AddCacheRoot(HCkMhtW cHandle, const wchar_t *dir);
void CkMhtW_AddCustomHeader(HCkMhtW cHandle, const wchar_t *name, const wchar_t *value);
void CkMhtW_AddExternalStyleSheet(HCkMhtW cHandle, const wchar_t *url);
void CkMhtW_ClearCustomHeaders(HCkMhtW cHandle);
void CkMhtW_ExcludeImagesMatching(HCkMhtW cHandle, const wchar_t *pattern);
BOOL CkMhtW_GetAndSaveEML(HCkMhtW cHandle, const wchar_t *url, const wchar_t *emlPath);
BOOL CkMhtW_GetAndSaveMHT(HCkMhtW cHandle, const wchar_t *url, const wchar_t *mhtPath);
BOOL CkMhtW_GetAndZipEML(HCkMhtW cHandle, const wchar_t *url, const wchar_t *zipEntryFilename, const wchar_t *zipPath);
BOOL CkMhtW_GetAndZipMHT(HCkMhtW cHandle, const wchar_t *url, const wchar_t *zipEntryFilename, const wchar_t *zipPath);
BOOL CkMhtW_GetCacheRoot(HCkMhtW cHandle, int index, HCkStringW outStr);
BOOL CkMhtW_GetEML(HCkMhtW cHandle, const wchar_t *url, HCkStringW outStr);
HCkEmailW CkMhtW_GetEmail(HCkMhtW cHandle, const wchar_t *url);
BOOL CkMhtW_GetMHT(HCkMhtW cHandle, const wchar_t *url, HCkStringW outStr);
HCkMimeW CkMhtW_GetMime(HCkMhtW cHandle, const wchar_t *url);
BOOL CkMhtW_HtmlToEML(HCkMhtW cHandle, const wchar_t *htmlText, HCkStringW outStr);
BOOL CkMhtW_HtmlToEMLFile(HCkMhtW cHandle, const wchar_t *html, const wchar_t *emlPath);
HCkEmailW CkMhtW_HtmlToEmail(HCkMhtW cHandle, const wchar_t *htmlText);
BOOL CkMhtW_HtmlToMHT(HCkMhtW cHandle, const wchar_t *htmlText, HCkStringW outStr);
BOOL CkMhtW_HtmlToMHTFile(HCkMhtW cHandle, const wchar_t *html, const wchar_t *mhtPath);
BOOL CkMhtW_IsUnlocked(HCkMhtW cHandle);
void CkMhtW_RemoveCustomHeader(HCkMhtW cHandle, const wchar_t *name);
void CkMhtW_RestoreDefaults(HCkMhtW cHandle);
BOOL CkMhtW_SaveLastError(HCkMhtW cHandle, const wchar_t *path);
BOOL CkMhtW_UnlockComponent(HCkMhtW cHandle, const wchar_t *unlockCode);
BOOL CkMhtW_UnpackMHT(HCkMhtW cHandle, const wchar_t *mhtPath, const wchar_t *unpackDir, const wchar_t *htmlFilename, const wchar_t *partsSubDir);
BOOL CkMhtW_UnpackMHTString(HCkMhtW cHandle, const wchar_t *mhtContents, const wchar_t *unpackDir, const wchar_t *htmlFilename, const wchar_t *partsSubDir);
const wchar_t *CkMhtW__baseUrl(HCkMhtW cHandle);
const wchar_t *CkMhtW__cacheRoot(HCkMhtW cHandle, int index);
const wchar_t *CkMhtW__debugHtmlAfter(HCkMhtW cHandle);
const wchar_t *CkMhtW__debugHtmlBefore(HCkMhtW cHandle);
const wchar_t *CkMhtW__debugLogFilePath(HCkMhtW cHandle);
const wchar_t *CkMhtW__eML(HCkMhtW cHandle, const wchar_t *url);
const wchar_t *CkMhtW__getCacheRoot(HCkMhtW cHandle, int index);
const wchar_t *CkMhtW__getEML(HCkMhtW cHandle, const wchar_t *url);
const wchar_t *CkMhtW__getMHT(HCkMhtW cHandle, const wchar_t *url);
const wchar_t *CkMhtW__htmlToEML(HCkMhtW cHandle, const wchar_t *htmlText);
const wchar_t *CkMhtW__htmlToMHT(HCkMhtW cHandle, const wchar_t *htmlText);
const wchar_t *CkMhtW__lastErrorHtml(HCkMhtW cHandle);
const wchar_t *CkMhtW__lastErrorText(HCkMhtW cHandle);
const wchar_t *CkMhtW__lastErrorXml(HCkMhtW cHandle);
const wchar_t *CkMhtW__mHT(HCkMhtW cHandle, const wchar_t *url);
const wchar_t *CkMhtW__proxy(HCkMhtW cHandle);
const wchar_t *CkMhtW__proxyLogin(HCkMhtW cHandle);
const wchar_t *CkMhtW__proxyPassword(HCkMhtW cHandle);
const wchar_t *CkMhtW__socksHostname(HCkMhtW cHandle);
const wchar_t *CkMhtW__socksPassword(HCkMhtW cHandle);
const wchar_t *CkMhtW__socksUsername(HCkMhtW cHandle);
const wchar_t *CkMhtW__version(HCkMhtW cHandle);
const wchar_t *CkMhtW__webSiteLogin(HCkMhtW cHandle);
const wchar_t *CkMhtW__webSiteLoginDomain(HCkMhtW cHandle);
const wchar_t *CkMhtW__webSitePassword(HCkMhtW cHandle);
#endif
