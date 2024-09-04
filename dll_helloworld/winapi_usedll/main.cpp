#include <windows.h>

typedef void(*HelloWorldFunc)();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //MessageBox(NULL, L"Hello, World!", L"Message", MB_OK | MB_ICONINFORMATION);

    HINSTANCE hDLL = LoadLibrary(L"dll_helloworld.dll");
    if (hDLL != NULL)
    {
        HelloWorldFunc HelloWorld = (HelloWorldFunc)GetProcAddress(hDLL, "HelloWorld");
        if (HelloWorld != NULL)
        {
            MessageBox(NULL, L"load dll func success", L"ok", MB_OK);
            HelloWorld();
        }
        else
        {
            MessageBox(NULL, L"Could not locate the function.", L"err window", MB_OK);

        }
        FreeLibrary(hDLL);
    }
    else
    {
       MessageBox(NULL, L"Could not load the DLL.",L"err", MB_OK);
    }


    return 0;
}
