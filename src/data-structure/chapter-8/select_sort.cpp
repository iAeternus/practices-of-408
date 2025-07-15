#include <bits/stdc++.h>

/**
 * @brief 选择排序
 * @note 时间复杂度：始终为 O(n^2)
 * @note 空间复杂度：O(1)
 * @note 稳定性：不稳定
 * @note 适用于顺序存储和链式存储的线性表，以及关键字较少的情况
 */
void select_sort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

/**
 * @brief 父节点
 */
int fa(int x) {
    return x >> 1;
}

/**
 * @brief 左孩子
 * @note 若下标从1开始，则左孩子下标为 2 * x
 */
int lch(int x) {
    return (x << 1) + 1;
}

/**
 * @brief 右孩子
 * @note 若下标从1开始，则右孩子下标为 2 * x + 1
 */
int rch(int x) {
    return (x << 1) + 2;
}

/**
 * @brief 调整以rt为根的子树，使之成为大根堆
 */
void heapify_down(int arr[], int n, int rt) {
    int max_idx = rt;
    while (true) {
        const int l = lch(rt), r = rch(rt);
        if (l < n && arr[l] > arr[max_idx]) max_idx = l;
        if (r < n && arr[r] > arr[max_idx]) max_idx = r;
        if (max_idx == rt) break;
        std::swap(arr[rt], arr[max_idx]);
        rt = max_idx;
    }
}

/**
 * @brief 建立大根堆
 */
void build_heap(int arr[], int n) {
    for (int i = (n >> 1) - 1; i >= 0; --i) {
        heapify_down(arr, n, i);
    }
}

/**
 * @brief 堆排序
 * @note 时间复杂度：始终为 O(n log n)
 * @note 空间复杂度：O(1)
 * @note 稳定性：不稳定
 * @note 仅适用于顺序存储的线性表
 */
void heap_sort(int arr[], int n) {
    build_heap(arr, n);
    for (int i = n - 1; i >= 1; --i) {
        std::swap(arr[0], arr[i]);
        heapify_down(arr, i, 0);
    }
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    // select_sort(arr, n);
    heap_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}