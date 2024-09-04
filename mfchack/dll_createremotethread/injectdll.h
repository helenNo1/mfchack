#pragma once

#include "pch.h"

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif // 

	// 使用 CreateRemoteThread 实现远线程注入
	__declspec(dllexport)   BOOL CreateRemoteThreadInjectDll(const char* processName, const char* pszDllFileName);

#ifdef __cplusplus
}
#endif /





