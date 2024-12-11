#include "aoc9.h"

long long get_checksum(const char* input, int fragmentation_type) {
    char* disk_map = strdup(input);
    long long checksum = 0;
    long disk_map_len = (long)strlen(disk_map);
    int count_back = disk_map_len - 1;
    int count_forward = 0;
    int count_blocks = 0;
    while (disk_map[count_forward]) {
        char forward_block_count = disk_map[count_forward] - '0';
        if (fragmentation_type == last_file_to_first_empty_slot)
            count_back = disk_map_len - 1;
        if (count_forward % 2 == 0) {
            if (!forward_block_count)
                count_blocks += input[count_forward] - '0';
            for (int bb = 0; bb < forward_block_count; bb++) {
                checksum += count_blocks * count_forward / 2;
                count_blocks++;
            }
        }
        else {
            while (count_forward <= count_back) {
                if (count_back % 2 == 0) {
                    char back_block_count = disk_map[count_back] - '0';
                    if (fragmentation_type == last_block_to_first_empty_slot || back_block_count <= disk_map[count_forward] - '0')
                        for (int bb = 0; bb < back_block_count && disk_map[count_forward] - '0' && disk_map[count_back] - '0'; bb++) {
                            checksum += count_blocks * count_back / 2;
                            count_blocks++;
                            disk_map[count_forward]--;
                            disk_map[count_back]--;
                        }
                    if (disk_map[count_forward] - '0' == 0)
                        break;
                }
                count_back--;
            }
            count_blocks += disk_map[count_forward] - '0';
        }
        count_forward++;
    }
    return checksum;
}