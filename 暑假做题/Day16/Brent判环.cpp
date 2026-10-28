//
// Created by 28447 on 2026/8/29.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Pollard_Rho(ll x) {
    ll t = 0;
    ll c = rand() % (x - 1) + 1;
    ll s = t;
    int step = 0, goal = 1;
    ll val = 1;
    for (goal = 1;; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
            t = f(t, c, x);
            val = val * abs(t - s) % x;
            // 如果 val 为 0，退出重新分解
            if (!val) return x;
            if (step % 127 == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
    }
}