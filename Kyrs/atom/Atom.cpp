//
// Created by Алексей on 13.10.2020.
//

#include "Atom.h"

void Atom::create(int value){
    this->mass = value;
    this->isPlusCenter = FALSE;
    this->isMinusCenter = FALSE;
    this->lathinName = GAME_LATHIN_NAME[value];
    this->name = GAME_NAME[value];
    this->rad = 0;
    this->angle = 0;
    this->color = RGB( firstHash(this->lathinName) % 256,secondHash(this->lathinName) % 256,thirdHash(this->lathinName) % 256);

}
void Atom::atomCreate(int mass) {
    this->create(mass);
}

int Atom::firstHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol * FIRST_HASH_ARGUMENT;
    }
    return result;
}

int Atom::secondHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol*(int)symbol * SECOND_HASH_ARGUMENT;
    }
    return result;
}

int Atom::thirdHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol * (int)symbol * (int)symbol * THIRD_HASH_ARGUMENT;
    }
    return result;
}

Atom::Atom() = default;

Atom::~Atom() = default;

