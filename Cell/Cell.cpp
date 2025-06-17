#include "Cell.h"

bool cell::check_is_inside(double x, double y, double cell_size) {
    return (x >= start_x) && (x <= x + cell_size) &&
           (y >= start_y) && (y <= y + cell_size);
}