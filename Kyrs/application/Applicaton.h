//
// Created by Алексей on 20.10.2020.
//

#ifndef KYRS_APPLICATON_H
#define KYRS_APPLICATON_H

#include <windows.h>
#include "../circle/Circle.h"

#define GAME_CIRCLE_RADIUS 200
#define ATOM_DIAMETER 40
#define PI 3.14

#define ANGLE_SPEED 0.1
#define RADIUS_SPEED 15

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define SLEEP_TIME 5/3

#define WHITE RGB(255,255,255)
#define BACKGROUND RGB(0x60,0x7D,0x8B)
#define COLOR_SHIFT 30

class Applicaton {
public:
    float circleLeft;
    float circleTop;
    float circleRight;
    float circleBottom;
    HBRUSH backgroundBrush;
    HBRUSH circleBrush;
    HFONT atomFont;
    HPEN atomPen;

    int getCircleSize();
    void insertAtom(int position, BaseAtom* atom);
    void generateNextAtom();
    BaseAtom* getCircleValue(int position);
    BaseAtom* getNextAtom();
    void update();
    void pushAtom(float angle, BaseAtom *insertAtom);
    void popAtom(float angle);
    void changeToPlus();

    Applicaton();

    ~Applicaton();
private:
    void addPlusResult(float angle, BaseAtom *insertAtom);
    void plusAnimation(BaseAtom *plusAtom, BaseAtom *tempAtom, BaseAtom *stepAtom);
    BOOL plusAction(int position, BaseAtom *atom);
    void checkPlusAction();
    BOOL isPlusAction;
    Circle circle;
};


#endif //KYRS_APPLICATON_H
