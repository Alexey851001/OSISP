//
// Created by Алексей on 20.10.2020.
//

#include "Applicaton.h"
#include "../atom/Plus.h"

int Applicaton::getCircleSize() {
    return this->circle.gameCircle.getSize();
}

void Applicaton::pushAtom(float angle, BaseAtom *insertAtom){

    BOOL isInsert = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        BaseAtom* atom = this->getCircleValue(i);
        float range = (2*PI / (this->getCircleSize() + 1));
        if (atom->angle > angle) {
            insertAtom->angle = range * i;
            this->insertAtom(i, insertAtom);
            isInsert = TRUE;
            break;
        }
    }
    if (!isInsert){
        this->insertAtom(0, insertAtom);
    }
}

void Applicaton::plusAnimation(BaseAtom *plusAtom, BaseAtom *tempAtom, BaseAtom *stepAtom){
    float relativeAngle = min(abs(tempAtom->angle-plusAtom->angle),abs(stepAtom->angle - plusAtom->angle));
    if (relativeAngle != 0){
        float plusAnimationSpeed = relativeAngle / SLOWDOWN_PLUS_ANIMATION;
        if (plusAnimationSpeed < LOWEST_PLUS_ANIMATION_SPEED)
            plusAnimationSpeed = LOWEST_PLUS_ANIMATION_SPEED;

        tempAtom->angle -= plusAnimationSpeed;
        stepAtom->angle += plusAnimationSpeed;
        relativeAngle -= plusAnimationSpeed;
        if (relativeAngle < 0){
            tempAtom->angle -= relativeAngle;
            stepAtom->angle += relativeAngle;
            relativeAngle = 0;
        }
    } else {
        int mass = max(tempAtom->mass + 1, plusAtom->mass + 1);
        mass = max(mass, stepAtom->mass + 1);
        if (plusAtom->mass == 0){
            Plus *plus = (Plus*)plusAtom;
            plus->isRed ? 0 : mass += BLACK_PLUS_DEBUFF_MASS;
        }
        Atom *atom = new Atom();
        atom->atomCreate(mass);
        atom->isPlusCenter = TRUE;
        this->circle.gameCircle.remove(tempAtom);
        this->circle.gameCircle.remove(stepAtom);
        this->addPlusResult(plusAtom->angle, atom);
        atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
        this->circle.gameCircle.remove(plusAtom);
        this->score += mass * SCORE_MULTIPLY;
        Sleep(SLEEP_VALUE);
    }
}

BOOL Applicaton::plusAction(int position, BaseAtom *atom){
    BaseAtom *tempAtom = this->getCircleValue(position + 1);
    BaseAtom *stepAtom = this->getCircleValue(position - 1);
    Plus *plus = (Plus*)atom;
    if (plus->isRed) {
        if (tempAtom->mass == stepAtom->mass && tempAtom != stepAtom && tempAtom->mass != 0) {
            this->plusAnimation(atom, tempAtom, stepAtom);
            return TRUE;
        }
    } else {
        if (tempAtom != stepAtom ) {
            this->plusAnimation(atom, tempAtom, stepAtom);
            return TRUE;
        }
    }
    atom->isPlusCenter = FALSE;
    return FALSE;
}

void Applicaton::checkPlusAction(){
    this->isPlusAction = TRUE;
    bool find = FALSE;
    int size = this->getCircleSize();
    for (int i = 0; i < size; i++) {
        BaseAtom* atom = this->getCircleValue(i);
        if (atom->mass == 0 || atom->isPlusCenter) {
            if(this->plusAction(i, atom)){
                find = TRUE;
            }
        }
    }
    if (!find){
        this->isPlusAction = FALSE;
    }
}

