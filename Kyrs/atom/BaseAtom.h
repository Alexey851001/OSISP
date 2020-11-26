//
// Created by Алексей on 15.10.2020.
//

#ifndef KYRS_BASEATOM_H
#define KYRS_BASEATOM_H


#include <type_traits>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

class BaseAtom  {
public:
    map <int, string> GAME_NAME = {{-1,"-"},{0,  "+"},{1,  "H"}, {2, "He"}, {3, "Li"}, {4, "Be"},
                                   {5,  "B"}, {6, "C"}, {7, "N"}, {8, "O"},
                                   {9,  "F"}, {10, "Ne"}, {11, "Na"}, {12, "Mg"},
                                   {13, "Al"}, {14, "Si"}, {15, "P"}, {16, "S"},
                                   {17, "Cl"}, {18, "Ar"}, {19, "K"}, {20, "Ca"},
                                   {21, "Sc"}, {22, "Ti"}, {23, "V"}, {24, "Cr"},
                                   {25, "Mn"}, {26, "F"}, {27, "Co"}, {28, "Ni"},
                                   {29, "Cu"}, {30, "Zn"}, {31, "Ga"}, {32, "Ge"}};

    COLORREF color;
    int mass;
    bool isPlusCenter;
    bool isMinusCenter;

    float angle;
    float rad;

    string name;

    virtual void create(int value) = 0;

    virtual ~BaseAtom() = 0;
};


#endif //KYRS_BASEATOM_H
