#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include "circle/Circle.h"
#include "main.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Circle circle;
BOOL isPlusAction;


int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
    isPlusAction = FALSE;
    const CHAR *CLASS_NAME = "Window Class";

    WNDCLASS windowClass = { };

    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = CLASS_NAME;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&windowClass);

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "Atomas",
            WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    if (hwnd == NULL)
    {
        return 1;
    }

    ShowWindow(hwnd, nShowCmd);
    SetTimer(hwnd, 1, 100, NULL);
    MSG msg = { };
    BOOL isDone = FALSE;
    while (!isDone) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT){
                isDone = TRUE;
            }
        }

        InvalidateRect(hwnd,NULL,FALSE);
        Sleep(5/3);
    }
    return 0;
}

void getCoordinate(float *x, float *y, float angle, float rad){
    *x = rad * cos(angle);
    *y = rad * sin(angle);
}

void drawAtom(HDC hdc, IAtom *atom){
    HBRUSH hbrush;
    hbrush = CreateSolidBrush(atom->color);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hbrush);
    float x = 0;
    float y = 0;
    getCoordinate(&x, &y, atom->angle, atom->rad);
    float left = x + WINDOW_WIDTH/2 - ATOM_DIAMETER / 2;
    float top = y + WINDOW_HEIGHT/2 - ATOM_DIAMETER / 2;
    float right = left + ATOM_DIAMETER;
    float bottom = top + ATOM_DIAMETER;
    Ellipse(hdc, left, top, right, bottom);
    SelectObject(hdc, oldBrush);
    DeleteObject(hbrush);
}

void pushAtom(float angle, IAtom *insertAtom){

    BOOL isInsert = FALSE;
    for (int i = 0; i < circle.gameCircle.getSize(); i++){
        IAtom* atom = circle.gameCircle.getValue(i);
        if (atom->angle > angle) {
            insertAtom->angle = (2*PI / (circle.gameCircle.getSize() + 1)) * i;
            circle.gameCircle.insert(i, insertAtom);
            isInsert = TRUE;
            break;
        }
    }
    if (!isInsert){
        circle.gameCircle.insert(0, circle.nextAtom);
    }
}

void plusAnimation(IAtom *plusAtom, IAtom *tempAtom, IAtom *stepAtom){

    if((tempAtom->angle != plusAtom->angle) || (stepAtom->angle != plusAtom->angle)){

        if (tempAtom->angle < plusAtom->angle) {
            tempAtom->angle += PLUS_ANIMATION_SPEED;
            if (tempAtom->angle > plusAtom->angle) {
                tempAtom->angle = plusAtom->angle;
            }
        }
        if (tempAtom->angle > plusAtom->angle) {
            tempAtom->angle -= PLUS_ANIMATION_SPEED;
            if (tempAtom->angle < plusAtom->angle) {
                tempAtom->angle = plusAtom->angle;
            }
        }
        if (stepAtom->angle < plusAtom->angle) {
            stepAtom->angle += PLUS_ANIMATION_SPEED;
            if (stepAtom->angle > plusAtom->angle) {
                stepAtom->angle = plusAtom->angle;
            }
        }
        if (stepAtom->angle > plusAtom->angle) {
            stepAtom->angle -= PLUS_ANIMATION_SPEED;
            if (stepAtom->angle < plusAtom->angle) {
                stepAtom->angle = plusAtom->angle;
            }
        }
    } else {
        circle.gameCircle.remove(tempAtom);
        circle.gameCircle.remove(stepAtom);
        Atom *atom = new Atom();
        atom->atomCreate(tempAtom->mass + 1);
        atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
        atom->isPlusCenter = TRUE;
        pushAtom(plusAtom->angle, atom);
        circle.gameCircle.remove(plusAtom);
        isPlusAction = FALSE;
    }
}

