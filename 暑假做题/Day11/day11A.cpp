//
// Created by 28447 on 2026/8/23.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n), b(n);
        ll minA = 1e9, minB = 1e9;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] < minA) minA = a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            if (b[i] < minB) minB = b[i];
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ll da = a[i] - minA;
            ll db = b[i] - minB;
            ans += (da > db ? da : db);
        }
        cout << ans << '\n';
    }
    return 0;
}