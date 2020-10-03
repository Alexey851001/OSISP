#include <iostream>
#include <windows.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

#include "queueElem/QueueElem.h"

#define FILE_PATH_TO_READ  "D:\\5sem\\OSISP\\OSISP\\Lab4\\test.txt"
#define FILE_PATH_TO_WRITE  "D:\\5sem\\OSISP\\OSISP\\Lab4\\out.txt"
#define MAX_STRING_SIZE 1024
#define COUNT_OF_THREAD 4

using namespace std;

queue <QueueElem> myQueue;
vector<string> buffer;

CRITICAL_SECTION pushCriticalSection;
CRITICAL_SECTION popCriticalSection;


void pushInQueue(QueueElem queueElement){

    EnterCriticalSection(&pushCriticalSection);

    myQueue.push(queueElement);

    LeaveCriticalSection(&pushCriticalSection);
}

QueueElem popFromQueue(){
    EnterCriticalSection(&popCriticalSection);

    QueueElem result = myQueue.front();
    myQueue.pop();

    LeaveCriticalSection(&popCriticalSection);

    return result;
}


void SortFile(QueueElem queueElem){
    int startIndex = queueElem.startOffset - 1;
    int finishIndex = queueElem.finishOffset;
    sort(buffer.begin()+startIndex,buffer.begin() + finishIndex);
}

void queueElementHandler(){
    QueueElem queueElement = popFromQueue();
    SortFile(queueElement);
    return;
}

void queueHandle(int countOfThreads){
   HANDLE* threadArray = new HANDLE[countOfThreads];
   for(int i = 0; i < countOfThreads;i++)
   {
       if (!myQueue.empty()) {
           HANDLE HThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) (queueElementHandler), NULL, 0, NULL);
           threadArray[i] = HThread;
       }
   }
   for(int i = 0; i < COUNT_OF_THREAD;i++) {
       WaitForSingleObject(threadArray[i], INFINITE);
   }
   for(int i = 0; i < countOfThreads;i++) {
       CloseHandle(threadArray[i]);
   }
   free(threadArray);
}

int main() {
    InitializeCriticalSection(&pushCriticalSection);
    InitializeCriticalSection(&popCriticalSection);

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
    if (stringCount > COUNT_OF_THREAD) {
        countOfThreads = COUNT_OF_THREAD;
        stringCountForThread = stringCount / COUNT_OF_THREAD;
        modCount = stringCount % COUNT_OF_THREAD;
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
        pushInQueue(queueElem);
    }

    queueHandle(countOfThreads);

    int countSort =  stringCount / stringCountForThread - 1;
    for (int i = 0; i < countSort; i++){
        if (i == (countSort - 1)) {
            std::inplace_merge(buffer.begin(), buffer.begin() + stringCountForThread * (i + 1),
                               buffer.end());
        } else {
            std::inplace_merge(buffer.begin(), buffer.begin() + stringCountForThread * (i + 1),
                               buffer.begin() + stringCountForThread * (i + 2));
        }
    }

    ofstream fout(FILE_PATH_TO_WRITE);
    for(int i = 0; i < buffer.size(); i++){
        fout << buffer[i];
    }
    fout.close();

    DeleteCriticalSection(&pushCriticalSection);
    DeleteCriticalSection(&popCriticalSection);
    return 0;
}
