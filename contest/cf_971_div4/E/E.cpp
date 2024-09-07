//
// Created by Stellaura on 2024/9/4.
//
#include "BigInt.hpp"
#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

// 这部分的精度足够了 n k i 都是 int类型内
// 乘起来最多就是 int64 2e18
// int64 是 2^63 大约为 9e18
int64_t value(int64_t n, int64_t k, int64_t i) {
    // 2 i + 2 i^2 + 2 k - 2 k^2 + n - 2 k n - n^2
    return (2 * i + 2 * i * i + 2 * k - 2 * k * k + n - 2 * k * n - n * n)/2;
}


// 1.5s 这个太慢了 再找找别的高精度库
// 374 ms 效果好多了
int64_t calc_with_bigint(int64_t n, int64_t k) {
    // i -> 1/2 (-1 + Sqrt[1 - 4 k + 4 k^2 - 2 n + 4 k n + 2 n^2])
    BigInt big_n{n};
    BigInt big_k{k};

    BigInt temp = 1 - 4 * big_k + 4 * big_k * big_k - 2 * big_n + 4 * big_k * big_n + 2 * big_n * big_n;
    BigInt x = (-1 + sqrt(temp)) / 2;

    int64_t before = x.to_long_long();
    int64_t after = before + 1;
    int64_t before_value = abs(value(n, k, before));
    int64_t after_value = abs(value(n, k, after));
    return min(before_value, after_value) ;
}

// 目的是找到第一个满足 >= 0 的位置
int64_t binary_search_recursive(int64_t n, int64_t k, int64_t left, int64_t right) {
    if (left == right) {
        return left;
    }
    auto mid = (left + right) / 2;
    int64_t mid_value = value(n, k, mid);
    if (mid_value >= 0) {
        // mid_value 当前位置可能就满足
        return binary_search_recursive(n, k, left, mid);
    } else {
        // 当前位置<0 至少应该向右一格
        return binary_search_recursive(n, k, mid + 1, right);
    }
}

// 62ms 这东西比O(1)的算法还快
int64_t binary_search(int64_t n, int64_t k) {
    auto index = binary_search_recursive(n, k, k - 1, k + n - 1);
    return min(abs(value(n, k, index)), abs(value(n, k, index - 1)));
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int t;
    int64_t n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        cout << binary_search(n, k) << endl;
    }
    return 0;
}