#include "aoc14.h"

Pos add_teleports(Pos pos, gint32 x_tiles, gint32 y_tiles) {
    if (pos.x < 0) {
        pos.x %= x_tiles;
        pos.x += x_tiles;
    }
    if (pos.y < 0) {
        pos.y %= y_tiles;
        pos.y += y_tiles;
    }
    return mod(pos, new_pos(x_tiles, y_tiles));
}

Pos get_robot_position(PosList** robot_data, gint32 x_tiles, gint32 y_tiles, gint64 move_count) {
    Pos pos = pos_list_iter(robot_data);
    Pos vel = pos_list_iter(robot_data);
    Pos without_teleports = plus(pos, mul(vel, new_pos(move_count, move_count)));
    return add_teleports(without_teleports, x_tiles, y_tiles);
}

int get_quadrant_index(Pos pos, Pos centre) {
    int index = 0b00;
    if (pos.x > centre.x)
        index |= 0b01;
    if (pos.y > centre.y)
        index |= 0b10;
    return index;
}

gint64 get_safety_factor(char* robots, gint32 x_tiles, gint32 y_tiles, gint64 move_count) {
    PosList* robot_data = pos_list_parse(robots);
    Pos centre = new_pos(x_tiles / 2, y_tiles / 2);
    gint64 quadrant_robot_counts[4] = {0};
    while (robot_data) {
        Pos pos = get_robot_position(&robot_data, x_tiles, y_tiles, move_count);
        if (pos.x != centre.x && pos.y != centre.y)
            quadrant_robot_counts[get_quadrant_index(pos, centre)]++;
    }
    g_list_free(robot_data);
    gint64 safety_factor = 1;
    for (int qq = 0; qq < 4; qq++)
        safety_factor *= quadrant_robot_counts[qq];
    return safety_factor;
}

gint64 get_seconds_to_lowest_safety_factor(char* robots, gint32 x_tiles, gint32 y_tiles) {
    gint64 seconds_to_lowest_safety_factor = 0;
    gint64 lowest_safety_factor = G_MAXINT64;
    for (gint64 ss = 0; ss < x_tiles * y_tiles; ss++) {
        gint64 safety_factor = get_safety_factor(robots, x_tiles, y_tiles, ss);
        if (safety_factor < lowest_safety_factor) {
            lowest_safety_factor = safety_factor;
            seconds_to_lowest_safety_factor = ss;
        }
    }
    return seconds_to_lowest_safety_factor;
}