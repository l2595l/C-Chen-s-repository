//
// Created by 28447 on 2026/9/9.
// 题目：烟花街道（线性 DP + 二维偏序 + 双树状数组）
#include <bits/stdc++.h>
using namespace std;

#define ll long long

// ============================================================================
//  题意回顾
// ----------------------------------------------------------------------------
//  一条街道有 n 个燃放点（编号 1..n，相邻两点距离 1）。
//  初始时间 t = 0，crq 的初始位置可以任选，每 1 单位时间最多移动 k 单位距离。
//  共有 m 束烟花，第 i 束：位置 a[i]、精彩值 b[i]、颜色 c[i]、时间 t[i]。
//  若 t[i] 时 crq 位于 a[i]，则可观看它：快乐值先 + b[i]，若 c[i]==1 再取相反数。
//  初始快乐值为 0，求所有烟花结束后快乐值的最大值。
//
// ============================================================================
//  一、状态设计：为什么要同时维护「最大值」和「最小值」
// ----------------------------------------------------------------------------
//  观看第 i 束烟花：happy' = happy + b[i]，若 c[i]==1 则 happy' = -happy'。
//  "取相反数"会颠倒大小关系：在 j 处较小的快乐值，经过一次取反反而更大。
//  因此仅仅记住"以 j 结尾的最大快乐值"是不够的，必须同时记住最小值。
//
//  记：
//    MX[i] = 以第 i 束烟花结尾能得到的【最大】快乐值
//    MN[i] = 以第 i 束烟花结尾能得到的【最小】快乐值
//
//  从 j 转移到 i（假设可达），转移公式：
//    c[i] == 0：happy' = happy + b[i]
//        MX[i] = max(MX[j]) + b[i]      —— 需要 max(MX[j])
//        MN[i] = min(MN[j]) + b[i]      —— 需要 min(MN[j])
//    c[i] == 1：happy' = -(happy + b[i]) = -happy - b[i]
//        MX[i] = -(min(MN[j])) - b[i]   —— 需要 min(MN[j])
//        MN[i] = -(max(MX[j])) - b[i]   —— 需要 max(MX[j])
//
//  可见：对"所有可达前驱 j"只需要两个量——max(MX[j]) 和 min(MN[j])。
//  用两棵"前缀最大值"树状数组维护：
//        bitMX  存 MX[j]   → 查询得到 max(MX[j])
//        bitMNN 存 -MN[j]  → 查询得到 max(-MN[j]) = -min(MN[j])
//
// ============================================================================
//  二、二维偏序转化（可达性判定）
// ----------------------------------------------------------------------------
//  从 j 到 i 需要：|a[i] - a[j]| <= k * (t[i] - t[j])，且 t[j] <= t[i]。
//  绝对值拆成两个不等式：
//        a[i]-a[j] <= k*(t[i]-t[j])   ==>  a[i] - k*t[i] <= a[j] - k*t[j]
//        a[j]-a[i] <= k*(t[i]-t[j])   ==>  a[i] + k*t[i] >= a[j] + k*t[j]
//  记 A = a - k*t，B = a + k*t，则条件等价于：
//        A[i] <= A[j]   且   B[i] >= B[j]
//  （⚠ 注意：A 这条的不等号方向是 <=，是本题最常见的易错点。）
//
//  实现：按 A 从大到小、A 相同时 B 从小到大排序，处理到 i 时，
//  所有满足 A[j] >= A[i] 且 B[j] <= B[i] 的 j 都已经被插入树状数组，
//  再在 B 维度（离散化后）做前缀查询即可。
//  题面保证"同时同地至多一束烟花"，故 (a,t) 互不相同，进而 (A,B) 也互不相同。
//
// ============================================================================
//  复杂度：O(m log m)
// ============================================================================

const ll INF = 4e18;   // 当作正无穷使用；-INF 即负无穷哨兵

struct Firework {
    ll a, b, t;   // 位置、精彩值、时间
    ll c;         // 颜色（0/1）
    ll A, B;      // A = a - k*t, B = a + k*t
};

// 树状数组：单点取 max 更新，前缀取 max 查询
struct BIT {
    int n;
    vector<ll> tree;
    BIT(int _n) : n(_n), tree(_n + 1, -INF) {}

    void update(int idx, ll val) {
        while (idx <= n) {
            tree[idx] = max(tree[idx], val);
            idx += idx & -idx;
        }
    }

    ll query(int idx) {
        ll res = -INF;
        while (idx > 0) {
            res = max(res, tree[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;                 // n 本题 DP 中不直接使用；m 烟花数；k 移动速度
    cin >> n >> m >> k;          // ⚠ 输入顺序是 n m k

    vector<Firework> f(m);
    vector<ll> Bs;               // 用于 B 的离散化
    for (int i = 0; i < m; i++) {
        cin >> f[i].a >> f[i].b >> f[i].c >> f[i].t;
        f[i].A = f[i].a - 1LL * k * f[i].t;   // 关键变量 A
        f[i].B = f[i].a + 1LL * k * f[i].t;   // 关键变量 B
        Bs.push_back(f[i].B);
    }

    // 离散化 B
    sort(Bs.begin(), Bs.end());
    Bs.erase(unique(Bs.begin(), Bs.end()), Bs.end());
    int sz = Bs.size();

    // 按 A 降序（A 大的先处理），A 相同时按 B 升序（B 小的先处理）
    sort(f.begin(), f.end(), [](const Firework& x, const Firework& y) {
        if (x.A != y.A) return x.A > y.A;
        return x.B < y.B;
    });

    // 两棵树状数组：一个维护 max(MX[j])，一个维护 -min(MN[j])
    BIT bitMX(sz);    // 存 MX[j]
    BIT bitMNN(sz);   // 存 -MN[j]

    ll ans = 0;       // 可以一束都不看，快乐值为 0

    for (int i = 0; i < m; i++) {
        // 当前 B 在离散化数组中的下标（1-based）
        int idx = (int)(lower_bound(Bs.begin(), Bs.end(), f[i].B) - Bs.begin()) + 1;

        // 基础情况：单独只看这一束烟花
        // 初始位置任选，所以第一束烟花没有任何距离限制
        ll MX = (f[i].c == 0) ? f[i].b : -f[i].b;
        ll MN = MX;    // 单束烟花时，最大值 == 最小值

        if (f[i].c == 0) {
            // happy' = happy + b[i]
            ll q1 = bitMX.query(idx);        // max(MX[j])
            if (q1 > -INF) MX = max(MX, q1 + f[i].b);
            ll q2 = bitMNN.query(idx);       // -min(MN[j])
            if (q2 > -INF) MN = min(MN, -q2 + f[i].b);
        } else {
            // happy' = -happy - b[i]
            ll q2 = bitMNN.query(idx);       // max(-MN[j]) = -min(MN[j])
            if (q2 > -INF) MX = max(MX, q2 - f[i].b);
            ll q1 = bitMX.query(idx);        // max(MX[j])
            if (q1 > -INF) MN = min(MN, -q1 - f[i].b);
        }

        // 插入自身，供后续烟花转移
        bitMX.update(idx, MX);
        bitMNN.update(idx, -MN);

        ans = max(ans, MX);
    }

    cout << ans << "\n";
    return 0;
}