#pragma once

#include "pch.h"


#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")


// 0 ���ط���    1 ��������    2 ֹͣ����    3 ɾ������
BOOL SystemServiceOperate(const char* lpszDriverPath, int iOperateType);
