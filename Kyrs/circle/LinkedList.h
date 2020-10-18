//
// Created by Алексей on 18.10.2020.
//

#ifndef KYRS_LINKEDLIST_H
#define KYRS_LINKEDLIST_H


#include "../atom/IAtom.h"

class LinkedList {
public:

    struct linkedList{
        IAtom* atom;
        linkedList* next;
        linkedList* prev;
    };
    linkedList* head;
    linkedList* tail;

    LinkedList();

    void insert(int position, IAtom* atom);

    void push_back(IAtom* atom);

    void push_front(IAtom* atom);

    IAtom* getValue(int position);

    void remove(IAtom* atom);

    int getSize();
private:
    int listSize;
};


#endif //KYRS_LINKEDLIST_H
