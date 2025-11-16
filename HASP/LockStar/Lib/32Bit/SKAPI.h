#ifndef __SKAPI_H__
#define __SKAPI_H__

#define MAX_PK_SIZE 7928

typedef struct
{
	GUID	guidDevelop;
	DWORD	dwReadPassword;
	DWORD	dwWritePassword;
	BYTE	byEncryptKey[16];
	DWORD   dwValidateOption;
	DWORD	dwStartDate;
	DWORD	dwEndDate;
} SKCONTROLDATA, *PSKCONTROLDATA;

#if defined _M_IX86
typedef BOOL (WINAPI *ENUMDEVICEPROC)(GUID* pidDevice, DWORD dwParam);
#endif
#if defined _WIN64
typedef BOOL (WINAPI *ENUMDEVICEPROC)(GUID* pidDevice, void* dwParam);
#endif

#define SKAPI_ALGORITHM_IDEA		1
#define SKAPI_ALGORITHM_HARDWARE	10


#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SKAPIInitialize();
void WINAPI SKAPIClose();


BOOL WINAPI SKAPIChangeAdminPassword(const GUID* pidDevice, const BYTE* pbyOld, const BYTE* pbyNew);
BOOL WINAPI SKAPIGetControlData(const GUID* pidDevice, const BYTE* pbyPassword, SKCONTROLDATA* pcd);
BOOL WINAPI SKAPISetControlData(const GUID* pidDevice, const BYTE* pbyPassword, const SKCONTROLDATA* pcd);
#if defined _M_IX86
BOOL WINAPI SKAPIEnumDevices(ENUMDEVICEPROC lpEnumProc, DWORD dwParam);
#endif
#if defined _WIN64
BOOL WINAPI SKAPIEnumDevices(ENUMDEVICEPROC lpEnumProc, void* dwParam);
#endif
BOOL WINAPI SKAPIGetUserData(const GUID* pidDevelop, const DWORD dwReadPassword, BYTE* pbyData);
BOOL WINAPI SKAPISetUserData(const GUID* pidDevelop, const DWORD dwWritePassword, const BYTE* pbyData);

BOOL WINAPI SKAPIInitEncryptKey(const UINT nAlgorithm, const GUID* pidDevelop, const BYTE* byKey);
BOOL WINAPI SKAPIEncrypt(BYTE* byData);
BOOL WINAPI SKAPIDecrypt(BYTE* byData);

//Hardware perform sha1 hash
BOOL WINAPI PKAPISHA1HashbyHard(const GUID* pidDevelop, DWORD lpUserReadPassword,BYTE* pucData,DWORD ulLength,BYTE* pucDigest);
//software perform sha1 hash
BOOL WINAPI PKAPISHA1HashbySoft(const GUID* pidDevelop,DWORD lpUserReadPassword,BYTE* pucData,DWORD ulLength,BYTE* pucKey,DWORD ulKeyLength, BYTE* pucDigest);
//Hardware generate 16 bytes random
BOOL WINAPI PKAPIGenRandom(const GUID* pidDevelop,	DWORD lpUserReadPassword,BYTE* pucBuffer,DWORD ulBufferSize);

//write key stored in key hardware
BOOL WINAPI PKAPIWriteKey(const GUID* pidDevice,LPCSTR lpAdminPassword, BYTE* pucKey,DWORD ulKeySize);

// read user data by deviceid and developid
BOOL WINAPI PKAPIGetUserData(const GUID* pidDevice, const GUID* pidDevelop, const DWORD dwReadPassword, BYTE* pbyData);
// write user data by deviceid and developid
BOOL WINAPI PKAPISetUserData(const GUID* pidDevice, const GUID* pidDevelop, const DWORD dwWritePassword, const BYTE* pbyData);


BOOL WINAPI PKAPIGetUserDataEx(const GUID* pidDevice, const GUID* pidDevelop, const DWORD dwReadPassword, DWORD dwOffset, BYTE* pbyData, DWORD dwLength);
BOOL WINAPI PKAPISetUserDataEx(const GUID* pidDevice, const GUID* pidDevelop, const DWORD dwWritePassword, DWORD dwOffset, const BYTE* pbyData, DWORD dwLength);

BOOL WINAPI PKAPISHA1HashbyHardEx(const GUID* pidDevice, const GUID* pidDevelop, DWORD dwReadPassword,BYTE* pucData,DWORD ulLength,BYTE* pucDigest);


#ifdef __cplusplus
}
#endif

#endif	// __SKAPI_H__