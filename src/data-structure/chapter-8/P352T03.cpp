#include <bits/stdc++.h>

typedef enum {
    RED,
    WHITE,
    BLUE
} Color;

void flag_arrange(Color a[], int n) {
    int bucket[3] = {0};
    for (int i = 0; i < n; ++i) {
        ++bucket[int(a[i])];
    }
    int pos = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < bucket[i]; ++j) {
            a[pos++] = Color(i);
        }
    }
}

void flag_arrange2(Color a[], int n) {
    int pos = 0, l = 0, r = n - 1;
    while (l <= r) {
        switch (a[l]) {
        case RED:
            std::swap(a[pos++], a[l]);
            ++l;
            break;
        case WHITE:
            ++l;
            break;
        case BLUE:
            std::swap(a[l], a[r]);
            --r;
            break;
        }
    }
}

int main() {
    Color a[] = {WHITE, BLUE, RED, BLUE, RED, WHITE, BLUE, RED, WHITE, RED};
    int n = sizeof(a) / sizeof(a[0]);

    // flag_arrange(a, n);
    flag_arrange2(a, n);

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}