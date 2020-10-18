//
// Created by Алексей on 15.10.2020.
//

#include "Plus.h"

void Plus::create(int value) {
    this->isRed = (value == 0);
    this->mass = 0;
    this->name = GAME_NAME[0];
    this->rad = 0;
    this->angle = 0;
    value == 0 ? this->color = RGB(255,0,0): this->color = RGB(0,0,0);
}
void Plus::atomCreate(int value) {
    this->create(value);
}

Plus::Plus() {}
