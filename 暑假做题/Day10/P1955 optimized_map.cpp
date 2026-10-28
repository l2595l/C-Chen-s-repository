#include <bits/stdc++.h>
using namespace std;

/* ============================================================
 * 程序自动分析 (NOI2015 / Luogu P1955)
 *
 * 思路：离线 + 离散化哈希 + 并查集
 *   1. 读入本组所有约束，暂存。
 *   2. 先处理所有 e=1（相等）约束：把 x_i、x_j 合并到同一集合。
 *   3. 再处理所有 e=0（不等）约束：若两端已在同一集合，则矛盾 → NO。
 *
 * 关键点（原代码的 bug）：不能在线边读边判，必须“先全合并、后全检查”。
 * 例：约束 (1,2,0) 和 (1,2,1)，在线处理会先判不等通过、再合并，
 *     但整体显然不可满足。离线两遍处理才能正确判定。
 *
 * 相比原始 map() 的优化：
 *  1. 抽取重复逻辑 i/j → get_id()。
 *  2. 修正负数取模：i % mod 在 i<0 时得负下标 → 越界（UB）。
 *  3. 去掉 ok 标志：命中即 return。
 *  4. auto& 遍历避免拷贝；小函数 inline。
 *  5. 按秩合并 + 路径压缩，并查集近似 O(α(n))。
 * ============================================================ */

const int MAXN = 2000005;   // 并查集结点数，>= 2*n（每个约束最多 2 个不同值）
const int MOD  = 400009;    // 哈希桶数量（质数，降低碰撞）

// ---------- 离散化哈希表 ----------
struct node { int real, map; };
vector<node> bucket[MOD];
int tot;                    // 已分配的离散化编号（从 1 开始）

inline int get_id(int v) {
    int b = v % MOD;
    if (b < 0) b += MOD;               // 负数取模修正
    for (const auto &e : bucket[b])
        if (e.real == v) return e.map; // 命中，返回已有编号
    bucket[b].push_back({v, ++tot});   // 未命中，新建编号
    return tot;
}

// ---------- 并查集 ----------
int fa[MAXN], rnk[MAXN];

inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);   // 路径压缩
}

inline void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);               // 按秩合并
    fa[y] = x;
    if (rnk[x] == rnk[y]) ++rnk[x];
}

struct Query { int i, j, e; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<Query> q(n);
        for (auto &x : q) cin >> x.i >> x.j >> x.e;

        // 重置状态：本组最多 2n 个不同编号
        tot = 0;
        for (int i = 0; i < MOD; ++i) bucket[i].clear();
        for (int i = 1; i <= 2 * n + 1; ++i) fa[i] = i, rnk[i] = 0;

        // 第一遍：合并所有“相等”约束
        for (auto &x : q)
            if (x.e == 1) unite(get_id(x.i), get_id(x.j));

        // 第二遍：检查所有“不等”约束是否冲突
        bool ok = true;
        for (auto &x : q) {
            if (x.e == 0 && find(get_id(x.i)) == find(get_id(x.j))) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}