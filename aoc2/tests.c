#include <assert.h>

#include "aoc2.h"

void ascending_should_be_safe() {
    assert(is_safe("1 2 3 4 5", 0));
}

void descending_should_be_safe() {
    assert(is_safe("5 4 3 2", 0));
}

void descending_one_ascending_dampened_should_be_safe() {
    assert(is_safe("5 6 3 2", 1));
}

void descending_two_ascending_dampened_should_be_unsafe() {
    assert(!is_safe("5 6 7 3 2", 1));
}

void one_dupe_number_should_be_unsafe() {
    assert(!is_safe("6 6 5", 0));
}

void one_dupe_number_dampened_should_be_safe() {
    assert(is_safe("6 6 5", 1));
}

void two_dupe_numbers_dampened_should_be_unsafe() {
    assert(!is_safe("6 6 6 5", 1));
}

void bad_difference_should_be_unsafe()
{
    assert(!is_safe("6 10 11", 0));
}

void bad_difference_dampened_should_be_safe()
{
    assert(is_safe("6 10 11", 1));
}

void two_bad_differences_dampened_should_be_unsafe()
{
    assert(!is_safe("9 7 2 1", 1));
}


int main(int argc, char **argv) {
    ascending_should_be_safe();
    descending_should_be_safe();
    descending_one_ascending_dampened_should_be_safe();
    descending_two_ascending_dampened_should_be_unsafe();
    one_dupe_number_should_be_unsafe();
    one_dupe_number_dampened_should_be_safe();
    two_dupe_numbers_dampened_should_be_unsafe();
    bad_difference_should_be_unsafe();
    bad_difference_dampened_should_be_safe();
    two_bad_differences_dampened_should_be_unsafe();
}