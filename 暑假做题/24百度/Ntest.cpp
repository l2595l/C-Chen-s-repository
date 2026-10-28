#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll INF = 4e18;

struct Firework {
    ll a, b, c, t;
    ll A, B;
};

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

    int n, m, k;
    cin >> n >> m >> k;

    vector<Firework> f(m);
    vector<ll> Bs;

    for (int i = 0; i < m; i++) {
        cin >> f[i].a >> f[i].b >> f[i].c >> f[i].t;
        f[i].A = f[i].a - 1LL * k * f[i].t;
        f[i].B = f[i].a + 1LL * k * f[i].t;
        Bs.push_back(f[i].B);
    }

    // 离散化 B
    sort(Bs.begin(), Bs.end());
    Bs.erase(unique(Bs.begin(), Bs.end()), Bs.end());
    int sz = Bs.size();

    // 按 A 排序，A 相同按 B 排序
    sort(f.begin(), f.end(), [](const Firework& x, const Firework& y) {
        if (x.A != y.A) return x.A < y.A;
        return x.B < y.B;
    });

    BIT bitMax(sz); // 维护 max(f_j)
    BIT bitMin(sz); // 维护 max(-f_j)

    ll ans = -INF;

    for (int i = 0; i < m; i++) {
        int idx = lower_bound(Bs.begin(), Bs.end(), f[i].B) - Bs.begin() + 1;

        ll best;
        if (f[i].c == 0) {
            best = bitMax.query(idx);
        } else {
            best = bitMin.query(idx);
        }

        ll fi;
        if (best == -INF) {
            // 没有前驱
            fi = (f[i].c == 0) ? f[i].b : -f[i].b;
        } else {
            if (f[i].c == 0) {
                fi = best + f[i].b;
            } else {
                fi = best - f[i].b;
            }
        }

        ans = max(ans, fi);

        // 更新树状数组
        bitMax.update(idx, fi);
        bitMin.update(idx, -fi);
    }

    cout << ans << "\n";
    return 0;
}