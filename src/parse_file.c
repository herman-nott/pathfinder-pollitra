#include "../inc/pathfinder.h"

bool is_in_list(const char *name, char **name_list, int size) {
    for (int i = 0; i < size; i++) {
        if (mx_strcmp(name_list[i], name) == 0) {
            return 1;
        }
    }
    return 0; 
}

static int strarr_len(char **str_arr)
{
    int len = 0;
    while (str_arr[len])
        len++;
        
    return len;
}

static void check_empty_line(char **str_arr, char *file) {
    int lines = mx_count_substr(file, "\n") + 1;
    int counter = 0;

    if (lines != strarr_len(str_arr)) {
        counter = 0;
        for (int i = 0; file[i]; i++) {
            if (file[i] == '\n') {
                counter++;
            }

            if (file[i - 1] == '\n' && file[i] == '\n') {
                mx_del_strarr(&str_arr);
                free(file);
                is_invalid_line(counter);
            }
        }
    }
}

t_graph* parse_file(const char *filename) {
    int fd =  open(filename, O_RDONLY);
    if (fd < 0) {
        error_file_not_exist(filename);
    }
    char *filestr =  mx_file_to_str(filename);

    if (mx_strlen(filestr) == 0) {
        error_file_empty(filename);
        mx_strdel(&filestr);
        exit(-1);
    }

    char **lines = mx_strsplit(filestr, '\n');

    check_empty_line(lines, filestr);

    check_first_line(lines[0]);
    int v = mx_atoi(lines[0]);
    int name_count = 0;
    long long sum_len = 0;
     
    char *island_from;
    char *island_to;
    int weight;
    int offset = 0;

    char **temp_name_list = malloc(v * 2 * sizeof(char*));
    char **edge_list = malloc(100 * sizeof(char*));
    int edge_count = 0;

    for (int i = 1; lines[i] != NULL; i++) {
        validate_line(lines[i], i + 1);

        island_from = mx_strndup(lines[i], mx_get_char_index(lines[i], '-'));
        if (!is_in_list(island_from, temp_name_list, name_count)) {
            temp_name_list[name_count++] = island_from;
        }

        offset = mx_get_char_index(lines[i], '-') + 1;
        island_to = mx_strndup(&lines[i][offset], mx_get_char_index(&lines[i][offset], ','));
        if (!is_in_list(island_to, temp_name_list, name_count)) {
            temp_name_list[name_count++] = island_to;
        }
    }

    if (name_count != v) {
        islands_number();
    }

    t_graph *graph = create_graph(v);
    graph->name_list = temp_name_list;

    for (int i = 1; lines[i] != NULL; i++) {
        island_from = mx_strndup(lines[i], mx_get_char_index(lines[i], '-'));
        offset = mx_get_char_index(lines[i], '-') + 1;
        island_to = mx_strndup(&lines[i][offset], mx_get_char_index(&lines[i][offset], ','));
        offset += mx_get_char_index(&lines[i][offset], ',') + 1;

        long long weight_ll = mx_atoi(&lines[i][offset]);
        if (weight_ll > INT_MAX) {
            bridge_overload();
        }
        weight = (int)weight_ll;

        if (sum_len + weight > INT_MAX) {
            bridge_overload();
        }
        sum_len += weight;

        char *edge_str = mx_strjoin(island_from, "-");
        char *temp = edge_str;
        edge_str = mx_strjoin(edge_str, island_to);
        free(temp);

        is_dup(edge_str, edge_list, edge_count);
        edge_list[edge_count++] = edge_str;

        create_edge(graph, island_from, island_to, weight);
    }

    mx_strdel(&filestr);
    mx_del_strarr(&lines);
    free(edge_list);
    close(fd);
    
    return graph;
}
