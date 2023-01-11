// This is a generated source file for Chilkat version 9.4.1.34
#ifndef _C_CkTar_W_H
#define _C_CkTar_W_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkTarW CkTarW_Create(void);
HCkTarW CkTarW_Create2(BOOL bForDso);
void CkTarW_Dispose(HCkTarW handle);
void CkTarW_getCharset(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putCharset(HCkTarW cHandle, const wchar_t *newVal);
void CkTarW_getDebugLogFilePath(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putDebugLogFilePath(HCkTarW cHandle, const wchar_t *newVal);
int CkTarW_getDirMode(HCkTarW cHandle);
void CkTarW_putDirMode(HCkTarW cHandle, int newVal);
void CkTarW_getDirPrefix(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putDirPrefix(HCkTarW cHandle, const wchar_t *newVal);
int CkTarW_getFileMode(HCkTarW cHandle);
void CkTarW_putFileMode(HCkTarW cHandle, int newVal);
int CkTarW_getGroupId(HCkTarW cHandle);
void CkTarW_putGroupId(HCkTarW cHandle, int newVal);
void CkTarW_getGroupName(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putGroupName(HCkTarW cHandle, const wchar_t *newVal);
int CkTarW_getHeartbeatMs(HCkTarW cHandle);
void CkTarW_putHeartbeatMs(HCkTarW cHandle, int newVal);
void CkTarW_getLastErrorHtml(HCkTarW cHandle, HCkStringW retval);
void CkTarW_getLastErrorText(HCkTarW cHandle, HCkStringW retval);
void CkTarW_getLastErrorXml(HCkTarW cHandle, HCkStringW retval);
BOOL CkTarW_getNoAbsolutePaths(HCkTarW cHandle);
void CkTarW_putNoAbsolutePaths(HCkTarW cHandle, BOOL newVal);
int CkTarW_getNumDirRoots(HCkTarW cHandle);
int CkTarW_getScriptFileMode(HCkTarW cHandle);
void CkTarW_putScriptFileMode(HCkTarW cHandle, int newVal);
BOOL CkTarW_getUntarCaseSensitive(HCkTarW cHandle);
void CkTarW_putUntarCaseSensitive(HCkTarW cHandle, BOOL newVal);
BOOL CkTarW_getUntarDebugLog(HCkTarW cHandle);
void CkTarW_putUntarDebugLog(HCkTarW cHandle, BOOL newVal);
BOOL CkTarW_getUntarDiscardPaths(HCkTarW cHandle);
void CkTarW_putUntarDiscardPaths(HCkTarW cHandle, BOOL newVal);
void CkTarW_getUntarFromDir(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putUntarFromDir(HCkTarW cHandle, const wchar_t *newVal);
void CkTarW_getUntarMatchPattern(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putUntarMatchPattern(HCkTarW cHandle, const wchar_t *newVal);
int CkTarW_getUntarMaxCount(HCkTarW cHandle);
void CkTarW_putUntarMaxCount(HCkTarW cHandle, int newVal);
int CkTarW_getUserId(HCkTarW cHandle);
void CkTarW_putUserId(HCkTarW cHandle, int newVal);
void CkTarW_getUserName(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putUserName(HCkTarW cHandle, const wchar_t *newVal);
BOOL CkTarW_getVerboseLogging(HCkTarW cHandle);
void CkTarW_putVerboseLogging(HCkTarW cHandle, BOOL newVal);
void CkTarW_getVersion(HCkTarW cHandle, HCkStringW retval);
void CkTarW_getWriteFormat(HCkTarW cHandle, HCkStringW retval);
void CkTarW_putWriteFormat(HCkTarW cHandle, const wchar_t *newVal);
BOOL CkTarW_AddDirRoot(HCkTarW cHandle, const wchar_t *dirPath);
BOOL CkTarW_GetDirRoot(HCkTarW cHandle, int index, HCkStringW outStr);
BOOL CkTarW_ListXml(HCkTarW cHandle, const wchar_t *tarPath, HCkStringW outStr);
BOOL CkTarW_SaveLastError(HCkTarW cHandle, const wchar_t *path);
BOOL CkTarW_UnlockComponent(HCkTarW cHandle, const wchar_t *unlockCode);
int CkTarW_Untar(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_UntarBz2(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_UntarFirstMatchingToMemory(HCkTarW cHandle, HCkByteDataW tarFileBytes, const wchar_t *matchPattern, HCkByteDataW outBytes);
int CkTarW_UntarFromMemory(HCkTarW cHandle, HCkByteDataW tarFileBytes);
BOOL CkTarW_UntarGz(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_UntarZ(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_VerifyTar(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_WriteTar(HCkTarW cHandle, const wchar_t *tarPath);
BOOL CkTarW_WriteTarBz2(HCkTarW cHandle, const wchar_t *bz2Path);
BOOL CkTarW_WriteTarGz(HCkTarW cHandle, const wchar_t *gzPath);
const wchar_t *CkTarW__charset(HCkTarW cHandle);
const wchar_t *CkTarW__debugLogFilePath(HCkTarW cHandle);
const wchar_t *CkTarW__dirPrefix(HCkTarW cHandle);
const wchar_t *CkTarW__dirRoot(HCkTarW cHandle, int index);
const wchar_t *CkTarW__getDirRoot(HCkTarW cHandle, int index);
const wchar_t *CkTarW__groupName(HCkTarW cHandle);
const wchar_t *CkTarW__lastErrorHtml(HCkTarW cHandle);
const wchar_t *CkTarW__lastErrorText(HCkTarW cHandle);
const wchar_t *CkTarW__lastErrorXml(HCkTarW cHandle);
const wchar_t *CkTarW__listXml(HCkTarW cHandle, const wchar_t *tarPath);
const wchar_t *CkTarW__untarFromDir(HCkTarW cHandle);
const wchar_t *CkTarW__untarMatchPattern(HCkTarW cHandle);
const wchar_t *CkTarW__userName(HCkTarW cHandle);
const wchar_t *CkTarW__version(HCkTarW cHandle);
const wchar_t *CkTarW__writeFormat(HCkTarW cHandle);
#endif
