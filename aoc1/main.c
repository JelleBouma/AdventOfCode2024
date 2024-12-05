#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define location_id_base 10

int cmpll(const void* a, const void* b) {
    if (*(long*)a - *(long*)b < 0)
        return -1;
    if (*(long*)a - *(long*)b > 0)
        return 1;
    return 0;
}

int count_ids(char *str) {
    char* next_id = str;
    int count = 0;
    while (next_id && *next_id) {
        strtol(next_id, &next_id, location_id_base);
        count++;
    }
    return count;
}

void calc_answers(FILE *file) {
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
    long column_0[pair_count], column_1[pair_count];
    char* next_location_id = buffer;
    for (int pp = 0; pp < pair_count; pp++) {
        column_0[pp] = strtol(next_location_id, &next_location_id, location_id_base);
        column_1[pp] = strtol(next_location_id, &next_location_id, location_id_base);
    }

    struct timespec cpu_start, cpu_end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_start);

    // sort arrays
    qsort(column_0, pair_count, sizeof(long), cmpll);
    qsort(column_1, pair_count, sizeof(long), cmpll);

    // calculate total distance
    long total_distance = 0;
    for (int pp = 0; pp < pair_count; pp++)
        total_distance += labs(column_0[pp] - column_1[pp]);
    printf("Total distance: %ld\n", total_distance);

    // calculate similarity score
    long similarity_score = 0;
    int indexer_0 = 0, indexer_1 = 0;
    while (indexer_0 < pair_count && indexer_1 < pair_count)
    {
        const long element_0 = column_0[indexer_0];
        const long element_1 = column_1[indexer_1];
        if (element_0 == element_1)
        {
            indexer_0++;
            indexer_1++;
            int count_0 = 1;
            int count_1 = 1;
            while (element_0 == column_0[indexer_0] && indexer_0 < pair_count)
            {
                count_0++;
                indexer_0++;
            }
            while (element_1 == column_1[indexer_1] && indexer_1 < pair_count)
            {
                count_1++;
                indexer_1++;
            }
            similarity_score += count_0 * count_1 * element_0;
        }
        else if (element_0 < element_1)
            indexer_0++;
        else if (element_0 > element_1)
            indexer_1++;
    }
    printf("Similarity score: %ld\n", similarity_score);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_end);
    printf("Execution time (CPU) in nanoseconds: %ld\n", cpu_end.tv_nsec - cpu_start.tv_nsec);
}

// supports location ids up to at least 2^31-1
int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Invalid number of arguments, usage: aoc1 [file]");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    calc_answers(file);
    return EXIT_SUCCESS;
}