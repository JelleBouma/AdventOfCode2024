#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define location_id_base 10

int cmpll(const void* a, const void* b) {
    if (*((long long*)a) - *((long long*)b) < 0)
        return -1;
    if (*((long long*)a) - *((long long*)b) > 0)
        return 1;
    return 0;
}

int count_ids(char *str) {
    char* next_id = str;
    int count = 0;
    while (next_id && *next_id) {
        strtoll(next_id, &next_id, location_id_base);
        count++;
    }
    return count;
}

long long fget_pairwise_sum_of_distances(FILE *file) {
    // read entire file into buffer
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char buffer[file_size + 1];
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = 0;
    fclose(file);

    // fill arrays with numbers
    int id_count = count_ids(buffer);
    int pair_count = id_count / 2;
    long long column_0[pair_count], column_1[pair_count];
    char* next_location_id = buffer;
    for (int pp = 0; pp < pair_count; pp++) {
        column_0[pp] = strtoll(next_location_id, &next_location_id, location_id_base);
        column_1[pp] = strtoll(next_location_id, &next_location_id, location_id_base);
    }

    // sort arrays
    qsort(column_0, pair_count, sizeof(long long), cmpll);
    qsort(column_1, pair_count, sizeof(long long), cmpll);

    // calculate
    long long pairwise_sum_of_distances = 0;
    for (int pp = 0; pp < pair_count; pp++)
        pairwise_sum_of_distances += llabs(column_0[pp] - column_1[pp]);
    return pairwise_sum_of_distances;
}

// supports location ids up to 2^63-aoc1 and line lengths up to 63 characters
int main(int argc, char **argv) {
    struct timespec cpu_start, cpu_end, wall_start, wall_end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_start);
    clock_gettime(CLOCK_MONOTONIC, &wall_start);
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc1 [file]");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    long long pairwise_sum_of_distances = fget_pairwise_sum_of_distances(file);
    printf("Smallest sum of distances: %lld\n", pairwise_sum_of_distances);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_end);
    clock_gettime(CLOCK_MONOTONIC, &wall_end);
    printf("Execution time (CPU) in nanoseconds: %ld\n", cpu_end.tv_nsec - cpu_start.tv_nsec);
    printf("Execution time (Wall) in nanoseconds: %ld\n", wall_end.tv_nsec - wall_start.tv_nsec);
    return EXIT_SUCCESS;
}