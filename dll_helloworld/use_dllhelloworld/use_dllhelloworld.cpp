#include <Windows.h>
#include <iostream>

typedef void(*HelloWorldFunc)();

int main()
{
    HINSTANCE hDLL = LoadLibrary(L"dll_helloworld.dll");
    if (hDLL != NULL)
    {
        HelloWorldFunc HelloWorld = (HelloWorldFunc)GetProcAddress(hDLL, "HelloWorld");
        if (HelloWorld != NULL)
        {
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
        std::cerr << "Could not load the DLL." << std::endl;
    }

    return 0;
}
