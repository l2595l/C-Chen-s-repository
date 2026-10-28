//
// Created by 28447 on 2026/10/19.
//

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3e5+5;
const LL MOD = 998244353;

int n;
vector<int> g[N];

// 状态定义（关键：任意两点距离必须 > 2）
//   dp[u][0] : u 不选，且 u 的儿子一个都不选
//   dp[u][1] : u 选
//   dp[u][2] : u 不选，且 u 的儿子中"恰好一个"被选（两个都在选 → 距离 2，非法）
LL dp[N][3];

void DFS(int u, int fa){
    dp[u][0] = 1;   // 空儿子集：不选、零个选中，1 种
    dp[u][1] = 1;   // u 选
    dp[u][2] = 0;   // 空儿子集：不可能已有选中，0 种

    for(int v : g[u]) if(v != fa){
        DFS(v, u);

        LL no   = dp[u][0];                 // 已处理儿子：都不选
        LL one  = dp[u][2];                 // 已处理儿子：恰好一个选
        LL free_= (dp[v][0] + dp[v][2]) % MOD;  // 儿子 v 不选（v 的儿子怎么选都行）

        dp[u][2] = (one * free_ + no * dp[v][1]) % MOD;  // 已有选中→v必须不选；还没有→v选
        dp[u][0] = no * free_ % MOD;
        dp[u][1] = dp[u][1] * dp[v][0] % MOD;            // u 选 → v 不选且 v 的儿子也不选
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    DFS(1, 0);
    LL ans = (dp[1][0] + dp[1][1] + dp[1][2] - 1) % MOD;
    ans = (ans % MOD + MOD) % MOD;   // 防止出现 -1
    printf("%lld\n", ans);
    return 0;
}
