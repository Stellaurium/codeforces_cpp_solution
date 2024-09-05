//
// Created by stellaura on 04/09/24.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // 需要判断是否能切成两个 如果太小了根本不够分
    if (n % 2 == 0 && n >= 4) {
        cout << "YES\n" << endl;
    } else {
        cout << "NO\n" << endl;
    }
    return 0;
}