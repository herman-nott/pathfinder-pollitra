#include "pathfinder.h"

static bool mx_isdigit(int c)
{
    if (c >= 48 && c <= 57)
        return true;
    else
        return false;
}

void mx_printerr(const char* errortext) {
    write(2, errortext, mx_strlen(errortext));
}

void error_file_not_exist(const char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
    exit(-1);
}
void error_file_empty(const char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
}

void bridge_overload() {
    mx_printerr("error: sum of bridges lengths is too big\n");
    exit(-1);
}

void check_first_line(char* firstline) {
    if (not_a_number(firstline) == true || firstline[0] == '0') {
       mx_printerr("error: line 1 is not valid\n");
       exit(-1);
    }

    long long value = mx_atoi(firstline);

    if (value < 0 || value > INT_MAX) {
        mx_printerr("error: line 1 is not valid\n");
        exit(-1);
    }
}

void inv_number_arguments() {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(-1);
}

void islands_number() {
    mx_printerr("error: invalid number of islands\n");
    exit(-1);
}

void is_invalid_line(int idx) {
    mx_printerr("error: line "); 
    mx_printerr(mx_itoa(idx));
    mx_printerr(" is not valid\n");
    exit(-1);
}

void is_dup(const char *edge, char **edge_list, int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        if (mx_strcmp(edge, edge_list[i]) == 0) {
            mx_printerr("error: duplicate bridges\n");
            exit(-1);
        }
    }
}

void validate_line(const char *line, int line_num) {
    if (mx_isdigit(line[0])) {
        is_invalid_line(line_num);
    }

    int dash_index = mx_get_char_index(line, '-');
    if (dash_index < 1) {
        is_invalid_line(line_num);
    }
    
    int second_dash_index = mx_get_char_index(&line[dash_index + 1], '-') + dash_index + 1;
    if (second_dash_index > dash_index) {
        is_invalid_line(line_num);
    }

    int comma_index = mx_get_char_index(line, ',');
    if (comma_index <= dash_index + 1) {
        is_invalid_line(line_num);
    }

    const char *weight_str = &line[comma_index + 1];
    long long weight_ll = mx_atoi(weight_str);
    if (not_a_number(weight_str) || weight_str[0] == '-' || weight_str[0] == '0' || weight_ll < 0 || weight_ll > INT_MAX) {
        is_invalid_line(line_num);
    }

    char *island_from = mx_strndup(line, dash_index);
    char *island_to = mx_strndup(&line[dash_index + 1], comma_index - dash_index - 1);
    if (mx_strcmp(island_from, island_to) == 0) {
        mx_strdel(&island_from);
        mx_strdel(&island_to);
        is_invalid_line(line_num);
    }
    mx_strdel(&island_from);
    mx_strdel(&island_to);
}
