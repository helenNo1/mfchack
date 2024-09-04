#pragma once

// CreateProcess_Test.cpp : 定义控制台应用程序的入口点。
//

#include "pch.h"



BOOL WinExec_Test(char* pszExePath, UINT uiCmdShow);



BOOL ShellExecute_Test(char* pszExePath, UINT uiCmdShow);


BOOL CreateProcess_Test(char* pszExePath, UINT uiCmdShow);





#ifdef __cplusplus
extern "C" {
#endif // DEBUG
	__declspec(dllexport) int ApiCreateProc(char* pszExePath, UINT uiCmdShow);
	
#ifdef __cplusplus
}
#endif // DEBUG
