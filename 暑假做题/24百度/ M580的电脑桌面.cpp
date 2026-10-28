//
// Created by 28447 on 2026/9/13.
//
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> phi(n + 1);
    vector<int> primes;
    vector<bool> vis(n + 1, false);

    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > n) break;
            vis[v] = true;
            if (i % p == 0) {
                phi[v] = phi[i] * p;
                break;
            } else {
                phi[v] = phi[i] * (p - 1);
            }
        }
    }

    long long ans = 0;

    for (int t = 1; t <= n; t++) {
        long long q = n / t;
        q %= MOD;

        long long term = q * q % MOD;
        term = term * phi[t] % MOD;

        ans += term;
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}