//
// Created by Stellaura on 2024/9/14.
//
#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
#define int int64_t

int solve();

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
		cout << solve() << endl;
	return 0;
}

int solve() {
	// deal with one case here
	int m, n, q;
	cin >> n >> m >> q;
	int left, right;
	cin >> left >> right;
	if (left > right) { swap(left, right); }
	int position;
	cin >> position;

	// 在中间
	if (left < position && position < right) {
		return int(ceil((right - left - 1) / 2.0));
	}

	if (position < left) {
		return left - 1;
	}

	if (right < position) {
		return n - right;
	}

	return 0;

}