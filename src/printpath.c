#include "../inc/pathfinder.h"

void print_path_between(const char *src_name, const char *dest_name) {
    mx_printstr("Path: ");
    mx_printstr(src_name);
    mx_printstr(" -> ");
    mx_printstr(dest_name);
    mx_printstr("\n");
}

void print_distance(int *distances, int dest, int *parents) {
    int total_distance = 0;
    int segment_count = 0;
    int segments[dest];

    for (int i = dest; parents[i] != -1; i = parents[i]) {
        int parent = parents[i];
        segments[segment_count++] = distances[i] - distances[parent];
        total_distance += segments[segment_count - 1];
    }

    mx_printstr("Distance: ");

    if (segment_count == 1) {
        mx_printint(total_distance);
    } else {
        for (int i = segment_count - 1; i >= 0; i--) {
            mx_printint(segments[i]);
            if (i > 0) {
                mx_printstr(" + ");
            }
        }
        mx_printstr(" = ");
        mx_printint(total_distance);
    }
    mx_printstr("\n");
}

void print_route(int *parents, int dest, char **name_list) {
    if (parents[dest] == -1) {
        mx_printstr(name_list[dest]);
        return;
    }
    print_route(parents, parents[dest], name_list);
    mx_printstr(" -> ");
    mx_printstr(name_list[dest]);
}

void print_path(t_graph *graph, int *dist, int *parents, const char *src_name, char **name_list, bool **printed_paths) {
    for (int i = 0; i < graph->v; i++)
    {
        if (dist[i] == 0 || i == mx_get_name_index(graph, src_name)) {
            continue;
        }

        int src_idx = mx_get_name_index(graph, src_name);
        int dest_idx = i;

        if (printed_paths[src_idx][dest_idx] || printed_paths[dest_idx][src_idx]) {
            continue;
        }

        printed_paths[src_idx][dest_idx] = true;

        mx_printstr("========================================\n");
        print_path_between(src_name, name_list[i]);
        
        mx_printstr("Route: ");
        print_route(parents, i, name_list);
        mx_printchar('\n');

        print_distance(dist, i, parents);
        mx_printstr("========================================\n");
    }
    
}

