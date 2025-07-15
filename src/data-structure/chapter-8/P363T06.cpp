#include <bits/stdc++.h>
#include <cassert>

int fa(int x) {
    return x >> 1;
}

int lch(int x) {
    return (x << 1) + 1;
}

int rch(int x) {
    return (x << 1) + 2;
}

bool is_heap(int arr[], int n) {
    for(int i = (n >> 1) - 1; i >= 0; --i) {
        if(arr[i] > arr[lch(i)] || arr[i] > arr[rch(i)]) {
            return false;
        }
    }
    return true;
}

int main() {
    int a1[] = {1, 2, 3, 4, 5, 6, 7};
    assert(is_heap(a1, 7));

    int a2[] = {9, 8, 7, 1, 6, 4, 5};
    assert(!is_heap(a2, 7));

    int a3[] = {1};
    assert(is_heap(a3, 1));

    int a4[] = {1, 3, 2, 4, 5, 6};
    assert(is_heap(a4, 6));
}