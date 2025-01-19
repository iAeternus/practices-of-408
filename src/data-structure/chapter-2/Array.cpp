// 线性表的顺序表示
#include <bits/stdc++.h>

#define INIT_SIZE 100
using value_t = int;

struct Array {
    int length;
    int capacity;
    value_t* data;

    Array() :
            length(0), capacity(INIT_SIZE), data(new value_t[capacity]) {}

    Array(std::initializer_list<value_t>&& initList) :
            length(initList.size()), capacity(INIT_SIZE), data(new value_t[capacity]) {
        int pos = 0;
        for (auto&& item : initList) {
            data[pos++] = item;
        }
    }

    Array(const Array& other) :
            length(other.length), capacity(other.capacity), data(new value_t[capacity]) {
        for (int i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }

    Array(Array&& other) noexcept :
            length(other.length), capacity(other.capacity), data(other.data) {
        other.length = other.capacity = 0;
        other.data = nullptr;
    }

    ~Array() {
        length = capacity = 0;
        delete[] data;
        data = nullptr;
    }

    value_t* begin() {
        return data;
    }

    const value_t* const begin() const {
        return data;
    }

    value_t* end() {
        return data + length;
    }

    const value_t* const end() const {
        return data + length;
    }

    bool isEmpty() const {
        return length == 0;
    }

    /**
     * 最好 O(1)
     * 最坏 O(n)
     * 平均 O(n)
     */
    bool insert(int idx, value_t x) {
        if (idx < 0 || idx > length || length >= capacity) {
            return false;
        }
        for (int i = length; i > idx; --i) {
            data[i] = data[i - 1];
        }
        data[idx] = x;
        length++;
        return true;
    }

    bool push_back(value_t x) {
        return insert(length, x);
    }

    /**
     * 最好 O(1)
     * 最坏 O(n)
     * 平均 O(n)
     */
    bool remove(int idx, value_t& x) {
        if (idx < 0 || idx >= length) {
            return false;
        }
        x = data[idx];
        for (int i = idx; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        length--;
        return true;
    }

    /**
     * 最好 O(1)
     * 最坏 O(n)
     * 平均 O(n)
     */
    int find(value_t target) const {
        for (int i = 0; i < length; ++i) {
            if (data[i] == target) {
                return i;
            }
        }
        return -1;
    }

    void print() const {
        for (int i = 0; i < length; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    void print(int begin, int end) const {
        for (int i = begin; i < end; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    //////////////////////////////////// PAGE 19 20 ////////////////////////////////////

    /**
     * @see P19 T01
     */
    int removeMin() {
        if (length == 0) {
            std::runtime_error("");
        }

        int minIdx = 0, min = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] < min) {
                min = data[i];
                minIdx = i;
            }
        }
        data[minIdx] = data[length - 1];
        return min;
    }

    /**
     * @see P19 T02
     */
    static void reverse(value_t* begin, value_t* end) {
        value_t* mid = begin + ((end - begin) >> 1);
        for (value_t* idx = begin; idx < mid; ++idx) {
            std::swap(*idx, *(end - (idx - begin) - 1));
        }
    }

    /** 
     * @see P19 T03
     */
    int removeAll(int x) {
        int i = 0;
        for (int j = 0; j < length; ++j) {
            if (data[j] != x) {
                data[i++] = data[j];
            }
        }
        return i;
    }

    /**
     * @see P19 T04
     */
    int removeBetween(int s, int t) {
        if (s >= t || isEmpty()) {
            return -1;
        }

        int i = 0;
        for (int j = 0; j < length; ++j) {
            if (data[j] < s || data[j] > t) {
                data[i++] = data[j];
            }
        }
        return i;
    }

    /**
     * @brief 需要有序表
     * @see P19 T05
     */
    int distinct() {
        if (isEmpty()) {
            return -1;
        }

        int i = 0;
        for (int j = 1; j < length; ++j) {
            if (data[i] != data[j]) {
                data[++i] = data[j];
            }
        }
        return i + 1;
    }

    /**
     * @see P19 T06
     */
    Array merge(const Array& other) const {
        if (isEmpty() || other.isEmpty()) {
            return Array{};
        }

        int i = 0, j = 0;
        Array ans;
        int minLen = std::min(length, other.length);
        while (i < minLen && j < minLen) {
            if (data[i] < other.data[j]) {
                ans.push_back(data[i++]);
            } else if (data[i] > other.data[j]) {
                ans.push_back(other.data[j++]);
            } else {
                ans.push_back(data[i++]);
                ans.push_back(other.data[j++]);
            }
        }
        while (i < length) {
            ans.push_back(data[i++]);
        }
        while (j < other.length) {
            ans.push_back(other.data[j++]);
        }
        return ans;
    }

    /**
     * @see 19-07
     */
    void reverse(int k) {
        reverse(begin(), begin() + k);
        reverse(begin() + k, end());
        reverse(begin(), end());
    }

    /**
     * @brief 需要有序表
     * @see P19 T08
     */
    int search(value_t x) {
        int l = 0, r = length - 1;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            if (data[mid] < x) {
                l = mid + 1;
            } else if (data[mid] > x) {
                r = mid - 1;
            } else {
                if (mid < length) {
                    std::swap(data[mid], data[mid + 1]);
                }
                return mid;
            }
        }
        insert(r, x);
        return -1;
    }

    /**
     * @see P19 T09
     * 使用3个指针分别遍历数组，每次自增指向三者最小值的指针，若相等则打印并自增三个指针
     * 
     * 时间复杂度 O(min(n, m, k)) n, m, k 分别为三个数组的长度
     * 空间复杂度 O(1)
     */
    static void printSame(const Array& a, const Array& b, const Array& c) {
        int minLength = std::min(std::min(a.length, b.length), c.length);
        int i = 0, j = 0, k = 0;
        while (i < minLength && j < minLength && k < minLength) {
            if (a.data[i] < b.data[j] && a.data[i] < c.data[k]) {
                ++i;
            } else if (b.data[j] < a.data[i] && b.data[j] < c.data[k]) {
                ++j;
            } else if (c.data[k] < a.data[i] && c.data[k] < b.data[j]) {
                ++k;
            } else {
                std::cout << a.data[i] << std::endl;
                ++i, ++j, ++k;
            }
        }
    }

    /**
     * @see P19 T10
     * 依次反转arr[0...p], arr[p...n], arr[0...n]，注意是左开右闭区间
     * 
     * 时间复杂度 O(n)
     * 空间复杂度 O(1)
     */
    void cyclicLeftShift(int p) {
        reverse(begin(), begin() + p);
        reverse(begin() + p, end());
        reverse(begin(), end());
    }

    /**
     * @brief 循环右移
     */
    void cyclicRightShift(int p) {
        cyclicLeftShift(length - p);
    }

    /**
     * @brief 需要有序集，最优解
     * @see P19 T11
     * 
     * 分别找出两个有序集A, B的中位数a, b，比较二者的大小
     * 1. 若a < b，则舍弃A较大的一半和B较小的一半
     * 2. 若a > b，则舍弃A较小的一半和B较大的一半
     * 3. 若a == b，则找到了中位数
     * 
     * 时间复杂度 O(log n)
     * 空间复杂复 O(1)
     */
    value_t median(const Array& other) const {
        int l1 = 0, r1 = length - 1, l2 = 0, r2 = other.length - 1;
        while (l1 != r1 || l2 != r2) {
            int m1 = l1 + ((r1 - l1) >> 1);
            int m2 = l2 + ((r2 - l2) >> 1);
            if (data[m1] > other.data[m2]) {
                if ((l1 + r1) % 2 == 0) {
                    r1 = m1;
                    l2 = m2;
                } else {
                    r1 = m1;
                    l2 = m2 + 1;
                }
            } else if (data[m1] < other.data[m2]) {
                if ((l1 + r1) % 2 == 0) {
                    l1 = m1;
                    r2 = m2;
                } else {
                    l1 = m1 + 1;
                    r2 = m2;
                }
            } else {
                return data[m1];
            }
        }
        return std::min(data[l1], other.data[l2]);
    }

    /**
     * @brief 需要有序集，非最优解
     * @see P19 T11
     * 
     * 升序依次访问两个有序集，第n个元素即为中位数
     * 
     * 时间复杂度 O(n)
     * 空间复杂复 O(1)
     */
    value_t median2(const Array& other) const {
        int n = length;
        int i = 0, j = 0, idx = 0;
        while (i < n && j < n) {
            if (data[i] < other.data[j]) {
                ++i;
            } else if (data[i] > other.data[j]) {
                ++j;
            } else {
                ++i;
                ++j;
                ++idx;
            }
            ++idx;
            if (idx == n) {
                return std::max(data[i - 1], other.data[j - 1]);
            }
        }
        return value_t{};
    }

    /**
     * @see P20 T12
     * 
     * 遍历数组，第一次将首元记为主元，若遍历到主元计数加一否则计数减一，若计数为0，则选取当前元素为主元，重新计数
     * 遍历完成后，若计数大于0，重新计数并判断主元出现的次数k是否大于n/2，若是返回主元，若不是则不存在主元
     * 
     * 时间复杂度 O(n)
     * 空间复杂度 O(1)
     */
    value_t pivot() const {
        int cnt = 1, pivot = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] == pivot) {
                ++cnt;
            } else {
                if (cnt > 0) {
                    --cnt;
                } else {
                    pivot = data[i];
                    cnt = 1;
                }
            }
        }
        if (cnt > 0) {
            cnt = 0;
            for (int i = 0; i < length; ++i) {
                if (data[i] == pivot) {
                    ++cnt;
                }
            }
        }
        return cnt > length / 2 ? cnt : -1;
    }

    /**
     * @see P20 T12
     * 
     * 使用哈希表对数组中的每个元素计数，遍历哈希表，寻找计数大于n/2的元素并返回，若不存在则返回-1
     * 
     * 时间复杂度 O(n)
     * 空间复杂度 O(n)
     */
    value_t pivot2() const {
        std::unordered_map<int, int> mp;
        for (int i = 0; i < length; ++i) {
            mp[data[i]]++;
        }
        for (const auto& [num, cnt] : mp) {
            if (cnt > length / 2) {
                return num;
            }
        }
        return -1;
    }

    /**
     * @see P20 T13
     * 
     * 使用哈希对数组计数，找到数组中的最大元素m，从1枚举到m，若计数为0则找到了未出现的最小正整数，若不存在返回m+1
     * 
     * 时间复杂度 O(n)
     * 空间复杂度 O(n)
     */
    value_t findMinNotExists() const {
        value_t maxElem = INT_MIN;
        std::unordered_map<int, int> mp;
        for (int i = 0; i < length; ++i) {
            mp[data[i]]++;
            maxElem = std::max(maxElem, data[i]);
        }
        for (value_t num = 1; num <= maxElem; ++num) {
            if (mp[num] == 0) {
                return num;
            }
        }
        return maxElem + 1;
    }

    /**
     * @see P20 T14，最优解
     * 
     * 模拟按升序遍历三个数组，即每次只移动三者之间最小元素所在数组的指针，
     * 三个指针指向的数字构成一个三元组，求三元组距离最小值即可
     * 
     * 时间复杂度 O(n)
     * 空间复杂复 O(1)
     */
    static value_t minDistance(const Array& a, const Array& b, const Array& c) {
        int i = 0, j = 0, k = 0, ans = INT_MAX;

        static auto calc_d = [](value_t x, value_t y, value_t z) {
            return std::abs(x - y) + std::abs(y - z) + std::abs(z - x);
        };

        static auto xis_min = [](value_t x, value_t y, value_t z) {
            return x <= y && x <= z;
        };

        while (i < a.length && j < b.length && k < c.length) {
            ans = std::min(ans, calc_d(a.data[i], b.data[j], c.data[k]));
            if (xis_min(a.data[i], b.data[j], c.data[k])) { // i指向的元素最小
                ++i;
            } else if (xis_min(b.data[j], a.data[i], c.data[k])) { // j指向的元素最小
                ++j;
            } else if (xis_min(c.data[k], a.data[i], b.data[j])) { // k指向的元素最小
                ++k;
            }
        }
        return ans;
    }
};

