//
// Created by 28447 on 2026/8/26.
//
#include <bits/stdc++.h>
using namespace std;
const int mN=1e4+9, mM=5e4+9;
int n, m;
int oe=1, head[mN], nxt[mM<<1], ver[mM<<1];
bool used[mM];  //边是否被遍历过
inline void add(int x, int y) {nxt[++oe]=head[x], ver[oe]=y, head[x]=oe;}

bool vis[mN];   //点是否被遍历过
void dfs(int x) {
    printf("%d\n", x), vis[x]=1;    //第一次遍历到点 x，标记并且输出路径
    for(int t=head[x]; t; t=nxt[t]) if(!used[t>>1]) {
        used[t>>1]=1;
        if(!vis[ver[t]]) dfs(ver[t]), printf("%d\n", x);  //点未被遍历过，是树边，去 dfs 另一个点
        else printf("%d\n%d\n", ver[t], x); //点被遍历过，是非树边，去一次再回来
    }
}

int main() {
    scanf("%d%d", &n, &m);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    return 0;
}
