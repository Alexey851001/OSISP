//
// Created by Алексей on 13.10.2020.
//

#ifndef KYRS_CIRCLE_H
#define KYRS_CIRCLE_H

#include <list>
#include "../atom/Atom.h"

using namespace std;

class Circle {
public:

    list <Atom> gameCircle;
    Atom nextAtom;

    Circle();
    void push(Atom atom, int position);

    BOOL checkOverflow();

    void generateNext();

};


#endif //KYRS_CIRCLE_H
