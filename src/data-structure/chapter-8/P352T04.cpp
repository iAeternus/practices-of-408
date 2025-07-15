#include <bits/stdc++.h>

int partition(int arr[], int l, int r) {
    int pivot = arr[l];
    while (l < r) {
        while (l < r && arr[r] >= pivot) --r;
        arr[l] = arr[r];
        while (l < r && arr[l] <= pivot) ++l;
        arr[r] = arr[l];
    }
    arr[l] = pivot;
    return l;
}

void quick_select(int arr[], int l, int r) {
    if (l >= r) return;
    int pivot_idx = partition(arr, l, r);
    int mid = (l + r) >> 1;
    if (pivot_idx < mid) {
        quick_select(arr, pivot_idx + 1, r);
    } else if (pivot_idx > mid) {
        quick_select(arr, l, pivot_idx - 1);
    }
}

// 法一
void quick_select(int arr[], int n) {
    quick_select(arr, 0, n - 1);
}

// 法二
void partition(int arr[], int n) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int pivot_idx = partition(arr, l, r);
        int mid = (l + r) >> 1;
        if (pivot_idx < mid) {
            l = pivot_idx + 1;
        } else if (pivot_idx > mid) {
            r = pivot_idx - 1;
        } else {
            return;
        }
    }
}
 
int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    // partition(arr, n);
    quick_select(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}