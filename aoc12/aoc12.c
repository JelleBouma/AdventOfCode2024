#include "aoc12.h"

void process_pos(Matrix map, Matrix region, Pos pos, int* area, int* perimeter) {
    char plant = get_from_pos(map, pos);
    if (plant <= 'Z') {
        (*area)++;
        set_pos_to(region, pos, 1);
        set_pos_to(map, pos, plant + 26);
        for (int dd = 0; dd < 4; dd++) {
            Pos adjacent_pos = directions_4[dd](pos);
            if (is_in_range(adjacent_pos, map)) {
                char adjacent_plant = get_from_pos(map, adjacent_pos);
                if (adjacent_plant == plant)
                    process_pos(map, region, adjacent_pos, area, perimeter);
                else if (adjacent_plant != plant + 26)
                    (*perimeter)++;
            }
            else
                (*perimeter)++;
        }
    }
}

int get_sides_by_rows(Matrix region, Pos(*direction)(Pos)) {
    int sides = 0;
    Pos pos;
    gboolean found_side = false;
    for (pos.y = 0; pos.y < region.y_len; pos.y++)
        for (pos.x = 0; pos.x < region.x_len; pos.x++) {
            if (get_from_pos(region, pos) && !get_from_pos(region, direction(pos))) {
                if (!found_side) {
                    found_side = true;
                    sides++;
                }
            }
            else
                found_side = false;
        }
    return sides;
}

int get_sides_by_columns(Matrix region, Pos(*direction)(Pos)) {
    int sides = 0;
    Pos pos;
    gboolean found_side = false;
    for (pos.x = 0; pos.x < region.x_len; pos.x++)
        for (pos.y = 0; pos.y < region.y_len; pos.y++) {
            if (get_from_pos(region, pos) && !get_from_pos(region, direction(pos))) {
                if (!found_side) {
                    found_side = true;
                    sides++;
                }
            }
            else
                found_side = false;
        }
    return sides;
}

int get_sides(Matrix region) {
    return get_sides_by_rows(region, up) + get_sides_by_rows(region, down) + get_sides_by_columns(region, left) + get_sides_by_columns(region, right);
}

gint64 get_total_fence_price(char* map, gboolean has_bulk_discount) {
    gint64 total_fence_price = 0;
    Matrix matrix = new_matrix(map);
    Matrix region = new_matrix(strdup(map));
    clear_matrix(region, 0);
    Pos pos;
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            int area = 0;
            int perimeter = 0;
            process_pos(matrix, region, pos, &area, &perimeter);
            if (area != 0) {
                int sides = get_sides(region);
                if (has_bulk_discount)
                    total_fence_price += area * sides;
                else
                    total_fence_price += area * perimeter;
                clear_matrix(region, 0);
            }
        }
    return total_fence_price;
}