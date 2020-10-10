#include <iostream>
#include <windows.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <thread>

#include "queueElem/QueueElem.h"
#include "ThreadpoolQueueProcessor.h"

#define FILE_PATH_TO_READ  "D:\\5sem\\OSISP\\OSISP\\Lab4\\test.txt"
#define FILE_PATH_TO_WRITE  "D:\\5sem\\OSISP\\OSISP\\Lab4\\out.txt"
#define MAX_STRING_SIZE 1024

using namespace std;

CRITICAL_SECTION pushCriticalSection;

void pushInQueue(QueueElem queueElement, queue <QueueElem> *myQueue){

    EnterCriticalSection(&pushCriticalSection);

    myQueue->push(queueElement);

    LeaveCriticalSection(&pushCriticalSection);
}

int main() {
    queue <QueueElem> myQueue;
    vector<string> buffer;
    InitializeCriticalSection(&pushCriticalSection);

    cout << "Enter count of the threads" << endl;
    int countOfThreadsFromConsole;
    cin >> countOfThreadsFromConsole;

    unsigned int maxThreads = thread::hardware_concurrency();
    if (countOfThreadsFromConsole > maxThreads){
        std::cout << "Max number of threads is " << maxThreads << std::endl;
        return 1;
    }
    ifstream fin(FILE_PATH_TO_READ);
    long stringCount = 0;
    char str[MAX_STRING_SIZE];

    int j = 0;
    while (!fin.eof()){
        fin.getline(str,MAX_STRING_SIZE);
        stringCount++;
        buffer.resize(stringCount);
        buffer[j] = str;
        if (buffer[j][buffer[j].size() - 1] != '\n'){
            buffer[j] += '\n';
        }
        j++;
    }

    fin.close();
    int countOfThreads;
    long stringCountForThread;
    int modCount;
    if (stringCount > countOfThreadsFromConsole) {
        countOfThreads = countOfThreadsFromConsole;
        stringCountForThread = stringCount / countOfThreadsFromConsole;
        modCount = stringCount % countOfThreadsFromConsole;
    } else {
        stringCountForThread = 1;
        modCount = 0;
        countOfThreads = stringCount;
    }
    for (int i = 0; i < countOfThreads; i++) {
        QueueElem queueElem;
        if (i != countOfThreads - 1) {
            queueElem = queueElem.Create(stringCountForThread * i + 1, stringCountForThread * (i + 1));
        } else {
            queueElem = queueElem.Create(stringCountForThread * i + 1, stringCountForThread * (i + 1) + modCount);
        }
        pushInQueue(queueElem, &myQueue);
    }

    ThreadpoolQueueProcessor queueHandler(&myQueue,&buffer);

    queueHandler.Process(&myQueue,countOfThreads);
    queueHandler.Wait();

    int countSort =  stringCount / stringCountForThread - 1;
    for (int i = 0; i < countSort; i++){
        if (i == (countSort - 1)) {
            inplace_merge(buffer.begin(), buffer.begin() + stringCountForThread * (i + 1),
                               buffer.end());
        } else {
            inplace_merge(buffer.begin(), buffer.begin() + stringCountForThread * (i + 1),
                               buffer.begin() + stringCountForThread * (i + 2));
        }
    }

    ofstream fout(FILE_PATH_TO_WRITE);
    for(int i = 0; i < buffer.size(); i++){
        fout << buffer[i];
    }
    fout.close();

    DeleteCriticalSection(&pushCriticalSection);
    return 0;
}
