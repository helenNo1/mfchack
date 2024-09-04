#pragma once
#include"stdafx.h"





#ifdef DEBUG
extern "C" {
#endif // DEBUG

	__declspec(dllexport) int MemRunExe(const char* szFileName);

#ifdef DEBUG
}
#endif // DEBUG
