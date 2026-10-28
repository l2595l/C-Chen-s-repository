//
// Created by 28447 on 2026/9/9.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ops = 0;
        long long prev = a[0];

        for (int i = 1; i < n; i++) {
            long long x = a[i];
            if (x < prev) {
                long long cnt = 0;
                while (x < prev) {
                    x *= 2;
                    cnt++;
                }
                ops += cnt;
            }
            prev = x;
        }

        cout << ops << "\n";
    }
    return 0;
}