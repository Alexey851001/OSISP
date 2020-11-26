//
// Created by Алексей on 13.10.2020.
//

#include "Circle.h"
#include "../atom/Plus.h"
#include "../atom/Minus.h"

Circle::Circle() {
    for (int i = 0; i < WORKGROUP_SIZE; i++) {
        this->workGroup.push_back(i + 1);
    }
    srand(time(NULL));
    for (int i = 0; i < START_GAME_CIRCLE_SIZE; i++){

        int j = (rand()) % WORKGROUP_SIZE;
        Atom *tempAtom = new Atom();
        tempAtom->atomCreate(this->workGroup[j]);
        this->gameCircle.insert(0,tempAtom);
    }
    generateNext();
}

bool Circle::checkOverflow() {
    return this->gameCircle.getSize() == GAME_OVER_COUNTER;
}


void Circle::generateNext() {
    srand(time(NULL));
    int j = (rand()) % ATOMS_IN_GAME;
    if (j < WORKGROUP_SIZE) {
        Atom *next = new Atom();
        next->atomCreate(this->workGroup[j]);
        this->nextAtom = next;
    } else {
        if (j < WORKGROUP_SIZE + 2) {
            Plus *next = new Plus();
            next->atomCreate(j - WORKGROUP_SIZE);
            this->nextAtom = next;
        } else {
            Minus *next = new Minus();
            next->atomCreate(-1);
            this->nextAtom = next;
        }
    }
}
