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
#define SLOWDOWN_PLUS_ANIMATION 10
#define LOWEST_PLUS_ANIMATION_SPEED 0.05
#define BLACK_PLUS_DEBUFF_MASS 2
#define SCORE_MULTIPLY 3
#define SLEEP_VALUE 10
#define LEVEL_UP_SCORE 500

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define SLEEP_TIME 5/3

#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define BACKGROUND RGB(0x60,0x7D,0x8B)
#define COLOR_SHIFT 30

#define TEXT_WIDTH 70
#define TEXT_HEIGHT 40
#define PLAY_Y_COORDINATE 100
#define TEXT_LENGTH 20
#define PLAY_TEXT "Play"
#define LEFT_TEXT "<"
#define RIGHT_TEXT ">"
#define HIGH_SCORE_TEXT "High Score: "

#define MENU_ATOM_DIAMETER WINDOW_WIDTH/3
#define MENU_ANIMATION_SPEED 20

#define COUNT_OF_ATOMS 32
#define COUNT_OF_COLUMN 8



class Applicaton {
public:
    float circleLeft;
    float circleTop;
    float circleRight;
    float circleBottom;
    HBRUSH backgroundBrush;
    HBRUSH circleBrush;
    HFONT atomFont;
    HFONT menuFont;
    HFONT menuAtomFont;
    HPEN atomPen;
    Atom* menuAtom;
    BOOL isMenu;

    int menuOffset;
    BOOL leftAnimation;
    BOOL rightAnimation;
    int highScore;
    int score;

    int getCircleSize();
    void insertAtom(int position, BaseAtom* atom);
    void generateNextAtom();
    BaseAtom* getCircleValue(int position);
    BaseAtom* getNextAtom();
    void update();
    void pushAtom(float angle, BaseAtom *insertAtom);
    void popAtom(float angle);
    void changeToPlus();
    bool checkGameOver();

    Applicaton();

    ~Applicaton();
private:
    void moveAnimation();
    void menuAnimation();
    void updateScore();
    void addPlusResult(float angle, BaseAtom *insertAtom);
    void plusAnimation(BaseAtom *plusAtom, BaseAtom *tempAtom, BaseAtom *stepAtom);
    BOOL plusAction(int position, BaseAtom *atom);
    void checkPlusAction();
    BOOL isPlusAction;
    Circle circle;
    int limiter;
};


#endif //KYRS_APPLICATON_H
