#include <string.h>
#include <stdlib.h>
#include "aoc5.h"

void get_middle_page_total_from_file(FILE* file) {
    // read entire file into buffer
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char buffer[file_size + 1];
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = 0;
    fclose(file);

    struct ordered_page pages[max_pages] = {0};
    char* updates = order_page_numbers(buffer, pages);
    long middle_page_total = get_middle_page_total(updates, pages);
    printf("middle page total: %ld", middle_page_total);
}
char* order_page_numbers(char* str, struct ordered_page* pages) {
    char* current_line = str;
    while (current_line && *current_line != '\n' && *current_line != '\r')
    {
        char* next_line = strchr(current_line, '\n');
        long before_page = strtol(current_line, &current_line, page_base);
        long after_page = strtol(current_line + 1, &current_line, page_base);
        int before_index = -1;
        int after_index = -1;
        for (int pp = 0; 1; pp++) {
            long page = pages[pp].page;
            if (page == before_page) {
                before_index = pp;
                if (after_index != -1) {
                    memmove(pages + after_index, pages + after_index + 1, (before_index - after_index) * sizeof(struct ordered_page));
                    pages[before_index].page = after_page;
                    break;
                }
            }
            if (page == after_page) {
                if (before_index != -1)
                    break;
                after_index = pp;
            }
            if (!page) {
                if (after_index != -1) {
                    memmove(pages + after_index + 1, pages + after_index, (pp - after_index) * sizeof(struct ordered_page));
                    pages[after_index].page = before_page;
                }
                else if (before_index == -1) {
                    pages[pp].page = before_page;
                    pages[pp + 1].page = after_page;
                }
                else
                    pages[pp].page = after_page;
                break;
            }
        }
        current_line = next_line + 1;
    }
    current_line = str;
    while (current_line && *current_line != '\n' && *current_line != '\r')
    {
        char* next_line = strchr(current_line, '\n');
        long before_page = strtol(current_line, &current_line, page_base);
        long after_page = strtol(current_line + 1, &current_line, page_base);
        for (int pp = 0; 1; pp++) {
            long page = pages[pp].page;
            if (page == before_page && pages[pp + 1].page == after_page) {
                pages[pp + 1].related_to_previous = 1;
                break;
            }
            if (!page)
                break;
        }
        current_line = next_line + 1;
    }
    return current_line + 1;
}

int has_remaining_updates(const char* str) {
    return str && *str && *str != '\n' && *str != '\r';
}

long get_middle_page_total(char* updates, const struct ordered_page* page_order) {
    long middle_page_total = 0;
    char* current_line = updates;
    long pages[max_pages] = {0};
    while (has_remaining_updates(current_line))
    {
        for (int pp = 0; pages[pp]; pp++)
            pages[pp] = 0;
        int page_count = 0;
        while (has_remaining_updates(current_line)) {
            if (*current_line == ',')
                current_line++;
            long page = strtol(current_line, &current_line, page_base);
            pages[page_count] = page;
            page_count++;
        }
        int is_correct_order = 1;
        int order_index = 0;
        for (int pp = 0; pp < page_count; pp++) {
            long page = pages[pp];
            while (page_order[order_index].page && page != page_order[order_index].page)
                order_index++;
            while (order_index && page_order[order_index].page && !page_order[order_index].related_to_previous)
                order_index--;
            if (!page_order[order_index].page) {
                is_correct_order = 0;
                break;
            }
        }
        if (is_correct_order)
            middle_page_total += pages[page_count / 2];
        char* next_line = strchr(current_line, '\n');
        current_line = next_line ? (next_line + 1) : NULL;
    }
    return middle_page_total;
}