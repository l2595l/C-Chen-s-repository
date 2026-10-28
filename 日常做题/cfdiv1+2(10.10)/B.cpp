//
// Created by 28447 on 2026/10/12.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<int> cnt(n + 2, 0);            // a_i ¡Ê [0, n]
        for (int i = 0; i < n; ++i) {
            int x; scanf("%d", &x); ++cnt[x];
        }
        int M = 0;
        while (cnt[M] >= 2 * k) ++M;          // cnt[n+1]=0 ±£Ö¤Í£ÏÂ
        printf(cnt[M] >= 2 * k - 1 ? "YES\n" : "NO\n");
    }
    return 0;
}
