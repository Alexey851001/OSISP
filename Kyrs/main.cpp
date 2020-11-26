#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include "circle/Circle.h"
#include "application/Applicaton.h"
#include "atom/Plus.h"
#include "atom/Minus.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MenuWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND menuHwnd, gameHwnd;

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
        if (!applicaton.isMenu) {
            InvalidateRect(gameHwnd, NULL, FALSE);
        } else {
            InvalidateRect(menuHwnd,NULL,FALSE);
        }
        Sleep(SLEEP_TIME);
    }
    return 0;
}

void getCoordinate(float *x, float *y, float angle, float rad){
    *x = rad * cos(angle);
    *y = rad * sin(angle);
}

void drawAtom(HDC hdc, BaseAtom *atom, float diameter, HFONT font, float x = 0 , float y = 0){
    HBRUSH hbrush;
    hbrush = CreateSolidBrush(atom->color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hbrush);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);

    if (x == 0 && y == 0)
        getCoordinate(&x, &y, atom->angle, atom->rad);
    float left = x + WINDOW_WIDTH/2 - diameter / 2;
    float top = y + WINDOW_HEIGHT/2 - diameter / 2;
    float right = left + diameter;
    float bottom = top + diameter;
    Ellipse(hdc, left, top, right, bottom);

    RECT rect;
    char name[TEXT_LENGTH];
    strcpy_s(name, atom->name.size()+1,atom->name.c_str());
    if (atom->mass > 0) {
        SetRect(&rect,left,top,right,bottom);
        strcat_s(name, TEXT_LENGTH, "\n");
        strcat_s(name, TEXT_LENGTH, to_string(atom->mass).c_str());
    } else {
        SetRect(&rect,left,top + diameter / 4,right,bottom - diameter / 4);
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
        drawAtom(memHdc, applicaton.getCircleValue(i), ATOM_DIAMETER, applicaton.atomFont);
    }

    drawAtom(memHdc,applicaton.getNextAtom(), ATOM_DIAMETER, applicaton.atomFont);

    SetBkMode(memHdc, TRANSPARENT);
    RECT scoreRect;
    SetRect(&scoreRect, applicaton.menuOffset, 0,WINDOW_WIDTH + applicaton.menuOffset, TEXT_HEIGHT);
    SetTextColor(memHdc, BLACK);
    char score[TEXT_LENGTH];
    strcpy_s(score, "Score: ");
    strcat_s(score, TEXT_LENGTH, to_string(applicaton.score).c_str());
    DrawText(memHdc, score, -1, &scoreRect, DT_CENTER);
    SetBkMode(memHdc, OPAQUE);

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
            applicaton.isMenu = TRUE;
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
            if (applicaton.checkGameOver()) {
                PostMessage(hwnd,WM_QUIT,wParam,lParam);
                return 0;
            }
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
                    applicaton.generateNextAtom();
                }
            } else {
                applicaton.popAtom(angle);
            }
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL checkMousePosition(HWND hwnd, int x1, int y1, int x2, int y2){
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    return (pt.x > x1 && pt.x < x2 && pt.y > y1 && pt.y < y2);
}

