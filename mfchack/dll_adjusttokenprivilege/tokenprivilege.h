#pragma once
#include "pch.h"


#include <Windows.h>


BOOL EnbalePrivileges(HANDLE hProcess, char* pszPrivilegesName);


extern "C" {

	__declspec(dllexport) int ExportMain(HANDLE hProcess, char* pszPrivilegesName);
}


