//
// Created by Алексей on 23.10.2020.
//

#ifndef KYRS_MINUS_H
#define KYRS_MINUS_H

#define BLUE RGB(0,0,255)


#include "BaseAtom.h"

class Minus : public BaseAtom{
private:
    void create(int value) override;
public:

    void atomCreate(int value);

    Minus();

    ~Minus() override;

};


#endif //KYRS_MINUS_H