void drawTutorial(HDC hdc){
    Plus *plus = new Plus();
    Minus *minus = new Minus();
    minus->atomCreate(-1);
    plus->atomCreate(0);
    drawAtom(hdc,plus,ATOM_DIAMETER,applicaton.atomFont,-3*WINDOW_WIDTH/2 + ATOM_DIAMETER + applicaton.menuOffset,
             -WINDOW_HEIGHT / 2 + 3*ATOM_DIAMETER/2);
    RECT plusRectTutorial;
    SetTextColor(hdc, BLACK);
    SetBkMode(hdc, TRANSPARENT);
    SetRect(&plusRectTutorial, -1*WINDOW_WIDTH + 2 * ATOM_DIAMETER + applicaton.menuOffset,
            0, applicaton.menuOffset - ATOM_DIAMETER, 3*ATOM_DIAMETER);
    DrawText(hdc, "Unites two identical atoms if it comes between them. A chain reaction is possible.",
             -1, &plusRectTutorial, DT_WORDBREAK);
    SetBkMode(hdc, OPAQUE);

    drawAtom(hdc,minus,ATOM_DIAMETER,applicaton.atomFont,-3*WINDOW_WIDTH/2 + ATOM_DIAMETER + applicaton.menuOffset,
             -WINDOW_HEIGHT / 2 + 11*ATOM_DIAMETER/2);
    RECT minusRectTutorial;
    SetTextColor(hdc, BLACK);
    SetBkMode(hdc, TRANSPARENT);
    SetRect(&minusRectTutorial, -1*WINDOW_WIDTH + 2 * ATOM_DIAMETER + applicaton.menuOffset,
            4*ATOM_DIAMETER, applicaton.menuOffset - ATOM_DIAMETER, 7*ATOM_DIAMETER);
    DrawText(hdc, "Moves the selected atom to the middle. When pressed, the removed atom turns into +.",
             -1, &minusRectTutorial, DT_WORDBREAK);

    SetBkMode(hdc, OPAQUE);

    plus->atomCreate(1);
    drawAtom(hdc,plus,ATOM_DIAMETER,applicaton.atomFont,-3*WINDOW_WIDTH/2 + ATOM_DIAMETER + applicaton.menuOffset,
             -WINDOW_HEIGHT / 2 + 19*ATOM_DIAMETER/2);
    RECT blackPlusRectTutorial;
    SetTextColor(hdc, BLACK);
    SetBkMode(hdc, TRANSPARENT);
    SetRect(&blackPlusRectTutorial, -1*WINDOW_WIDTH + 2 * ATOM_DIAMETER + applicaton.menuOffset,
            8*ATOM_DIAMETER, applicaton.menuOffset - ATOM_DIAMETER, 11*ATOM_DIAMETER);
    DrawText(hdc, "Unites any two atoms if it comes between them. A chain reaction is possible.",
             -1, &blackPlusRectTutorial, DT_WORDBREAK);

    SetBkMode(hdc, OPAQUE);
}

void drawMenuText(HWND hwnd, HDC hdc, float xLeft, float yTop, float xRight, float yBottom, int compare){
    RECT rect;
    SetRect(&rect, xLeft, yTop, xRight, yBottom);
    if (checkMousePosition(hwnd, xLeft, yTop, xRight, yBottom))
    {
        SetTextColor(hdc, WHITE);
    } else {
        SetTextColor(hdc, BLACK);
    }
    SetBkMode(hdc, TRANSPARENT);

    switch (compare) {
        case -1:{
            if (applicaton.menuOffset <= 0)
                DrawText(hdc, LEFT_TEXT, -1, &rect, DT_CENTER);
            break;
        }
        case 0:{
            DrawText(hdc, PLAY_TEXT, -1, &rect, DT_CENTER);
            break;
        }
        case 1:{
            if (applicaton.menuOffset >= 0)
                DrawText(hdc, RIGHT_TEXT, -1, &rect, DT_CENTER);

        }
    }
    SetBkMode(hdc, OPAQUE);
}

void drawMendeleevTable(HDC hdc){
    Atom* atom = new Atom();
    atom->atomCreate(0);
    int i = 0;
    int j = 0;
    while (i * COUNT_OF_COLUMN + j + 1 <= COUNT_OF_ATOMS) {
        atom->atomCreate(i * 8 + j + 1);
        drawAtom(hdc, atom, ATOM_DIAMETER, applicaton.atomFont,
                 WINDOW_WIDTH / 2 + ATOM_DIAMETER * (j + 1) + (WINDOW_WIDTH / COUNT_OF_COLUMN - ATOM_DIAMETER) * j + applicaton.menuOffset,
                 -WINDOW_HEIGHT / 2 + (i + 1) * ATOM_DIAMETER + (WINDOW_WIDTH / COUNT_OF_COLUMN - ATOM_DIAMETER) * i);

        if ((j+1) % COUNT_OF_COLUMN == 0){
            i++;
            j = -1;
        }
        j++;
    }
}