void Applicaton::moveAnimation() {
    float circleDegree = 2 * PI;
    BOOL isCurrentValue = TRUE;
    float range = circleDegree / circle.gameCircle.getSize();
    for (int i = 0; i < circle.gameCircle.getSize(); i++) {
        BaseAtom *atom = circle.gameCircle.getValue(i);
        if(!this->isPlusAction) {
            if (atom->angle >  PI && (range * i) < PI/2){
                atom->angle -= 2*PI;
            }
            if (atom->angle < (range * i)) {
                atom->angle += ANGLE_SPEED;
                isCurrentValue = FALSE;
                if (atom->angle > (range * i)) {
                    atom->angle = range * i;
                }
            }
            if (atom->angle > (range * i )) {
                atom->angle -= ANGLE_SPEED;
                isCurrentValue = FALSE;
                if (atom->angle < (range * i)) {
                    atom->angle = (range * i);
                }
            }

            if (atom->rad < (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                atom->rad += RADIUS_SPEED;
                isCurrentValue = FALSE;
                if (atom->rad > (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                    atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
                }
            }
        }
    }
    if (circle.nextAtom->rad != 0){
        circle.nextAtom->rad -= RADIUS_SPEED;
        isCurrentValue = FALSE;
        if (circle.nextAtom->rad < 0){
            circle.nextAtom->rad = 0;
        }
    }
    if(isCurrentValue) {
        this->checkPlusAction();
    }
}

void Applicaton::updateScore(){
    if (this->score - this->limiter > (LEVEL_UP_SCORE + this->limiter / 2)){
        this->circle.workGroup.erase(this->circle.workGroup.begin());
        this->limiter += LEVEL_UP_SCORE;
        this->circle.workGroup.push_back(this->limiter / LEVEL_UP_SCORE + WORKGROUP_SIZE);
    }
}

void Applicaton::update() {
    if (!this->isMenu) {
        moveAnimation();
    } else {
        menuAnimation();
    }
    updateScore();
}

Applicaton::Applicaton() {
    this->menuOffset = 0;
    this->leftAnimation = FALSE;
    this->rightAnimation = FALSE;
    this->isPlusAction = FALSE;
    this->circleLeft = WINDOW_WIDTH/2 - GAME_CIRCLE_RADIUS;
    this->circleTop = WINDOW_HEIGHT/2 - GAME_CIRCLE_RADIUS;
    this->circleRight = WINDOW_WIDTH/2 + GAME_CIRCLE_RADIUS;
    this->circleBottom = WINDOW_HEIGHT/2 + GAME_CIRCLE_RADIUS;
    this->backgroundBrush = CreateSolidBrush(BACKGROUND);
    this->circleBrush = CreateSolidBrush(BACKGROUND-COLOR_SHIFT);
    this->atomFont = CreateFont(ATOM_DIAMETER/2, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, VARIABLE_PITCH, NULL);
    this->menuFont = CreateFont(TEXT_HEIGHT, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, VARIABLE_PITCH, NULL);
    this->menuAtomFont = CreateFont(MENU_ATOM_DIAMETER/2, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, VARIABLE_PITCH, NULL);
    this->atomPen = CreatePen(0,1,WHITE);
    this->menuAtom = new Atom();
    this->menuAtom->atomCreate(1);
    this->highScore = 0;
    this->score = 0;
    this->limiter = 0;
    this->isMenu = TRUE;
}

Applicaton::~Applicaton() {
    DeleteObject(this->backgroundBrush);
    DeleteObject(this->circleBrush);
    DeleteObject(this->atomFont);
    DeleteObject(this->atomPen);
    DeleteObject(this->menuFont);
    DeleteObject(this->menuAtomFont);
    delete this->menuAtom;
}

BaseAtom *Applicaton::getCircleValue(int position) {
    return this->circle.gameCircle.getValue(position);
}

BaseAtom *Applicaton::getNextAtom() {
    return this->circle.nextAtom;
}

void Applicaton::generateNextAtom() {
    this->circle.generateNext();
}

void Applicaton::insertAtom(int position, BaseAtom* atom) {
    this->circle.gameCircle.insert(position,atom);
}

void Applicaton::addPlusResult(float angle, BaseAtom *insertAtom) {
    BOOL isInsert = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        BaseAtom* atom = this->getCircleValue(i);
        if (atom->angle > angle) {
            insertAtom->angle = angle;
            this->insertAtom(i, insertAtom);
            isInsert = TRUE;
            break;
        }
    }
    if (!isInsert){
        insertAtom->angle = angle;
        this->insertAtom(0, insertAtom);
    }
}

void Applicaton::popAtom(float angle) {
    BOOL isFind = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        BaseAtom* atom = this->getCircleValue(i);
        BaseAtom* stepAtom = this->getCircleValue(i - 1);
        if (atom->angle > angle) {
            BaseAtom *minus;
            abs(atom->angle - angle) > abs(stepAtom->angle - angle) ? minus = stepAtom : minus = atom;
            switch (minus->mass) {
                case 0:{
                    Plus *next = new Plus();
                    Plus *plus = (Plus*)minus;
                    next->atomCreate(!plus->isRed);
                    this->circle.nextAtom = next;
                    break;
                }
                default: {
                    Atom *next = new Atom();
                    next->atomCreate(minus->mass);
                    this->circle.nextAtom = next;
                }

            }
            this->circle.nextAtom->angle = minus->angle;
            this->circle.nextAtom->rad = minus->rad;
            this->circle.gameCircle.remove(minus);
            isFind = TRUE;
            break;
        }
    }
    if (!isFind){
        BaseAtom *minus;
        BaseAtom* atom = this->getCircleValue(0);
        BaseAtom* stepAtom = this->getCircleValue(this->getCircleSize() - 1);
        abs(atom->angle - (angle - 2*PI)) > abs(stepAtom->angle - angle) ? minus = stepAtom : minus = atom;
        switch (minus->mass) {
            case 0:{
                Plus *next = new Plus();
                Plus *plus = (Plus*)minus;
                next->atomCreate(!plus->isRed);
                this->circle.nextAtom = next;
                break;
            }
            default: {
                Atom *next = new Atom();
                next->atomCreate(minus->mass);
                this->circle.nextAtom = next;
            }
        }
        this->circle.nextAtom->angle = minus->angle;
        this->circle.nextAtom->rad = minus->rad;
        this->circle.gameCircle.remove(minus);
    }
    this->circle.nextAtom->isMinusCenter = TRUE;
}

