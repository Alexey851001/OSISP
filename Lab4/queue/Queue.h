//
// Created by Алексей on 13.10.2020.
//

#ifndef LAB4_QUEUE_H
#define LAB4_QUEUE_H

#include <queue>
#include <windows.h>
#include "../queueElem/QueueElem.h"

using namespace std;

class Queue {
public:
    queue<QueueElem> myQueue;

    CRITICAL_SECTION pushCriticalSection;
    CRITICAL_SECTION popCriticalSection;

    Queue();
    ~Queue();

    void pushInQueue(QueueElem Element);

    QueueElem popFromQueue();

};


#endif //LAB4_QUEUE_H
