#pragma once


#include "pch.h"

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

	// 使用 ZwCreateThreadEx 实现远线程注入
	__declspec(dllexport)	  BOOL ZwCreateThreadExInjectDll(const char* pszProcessName, const char* pszDllFileName);

#ifdef __cplusplus
}
#endif

