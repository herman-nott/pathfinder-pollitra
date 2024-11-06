#include "../inc/pathfinder.h"

t_island* new_adj_node(const char *name , int weight) {
    t_island *new_node = malloc(sizeof(t_island));
    new_node->name = mx_strdup(name);
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

int mx_get_name_index(t_graph *graph,const char *name) {
    for (int i = 0; i < graph->v; i++) {
        if (graph->name_list[i] != NULL && mx_strcmp(graph->name_list[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int mx_atoi(const char* str) {
    if (!str) return 0;
    int n = 0;
    int sign = (*str == '-')? -1: 1;
    if (*str == '-' || *str == '+') str++;
    while(*str && *str >= '0' && *str <= '9') n = n * 10 + (*str++ - '0');
    return n * sign;
}
bool not_a_number(const char *str) {
    if (str == NULL || *str == '\0') return true;

    if (*str == '-' || (*str == '0' && mx_strlen(str) > 1)) {
        return true;
    }

    if (*str == '+') str++;

    while (*str) {
        if (*str < '0' || *str > '9') return true;
        str++;
    }
    return false;
}
