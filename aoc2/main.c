#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define level_base 10
#define sector_max_byte_len 64

int are_levels_remaining(char* str)
{
    return str && *str && *str != '\r' && *str != '\n';
}

int is_safe(char* level) {
    long prev_level_val = strtol(level, &level, level_base);
    int prev_difference = 0;
    while (are_levels_remaining(level)) {
        long level_val = strtol(level, &level, level_base);
        long difference = level_val - prev_level_val;
        long abs_difference = labs(difference);
        int bad_difference = abs_difference < 1 || abs_difference > 3;
        int inconsistent_order = prev_difference != 0 && (prev_difference > 0 != difference > 0);
        if (bad_difference || inconsistent_order)
            return 0;
        prev_difference = difference;
        prev_level_val = level_val;
    }
    return 1;
}

int count_safe_reports(FILE* file) {
    int safe_report_count = 0;
    char sector_string[sector_max_byte_len];
    while (fgets(sector_string, sector_max_byte_len, file))
        safe_report_count += is_safe(sector_string);
    return safe_report_count;
}

// max line length = 63 bytes
int main(int argc, char **argv) {
    struct timespec cpu_start, cpu_end, wall_start, wall_end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_start);
    clock_gettime(CLOCK_MONOTONIC, &wall_start);
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc2 [file]");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    int safe_report_count = count_safe_reports(file);
    printf("Safe reports: %d\n", safe_report_count);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_end);
    clock_gettime(CLOCK_MONOTONIC, &wall_end);
    printf("Execution time (CPU) in nanoseconds: %ld\n", cpu_end.tv_nsec - cpu_start.tv_nsec);
    printf("Execution time (Wall) in nanoseconds: %ld\n", wall_end.tv_nsec - wall_start.tv_nsec);
    return EXIT_SUCCESS;
}