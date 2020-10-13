//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_ATOM_H
#define KYRS_ATOM_H


#include <windows.h>

const int maxRGBValue = 255;

class Atom {
public:

    COLORREF color;
    int mass;
    int x;
    int y;

    Atom(int mass);

    Atom();

};


#endif //KYRS_ATOM_H
