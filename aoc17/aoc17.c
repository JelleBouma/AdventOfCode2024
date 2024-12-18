#include "aoc17.h"

#define adv_opcode 0
#define bxl_opcode 1
#define bst_opcode 2
#define jnz_opcode 3
#define bxc_opcode 4
#define out_opcode 5
#define bdv_opcode 6
#define cdv_opcode 7

gint64 register_a;
gint64 register_b;
gint64 register_c;
gint64 instruction_pointer = 0;
Int64List* output = NULL;

gint64 get_combo_operand(gint64 literal) {
    if (literal == 4)
        return register_a;
    if (literal == 5)
        return register_b;
    if (literal == 6)
        return register_c;
    return literal;
}

void adv(gint64 operand) {
    register_a /= (gint64)pow(2, (double)get_combo_operand(operand));
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
    int_list_prepend(&output, get_combo_operand(literal) % 8);
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

GHashTable* build_op_dict() {
    GHashTable* op_dict = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(op_dict, (gpointer)adv_opcode, adv);
    g_hash_table_insert(op_dict, (gpointer)bxl_opcode, bxl);
    g_hash_table_insert(op_dict, (gpointer)bst_opcode, bst);
    g_hash_table_insert(op_dict, (gpointer)jnz_opcode, jnz);
    g_hash_table_insert(op_dict, (gpointer)bxc_opcode, bxc);
    g_hash_table_insert(op_dict, (gpointer)out_opcode, out);
    g_hash_table_insert(op_dict, (gpointer)bdv_opcode, bdv);
    g_hash_table_insert(op_dict, (gpointer)cdv_opcode, cdv);
    return op_dict;
}

GString* get_program_output(char* input) {
    Int64List* ints = int_list_parse(input);
    register_a = int_list_take(&ints);
    register_b = int_list_take(&ints);
    register_c = int_list_take(&ints);
    GHashTable* op_dict = build_op_dict();
    Int64List* iter = ints;
    while (iter) {
        gint64 op_code = int_list_iter(&iter);
        gint64 literal = int_list_iter(&iter);
        void(*op)(gint64) = g_hash_table_lookup(op_dict, (gconstpointer)op_code);
        op(literal);
        if (op_code == jnz_opcode)
            iter = g_list_nth(ints, instruction_pointer);
    }
    output = g_list_reverse(output);
    GString* output_string = int_list_to_string(output);
    g_list_free(output);
    return output_string;
}