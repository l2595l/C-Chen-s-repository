//
// Created by 28447 on 2026/8/30.
/*
///dfs(1)
 开始放第1行
  ├─ 尝试 col=1: 合法 ✓
  │   ├─ 放置 (1,1)
  │   ├─ dfs(2)
  │   │   ├─ 尝试 col=1: check[0][1]已被占用 ✗
  │   │   ├─ 尝试 col=2: 副对角线冲突 ✗
  │   │   ├─ 尝试 col=3: 合法 ✓
  │   │   │   ├─ 放置 (2,3)
  │   │   │   ├─ dfs(3)
  │   │   │   │   ├─ 尝试 col=1: 主对角线冲突 ✗
  │   │   │   │   ├─ 尝试 col=2: 副对角线冲突 ✗
  │   │   │   │   ├─ 尝试 col=4: 合法 ✓
  │   │   │   │   │   ├─ 放置 (3,4)
  │   │   │   │   │   ├─ dfs(4)
  │   │   │   │   │   │   ├─ 尝试 col=2: 合法 ✓
  │   │   │   │   │   │   │   ├─ 放置 (4,2)
  │   │   │   │   │   │   │   ├─ dfs(5) → line>n, 输出解 {1,3,4,2}
│   │   │   │   │   │   │   └─ 回溯
│   │   │   │   │   │   └─ 继续尝试...
│   │   │   │   │   └─ 回溯
│   │   │   │   └─ 回溯
│   │   │   └─ 回溯
│   │   └─ 继续尝试...
│   └─ 回溯
└─ 继续尝试 col=2...
*/
#include<cstdio>
#include<iostream>
using namespace std;

/**
 * N皇后问题 - 求解所有解，输出前3组
 *
 * 算法：回溯法（DFS）+ 剪枝
 * 时间复杂度：O(n!)
 * 空间复杂度：O(n)
 */

const int MAXN = 14;           // 最大棋盘大小（可根据题目调整）
const int MAX_DIAG = 28;       // 对角线数组大小 (2*MAXN)

int queen_pos[MAXN];           // queen_pos[row] = col，第row行皇后在第col列
bool conflict[3][MAX_DIAG];    // 冲突标记数组
                               // conflict[0][col]：列是否被占用
                               // conflict[1][row+col]：主对角线是否被占用
                               // conflict[2][row-col+n]：副对角线是否被占用

int solution_count = 0;        // 已找到的解的总数
int board_size;                // 棋盘大小 n

/**
 * 深度优先搜索 - 逐行放置皇后
 * @param row 当前要放置皇后的行号 (1-based)
 */
void dfs(int row) {
    // ===== 递归终止条件：所有行都已放置皇后 =====
    if (row > board_size) {
        solution_count++;  // 找到一个有效解

        // 只输出前3组解
        if (solution_count <= 3) {
            for (int col = 1; col <= board_size; col++) {
                printf("%d ", queen_pos[col]);
            }
            printf("\n");
        }
        return;
    }

    // ===== 尝试在当前行的每一列放置皇后 =====
    for (int col = 1; col <= board_size; col++) {
        // 检查三个冲突条件：
        // 1. 第col列是否已有皇后
        // 2. 主对角线 (row+col) 是否已被占用
        // 3. 副对角线 (row-col+board_size) 是否已被占用
        if (!conflict[0][col] &&
            !conflict[1][row + col] &&
            !conflict[2][row - col + board_size]) {

            // ----- 放置皇后 -----
            queen_pos[row] = col;
            conflict[0][col] = true;
            conflict[1][row + col] = true;
            conflict[2][row - col + board_size] = true;

            // 递归搜索下一行
            dfs(row + 1);

            // ----- 回溯：移除皇后 -----
            conflict[0][col] = false;
            conflict[1][row + col] = false;
            conflict[2][row - col + board_size] = false;
        }
    }
}

int main() {
    // 读入棋盘大小
    scanf("%d", &board_size);

    // 初始化冲突标记数组（全局变量默认已初始化为0）
    // 但为了代码清晰，显式初始化
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < MAX_DIAG; j++) {
            conflict[i][j] = false;
        }
    }

    // 从第1行开始搜索
    dfs(1);

    // 输出总解数
    printf("%d\n", solution_count);

    return 0;
}
// /*增加剪枝
// #include<cstdio>
// #include<iostream>
// using namespace std;
//
// const int MAXN = 14;
// const int MAX_DIAG = 28;
//
// int queen_pos[MAXN];
// bool conflict[3][MAX_DIAG];
// int solution_count = 0;
// int board_size;
// */
// /*
//  * 检查在第row行第col列放置皇后是否合法
//  * 内联函数，提高性能
//  */
// inline bool can_place(int row, int col) {
//     return !conflict[0][col] &&
//            !conflict[1][row + col] &&
//            !conflict[2][row - col + board_size];
// }
//
// /**
//  * 放置皇后并更新冲突标记
//  */
// inline void place_queen(int row, int col) {
//     queen_pos[row] = col;
//     conflict[0][col] = true;
//     conflict[1][row + col] = true;
//     conflict[2][row - col + board_size] = true;
// }
//
// /**
//  * 移除皇后并恢复冲突标记（回溯）
//  */
// inline void remove_queen(int row, int col) {
//     conflict[0][col] = false;
//     conflict[1][row + col] = false;
//     conflict[2][row - col + board_size] = false;
// }
//
// /**
//  * 输出一组解
//  */
// inline void print_solution() {
//     for (int col = 1; col <= board_size; col++) {
//         printf("%d ", queen_pos[col]);
//     }
//     printf("\n");
// }
//
// void dfs(int row) {
//     // 剪枝：如果前几行已经不可能构成有效解，提前返回
//     // （N皇后问题的对称性剪枝可以在这里加入）
//
//     if (row > board_size) {
//         solution_count++;
//         if (solution_count <= 3) {
//             print_solution();
//         }
//         return;
//     }
//
//     for (int col = 1; col <= board_size; col++) {
//         if (can_place(row, col)) {
//             place_queen(row, col);
//             dfs(row + 1);
//             remove_queen(row, col);
//         }
//     }
// }
//
// int main() {
//     scanf("%d", &board_size);
//
//     // 初始化（全局变量默认0，但显式初始化更安全）
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < MAX_DIAG; j++) {
//             conflict[i][j] = false;
//         }
//     }
//
//     dfs(1);
//     printf("%d\n", solution_count);
//     return 0;
// }
// */