//////////////////////////////////// TEST ////////////////////////////////////

auto should_operator = []() {
    Array arr;

    int n = 10;
    for (int i = 0; i < n; ++i) {
        arr.insert(0, i);
    }
    arr.print();

    int x;
    arr.remove(0, x);
    arr.print();
    std::cout << x << std::endl;

    int idx = arr.find(8);
    std::cout << idx << std::endl;
};

auto should_remove_min = []() {
    // Given
    int n = 5;
    Array arr = {6, 5, 1, 7, 4};

    // When
    int min_elem = arr.removeMin();

    // Then
    assert(min_elem == 1);
    arr.print(0, 4); // 6 5 4 7
};

auto should_reverse = []() {
    int n = 10;
    Array arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Array::reverse(arr.begin(), arr.end());
    arr.print(); // 9 8 7 6 5 4 3 2 1 0
};

auto should_remove_all = []() {
    int n = 10, x = 2;
    Array arr = {1, 1, 2, 3, 5, 2, 2, 5, 7, 2};
    int newLength = arr.removeAll(x);
    arr.print(0, newLength); // 1 1 3 5 5 7
};

auto should_remove_between = []() {
    int n = 10;
    Array arr = {1, 1, 2, 3, 5, 2, 2, 5, 7, 2};
    int s = 2, t = 5;
    assert(arr.removeBetween(t, s) == -1);
    int newLength = arr.removeBetween(s, t);
    arr.print(0, newLength); // 1 1 7
};

