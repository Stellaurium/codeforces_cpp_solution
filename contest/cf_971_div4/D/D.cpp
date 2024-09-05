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

int main() {
	int t;
	cin >> t;
	int n;
	int x, y;

	while (t--) {
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

		int count = 0;
		int last_x = -1;

		for (int i = 0; i < n - 1; i++) {
			if (a[i].x == a[i + 1].x && a[i].x != last_x) {
				last_x = a[1].x;
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

	return 0;
}