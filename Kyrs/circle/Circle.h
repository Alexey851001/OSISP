//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_CIRCLE_H
#define KYRS_CIRCLE_H

#include <list>
#include <vector>
#include "../atom/Atom.h"

using namespace std;

class Circle {

public:

    list <Atom> gameCircle;
    vector<int> workGroup;
    Atom nextAtom;

    Circle();

    BOOL checkOverflow();

    void generateNext();

};


#endif //KYRS_CIRCLE_H
