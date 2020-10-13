//
// Created by Алексей on 27.09.2020.
//

#ifndef LAB4_QUEUEELEM_H
#define LAB4_QUEUEELEM_H


class QueueElem {
public:
    long startOffset{ 0 };
    long finishOffset{ 0 };

    QueueElem(long start, long finish);

};



#endif //LAB4_QUEUEELEM_H
