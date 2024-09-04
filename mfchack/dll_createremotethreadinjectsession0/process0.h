#pragma once
#include "pch.h"


#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcessIdByProcessName(const char* pszProcessName);