#include "ThreadpoolQueueProcessor.h"
#include <windows.h>
#include <iostream>
#include <queue>

ThreadpoolQueueProcessor::ThreadpoolQueueProcessor(queue <QueueElem> *MyQueue, vector<string> *Buffer) {
    InitializeThreadpoolEnvironment(&this->callbackEnvironment);

    InitializeCriticalSection(&popCriticalSection);
    this->pool = CreateThreadpool(nullptr);
    SetThreadpoolThreadMinimum(this->pool, 1);

    this->cleanupGroup = CreateThreadpoolCleanupGroup();
    SetThreadpoolCallbackCleanupGroup(&this->callbackEnvironment, this->cleanupGroup, nullptr);

    myQueue = MyQueue;
    buffer = Buffer;
}

QueueElem ThreadpoolQueueProcessor::popFromQueue(){

    EnterCriticalSection(&popCriticalSection);

    QueueElem result = myQueue->front();
    myQueue->pop();

    LeaveCriticalSection(&popCriticalSection);

    return result;
}


void ThreadpoolQueueProcessor::SortFile(QueueElem queueElem){
    int startIndex = queueElem.startOffset - 1;
    int finishIndex = queueElem.finishOffset;
    sort(buffer->begin()+startIndex,buffer->begin() + finishIndex);
}

void ThreadpoolQueueProcessor::queueElementHandler(ThreadpoolQueueProcessor *queueHandler){
    QueueElem queueElement = queueHandler->popFromQueue();
    queueHandler->SortFile(queueElement);
}

ThreadpoolQueueProcessor::~ThreadpoolQueueProcessor() {
    DeleteCriticalSection(&popCriticalSection);
    CloseThreadpoolCleanupGroup(this->cleanupGroup);
    CloseThreadpool(this->pool);
}

void ThreadpoolQueueProcessor::Process(std::queue <QueueElem> *queue, int threadCount) {
    SetThreadpoolThreadMaximum(this->pool, threadCount);

    PTP_WORK work = CreateThreadpoolWork(WorkCallback, this, &this->callbackEnvironment);
    for (int i = 0; i < threadCount; i++) {
        SubmitThreadpoolWork(work);
    }
}

void ThreadpoolQueueProcessor::Wait() {
    CloseThreadpoolCleanupGroupMembers(this->cleanupGroup, false, nullptr);
}

void ThreadpoolQueueProcessor::WorkCallback(PTP_CALLBACK_INSTANCE instance, PVOID parameter, PTP_WORK work) {
    auto *myThis = reinterpret_cast<ThreadpoolQueueProcessor *>(parameter);

    queueElementHandler(myThis);
}



