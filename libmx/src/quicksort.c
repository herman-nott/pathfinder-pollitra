#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL) return -1;

    int swaps = 0;

    if (left < right) {
        char *pivot = arr[(left + right) / 2];
        int l = left;
        int r = right;

        while (l <= r) {
            while (mx_strlen(arr[l]) < mx_strlen(pivot)) l++;
            while (mx_strlen(arr[r]) > mx_strlen(pivot)) r--;

            if (l <= r) {
                if (l != r && mx_strlen(arr[r]) != mx_strlen(arr[l])) {
                    mx_swap_str(&arr[l], &arr[r]);
	            swaps++;
                }
                l++;
                r--;
            }
        }
        swaps += mx_quicksort(arr, left, r);
        swaps += mx_quicksort(arr, l, right);
    }
    return swaps;
}
