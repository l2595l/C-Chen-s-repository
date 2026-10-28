//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int N, M;
vector<int> G[MAXN];  // 反向建边：G[v]存储所有能到达v的节点
int A[MAXN];          // A[i]表示从i出发能到达的最大编号

void dfs(int x, int d) {
    if(A[x]) return;  // 已经访问过，直接返回
    A[x] = d;         // 记录从x出发能到达的最大编号是d

    for(int i = 0; i < G[x].size(); i++) {
        dfs(G[x][i], d);  // 递归访问所有能到达x的节点
    }
}

int main() {
    scanf("%d%d", &N, &M);

    // 反向建边
    for(int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[v].push_back(u);  // 反向建边：v -> u
    }

    // 从大到小遍历，保证大编号优先更新
    for(int i = N; i >= 1; i--) {
        dfs(i, i);
    }

    // 输出结果
    for(int i = 1; i <= N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
// #include <iostream>
// #include <cstdio>
// #include <vector>
// using namespace std;
//
// #define MAXL 100010
//
// int N, M, A[MAXL];
// vector<int> G[MAXL]; //vector存图
//
// void dfs(int x, int d) {
//     if(A[x]) return; //访问过
//     A[x] = d;
//     for(int i=0; i<G[x].size(); i++)
//         dfs(G[x][i], d);
// }
//
// int main() {
//     int u, v;
//     scanf("%d%d", &N, &M);
//     for(int i=1; i<=M; i++) {
//         scanf("%d%d", &u, &v);
//         G[v].push_back(u); //反向建边
//     }
//     for(int i=N; i; i--) dfs(i, i);
//     for(int i=1; i<=N; i++) printf("%d ", A[i]);
//     printf("\n");
//     return 0;
// }
