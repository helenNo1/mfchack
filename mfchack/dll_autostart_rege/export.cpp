#include "pch.h"
#include "export.h"


int AutoStartReg(const char* lpszFileName, const char* lpszValueName) {

	// ��һ�ַ�ʽ�޸�ע���:HKEY_CURRENT_USER
	if (FALSE == Reg_CurrentUser(lpszFileName, lpszValueName))
	{
		MessageBox(NULL, "Reg_CurrentUser Error!\n", "info",MB_OK);
	}
	// �ڶ��ַ�ʽ�޸�ע���:HKEY_LOCAL_MACHINE
	if (FALSE == Reg_LocalMachine(lpszFileName, lpszValueName))
	{
		MessageBox(NULL,"Reg_LocalMachine Error!\n","info", MB_OK);
	}

	return 0;
}