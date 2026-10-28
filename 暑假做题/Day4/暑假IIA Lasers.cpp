//
// Created by 28447 on 2026/8/16.
//
#include <bits/stdc++.h>
using namespace std;
/////¾ÍÊÇm+n
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        long long x, y;
        cin >> n >> m >> x >> y;
        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
        }
        for (int i = 0; i < m; i++) {
            long long b;
            cin >> b;
        }
        cout << n + m << '\n';
    }

    return 0;
}