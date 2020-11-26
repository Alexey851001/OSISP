//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_CIRCLE_H
#define KYRS_CIRCLE_H

#include <list>
#include <vector>
#include <ctime>
#include "../atom/Atom.h"
#include "LinkedList.h"

#define WORKGROUP_SIZE 4
#define START_GAME_CIRCLE_SIZE 8
#define GAME_OVER_COUNTER 25
#define ATOMS_IN_GAME 7

using namespace std;

class Circle {

public:
    LinkedList gameCircle;

    vector<int> workGroup;
    BaseAtom *nextAtom;

    Circle();

    bool checkOverflow();

    void generateNext();
};


#endif //KYRS_CIRCLE_H
