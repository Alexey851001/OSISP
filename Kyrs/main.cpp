#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include "circle/Circle.h"
#include "main.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Circle circle;


int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
    const CHAR *CLASS_NAME = "Window Class";

    WNDCLASS windowClass = { };

    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = CLASS_NAME;

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

void drawAtom(HDC hdc, Atom atom){
    HBRUSH hbrush;
    hbrush = CreateSolidBrush(atom.color);
    SelectObject(hdc, hbrush);
    float x = 0;
    float y = 0;
    getCoordinate(&x, &y, atom.angle, atom.rad);
    float left = x + WINDOW_WIDTH/2 - ATOM_DIAMETER / 2;
    float top = y + WINDOW_HEIGHT/2 - ATOM_DIAMETER / 2;
    float right = left + ATOM_DIAMETER;
    float bottom = top + ATOM_DIAMETER;
    Ellipse(hdc, left, top, right, bottom);
    DeleteObject(hbrush);
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

    FillRect(memHdc, &ps.rcPaint, CreateSolidBrush(BACKGROUND));

    HBRUSH hbrush = CreateSolidBrush(BACKGROUND-COLOR_SHIFT);
    SelectObject(memHdc,hbrush);
    float circleLeft = WINDOW_WIDTH/2 - GAME_CIRCLE_RADIUS;
    float circleTop = WINDOW_HEIGHT/2 - GAME_CIRCLE_RADIUS;
    float circleRight = WINDOW_WIDTH/2 + GAME_CIRCLE_RADIUS;
    float circleBottom = WINDOW_HEIGHT/2 + GAME_CIRCLE_RADIUS;
    Ellipse(memHdc, circleLeft, circleTop, circleRight, circleBottom);
    DeleteObject(hbrush);

    float circleDegree = 2*PI;
    float range = circleDegree / circle.gameCircle.size();

    float i = 0;
    for(auto &atom : circle.gameCircle) {
        if (atom.angle < range * i){
            atom.angle += 0.1;
            if (atom.angle > range*i){
                atom.angle = range * i;
            }
        }
        if (atom.rad < (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)){
            atom.rad += 7;
            if (atom.rad > (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2)){
                atom.rad = (GAME_CIRCLE_RADIUS - ATOM_DIAMETER / 2);
            }
        }
        if (atom.angle > range*i){
            atom.angle -= 0.1;
            if (atom.angle < range*i){
                atom.angle = range*i;
            }
        }
        drawAtom(memHdc, atom);
        i++;
    }

    Atom atom = circle.nextAtom;
    drawAtom(memHdc, atom);

    BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,memHdc,0,0,SRCCOPY);
    SelectObject(hdc,oldbmp);
    DeleteObject(bmp);
    DeleteDC(memHdc);

    EndPaint(hwnd, &ps);
}

void pushAtom(LPARAM lParam){
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
    auto iterator = circle.gameCircle.begin();
    float i = 0;
    BOOL isInsert = FALSE;
    for (auto &atom : circle.gameCircle){
        if (atom.angle > angle) {
            circle.nextAtom.angle = (2*PI / (circle.gameCircle.size() + 1)) * i;
            circle.gameCircle.insert(iterator, circle.nextAtom);
            isInsert = TRUE;
            break;
        }
        i++;
        advance(iterator, 1);
    }
    if (!isInsert){
        circle.gameCircle.insert(circle.gameCircle.begin(), circle.nextAtom);
    }
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
            pushAtom(lParam);
            circle.generateNext();
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}