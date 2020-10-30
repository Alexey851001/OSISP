//
// Created by Алексей on 23.10.2020.
//

#include "Minus.h"

Minus::Minus() = default;

void Minus::create(int value) {
    this->mass = -1;
    this->isMinusCenter = FALSE;
    this->isPlusCenter = FALSE;
    this->name = GAME_NAME[value];
    this->rad = 0;
    this->angle = 0;
    this->color = BLUE;
}

Minus::~Minus() = default;

void Minus::atomCreate(int value) {
    this->create(value);
}
