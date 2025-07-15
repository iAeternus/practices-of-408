#include <bits/stdc++.h>
#include <cstring>

/**
 * @brief 计数排序
 * @note 时间复杂度：O(n + k)
 * @note 空间复杂度：O(n + k)
 * @note 稳定性：稳定
 * @param k 数组元素最大值
 */
void count_sort(int arr[], int n, int k) {
    int* tmp = new int[n];
    int* cnt = new int[k]{0};
    for (int i = 0; i < n; ++i) {
        ++cnt[arr[i]];
    }
    for (int i = 1; i < k; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        tmp[--cnt[arr[i]]] = arr[i]; // cnt[arr[i]] - 1即为arr[i]的正确位置，因为下标从0开始且共有cnt[arr[i]]个元素小于或等于arr[i]
    }
    std::memcpy(arr, tmp, sizeof(int) * n);
    delete[] cnt;
    delete[] tmp;
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 100;

    count_sort(arr, n, k);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}