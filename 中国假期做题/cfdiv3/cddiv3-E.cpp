//
// Created by 28447 on 2026/10/10.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<ll> a(n + 2), b(n + 2);
        for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
        ll Q = 0;
        for (int v = 1; v <= n - 1; ++v) {
            if (a[v] == b[v + 1]) ++Q;
            if (a[v + 1] == b[v]) ++Q;
        }
        ll Vn = (a[n] == b[n]) ? 1 : 0;
        ll P = 0;
        ll best = P + Q + Vn;
        for (int p = 1; p <= n - 1; ++p) {
            if (a[p] == b[p]) ++P;
            if (a[p + 1] == b[p]) ++P;
            if (a[p] == b[p + 1]) --Q;
            if (a[p + 1] == b[p]) --Q;
            best = max(best, P + Q + Vn);
        }
        printf("%lld\n", (ll)(2 * n - 1) + best);
    }
    return 0;
}
