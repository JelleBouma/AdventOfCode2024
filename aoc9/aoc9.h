#ifndef AOC7_H
#define AOC7_H

#include <glib.h>

#define last_block_to_first_empty_slot 0
#define last_file_to_first_empty_slot 1

gint64 get_checksum(const char* disk_map, int fragmentation_type);

#endif //AOC7_H