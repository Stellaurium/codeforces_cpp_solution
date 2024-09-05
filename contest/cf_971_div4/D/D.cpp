//
// Created by Stellaura on 2024/9/4.
//
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

array<Point, 200001> a;

// 这个题要求的测试点范围相当的少 仅仅有 2e5 个点
// 并且他保证 x的值是有界的 x <= n
// 因此我们可以直接初始化一个n大小的数组 存放所有点
// 遍历也只需要遍历一次 所有的格点
// 由于数据量很小 不会造成问题
// 这个题做了半天 debug了半天
// 最后的问题就是 最后的答案int盛不下 要用longlong
// 以后还是老老实实所有返回值都longlong把

// 使用 map set 线性复杂度
void solve_linear() {
    int n;
    int x, y;
    map<int, int> x_count_map;
    set<pair<int, int>> point_set;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        a[i] = Point{x, y};
        x_count_map[x]++;
        point_set.emplace(x, y);
    }

    int64_t count = 0;

    // 竖着的三角形
    for (auto e : x_count_map) {
        if (e.second == 2) {
            count += n - 2;
        }
    }

    // 斜着的三角
    for (int i = 0; i < n; i++) {
        if (point_set.contains({a[i].x + 1, a[i].y ^ 1}) && point_set.contains({a[i].x + 2, a[i].y})) {
            count++;
        }
    }

    cout << count << endl;
}

// 定义一个哈希函数用于 unordered_set
namespace std {
template <>
struct hash<pair<int, int>> {
    size_t operator()(const pair<int, int> &p) const {
        //
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
} // namespace std

// 使用 map set 线性复杂度
void solve_linear_unordered() {
    int n;
    int x, y;

    // 使用 unordered_map 和 unordered_set 替换 map 和 set
    unordered_map<int, int> x_count_map;
    unordered_set<pair<int, int>, hash<pair<int, int>>> point_set;

    cin >> n;
    vector<Point> a(n);

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        a[i] = Point{x, y};
        x_count_map[x]++;
        point_set.emplace(x, y);
    }

    int64_t count = 0;

    // 竖着的三角形
    for (const auto &e : x_count_map) {
        if (e.second == 2) {
            count += n - 2;
        }
    }

    // 斜着的三角
    for (const auto &p : a) {
        if (point_set.contains({p.x + 1, p.y ^ 1}) && point_set.contains({p.x + 2, p.y})) {
            count++;
        }
    }

    cout << count << endl;
}

// 两眼一闭 sort以下 nlogn 甚至比上面的更快
void solve_sort() {
    int n;
    int x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        a[i] = Point{x, y};
    }

    std::sort(a.begin(), a.begin() + n, [](Point a, Point b) {
        if (a.x != b.x)
            return a.x < b.x;
        else
            return a.y < b.y;
    });

    int64_t count = 0;
    int last_x = -1;

    for (int i = 0; i < n - 1; i++) {
        if (a[i].x == a[i + 1].x && a[i].x != last_x) {
            last_x = a[i].x;
            count += n - 2;
        }
    }

    // 斜着的三角
    for (int i = 0; i < n; i++) {
        bool has_next_1 = false;
        bool has_next_2 = false;
        for (int j = 1; j <= 5 && j + i < n; j++) {
            if (a[i + j].x == a[i].x + 1 && a[i + j].y + a[i].y == 1) {
                has_next_1 = true;
            }
            if (a[i + j].x == a[i].x + 2 && a[i + j].y == a[i].y) {
                has_next_2 = true;
            }
        }

        if (has_next_1 && has_next_2) {
            count++;
        }
    }

    cout << count << endl;
}

signed main() {
    int t;
    cin >> t;

    while (t--) {
        solve_linear_unordered();
    }

    return 0;
}