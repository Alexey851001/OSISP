#ifndef OSISP_5_THREADPOOLQUEUEPROCESSOR_H
#define OSISP_5_THREADPOOLQUEUEPROCESSOR_H

#include <windows.h>
#include <queue>

#include "queueElem/QueueElem.h"
#include "queueHandler/QueueHandler.h"

class ThreadpoolQueueProcessor {
public:
    queue <QueueElem> *myQueue;
    vector<string> *buffer;
    CRITICAL_SECTION popCriticalSection;

    ThreadpoolQueueProcessor(queue <QueueElem> *MyQueue, vector<string>* Buffer);

    ~ThreadpoolQueueProcessor();

    void Process(std::queue <QueueElem> *queue, int threadCount);

    void Wait();

private:
    PTP_POOL pool;
    PTP_CLEANUP_GROUP cleanupGroup;
    TP_CALLBACK_ENVIRON callbackEnvironment{};

    QueueElem popFromQueue();

    void SortFile(QueueElem queueElem);

    static void queueElementHandler(ThreadpoolQueueProcessor *queueHandler);

    static void CALLBACK WorkCallback(PTP_CALLBACK_INSTANCE instance, PVOID parameter, PTP_WORK work);
};


#endif
