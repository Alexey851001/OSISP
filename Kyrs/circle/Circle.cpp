//
// Created by Алексей on 13.10.2020.
//

#include "Circle.h"

Circle::Circle() {
    this->workGroup.push_back(1);
    this->workGroup.push_back(2);
    this->workGroup.push_back(3);
    this->workGroup.push_back(4);
    for (int i = 0; i < 8; i++){
        int j = (rand()) % 4 ;
        Atom tempAtom;
        tempAtom.atomCreate(this->workGroup[j]);
        this->gameCircle.push_front(tempAtom);
    }
    generateNext();
}

void Circle::generateNext() {
    Atom next;
    int j = (rand()) % 4;
    if (j < 4) {
        next.atomCreate(this->workGroup[j]);
    }
    this->nextAtom = next;
}
