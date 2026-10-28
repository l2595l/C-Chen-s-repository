//
// Created by 28447 on 2026/9/6.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    if (N % 4 != 0) {
        cout << -1 << "\n";
        return 0;
    }

    int blocks = N / 4;
    // 每个 2x2 方块占 2 行 2 列，间隔至少 1 行/列
    int rows = 1;      // 至少 1 行
    int cols = 1;
    // 简单起见，每行放最多 10 个方块，方便计算
    int perRow = 10;
    int numRows = (blocks + perRow - 1) / perRow;
    rows = numRows * 3;   // 每个方块占2行+1间隔
    cols = perRow * 3;    // 每行10个，每个占2列+1间隔

    // 限制在 1000 以内
    rows = min(rows, 1000);
    cols = min(cols, 1000);

    vector<string> grid(rows, string(cols, '0'));

    int placed = 0;
    for (int r = 0; r < rows && placed < blocks; r += 3) {
        for (int c = 0; c < cols && placed < blocks; c += 3) {
            if (r + 1 < rows && c + 1 < cols) {
                grid[r][c] = '1';
                grid[r][c+1] = '1';
                grid[r+1][c] = '1';
                grid[r+1][c+1] = '1';
                placed++;
            }
        }
    }

    cout << rows << " " << cols << "\n";
    for (auto &s : grid) {
        cout << s << "\n";
    }

    return 0;
}