bool plusAction(int position, IAtom *atom){
    IAtom *tempAtom = circle.gameCircle.getValue(position+1);
    IAtom *stepAtom = circle.gameCircle.getValue(position - 1);
    if (tempAtom->mass == stepAtom->mass){
        plusAnimation(atom, tempAtom, stepAtom);
        return TRUE;
    }
    return FALSE;
}

void checkPlusAction(){
    bool find = FALSE;
    for (int i = 0; i < circle.gameCircle.getSize(); i++) {
        IAtom* atom = circle.gameCircle.getValue(i);
        if (atom->mass == 0) {
            if(plusAction(i, atom)){
                find = TRUE;
            }
        }
    }
    if (!find){
        isPlusAction = FALSE;
    }
}

void moveAnimation(HDC memHdc){
    float circleDegree = 2 * PI;
    float range = circleDegree / circle.gameCircle.getSize();


    for (int i = 0; i < circle.gameCircle.getSize(); i++) {
        IAtom* atom = circle.gameCircle.getValue(i);
        if (!isPlusAction) {
            if (atom->angle < range * i) {
                atom->angle += 0.1;
                if (atom->angle > range * i) {
                    atom->angle = range * i;
                }
            }
            if (atom->angle > range * i) {
                atom->angle -= 0.1;
                if (atom->angle < range * i) {
                    atom->angle = range * i;
                }
            }
        } else {
            checkPlusAction();
        }
        if (atom->rad < (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
            atom->rad += 15;
            if (atom->rad > (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)) {
                atom->rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
            }
        }

        drawAtom(memHdc, atom);
    }

    IAtom *atom = circle.nextAtom;
    drawAtom(memHdc, atom);
}

void fillWindow(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HDC memHdc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right,clientRect.bottom);
    HBITMAP oldbmp = (HBITMAP)SelectObject(memHdc, bmp);

    HBRUSH backgroundBrush = CreateSolidBrush(BACKGROUND);

    FillRect(memHdc, &ps.rcPaint, backgroundBrush);

    DeleteObject(backgroundBrush);

    HBRUSH hbrush = CreateSolidBrush(BACKGROUND-COLOR_SHIFT);

    HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc,hbrush);
    float circleLeft = WINDOW_WIDTH/2 - GAME_CIRCLE_RADIUS;
    float circleTop = WINDOW_HEIGHT/2 - GAME_CIRCLE_RADIUS;
    float circleRight = WINDOW_WIDTH/2 + GAME_CIRCLE_RADIUS;
    float circleBottom = WINDOW_HEIGHT/2 + GAME_CIRCLE_RADIUS;
    Ellipse(memHdc, circleLeft, circleTop, circleRight, circleBottom);
    SelectObject(memHdc,oldBrush);
    DeleteObject(hbrush);

    moveAnimation(memHdc);

    BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,memHdc,0,0,SRCCOPY);
    SelectObject(hdc,oldbmp);
    DeleteObject(bmp);
    DeleteDC(memHdc);

    EndPaint(hwnd, &ps);
}

float getAngle(LPARAM lParam){
    float xPos = GET_X_LPARAM(lParam);
    float yPos = GET_Y_LPARAM(lParam);
    xPos -= WINDOW_WIDTH/2;
    yPos -= WINDOW_HEIGHT/2;
    float angle = atan(yPos/xPos);
    if (xPos < 0){
        angle += PI;
    } else {
        if (yPos < 0){
            angle += 2*PI;
        }
    }
    return angle;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            fillWindow(hwnd);
            return 0;
        }
        case WM_KEYDOWN:
        {
            return 0;
        }
        case WM_LBUTTONUP:
        {
            float angle = getAngle(lParam);
            pushAtom(angle, circle.nextAtom);
            isPlusAction = TRUE;
            //if (!circle.checkOverflow()) {
                circle.generateNext();
            //} else {
              //  PostMessage(hwnd,WM_QUIT,wParam,lParam);
            //}
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}