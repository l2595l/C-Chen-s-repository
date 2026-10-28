//
// Created by 28447 on 2026/10/9.
//
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n + 2);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        int m = n - 4;
        // 三和弦起点 x 可取 1..m
        if (m < 2){ printf("0\n"); continue; }
        vector<int> v(m + 1);
        for (int x = 1; x <= m; ++x)
            v[x] = a[x] + a[x + 2] - a[x + 4];
        //任取两个即为候选
        vector<int> srt(v.begin() + 1, v.end());
        sort(srt.begin(), srt.end());
        long long ans = 0;
        for (size_t i = 0; i < srt.size(); ) {
            size_t j = i;
            while (j < srt.size() && srt[j] == srt[i]) ++j;
            long long c = (long long)(j - i);
            ans += c * (c - 1) / 2;
            i = j;
        }
        //减去共用琴键的
        for (int x = 1; x + 2 <= m; ++x) if (v[x] == v[x + 2]) --ans;
        for (int x = 1; x + 4 <= m; ++x) if (v[x] == v[x + 4]) --ans;
        printf("%lld\n", ans);
    }
    return 0;
}
