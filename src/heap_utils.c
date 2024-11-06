#include "../inc/pathfinder.h"

t_min_heap_node* new_heap_node(int v, int dist) {
    t_min_heap_node* node = malloc(sizeof(t_min_heap_node));
    node->dist = dist;
    node->v = v;
    node->parent = -1;
    return node;
}
t_min_heap* create_min_heap(int capacity) {
    t_min_heap* min_heap = malloc(sizeof(t_min_heap));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->arr = malloc(capacity * (sizeof(t_min_heap_node*)));
    return min_heap;
}
void free_min_heap(t_min_heap* min_heap) {
    // for (int i = 0; i < min_heap->capacity; i++) {
    //     free(min_heap->arr[i]);
    // }
    free(min_heap->arr);
    free(min_heap);

}
void swap_nodes(t_min_heap_node* a, t_min_heap_node* b) {
    t_min_heap_node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(t_min_heap* min_heap, int ind) {
    int smallest = ind;
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    
    if (left < min_heap->size && min_heap->arr[left]->dist < min_heap->arr[smallest]->dist)
        smallest = left;
    
    if (right < min_heap->size && min_heap->arr[right]->dist < min_heap->arr[smallest]->dist)
        smallest = right;

    if (smallest != ind) {
        swap_nodes(min_heap->arr[smallest], min_heap->arr[right]);
        heapify(min_heap, smallest);
    }    
}
t_min_heap_node* extract_min_node(t_min_heap* min_heap) {
    if(min_heap->size != 0) {
        t_min_heap_node* root = min_heap->arr[0];
        t_min_heap_node* last_node = min_heap->arr[min_heap->size - 1];
        min_heap->arr[0] = last_node;
        min_heap->size--;
        heapify(min_heap, 0);
        return root;
    }
    return NULL;
}

void insert_min_node(t_min_heap* min_heap, t_min_heap_node* node) {
    min_heap->size++;
    int i = min_heap->size - 1;
    min_heap->arr[i] = node;

    while(i && min_heap->arr[i]->dist < min_heap->arr[(i - 1)/2]->dist) {
        swap_nodes(min_heap->arr[i],min_heap->arr[(i-1)/2]);
        i = (i - 1) / 2;
    }
}
