//
// Created by 28447 on 2026/10/15.
//
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>

// 八数码问题（IDA*：迭代加深 + 估价函数剪枝）。
// 输入：9 个字符，无分隔符，按行优先给出初始布局（例如 283104765），0 表示空格。
// 输出：到达目标布局的最少移动步数；若无解输出 -1。

constexpr int kBoardSize = 3;
using Grid = std::array<std::array<int, kBoardSize>, kBoardSize>;

// 目标布局：
// 1 2 3
// 8 0 4
// 7 6 5
const Grid kTarget = {{
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
}};

// 空格的四个移动方向：右、下、上、左。
// 方向 i 与方向 3 - i 互为反向，据此可以避免立刻走回头路。
constexpr int kDeltaRow[4] = {0, 1, -1, 0};
constexpr int kDeltaCol[4] = {1, 0, 0, -1};
constexpr int kNoDirection = -1;

// 统计与目标布局不同的格子数（空格所在格也计入）。
int CountMismatches(const Grid& grid) {
    int count = 0;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (grid[r][c] != kTarget[r][c]) {
                ++count;
            }
        }
    }
    return count;
}

// 按行优先展开后，非 0 数字的逆序对数。
int CountInversions(const Grid& grid) {
    std::array<int, kBoardSize * kBoardSize> flat{};
    int n = 0;
    for (const auto& row : grid) {
        for (int value : row) {
            if (value != 0) {
                flat[n++] = value;
            }
        }
    }
    int inversions = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (flat[i] > flat[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

// 棋盘宽度为奇数时，逆序对奇偶性相同的两个布局才能互相到达。
bool IsSolvable(const Grid& grid) {
    return CountInversions(grid) % 2 == CountInversions(kTarget) % 2;
}

class IdaSolver {
public:
    IdaSolver(const Grid& start, int blankRow, int blankCol)
        : grid_(start), blankRow_(blankRow), blankCol_(blankCol) {}

    // 逐步放宽深度上限，第一个能到达目标的上限即为最少步数。
    // 调用前需确认局面有解，否则循环不会结束。
    int Solve() {
        if (grid_ == kTarget) {
            return 0;
        }
        for (depthLimit_ = 1;; ++depthLimit_) {
            if (Dfs(0, blankRow_, blankCol_, kNoDirection)) {
                return depthLimit_;
            }
        }
    }

private:
    bool Dfs(int step, int row, int col, int prevDir) {
        if (step == depthLimit_) {
            return grid_ == kTarget;
        }
        for (int dir = 0; dir < 4; ++dir) {
            if (prevDir != kNoDirection && dir == 3 - prevDir) {
                continue;  // 不走回头路
            }
            int nr = row + kDeltaRow[dir];
            int nc = col + kDeltaCol[dir];
            if (nr < 0 || nr >= kBoardSize || nc < 0 || nc >= kBoardSize) {
                continue;
            }

            std::swap(grid_[row][col], grid_[nr][nc]);
            // 走完这一步后还剩 remaining 步可用。
            // 一步只能让一个数字块归位，空格最多多贡献一个错位格，
            // 所以「错位格数 - 1」是剩余步数的下界，超出预算就剪枝。
            int remaining = depthLimit_ - (step + 1);
            bool found = CountMismatches(grid_) - 1 <= remaining &&
                         Dfs(step + 1, nr, nc, dir);
            std::swap(grid_[row][col], grid_[nr][nc]);
            if (found) {
                return true;
            }
        }
        return false;
    }

    Grid grid_;
    int blankRow_;
    int blankCol_;
    int depthLimit_ = 0;
};

int main() {
    std::string input;
    std::cin >> input;

    std::string sorted = input;
    std::sort(sorted.begin(), sorted.end());
    if (sorted != "012345678") {
        std::cerr << "输入必须是 0-8 各出现一次的 9 个字符\n";
        return 1;
    }

    Grid start{};
    int blankRow = 0;
    int blankCol = 0;
    for (int i = 0; i < kBoardSize * kBoardSize; ++i) {
        int r = i / kBoardSize;
        int c = i % kBoardSize;
        start[r][c] = input[i] - '0';
        if (start[r][c] == 0) {
            blankRow = r;
            blankCol = c;
        }
    }

    if (!IsSolvable(start)) {
        std::cout << -1 << std::endl;
        return 0;
    }

    IdaSolver solver(start, blankRow, blankCol);
    std::cout << solver.Solve() << std::endl;
    return 0;
}
