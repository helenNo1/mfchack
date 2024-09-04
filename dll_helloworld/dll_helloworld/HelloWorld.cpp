#include"pch.h"
#include "HelloWorld.h"
#include <iostream>

// Exported function that prints "Hello, World!"
extern "C" __declspec(dllexport) void HelloWorld()
{
    //std::cout << "Hello, World!" << std::endl;
    MessageBox(NULL, L"helloworld", L"tishi", MB_OK);
}
