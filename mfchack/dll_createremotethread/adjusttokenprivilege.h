#pragma once
#include "pch.h"

#include <Windows.h>


BOOL EnbalePrivileges(HANDLE hProcess, const char* pszPrivilegesName);