// This is a generated source file for Chilkat version 9.4.1.34
#ifndef _C_CkImap_W_H
#define _C_CkImap_W_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkImapW CkImapW_Create(void);
HCkImapW CkImapW_Create2(BOOL bForDso);
void CkImapW_Dispose(HCkImapW handle);
BOOL CkImapW_getAppendSeen(HCkImapW cHandle);
void CkImapW_putAppendSeen(HCkImapW cHandle, BOOL newVal);
int CkImapW_getAppendUid(HCkImapW cHandle);
void CkImapW_getAuthMethod(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putAuthMethod(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getAuthzId(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putAuthzId(HCkImapW cHandle, const wchar_t *newVal);
BOOL CkImapW_getAutoDownloadAttachments(HCkImapW cHandle);
void CkImapW_putAutoDownloadAttachments(HCkImapW cHandle, BOOL newVal);
BOOL CkImapW_getAutoFix(HCkImapW cHandle);
void CkImapW_putAutoFix(HCkImapW cHandle, BOOL newVal);
void CkImapW_getClientIpAddress(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putClientIpAddress(HCkImapW cHandle, const wchar_t *newVal);
int CkImapW_getConnectTimeout(HCkImapW cHandle);
void CkImapW_putConnectTimeout(HCkImapW cHandle, int newVal);
void CkImapW_getConnectedToHost(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getDebugLogFilePath(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putDebugLogFilePath(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getDomain(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putDomain(HCkImapW cHandle, const wchar_t *newVal);
int CkImapW_getHeartbeatMs(HCkImapW cHandle);
void CkImapW_putHeartbeatMs(HCkImapW cHandle, int newVal);
void CkImapW_getHttpProxyAuthMethod(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putHttpProxyAuthMethod(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getHttpProxyDomain(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putHttpProxyDomain(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getHttpProxyHostname(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putHttpProxyHostname(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getHttpProxyPassword(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putHttpProxyPassword(HCkImapW cHandle, const wchar_t *newVal);
int CkImapW_getHttpProxyPort(HCkImapW cHandle);
void CkImapW_putHttpProxyPort(HCkImapW cHandle, int newVal);
void CkImapW_getHttpProxyUsername(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putHttpProxyUsername(HCkImapW cHandle, const wchar_t *newVal);
BOOL CkImapW_getKeepSessionLog(HCkImapW cHandle);
void CkImapW_putKeepSessionLog(HCkImapW cHandle, BOOL newVal);
void CkImapW_getLastAppendedMime(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastCommand(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastErrorHtml(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastErrorText(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastErrorXml(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastIntermediateResponse(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLastResponse(HCkImapW cHandle, HCkStringW retval);
void CkImapW_getLoggedInUser(HCkImapW cHandle, HCkStringW retval);
int CkImapW_getNumMessages(HCkImapW cHandle);
BOOL CkImapW_getPeekMode(HCkImapW cHandle);
void CkImapW_putPeekMode(HCkImapW cHandle, BOOL newVal);
int CkImapW_getPort(HCkImapW cHandle);
void CkImapW_putPort(HCkImapW cHandle, int newVal);
int CkImapW_getReadTimeout(HCkImapW cHandle);
void CkImapW_putReadTimeout(HCkImapW cHandle, int newVal);
void CkImapW_getSearchCharset(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putSearchCharset(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getSelectedMailbox(HCkImapW cHandle, HCkStringW retval);
int CkImapW_getSendBufferSize(HCkImapW cHandle);
void CkImapW_putSendBufferSize(HCkImapW cHandle, int newVal);
char CkImapW_getSeparatorChar(HCkImapW cHandle);
void CkImapW_putSeparatorChar(HCkImapW cHandle, char newVal);
void CkImapW_getSessionLog(HCkImapW cHandle, HCkStringW retval);
int CkImapW_getSoRcvBuf(HCkImapW cHandle);
void CkImapW_putSoRcvBuf(HCkImapW cHandle, int newVal);
int CkImapW_getSoSndBuf(HCkImapW cHandle);
void CkImapW_putSoSndBuf(HCkImapW cHandle, int newVal);
void CkImapW_getSocksHostname(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putSocksHostname(HCkImapW cHandle, const wchar_t *newVal);
void CkImapW_getSocksPassword(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putSocksPassword(HCkImapW cHandle, const wchar_t *newVal);
int CkImapW_getSocksPort(HCkImapW cHandle);
void CkImapW_putSocksPort(HCkImapW cHandle, int newVal);
void CkImapW_getSocksUsername(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putSocksUsername(HCkImapW cHandle, const wchar_t *newVal);
int CkImapW_getSocksVersion(HCkImapW cHandle);
void CkImapW_putSocksVersion(HCkImapW cHandle, int newVal);
BOOL CkImapW_getSsl(HCkImapW cHandle);
void CkImapW_putSsl(HCkImapW cHandle, BOOL newVal);
void CkImapW_getSslProtocol(HCkImapW cHandle, HCkStringW retval);
void CkImapW_putSslProtocol(HCkImapW cHandle, const wchar_t *newVal);
BOOL CkImapW_getSslServerCertVerified(HCkImapW cHandle);
BOOL CkImapW_getStartTls(HCkImapW cHandle);
void CkImapW_putStartTls(HCkImapW cHandle, BOOL newVal);
int CkImapW_getUidNext(HCkImapW cHandle);
int CkImapW_getUidValidity(HCkImapW cHandle);
BOOL CkImapW_getVerboseLogging(HCkImapW cHandle);
void CkImapW_putVerboseLogging(HCkImapW cHandle, BOOL newVal);
void CkImapW_getVersion(HCkImapW cHandle, HCkStringW retval);
BOOL CkImapW_AddPfxSourceData(HCkImapW cHandle, HCkByteDataW pfxData, const wchar_t *password);
BOOL CkImapW_AddPfxSourceFile(HCkImapW cHandle, const wchar_t *pfxFilePath, const wchar_t *password);
BOOL CkImapW_AppendMail(HCkImapW cHandle, const wchar_t *mailbox, HCkEmailW email);
BOOL CkImapW_AppendMime(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText);
BOOL CkImapW_AppendMimeWithDate(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, SYSTEMTIME *internalDate);
BOOL CkImapW_AppendMimeWithDateStr(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, const wchar_t *internalDateStr);
BOOL CkImapW_AppendMimeWithFlags(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, BOOL seen, BOOL flagged, BOOL answered, BOOL draft);
HCkMessageSetW CkImapW_CheckForNewEmail(HCkImapW cHandle);
void CkImapW_ClearSessionLog(HCkImapW cHandle);
BOOL CkImapW_CloseMailbox(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_Connect(HCkImapW cHandle, const wchar_t *hostname);
BOOL CkImapW_Copy(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *copyToMailbox);
BOOL CkImapW_CopyMultiple(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *copyToMailbox);
BOOL CkImapW_CopySequence(HCkImapW cHandle, int startSeqNum, int count, const wchar_t *copyToMailbox);
BOOL CkImapW_CreateMailbox(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_DeleteMailbox(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_Disconnect(HCkImapW cHandle);
BOOL CkImapW_ExamineMailbox(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_Expunge(HCkImapW cHandle);
BOOL CkImapW_ExpungeAndClose(HCkImapW cHandle);
BOOL CkImapW_FetchAttachment(HCkImapW cHandle, HCkEmailW email, int attachIndex, const wchar_t *saveToPath);
BOOL CkImapW_FetchAttachmentBytes(HCkImapW cHandle, HCkEmailW email, int attachIndex, HCkByteDataW outBytes);
BOOL CkImapW_FetchAttachmentString(HCkImapW cHandle, HCkEmailW email, int attachIndex, const wchar_t *charset, HCkStringW outStr);
HCkEmailBundleW CkImapW_FetchBundle(HCkImapW cHandle, HCkMessageSetW messageSet);
HCkStringArrayW CkImapW_FetchBundleAsMime(HCkImapW cHandle, HCkMessageSetW messageSet);
HCkEmailBundleW CkImapW_FetchChunk(HCkImapW cHandle, int startSeqNum, int count, HCkMessageSetW failedSet, HCkMessageSetW fetchedSet);
BOOL CkImapW_FetchFlags(HCkImapW cHandle, int msgId, BOOL bUid, HCkStringW outStrFlags);
HCkEmailBundleW CkImapW_FetchHeaders(HCkImapW cHandle, HCkMessageSetW messageSet);
HCkEmailBundleW CkImapW_FetchSequence(HCkImapW cHandle, int startSeqNum, int numMessages);
HCkStringArrayW CkImapW_FetchSequenceAsMime(HCkImapW cHandle, int startSeqNum, int count);
HCkEmailBundleW CkImapW_FetchSequenceHeaders(HCkImapW cHandle, int startSeqNum, int numMessages);
HCkEmailW CkImapW_FetchSingle(HCkImapW cHandle, int msgId, BOOL bUid);
BOOL CkImapW_FetchSingleAsMime(HCkImapW cHandle, int msgId, BOOL bUid, HCkStringW outStrMime);
HCkEmailW CkImapW_FetchSingleHeader(HCkImapW cHandle, int msgId, BOOL bUid);
BOOL CkImapW_FetchSingleHeaderAsMime(HCkImapW cHandle, int msgId, BOOL bUID, HCkStringW outStr);
HCkMessageSetW CkImapW_GetAllUids(HCkImapW cHandle);
BOOL CkImapW_GetMailAttachFilename(HCkImapW cHandle, HCkEmailW email, int attachIndex, HCkStringW outStrFilename);
int CkImapW_GetMailAttachSize(HCkImapW cHandle, HCkEmailW email, int attachIndex);
int CkImapW_GetMailFlag(HCkImapW cHandle, HCkEmailW email, const wchar_t *flagName);
int CkImapW_GetMailNumAttach(HCkImapW cHandle, HCkEmailW email);
int CkImapW_GetMailSize(HCkImapW cHandle, HCkEmailW email);
HCkCertW CkImapW_GetSslServerCert(HCkImapW cHandle);
BOOL CkImapW_IsConnected(HCkImapW cHandle);
BOOL CkImapW_IsLoggedIn(HCkImapW cHandle);
BOOL CkImapW_IsUnlocked(HCkImapW cHandle);
HCkMailboxesW CkImapW_ListMailboxes(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
HCkMailboxesW CkImapW_ListSubscribed(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
BOOL CkImapW_Login(HCkImapW cHandle, const wchar_t *login, const wchar_t *password);
BOOL CkImapW_Logout(HCkImapW cHandle);
BOOL CkImapW_Noop(HCkImapW cHandle);
BOOL CkImapW_RefetchMailFlags(HCkImapW cHandle, HCkEmailW emailInOut);
BOOL CkImapW_RenameMailbox(HCkImapW cHandle, const wchar_t *fromMailbox, const wchar_t *toMailbox);
BOOL CkImapW_SaveLastError(HCkImapW cHandle, const wchar_t *path);
HCkMessageSetW CkImapW_Search(HCkImapW cHandle, const wchar_t *criteria, BOOL bUid);
BOOL CkImapW_SelectMailbox(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_SendRawCommand(HCkImapW cHandle, const wchar_t *rawCommand, HCkStringW outRawResponse);
BOOL CkImapW_SendRawCommandB(HCkImapW cHandle, const wchar_t *cmd, HCkByteDataW outBytes);
BOOL CkImapW_SendRawCommandC(HCkImapW cHandle, HCkByteDataW cmd, HCkByteDataW outBytes);
#if defined(CK_CSP_INCLUDED)
BOOL CkImapW_SetCSP(HCkImapW cHandle, HCkCspW csp);
#endif
BOOL CkImapW_SetDecryptCert2(HCkImapW cHandle, HCkCertW cert, HCkPrivateKeyW key);
BOOL CkImapW_SetFlag(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagName, int value);
BOOL CkImapW_SetFlags(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *flagName, int value);
BOOL CkImapW_SetMailFlag(HCkImapW cHandle, HCkEmailW email, const wchar_t *flagName, int value);
BOOL CkImapW_SetSslClientCert(HCkImapW cHandle, HCkCertW cert);
BOOL CkImapW_SetSslClientCertPem(HCkImapW cHandle, const wchar_t *pemDataOrPath, const wchar_t *pemPassword);
BOOL CkImapW_SetSslClientCertPfx(HCkImapW cHandle, const wchar_t *pfxPath, const wchar_t *pfxPassword);
BOOL CkImapW_SshAuthenticatePk(HCkImapW cHandle, const wchar_t *sshLogin, HCkSshKeyW privateKey);
BOOL CkImapW_SshAuthenticatePw(HCkImapW cHandle, const wchar_t *sshLogin, const wchar_t *sshPassword);
BOOL CkImapW_SshTunnel(HCkImapW cHandle, const wchar_t *sshServerHostname, int sshServerPort);
BOOL CkImapW_StoreFlags(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagName, int value);
BOOL CkImapW_Subscribe(HCkImapW cHandle, const wchar_t *mailbox);
BOOL CkImapW_UnlockComponent(HCkImapW cHandle, const wchar_t *unlockCode);
BOOL CkImapW_Unsubscribe(HCkImapW cHandle, const wchar_t *mailbox);
const wchar_t *CkImapW__authMethod(HCkImapW cHandle);
const wchar_t *CkImapW__authzId(HCkImapW cHandle);
const wchar_t *CkImapW__clientIpAddress(HCkImapW cHandle);
const wchar_t *CkImapW__connectedToHost(HCkImapW cHandle);
const wchar_t *CkImapW__debugLogFilePath(HCkImapW cHandle);
const wchar_t *CkImapW__domain(HCkImapW cHandle);
const wchar_t *CkImapW__fetchAttachmentString(HCkImapW cHandle, HCkEmailW email, int attachIndex, const wchar_t *charset);
const wchar_t *CkImapW__fetchFlags(HCkImapW cHandle, int msgId, BOOL bUid);
const wchar_t *CkImapW__fetchSingleAsMime(HCkImapW cHandle, int msgId, BOOL bUid);
const wchar_t *CkImapW__fetchSingleHeaderAsMime(HCkImapW cHandle, int msgId, BOOL bUID);
const wchar_t *CkImapW__getMailAttachFilename(HCkImapW cHandle, HCkEmailW email, int attachIndex);
const wchar_t *CkImapW__httpProxyAuthMethod(HCkImapW cHandle);
const wchar_t *CkImapW__httpProxyDomain(HCkImapW cHandle);
const wchar_t *CkImapW__httpProxyHostname(HCkImapW cHandle);
const wchar_t *CkImapW__httpProxyPassword(HCkImapW cHandle);
const wchar_t *CkImapW__httpProxyUsername(HCkImapW cHandle);
const wchar_t *CkImapW__lastAppendedMime(HCkImapW cHandle);
const wchar_t *CkImapW__lastCommand(HCkImapW cHandle);
const wchar_t *CkImapW__lastErrorHtml(HCkImapW cHandle);
const wchar_t *CkImapW__lastErrorText(HCkImapW cHandle);
const wchar_t *CkImapW__lastErrorXml(HCkImapW cHandle);
const wchar_t *CkImapW__lastIntermediateResponse(HCkImapW cHandle);
const wchar_t *CkImapW__lastResponse(HCkImapW cHandle);
const wchar_t *CkImapW__loggedInUser(HCkImapW cHandle);
const wchar_t *CkImapW__mailAttachFilename(HCkImapW cHandle, HCkEmailW email, int attachIndex);
const wchar_t *CkImapW__searchCharset(HCkImapW cHandle);
const wchar_t *CkImapW__selectedMailbox(HCkImapW cHandle);
const wchar_t *CkImapW__sendRawCommand(HCkImapW cHandle, const wchar_t *rawCommand);
const wchar_t *CkImapW__sessionLog(HCkImapW cHandle);
const wchar_t *CkImapW__socksHostname(HCkImapW cHandle);
const wchar_t *CkImapW__socksPassword(HCkImapW cHandle);
const wchar_t *CkImapW__socksUsername(HCkImapW cHandle);
const wchar_t *CkImapW__sslProtocol(HCkImapW cHandle);
const wchar_t *CkImapW__version(HCkImapW cHandle);
#endif
