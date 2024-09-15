//
// Created by Stellaura on 2024/9/15.
//
#include <bits/stdc++.h>

// #pragma GCC optimize("O3")

using namespace std;
#define int int64_t

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

constexpr const char *narek = "narek";
int max_value[1000 + 1][5];

bool is_narek(char c) { return c == 'n' | c == 'a' | c == 'r' | c == 'e' | c == 'k'; }

// 返回下一个的位置+分数
// 分数的计算方式是 narek 每按照顺序找到+1，不按照顺序-1
pair<int, int> simulate(const string &s, int index) {
    int score = 0;
    for (auto e : s) {
        if (is_narek(e)) {
            if (e == narek[index]) {
                score++;
                index++;
                index %= 5;
            } else {
                score--;
            }
        }
    }
    return {index, score};
}

void solve() {
    // deal with one case here
    int n, m;
    cin >> n >> m;
    vector<string> strs;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        strs.push_back(s);
    }

    // 初始化最小值
    for (int j = 1; j < 5; j++) {
        // 不能设置为最小的，这样会溢出为正数
        max_value[0][j] = numeric_limits<int>::min() / 2;
    }

    for (int i = 0; i < n; i++) {
        // 至少是前面的值，让后面不需要一直跟前面max
        for (int j = 0; j < 5; j++) {
            max_value[i + 1][j] = max_value[i][j];
        }
        for (int j = 0; j < 5; j++) {
            auto [next_index, score] = simulate(strs[i], j);
            // 这里max的两边都是以next_index结尾的，所以可以不减去narek多余的部分
            max_value[i + 1][next_index] = max(max_value[i][j] + score, max_value[i + 1][next_index]);
        }
    }

    int ret = 0;
    for (int j = 0; j < 5; j++) {
        ret = max(ret, max_value[n][j] - 2 * j);
    }
    cout << ret << endl;
}