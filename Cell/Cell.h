#pragma once

#include <windows.h>

class cell {
    double start_x; // Left top start pos
    double start_y; // Left top start pos

    int is_open;
    int is_mine;

public:
    cell(double x, double y): start_x(x), start_y(y), is_open(0), is_mine(0) {}

    bool check_is_inside(double x, double y, double cell_size);
    bool open() {is_open = 1;};
};