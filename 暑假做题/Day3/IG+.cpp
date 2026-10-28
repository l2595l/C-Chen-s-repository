//
// Created by 28447 on 2026/8/15.
//
#include <bits/stdc++.h>  // 万能头文件，包含所有常用库
using namespace std;

using i64 = long long;  // 将 long long 类型重命名为 i64，方便书写
constexpr i64 inf = (i64)1e18;  // 定义无穷大，1e18 足够大

/**
 * Dijkstra 算法函数
 * @param adj: 邻接表，adj[u] 存储从 u 出发的所有边，每条边是 {目标节点, 权重}
 * @param s: 起点（首都，编号为0）
 * @return d: d[i][0] 表示从起点到 i 的最短距离，d[i][1] 表示最短路径的数量
 */
vector<array<i64,2>> Dijkstra(const vector<vector<array<i64,2>>> &adj, int s) {
    int n = adj.size();  // 获取节点总数
    vector<int> vis(n);  // vis[i] 标记节点 i 是否已经确定最短距离
    // d[i][0] = 最短距离, d[i][1] = 最短路径条数
    vector<array<i64,2>> d(n, {inf, -1});  // 初始化：距离无穷大，路径条数为 -1

    // 优先队列：存储 {距离, 节点}，按距离从小到大排列
    // greater<> 表示小根堆，距离小的先出队
    priority_queue<array<i64,2>, vector<array<i64,2>>, greater<>> q;

    d[s] = {0, 1};  // 起点到自己的距离为0，路径条数为1
    q.push({0, s});  // 将起点加入优先队列

    while (!q.empty()) {  // 当队列不为空时循环
        auto [tmp, u] = q.top();  // 结构化绑定：取出队首元素 {距离, 节点}
        q.pop();  // 弹出队首元素

        if (vis[u]) continue;  // 如果该节点已经确定最短距离，跳过
        vis[u] = 1;  // 标记该节点已确定最短距离

        // 遍历节点 u 的所有邻接边
        for (auto [v, w] : adj[u]) {  // v: 邻居节点, w: 边权
            // 如果通过 u 到达 v 的距离比当前记录的更短
            if (d[u][0] + w < d[v][0]) {
                // 更新最短距离
                d[v] = {d[u][0] + w, d[u][1]};
                // 将更新后的节点加入优先队列
                q.push({d[v][0], v});
            }
            // 如果通过 u 到达 v 的距离等于当前最短距离（找到另一条最短路径）
            else if (d[u][0] + w == d[v][0]) {
                // 增加最短路径条数，但不能超过 inf
                d[v][1] = min(d[v][1] + d[u][1], inf);
            }
        }
    }
    return d;  // 返回所有节点的最短距离和路径条数
}

void solve() {
    int n, m, k;  // n: 城市数, m: 公路数, k: 火车路线数
    cin >> n >> m >> k;

    // 邻接表：n 个节点，每个节点存储 {目标节点, 边权}
    vector<vector<array<i64,2>>> adj(n);

    // ========== 读入公路 ==========
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;  // 将编号从 1-based 转为 0-based（题目是1到n，我们存为0到n-1）
        // 无向图，双向加边
        adj[u].push_back({v, w});  // u -> v，权重 w
        adj[v].push_back({u, w});  // v -> u，权重 w
    }

    // ========== 读入火车路线 ==========
    vector<array<i64,2>> iron;  // 存储所有火车路线 {城市, 距离}
    iron.reserve(k);  // 预分配空间，提高效率

    for (int i = 0; i < k; i++) {
        int s, y;
        cin >> s >> y;
        s--;  // 转为 0-based
        iron.push_back({s, y});  // 保存这条火车路线

        // 将火车路线加入图中（也是无向边）
        adj[0].push_back({s, y});  // 首都 0 -> s，权重 y
        adj[s].push_back({0, y});  // s -> 首都 0，权重 y
    }

    // ========== 运行 Dijkstra 算法 ==========
    // d[i][0] = 从首都到城市 i 的最短距离
    // d[i][1] = 从首都到城市 i 的最短路径条数
    auto d = Dijkstra(adj, 0);  // 0 表示首都（原来的城市1）

    // ========== 判断哪些火车路线可以删除 ==========
    int ans = 0;  // 可以删除的火车路线数量

    // 遍历每条火车路线
    for (auto &[s, y] : iron) {  // s: 城市, y: 火车路线长度
        if (y > d[s][0]) {
            // 情况1：火车路线长度 > 最短距离
            // 说明有更短的路径可以到达 s，这条火车路线没用，可以删除
            ans++;
        }
        else if (d[s][1] > 1) {
            // 情况2：火车路线长度 == 最短距离，且最短路径条数 > 1
            // 说明到达 s 有多个最短路径，删除其中一条不影响最短距离
            ans++;  // 可以删除
            d[s][1]--;  // 删除一条路径，减少计数
        }
        // 情况3：火车路线长度 == 最短距离，且最短路径条数 == 1
        // 说明这是唯一的最短路径，不能删除
    }

    cout << ans << '\n';  // 输出结果
}

int main() {
    ios_base::sync_with_stdio(false);  // 关闭 C 和 C++ 的输入输出同步，加快速度
    cin.tie(nullptr);  // 解除 cin 和 cout 的绑定，加快速度
    solve();  // 调用解题函数
    return 0;
}
// #include <bits/stdc++.h>
// using namespace std;
// using i64 = long long;
// constexpr i64 inf = (i64)1e18;
//
// vector<array<i64,2>> Dijkstra(const vector<vector<array<i64,2>>> &adj, int s) {
//     int n = adj.size();
//     vector<int> vis(n);
//     vector<array<i64,2>> d(n, {inf, -1});
//     priority_queue<array<i64,2>, vector<array<i64,2>>, greater<>> q;
//
//     d[s] = {0, 1};
//     q.push({0, s});
//     while (!q.empty()) {
//         auto [tmp, u] = q.top();
//         q.pop();
//         if (vis[u]) continue;
//         vis[u] = 1;
//         for (auto [v, w] : adj[u]) {
//             if (d[u][0] + w < d[v][0]) {
//                 d[v] = {d[u][0] + w, d[u][1]};
//                 q.push({d[v][0], v});
//             }
//             else if (d[u][0] + w == d[v][0]) {
//                 d[v][1] = min(d[v][1] + d[u][1], inf);
//             }
//         }
//     }
//     return d;
// }
//
// void solve() {
//     int n, m, k;
//     cin >> n >> m >> k;
//     vector<vector<array<i64,2>>> adj(n);
//     for (int i = 0; i < m; i++) {
//         int u, v, w;
//         cin >> u >> v >> w;
//         u--, v--;
//         adj[u].push_back({v, w});
//         adj[v].push_back({u, w});
//     }
//     vector<array<i64,2>> iron;
//     iron.reserve(k);
//     for (int i = 0; i < k; i++) {
//         int s, y;
//         cin >> s >> y;
//         s--;
//         iron.push_back({s, y});
//         adj[0].push_back({s, y});
//         adj[s].push_back({0, y});
//     }
//     int ans = 0;
//     auto d = Dijkstra(adj, 0);
//     for (auto &[s, y] : iron) {
//         if (y > d[s][0]) ans++;
//         else if (d[s][1] > 1) ans++, d[s][1]--;
//     }
//     cout << ans << '\n';
// }
//
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     solve();
//     return 0;
// }