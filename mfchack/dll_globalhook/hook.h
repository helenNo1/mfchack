#pragma once

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


	__declspec(dllexport) BOOL SetGlobalHook();

	__declspec(dllexport) BOOL UnsetGlobalHook();

#ifdef __cplusplus
}
#endif // __cplusplus


