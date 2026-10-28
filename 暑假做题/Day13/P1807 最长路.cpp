//
// Created by 28447 on 2026/8/25.
//
#include<bits/stdc++.h>  // 万能头文件，包含所有标准库
using namespace std;

const int N = 1505;        // 最大节点数
const int INF = -1e9;      // 负无穷，表示不可达

int n, m;                  // n: 节点数, m: 边数
int in[N];                 // in[i] 表示节点i的入度（有多少条边指向i）
vector<int> g[N], d[N];    // g[i] 存储从i出发的所有边的终点
// d[i] 存储从i出发的所有边的权值
int dp[N];                 // dp[i] 表示从起点1到节点i的最长路径长度

int main() {
    // 1. 输入数据
    cin >> n >> m;

    for(int i = 1; i <= m; i++) {
        int u, v, w;       // u: 起点, v: 终点, w: 边权
        cin >> u >> v >> w;
        g[u].push_back(v); // 将终点v加入u的邻接表
        d[u].push_back(w); // 将边权w加入u的边权表
        in[v]++;           // 节点v的入度+1
    }

    // 2. 初始化dp数组
    for(int i = 1; i <= n; i++) {
        dp[i] = INF;       // 所有节点初始为不可达
    }
    dp[1] = 0;             // 起点到自己的距离为0

    // 3. 核心算法：利用 u < v 的性质，直接按编号顺序DP
    // 因为所有边都满足 u < v（起点编号小于终点编号）
    // 所以按编号从小到大处理，保证处理到节点u时，
    // 所有指向u的边都已经处理过了，dp[u]已经是最终值
    for(int u = 1; u <= n; u++) {
        // 如果节点u不可达，跳过（不能作为中间节点去更新其他节点）
        if(dp[u] == INF) continue;

        // 遍历从u出发的所有边
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];    // 取出终点v
            int w = d[u][i];    // 取出边权w

            // 松弛操作：如果通过u到达v的路径更长，就更新dp[v]
            // dp[u] + w 表示：从起点1到u的最长路径 + 边u→v的权值
            // 这代表从起点1出发，经过u，再到v的路径长度
            dp[v] = max(dp[v], dp[u] + w);
        }
    }

    // 4. 输出结果
    if(dp[n] == INF) {         // 如果节点n不可达
        cout << -1 << endl;    // 输出-1
    } else {
        cout << dp[n] << endl; // 否则输出最长路径长度
    }

    return 0;
}