//
// Created by Алексей on 27.09.2020.
//

#ifndef LAB4_QUEUEELEM_H
#define LAB4_QUEUEELEM_H


class QueueElem {
public:
    long startOffset{ 0 };
    long finishOffset{ 0 };

public:    QueueElem Create(long start, long finish) {
        QueueElem queueElem;
        queueElem.startOffset = start;
        queueElem.finishOffset = finish;
        return queueElem;
    }
};



#endif //LAB4_QUEUEELEM_H
