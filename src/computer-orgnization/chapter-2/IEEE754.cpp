#include <bits/stdc++.h>

using i32 = int;
using i64 = long long;
using f32 = float;
using f64 = double;

i64 display_bits(f64 x) {
    union {
        f64 f;
        i64 i;
    } u;
    u.f = x;
    return u.i;
}

i32 display_bits(f32 x) {
    union {
        f32 f;
        i32 i;
    } u;
    u.f = x;
    return u.i;
}

void print_bits(i64 x) {
    for (int i = sizeof(x) * 8 - 1; i >= 0; --i) {
        std::cout << ((x >> i) & 1);
    }
    std::cout << std::endl;
}

void print_hex(i64 x) {
    printf("%X\n", x);
}

void print_bits(i32 x) {
    for (int i = sizeof(x) * 8 - 1; i >= 0; --i) {
        std::cout << ((x >> i) & 1);
    }
    std::cout << std::endl;
}

void print_hex(i32 x) {
    printf("%X\n", x);
}

int main() {
    f64 x = -0.4376f;
    auto res = display_bits(x);
    print_bits(res);
    print_hex(res);

    f32 x2 = -0.4375f;
    auto res2 = display_bits(x2);
    print_bits(res2);
    print_hex(res2);

    f32 x3 = -126.0f;
    auto res3 = display_bits(x3);
    print_bits(res3);
    print_hex(res3);
}