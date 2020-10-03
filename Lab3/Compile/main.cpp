#include <iostream>
#include <stdio.h>
#include <new>
#include <thread>
#include <windows.h>


#define PATH_TO_DLL "library.dll"
#define FUNCTION_NAME "FindString"
#define PATH_TO_DLL_FOR_INJECTION "injectDll.dll"
#define PATH_TO_KERNEL_DLL "Kernel32.dll"
#define NAME_LOAD_LIBRARY_FUNCTION "LoadLibraryA"

const char* STRING = "Test";
const char* REPLACE_STRING = "SomeSifdffhdj";

const long PROC_PID = 2244;

typedef HMODULE(WINAPI* LPLoadLibrary)(LPCSTR);

typedef void ReplaceData(const char* str, const char* replaceStr);

extern "C" _declspec(dllimport) void FindString(const char* str, const char* replaceStr);

char* buf = new char[strlen(STRING) + 1];

void useStaticConnection() {

    FindString( STRING, REPLACE_STRING);
}

void useDynamicConnection() {
    HMODULE moduleDll = LoadLibraryA(PATH_TO_DLL);
    if (moduleDll != NULL) {
        ReplaceData* FindStringFunc = (ReplaceData*)GetProcAddress(moduleDll, FUNCTION_NAME);
        FindStringFunc(STRING, REPLACE_STRING);
        FreeLibrary(moduleDll);
    }

}

void injectedDll(DWORD injectPid) {
    HMODULE hdll = LoadLibraryA(PATH_TO_KERNEL_DLL);

    LPLoadLibrary LoadLibraryA = (LPLoadLibrary)GetProcAddress(hdll, NAME_LOAD_LIBRARY_FUNCTION);


    HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE |
                               PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS,
                               FALSE, injectPid);

    LPVOID path = VirtualAllocEx(hProc, NULL, strlen(PATH_TO_DLL_FOR_INJECTION) + 1,
                                 MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);


    WriteProcessMemory(hProc, path, PATH_TO_DLL_FOR_INJECTION,
                                strlen(PATH_TO_DLL_FOR_INJECTION) + 1, NULL);

    DWORD threadID;

    HANDLE HThread = CreateRemoteThread(hProc, NULL, NULL,
                                        (LPTHREAD_START_ROUTINE)LoadLibraryA, (LPVOID)path, NULL, &threadID);

    Sleep(1000);



    if (HThread == NULL)
    {
        printf("error\n");
    }
    else {

        WaitForSingleObject(HThread, INFINITE);
    }

    FreeLibrary(hdll);
    CloseHandle(hProc);

}

void switchFunc(char mode)
{
    switch (mode)
    {
        case 0: {
            useStaticConnection();
            break;
        }
        case 1: {
            useDynamicConnection();
            break;
        }
        case 2: {
            DWORD injectPid = PROC_PID;
            injectedDll(injectPid);
            break;
        }
        default: {
            useStaticConnection();
            break;
        }
    }
}

int main()
{
    strcpy_s(buf, strlen(STRING) + 1, STRING);
    int mode;
    printf("Enter case of connection: 0 - static; 1 - dynamic; 2 - inject dll");
    scanf("%d", &mode);
    printf(buf);
    printf(" ");
    std::thread thread(switchFunc, mode);
    thread.join();
    printf(buf);
    return 0;
}


