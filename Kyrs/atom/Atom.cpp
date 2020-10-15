//
// Created by Алексей on 13.10.2020.
//

#include "Atom.h"


Atom::Atom(int mass) {
    this->mass = mass;
    this->lathinName = GAME_LATHIN_NAME[mass];
    this->name = GAME_NAME[mass];
    this->rad = 0;
    this->angle = 0;
    this->color = RGB( firstHash(this->lathinName) % 256,secondHash(this->lathinName) % 256,thirdHash(this->lathinName) % 256);
}

int Atom::firstHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol * 15;
    }
    return result;
}

int Atom::secondHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol*(int)symbol * 42;
    }
    return result;
}

int Atom::thirdHash(string str) {
    int result = 0;
    for (auto &symbol : str){
        result += (int)symbol*(int)symbol * (int)symbol * 51;
    }
    return result;
}

Atom::Atom() {}