auto should_distinct = []() {
    int n = 10;
    Array arr = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4};
    int newLength = arr.distinct();
    arr.print(0, newLength); // 1 2 3 4
};

auto should_merge = []() {
    Array a = {1, 2, 2, 5, 5};
    Array b = {1, 3, 3, 4, 4};
    auto ans = a.merge(b);
    ans.print();
};

auto should_reverse2 = []() {
    int k = 4; // 4 6
    Array arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    arr.reverse(k);
    arr.print(); // 4 5 6 7 8 9 0 1 2 3
};

auto should_search = []() {
    Array arr = {1, 1, 2, 2, 2, 3, 3, 5, 5, 5};
    std::cout << arr.search(2) << std::endl; // 4
    arr.print();                             // 1 1 2 2 3 2 3 5 5 5

    std::cout << arr.search(4) << std::endl; // -1
    arr.print();                             // 1 1 2 2 3 2 3 4 5 5 5
};

auto should_print_same = []() {
    Array a = {1, 2, 3}, b = {2, 3, 4}, c = {-1, 0, 2};
    Array::printSame(a, b, c); // 2
};

auto should_cyclic_left_shift = []() {
    int p = 4; // 4 6
    Array arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    arr.cyclicLeftShift(p);
    arr.print(); // 4 5 6 7 8 9 0 1 2 3
};

