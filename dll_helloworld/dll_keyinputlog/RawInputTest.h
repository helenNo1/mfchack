#ifndef _RAW_INPUT_TEST_H_
#define _RAW_INPUT_TEST_H_


#include <stdio.h>
#include <Windows.h>

#define WM_EXIT_APP (WM_USER + 1)  // �����Զ�����˳���Ϣ


#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)	int initApp();
	

#ifdef __cplusplus
}
#endif

// ע��ԭʼ�����豸
BOOL Init(HWND hWnd);

// ��ȡԭʼ��������
BOOL GetData(LPARAM lParam);

// ���水����Ϣ
void SaveKey(USHORT usVKey);

#endif