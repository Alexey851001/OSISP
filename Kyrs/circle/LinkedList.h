//
// Created by Алексей on 18.10.2020.
//

#ifndef KYRS_LINKEDLIST_H
#define KYRS_LINKEDLIST_H


#include "../atom/BaseAtom.h"

class LinkedList {
public:

    struct linkedList{
        BaseAtom* atom;
        linkedList* next;
        linkedList* prev;
    };
    linkedList* head;
    linkedList* tail;

    LinkedList();

    void insert(int position, BaseAtom* atom);

    void push_back(BaseAtom* atom);

    void push_front(BaseAtom* atom);

    BaseAtom* getValue(int position);

    void remove(BaseAtom* atom);

    int getSize();
private:
    int listSize;
};


#endif //KYRS_LINKEDLIST_H
