//
// Created by 28447 on 2026/8/27.
//-状压 DP
/*在 𝑁 ×𝑁
N\times N 的棋盘里面放 𝐾
K 个国王(1 ≤𝑁 ≤9,1 ≤𝐾 ≤𝑁 ×𝑁 )，使他们互不攻击，共有多少种摆放方案．

国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共 8 个格子．*/
#include <algorithm>
#include <iostream>
using namespace std;
long long sta[2005], sit[2005], f[15][2005][105];
int n, k, cnt;

void dfs(int x, int num, int cur) {
    if (cur >= n) {  // 有新的合法状态
        sit[++cnt] = x;
        sta[cnt] = num;
        return;
    }
    dfs(x, num, cur + 1);  // cur位置不放国王
    dfs(x + (1 << cur), num + 1,
        cur + 2);  // cur位置放国王，与它相邻的位置不能再放国王
}

bool compatible(int j, int x) {
    if (sit[j] & sit[x]) return false;
    if ((sit[j] << 1) & sit[x]) return false;
    if (sit[j] & (sit[x] << 1)) return false;
    return true;
}

int main() {
    cin >> n >> k;
    dfs(0, 0, 0);  // 先预处理一行的所有合法状态
    for (int j = 1; j <= cnt; j++) f[1][j][sta[j]] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= cnt; j++)
            for (int x = 1; x <= cnt; x++) {
                if (!compatible(j, x)) continue;  // 排除不合法转移-》直接跳过
                for (int l = sta[j]; l <= k; l++) f[i][j][l] += f[i - 1][x][l - sta[j]];
            }//f(i,j,l) 表示前i行，第i行的状态为 𝑗j，且棋盘上已经放置l个国王时的合法方案数
    long long ans = 0;
    for (int i = 1; i <= cnt; i++) ans += f[n][i][k];  // 累加答案
    cout << ans << endl;
    return 0;
}