//
// Created by Алексей on 13.10.2020.
//

#include "Circle.h"
#include "../atom/Plus.h"
#include "../atom/Minus.h"

Circle::Circle() {
    this->gameCircle;
    this->workGroup.push_back(1);
    this->workGroup.push_back(2);
    this->workGroup.push_back(3);
    this->workGroup.push_back(4);
    srand(time(NULL));
    for (int i = 0; i < 8; i++){

        int j = (rand()) % 4 ;
        Atom *tempAtom = new Atom();
        tempAtom->atomCreate(this->workGroup[j]);
        this->gameCircle.insert(0,tempAtom);
    }
    generateNext();
}

bool Circle::checkOverflow() {
    return this->gameCircle.getSize() == 17;
}


void Circle::generateNext() {
    srand(time(NULL));
    int j = (rand()) % 7;
    if (j < 4) {
        Atom *next = new Atom();
        next->atomCreate(this->workGroup[j]);
        this->nextAtom = next;
    } else {
        if (j < 6) {
            Plus *next = new Plus();
            next->atomCreate(j - 4);
            this->nextAtom = next;
        } else {
            Minus *next = new Minus();
            next->atomCreate(-1);
            this->nextAtom = next;
        }
    }
}
