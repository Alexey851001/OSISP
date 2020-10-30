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
