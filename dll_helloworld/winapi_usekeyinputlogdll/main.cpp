#include <windows.h>

/*
typedef void(*HelloWorldFunc)();
typedef BOOL(*Init)(HWND hWnd);
typedef BOOL(*GetData)(LPARAM lParam);

GetData getdataFunc;
Init initFunc ;
*/
typedef int(*initApp)();
initApp iaFunc = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    //MessageBox(NULL, L"Hello, World!", L"Message", MB_OK | MB_ICONINFORMATION);

    
    HINSTANCE hDLL = LoadLibrary("dll_keyinputlog.dll");
    if (hDLL != NULL)
    {
        iaFunc = (initApp)GetProcAddress(hDLL, "initApp");
        if (iaFunc != NULL)
        {
            MessageBox(NULL, "load initApp func success", "ok window", MB_OK);
            //HelloWorld();
        }
        else
        {
            MessageBox(NULL, "load initApp func fail", "err window", MB_OK);
            return 1;

        }
        iaFunc();
        FreeLibrary(hDLL);
        
    }
    else
    {
        MessageBox(NULL, "Could not load dll_keyinputlog.dll", "err", MB_OK);
        return 1;
    }
    
    return 0;

   
}
