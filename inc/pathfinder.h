#pragma once

#include "../libmx/inc/libmx.h"
#include <limits.h>

typedef struct s_island t_island;
typedef struct s_graph t_graph;
typedef struct s_min_heap t_min_heap;
typedef struct s_min_heap_node t_min_heap_node;
typedef struct s_adj_list t_adj_list;
typedef struct s_parent_list t_parent_list;

struct s_island {
    char *name;
    int weight;
    t_island *next;
};

struct s_adj_list {
    t_island *head;
};

struct s_graph {
    int v;
    t_adj_list *list;
    char **name_list;// new
};

struct s_min_heap{
    int size;
    int capacity;
    t_min_heap_node** arr;
};

struct s_min_heap_node {
    int v;
    int dist;
    int parent;
};

struct s_parent_list {
    int parent;
    struct s_parent_list *next;
};

//validation
void error_file_not_exist(const char *filename);
void error_file_empty(const char *filename);
void bridge_overload(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list, char *island_to, char *island_from);
void check_first_line(char* firstline, t_graph *graph, char **lines, char *filestr);
void inv_number_arguments();
void islands_number(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list);
void is_invalid_line(int idx);
int is_dup(char *edge, char **edge_list, int edge_count, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char *island_to, char *island_from);
void validate_line(const char *line, int line_num, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list);

//printing
void print_path_between( const char *src_name, const char *dest_name);
void print_distance_and_route(int *distances, int *path, int path_len, char **name_list);
void print_path(t_graph *graph, int *dist, t_parent_list **parents, const char *src_name, char **name_list, bool **printed_paths);

//algorithm
void pathfinder(t_graph *graph, char **islands_names);
void dijkstra(t_graph* graph, int src_idx, const char *src_name, char **name_list, bool **printed_paths);

//min_heap
t_min_heap_node* new_heap_node(int v, int dist);
t_min_heap* create_min_heap(int capacity);
void free_min_heap(t_min_heap* min_heap);
void swap_nodes(t_min_heap_node* a, t_min_heap_node* b);
void heapify(t_min_heap* min_heap, int ind);
t_min_heap_node* extract_min_node(t_min_heap* min_heap);
void insert_min_node(t_min_heap* min_heap, t_min_heap_node* node);
t_island* new_adj_node(const char *name , int weight);

//parse file
bool is_in_list(const char *name, char **name_list, int size);
t_graph* parse_file(const char *filename);

//graph
t_graph* create_graph(int v);
void create_edge(t_graph *graph, const char *island_from, const char *island_to, int weight);
int mx_get_name_index(t_graph *graph,const char *name);
void clear_islands(t_adj_list* list);
void clear_graph(t_graph** graph);

//added basics 
int mx_atoi(const char* str);
void mx_printerr(const char *errortext);
bool not_a_number(const char *str);
