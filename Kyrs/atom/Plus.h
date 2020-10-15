//
// Created by Алексей on 15.10.2020.
//

#ifndef KYRS_PLUS_H
#define KYRS_PLUS_H


#include "IAtom.h"

class Plus : IAtom {

private:
    void create(int value) override;

public:
    bool isRed;

    void atomCreate(int value);

    Plus();
};


#endif //KYRS_PLUS_H
