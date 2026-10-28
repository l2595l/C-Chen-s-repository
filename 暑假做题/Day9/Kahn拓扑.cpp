//
// Created by 28447 on 2026/8/23.
//
int n, m;                    // n: 节点总数, m: 边总数
vector<int> G[MAXN];         // 邻接表：G[i]存储所有从节点i出发的边所指向的节点
int in[MAXN];                // in[i]存储节点i的入度（有多少条边指向i）

bool toposort() {
    vector<int> L;           // L: 存储拓扑排序的结果序列
    queue<int> S;            // S: 队列，存储所有当前入度为0的节点（可立即处理的节点）

    // 第一步：将所有初始入度为0的节点加入队列
    // 这些节点没有任何前置依赖，可以最先被处理
    for (int i = 1; i <= n; i++)
        if (in[i] == 0)
            S.push(i);

    // 第二步：不断从队列中取出入度为0的节点进行处理
    while (!S.empty()) {
        int u = S.front();   // 取出队首节点u
        S.pop();

        L.push_back(u);      // 将u加入拓扑序列（u的所有前置依赖都已处理完）

        // 遍历u的所有后继节点v（即所有边 u→v）
        for (auto v : G[u]) {
            // 关键操作：删除边 u→v
            // 因为u已经被处理了，所以v的入度减1
            // --in[v] 表示先让in[v]减1，再判断减完后是否为0
            if (--in[v] == 0) {
                // 如果v的入度变为0，说明所有指向v的节点都处理完了
                // v现在没有任何前置依赖，可以加入队列等待处理
                S.push(v);
            }
        }
    }

    // 第三步：判断是否所有节点都被加入了拓扑序列
    if (L.size() == n) {
        // 所有节点都处理完了，说明图是无环图（DAG）
        // 输出拓扑排序结果
        for (auto i : L)
            cout << i << ' ';
        return true;
    }

    // L.size() < n，说明图中存在环
    // 有环的图无法进行拓扑排序
    return false;
}