auto should_cyclic_right_shift = []() {
    int p = 4; // 4 6
    Array arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    arr.cyclicRightShift(p);
    arr.print(); // 6 7 8 9 0 1 2 3 4 5
};

auto should_get_median = []() {
    Array a = {11, 13, 15, 17, 19}, b = {2, 4, 6, 8, 20};
    int ans = a.median(b);
    std::cout << ans << std::endl; // 11
};

auto should_get_median2 = []() {
    Array a = {11, 13, 15, 17, 19}, b = {2, 4, 6, 8, 20};
    int ans = a.median2(b);
    std::cout << ans << std::endl; // 11
};

auto should_get_pivot = []() {
    Array a = {0, 5, 5, 3, 5, 7, 5, 5}, b = {0, 5, 5, 3, 5, 1, 5, 7};
    assert(a.pivot() == 5);
    assert(b.pivot() == -1);
};

auto should_get_pivot2 = []() {
    Array a = {0, 5, 5, 3, 5, 7, 5, 5}, b = {0, 5, 5, 3, 5, 1, 5, 7};
    assert(a.pivot2() == 5);
    assert(b.pivot2() == -1);
};

auto should_find_min_not_exists = []() {
    Array a = {-5, 3, 2, 3}, b = {1, 2, 3};
    assert(a.findMinNotExists() == 1);
    assert(b.findMinNotExists() == 4);
};

auto should_get_min_distance = []() {
    Array s1 = {-1, 0, 9}, s2 = {-25, -10, 10, 11}, s3 = {2, 9, 17, 30, 41};
    assert(Array::minDistance(s1, s2, s3) == 2);
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    should_operator();
    separator();

    should_remove_min();
    separator();

    should_reverse();
    separator();

    should_remove_all();
    separator();

    should_remove_between();
    separator();

    should_distinct();
    separator();

    should_merge();
    separator();

    should_reverse2();
    separator();

    should_search();
    separator();

    should_print_same();
    separator();

    should_cyclic_left_shift();
    separator();

    should_cyclic_right_shift();
    separator();

    should_get_median();
    separator();

    should_get_median2();
    separator();

    should_get_pivot();
    separator();

    should_get_pivot2();
    separator();

    should_find_min_not_exists();
    separator();

    should_get_min_distance();
    separator();
}