//
// Created by Stellaura on 2024/9/14.
//
#include <bits/stdc++.h>

#pragma GCC optimize("O3")

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

class Tree {
  private:
	std::multiset<int> ms;

  public:
	// 构造函数，允许通过初始化列表插入元素
	Tree() {}

	// 插入元素
	void insert(int value) {
		ms.insert(value);
	}

	// 查找第一个大于n的元素
	std::optional<int> find_first_greater(int n) const {
		auto it = ms.upper_bound(n);
		if (it != ms.end()) {
			return *it; // 找到大于n的元素
		}
		return std::nullopt; // 没有大于n的元素，返回空
	}

	// 查找第一个小于n的元素
	std::optional<int> find_first_less(int n) const {
		auto it = ms.lower_bound(n);
		if (it != ms.begin()) {
			--it; // 向前移动迭代器，找到小于n的元素
			return *it;
		}
		return std::nullopt; // 没有小于n的元素，返回空
	}

	int get_first() {
		return *(ms.begin());
	}
	int get_last() {
		return *(ms.rbegin());
	}

};

// 只需要查到输入的元素的在数组中的上下界
// 该功能可以使用二叉树实现
// c++中就是multiset
void solve() {
	// deal with one case here
	Tree teachers;
	int m, n, q;
	cin >> n >> m >> q;
	int index;
	for (int i = 0; i < m; i++) {
		cin >> index;
		teachers.insert(index);
	}
	int query;
	int ret;
	for (int i = 0; i < q; i++) {
		cin >> query;
		auto upper = teachers.find_first_greater(query);
		auto lower = teachers.find_first_less(query);
		if (!lower.has_value()) {
			ret = teachers.get_first() - 1;
		}
		else if (!upper.has_value()) {
			ret = n - teachers.get_last();
		}
		else {
			ret = int(ceil((*upper - *lower - 1) / 2.0));
		}
		cout << ret << endl;
	}
}