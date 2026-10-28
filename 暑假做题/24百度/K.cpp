//
// Created by 28447 on 2026/9/9.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 一条边的信息
struct Edge {
    int id;              // 输入顺序中的边编号 (1 ~ n-1)
    vector<int> T;       // 切断该边后，与根(1)不相连的那一侧集合（即某个子树）
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Edge> edges(n - 1);

    // 1. 读入，并确定每条边的 T（与根不相连的那一侧）
    for (int i = 0; i < n - 1; i++) {
        edges[i].id = i + 1;

        int m1; cin >> m1;
        vector<int> a(m1);
        for (int j = 0; j < m1; j++) cin >> a[j];

        int m2; cin >> m2;
        vector<int> b(m2);
        for (int j = 0; j < m2; j++) cin >> b[j];

        // 与根相连的一侧一定包含节点 1；据此判断哪个集合是 T
        bool rootInA = false;
        for (int x : a) if (x == 1) { rootInA = true; break; }
        edges[i].T = rootInA ? b : a;
    }

    // 2. 按子树大小 |T| 从小到大排序（“剥洋葱”：先处理最底层的小子树）
    sort(edges.begin(), edges.end(), [](const Edge& x, const Edge& y) {
        return x.T.size() < y.T.size();
    });

    // contain[v]：包含节点 v 的所有子树，按大小升序（存排序后的下标 s）
    vector<vector<int>> contain(n + 1);
    for (int s = 0; s < n - 1; s++) {
        for (int v : edges[s].T) {
            contain[v].push_back(s);
        }
    }

    // top_of[s]：排序后第 s 个子树集合的“最高点”（这个子树的根节点）
    // ans_edge[v] / ans_father[v]：节点 v 相连边的编号 / 父节点
    vector<int> top_of(n - 1, 0);
    vector<int> ans_father(n + 1, 0);
    vector<int> ans_edge(n + 1, 0);

    // 3. 每个非根节点的子树 = 包含它的最小集合
    for (int v = 2; v <= n; v++) {
        int s0 = contain[v][0];      // subtree(v)
        top_of[s0] = v;
        ans_edge[v] = edges[s0].id;
    }

    // 4. 父节点 = 第二小的包含 v 的集合的“最高点”；若不存在，则父节点是根 1
    for (int v = 2; v <= n; v++) {
        if ((int)contain[v].size() >= 2) {
            ans_father[v] = top_of[contain[v][1]];
        } else {
            ans_father[v] = 1;
        }
    }

    // 5. 输出：节点 2 ~ n 的父节点和边编号
    for (int v = 2; v <= n; v++) {
        cout << ans_father[v] << " " << ans_edge[v] << "\n";
    }

    return 0;
}
