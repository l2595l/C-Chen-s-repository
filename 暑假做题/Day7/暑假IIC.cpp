//
// Created by 28447 on 2026/8/20.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    const long long BASE = 1000000000LL; // 10^9

    while (t--) {
        long long x;
        cin >> x;

        // y = 10^9 - 1 - x
        long long y = BASE - 1 - x;

        cout << y << '\n';
    }

    return 0;
}