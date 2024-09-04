#include "pch.h"

#include "export.h"

void ShowError(const char* pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}


// �޸�ָ�����̵Ľ��̻�����PEB�е�·������������Ϣ, ʵ�ֽ���αװ
BOOL DisguiseProcess(DWORD dwProcessId, wchar_t* lpwszPath, wchar_t* lpwszCmd)
{
	// �򿪽��̻�ȡ���
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		ShowError("OpenProcess");
		return FALSE;
	}
	ShowError("111");

	typedef_NtQueryInformationProcess NtQueryInformationProcess = NULL;
	PROCESS_BASIC_INFORMATION pbi = { 0 };
	PEB peb = { 0 };
	RTL_USER_PROCESS_PARAMETERS Param = { 0 };
	USHORT usCmdLen = 0;
	USHORT usPathLen = 0;
	// ��Ҫͨ�� LoadLibrary��GetProcessAddress �� ntdll.dll �л�ȡ��ַ
	NtQueryInformationProcess = (typedef_NtQueryInformationProcess)::GetProcAddress(
		::LoadLibrary("ntdll.dll"), "NtQueryInformationProcess");
	if (NULL == NtQueryInformationProcess)
	{
		ShowError("GetProcAddress");
		return FALSE;
	}
	ShowError("222");
	// ��ȡָ�����̵Ļ�����Ϣ
	NTSTATUS status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
	if (!NT_SUCCESS(status))
	{
		ShowError("NtQueryInformationProcess");
		return FALSE;
	}
	ShowError("333");

	/*
		ע���ڶ�д�������̵�ʱ��ע��Ҫʹ��ReadProcessMemory/WriteProcessMemory���в�����
		ÿ��ָ��ָ������ݶ���Ҫ��ȡ����Ϊָ��ֻ��ָ�򱾽��̵ĵ�ַ�ռ䣬����Ҫ��ȡ�������̿ռ䡣
		Ҫ��Ȼһֱ��ʾλ�÷��ʴ���!
	*/
	// ��ȡָ�����̽�����Ϣ�ṹ�е�PebBaseAddress
	::ReadProcessMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), NULL);
	ShowError("444");
	// ��ȡָ�����̻�����ṹ�е�ProcessParameters, ע��ָ��ָ�����ָ�����̿ռ���
	::ReadProcessMemory(hProcess, peb.ProcessParameters, &Param, sizeof(Param), NULL);
	ShowError("555");

	// �޸�ָ�����̻�����PEB����������Ϣ, ע��ָ��ָ�����ָ�����̿ռ���
	usCmdLen = 2 + 2 * ::wcslen(lpwszCmd);
	::WriteProcessMemory(hProcess, Param.CommandLine.Buffer, lpwszCmd, usCmdLen, NULL);
	ShowError("666");
	::WriteProcessMemory(hProcess, &Param.CommandLine.Length, &usCmdLen, sizeof(usCmdLen), NULL);
	ShowError("777");
	// �޸�ָ�����̻�����PEB��·����Ϣ, ע��ָ��ָ�����ָ�����̿ռ���
	usPathLen = 2 + 2 * ::wcslen(lpwszPath);
	::WriteProcessMemory(hProcess, Param.ImagePathName.Buffer, lpwszPath, usPathLen, NULL);
	ShowError("888");
	::WriteProcessMemory(hProcess, &Param.ImagePathName.Length, &usPathLen, sizeof(usPathLen), NULL);
	ShowError("999");

	return TRUE;
}