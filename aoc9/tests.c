#include "aoc9.h"

char* input = "2333133121414131402";

void get_checksum_block_move_test() {
    long long checksum = get_checksum(input, last_block_to_first_empty_slot);
    g_assert_cmpint(checksum, ==, 1928);
}

void get_checksum_file_move_test() {
    long long checksum = get_checksum(input, last_file_to_first_empty_slot);
    g_assert_cmpint(checksum, ==, 2858);
}


int main(int argc, char **argv) {
    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/get_checksum/block_move", get_checksum_block_move_test);
    g_test_add_func("/get_checksum/file_move", get_checksum_file_move_test);
    return g_test_run();
}