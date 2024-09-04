#ifndef _RAW_INPUT_TEST_H_
#define _RAW_INPUT_TEST_H_


#include <stdio.h>
#include <Windows.h>

#define WM_EXIT_APP (WM_USER + 1)  // 定义自定义的退出消息


#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)	int initApp();
	

#ifdef __cplusplus
}
#endif

// 注册原始输入设备
BOOL Init(HWND hWnd);

// 获取原始输入数据
BOOL GetData(LPARAM lParam);

// 保存按键信息
void SaveKey(USHORT usVKey);

#endif