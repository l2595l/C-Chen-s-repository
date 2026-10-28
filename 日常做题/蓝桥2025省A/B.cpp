//
// Created by 28447 on 2026/10/19.
//
// P12139 [蓝桥杯 2025 省 A] 黑白棋
// 逐格 DFS + 三条剪枝，找到解就返回
#include <bits/stdc++.h>
using namespace std;

const int N = 6, HALF = 3, TOTAL = N * N;

int init[N][N];                 // 初盘: 0=空, 1=黑, 2=白
int g[N][N];                    // 当前盘面
int ans[N][N];                  // 最终答案（找到解后整体拷出来，别在回溯里清掉）
int rowCnt[N][3], colCnt[N][3];
long long nodes = 0;

// 剪枝 1+2：行内黑/白不超过 3，且不能出现连续三同色
inline bool rowOk(int r, int c, int v) {
    if (rowCnt[r][v] > HALF) return false;
    if (c >= 2 && g[r][c - 1] == v && g[r][c - 2] == v) return false;
    return true;
}
// 剪枝 1+2：列方向同理
inline bool colOk(int r, int c, int v) {
    if (colCnt[c][v] > HALF) return false;
    if (r >= 2 && g[r - 1][c] == v && g[r - 2][c] == v) return false;
    return true;
}

// 填满之后：每行每列黑白各 3，且行、列各自互不相同
bool finalCheck() {
    for (int i = 0; i < N; i++)
        if (rowCnt[i][1] != HALF || colCnt[i][1] != HALF) return false;

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            bool same = true;
            for (int k = 0; k < N; k++)
                if (g[i][k] != g[j][k]) { same = false; break; }
            if (same) return false;                 // 第 i 行 == 第 j 行

            same = true;
            for (int k = 0; k < N; k++)
                if (g[k][i] != g[k][j]) { same = false; break; }
            if (same) return false;                 // 第 i 列 == 第 j 列
        }
    return true;
}

bool dfs(int pos) {
    if (pos == TOTAL) {
        if (!finalCheck()) return false;
        memcpy(ans, g, sizeof g);
        return true;
    }
    int r = pos / N, c = pos % N;
    int lo = 1, hi = 2;
    if (init[r][c]) lo = hi = init[r][c];           // 初盘已给定就只能填它

    for (int v = lo; v <= hi; v++) {
        g[r][c] = v;
        rowCnt[r][v]++; colCnt[c][v]++;
        bool ok = rowOk(r, c, v) && colOk(r, c, v);
        if (ok) {
            nodes++;
            if (dfs(pos + 1)) return true;
        }
        rowCnt[r][v]--; colCnt[c][v]--;
        g[r][c] = 0;
    }
    return false;
}

int main() {
    // 读入 6 行初盘：'*' 空，'#'/'B' 黑，'O'/'W'/'0' 白
    for (int i = 0; i < N; i++) {
        string s="1010*****0*****100********1**1*0**1*";
        // if (!(cin >> s)) break;
        for (int j = 0; j < N && j < (int)s.size(); j++) {
            char ch = s[j];
            if (ch == '#' || ch == 'B' || ch == '1') init[i][j] = 1;
            else if (ch == 'O' || ch == 'W' || ch == '0') init[i][j] = 2;
            else init[i][j] = 0;
            // 注意：这里只记 init，不要顺手填 g / rowCnt / colCnt
            // 否则 dfs 里再 ++ 一次就重复计数了（我第一次写就是这么错的）
        }
    }

    if (!dfs(0)) { puts("no solution"); return 0; }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) putchar(ans[i][j] == 1 ? '#' : 'O');
        putchar('\n');
    }
    fprintf(stderr, "nodes=%lld\n", nodes);
    return 0;
}
