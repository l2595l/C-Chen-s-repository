//
// Created by 28447 on 2026/9/2.
//
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#define ll long long
using namespace std;

// ============================================================
// 1. 棋盘状态定义
// ============================================================

char currentBoard[5][5];   // 当前棋盘 (1-based索引)
char targetBoard[5][5];    // 目标棋盘 (1-based索引)

// ============================================================
// 2. 路径记录 (存储每一步的交换操作)
// ============================================================

struct Move {
    int x1, y1;  // 第一个格子的行列 (1-based)
    int x2, y2;  // 第二个格子的行列 (1-based)
};

Move path[1000000];  // 存储搜索过程中的每一步操作

// ============================================================
// 3. 状态去重
// ============================================================

map<ll, bool> visited;  // 记录已访问的状态 (key: 编码后的17位整数)

// ============================================================
// 4. 核心函数
// ============================================================

/**
 * 检查当前棋盘是否等于目标棋盘
 */
bool isTarget() {
    for(int i = 1; i <= 4; i++)
        for(int j = 1; j <= 4; j++)
            if(currentBoard[i][j] != targetBoard[i][j])
                return false;
    return true;
}

/**
 * 启发式估价函数: 估算从当前状态到目标状态至少还需要多少步
 *
 * 原理：
 *   - 统计位置错误的棋子数量 diffCount
 *   - 每次交换最多让 2 个棋子归位
 *   - 所以至少需要 ceil(diffCount / 2) 步
 *
 * @return 乐观估计的剩余步数 (一定 <= 实际步数)
 */
int heuristic() {
    int diffCount = 0;
    for(int i = 1; i <= 4; i++)
        for(int j = 1; j <= 4; j++)
            if(currentBoard[i][j] != targetBoard[i][j])
                diffCount++;

    return (diffCount + 1) / 2;  // 向上取整
}

/**
 * 将当前棋盘编码为唯一的17位整数
 *
 * 编码格式：
 *   [ 深度信息 (1位) ] [ 16个格子的值 (16位) ]
 *
 * 为什么最高位是 deep+1 而不是 deep？
 *   - 防止前导零丢失信息 (如果 deep=0，加1后变成1)
 *   - 保证不同深度 + 不同棋盘 → 不同编码
 *
 * @param depth 当前搜索深度
 * @return 唯一的状态编码
 */
/**
 * 状态编码说明:
 *
 * 1. 棋盘有16个格子, 每个格子0或1 → 直接拼接会得到16位二进制数
 * 2. 但全0棋盘拼接后是0, 无法与"空编码"区分 → 需要加前导非零数字
 * 3. 用 depth+1 作为前导数字, 同时记录深度信息, 一举两得
 * 4. 10进制拼接相当于把16个0/1字符转成整数, 便于作为 map 的 key
 */
ll encodeState(int depth) {
    ll code = depth + 1;  // 最高位存储深度+1

    // 拼接16个格子的值 (0或1)
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            code = code * 10 + (currentBoard[i][j] - '0');//十进制
        }
    }
    return code;
}

/**
 * 尝试交换两个相邻格子 (仅当颜色不同时才有意义)
 *
 * @param x1 格子1的行
 * @param y1 格子1的列
 * @param x2 格子2的行
 * @param y2 格子2的列
 * @return 交换是否成功 (颜色相同则返回false)
 */
bool trySwap(int x1, int y1, int x2, int y2) {
    // 检查边界
    if(x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4) return false;
    if(x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4) return false;

    // 只有颜色不同时交换才有意义
    if(currentBoard[x1][y1] == currentBoard[x2][y2]) return false;

    swap(currentBoard[x1][y1], currentBoard[x2][y2]);
    return true;
}

/**
 * IDA* 深度优先搜索
 *
 * @param depth      当前已走的步数
 * @param maxDepth   本次搜索允许的最大步数
 * @return           是否找到解
 */
bool dfs(int depth, int maxDepth) {
    // ----- 1. 状态去重 (记录当前状态已访问) -----
    visited[encodeState(depth)] = true;

    // ----- 2. A* 剪枝: 如果注定无法在限制步数内到达，则剪枝 -----
    if(depth + heuristic() > maxDepth) {
        return false;
    }

    // ----- 3. 检查是否到达目标 -----
    if(isTarget()) {
        return true;
    }

    // ----- 4. 枚举所有可能的交换操作 -----
    // 优化: 只枚举 "向右" 和 "向下"，避免重复搜索
    // 理由: 向左交换 = 左邻居的向右交换，向上交换 = 上邻居的向下交换
    for(int row = 1; row <= 4; row++) {
        for(int col = 1; col <= 4; col++) {

            // 4.1 向右交换: (row, col) <-> (row, col+1)
            if(col + 1 <= 4) {
                if(trySwap(row, col, row, col + 1)) {
                    ll nextState = encodeState(depth + 1);

                    if(!visited[nextState]) {
                        // 记录当前操作
                        path[depth] = {row, col, row, col + 1};

                        // 递归搜索
                        if(dfs(depth + 1, maxDepth)) {
                            return true;
                        }
                    }

                    // 回溯: 恢复棋盘
                    trySwap(row, col, row, col + 1);  // 再次交换即恢复原状
                }
            }

            // 4.2 向下交换: (row, col) <-> (row+1, col)
            if(row + 1 <= 4) {
                if(trySwap(row, col, row + 1, col)) {
                    ll nextState = encodeState(depth + 1);

                    if(!visited[nextState]) {
                        path[depth] = {row, col, row + 1, col};

                        if(dfs(depth + 1, maxDepth)) {
                            return true;
                        }
                    }

                    // 回溯
                    trySwap(row, col, row + 1, col);
                }
            }
        }
    }

    return false;  // 所有分支都无法到达目标
}

/**
 * 迭代加深 + A* 搜索 (IDA*)
 *
 * 过程：
 *   1. 从 maxDepth = 1 开始，逐步增加搜索深度
 *   2. 每次在限制深度内尝试搜索
 *   3. 如果找不到，清空历史记录，增加深度继续
 *   4. 第一次找到解时，一定是最短路径
 *
 * @return 最短步数
 */
int solve() {
    // 如果已经到达目标，步数为0
    if(isTarget()) return 0;

    int maxDepth = 1;
    while(!dfs(0, maxDepth)) {
        maxDepth++;          // 扩大搜索深度限制
        visited.clear();     // 清空历史 (不同深度需要重新探索)
    }

    return maxDepth;
}

/**
 * 输出操作序列
 *
 * @param totalSteps 总步数
 */
void printPath(int totalSteps) {
    printf("%d\n", totalSteps);
    for(int i = 0; i < totalSteps; i++) {
        // 输出格式: 行1 列1 行2 列2 (都是1-based)
        printf("%d%d%d%d\n",
               path[i].x1, path[i].y1,
               path[i].x2, path[i].y2);
    }
}

// ============================================================
// 5. 主函数
// ============================================================

int main() {
    // ----- 读取输入 -----
    // 初始棋盘 (4行，每行4个字符)
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            cin >> currentBoard[i][j];
        }
    }

    // 目标棋盘
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            cin >> targetBoard[i][j];
        }
    }

    // ----- 求解 -----
    int totalSteps = solve();

    // ----- 输出 -----
    printPath(totalSteps);

    return 0;
}