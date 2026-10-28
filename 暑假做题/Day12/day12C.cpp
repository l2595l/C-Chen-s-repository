//
// Created by 28447 on 2026/8/24.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    ll* a = new ll[n * m];

    for (int i = 0; i < n * m; i++) cin >> a[i];

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            int p = i * m + j;
            cout << (j > 1 ? " " : "")
                 << a[p-m-1] + a[p-m] + a[p-m+1]
                 + a[p-1] + a[p+1]
                 + a[p+m-1] + a[p+m] + a[p+m+1];
        }
        if (i < n - 2) cout << '\n';
    }

    delete[] a;
    return 0;
}