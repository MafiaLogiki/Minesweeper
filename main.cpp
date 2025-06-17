#define UNICODE
#include <windows.h>
#include <iostream>

#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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
        LoadMenu(hInstance, MAKEINTRESOURCE(MAIN_MENU)),
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
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}