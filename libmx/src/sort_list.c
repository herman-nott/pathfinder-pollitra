#include "libmx.h"

static void swap(void **node1, void **node2) {
    void *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
     if (lst == NULL || lst->next == NULL)
        return lst;

    t_list *current;
    t_list *last = NULL;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        current = lst;
        while (current->next != last) {
            if (cmp(current->data, current->next->data)) {
                swap(&current->data, &current->next->data);
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    }
    return lst;
}
