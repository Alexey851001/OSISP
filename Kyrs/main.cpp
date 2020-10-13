#include <iostream>
#include <windows.h>
#include "circle/Circle.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const int SHIFT_CODE = 4;
const int RADIUS = 200;
const int ATOM_RADIUS = 40;
const float PI = 3.14;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 800;
const COLORREF BACKGROUND = RGB(139, 0, 0);
const int COLOR_SHIFT = 30;

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
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void fillWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    RECT clientRect;

    FillRect(hdc, &ps.rcPaint, CreateSolidBrush(BACKGROUND));

    HBRUSH hbrush = CreateSolidBrush(BACKGROUND-COLOR_SHIFT);
    SelectObject(hdc,hbrush);
    float circleLeft = WINDOW_WIDTH/2-RADIUS;
    float circleTop = WINDOW_HEIGHT/2-RADIUS;
    float circleRight = WINDOW_WIDTH/2+RADIUS;
    float circleBottom = WINDOW_HEIGHT/2+RADIUS;
    Ellipse(hdc, circleLeft, circleTop, circleRight, circleBottom);
    DeleteObject(hbrush);

    float circleDegree = 2*PI;
    float range = circleDegree / circle.gameCircle.size();

    for(int i = 0; i < circle.gameCircle.size(); i++) {
        hbrush = CreateSolidBrush(circle.gameCircle.front().color);
        SelectObject(hdc, hbrush);
        float left = 0;
        float top = 0;
        float right = ATOM_RADIUS;
        float bottom = ATOM_RADIUS;
        Ellipse(hdc, left, top, right, bottom);
        DeleteObject(hbrush);
    }

    EndPaint(hwnd, &ps);
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
            fillWindow(hwnd, uMsg, wParam, lParam);
            return 0;
        }
        case WM_TIMER:
        {
            return 0;
        }
        case WM_KEYDOWN:
        {
            return 0;
        }
        case WM_MOUSEWHEEL:
        {

            return 0;
        }
        case WM_SIZE:
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}