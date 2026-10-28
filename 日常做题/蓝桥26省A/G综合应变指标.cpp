//
// Created by 28447 on 2026/10/23.
//
#include <bits/stdc++.h>
using namespace std;

// 把序列切成 4 个非空连续段,最大化 |段1和| + |段2和| + |段3和| + |段4和|。
// 关键转化:|s| = max(s, -s)。
// 求最大值时,给每段独立选一个符号,取最大的那种选法,结果就等于 |s|。
// 所以问题变成:切 4 段 + 给每段选符号 ±1,使 Σ 符号 * 段和 最大,可以直接 DP。

using Int = long long;
constexpr Int kNegInf = LLONG_MIN / 4;  // 不可达状态,留余量防止相加溢出
constexpr int kSegments = 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Int> a(n);
    for (Int& v : a) {
        cin >> v;
    }

    // f[t][s]:已处理若干个元素,当前元素落在第 t 段(0..3),该段符号为 sign[s] 时的最大值
    const Int sign[2] = {1, -1};
    Int f[kSegments][2];
    for (auto& row : f) {
        row[0] = row[1] = kNegInf;
    }
    // 第一个元素必然属于第 1 段
    f[0][0] = a[0];
    f[0][1] = -a[0];

    for (int i = 1; i < n; ++i) {
        Int g[kSegments][2];
        for (int t = 0; t < kSegments; ++t) {
            // 从上一段结束的最好结果:t == 0 时没有上一段
            Int fromPrev = kNegInf;
            if (t > 0) {
                fromPrev = max(f[t - 1][0], f[t - 1][1]);
            }
            for (int s = 0; s < 2; ++s) {
                // 要么继续留在第 t 段,要么这个元素是第 t 段的第一个元素
                Int best = max(f[t][s], fromPrev);
                g[t][s] = (best <= kNegInf) ? kNegInf : best + sign[s] * a[i];
            }
        }
        memcpy(f, g, sizeof(f));
    }

    cout << max(f[kSegments - 1][0], f[kSegments - 1][1]) << '\n';
    return 0;
}
