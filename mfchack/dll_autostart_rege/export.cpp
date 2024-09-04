#include "pch.h"
#include "export.h"


int AutoStartReg(const char* lpszFileName, const char* lpszValueName) {

	// 第一种方式修改注册表:HKEY_CURRENT_USER
	if (FALSE == Reg_CurrentUser(lpszFileName, lpszValueName))
	{
		MessageBox(NULL, "Reg_CurrentUser Error!\n", "info",MB_OK);
	}
	// 第二种方式修改注册表:HKEY_LOCAL_MACHINE
	if (FALSE == Reg_LocalMachine(lpszFileName, lpszValueName))
	{
		MessageBox(NULL,"Reg_LocalMachine Error!\n","info", MB_OK);
	}

	return 0;
}