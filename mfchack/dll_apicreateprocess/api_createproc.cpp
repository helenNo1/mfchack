#include "pch.h"
#include "api_createproc.h"
#include <Windows.h>
#include <shellapi.h>




BOOL WinExec_Test(char* pszExePath, UINT uiCmdShow)
{
	UINT uiRet = 0;
	uiRet = ::WinExec(pszExePath, uiCmdShow);
	if (31 < uiRet)
	{
		return TRUE;
	}
	return FALSE;
}


BOOL ShellExecute_Test(char* pszExePath, UINT uiCmdShow)
{
	HINSTANCE hInstance = 0;
	hInstance = ::ShellExecute(NULL, NULL, pszExePath, NULL, NULL, uiCmdShow);
	if (32 < (DWORD)hInstance)
	{
		return TRUE;
	}
	return FALSE;
}


BOOL CreateProcess_Test(char* pszExePath, UINT uiCmdShow)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	BOOL bRet = FALSE;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;  //指定wShowWindow成员有效
	si.wShowWindow = uiCmdShow;
	bRet = ::CreateProcess(NULL, pszExePath, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	if (bRet)
	{
		//不使用的句柄最好关掉
		::CloseHandle(pi.hThread);
		::CloseHandle(pi.hProcess);
		return TRUE;
	}
	return FALSE;
}


int ApiCreateProc(char* pszExePath, UINT uiCmdShow)
{
	BOOL bRet = FALSE;
	// 520.exe
	bRet = WinExec_Test(pszExePath, SW_SHOWNORMAL);
	if (bRet)
	{
		MessageBox(NULL, "winexec ok", "ok", MB_OK);
	}
	else
	{
		MessageBox(NULL, "winexec err", "err", MB_OK);
	}
	// 521.exe
	bRet = ShellExecute_Test(pszExePath, SW_SHOWNORMAL);
	if (bRet)
	{
		MessageBox(NULL, "shellexecute ok", "ok", MB_OK);
	}
	else
	{
		MessageBox(NULL, "shellexecute err", "err", MB_OK);
	}
	// 522.exe
	bRet = CreateProcess_Test(pszExePath, SW_SHOWNORMAL);
	if (bRet)
	{
		MessageBox(NULL, "createproc ok", "ok", MB_OK);
	}
	else
	{
		MessageBox(NULL, "createproc err", "err", MB_OK);
	}

	
	return 0;
}