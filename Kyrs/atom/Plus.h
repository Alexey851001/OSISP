//
// Created by Алексей on 15.10.2020.
//

#ifndef KYRS_PLUS_H
#define KYRS_PLUS_H


#include "IAtom.h"

class Plus : public IAtom {

private:
    void create(int value) override;

public:
    bool isRed;

    void atomCreate(int value);

    Plus();

    ~Plus() override;
};


#endif //KYRS_PLUS_H
