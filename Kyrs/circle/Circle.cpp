//
// Created by Алексей on 13.10.2020.
//

#include "Circle.h"

Circle::Circle() {
    for (int i = 0;i < 6;i++) {
        Atom tempAtom(7);
        this->gameCircle.push_front(tempAtom);
    }
    for (int i = 0;i < 6;i++) {
        Atom tempAtom(6);
        this->gameCircle.push_front(tempAtom);
    }
    Atom next(1);
    this->nextAtom = next;
}
