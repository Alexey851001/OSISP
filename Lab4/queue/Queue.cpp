//
// Created by Алексей on 13.10.2020.
//

#include "Queue.h"

void Queue::pushInQueue(QueueElem queueElement){

    EnterCriticalSection(&pushCriticalSection);

    this->myQueue.push(queueElement);

    LeaveCriticalSection(&pushCriticalSection);
}

QueueElem Queue::popFromQueue(){

    EnterCriticalSection(&popCriticalSection);

    QueueElem result = this->myQueue.front();
    this->myQueue.pop();

    LeaveCriticalSection(&popCriticalSection);

    return result;
}

Queue::Queue() {
    InitializeCriticalSection(&popCriticalSection);
    InitializeCriticalSection(&pushCriticalSection);
}

Queue::~Queue() {
    DeleteCriticalSection(&popCriticalSection);
    DeleteCriticalSection(&pushCriticalSection);
}