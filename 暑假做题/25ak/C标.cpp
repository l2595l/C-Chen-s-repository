//
// Created by 28447 on 2026/9

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void R() {
    i64 n, m, p;
    cin >> n >> m >> p;

    auto S2 = [&](i64 n) {
        return (n & 1 ? (n + 1) / 2 * (n % p) : n / 2 * ((n + 1) % p)) % p;
    };

    auto S3 = [&](i64 n) {
        i64 res = 1;
        array<i64, 3> t = {n - 1, n, n + 1};
        t[t[0] & 1] = 2;
        t[2 - (n + 1) % 3] = 3;
        for (i64 x : t) res = res * (x % p) % p;
        return res;
    };
    //(a¡Áb)modp=((amodp)¡Á(bmodp))modp
    cout << S3(n) * ((m + 1) % p) % p << " "
         << S3(m) * ((n + 1) % p) % p << " "
         << S2(n) * S2(m) % p << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        R();
    }
    return 0;
}