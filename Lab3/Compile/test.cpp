//
// Created by Алексей on 26.09.2020.
//

#include <iostream>
#include <thread>
#include <windows.h>

//char* buf = new char[sizeof(STRING) + 1];

int main()
{
    char text[] = "Test";
    long pid = GetCurrentProcessId();
    printf("%d \n", pid);
    int i = 0;
    while (i < 50) {
        printf("%s ", text);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

