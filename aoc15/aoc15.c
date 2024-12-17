#include "aoc15.h"

#define empty_char '.'
#define robot_char '@'
#define wall_char '#'
#define box_char 'O'
#define left_box_char '['
#define right_box_char ']'

void move_robot(Matrix matrix, Pos robot, char* moves) {
    GHashTable* char_direction_dict = get_char_direction_dict();
    char* move_iter = moves;
    while (*move_iter) {
        if (g_hash_table_contains(char_direction_dict, GINT_TO_POINTER(*move_iter))) {
            gint64 move_size = 0;
            Pos(*move_func)(Pos) = g_hash_table_lookup(char_direction_dict, GINT_TO_POINTER(*move_iter));
            Pos pos_to_check = move_func(robot);
            char char_to_check = get_from_pos(matrix, pos_to_check);
            while (char_to_check == box_char) {
                move_size++;
                pos_to_check = move_func(pos_to_check);
                char_to_check = get_from_pos(matrix, pos_to_check);
            }
            if (char_to_check != wall_char) {
                set_pos_to(matrix, pos_to_check, box_char);
                set_pos_to(matrix, robot, empty_char);
                robot = move_func(robot);
                set_pos_to(matrix, robot, robot_char);
            }
        }
        move_iter++;
    }
}

gint64 get_sum_of_box_gps_coordinates_from_matrix(Matrix matrix) {
    gint64 sum_of_box_gps_coordinates = 0;
    Pos pos = new_pos(0, 0);
    for (pos.y = 0; pos.y < matrix.y_len; pos.y++)
        for (pos.x = 0; pos.x < matrix.x_len; pos.x++) {
            char at_pos = get_from_pos(matrix, pos);
            if (at_pos == box_char || at_pos == left_box_char)
                sum_of_box_gps_coordinates += pos.x + pos.y * 100;
        }
    return sum_of_box_gps_coordinates;
}

gint64 get_sum_of_box_gps_coordinates(char* input) {
    char** split = split_on_empty_lines(input);
    Matrix matrix = new_matrix(split[0]);
    Pos robot = find_in_matrix(matrix, robot_char);
    move_robot(matrix, robot, split[1]);
    return get_sum_of_box_gps_coordinates_from_matrix(matrix);
}

char* scale_up_warehouse(char* warehouse) {
    gint64 len = (gint64)strlen(warehouse);
    char* scaled_up = malloc(len * 2);
    gint64 scaled_up_counter = 0;
    for (int cc = 0; cc < len; cc++) {
        char tile = warehouse[cc];
        if (tile == box_char) {
            scaled_up[scaled_up_counter] = left_box_char;
            scaled_up[scaled_up_counter + 1] = right_box_char;
            scaled_up_counter += 2;
        }
        else if (tile == robot_char) {
            scaled_up[scaled_up_counter] = robot_char;
            scaled_up[scaled_up_counter + 1] = empty_char;
            scaled_up_counter += 2;
        }
        else if (tile == wall_char || tile == empty_char) {
            scaled_up[scaled_up_counter] = tile;
            scaled_up[scaled_up_counter + 1] = tile;
            scaled_up_counter += 2;
        }
        else {
            scaled_up[scaled_up_counter] = tile;
            scaled_up_counter++;
        }
    }
    scaled_up[scaled_up_counter] = '\0';
    return scaled_up;
}

void move_robot_scaled_up(Matrix matrix, Pos robot, char* moves) {
    GHashTable* char_direction_dict = get_char_direction_dict();
    PosCharDict* pos_to_move_dict = pos_char_dict_new();
    char* robot_move_iter = moves;
    while (*robot_move_iter) {
        if (g_hash_table_contains(char_direction_dict, GINT_TO_POINTER(*robot_move_iter))) {
            Int64List* pos_to_check_list = NULL;
            Pos(*move_func)(Pos) = g_hash_table_lookup(char_direction_dict, GINT_TO_POINTER(*robot_move_iter));
            pos_char_dict_insert(pos_to_move_dict, robot, robot_char);
            int_list_prepend(&pos_to_check_list, move_func(robot).as_int);
            while (g_list_length(pos_to_check_list)) {
                Pos pos_to_check = (Pos)int_list_get(pos_to_check_list);
                pos_to_check_list = g_list_delete_link(pos_to_check_list, pos_to_check_list);
                char char_to_check = get_from_pos(matrix, pos_to_check);
                if (char_to_check == wall_char) {
                    g_list_free(pos_to_check_list);
                    pos_to_check_list = NULL;
                    g_hash_table_remove_all(pos_to_move_dict);
                    break;
                }
                Pos extra_pos;
                if (char_to_check == left_box_char)
                    extra_pos = right(pos_to_check);
                else if (char_to_check == right_box_char)
                    extra_pos = left(pos_to_check);
                if (char_to_check != empty_char) {
                    int_list_prepend(&pos_to_check_list, move_func(pos_to_check).as_int);
                    pos_char_dict_insert(pos_to_move_dict, pos_to_check, char_to_check);
                    if (move_func(extra_pos).as_int != pos_to_check.as_int) {
                        int_list_prepend(&pos_to_check_list, move_func(extra_pos).as_int);
                        pos_char_dict_insert(pos_to_move_dict, extra_pos, get_from_pos(matrix, extra_pos));
                    }
                }
            }
            if (g_hash_table_size(pos_to_move_dict)) {
                Int64List* pos_to_move_list = g_hash_table_get_keys(pos_to_move_dict);
                Int64List* iter = pos_to_move_list;
                while (iter) {
                    Pos to_move = (Pos)int_list_get(iter);
                    set_pos_to(matrix, to_move, empty_char);
                    iter = iter->next;
                }
                iter = pos_to_move_list;
                while (iter) {
                    Pos to_move = (Pos)int_list_get(iter);
                    set_pos_to(matrix, move_func(to_move), pos_char_dict_lookup(pos_to_move_dict, to_move));
                    iter = iter->next;
                }
                robot = move_func(robot);
                g_list_free(pos_to_check_list);
                pos_to_check_list = NULL;
                g_hash_table_remove_all(pos_to_move_dict);
            }
        }
        robot_move_iter++;
    }
}

gint64 get_sum_of_box_gps_coordinates_scaled_up(char* input) {
    char** split = split_on_empty_lines(input);
    Matrix matrix = new_matrix(scale_up_warehouse(split[0]));
    Pos robot = find_in_matrix(matrix, robot_char);
    move_robot_scaled_up(matrix, robot, split[1]);
    return get_sum_of_box_gps_coordinates_from_matrix(matrix);
}