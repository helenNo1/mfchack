#pragma once
#include"stdafx.h"
#include "export.h"
#include "mmloadexe.h"

int MemRunExe(const char* szFileName) {

	// 打开EXE文件并获取EXE文件大小
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		ShowError("CreateFile");
		return 1;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	// 申请动态内存并读取DLL到内存中
	BYTE* pData = new BYTE[dwFileSize];
	if (NULL == pData)
	{
		ShowError("new");
		return 2;
	}
	DWORD dwRet = 0;
	ReadFile(hFile, pData, dwFileSize, &dwRet, NULL);
	CloseHandle(hFile);

	// 判断有无重定位表
	if (FALSE == IsExistRelocationTable(pData))
	{
		::MessageBox(NULL,"[FALSE] IsExistRelocationTable\n", "err",MB_OK);
		
		return 0;
	}
	// 将内存DLL加载到程序中
	LPVOID lpBaseAddress = MmRunExe(pData, dwFileSize);
	if (NULL == lpBaseAddress)
	{
		ShowError("MmRunExe");
		return 3;
	}
	return 0;
}