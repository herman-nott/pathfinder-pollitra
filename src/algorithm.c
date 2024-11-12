#include "../inc/pathfinder.h"

static bool **initialize_printed_paths(int num_vertices) {
    bool **printed_paths = malloc(num_vertices * sizeof(bool *));
    for (int i = 0; i < num_vertices; i++) {
        printed_paths[i] = calloc(num_vertices, sizeof(bool));
    }
    return printed_paths;
}

static void free_printed_paths(bool **printed_paths, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        free(printed_paths[i]);
    }
    free(printed_paths);
}

t_parent_list **initialize_parents(int num_vertices) {
    t_parent_list **parents = malloc(num_vertices * sizeof(t_parent_list *));
    for (int i = 0; i < num_vertices; i++) {
        parents[i] = NULL;
    }
    return parents;
}

void add_parent(t_parent_list **parents, int vertex, int parent) {
    t_parent_list *new_node = malloc(sizeof(t_parent_list));
    new_node->parent = parent;
    new_node->next = parents[vertex];
    parents[vertex] = new_node;
}

// void add_parent(t_parent_list **parents, int vertex, int parent) {
//     t_parent_list *new_node = malloc(sizeof(t_parent_list));
//     new_node->parent = parent;
//     new_node->next = NULL;

//     if (parents[vertex] == NULL) {
//         parents[vertex] = new_node;
//     } else {
//         t_parent_list *current = parents[vertex];
//         while (current->next != NULL) {
//             current = current->next;
//         }
//         current->next = new_node;
//     }
// }

void free_parents(t_parent_list **parents, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        t_parent_list *current = parents[i];
        while (current) {
            t_parent_list *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(parents);
}

void pathfinder(t_graph *graph, char **name_list) {
    int num_vertices = graph->v;
    
    bool **printed_paths = initialize_printed_paths(num_vertices);

    for (int i = 0; i < graph->v; i++)
    {
        dijkstra(graph, i, name_list[i], name_list, printed_paths);
    }

    free_printed_paths(printed_paths, num_vertices);
}

void dijkstra(t_graph* graph, int src_idx, const char *src_name, char **name_list, bool **printed_paths) {
    int v = graph->v;
    int *dist = malloc(v * sizeof(int));
    t_parent_list **parents = initialize_parents(v);
    t_min_heap* min_heap = create_min_heap(v);

    if (!dist || !parents) {
        free(dist);
        free_parents(parents, v);
        return;
    }

    for (int i = 0; i < v; i++) {
        dist[i] = INT_MAX;
    }

    dist[src_idx] = 0;
    insert_min_node(min_heap, new_heap_node(src_idx, 0));
    
    while (min_heap->size > 0) {
        t_min_heap_node* min_node = extract_min_node(min_heap);
        int u = min_node->v;

        if (min_node->dist > dist[u]) {
            free(min_node);
            continue;
        }
    
        t_island* adj = graph->list[u].head;
        while (adj != NULL) {
            int v = mx_get_name_index(graph, adj->name);
            int weight = adj->weight;
            
            if (dist[u] != INT_MAX && weight + dist[u] < dist[v]) {
                dist[v] = weight + dist[u];
                
                t_parent_list *temp;
                while ((temp = parents[v]) != NULL) {
                    parents[v] = temp->next;
                    free(temp);
                }
                add_parent(parents, v, u);
                
                insert_min_node(min_heap, new_heap_node(v, dist[v]));
            } else if (dist[u] != INT_MAX && weight + dist[u] == dist[v]) {
                add_parent(parents, v, u);
            }
            adj = adj->next; 
        }
        free(min_node);
    }
    
    print_path(graph, dist, parents, src_name, name_list, printed_paths);
    
    free(dist);
    free_parents(parents, v);
    free_min_heap(min_heap);
}
