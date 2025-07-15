#include <bits/stdc++.h>

void odd_even_sort(int arr[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        while (l < r && arr[l] & 1) ++l;
        while (l < r && !(arr[r] & 1)) --r;
        std::swap(arr[l], arr[r]);
        ++l;
        --r;
    }
}

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    odd_even_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}