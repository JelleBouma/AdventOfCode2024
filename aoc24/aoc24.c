#include "aoc24.h"

#define inactive (-1)
#define or_str "OR"
#define xor_str "XOR"
#define and_str "AND"

typedef struct {
    char* input0;
    enum { AND, OR, XOR } operator;
    char* input1;
    char* output;
} LogicGate;

GHashTable* wire_dict;
GList* logic_gates = NULL;

void add_starting_values(char** starting_values) {
    while (*starting_values) {
        (*starting_values)[3] = '\0';
        gint64 value = strtoll(*starting_values + 5, NULL, decimal_base);
        g_hash_table_insert(wire_dict, *starting_values, (gpointer)value);
        starting_values++;
    }
}

void add_logic_gates(char** logic_gate_strs) {
    while (*logic_gate_strs) {
        LogicGate* gate = malloc(sizeof(LogicGate));
        (*logic_gate_strs)[3] = '\0';
        gate->input0 = *logic_gate_strs;
        if (starts_with(*logic_gate_strs + 4, or_str)) {
            gate->operator = OR;
            (*logic_gate_strs)[10] = '\0';
            gate->input1 = *logic_gate_strs + 7;
            gate->output = *logic_gate_strs + 14;
        }
        else {
            if (starts_with(*logic_gate_strs + 4, and_str))
                gate->operator = AND;
            else
                gate->operator = XOR;
            (*logic_gate_strs)[11] = '\0';
            gate->input1 = *logic_gate_strs + 8;
            gate->output = *logic_gate_strs + 15;
        }
        logic_gates = g_list_prepend(logic_gates, gate);
        if (!g_hash_table_contains(wire_dict, gate->input0))
            g_hash_table_insert(wire_dict, gate->input0, (gpointer)inactive);
        if (!g_hash_table_contains(wire_dict, gate->input1))
            g_hash_table_insert(wire_dict, gate->input1, (gpointer)inactive);
        if (!g_hash_table_contains(wire_dict, gate->output))
            g_hash_table_insert(wire_dict, gate->output, (gpointer)inactive);
        logic_gate_strs++;
    }
}

void build_dicts(char* input) {
    wire_dict = g_hash_table_new(g_str_hash, g_str_equal);
    char** split = split_on_empty_lines(input);
    char** starting_values = split_lines(split[0]);
    char** logic_gate_strs = split_lines(split[1]);
    add_starting_values(starting_values);
    add_logic_gates(logic_gate_strs);
}

void logic() {
    bool any_activated = true;
    while (any_activated) {
        any_activated = false;
        GList* logic_gate_iter = logic_gates;
        while (logic_gate_iter) {
            LogicGate* gate = logic_gate_iter->data;
            gint64 input0state = (gint64) g_hash_table_lookup(wire_dict, gate->input0);
            gint64 input1state = (gint64) g_hash_table_lookup(wire_dict, gate->input1);
            if (input0state != inactive && input1state != inactive) {
                any_activated = true;
                gint64 output;
                if (gate->operator == AND)
                    output = input0state & input1state;
                else if (gate->operator == XOR)
                    output = input0state ^ input1state;
                else
                    output = input0state | input1state;
                g_hash_table_insert(wire_dict, gate->output, (gpointer)output);
                GList* next = logic_gate_iter->next;
                logic_gates = g_list_remove_link(logic_gates, logic_gate_iter);
                logic_gate_iter = next;
            }
            else
                logic_gate_iter = logic_gate_iter->next;
        }
    }
}

gint64 get_output_from_z_wires() {
    gint64 res = 0;
    char wire[4] = {0};
    bool wire_exists = true;
    gint32 z_counter = 0;
    while (wire_exists) {
        g_snprintf(wire, 4, "z%02d", z_counter);
        wire_exists = g_hash_table_contains(wire_dict, wire);
        if (wire_exists)
            res += (gint64)g_hash_table_lookup(wire_dict, wire) << z_counter;
        z_counter++;
    }
    return res;
}

gint64 get_output(char* input) {
    build_dicts(input);
    logic();
    return get_output_from_z_wires();
}