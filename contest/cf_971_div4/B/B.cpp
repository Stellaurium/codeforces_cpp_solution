//
// Created by Stellaura on 2024/9/4.
//
#include <bits/stdc++.h>

using namespace std;

int ret[1000];

int main() {
	int t;
	cin >> t;
	int row;
	char note;

	while (t--) {
		cin >> row;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> note;
				if (note == '#') {
					ret[i] = j + 1;
				}
			}
		}
		// print
		bool print_space = false;
		for (int i = row - 1; i >= 0; i--) {
			if (print_space) {
				cout << " ";
			}
			print_space = true;
			cout << ret[i];
		}
		cout << endl;
	}

	return 0;
}