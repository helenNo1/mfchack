#pragma once


#include "pch.h"

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

	// ʹ�� ZwCreateThreadEx ʵ��Զ�߳�ע��
	__declspec(dllexport)	  BOOL ZwCreateThreadExInjectDll(const char* pszProcessName, const char* pszDllFileName);

#ifdef __cplusplus
}
#endif

