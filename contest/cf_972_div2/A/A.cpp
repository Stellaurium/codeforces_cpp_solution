//
// Created by Stellaura on 2024/9/14.
//
#include <bits/stdc++.h>

//#pragma GCC optimize("O3")

using namespace std;
#define int int64_t

void solve();

char c_list[] = {'a', 'e', 'i', 'o', 'u'};

void construct(int n) {
	int number = n / 5;
	int remain = n % 5;
	for (int i = 0; i < 5; i++) {
		if (i < remain) {
			cout << (c_list[i]);
		}
		for (int j = 0; j < number; j++) {
			cout << (c_list[i]);

		}
	}
}

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

void solve() {
	// deal with one case here
	int n;
	cin >> n;
	construct(n);
	cout << endl;
}