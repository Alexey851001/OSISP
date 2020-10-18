//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_ATOM_H
#define KYRS_ATOM_H


#include <windows.h>
#include <string>
#include <map>
#include "../main.h"
#include "IAtom.h"

using namespace std;

class Atom : public IAtom{
private:
    map <int, string> GAME_LATHIN_NAME = {{1,  "Hydrogenium"}, {2, "Helium"}, {3, "Lithium"}, {4, "Beryllium"},
                                                 {5,  "Borum"}, {6, "Carboneum"}, {7, "Nitrogenium"}, {8, "Oxygenium"},
                                                 {9,  "Fluorum"}, {10, "Neon"}, {11, "Natrium"}, {12, "Magnesium"},
                                                 {13, "Aluminium"}, {14, "Silicium"}, {15, "Phosphorus"}, {16, "Sulfur"},
                                                 {17, "Chlorium"}, {18, "Argon"}, {19, "Kalium"}, {20, "Calcium"},
                                                 {21, "Scandium"}, {22, "Titanium"}, {23, "Vanadium"}, {24, "Chromium"},
                                                 {25, "Manganum"}, {26, "Ferrum"}, {27, "Cobaltum"}, {28, "Niccolum"}};

    int firstHash(string str);
    int secondHash(string str);
    int thirdHash(string str);
    void create(int value) override;
public:

    string lathinName;
    bool isPlusCenter;

    void atomCreate(int mass);

    Atom();

};


#endif //KYRS_ATOM_H
