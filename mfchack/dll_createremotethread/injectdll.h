#pragma once

#include "pch.h"

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif // 

	// ʹ�� CreateRemoteThread ʵ��Զ�߳�ע��
	__declspec(dllexport)   BOOL CreateRemoteThreadInjectDll(const char* processName, const char* pszDllFileName);

#ifdef __cplusplus
}
#endif /





