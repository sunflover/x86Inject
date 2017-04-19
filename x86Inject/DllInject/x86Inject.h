#pragma once
#include "MyOutputDebugString.h"
#include <shlwapi.h>
#pragma comment (lib, "shlwapi.lib")

//Native DLL L"C:\\Windows\\System32\\sfc.dll";

typedef struct _LSA_UNICODE_STRING{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

typedef NTSTATUS (NTAPI *pRtlInitUnicodeString)(PUNICODE_STRING,PCWSTR);
typedef NTSTATUS (NTAPI *pLdrLoadDll)(PWCHAR,ULONG,PUNICODE_STRING,PHANDLE);

typedef struct _THREAD_DATA
{
	pRtlInitUnicodeString fnRtlInitUnicodeString;
	pLdrLoadDll fnLdrLoadDll;
	UNICODE_STRING UnicodeString;
	WCHAR DllName[260];
	PWCHAR DllPath;
	ULONG Flags;
	HANDLE ModuleHandle;
}THREAD_DATA,*PTHREAD_DATA;

typedef VOID (WINAPI *fRtlInitUnicodeString)(PUNICODE_STRING DestinationString,PCWSTR ourceString);

typedef NTSTATUS (WINAPI *fLdrLoadDll)(IN PWCHAR PathToFile OPTIONAL, IN ULONG Flags OPTIONAL, IN PUNICODE_STRING  ModuleFileName, OUT PHANDLE ModuleHandle);

typedef DWORD64 (WINAPI *_NtCreateThreadEx64)(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, LPVOID ObjectAttributes, HANDLE ProcessHandle, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, BOOL CreateSuspended, DWORD64 dwStackSize, DWORD64 dw1, DWORD64 dw2, LPVOID Unknown);

typedef DWORD (WINAPI *_NtCreateThreadEx32)(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, LPVOID ObjectAttributes, HANDLE ProcessHandle, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, BOOL CreateSuspended, DWORD dwStackSize, DWORD dw1, DWORD dw2, LPVOID Unknown); 

class Cx86Inject
{
public:
	Cx86Inject(void);
	~Cx86Inject(void);
	BOOL InjectDll(DWORD dwProcessId,LPCWSTR lpcwDllPath);
private:
	BOOL EnableDebugPrivilege();
	BOOL IsVistaOrLater();
	HANDLE MyCreateRemoteThread(HANDLE hProcess, LPTHREAD_START_ROUTINE pThreadProc, LPVOID pRemoteBuf);
};

