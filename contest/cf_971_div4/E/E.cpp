//
// Created by Stellaura on 2024/9/4.
//
#include "BigInt.hpp"
#include <bits/stdc++.h>

using namespace std;

// 这部分的精度足够了 n k i 都是 int类型内
// 乘起来最多就是 int64 2e18
// int64 是 2^63 大约为 9e18
int64_t value(int64_t n, int64_t k, int64_t i) {
    // 2 i + 2 i^2 + 2 k - 2 k^2 + n - 2 k n - n^2
    return abs(2 * i + 2 * i * i + 2 * k - 2 * k * k + n - 2 * k * n - n * n);
}

int64_t calc(int64_t n, int64_t k) {
    // i -> 1/2 (-1 + Sqrt[1 - 4 k + 4 k^2 - 2 n + 4 k n + 2 n^2])
    BigInt big_n{n};
    BigInt big_k{k};

    BigInt temp = 1 - 4 * big_k + 4 * big_k * big_k - 2 * big_n + 4 * big_k * big_n + 2 * big_n * big_n;
    BigInt x = (-1 + sqrt(temp)) / 2;

    int64_t before = x.to_long_long();
    int64_t after = before + 1;
    int64_t before_value = value(n, k, before);
    int64_t after_value = value(n, k, after);
    return min(before_value, after_value) / 2;
}

// 1.5s 这个太慢了 再找找别的高精度库
// 374 ms 效果好多了
int main() {
    int t;
    int64_t n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        cout << calc(n, k) << endl;
    }
    return 0;
}