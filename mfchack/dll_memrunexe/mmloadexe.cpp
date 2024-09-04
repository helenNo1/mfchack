#include "stdafx.h"
#include "mmloadexe.h"


void ShowError(const char* lpszText)
{
    char szErr[MAX_PATH] = { 0 };
    wsprintf(szErr, "%s Error!\nError Code Is:%d\n", lpszText, GetLastError());
#ifdef _DEBUG
    MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}

BOOL IsExistRelocationTable(LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

    if ((PVOID)pLoc == (PVOID)pDosHeader)
    {
        return FALSE;
    }

    return TRUE;
}

LPVOID MmRunExe(LPVOID lpData, DWORD dwSize)
{
    LPVOID lpBaseAddress = NULL;
    DWORD dwSizeOfImage = GetSizeOfImage(lpData);

    lpBaseAddress = ::VirtualAlloc(NULL, dwSizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (NULL == lpBaseAddress)
    {
        ShowError("VirtualAlloc");
        return NULL;
    }
    ::RtlZeroMemory(lpBaseAddress, dwSizeOfImage);

    if (FALSE == MmMapFile(lpData, lpBaseAddress))
    {
        ShowError("MmMapFile");
        return NULL;
    }

    if (FALSE == DoRelocationTable(lpBaseAddress))
    {
        ShowError("DoRelocationTable");
        return NULL;
    }

    if (FALSE == DoImportTable(lpBaseAddress))
    {
        ShowError("DoImportTable");
        return NULL;
    }

    DWORD dwOldProtect = 0;
    if (FALSE == ::VirtualProtect(lpBaseAddress, dwSizeOfImage, PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        ShowError("VirtualProtect");
        return NULL;
    }

    if (FALSE == SetImageBase(lpBaseAddress))
    {
        ShowError("SetImageBase");
        return NULL;
    }

    if (FALSE == CallExeEntry(lpBaseAddress))
    {
        ShowError("CallExeEntry");
        return NULL;
    }

    return lpBaseAddress;
}

DWORD GetSizeOfImage(LPVOID lpData)
{
    DWORD dwSizeOfImage = 0;
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpData;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    dwSizeOfImage = pNtHeaders->OptionalHeader.SizeOfImage;

    return dwSizeOfImage;
}

BOOL MmMapFile(LPVOID lpData, LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpData;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    DWORD dwSizeOfHeaders = pNtHeaders->OptionalHeader.SizeOfHeaders;
    WORD wNumberOfSections = pNtHeaders->FileHeader.NumberOfSections;
    PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders + sizeof(IMAGE_NT_HEADERS));

    ::RtlCopyMemory(lpBaseAddress, lpData, dwSizeOfHeaders);

    WORD i = 0;
    LPVOID lpSrcMem = NULL;
    LPVOID lpDestMem = NULL;
    DWORD dwSizeOfRawData = 0;
    for (i = 0; i < wNumberOfSections; i++)
    {
        if ((0 == pSectionHeader->VirtualAddress) || (0 == pSectionHeader->SizeOfRawData))
        {
            pSectionHeader++;
            continue;
        }

        lpSrcMem = (LPVOID)((DWORD)lpData + pSectionHeader->PointerToRawData);
        lpDestMem = (LPVOID)((DWORD)lpBaseAddress + pSectionHeader->VirtualAddress);
        dwSizeOfRawData = pSectionHeader->SizeOfRawData;
        ::RtlCopyMemory(lpDestMem, lpSrcMem, dwSizeOfRawData);

        pSectionHeader++;
    }

    return TRUE;
}

DWORD Align(DWORD dwSize, DWORD dwAlignment)
{
    DWORD dwRet = 0;
    DWORD i = 0, j = 0;
    i = dwSize / dwAlignment;
    j = dwSize % dwAlignment;
    if (0 != j)
    {
        i++;
    }

    dwRet = i * dwAlignment;

    return dwRet;
}

BOOL DoRelocationTable(LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

    if ((PVOID)pLoc == (PVOID)pDosHeader)
    {
        return TRUE;
    }

    while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0)
    {
        WORD* pLocData = (WORD*)((PBYTE)pLoc + sizeof(IMAGE_BASE_RELOCATION));
        int nNumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);

        for (int i = 0; i < nNumberOfReloc; i++)
        {
            if ((DWORD)(pLocData[i] & 0x0000F000) == 0x00003000)
            {
                DWORD* pAddress = (DWORD*)((PBYTE)pDosHeader + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
                DWORD dwDelta = (DWORD)pDosHeader - pNtHeaders->OptionalHeader.ImageBase;
                *pAddress += dwDelta;
            }
        }

        pLoc = (PIMAGE_BASE_RELOCATION)((PBYTE)pLoc + pLoc->SizeOfBlock);
    }

    return TRUE;
}

BOOL DoImportTable(LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pDosHeader +
        pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    char* lpDllName = NULL;
    HMODULE hDll = NULL;
    PIMAGE_THUNK_DATA lpImportNameArray = NULL;
    PIMAGE_IMPORT_BY_NAME lpImportByName = NULL;
    PIMAGE_THUNK_DATA lpImportFuncAddrArray = NULL;
    FARPROC lpFuncAddress = NULL;
    DWORD i = 0;

    while (TRUE)
    {
        if (0 == pImportTable->OriginalFirstThunk)
        {
            break;
        }

        lpDllName = (char*)((DWORD)pDosHeader + pImportTable->Name);
        hDll = ::GetModuleHandle(lpDllName);
        if (NULL == hDll)
        {
            hDll = ::LoadLibrary(lpDllName);
        }
        if (NULL == hDll)
        {
            return FALSE;
        }

        lpImportNameArray = (PIMAGE_THUNK_DATA)((DWORD)pDosHeader + pImportTable->OriginalFirstThunk);
        lpImportFuncAddrArray = (PIMAGE_THUNK_DATA)((DWORD)pDosHeader + pImportTable->FirstThunk);

        while (TRUE)
        {
            if (0 == lpImportNameArray->u1.AddressOfData)
            {
                break;
            }

            if (IMAGE_ORDINAL_FLAG == (lpImportNameArray->u1.Ordinal & IMAGE_ORDINAL_FLAG))
            {
                lpFuncAddress = ::GetProcAddress(hDll, (LPCSTR)(lpImportNameArray->u1.Ordinal & 0xFFFF));
            }
            else
            {
                lpImportByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pDosHeader + lpImportNameArray->u1.AddressOfData);
                lpFuncAddress = ::GetProcAddress(hDll, (LPCSTR)lpImportByName->Name);
            }

            if (NULL == lpFuncAddress)
            {
                return FALSE;
            }

            lpImportFuncAddrArray->u1.Function = (DWORD)lpFuncAddress;

            lpImportNameArray++;
            lpImportFuncAddrArray++;
        }

        pImportTable++;
    }

    return TRUE;
}

BOOL SetImageBase(LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    pNtHeaders->OptionalHeader.ImageBase = (DWORD)pDosHeader;

    return TRUE;
}




BOOL CallExeEntry(LPVOID lpBaseAddress)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
    LPVOID lpExeEntry = (LPVOID)((ULONG32)pDosHeader + pNtHeaders->OptionalHeader.AddressOfEntryPoint);
    // 跳转到入口点处执行
    __asm
    {
        mov eax, lpExeEntry
        jmp eax
    }

    return TRUE;
}