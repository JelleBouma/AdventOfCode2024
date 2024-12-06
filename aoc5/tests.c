#include <assert.h>
#include "aoc5.h"

 char* input = "2|3\n"
"1|2\n"
"1|5\n"
"5|3\n"
"\n"
"5,3,1\n"
"1,2,3\n"
"1,5,3\n";

void order_page_numbers_test() {
    struct ordered_page pages[max_pages] = {0};
    order_page_numbers(input, pages);
    assert(pages[0].page == 1);
    assert(pages[1].page == 2);
    assert(pages[1].related_to_previous);
    assert(pages[2].page == 5);
    assert(!pages[2].related_to_previous);
    assert(pages[3].page == 3);
    assert(pages[3].related_to_previous);
    assert(pages[4].page == 0);
}

char* full_input = "47|53\n"
"97|13\n"
"97|61\n"
"97|47\n"
"75|29\n"
"61|13\n"
"75|53\n"
"29|13\n"
"97|29\n"
"53|29\n"
"61|53\n"
"97|53\n"
"61|29\n"
"47|13\n"
"75|47\n"
"97|75\n"
"47|61\n"
"75|61\n"
"47|29\n"
"75|13\n"
"53|13\n"
"\n"
"75,47,61,53,29\n"
"97,61,53,29,13\n"
"75,29,13\n"
"75,97,47,61,53\n"
"61,13,29\n"
"97,13,75,29,47\n";

void get_middle_page_total_test() {
    struct ordered_page pages[max_pages] = {0};
    char* updates = order_page_numbers(full_input, pages);
    long total = get_middle_page_total(updates, pages);
    assert(total == 143);
}


int main(int argc, char **argv) {
    order_page_numbers_test();
    get_middle_page_total_test();
}