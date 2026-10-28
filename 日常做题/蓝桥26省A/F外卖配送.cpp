//
// Created by 28447 on 2026/10/23.
//
#include <bits/stdc++.h>
using namespace std;

// 输入:N M X,随后 M 行,每行 A_i B_i。
// 订单按固定顺序分成若干连续批次,每批可独立选交通工具。
// 一批有 L 个订单、用第 i 种交通工具的耗时为 L*A_i + L*(L-1)/2*B_i。
// 除第一批外,每开一个新批次要额外花 X 秒返回。
// 输出:送完 N 个订单的最小总耗时。

using Int = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    Int x;
    cin >> n >> m >> x;
    vector<Int> a(m), b(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
    }

    // cost[len]:一批恰有 len 个订单时,选最合适的交通工具的最小耗时
    vector<Int> cost(n + 1, LLONG_MAX);
    for (Int len = 1; len <= n; ++len) {
        for (int k = 0; k < m; ++k) {
            cost[len] = min(cost[len], len * a[k] + len * (len - 1) / 2 * b[k]);
        }
    }

    // dp[i]:送完前 i 个订单的最小总耗时
    vector<Int> dp(n + 1, LLONG_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            // 最后一批是订单 j+1..i;第一批(j == 0)不用返回
            Int back = (j > 0) ? x : 0;
            dp[i] = min(dp[i], dp[j] + cost[i - j] + back);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
