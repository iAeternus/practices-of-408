#include <bits/stdc++.h>

/**
 * @brief 直接插入排序
 * @note 时间复杂度：最好情况 O(n) 最坏情况 O(n^2) 平均情况 O(n^2)
 * @note 空间复杂度：O(1)
 * @note 稳定性：稳定
 * @note 适用于顺序存储和链式存储的线性表，采用链式存储时无需移动元素
 */
void insert_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/**
 * @brief 折半插入排序
 * @note 时间复杂度：最好情况 O(n log n) 最坏情况 O(n^2) 平均情况 O(n^2)
 * @note 空间复杂度：O(1)
 * @note 稳定性：稳定
 * @note 仅适用于顺序存储的线性表
 */
void binary_insert_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;

        // 二分查找插入位置
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // 移动元素
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

/**
 * @brief 希尔排序
 * @note 时间复杂度：最好情况 O(n) 最坏情况 O(n^2) 平均情况 O(n^{1.3})
 * @note 空间复杂度：O(1)
 * @note 稳定性：不稳定
 * @note 适用于顺序存储的线性表
 */
void shell_sort(int arr[], int n) {
    int gap = n >> 1;
    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            int key = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > key) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = key;
        }
        gap >>= 1;
    }
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    // insert_sort(arr, n);
    // binary_insert_sort(arr, n);
    shell_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}