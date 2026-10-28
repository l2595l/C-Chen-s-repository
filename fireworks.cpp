#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 * ============================================================================
 *  题目：烟花街道（线性 DP + 二维偏序 + 双树状数组）
 * ============================================================================
 *
 *  题意：
 *    一条街道有 n 个燃放点（编号 1..n，相邻距离 1），初始时刻 0 crq 的位置任选，
 *    每 1 单位时间最多移动 k 单位距离。
 *    有 m 束烟花，第 i 束在位置 a[i]、精彩值 b[i]、颜色 c[i]、时间 t[i] 燃放。
 *    若 t[i] 时 crq 位于 a[i]，可观看它：快乐值先 + b[i]；若 c[i]==1，再取相反数。
 *    初始快乐值 0，求结束后快乐值的最大值。
 *
 * ----------------------------------------------------------------------------
 *  核心难点：为什么要维护「最大」和「最小」两个值？
 * ----------------------------------------------------------------------------
 *    观看第 i 束烟花后：happy = happy + b[i]，若 c[i]==1 再取反。
 *    取反会让「比较方向」反过来：一个在 j 处"比较小"的快乐值，经过一次取反反而更大。
 *    因此仅仅记住"以 j 结尾的最大快乐值"是不够的，还必须同时记住"最小快乐值"。
 *
 *    设 MX[j] = 以 j 结尾能得到的最大快乐值，MN[j] = 最小快乐值。
 *    从 j 转移到 i（要求能赶到：t[j]<=t[i] 且距离可达）：
 *
 *      c[i] == 0：happy = happy_j + b[i]
 *          MX[i] = max(MX[j]) + b[i]      -> 需要 max(MX[j])
 *          MN[i] = min(MN[j]) + b[i]      -> 需要 min(MN[j])
 *
 *      c[i] == 1：happy = -(happy_j + b[i]) = -happy_j - b[i]
 *          MX[i] = -(min(MN[j])) - b[i]   -> 需要 min(MN[j])
 *          MN[i] = -(max(MX[j])) - b[i]   -> 需要 max(MX[j])
 *
 *    所以对"所有可达前驱 j"只需要两个量：max(MX[j]) 和 min(MN[j])。
 *    用两棵"前缀最大值"树状数组维护：
 *          bitMX  存 MX[j]，查询得到 max(MX[j])
 *          bitMNN 存 -MN[j]，查询得到 max(-MN[j]) = -min(MN[j])
 *
 * ----------------------------------------------------------------------------
 *  二维偏序转化
 * ----------------------------------------------------------------------------
 *    从 j 到 i 需要 |a[i]-a[j]| <= k*(t[i]-t[j])（且 t[j]<=t[i]）。
 *    拆成两个不等式：
 *          a[i]-a[j] <= k(t[i]-t[j])  ==>  a[i]-k*t[i] <= a[j]-k*t[j]
 *          a[j]-a[i] <= k(t[i]-t[j])  ==>  a[i]+k*t[i] >= a[j]+k*t[j]
 *    记 A = a - k*t，B = a + k*t，则条件等价于：
 *          A[i] <= A[j]  且  B[i] >= B[j]        （⚠ A 是不等号是 <=，常见易错点）
 *
 *    把所有烟花按 A 从大到小、A 相同时 B 从小到大排序，
 *    处理到 i 时，所有满足 A[j]>=A[i] 且 B[j]<=B[i] 的 j 都已插入树状数组，
 *    再在 B 维度做前缀查询即可。时间复杂度 O(m log m)。
 *
 *    （题面保证"同时同地至多一束烟花"，故 (a,t) 互不相同，(A,B) 也互不相同。）
 *
 * ----------------------------------------------------------------------------
 *  输入格式
 * ----------------------------------------------------------------------------
 *  第 1 行：n m k
 *  接下来 m 行：a b c t
 * ============================================================================
 */

const ll NEG = LLONG_MIN / 4;   // 负无穷哨兵（远小于任何合法快乐值）

struct Firework {
    ll a, b, t;   // 位置、精彩值、时间
    int c;        // 颜色
    ll A, B;      // A = a - k*t, B = a + k*t
};

// 树状数组：单点取 max 更新，前缀取 max 查询
struct BIT {
    int n;
    vector<ll> tr;
    BIT(int _n = 0) : n(_n), tr(_n + 1, NEG) {}
    void upd(int x, ll v) { for (; x <= n; x += x & -x) tr[x] = max(tr[x], v); }
    ll qry(int x) { ll r = NEG; for (; x > 0; x -= x & -x) r = max(r, tr[x]); return r; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    int m;
    cin >> n >> m >> k;          // 注意顺序：n m k

    vector<Firework> fw(m);
    vector<ll> allB;
    for (int i = 0; i < m; ++i) {
        cin >> fw[i].a >> fw[i].b >> fw[i].c >> fw[i].t;
        fw[i].A = fw[i].a - k * fw[i].t;
        fw[i].B = fw[i].a + k * fw[i].t;
        allB.push_back(fw[i].B);
    }

    // B 离散化
    sort(allB.begin(), allB.end());
    allB.erase(unique(allB.begin(), allB.end()), allB.end());

    // A 降序（A 大的先处理），A 相同时 B 升序
    sort(fw.begin(), fw.end(), [](const Firework &x, const Firework &y) {
        if (x.A != y.A) return x.A > y.A;
        return x.B < y.B;
    });

    BIT bitMX((int)allB.size());   // 维护 MX[j]（最大快乐值）
    BIT bitMNN((int)allB.size());  // 维护 -MN[j]（最小快乐值的相反数）

    ll ans = 0;                    // 可以一束都不看，快乐值 0

    for (auto &e : fw) {
        int rk = (int)(lower_bound(allB.begin(), allB.end(), e.B) - allB.begin()) + 1;

        // 基础情况：单独只看这一束（初始位置任选，第一束无距离限制）
        ll MX = (e.c == 0) ? e.b : -e.b;
        ll MN = MX;                 // 单束烟花时最大 = 最小

        if (e.c == 0) {
            // happy = happy_j + b[i]
            ll q1 = bitMX.qry(rk);      // max(MX[j])
            if (q1 > NEG) MX = max(MX, q1 + e.b);
            ll q2 = bitMNN.qry(rk);     // -min(MN[j])
            if (q2 > NEG) MN = min(MN, -q2 + e.b);
        } else {
            // happy = -happy_j - b[i]
            ll q2 = bitMNN.qry(rk);     // max(-MN[j]) = -min(MN[j])
            if (q2 > NEG) MX = max(MX, q2 - e.b);
            ll q1 = bitMX.qry(rk);      // max(MX[j])
            if (q1 > NEG) MN = min(MN, -q1 - e.b);
        }

        // 插入自身，供后续烟花转移
        bitMX.upd(rk, MX);
        bitMNN.upd(rk, -MN);

        ans = max(ans, MX);
    }

    cout << ans << '\n';
    return 0;
}
