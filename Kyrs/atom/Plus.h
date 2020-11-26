//
// Created by Алексей on 15.10.2020.
//

#ifndef KYRS_PLUS_H
#define KYRS_PLUS_H


#include "BaseAtom.h"
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)

class Plus : public BaseAtom {

private:
    void create(int value) override;

public:
    bool isRed;

    void atomCreate(int value);

    Plus();

    ~Plus() override;
};


#endif //KYRS_PLUS_H
