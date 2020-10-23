//
// Created by Алексей on 18.10.2020.
//

#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = NULL;
    this->tail = NULL;
    this->listSize = 0;
}
int LinkedList::getSize() {
    return listSize;
}
void LinkedList::push_front(IAtom * atom) {
    linkedList* node = new linkedList;
    node->atom = atom;
    node->next = head;
    head->prev = node;
    node->prev = tail;
    tail->next = node;
    head = node;
    listSize++;
}

void LinkedList::push_back(IAtom *atom) {
    linkedList* node = new linkedList;
    node->atom = atom;
    node->next = head;
    tail->next = node;
    node->prev = tail;
    head->prev = node;
    tail = node;
    listSize++;
}

void LinkedList::insert(int position, IAtom *atom) {
    linkedList* node = new linkedList;
    node->atom = atom;
    if (listSize == 0) {
        head = node;
        head->next = head;
        head->prev = head;
        tail = head;
        listSize++;
        return;
    }
    if (position == 0){
        push_front(atom);
        return;
    }
    if(position >= listSize){
        push_back(atom);
        return;
    }
    linkedList* temp = head;
    for(int i = 0; i < position - 1; i++){
        temp = temp->next;
    }
    node->next = temp->next;
    temp->next->prev = node;
    node->prev = temp;
    temp->next = node;
    listSize++;
}

IAtom * LinkedList::getValue(int position) {
    if(position < 0){
        position += listSize;
    }
    if (position >= listSize){
        position -= listSize;
    }
    linkedList* temp = head;
    for(int i = 0; i < position; i++){
        temp = temp->next;
    }
    return temp->atom;
}

void LinkedList::remove(IAtom *atom) {
    linkedList* temp = head;
    int count = 0;
    while(temp->atom != atom){
        if (count > listSize){
            return;
        }
        temp = temp->next;
        count++;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == head){
        head = temp->next;
    }
    if (temp == tail){
        tail = temp->prev;
    }
    listSize--;
    delete temp->atom;
    free(temp);
}