#include <stdio.h>
#include "aoc2.h"

int main() {
    char* file_contents;
    g_file_get_contents("aoc2input.txt", &file_contents, NULL, NULL);
    gint64 safe_report_count = count_safe_reports(file_contents, false);
    gint64 safe_report_count_with_dampener = count_safe_reports(file_contents, true);
    printf("Safe reports (without problem dampener): %lld\n", safe_report_count);
    printf("Safe reports (with problem dampener): %lld\n", safe_report_count_with_dampener);
    return EXIT_SUCCESS;
}