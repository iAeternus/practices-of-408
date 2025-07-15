#include <bits/stdc++.h>

int partition(int arr[], int l, int r) {
    int pivot = arr[l];
    while(l < r) {
        while(l < r && arr[r] >= pivot) --r;
        arr[l] = arr[r];
        while(l < r && arr[l] <= pivot) ++l;
        arr[r] = arr[l];
    }
    arr[l] = pivot;
    return l;
}

int quick_select(int arr[], int l, int r, int k) {
    if (l >= r) return arr[l];
    int pivot_idx = partition(arr, l, r);
    if (pivot_idx < k) {
        return quick_select(arr, pivot_idx + 1, r, k);
    } else if (pivot_idx > k) {
        return quick_select(arr, l, pivot_idx - 1, k);
    } else {
        return arr[pivot_idx];
    }
}

int quick_select(int arr[], int n, int k) {
    return quick_select(arr, 0, n - 1, k);
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
   
    assert(49 == quick_select(arr, n, k));
}