//
// Created by 28447 on 2026/10/12.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 * D. Target Infection
 * ---------------------------------------------------------------
 * 记 f(s) = |[s, s+m-1] ∩ 感染集合|。要找一个 s 使 f(s) = k。
 *
 * 关键观察：窗口整体右移一格时，只有两个位置改变状态——
 *   f(s+1) - f(s) = [s+m 感染] - [s 感染]  ∈ {-1, 0, +1}
 * 即 f 是一条"每步变化不超过 1"的走字。
 *
 * 记 step(t) = f(t+1) - f(t)。它只在 4n 个位置发生变化：
 *   t = l_i - m     : 窗口右端进入区间 i   → step +1
 *   t = r_i - m + 1 : 窗口右端离开区间 i   → step -1
 *   t = l_i         : 窗口左端进入区间 i   → step -1
 *   t = r_i + 1     : 窗口左端离开区间 i   → step +1
 * 把这些"事件"按位置排序后从左往右扫：
 * 两个事件之间 f 是斜率 σ ∈ {-1,0,+1} 的直线段，
 * 在每段上直接解 f(s) = k（落入段值域就命中）。
 * 扫描范围 [1, 10^18]；题面保证：若存在解，则界内必有解。
 * ---------------------------------------------------------------
 * 复杂度：O(n log n)（事件排序），Σn ≤ 2e5。
 */

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n; ll m, k;
        scanf("%d %lld %lld", &n, &m, &k);
        vector<ll> L(n), R(n);
        for (int i = 0; i < n; ++i) scanf("%lld %lld", &L[i], &R[i]);

        /* ---- 1) 先直接算出 f(1)：窗口 [1, m] 与各区间交长之和 ---- */
        ll f1 = 0;
        for (int i = 0; i < n; ++i) {
            if (L[i] > m) break;                    // 区间全在窗口右侧，后面都不用看
            f1 += min(R[i], m) - L[i] + 1;
        }

        /* ---- 2) 事件表：(位置, Δσ) ---- */
        vector<pair<ll,int>> ev;
        ev.reserve(4 * (size_t)n);
        for (int i = 0; i < n; ++i) {
            ev.push_back({L[i] - m,     +1});       // 右端进入
            ev.push_back({R[i] - m + 1, -1});       // 右端离开
            ev.push_back({L[i],         -1});       // 左端进入
            ev.push_back({R[i] + 1,     +1});       // 左端离开
        }
        sort(ev.begin(), ev.end());

        const ll S = 1000000000000000000LL;         // s 的上界 10^18
        ll ans = -1;

        /* 在 [s0, s1] 这段斜率 σ 的直线上找 f(s) = k */
        auto check = [&](ll s0, ll f0, ll sl, ll s1) -> ll {
            ll endv = f0 + sl * (s1 - s0);
            if (sl == 1) {
                if (k >= f0 && k <= endv) return s0 + (k - f0);
            } else if (sl == -1) {
                if (k <= f0 && k >= endv) return s0 + (f0 - k);
            } else {
                if (f0 == k) return s0;
            }
            return -1;
        };

        /* ---- 3) 从 s = 1 出发扫描 ---- */
        ll cur_s = 1, cur_f = f1, slope = 0;
        size_t idx = 0;
        // 位置 ≤ 1 的事件直接并入 s = 1 处的初始斜率
        while (idx < ev.size() && ev[idx].first <= 1) {
            slope += ev[idx].second; ++idx;
        }
        if (cur_f == k) ans = 1;

        while (ans == -1 && idx < ev.size()) {
            ll p = ev[idx].first;
            if (p > S) break;                       // 界外事件不再影响 [1,S]
            ans = check(cur_s, cur_f, slope, p);    // 段 [cur_s, p]
            if (ans != -1) break;
            cur_f = cur_f + slope * (p - cur_s);    // 走到事件位置 p（先算值）
            cur_s = p;                              // 再移动指针
            while (idx < ev.size() && ev[idx].first == p) {   // 同位置事件一起应用
                slope += ev[idx].second; ++idx;
            }
        }
        if (ans == -1) ans = check(cur_s, cur_f, slope, S);   // 最后一段 [cur_s, S]

        printf("%lld\n", ans);
    }
    return 0;
}
