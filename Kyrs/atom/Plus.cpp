//
// Created by Алексей on 15.10.2020.
//

#include "Plus.h"

void Plus::create(int value) {
    this->isRed = (value == 0);
}
void Plus::atomCreate(int value) {
    this->create(value);
}

Plus::Plus() {}
