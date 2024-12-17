#include "aoc15.h"

char* input = "##########\n"
              "#..O..O.O#\n"
              "#......O.#\n"
              "#.OO..O.O#\n"
              "#..O@..O.#\n"
              "#O#..O...#\n"
              "#O..O..O.#\n"
              "#.OO.O.OO#\n"
              "#....O...#\n"
              "##########\n"
              "\n"
              "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^\n"
              "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v\n"
              "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<\n"
              "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^\n"
              "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><\n"
              "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^\n"
              ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^\n"
              "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>\n"
              "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>\n"
              "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^";

void get_sum_of_box_gps_coordinates_test() {
    gint64 sum_of_box_gps_coordinates = get_sum_of_box_gps_coordinates(input);
    g_assert_cmpint(sum_of_box_gps_coordinates, ==, 10092);
}

void get_sum_of_box_gps_coordinates_scaled_up_test() {
    gint64 sum_of_box_gps_coordinates = get_sum_of_box_gps_coordinates_scaled_up(input);
    g_assert_cmpint(sum_of_box_gps_coordinates, ==, 9021);
}

int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_sum_of_box_gps_coordinates/test", get_sum_of_box_gps_coordinates_test);
    g_test_add_func("/get_sum_of_box_gps_coordinates_scaled_up/test", get_sum_of_box_gps_coordinates_scaled_up_test);
    return g_test_run();
}