#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>

// 二分查找-迭代实现
int binary_search(const std::vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1); // (l + r) / 2
        if (nums[mid] < target) {
            l = mid + 1;
        } else if (nums[mid] > target) {
            r = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// 二分查找-递归实现 P277 T04
int binary_search_r(const std::vector<int>& nums, int l, int r, int target) {
    if(l > r) return -1;

    int mid = l + ((r - l) >> 1);
    if(nums[mid] < target) {
        return binary_search_r(nums, mid + 1, r, target);
    } else if(nums[mid] > target) {
        return binary_search_r(nums, l, mid - 1, target);
    } else {
        return mid;
    }
}

int binary_search_r(const std::vector<int>& nums, int target) {
    return binary_search_r(nums, 0, nums.size() - 1, target);
}

auto main() -> int {
    std::vector<int> nums = {7, 10, 13, 16, 19, 29, 32, 33, 37, 41, 43};

    assert(binary_search(nums, 11) == -1);
    assert(binary_search(nums, 32) == 6);

    assert(binary_search_r(nums, 11) == -1);
    assert(binary_search_r(nums, 32) == 6);
}