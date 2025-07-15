#include <bits/stdc++.h>

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

/**
 * @brief 冒泡排序
 * @details 每趟排序都会将一个元素放置到其最终的位置上
 * @note 时间复杂度：最好情况 O(n) 最坏情况 O(n^2) 平均情况 O(n^2)
 * @note 空间复杂度：O(1)
 * @note 稳定性：稳定
 * @note 适用于顺序存储和链式存储的线性表
 */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = n - 1; j >= 1; --j) {
            if (arr[j - 1] > arr[j]) {
                swap(arr[j - 1], arr[j]);
                flag = true;
            }
        }
        // 若不发生交换，则已有序
        if (flag == false) {
            return;
        }
    }
}

/**
 * @details 划分数组
 * @return 返回枢轴位置
 */
int partition(int arr[], int l, int r) {
    int pivot = arr[l]; // 选用首元充当枢轴，也可选取随机位置
    while (l < r) {
        while (l < r && arr[r] >= pivot) --r;
        arr[l] = arr[r];
        while (l < r && arr[l] <= pivot) ++l;
        arr[r] = arr[l];
    }
    arr[l] = pivot;
    return l;
}

/**
 * @brief 获取枢轴位置，左右递归
 */
void quick_sort(int arr[], int l, int r) {
    if (l >= r) return;
    int pivot_idx = partition(arr, l, r);
    quick_sort(arr, l, pivot_idx - 1);
    quick_sort(arr, pivot_idx + 1, r);
}

/**
 * @brief 快速排序
 * @note 快排是所有排序算法中平均性能最优的算法
 * @note 时间复杂度：最好情况 O(n log n) 最坏情况 O(n^2) 平均情况 O(n log n)
 * @note 空间复杂度：最好情况 O(log n) 最坏情况 O(n) 平均情况 O(log n)
 * @note 稳定性：不稳定
 * @note 仅适用于顺序存储的线性表
 */
void quick_sort(int arr[], int n) {
    quick_sort(arr, 0, n - 1);
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    // bubble_sort(arr, n);
    quick_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}