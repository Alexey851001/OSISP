//
// Created by Алексей on 13.10.2020.
//

#include "Atom.h"

Atom::Atom(int mass) {
    this->mass = mass;
    this->color = RGB(mass,mass/2,maxRGBValue - mass);
}

Atom::Atom() {}
