//
// Created by 28447 on 2026/10/10.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; } return x; }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);

        vector<array<ll, 3>> e(m);      // {d, u, v}
        ll D = 0;                        // 全部铜的总价值（全部卖掉能拿到的钱）
        for (int i = 0; i < m; ++i) {
            ll u, v, d;
            scanf("%lld %lld %lld", &u, &v, &d);
            e[i] = {d, u, v};
            D += d;
        }
        sort(e.begin(), e.end());        // 按铜含量升序（Kruskal 顺序）

        DSU dsu(n);
        vector<ll> w(1, 0);              // w[1..r]：Kruskal 中成功合并的边的 d 值（非递减）
        for (auto &x : e)
            if (dsu.unite((int)x[1], (int)x[2])) w.push_back(x[0]);

        int r = (int)w.size() - 1;
        vector<ll> W(r + 1, 0);          // W[j] = 保留前 j 条边的总铜价值
        for (int j = 1; j <= r; ++j) W[j] = W[j - 1] + w[j];

        for (int qi = 0; qi < q; ++qi) {
            ll x;
            scanf("%lld", &x);

            // 保留 j 条边 => 连通分量数 c = n - j => 需铺 k = c - 1 条新电缆
            // 总成本 cost(j) = W[j] + x * k(k+1)/2，利润 = D - cost(j)
            // cost(j) 关于 j 是凸函数（W 的增量 w 非递减、x*k(k+1)/2 关于 j 也是凸的）
            // => 三分搜索最小值
            auto val = [&](ll j) -> ll {
                ll k = n - j - 1;                       // 需要铺设的新电缆条数
                return W[j] + x * (k * (k + 1) / 2);
            };

            ll lo = 0, hi = r;
            while (hi - lo > 2) {
                ll m1 = lo + (hi - lo) / 3;
                ll m2 = hi - (hi - lo) / 3;
                if (val(m1) <= val(m2)) hi = m2;        // 谷底在左半
                else lo = m1;                          // 谷底在右半
            }
            ll best = val(lo);
            for (ll j = lo + 1; j <= hi; ++j) best = min(best, val(j));

            printf("%lld%c", D - best, qi + 1 == q ? '\n' : ' ');
        }
    }
    return 0;
}
