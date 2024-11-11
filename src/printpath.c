#include "../inc/pathfinder.h"

void print_path_between(const char *src_name, const char *dest_name) {
    mx_printstr("Path: ");
    mx_printstr(src_name);
    mx_printstr(" -> ");
    mx_printstr(dest_name);
    mx_printstr("\n");
}

void print_distance_and_route(int *distances, int *path, int path_len, char **name_list) {
    int total_distance = 0;

    mx_printstr("Route: ");
    for (int i = path_len - 1; i >= 0; i--) {
        mx_printstr(name_list[path[i]]);
        if (i > 0) mx_printstr(" -> ");
    }
    mx_printstr("\n");

    mx_printstr("Distance: ");
    if (path_len == 2) {
        total_distance = distances[path[0]] - distances[path[1]];
        mx_printint(total_distance);
    } else {
        for (int i = path_len - 1; i > 0; i--) {
            int segment_distance = distances[path[i - 1]] - distances[path[i]];
            mx_printint(segment_distance);
            total_distance += segment_distance;
            if (i > 1) {
                mx_printstr(" + ");
            }
        }
        mx_printstr(" = ");
        mx_printint(total_distance);
    }
    mx_printstr("\n");
}

void print_all_paths(t_graph *graph, int src, int dest, t_parent_list **parents, char **name_list, int *path, int path_index, int *distances) {
    path[path_index] = dest;
    path_index++;

    if (dest == src) {
        mx_printstr("========================================\n");
        print_path_between(name_list[src], name_list[path[0]]);
        print_distance_and_route(distances, path, path_index, name_list);
        mx_printstr("========================================\n");
        return;
    }

    for (t_parent_list *p = parents[dest]; p != NULL; p = p->next) {
        print_all_paths(graph, src, p->parent, parents, name_list, path, path_index, distances);
    }
}

void print_path(t_graph *graph, int *dist, t_parent_list **parents, const char *src_name, char **name_list, bool **printed_paths) {
    int src_idx = mx_get_name_index(graph, src_name);
    int *path = malloc(graph->v * sizeof(int));

    for (int i = 0; i < graph->v; i++) {
        if (dist[i] == 0 || i == src_idx) {
            continue;
        }

        int dest_idx = i;
        if (printed_paths[src_idx][dest_idx] || printed_paths[dest_idx][src_idx]) {
            continue;
        }

        printed_paths[src_idx][dest_idx] = true;

        print_all_paths(graph, src_idx, i, parents, name_list, path, 0, dist);
    }

    free(path);
}
