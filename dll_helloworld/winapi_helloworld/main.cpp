#include <windows.h>

// ���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        MessageBox(NULL, "close?", "warning", MB_OK);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// �������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ���崰����
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "HelloWorldClass";

    // ע�ᴰ����
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // ��������
    HWND hwnd = CreateWindow(
        "HelloWorldClass",    // ��������
        "Hello, World!",      // ���ڱ���
        WS_OVERLAPPEDWINDOW,  // ������ʽ
        CW_USEDEFAULT,        // ����λ��X
        CW_USEDEFAULT,        // ����λ��Y
        400,                  // ���ڿ��
        300,                  // ���ڸ߶�
        NULL,                 // �����ھ��
        NULL,                 // �˵����
        hInstance,            // ʵ�����
        NULL                  // ��������
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // ��ʾ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
