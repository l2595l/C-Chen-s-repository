//
// Created by 28447 on 2026/10/14.
//
#include <iostream>
#include <queue>
#include <array>
#include <unordered_set>
// #include<bits/stdc++.h>
// 经典「八数码」问题：3x3 滑块拼图，0 表示空格。
// 输入：9 个字符，无分隔符，按行优先给出初始布局（例如 283104765）。
// 输出：从初始布局到目标布局所需的最少移动步数。
using namespace std;

constexpr int kBoardSize = 3;
using Grid = std::array<std::array<int, kBoardSize>, kBoardSize>;//数组大小

// 目标布局：
// 1 2 3
// 8 0 4
// 7 6 5
const Grid kTarget = {{
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
}};

// 空格的四个移动方向：下、右、上、左
constexpr int kDeltaRow[4] = {1, 0, -1, 0};
constexpr int kDeltaCol[4] = {0, 1, 0, -1};

struct State {
    Grid grid;
    int blankRow;
    int blankCol;
    int steps;
};
//状态压缩
// 把棋盘编码为唯一整数（九进制，每格一位数字），用于判重。
// 相比原来的 9 维布尔数组，内存占用从约 387MB 降到仅存储实际访问过的状态。
int Encode(const Grid& grid) {
    int code = 0;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            code = code * 9 + grid[r][c];
        }
    }
    return code;
}

bool IsGoal(const Grid& grid) {
    return grid == kTarget;
}

// 广度优先搜索：按步数逐层扩展，第一次遇到目标布局时的步数即为最少步数。
int Bfs(const State& start) {
    if (IsGoal(start.grid)) {
        return 0;
    }

    std::queue<State> q;
    std::unordered_set<int> visited;

    q.push(start);
    visited.insert(Encode(start.grid));

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nr = current.blankRow + kDeltaRow[dir];
            int nc = current.blankCol + kDeltaCol[dir];
            if (nr < 0 || nr >= kBoardSize || nc < 0 || nc >= kBoardSize) {
                continue;
            }

            State next = current;
            std::swap(next.grid[current.blankRow][current.blankCol], next.grid[nr][nc]);
            next.blankRow = nr;
            next.blankCol = nc;
            next.steps = current.steps + 1;

            int code = Encode(next.grid);
            if (visited.count(code)) {
                continue;
            }
            visited.insert(code);

            if (IsGoal(next.grid)) {
                return next.steps;
            }
            q.push(next);
        }
    }

    return -1; // 理论上八数码问题若有解必定能找到，这里仅作防御性返回。
}

int main() {
    State start;
    start.steps = 0;

    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            char ch;
            std::cin >> ch;
            start.grid[r][c] = ch - '0';
            if (start.grid[r][c] == 0) {
                start.blankRow = r;
                start.blankCol = c;
            }
        }
    }

    std::cout << Bfs(start) << std::endl;
    return 0;
}
