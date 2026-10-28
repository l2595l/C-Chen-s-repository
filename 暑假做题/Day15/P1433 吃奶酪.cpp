//
// Created by 28447 on 2026/8/27.
//
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>  // 使用 std::min 替代宏定义

using namespace std;

const int MAXN = 15;        // 最大奶酪数量
const double INF = 1e9;     // 无穷大值

double x[MAXN + 5], y[MAXN + 5];// 坐标数组，0号点是原点
double dist[MAXN + 5][MAXN + 5];// dist[i][j]：点i到点j的距离
double dp[1 << MAXN][MAXN + 5]; // dp[mask][i]：已访问集合mask（以二进制位表示哪些点被访问了），当前在点i的最短距离
int n;

/**
 * 计算两点之间的欧几里得距离
 */
double calcDist(int i, int j) {
    double dx = x[i] - x[j];
    double dy = y[i] - y[j];
    return sqrt(dx * dx + dy * dy);
}

int main() {
    // 1. 输入数据
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    x[0] = 0.0; y[0] = 0.0;  // 原点

    // 2. 预处理所有点对之间的距离
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dist[i][j] = calcDist(i, j);
        }
    }

    // 3. 初始化DP数组为无穷大
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i <= n; i++) {
            dp[mask][i] = INF;
        }
    }

    // 4. 初始化：从原点(0)出发，只访问第i个点
    for (int i = 1; i <= n; i++) {
        dp[1 << (i - 1)][i] = dist[0][i];
    }

    // 5. 状态压缩DP
    // 枚举所有访问状态（mask的二进制位表示哪些点已被访问）
    for (int mask = 1; mask < (1 << n); mask++) {
        // 枚举当前所在的点 i
        for (int i = 1; i <= n; i++) {
            // 如果 i 不在 mask 中，跳过（当前点必须在已访问集合中）
            if (!(mask & (1 << (i - 1)))) continue;
            if (dp[mask][i] == INF) continue;  // 剪枝

            // 尝试从 i 走到下一个未访问的点 j
            for (int j = 1; j <= n; j++) {
                // 如果 j 已经在 mask 中，跳过（不能重复访问）
                if (mask & (1 << (j - 1))) continue;

                int nextMask = mask | (1 << (j - 1));
                // 状态转移：从 (mask, i) 走到 j，更新 (nextMask, j)
                dp[nextMask][j] = min(dp[nextMask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }

    // 6. 从所有点中找出答案：访问完所有点后的最短距离
    int fullMask = (1 << n) - 1;
    double ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[fullMask][i]);
    }

    // 7. 输出结果，保留2位小数
    printf("%.2f\n", ans);
    return 0;
}