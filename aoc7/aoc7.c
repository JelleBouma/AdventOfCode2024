#include <stdio.h>
#include <math.h>
#include "aoc7.h"

long long plus(long long a, long long b) {
    return a + b;
}

long long mul(long long a, long long b) {
    return a * b;
}

long long concat(long long a, long long b) {
    char digits[32] = {0};
    sprintf(digits, "%lld%lld", a, b);
    return strtoll(digits, NULL, equation_base);
}


long long(*plus_mul[2])(long long, long long) = { plus, mul };
long long(*plus_mul_concat[3])(long long, long long) = { plus, mul, concat };

long long get_calibration_result(char* line, long long(**operators)(long long, long long), int operator_count) {
    long long test_value = strtoll(line, &line, equation_base);
    line++;
    long numbers[32];
    int number_count = 0;
    while (line && *line && *line != '\r') {
        long number = strtol(line, &line, equation_base);
        numbers[number_count] = number;
        number_count++;
    }
    long combination_count = pow(operator_count, (number_count - 1));
    for (int cc = 0; cc < combination_count; cc++) {
        long long calibration_result = numbers[0];
        for (int nn = 1; nn < number_count; nn++)
            calibration_result = operators[(cc / (int)pow(operator_count, nn - 1)) % operator_count](calibration_result, numbers[nn]);
        if (calibration_result == test_value)
            return test_value;
    }
    return 0;
}

long long get_total_calibration_result(char* input, long long(**operators)(long long, long long), int operator_count) {
    long long total_calibration_result = 0;
    char** lines = g_strsplit(input, "\n", 0);
    while (*lines) {
        total_calibration_result += get_calibration_result(*lines, operators, operator_count);
        lines++;
    }
    return total_calibration_result;
}