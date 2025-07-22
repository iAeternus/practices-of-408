#include <bits/stdc++.h>

template <typename T>
using Vec = std::vector<T>;
template <typename T>
using Matrix = std::vector<std::vector<T>>;

Matrix<int> operator-(const Matrix<int>& m1, const Matrix<int>& m2) {
    int n = m1.size(), m = m1[0].size();
    Matrix res(n, Vec<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return res;
}

Vec<int> operator-(const Vec<int>& v1, const Vec<int>& v2) {
    int n = v1.size();
    Vec<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

Vec<int> operator+(const Vec<int>& v1, const Vec<int>& v2) {
    int n = v1.size();
    Vec<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

/**
 * @brief 银行家算法 Banker's algorithm
 * @param n 进程数
 * @param m 资源数
 * @param names 进程名称，n
 * @param available 可用资源向量，m
 * @param max 最大需求矩阵，n*m
 * @param allocation 分配矩阵，n*m
 * @return 若存在安全序列则返回安全序列，否则返回空字符串
 */
std::string banker_algorithm(int n, int m, Vec<std::string> names, Vec<int> available, Matrix<int> max, Matrix<int> allocation) {
    auto need = max - allocation;   // 需求矩阵 = 最大需求矩阵 - 分配矩阵
    Vec<bool> finish(n, false);     // 标记进程是否完成
    Vec<int> work = available;      // 工作向量初始化为可用资源
    std::string safe_sequence = ""; // 安全序列
    int count = 0;                  // 已完成的进程计数

    // 尝试分配资源直到所有进程完成或检测到死锁
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool can_allocate = false;
                // 检查当前进程需求是否小于等于可用资源
                if (need[i] <= work) {
                    can_allocate = true;
                }
                // 如果满足需求，分配资源
                if (can_allocate) {
                    // 释放进程占用的资源
                    work = work + allocation[i];
                    finish[i] = true;
                    safe_sequence += names[i];
                    if (count < n - 1) safe_sequence += " ";
                    count++;
                    found = true;
                    break; // 找到后重新开始扫描
                }
            }
        }
        // 未找到可执行进程，系统不安全
        if (!found) {
            return "";
        }
    }
    return safe_sequence;
}

int main() {
    int n = 5, m = 3;
    Vec<std::string> names = {"P0", "P1", "P2", "P3", "P4"};
    Vec<int> available = {3, 3, 2};
    Matrix<int> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3},
    };
    Matrix<int> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2},
    };

    std::string result = banker_algorithm(n, m, names, available, max, allocation);
    if (result.empty()) {
        std::cout << "No safe sequence found (deadlock detected)" << std::endl;
    } else {
        std::cout << "Safe sequence: " << result << std::endl;
    }
}