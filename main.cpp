#define UNICODE
#include <windows.h>
#include <iostream>

#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void HideAllElementsOnWindow(HWND hwnd);
bool RegisterWindow(WNDCLASSEX *wc, HINSTANCE hInstance);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) { 
    WNDCLASSEX wc = {0};
    if (!RegisterWindow(&wc, hInstance)) {
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,
        L"SampleWindowClass",
        L"Minesweeper",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) {
        MessageBox(NULL, L"Creation Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

bool RegisterWindow(WNDCLASSEX *wc, HINSTANCE hInstance) {
    wc->cbSize        = sizeof(WNDCLASSEX);
    wc->style         = CS_HREDRAW | CS_VREDRAW;
    wc->lpfnWndProc   = WindowProc;
    wc->hInstance     = hInstance;
    wc->hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc->lpszClassName = L"SampleWindowClass";

    if (!RegisterClassEx(wc)) {
        MessageBox(NULL, L"Window Registration Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

            RECT rect;
            GetClientRect(hwnd, &rect);

            int button_width = 100;
            int button_high  = 50;

            int x = (rect.right - rect.left - button_width) / 2;
            int y = (rect.bottom - rect.top - button_high) / 2;

            HWND new_game_button = CreateWindowEx(
                0,
                L"BUTTON",
                L"New game",
                WS_VISIBLE | WS_CHILD,
                x, y, button_width, button_high,
                hwnd,   
                NULL, hInstance, NULL
            );
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void HideAllElementsOnWindow(HWND hwnd) {
    HWND ChildHWND = GetWindow(hwnd, GW_CHILD);
    while(!ChildHWND) {
        ShowWindow(ChildHWND, SW_HIDE);
        ChildHWND = GetWindow(hwnd, GW_HWNDNEXT);
    }
}