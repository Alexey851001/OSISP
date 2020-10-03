#include "library.h"

#include <windows.h>
#include <stdio.h>

#include <new>
#include <vector>

void FindString(const char *str, const char *replaceStr) {
    size_t targetLen = strlen(str);
    size_t valueLen = strlen(replaceStr);

    SYSTEM_INFO si;
    GetSystemInfo(&si);

    MEMORY_BASIC_INFORMATION info;
    auto baseAddress = (LPSTR) si.lpMinimumApplicationAddress;

    while (baseAddress < si.lpMaximumApplicationAddress) {
        if (VirtualQuery(baseAddress, &info, sizeof(info)) == sizeof(info)) {
            if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE) {
                baseAddress = (LPSTR) info.BaseAddress;
                char *memory = (char *) malloc(info.RegionSize);
                SIZE_T bytesRead;

                if (ReadProcessMemory(GetCurrentProcess(), baseAddress, memory, info.RegionSize, &bytesRead)) {
                    for (SIZE_T i = 0; i < bytesRead - targetLen; i++) {
                        if (strcmp(baseAddress + i, str) == 0) {
                            memcpy(baseAddress + i, replaceStr, valueLen + 1);
                        }
                    }
                }
                free(memory);
            }
        }
        baseAddress += info.RegionSize;
    }
}

#ifdef INJECT
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
)
{

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
            FindString("Test", "Some232fgdgfdghfd3");
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
#endif