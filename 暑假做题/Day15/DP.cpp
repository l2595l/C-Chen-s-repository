//
// Created by 28447 on 2026/8/27.
//
/*// 1. 定义缓存数组
int memo[N][M];  // 维度根据状态而定

// 2. DFS函数
int dfs(状态参数) {
// 3. 查缓存（记忆化）
if (memo[状态] != -1)
return memo[状态];

// 4. 递归边界
if (边界条件)
return memo[状态] = 边界值;

// 5. 状态转移 + 存缓存
int ans = 初始值;
for (所有可能的决策) {
ans = max/min/累加(ans, dfs(下一个状态) + 代价);
}
return memo[状态] = ans;
}

// 6. 主函数初始化
int main() {
memset(memo, -1, sizeof(memo));  // 用 -1 表示未计算
cout << dfs(初始状态) << endl;
}*/