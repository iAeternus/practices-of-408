#include <bits/stdc++.h>

/**
 * @brief 计算整数的相反数
 * @param x 一个整数
 * @return x的相反数
 * @example
 * assert(neg(-1) == 1);
 * assert(neg(1) == -1);
 * assert(neg(100) == -100);
 * assert(neg(-100) == 100);
 */
int neg(int x) {
    return ~x + 1;
}

/**
 * @brief 判断两个整数相加是否会溢出
 * @param a 
 * @param b 
 * @return true
 * @return false
 */
bool is_add_overflow(int a, int b) {
    return (a > 0 && b > 0 && a > INT_MAX - b) || (a < 0 && b < 0 && a < INT_MIN - b);
}

int main() {
    assert(neg(-1) == 1);
    assert(neg(1) == -1);
    assert(neg(100) == -100);
    assert(neg(-100) == 100);
}