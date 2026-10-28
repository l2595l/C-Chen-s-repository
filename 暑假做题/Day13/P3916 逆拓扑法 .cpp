//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int N, M;
vector<int> G[MAXN];  // 正向建边
int in[MAXN];         // 入度
int A[MAXN];          // 结果

int main() {
    scanf("%d%d", &N, &M);

    // 正向建边
    for(int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        in[v]++;
    }

    // 1. 拓扑排序
    queue<int> q;
    vector<int> topo;

    for(int i = 1; i <= N; i++) {
        if(in[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);

        for(int v : G[u]) {
            in[v]--;
            if(in[v] == 0) q.push(v);
        }
    }

    // 如果有环，拓扑序长度小于N
    if(topo.size() < N) {
        printf("图中有环，无法计算\n");
        return 0;
    }

    // 2. 初始化
    for(int i = 1; i <= N; i++) {
        A[i] = i;  // 至少能到达自己
    }

    // 3. 逆拓扑序DP（从后往前）
    for(int i = topo.size() - 1; i >= 0; i--) {
        int u = topo[i];
        for(int v : G[u]) {
            A[u] = max(A[u], A[v]);
        }
    }

    // 4. 输出结果
    for(int i = 1; i <= N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}