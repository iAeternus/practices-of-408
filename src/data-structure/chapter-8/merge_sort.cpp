#include <bits/stdc++.h>

void merge(int arr[], int low, int mid, int high) {
    int* b = new int[high - low + 1];
    int i = low, j = mid + 1, pos = 0;
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            b[pos++] = arr[i++];
        } else {
            b[pos++] = arr[j++];
        }
    }
    while (i <= mid) {
        b[pos++] = arr[i++];
    }
    while (j <= high) {
        b[pos++] = arr[j++];
    }
    std::memcpy(arr + low, b, sizeof(int) * (high - low + 1));
    delete[] b;
}

void merge_sort(int arr[], int l, int r) {
    if (l >= r) return;
    int mid = l + ((r - l) >> 1);
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

/**
 * @brief 归并排序
 * @note 时间复杂度：O(n log n)
 * @note 空间复杂度：O(n)
 * @note 稳定性：稳定
 * @note 适用于顺序存储和链式存储的线性表
 */
void merge_sort(int arr[], int n) {
    merge_sort(arr, 0, n - 1);
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}