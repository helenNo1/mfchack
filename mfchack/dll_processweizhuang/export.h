#include "pch.h"


#include <Windows.h>
#include <winternl.h>


typedef NTSTATUS(NTAPI* typedef_NtQueryInformationProcess)(
	IN HANDLE ProcessHandle,
	IN PROCESSINFOCLASS ProcessInformationClass,
	OUT PVOID ProcessInformation,
	IN ULONG ProcessInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);


// �޸�ָ�����̵Ľ��̻�����PEB�е�·������������Ϣ, ʵ�ֽ���αװ
extern "C" {
	__declspec(dllexport)  BOOL DisguiseProcess(DWORD dwProcessId, wchar_t* lpwszPath, wchar_t* lpwszCmd);
}