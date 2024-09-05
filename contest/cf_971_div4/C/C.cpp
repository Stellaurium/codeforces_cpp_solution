//
// Created by Stellaura on 2024/9/4.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	int x, y, k;

	while (t--) {
		cin >> x >> y >> k;
		int x_jump = (int)ceil((double)x / k) * 2 - 1;
		int y_jump = (int)ceil((double)y / k) * 2;
		cout << max(x_jump, y_jump) << endl;
	}

	return 0;
}