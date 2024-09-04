#ifndef _AUTORUN_REG_H_
#define _AUTORUN_REG_H_

#include "pch.h"
#include <Windows.h>


BOOL Reg_CurrentUser(const char* lpszFileName, const  char* lpszValueName);
BOOL Reg_LocalMachine(const char* lpszFileName, const  char* lpszValueName);


#endif