void fillMenu(HWND hwnd){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HDC memHdc ;
    memHdc = CreateCompatibleDC(hdc);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    HBITMAP bmp = CreateCompatibleBitmap(hdc, clientRect.right,clientRect.bottom);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memHdc, bmp);

    FillRect(memHdc, &ps.rcPaint, applicaton.backgroundBrush);

    HFONT oldFont = (HFONT)SelectObject(memHdc, applicaton.menuFont);
    drawMenuText(hwnd,memHdc, (WINDOW_WIDTH - TEXT_WIDTH) / 2 + applicaton.menuOffset, WINDOW_HEIGHT - PLAY_Y_COORDINATE, (WINDOW_WIDTH + TEXT_WIDTH) / 2 + applicaton.menuOffset, WINDOW_HEIGHT - (PLAY_Y_COORDINATE - TEXT_HEIGHT), 0);
    drawMenuText(hwnd, memHdc, 0, (WINDOW_HEIGHT - TEXT_HEIGHT)/2,TEXT_HEIGHT, (WINDOW_HEIGHT + TEXT_HEIGHT)/2, -1);
    drawMenuText(hwnd, memHdc, WINDOW_WIDTH - 5*TEXT_HEIGHT/4,(WINDOW_HEIGHT - TEXT_HEIGHT)/2,WINDOW_WIDTH - TEXT_HEIGHT/2 , (WINDOW_HEIGHT + TEXT_HEIGHT)/2, 1);

    RECT scoreRect;
    SetRect(&scoreRect, applicaton.menuOffset, 0,WINDOW_WIDTH + applicaton.menuOffset, TEXT_HEIGHT);

    SetBkMode(memHdc, TRANSPARENT);
    SetTextColor(memHdc, BLACK);
    char highScore[TEXT_LENGTH];
    strcpy_s(highScore, HIGH_SCORE_TEXT);
    strcat_s(highScore, TEXT_LENGTH, to_string(applicaton.highScore).c_str());
    DrawText(memHdc, highScore, -1, &scoreRect, DT_CENTER);
    SetBkMode(memHdc, OPAQUE);

    drawTutorial(memHdc);
    drawMendeleevTable(memHdc);

    SelectObject(memHdc, oldFont);
    drawAtom(memHdc,applicaton.menuAtom,MENU_ATOM_DIAMETER,applicaton.menuAtomFont);

    BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,memHdc,0,0,SRCCOPY);
    SelectObject(hdc, oldBmp);
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
            if (checkMousePosition(hwnd, (WINDOW_WIDTH - TEXT_WIDTH)/2 + applicaton.menuOffset, WINDOW_HEIGHT - PLAY_Y_COORDINATE, (WINDOW_WIDTH + TEXT_WIDTH)/2 + applicaton.menuOffset, WINDOW_HEIGHT - (PLAY_Y_COORDINATE - TEXT_HEIGHT)))
            {
                ShowWindow(hwnd, SW_HIDE);
                applicaton.isMenu = FALSE;
                ShowWindow(gameHwnd, SW_SHOWNORMAL);
            }
            if (checkMousePosition(hwnd, 0,(WINDOW_HEIGHT - TEXT_HEIGHT)/2,TEXT_HEIGHT, (WINDOW_HEIGHT + TEXT_HEIGHT)/2))
            {
                applicaton.leftAnimation = TRUE;
            }
            if (checkMousePosition(hwnd, WINDOW_WIDTH - 5*TEXT_HEIGHT/4,(WINDOW_HEIGHT - TEXT_HEIGHT)/2,WINDOW_WIDTH - TEXT_HEIGHT/2 , (WINDOW_HEIGHT + TEXT_HEIGHT)/2))
            {
                applicaton.rightAnimation = TRUE;
            }
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}