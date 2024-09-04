#pragma once
#include"stdafx.h"
#include "export.h"
#include "mmloadexe.h"

int MemRunExe(const char* szFileName) {

	// ��EXE�ļ�����ȡEXE�ļ���С
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		ShowError("CreateFile");
		return 1;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	// ���붯̬�ڴ沢��ȡDLL���ڴ���
	BYTE* pData = new BYTE[dwFileSize];
	if (NULL == pData)
	{
		ShowError("new");
		return 2;
	}
	DWORD dwRet = 0;
	ReadFile(hFile, pData, dwFileSize, &dwRet, NULL);
	CloseHandle(hFile);

	// �ж������ض�λ��
	if (FALSE == IsExistRelocationTable(pData))
	{
		::MessageBox(NULL,"[FALSE] IsExistRelocationTable\n", "err",MB_OK);
		
		return 0;
	}
	// ���ڴ�DLL���ص�������
	LPVOID lpBaseAddress = MmRunExe(pData, dwFileSize);
	if (NULL == lpBaseAddress)
	{
		ShowError("MmRunExe");
		return 3;
	}
	return 0;
}