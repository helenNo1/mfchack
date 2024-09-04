#include "pch.h"

#include "session0.h"


#include "service_oper.h"

void GetAbsolutePath(const char* relativePath, char* absolutePath, DWORD absolutePathSize)
{
	DWORD result = GetFullPathName(relativePath, absolutePathSize, absolutePath, NULL);
	if (result == 0 || result > absolutePathSize)
	{
		::MessageBox(NULL , "Failed to get full path name." , "err",MB_OK );
	}
}

int CreateSession0Service() {

	BOOL bRet = FALSE;
	char relativePath[] = "exe_session0service.exe";

	char szExePath[MAX_PATH];

	GetAbsolutePath(relativePath, szExePath, MAX_PATH);


	// 加载服务
	bRet = SystemServiceOperate(szExePath, 0);
	if (bRet)
	{
		MessageBox(NULL, "INSTALL OK.\n", "info", MB_OK);
	}
	else
	{
		MessageBox(NULL, "INSTALL ERR.\n", "err", MB_OK);
	}
	// 启动服务
	bRet = SystemServiceOperate(szExePath, 1);
	if (bRet)
	{
		MessageBox(NULL, "START OK.\n", "info", MB_OK);
	}
	else
	{
		MessageBox(NULL, "START ERR.\n", "err", MB_OK);
	}


	

	// 停止服务
	bRet = SystemServiceOperate(szExePath, 2);
	if (bRet)
	{
		MessageBox(NULL, "stop OK.\n", "info", MB_OK);
	}
	else
	{
		MessageBox(NULL, "stop err.\n", "err", MB_OK);
	}
	// 卸载服务
	bRet = SystemServiceOperate(szExePath, 3);
	if (bRet)
	{
		MessageBox(NULL, "uninstall OK.\n", "info", MB_OK);
	}
	else
	{
		MessageBox(NULL, "uninstall err.\n", "err", MB_OK);
	}

	return 0;
}