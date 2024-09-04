// CUserhackPage.cpp: 实现文件
//

#include "pch.h"
#include "mfchack.h"
#include "CUserhackPage.h"
#include "afxdialogex.h"
#include<Windows.h>
#include <tchar.h> // Include this for _T macro


#define WM_EXIT_APP (WM_USER + 1)  // 定义自定义的退出消息

// CUserhackPage 对话框

IMPLEMENT_DYNAMIC(CUserhackPage, CMFCPropertyPage)

CUserhackPage::CUserhackPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_DIALOG_USER)
{

}

CUserhackPage::~CUserhackPage()
{
}

void CUserhackPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}
void CUserhackPage::OnSize(UINT nType, int cx, int cy) {
	CPropertyPage::OnSize(nType, cx, cy);
}



BEGIN_MESSAGE_MAP(CUserhackPage, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserhackPage::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CUserhackPage::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CUserhackPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserhackPage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUserhackPage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUserhackPage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CUserhackPage::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CUserhackPage::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CUserhackPage::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CUserhackPage::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CUserhackPage::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CUserhackPage::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CUserhackPage::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CUserhackPage::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CUserhackPage::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CUserhackPage::OnBnClickedButton16)
END_MESSAGE_MAP()


// CUserhackPage 消息处理程序





void CUserhackPage::OnBnClickedButton1()
{
    
    MessageBox(_T("键盘记录测试"), _T("info"), MB_OK);

    typedef int(*initApp)();
    initApp iaFunc = NULL;

    HINSTANCE hDLL = LoadLibrary(L"dll_keyinputlog.dll");
    if (hDLL != NULL)
    {
        iaFunc = (initApp)GetProcAddress(hDLL, "initApp");
        if (iaFunc != NULL)
        {
            MessageBox( _T("load initApp func success"), _T("ok window"), MB_OK);
            //HelloWorld();
        }
        else
        {
            MessageBox(_T("load initApp func fail"), _T("err window"), MB_OK);
            return ;

        }
        iaFunc();
        FreeLibrary(hDLL);

    }
    else
    {
        MessageBox(_T("Could not load dll_keyinputlog.dll"), _T("err"), MB_OK);
        
    }
    


}



