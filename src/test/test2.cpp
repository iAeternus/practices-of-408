#include <bits/stdc++.h>

int main() {
    int n = 100, k = 7;
    int max_m = 1 << (k - 2);
    int max_lk = 0;
    for (int m = 1; m <= max_m; ++m) {
        int s = m;
        for (int i = 1; i <= k - 2; ++i) {
            s += ceil(1.0 * m / (1 << i));
        }
        int s_min = std::max(n - 2 * m, s);
        max_lk = std::max(max_lk, n - s_min);
    }
    std::cout << max_lk << std::endl;
}
