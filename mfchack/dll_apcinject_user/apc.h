#pragma once

#include "pch.h"

#include <Windows.h>
#include <TlHelp32.h>

#ifdef __cplusplus
extern "C" {
#endif // DEBUG

__declspec(dllexport) BOOL ApcInjectDll(char* pszProcessName, char* pszDllName);

#ifdef __cplusplus
}
#endif // DEBUG

// ����PID��ȡ���е���Ӧ�߳�ID
BOOL GetAllThreadIdByProcessId(DWORD dwProcessId, DWORD** ppThreadId, DWORD* dwThreadIdLength);

// APCע��
BOOL ApcInjectDll(char* pszProcessName, char* pszDllName);
