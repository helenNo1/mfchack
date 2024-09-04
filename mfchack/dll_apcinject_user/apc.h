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

// 根据PID获取所有的相应线程ID
BOOL GetAllThreadIdByProcessId(DWORD dwProcessId, DWORD** ppThreadId, DWORD* dwThreadIdLength);

// APC注入
BOOL ApcInjectDll(char* pszProcessName, char* pszDllName);
