#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "aoc2.h"

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
    count_safe_reports(file);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_end);
    clock_gettime(CLOCK_MONOTONIC, &wall_end);
    printf("Execution time (CPU) in nanoseconds: %ld\n", cpu_end.tv_nsec - cpu_start.tv_nsec);
    printf("Execution time (Wall) in nanoseconds: %ld\n", wall_end.tv_nsec - wall_start.tv_nsec);
    return EXIT_SUCCESS;
}