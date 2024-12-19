#include "aoc17.h"

#define adv_opcode 0
#define bxl_opcode 1
#define bst_opcode 2
#define jnz_opcode 3
#define bxc_opcode 4
#define out_opcode 5
#define bdv_opcode 6
#define cdv_opcode 7

GHashTable* op_dict;
__int128 register_a_initial;
__int128 register_b_initial;
__int128 register_c_initial;
__int128 register_a;
__int128 register_b;
__int128 register_c;
gint64 instruction_pointer = 0;
Int64List* program;
Int64List* output = NULL;
Int64List* wanted_output = NULL;

__int128 get_combo_operand(gint64 literal) {
    if (literal == 4)
        return register_a;
    if (literal == 5)
        return register_b;
    if (literal == 6)
        return register_c;
    return literal;
}

void adv(gint64 operand) {
    register_a >>= get_combo_operand(operand);
    instruction_pointer += 2;
}

void bxl(gint64 literal) {
    register_b ^= literal;
    instruction_pointer += 2;
}

void bst(gint64 literal) {
    register_b = get_combo_operand(literal) % 8;
    instruction_pointer += 2;
}

void jnz(gint64 literal) {
    if (register_a)
        instruction_pointer = literal;
    else
        instruction_pointer += 2;
}

void bxc(gint64 literal) {
    register_b ^= register_c;
    instruction_pointer += 2;
}

void out(gint64 literal) {
    int_list_prepend(&output, (gint64)(get_combo_operand(literal) % 8));
    instruction_pointer += 2;
}

void bdv(gint64 operand) {
    register_b = register_a / (gint64)pow(2, (double)get_combo_operand(operand));
    instruction_pointer += 2;
}

void cdv(gint64 operand) {
    register_c = register_a / (gint64)pow(2, (double)get_combo_operand(operand));
    instruction_pointer += 2;
}

void build_op_dict() {
    op_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(op_dict, (gpointer)adv_opcode, adv);
    g_hash_table_insert(op_dict, (gpointer)bxl_opcode, bxl);
    g_hash_table_insert(op_dict, (gpointer)bst_opcode, bst);
    g_hash_table_insert(op_dict, (gpointer)jnz_opcode, jnz);
    g_hash_table_insert(op_dict, (gpointer)bxc_opcode, bxc);
    g_hash_table_insert(op_dict, (gpointer)out_opcode, out);
    g_hash_table_insert(op_dict, (gpointer)bdv_opcode, bdv);
    g_hash_table_insert(op_dict, (gpointer)cdv_opcode, cdv);
}

void program_setup(char* input) {
    Int64List* ints = int_list_parse(input);
    register_a = int_list_take(&ints);
    register_b = int_list_take(&ints);
    register_c = int_list_take(&ints);
    register_a_initial = register_a;
    register_b_initial = register_b;
    register_c_initial = register_c;
    program = ints;
    build_op_dict();
}

void run_program() {
    Int64List* iter = program;
    Int64List* wanted_output_iter = wanted_output;
    while (iter) {
        gint64 op_code = int_list_iter(&iter);
        gint64 literal = int_list_iter(&iter);
        void(*op)(gint64) = g_hash_table_lookup(op_dict, (gconstpointer)op_code);
        op(literal);
        if (op_code == out_opcode && wanted_output_iter) {
            if (int_list_get(output) != int_list_get(wanted_output_iter))
                break;
            wanted_output_iter = wanted_output_iter->next;
        }
        if (op_code == jnz_opcode)
            iter = g_list_nth(program, instruction_pointer);
    }
    output = g_list_reverse(output);
}

void reset_program() {
    register_a = register_a_initial;
    register_b = register_b_initial;
    register_c = register_c_initial;
    instruction_pointer = 0;
    g_list_free(output);
    output = NULL;
}

GString* get_program_output(char* input) {
    program_setup(input);
    run_program();
    GString* output_string = int_list_to_string(output);
    g_list_free(output);
    output = NULL;
    return output_string;
}

gint64 get_corrected_register_a(char* input) {
    program_setup(input);
    wanted_output = program;
    gint64 corrected_register_a = 0;
    gint64 needed_correct_numbers = g_list_length(wanted_output);
    gint64 highest_correct_numbers = 0;
    gint64 bit_shifts = 0;
    gint64 limit = (1 << 21) - 1;
    while (highest_correct_numbers != needed_correct_numbers) {
        highest_correct_numbers = 0;
        gint64 best_bits = 0;
        for (gint64 bb = 0; bb <= limit; bb++) {
            reset_program();
            register_a = corrected_register_a;
            register_a ^= bb << (3 * bit_shifts);
            run_program();
            Int64List* output_iter = output;
            Int64List* wanted_output_iter = wanted_output;
            gint64 correct_numbers = 0;
            while (output_iter && int_list_get(output_iter) == int_list_get(wanted_output_iter)) {
                correct_numbers++;
                if (correct_numbers > highest_correct_numbers) {
                    highest_correct_numbers = correct_numbers;
                    best_bits = bb;
                }
                output_iter = output_iter->next;
                wanted_output_iter = wanted_output_iter->next;
            }
            if (highest_correct_numbers == needed_correct_numbers)
                break;
        }
        if (highest_correct_numbers == needed_correct_numbers)
            corrected_register_a |= best_bits << (3 * bit_shifts);
        else
            corrected_register_a |= (best_bits & 0b111) << (3 * bit_shifts);
        bit_shifts++;
    }
    return corrected_register_a;
}