//
// Created by stellaura on 07/09/24.
//
#include <bits/stdc++.h>

#pragma GCC optimize("O3")
using namespace std;
#define int int64_t

// 0 -> 0
// 1 -> a_1
// 2 -> a_1 + a_2
int prefix_sum[400001];

void solve();

signed main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
#ifdef _FILE_IO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int _TT = 1;
    cin >> _TT;
    while (_TT--)
        solve();
    return 0;
}

// 第几组的第几个
pair<int, int> parse(int size, int index) {
    // 从1开始数数
    // index = 5 , size = 2; return 3,1
    // index = 4 , size = 2; return 2,2
    int count = index % size;
    if (count == 0) {
        count = size;
    }
    int group = (index - count) / size + 1;
    return {group, count};
}

// 计算在ci的情况下 1到index的和
// 需要前缀和 进行 o1时间 计算
int partial_array_sum(int size, int i, int index) {
    //    if (index == 0) {
    //        return 0;
    //    }
    int ret;
    if (i + index - 1 <= size) {
        // 完整的连续序列
        // i --> index + i - 1
        ret = prefix_sum[index + i - 1] - prefix_sum[i - 1];
        return ret;
    } else {
        // 从index 到末尾是完整的序列
        // sum - sum(i-1-n+index+1 ,i-1)
        // 恰好 n - index 个
        ret = prefix_sum[size] - (prefix_sum[i - 1] - prefix_sum[i - 1 - size + index + 1 - 1]);
        return ret;
    }
}

// 计算在ci的情况下 1到index的和
// 需要前缀和 进行 o1时间 计算
int extended_partial_array_sum(int i, int index) { return prefix_sum[i + index - 1] - prefix_sum[i - 1]; }

int query(int size, int l, int r) {
    pair<int, int> p1 = parse(size, l);
    pair<int, int> p2 = parse(size, r);
    int first_sum = prefix_sum[size] - extended_partial_array_sum(p1.first, p1.second - 1);
    int last_sum = extended_partial_array_sum(p2.first, p2.second);
    int middle_sum = (p2.first - p1.first - 1) * prefix_sum[size];
    return first_sum + last_sum + middle_sum;
}

// 343 ms
void solve() {
    int n, q;
    int l, r;
    cin >> n >> q;
    vector<int> a(n);
    int a_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a_sum += a[i];
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1 + n] = prefix_sum[i + n] + a[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        cout << query(a.size(), l, r) << endl;
    }
}

// 将数组拼接两次 就可以快速获得 轮换后的数组
// Let's duplicate the array a and concatenate it with itself.
// Now, a should have length 2n and a_i=a_{i−n} for all n<i≤2n.
// Now, the j'th element of the i'th rotation is a_{i+j−1}.
// 轮换后的数组 就是拼接两次的数组的字数组
// 因此我们就可以创建 2a 的前缀和
// 然后 就可以 更简单的得到 轮换数组的任意区间和
