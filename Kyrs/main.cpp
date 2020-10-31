#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include "circle/Circle.h"
#include "application/Applicaton.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MenuWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND menuHwnd, gameHwnd;
BOOL setWhite = FALSE;

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

    const CHAR *MENU_NAME = "Menu Class";

    WNDCLASS menuClass = { };

    menuClass.lpfnWndProc = MenuWindowProc;
    menuClass.hInstance = hInstance;
    menuClass.lpszClassName = MENU_NAME;
    menuClass.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&menuClass);

    gameHwnd = CreateWindowEx(
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

    if (gameHwnd == NULL)
    {
        return 1;
    }

    menuHwnd = CreateWindowEx(
            0,
            MENU_NAME,
            "Menu",
            WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    if (menuHwnd == NULL)
    {
        return 1;
    }

    ShowWindow(menuHwnd, nShowCmd);
    //ShowWindow(gameHwnd, nShowCmd);

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
        InvalidateRect(gameHwnd,NULL,FALSE);
        InvalidateRect(menuHwnd,NULL,FALSE);
        Sleep(SLEEP_TIME);
    }
    return 0;
}

void getCoordinate(float *x, float *y, float angle, float rad){
    *x = rad * cos(angle);
    *y = rad * sin(angle);
}

void drawAtom(HDC hdc, BaseAtom *atom){
    HBRUSH hbrush;
    hbrush = CreateSolidBrush(atom->color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hbrush);
    HFONT oldFont = (HFONT)SelectObject(hdc, applicaton.atomFont);

    float x = 0;
    float y = 0;
    getCoordinate(&x, &y, atom->angle, atom->rad);
    float left = x + WINDOW_WIDTH/2 - ATOM_DIAMETER / 2;
    float top = y + WINDOW_HEIGHT/2 - ATOM_DIAMETER / 2;
    float right = left + ATOM_DIAMETER;
    float bottom = top + ATOM_DIAMETER;
    Ellipse(hdc, left, top, right, bottom);

    RECT rect;
    char name[20];
    strcpy_s(name, atom->name.size()+1,atom->name.c_str());
    if (atom->mass > 0) {
        SetRect(&rect,left,top,right,bottom);
        strcat_s(name, 20, "\n");
        strcat_s(name, 20, to_string(atom->mass).c_str());
    } else {
        SetRect(&rect,left,top + ATOM_DIAMETER / 4,right,bottom - ATOM_DIAMETER / 4);
    }

    SetTextColor(hdc, WHITE);
    SetBkMode(hdc, TRANSPARENT);
    DrawText(hdc,name, -1, &rect, DT_CENTER);
    SetBkMode(hdc, OPAQUE);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldFont);
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
        case WM_CLOSE:{
            ShowWindow(hwnd, SW_HIDE);
            ShowWindow(menuHwnd, SW_SHOWNORMAL);
            return 0;
        }

        case WM_PAINT:
        {
            fillWindow(hwnd);
            return 0;
        }
        case WM_LBUTTONUP:
        {
            float angle = getAngle(lParam);
            if (applicaton.getNextAtom()->mass != -1) {
                if (applicaton.getNextAtom()->isMinusCenter && GET_X_LPARAM(lParam) < (WINDOW_WIDTH + ATOM_DIAMETER)/2 &&
                        GET_X_LPARAM(lParam) > (WINDOW_WIDTH - ATOM_DIAMETER)/2 &&
                        GET_Y_LPARAM(lParam) < (WINDOW_HEIGHT + ATOM_DIAMETER)/2 &&
                        GET_Y_LPARAM(lParam) > (WINDOW_WIDTH - ATOM_DIAMETER)/2)
                {
                    applicaton.changeToPlus();
                } else {
                    applicaton.pushAtom(angle, applicaton.getNextAtom());
                    //if (!circle.checkOverflow()) {
                    applicaton.generateNextAtom();
                    //} else {
                    //  PostMessage(hwnd,WM_QUIT,wParam,lParam);
                    //}
                }
            } else {
                applicaton.popAtom(angle);
            }
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2){
    MoveToEx(hdc,x1,y1,NULL);
    return LineTo(hdc, x2, y2);
}

void fillMenu(HWND hwnd){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HDC memHdc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right,clientRect.bottom);
    HBITMAP oldbmp = (HBITMAP)SelectObject(memHdc, bmp);

    FillRect(memHdc, &ps.rcPaint, applicaton.backgroundBrush);

    HFONT font = CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY, VARIABLE_PITCH, NULL);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);

    RECT rect;

    SetRect(&rect,WINDOW_WIDTH / 2 - 20,WINDOW_HEIGHT - 100,WINDOW_WIDTH / 2 + 20,WINDOW_HEIGHT - 60);

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    if (pt.x > WINDOW_WIDTH / 2 - 20 && pt.x < WINDOW_WIDTH / 2 + 20 && pt.y > WINDOW_HEIGHT - 100 && pt.y < WINDOW_HEIGHT - 60)
    {
        SetTextColor(memHdc, WHITE);
    } else {
        SetTextColor(memHdc, BLACK);
    }

    SetBkMode(memHdc, TRANSPARENT);
    DrawText(memHdc,"Play", -1, &rect, DT_CENTER);
    SetBkMode(memHdc, OPAQUE);

    SelectObject(memHdc, oldFont);
    DeleteObject(font);

    BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,memHdc,0,0,SRCCOPY);
    SelectObject(hdc,oldbmp);
    DeleteObject(bmp);
    DeleteDC(memHdc);

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK MenuWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            fillMenu(hwnd);
            return 0;
        }
        case WM_LBUTTONUP:
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            if (pt.x > WINDOW_WIDTH / 2 - 20 && pt.x < WINDOW_WIDTH / 2 + 20 && pt.y > WINDOW_HEIGHT - 100 && pt.y < WINDOW_HEIGHT - 60)
            {
                ShowWindow(hwnd, SW_HIDE);
                ShowWindow(gameHwnd, SW_SHOWNORMAL);
            }
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}