void CUserhackPage::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码

    MessageBox(_T("开启全局hook弹窗"), _T("info"), MB_OK);

	typedef BOOL(*typedef_SetGlobalHook)();
	
	HMODULE hDll = NULL;
	typedef_SetGlobalHook SetGlobalHook = NULL;
	
	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;

	
	hDll = ::LoadLibrary(L"dll_globalhook.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	SetGlobalHook = (typedef_SetGlobalHook)::GetProcAddress(hDll, "SetGlobalHook");
	if (NULL == SetGlobalHook)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	bRet = SetGlobalHook();
	if (bRet)
	{
		::MessageBoxA(NULL, "SetGlobalHook OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "SetGlobalHook error", "Error", MB_OK | MB_ICONERROR);
		
	}

	FreeLibrary(hDll);

	
}


void CUserhackPage::OnBnClickedButton3()
{
    
	MessageBox(_T("关闭全局hook弹窗"), _T("info"), MB_OK);

	typedef BOOL(*typedef_UnsetGlobalHook)();

	HMODULE hDll = NULL;
	typedef_UnsetGlobalHook UnsetGlobalHook = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_globalhook.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	UnsetGlobalHook = (typedef_UnsetGlobalHook)::GetProcAddress(hDll, "UnsetGlobalHook");
	if (NULL == UnsetGlobalHook)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	bRet = UnsetGlobalHook();
	if (bRet)
	{
		::MessageBoxA(NULL, "UnSetGlobalHook OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "UnSetGlobalHook error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	MessageBox(_T("apc注入到explorer.exe"), _T("info"), MB_OK);

	typedef BOOL(*typedef_ApcInjectDll)(char* pszProcessName, char* pszDllName);

	HMODULE hDll = NULL;
	typedef_ApcInjectDll ApcInjectDll = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_apcinject_user.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ApcInjectDll = (typedef_ApcInjectDll)::GetProcAddress(hDll, "ApcInjectDll");
	if (NULL == ApcInjectDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	bRet = ApcInjectDll("explorer.exe","dll_helloworld_loadmessagebox.dll");
	if (bRet)
	{
		::MessageBoxA(NULL, "ApcInjectDll OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "ApcInjectDll error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton5()
{
	

	MessageBox(_T("apc注入到securityhealth.exe"), _T("info"), MB_OK);

	typedef BOOL(*typedef_ApcInjectDll)(char* pszProcessName, char* pszDllName);

	HMODULE hDll = NULL;
	typedef_ApcInjectDll ApcInjectDll = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_apcinject_user.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ApcInjectDll = (typedef_ApcInjectDll)::GetProcAddress(hDll, "ApcInjectDll");
	if (NULL == ApcInjectDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	bRet = ApcInjectDll("SecurityHealthService.exe", "dll_helloworld_loadmessagebox.dll");
	if (bRet)
	{
		::MessageBoxA(NULL, "ApcInjectDll OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "ApcInjectDll error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton6()
{
	MessageBox(_T("exe远程线程注入dll"), _T("info"), MB_OK);

	typedef BOOL(*typedef_CreateRemoteThreadInjectDll)(const char* pszProcessName, const char* pszDllFileName);

	HMODULE hDll = NULL;
	typedef_CreateRemoteThreadInjectDll CreateRemoteThreadInjectDll = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_createremotethread.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CreateRemoteThreadInjectDll = (typedef_CreateRemoteThreadInjectDll)::GetProcAddress(hDll, "CreateRemoteThreadInjectDll");
	if (NULL == CreateRemoteThreadInjectDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	
	bRet = CreateRemoteThreadInjectDll("explorer.exe", "dll_helloworld_loadmessagebox.dll");
	if (bRet)
	{
		::MessageBoxA(NULL, "CreateRemoteThreadInjectDll OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "CreateRemoteThreadInjectDll error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("exe远程线程注入dll"), _T("info"), MB_OK);

	typedef BOOL(*typedef_CreateRemoteThreadInjectDll)(const char* pszProcessName, const char* pszDllFileName);

	HMODULE hDll = NULL;
	typedef_CreateRemoteThreadInjectDll CreateRemoteThreadInjectDll = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_createremotethread.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CreateRemoteThreadInjectDll = (typedef_CreateRemoteThreadInjectDll)::GetProcAddress(hDll, "CreateRemoteThreadInjectDll");
	if (NULL == CreateRemoteThreadInjectDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限

	bRet = CreateRemoteThreadInjectDll("SecurityHealthService.exe", "dll_helloworld_loadmessagebox.dll");
	if (bRet)
	{
		::MessageBoxA(NULL, "CreateRemoteThreadInjectDll OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "CreateRemoteThreadInjectDll error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码


	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("exe远程线程注入dll"), _T("info"), MB_OK);

	typedef BOOL(*typedef_ZwCreateThreadExInjectDll)(const char* pszProcessName, const char* pszDllFileName);

	HMODULE hDll = NULL;
	typedef_ZwCreateThreadExInjectDll ZwCreateThreadExInjectDll = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_createremotethreadinjectsession0.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ZwCreateThreadExInjectDll = (typedef_ZwCreateThreadExInjectDll)::GetProcAddress(hDll, "ZwCreateThreadExInjectDll");
	if (NULL == ZwCreateThreadExInjectDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限

	bRet = ZwCreateThreadExInjectDll("svchost.exe", "dll_helloworld_loadmessagebox.dll");
	if (bRet)
	{
		::MessageBoxA(NULL, "ZwCreateThreadExInjectDll OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "ZwCreateThreadExInjectDll error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton9()
{

	typedef BOOL(*typedef_ApiCreateProc)(char* pszExePath, UINT uiCmdShow);

	HMODULE hDll = NULL;
	typedef_ApiCreateProc ApiCreateProc = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_apicreateprocess.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ApiCreateProc = (typedef_ApiCreateProc)::GetProcAddress(hDll, "ApiCreateProc");
	if (NULL == ApiCreateProc)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = ApiCreateProc("C:\\Windows\\explorer.exe", SW_SHOWNORMAL);
	if (bRet ==0 )
	{
		::MessageBoxA(NULL, "ApiCreateProc OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "ApiCreateProc error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton10()
{
	typedef int(*typedef_CreateSession0Service)();

	HMODULE hDll = NULL;
	typedef_CreateSession0Service CreateSession0Service = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_serviceloader.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CreateSession0Service = (typedef_CreateSession0Service)::GetProcAddress(hDll, "CreateSession0Service");
	if (NULL == CreateSession0Service)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = CreateSession0Service();
	if (bRet == 0)
	{
		::MessageBoxA(NULL, "CreateSession0Service OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "CreateSession0Service error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton11()
{
	typedef int(*typedef_AutoRunReg)(char* lpszFileName, char* lpszValueName);

	HMODULE hDll = NULL;
	typedef_AutoRunReg AutoRunReg = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_autostart_reg.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	AutoRunReg = (typedef_AutoRunReg)::GetProcAddress(hDll, "AutoStartReg");
	if (NULL == AutoRunReg)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = AutoRunReg("C:\\Windows\\System32\\mspaint.exe", "test_autostart_reg");
	if (bRet == 0)
	{
		::MessageBoxA(NULL, "AutoRunReg OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "AutoRunReg error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	typedef int(*typedef_EnbalePrivileges)(HANDLE hProcess, const char* pszPrivilegesName);

	HMODULE hDll = NULL;
	typedef_EnbalePrivileges EnbalePrivileges = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_adjusttokenprivilege.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	EnbalePrivileges = (typedef_EnbalePrivileges)::GetProcAddress(hDll, "ExportMain");
	if (NULL == EnbalePrivileges)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = EnbalePrivileges(::GetCurrentProcess(), CW2A(SE_DEBUG_NAME));
	if (bRet == 0)
	{
		::MessageBoxA(NULL, "TokenPrivilege OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "TokenPrivilege error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO: 在此添加控件通知处理程序代码
	typedef int(*typedef_ExportMain)(const char* );

	HMODULE hDll = NULL;
	typedef_ExportMain ExportMain = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_bypassuac.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ExportMain = (typedef_ExportMain)::GetProcAddress(hDll, "ExportMain");
	if (NULL == ExportMain)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = ExportMain("C:\\Windows\\System32\\cmd.exe");
	if (bRet == 0)
	{
		::MessageBoxA(NULL, "run dll func OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "run dll func  error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码

	typedef int(*typedef_ExportMain)();

	HMODULE hDll = NULL;
	typedef_ExportMain ExportMain = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_rundll.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ExportMain = (typedef_ExportMain)::GetProcAddress(hDll, "ExportMain");
	if (NULL == ExportMain)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// 提升当前进程令牌权限
	bRet = ExportMain();
	if (bRet == 0)
	{
		::MessageBoxA(NULL, "run dll func OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "run dll func  error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}

// 将 const char* 转换为 wchar_t*
wchar_t* ConvertCharToWChar(const char* str) {
	int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
	return wstr;
}

// 将 wchar_t* 转换为 const char*
char* ConvertWCharToChar(const wchar_t* wstr) {
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	return str;
}


void CUserhackPage::OnBnClickedButton15()
{
	typedef BOOL(*typedef_ExportMain)(DWORD dwProcessId, wchar_t* lpwszPath, wchar_t* lpwszCmd);

	HMODULE hDll = NULL;
	typedef_ExportMain ExportMain = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_processweizhuang.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	ExportMain = (typedef_ExportMain)::GetProcAddress(hDll, "DisguiseProcess");
	if (NULL == ExportMain)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	DWORD dwProcessId = ::GetCurrentProcessId();
	
	//bRet = ExportMain(dwProcessId, const_cast<char*>("C:\\Windows\\explorer.exe"), "explorer.exe");
	bRet = ExportMain(dwProcessId, L"C:\\Windows\\explorer.exe", L"explorer.exe");
	if (bRet == TRUE)
	{
		::MessageBoxA(NULL, "run dll func OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "123", "Error", MB_OK | MB_ICONERROR);
		::MessageBoxA(NULL, "run dll func  error", "Error", MB_OK | MB_ICONERROR);

	}
	FreeLibrary(hDll);
}


void CUserhackPage::OnBnClickedButton16()
{
	HHOOK hHook;
	typedef HHOOK(*typedef_sethook)();

	HMODULE hDll = NULL;
	typedef_sethook sethook_func = NULL;

	BOOL bRet = FALSE;
	char szErrorMessage[256];
	DWORD dwError = NULL;


	hDll = ::LoadLibrary(L"dll_hideproc.dll");
	if (NULL == hDll)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "load library Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}

	sethook_func = (typedef_sethook)::GetProcAddress(hDll, "SetHook");
	if (NULL == sethook_func)
	{
		::MessageBoxA(NULL, "11111", "Error", MB_OK | MB_ICONERROR);
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}
	
	hHook = sethook_func();
	if (hHook != NULL)
	{
		::MessageBoxA(NULL, "run dll func OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "22222", "Error", MB_OK | MB_ICONERROR);
		::MessageBoxA(NULL, "123", "Error", MB_OK | MB_ICONERROR);
		::MessageBoxA(NULL, "run dll func  error", "Error", MB_OK | MB_ICONERROR);

	}

	::MessageBoxA(NULL, "todo unset hook", "debug", MB_OK);


	typedef BOOL(*typedef_unsethook)(HHOOK hHook);
	typedef_unsethook unsethook_func = NULL;
	unsethook_func = (typedef_unsethook)::GetProcAddress(hDll, "UnsetHook");
	if (NULL == unsethook_func)
	{
		dwError = ::GetLastError();
		sprintf_s(szErrorMessage, "get proc addrss Error [%lu]", dwError);
		::MessageBoxA(NULL, szErrorMessage, "Error", MB_OK | MB_ICONERROR);
		return;
	}
	bRet = unsethook_func(hHook);
	if (bRet == TRUE)
	{
		::MessageBoxA(NULL, "run dll func OK.", "succ", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "123", "Error", MB_OK | MB_ICONERROR);
		::MessageBoxA(NULL, "run dll func  error", "Error", MB_OK | MB_ICONERROR);

	}

	FreeLibrary(hDll);
}
