//
// Created by Алексей on 10.10.2020.
//

#ifndef LAB4_QUEUEHANDLER_H
#define LAB4_QUEUEHANDLER_H

#include <iostream>
#include <windows.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

#include "../queueElem/QueueElem.h"

using namespace std;

class QueueHandler {

public:
    queue <QueueElem> myQueue;
    vector<string> buffer;
    CRITICAL_SECTION popCriticalSection;

    QueueHandler(queue <QueueElem> MyQueue, vector<string> Buffer, CRITICAL_SECTION PopCriticalSection){
        myQueue = MyQueue;
        buffer = Buffer;
        popCriticalSection = PopCriticalSection;
    }


};


#endif //LAB4_QUEUEHANDLER_H
