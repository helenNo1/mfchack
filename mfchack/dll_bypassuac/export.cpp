#include "pch.h"

#include "export.h"
#include <Windows.h>
#include <cstdlib>


void ShowError(const char* pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}


// �޸�ע���
BOOL SetReg(const char* lpszExePath)
{
	HKEY hKey = NULL;
	// ������
	::RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\Shell\\Open\\Command", 0, NULL, 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (NULL == hKey)
	{
		ShowError("RegCreateKeyEx");
		return FALSE;
	}
	// ���ü�ֵ
	::RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)lpszExePath, (1 + ::lstrlen(lpszExePath)));
	// �ر�ע���
	::RegCloseKey(hKey);
	return TRUE;
}

int ExportMain(const char* lpszExePath) {

	BOOL bRet = FALSE;
	PVOID OldValue = NULL;
	// �ر��ļ��ض�λ
	::Wow64DisableWow64FsRedirection(&OldValue);

	// �޸�ע���
	bRet = SetReg(lpszExePath);
	if (bRet)
	{
		// ���� CompMgmtLauncher.exe
		system("CompMgmtLauncher.exe");
		MessageBox(NULL,"Run OK!\n", "info", MB_OK);
	}
	else
	{
		MessageBox(NULL, "Run err!\n", "err", MB_OK);
		
	}
	
	// �ָ��ļ��ض�λ
	::Wow64RevertWow64FsRedirection(OldValue);
	return 0;

}