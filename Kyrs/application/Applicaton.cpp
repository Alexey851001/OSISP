//
// Created by Алексей on 20.10.2020.
//

#include "Applicaton.h"

int Applicaton::getCircleSize() {
    return this->circle.gameCircle.getSize();
}

void Applicaton::pushAtom(float angle, IAtom *insertAtom){

    BOOL isInsert = FALSE;
    for (int i = 0; i < this->getCircleSize(); i++){
        IAtom* atom = this->getCircleValue(i);
        if (atom->angle > angle) {
            insertAtom->angle = (2*PI / (this->getCircleSize() + 1)) * i;
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

    int i = 0;//abs(tempAtom->angle-plusAtom->angle) > abs(stepAtom->angle - plusAtom->angle) ?
    float relativeAngle = min(abs(tempAtom->angle-plusAtom->angle),abs(stepAtom->angle - plusAtom->angle));
    //if((tempAtom->angle != plusAtom->angle) || (stepAtom->angle != plusAtom->angle)){
    if (relativeAngle != 0){
        float plusAnimationSpeed = relativeAngle/5;
        if (plusAnimationSpeed < 0.001)
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
        int mass = 0;
        if (tempAtom->mass > plusAtom->mass){
            mass = tempAtom->mass + 1;
        } else {
            mass = plusAtom->mass + 1;
        }
        this->circle.gameCircle.remove(tempAtom);
        this->circle.gameCircle.remove(stepAtom);
        Atom *atom = new Atom();
        atom->atomCreate(mass);
        atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
        atom->isPlusCenter = TRUE;
        this->addPlusResult(plusAtom->angle, atom);
        this->circle.gameCircle.remove(plusAtom);
        Sleep(10);
    }
}

BOOL Applicaton::plusAction(int position, IAtom *atom){
    IAtom *tempAtom = this->getCircleValue(position+1);
    IAtom *stepAtom = this->getCircleValue(position - 1);
    if (tempAtom->mass == stepAtom->mass && tempAtom != stepAtom){
        this->plusAnimation(atom, tempAtom, stepAtom);
        return TRUE;
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
            if (atom->angle < range * i) {
                atom->angle += 0.1;
                isCurrentAngle = FALSE;
                if (atom->angle > range * i) {
                    atom->angle = range * i;
                }
            }
            if (atom->angle > range * i) {
                atom->angle -= 0.1;
                isCurrentAngle = FALSE;
                if (atom->angle < range * i) {
                    atom->angle = range * i;
                }
            }

            if (atom->rad < (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                atom->rad += 15;
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
}

Applicaton::~Applicaton() {

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
        this->insertAtom(0, insertAtom);
    }
}
