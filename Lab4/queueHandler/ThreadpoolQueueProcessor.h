#ifndef LAB4_THREADPOOLQUEUEPROCESSOR_H
#define LAB4_THREADPOOLQUEUEPROCESSOR_H

#include <Windows.h>
#include <queue>
#include <string>

#include "../queueElem/QueueElem.h"
#include "../queue/Queue.h"

using namespace std;

class ThreadpoolQueueProcessor {
public:
    Queue *myQueue;
    vector<string> *buffer;

    ThreadpoolQueueProcessor(Queue *MyQueue, vector<string>* Buffer);

    ~ThreadpoolQueueProcessor();

    void Process(int threadCount);

    void Wait();

private:
    PTP_POOL pool;
    PTP_CLEANUP_GROUP cleanupGroup;
    TP_CALLBACK_ENVIRON callbackEnvironment{};

    void SortFile(QueueElem queueElem);

    static void queueElementHandler(ThreadpoolQueueProcessor *queueHandler);

    static void CALLBACK WorkCallback(PTP_CALLBACK_INSTANCE instance, PVOID parameter, PTP_WORK work);
};


#endif
