#include <stdio.h>
#include <math.h>
#include "aoc7.h"

gint64 plus(gint64 a, gint64 b) {
    return a + b;
}

gint64 mul(gint64 a, gint64 b) {
    return a * b;
}

gint64 concat(gint64 a, gint64 b) {
    char digits[32] = {0};
    sprintf(digits, "%lld%lld", a, b);
    return strtoll(digits, NULL, equation_base);
}


gint64(*plus_mul[2])(gint64, gint64) = { plus, mul };
gint64(*plus_mul_concat[3])(gint64, gint64) = { plus, mul, concat };

gint64 get_calibration_result(char* line, gint64(**operators)(gint64, gint64), int operator_count) {
    gint64 test_value = strtoll(line, &line, equation_base);
    line++;
    gint64 numbers[32];
    int number_count = 0;
    while (line && *line && *line != '\r') {
        gint64 number = strtol(line, &line, equation_base);
        numbers[number_count] = number;
        number_count++;
    }
    gint64 combination_count = pow(operator_count, (number_count - 1));
    for (int cc = 0; cc < combination_count; cc++) {
        gint64 calibration_result = numbers[0];
        for (int nn = 1; nn < number_count; nn++)
            calibration_result = operators[(cc / (int)pow(operator_count, nn - 1)) % operator_count](calibration_result, numbers[nn]);
        if (calibration_result == test_value)
            return test_value;
    }
    return 0;
}

gint64 get_total_calibration_result(char* input, gint64(**operators)(gint64, gint64), int operator_count) {
    gint64 total_calibration_result = 0;
    char** lines = g_strsplit(input, "\n", 0);
    while (*lines) {
        total_calibration_result += get_calibration_result(*lines, operators, operator_count);
        lines++;
    }
    return total_calibration_result;
}