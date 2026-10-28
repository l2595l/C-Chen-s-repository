//
// Created by 28447 on 2026/8/23.
//
// 题意：给定 01 矩阵，求最大的「正十字」（加号）的半径 k。
//       即以某点为中心，上下左右四个方向各有 k 个连续的 1（中心也算）。
// 做法：对每个 1 点，半径 = min(上、下、左、右连续 1 的长度) - 1，取全局最大。
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3+5;

string g[MAXN];         // 01 矩阵，每行一个字符串
int v[MAXN][MAXN];      // v[i][j] = min(向上连续1数, 向下连续1数) —— 竖直方向的最小臂长
int L[MAXN], R[MAXN];   // 当前行的向左/向右连续 1 数（一维，逐行滚动）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> g[i];   // 读入整个矩阵（用 string 存，省内存）


    // 1) 向上连续 1 的长度（暂时存进 v）
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            v[i][j] = (g[i][j - 1] == '1') ? v[i - 1][j] + 1 : 0;

    // 2) 向下连续 1 的长度，并立刻与向上取 min，合成竖直方向最小臂长
    //    d[j] 滚动记录「下一行向下连续 1 的长度」，全局数组初值为 0（对应第 n+1 行）
    int d[MAXN] = {0};
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++) {
            d[j] = (g[i][j - 1] == '1') ? d[j] + 1 : 0;
            v[i][j] = min(v[i][j], d[j]);
        }

    // 3) 逐行算向左/向右连续 1 数（一维即可），并直接求答案
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)      // 向左
            L[j] = (g[i][j - 1] == '1') ? L[j - 1] + 1 : 0;
        for (int j = m; j >= 1; j--)      // 向右
            R[j] = (g[i][j - 1] == '1') ? R[j + 1] + 1 : 0;
        for (int j = 1; j <= m; j++)      // 该行每个 1 点求十字半径
            if (g[i][j - 1] == '1')
                ans = max(ans, min({v[i][j], L[j], R[j]}) - 1);
    }

    cout << ans << '\n';
    return 0;
}
