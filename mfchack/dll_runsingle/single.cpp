#include "pch.h"
#include "single.h"
#include <stdlib.h>


void checkRun() {

	HANDLE hMutex = NULL;
	hMutex = ::CreateMutex(NULL, FALSE, L"only run one exe");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			::MessageBox(NULL, L"one exe already run", L"ok", MB_OK);
			exit(0);
		}
	}

}