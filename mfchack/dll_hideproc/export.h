#include "pch.h"

#include <Windows.h>
#include <Winternl.h>


typedef NTSTATUS(*typedef_ZwQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);


NTSTATUS New_ZwQuerySystemInformation(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);
void HookApi();

void UnhookApi();

extern "C"
{
	__declspec(dllexport) HHOOK SetHook();


	// Ð¶ÔØÈ«¾Ö¹³×Ó
	__declspec(dllexport) BOOL UnsetHook(HHOOK hHook);
	

}

