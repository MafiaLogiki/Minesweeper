#include "Field.h"

void field::open_cell(double x, double y) {
    for (auto& cell_row : main_field) {
        for (auto& c : cell_row) {
            if (c.check_is_inside(x, y, cell_size)) {
                c.open();
                return;
            }
        }
    }
}