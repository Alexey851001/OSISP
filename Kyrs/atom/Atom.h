//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_ATOM_H
#define KYRS_ATOM_H


#include <windows.h>
#include <string>
#include <map>
#include "../main.h"

using namespace std;

class Atom {
private:
    map <int, string> GAME_LATHIN_NAME = {{1,  "Hydrogenium"}, {2, "Helium"}, {3, "Lithium"}, {4, "Beryllium"},
                                                 {5,  "Borum"}, {6, "Carboneum"}, {7, "Nitrogenium"}, {8, "Oxygenium"},
                                                 {9,  "Fluorum"}, {10, "Neon"}, {11, "Natrium"}, {12, "Magnesium"},
                                                 {13, "Aluminium"}, {14, "Silicium"}, {15, "Phosphorus"}, {16, "Sulfur"},
                                                 {17, "Chlorium"}, {18, "Argon"}, {19, "Kalium"}, {20, "Calcium"},
                                                 {21, "Scandium"}, {22, "Titanium"}, {23, "Vanadium"}, {24, "Chromium"},{25, "Manganum"}, {26, "Ferrum"}, {27, "Cobaltum"}, {28, "Niccolum"}};

    map <int, string> GAME_NAME = {{1,  "H"}, {2, "He"}, {3, "Li"}, {4, "Be"},
                                                {5,  "B"}, {6, "C"}, {7, "N"}, {8, "O"},
                                                {9,  "F"}, {10, "Ne"}, {11, "Na"}, {12, "Mg"},
                                                {13, "Al"}, {14, "Si"}, {15, "P"}, {16, "S"},
                                                {17, "Cl"}, {18, "Ar"}, {19, "K"}, {20, "Ca"},
                                                {21, "Sc"}, {22, "Ti"}, {23, "V"}, {24, "Cr"},
                                                {25, "Mn"}, {26, "F"}, {27, "Co"}, {28, "Ni"}};

    int firstHash(string str);
    int secondHash(string str);
    int thirdHash(string str);
public:

    COLORREF color;
    int mass;

    float angle;
    float rad;

    string name;
    string lathinName;

    Atom(int mass);

    Atom();

};


#endif //KYRS_ATOM_H
