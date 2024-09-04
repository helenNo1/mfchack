#include "pch.h"


#include "process0.h"




static void ShowError(const char* pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText);
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

// 根据进程名称获取PID
DWORD GetProcessIdByProcessName(const char* pszProcessName)
{
	DWORD dwProcessId = 0;
	PROCESSENTRY32 pe32 = { 0 };
	HANDLE hSnapshot = NULL;
	BOOL bRet = FALSE;
	::RtlZeroMemory(&pe32, sizeof(pe32));
	pe32.dwSize = sizeof(pe32);

	// 获取进程快照
	hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (NULL == hSnapshot)
	{
		ShowError("CreateToolhelp32Snapshot");
		return dwProcessId;
	}

	// 获取第一条进程快照信息
	bRet = ::Process32First(hSnapshot, &pe32);
	while (bRet)
	{
		// 获取快照信息
		if (0 == ::lstrcmpi(pe32.szExeFile, pszProcessName))
		{
			dwProcessId = pe32.th32ProcessID;
			break;
		}

		// 遍历下一个进程快照信息
		bRet = ::Process32Next(hSnapshot, &pe32);
	}

	return dwProcessId;
}
