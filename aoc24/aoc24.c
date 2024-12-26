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
            gint64 input0_state = (gint64) g_hash_table_lookup(wire_dict, gate->input0);
            gint64 input1_state = (gint64) g_hash_table_lookup(wire_dict, gate->input1);
            gint64 output_state = (gint64) g_hash_table_lookup(wire_dict, gate->output);
            if (input0_state != inactive && input1_state != inactive && output_state == inactive) {
                any_activated = true;
                gint64 output;
                if (gate->operator == AND)
                    output = input0_state & input1_state;
                else if (gate->operator == XOR)
                    output = input0_state ^ input1_state;
                else
                    output = input0_state | input1_state;
                g_hash_table_insert(wire_dict, gate->output, (gpointer)output);
            }
            logic_gate_iter = logic_gate_iter->next;
        }
    }
}

gint64 get_from_wires(char wire_prefix) {
    gint64 res = 0;
    char wire[4] = {0};
    bool wire_exists = true;
    gint32 z_counter = 0;
    while (wire_exists) {
        g_snprintf(wire, 4, "%c%02d", wire_prefix, z_counter);
        wire_exists = g_hash_table_contains(wire_dict, wire);
        if (wire_exists)
            res += (gint64)g_hash_table_lookup(wire_dict, wire) << z_counter;
        z_counter++;
    }
    return res;
}

void setup(char* input) {
    build_dicts(input);
}

gint64 get_output() {
    logic();
    return get_from_wires('z');
}

LogicGate* find_filtered_gate(char* input, gint32 operator) {
    GList* gate_iter = logic_gates;
    while (gate_iter) {
        LogicGate* gate = gate_iter->data;
        if ((g_str_equal(input, gate->input0) || g_str_equal(input, gate->input1)) && gate->operator == operator)
            return gate;
        gate_iter = gate_iter->next;
    }
    return NULL;
}

bool is_valid(LogicGate* gate) {
    bool input0_is_direct = *gate->input0 == 'x' || *gate->input0 == 'y';
    bool input1_is_direct = *gate->input1 == 'x' || *gate->input1 == 'y';
    bool output_is_direct = *gate->output == 'z';
    if (gate->operator == XOR) {
        if (!input0_is_direct && !input1_is_direct && !output_is_direct)
            return false;
        if (input0_is_direct && input1_is_direct && !g_str_equal(gate->output, "z00"))
            return find_filtered_gate(gate->output, XOR);
    }
    else if (gate->operator == OR) {
        if (output_is_direct && !g_str_equal(gate->output, "z45"))
            return false;
    }
    else {
        if (output_is_direct)
            return false;
        if (!g_str_equal(gate->input0, "x00") && !g_str_equal(gate->input1, "x00") && !g_str_equal(gate->input0, "y00") && !g_str_equal(gate->input1, "y00"))
            return find_filtered_gate(gate->output, OR);
    }
    return true;
}

char* get_crossed_wires() {
    GList* invalid_outputs = NULL;
    GList* logic_gate_iter = logic_gates;
    while (logic_gate_iter) {
        LogicGate* gate = logic_gate_iter->data;
        if (!is_valid(gate))
            invalid_outputs = g_list_prepend(invalid_outputs, gate->output);
        logic_gate_iter = logic_gate_iter->next;
    }
    invalid_outputs = g_list_sort(invalid_outputs, cmp_alphabetically);
    GString* res = g_string_new("");
    while (invalid_outputs) {
        g_string_append(res, invalid_outputs->data);
        if (invalid_outputs->next)
            g_string_append_c(res, ',');
        invalid_outputs = invalid_outputs->next;
    }
    return res->str;
}