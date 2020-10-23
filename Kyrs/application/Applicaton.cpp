//
// Created by Алексей on 20.10.2020.
//

#include "Applicaton.h"
#include "../atom/Plus.h"

int Applicaton::getCircleSize() {
    return this->circle.gameCircle.getSize();
}

void Applicaton::pushAtom(float angle, IAtom *insertAtom){

    BOOL isInsert = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        IAtom* atom = this->getCircleValue(i);
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

void Applicaton::plusAnimation(IAtom *plusAtom, IAtom *tempAtom, IAtom *stepAtom){
    float relativeAngle = min(abs(tempAtom->angle-plusAtom->angle),abs(stepAtom->angle - plusAtom->angle));
    if (relativeAngle != 0){
        float plusAnimationSpeed = relativeAngle/10;
        if (plusAnimationSpeed < 0.05)
            plusAnimationSpeed = 0.05;

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
            plus->isRed ? 0 : mass += 2;
        }
        Atom *atom = new Atom();
        atom->atomCreate(mass);
        atom->isPlusCenter = TRUE;
        this->circle.gameCircle.remove(tempAtom);
        this->circle.gameCircle.remove(stepAtom);
        this->addPlusResult(plusAtom->angle, atom);
        atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
        this->circle.gameCircle.remove(plusAtom);
        Sleep(10);
    }
}

BOOL Applicaton::plusAction(int position, IAtom *atom){
    IAtom *tempAtom = this->getCircleValue(position+1);
    IAtom *stepAtom = this->getCircleValue(position - 1);
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
        IAtom* atom = this->getCircleValue(i);
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

void Applicaton::update() {
    float circleDegree = 2 * PI;
    BOOL isCurrentAngle = TRUE;
    BOOL isCurrentRadius = TRUE;
    float range = circleDegree / circle.gameCircle.getSize();
    for (int i = 0; i < circle.gameCircle.getSize(); i++) {
        IAtom *atom = circle.gameCircle.getValue(i);
        if(!this->isPlusAction) {
            if (atom->angle > 3 * PI / 2 && (range * i) < PI/2){
                atom->angle -= 2*PI;
            }
            if (atom->angle < (range * i)) {
                atom->angle += ANGLE_SPEED;
                isCurrentAngle = FALSE;
                if (atom->angle > (range * i)) {
                    atom->angle = range * i;
                }
            }
            if (atom->angle > (range * i )) {
                atom->angle -= ANGLE_SPEED;
                isCurrentAngle = FALSE;
                if (atom->angle < (range * i)) {
                    atom->angle = (range * i);
                }
            }

            if (atom->rad < (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                atom->rad += RADIUS_SPEED;
                isCurrentRadius = FALSE;
                if (atom->rad > (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                    atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
                }
            }
        }
    }
    if(isCurrentRadius && isCurrentAngle) {
        this->checkPlusAction();
    }
}


Applicaton::Applicaton() {
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
    this->atomPen = CreatePen(0,1,RGB(255,255,255));
}

Applicaton::~Applicaton() {
    DeleteObject(this->backgroundBrush);
    DeleteObject(this->circleBrush);
    DeleteObject(this->atomFont);
    DeleteObject(this->atomPen);
}

IAtom *Applicaton::getCircleValue(int position) {
    return this->circle.gameCircle.getValue(position);
}

IAtom *Applicaton::getNextAtom() {
    return this->circle.nextAtom;
}

void Applicaton::generateNextAtom() {
    this->circle.generateNext();
}

void Applicaton::insertAtom(int position, IAtom* atom) {
    this->circle.gameCircle.insert(position,atom);

}

void Applicaton::addPlusResult(float angle, IAtom *insertAtom) {
    BOOL isInsert = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        IAtom* atom = this->getCircleValue(i);
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
