#include <bits/stdc++.h>
using namespace std;

// 基环树上的最大权路径。
// 输入：n，随后 n 个点权 w[1..n]，再 n 条无向边 (u, v)。
//       图连通，点数等于边数，因此恰好含一个环。
// 路径允许沿环走完整一圈再回到起点所在的点：每条边最多经过一次，
// 点权每个点只计一次。
// 输出：最大权路径的点权和（至少为 0）。
//
// 做法：
//   1. 从叶子开始逐层剥掉环外的树，同时记录每个点向下的最长链和次长链。
//   2. 剩下的点构成环，按环的顺序展开成数组，在环上做滑动窗口求最大值。

using Int = long long;

struct Graph {
    int size = 0;
    vector<Int> weight;           // weight[v]：点权，下标从 1 开始
    vector<vector<int>> adj;  // adj[v]：v 的邻居
};

Graph ReadGraph() {
    Graph g;
    cin >> g.size;
    g.weight.assign(g.size + 1, 0);
    g.adj.assign(g.size + 1, {});
    for (int v = 1; v <= g.size; ++v) {
        cin >> g.weight[v];
    }
    for (int i = 0; i < g.size; ++i) {
        int u = 0;
        int v = 0;
        cin >> u >> v;
        g.adj[u].push_back(v);
        g.adj[v].push_back(u);
    }
    return g;
}

// 剥树的结果。
struct PeelResult {
    vector<char> onCycle;  // onCycle[v]：v 在环上
    // down1[v] / down2[v]：从 v 出发只往环外子树里走的最长链与次长链的点权和，
    // 都包含 v 自己。没有第二条链时 down2[v] 等于 weight[v]。
    vector<Int> down1;
    vector<Int> down2;
    Int best = 0;  // 完全落在某个点的子树里（经过该点）的最大路径
};

// 把候选链 candidate 合并进 (first, second)，保持 first >= second。
void MergeChain(Int candidate, Int& first, Int& second) {
    if (candidate > first) {
        second = first;
        first = candidate;
    } else {
        second = max(second, candidate);
    }
}

// 拓扑剥叶：度数为 1 的点一定在环外，把它并入它唯一的未删除邻居。
// 一个点被取出时，它所有的孩子都已经合并完毕。
PeelResult PeelTrees(const Graph& g) {
    PeelResult result;
    result.onCycle.assign(g.size + 1, 1);
    result.down1 = g.weight;
    result.down2 = g.weight;

    vector<int> degree(g.size + 1, 0);
    queue<int> leaves;
    for (int v = 1; v <= g.size; ++v) {
        degree[v] = static_cast<int>(g.adj[v].size());
        if (degree[v] == 1) {
            leaves.push(v);
        }
    }

    while (!leaves.empty()) {
        int v = leaves.front();
        leaves.pop();
        result.onCycle[v] = 0;
        // 以 v 为最高点的路径：两条向下链共用 v，所以减去一次 weight[v]。
        result.best = max(result.best, result.down1[v] + result.down2[v] - g.weight[v]);

        for (int parent : g.adj[v]) {
            if (!result.onCycle[parent]) {
                continue;
            }
            MergeChain(result.down1[v] + g.weight[parent], result.down1[parent],
                       result.down2[parent]);
            if (--degree[parent] == 1) {
                leaves.push(parent);
            }
            break;  // 唯一未删除的邻居就是父亲
        }
    }
    return result;
}

// 按环上的相邻顺序列出环上的点。
vector<int> WalkCycle(const Graph& g, const vector<char>& onCycle) {
    int start = 0;
    for (int v = 1; v <= g.size && start == 0; ++v) {
        if (onCycle[v]) {
            start = v;
        }
    }

    vector<int> order;
    vector<char> seen(g.size + 1, 0);
    for (int cur = start; cur != 0;) {
        seen[cur] = 1;
        order.push_back(cur);
        int next = 0;
        for (int neighbor : g.adj[cur]) {
            if (onCycle[neighbor] && !seen[neighbor]) {
                next = neighbor;
                break;
            }
        }
        cur = next;
    }
    return order;
}

// 在环上求最大路径，r 为环上点的个数。
Int BestOnCycle(const Graph& g, const PeelResult& peel, const vector<int>& cycle) {
    const int r = static_cast<int>(cycle.size());

    // 环上第 i 个点：自己的点权，以及挂在它下面的最长链与次长链（不含自己）。
    vector<Int> weight(r);
    vector<Int> chain1(r);
    vector<Int> chain2(r);
    Int cycleTotal = 0;
    Int best = 0;
    for (int i = 0; i < r; ++i) {
        int v = cycle[i];
        weight[i] = g.weight[v];
        chain1[i] = peel.down1[v] - g.weight[v];
        chain2[i] = peel.down2[v] - g.weight[v];
        cycleTotal += weight[i];
        // 以环上点 v 为最高点、只在它自己的子树里走的路径。
        best = max(best, peel.down1[v] + peel.down2[v] - g.weight[v]);
    }

    // 特殊路径：从某个点的一棵子树走进来，绕环一整圈回到该点，再走进另一棵子树。
    // 点权只计一次，所以是环权和加上这个点的两条链。
    for (int i = 0; i < r; ++i) {
        best = max(best, cycleTotal + chain1[i] + chain2[i]);
    }

    // 其余路径：环上一段连续的弧，两端各接一条向下的链。
    // 把环复制一遍成长度 2r 的数组，弧就变成长度不超过 r 的区间 [j, i]（j < i）。
    // prefix[k] 为前 k 个点的权和，区间 [j, i] 的权和为 prefix[i+1] - prefix[j]。
    // 总值 = chain1[j] + chain1[i] + prefix[i+1] - prefix[j]，
    // 对每个 i 只需在窗口内取 chain1[j] - prefix[j] 的最大值，用单调队列维护。
    vector<Int> prefix(2 * r + 1, 0);
    for (int k = 0; k < 2 * r; ++k) {
        prefix[k + 1] = prefix[k] + weight[k % r];
    }

    deque<pair<int, Int>> window;  // (j, chain1[j] - prefix[j])，值单调递减
    for (int i = 0; i < 2 * r; ++i) {
        // 区间长度 i - j + 1 不能超过环长 r
        while (!window.empty() && i - window.front().first + 1 > r) {
            window.pop_front();
        }
        if (!window.empty()) {
            best = max(best, chain1[i % r] + prefix[i + 1] + window.front().second);
        }
        Int key = chain1[i % r] - prefix[i];
        while (!window.empty() && window.back().second < key) {
            window.pop_back();
        }
        window.emplace_back(i, key);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const Graph g = ReadGraph();
    const PeelResult peel = PeelTrees(g);
    const vector<int> cycle = WalkCycle(g, peel.onCycle);

    Int answer = peel.best;
    if (!cycle.empty()) {
        answer = max(answer, BestOnCycle(g, peel, cycle));
    }
    cout << answer << endl;
    return 0;
}
