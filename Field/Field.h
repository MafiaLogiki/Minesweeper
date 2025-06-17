#pragma once

#include <vector>

#include "../Cell/Cell.h"

class field {
    int width;
    int high;

    int cell_size;

    std::vector<std::vector<cell>> main_field;

public:
    field(int width, int high): width(width), high(high), cell_size(0), main_field(high, std::vector<cell>(width)) {}

    void open_cell(double x, double y);
    int is_endgame();
};