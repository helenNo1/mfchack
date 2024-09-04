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


// 修改指定进程的进程环境块PEB中的路径和命令行信息, 实现进程伪装
extern "C" {
	__declspec(dllexport)  BOOL DisguiseProcess(DWORD dwProcessId, wchar_t* lpwszPath, wchar_t* lpwszCmd);
}