void Applicaton::changeToPlus() {
    Plus *next = new Plus();
    next->atomCreate(0);
    this->circle.nextAtom = next;
}

void Applicaton::menuAnimation() {
    if (leftAnimation){
        if (menuOffset >= WINDOW_WIDTH){
            leftAnimation = FALSE;
        } else {
            menuOffset += 1;
        }
        if (menuOffset > 0 && menuOffset < WINDOW_WIDTH) {
            menuOffset += MENU_ANIMATION_SPEED;
            menuAtom->rad += MENU_ANIMATION_SPEED;
            if (menuOffset > WINDOW_WIDTH) {
                menuOffset = WINDOW_WIDTH;
                menuAtom->rad = WINDOW_WIDTH;
                leftAnimation = FALSE;
            }
        } else {
            if (menuOffset > -1 * WINDOW_WIDTH && menuOffset < 0) {
                menuOffset += MENU_ANIMATION_SPEED;
                menuAtom->rad += MENU_ANIMATION_SPEED;
                if (menuOffset > 0) {
                    menuOffset = 0;
                    menuAtom->rad = 0;
                    leftAnimation = FALSE;
                }
            } else {
                leftAnimation = FALSE;
            }
        }
    }
    if (rightAnimation) {
        if (menuOffset <= -1*WINDOW_WIDTH){
            rightAnimation = FALSE;
        } else {
            menuOffset -= 1;
        }
        if (menuOffset < 0 && menuOffset > -1*WINDOW_WIDTH) {
            menuOffset -= MENU_ANIMATION_SPEED;
            menuAtom->rad -= MENU_ANIMATION_SPEED;
            if (menuOffset < -1*WINDOW_WIDTH) {
                menuOffset = -1 * WINDOW_WIDTH;
                menuAtom->rad = -1 * WINDOW_WIDTH;
                rightAnimation = FALSE;
            }
        } else {
            if (menuOffset < WINDOW_WIDTH && menuOffset > 0){
                menuOffset -= MENU_ANIMATION_SPEED;
                menuAtom->rad -= MENU_ANIMATION_SPEED;
                if (menuOffset < 0) {
                    menuOffset = 0;
                    menuAtom->rad = 0;
                    rightAnimation = FALSE;
                }
            } else {
                rightAnimation = FALSE;
            }
        }
    }
}

bool Applicaton::checkGameOver() {
    return this->circle.checkOverflow();
}
