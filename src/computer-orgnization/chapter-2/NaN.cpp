#include <bits/stdc++.h>

int main() {
    printf("%f\n", 0.0f / 0.0f); // nan

    printf("%f\n", 1.0f / 0.0f);  // inf
    printf("%f\n", -1.0f / 0.0f); // -inf
}