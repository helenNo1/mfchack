#pragma once

#include "pch.h"
#include "hook.h"



extern HMODULE g_hDllModule;
// �����ڴ�
#pragma data_seg("mydata")
HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")


// ���ӻص�����
LRESULT GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	::MessageBox(NULL, L"enter hook callback", L"info", MB_OK);
	return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}


// ����ȫ�ֹ���
BOOL SetGlobalHook()
{
	g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (NULL == g_hHook)
	{
		return FALSE;
	}
	return TRUE;
}


// ж�ع���
BOOL UnsetGlobalHook()
{
	if (g_hHook)
	{
		::UnhookWindowsHookEx(g_hHook);
	}
	return TRUE;
}