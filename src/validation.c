#include "pathfinder.h"

void generate_error_message(const char *line_num_str, char **message) {
    int length = 15 + mx_strlen(line_num_str) + 14;

    *message = malloc(length + 1);

    mx_strcpy(*message, "error: line ");
    mx_strcat(*message, line_num_str);
    mx_strcat(*message, " is not valid\n");
}

void handle_error(const char *message, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    if (message) {
        mx_printerr(message);
    }
    if (filestr) mx_strdel(&filestr);
    if (lines) mx_del_strarr(&lines);
    if (graph) clear_graph(&graph);
    if (temp_name_list) mx_del_strarr(&temp_name_list);
    if (edge_list) mx_del_strarr(&edge_list);
}

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

void bridge_overload(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list, char *island_to, char *island_from) {
    handle_error("error: sum of bridges lengths is too big\n", graph, lines, filestr, temp_name_list, edge_list);
    free(island_to);
    free(island_from);
    exit(-1);
}

void check_first_line(char* firstline, t_graph *graph, char **lines, char *filestr) {
    if (not_a_number(firstline) == true || firstline[0] == '0') {
        handle_error("error: line 1 is not valid\n", graph, lines, filestr, NULL, NULL);
        exit(-1);
    }

    long long value = mx_atoi(firstline);

    if (value < 0 || value > INT_MAX) {
        handle_error("error: line 1 is not valid\n", graph, lines, filestr, NULL, NULL);
        exit(-1);
    }
}

void inv_number_arguments() {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(-1);
}

void islands_number(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    handle_error("error: invalid number of islands\n", graph, lines, filestr, temp_name_list, edge_list);
    exit(-1);
}

void is_invalid_line(int idx) {
    char *line_str = mx_itoa(idx);
    mx_printerr("error: line "); 
    mx_printerr(line_str);
    mx_printerr(" is not valid\n");
    free(line_str);
    exit(-1);
}

int is_dup(char *edge, char **edge_list, int edge_count, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char *island_to, char *island_from) {
    for (int i = 0; i < edge_count; i++) {
        if (mx_strcmp(edge, edge_list[i]) == 0) {
            handle_error("error: duplicate bridges\n", graph, lines, filestr, temp_name_list, edge_list);
            free(island_to);
            free(island_from);
            return 1; 
        }
    }
    return 0;
}

void validate_line(const char *line, int line_num, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    char *line_num_str = mx_itoa(line_num);
    char *error_message = NULL;

    if (mx_isdigit(line[0])) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    int dash_index = mx_get_char_index(line, '-');
    if (dash_index < 1) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    int second_dash_index = mx_get_char_index(&line[dash_index + 1], '-') + dash_index + 1;
    if (second_dash_index > dash_index) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    int comma_index = mx_get_char_index(line, ',');
    if (comma_index <= dash_index + 1) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    const char *weight_str = &line[comma_index + 1];
    long long weight_ll = mx_atoi(weight_str);
    if (not_a_number(weight_str) || weight_str[0] == '-' || weight_str[0] == '0' || weight_ll < 0 || weight_ll > INT_MAX) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    char *island_from = mx_strndup(line, dash_index);
    char *island_to = mx_strndup(&line[dash_index + 1], comma_index - dash_index - 1);
    if (mx_strcmp(island_from, island_to) == 0) {
        mx_strdel(&island_from);
        mx_strdel(&island_to);
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
        free(line_num_str);
        free(error_message);
        exit(-1);
    }

    mx_strdel(&island_from);
    mx_strdel(&island_to);
    free(line_num_str);
    free(error_message);
}
