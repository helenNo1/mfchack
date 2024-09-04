#include <windows.h>
#include "RawInputTest.h"

LRESULT CALLBACK DummyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_INPUT:
        GetData(lParam);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 创建一个虚拟窗口，用于接收全局的 WM_INPUT 消息
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DummyWndProc; // 虚拟窗口过程函数
    wc.hInstance = hInstance;
    wc.lpszClassName = "DummyWindowClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
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

    return msg.wParam;
}
