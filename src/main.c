#include "../inc/pathfinder.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        inv_number_arguments();
    }
    const char *filename = argv[1];
    t_graph* graph = parse_file(filename);
    char **islands_names = graph->name_list;
    pathfinder(graph, islands_names);
    clear_graph(&graph);
    return 0;
}
