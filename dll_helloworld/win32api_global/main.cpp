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
    // ����һ�����ⴰ�ڣ����ڽ���ȫ�ֵ� WM_INPUT ��Ϣ
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DummyWndProc; // ���ⴰ�ڹ��̺���
    wc.hInstance = hInstance;
    wc.lpszClassName = "DummyWindowClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindow(
        "DummyWindowClass", // ��������
        "Dummy Window",     // ���ڱ��⣨��ʵ����ʾ��
        0,                  // ������ʽ���ޱ߿��ޱ��⣩
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,               // �޸�����
        NULL,               // �޲˵�
        hInstance,
        NULL
    );

    if (!hwnd)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    Init(hwnd);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
