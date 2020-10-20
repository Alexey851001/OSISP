#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include "circle/Circle.h"
#include "application/Applicaton.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Applicaton applicaton;


int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
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

        applicaton.update();
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

void fillWindow(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HDC memHdc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right,clientRect.bottom);
    HBITMAP oldbmp = (HBITMAP)SelectObject(memHdc, bmp);

    FillRect(memHdc, &ps.rcPaint, applicaton.backgroundBrush);

    HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc,applicaton.circleBrush);
    Ellipse(memHdc, applicaton.circleLeft, applicaton.circleTop,
            applicaton.circleRight, applicaton.circleBottom);
    SelectObject(memHdc,oldBrush);

    for (int i = 0; i < applicaton.getCircleSize(); i++){
        drawAtom(memHdc, applicaton.getCircleValue(i));
    }

    drawAtom(memHdc,applicaton.getNextAtom());

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
            applicaton.pushAtom(angle, applicaton.getNextAtom());
            //if (!circle.checkOverflow()) {
                applicaton.generateNextAtom();
            //} else {
              //  PostMessage(hwnd,WM_QUIT,wParam,lParam);
            //}
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}