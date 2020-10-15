//
// Created by Алексей on 15.10.2020.
//

#ifndef KYRS_IATOM_H
#define KYRS_IATOM_H


#include <type_traits>
#include <string>
#include <windows.h>

using namespace std;

class IAtom  {
public:
    COLORREF color;
    int mass;

    float angle;
    float rad;

    string name;
     virtual void create(int value) = 0;
};


#endif //KYRS_IATOM_H
