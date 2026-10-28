//
// Created by 28447 on 2026/8/19.
//
//优化版用*阻碍且一维数组
#include <bits/stdc++.h>
using namespace std;

// 方向：上 右 下 左
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 一维数组优化内存和访问速度
    int cols = m + 2;
    vector<char> g((n + 2) * cols, '*');

    // 预计算甜度值（优化1：预计算）
    vector<int> val((n + 2) * cols, 0);
    //坐标计算
    auto idx = [&](int x, int y) {
        return x * cols + y;
    };

    // 读入数据
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            g[idx(i, j)] = ch;
            // 预计算甜度
            if (ch >= 'A' && ch <= 'Z') {
                val[idx(i, j)] = ch - 'A' + 1;
            } else {
                val[idx(i, j)] = -(ch - 'a' + 1);
            }
        }
    }

    int sx, sy;
    cin >> sx >> sy;

    int x = sx, y = sy;
    int sweetness = val[idx(x, y)];

    // 起点就负数
    if (sweetness < 0) {
        cout << sweetness << " " << x << " " << y << "\n";
        return 0;
    }

    // 标记起点为已访问（变成障碍）
    g[idx(x, y)] = '*';

    // 模拟移动
    while (true) {
        bool moved = false;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 如果是障碍（边界或已访问），跳过
            if (g[idx(nx, ny)] == '*') continue;

            // 甜度检查（直接用预计算的值）
            if (sweetness + val[idx(nx, ny)] < 0) continue;

            // 移动
            x = nx;
            y = ny;
            sweetness += val[idx(x, y)];
            g[idx(x, y)] = '*';  // 标记已访问
            moved = true;
            break;
        }

        if (!moved) break;
    }

    cout << sweetness << " " << x << " " << y << "\n";
    return 0;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// #include <bits/stdc++.h>
// using namespace std;
//
// const int dx[4] = {-1, 0, 1, 0};  // 上 右 下 左
// const int dy[4] = {0, 1, 0, -1};
//
// int getValue(char ch) {
//     if (ch >= 'A' && ch <= 'Z') {
//         return ch - 'A' + 1;
//     } else {
//         return -(ch - 'a' + 1);
//     }
// }
//
// int main() {
//     int n, m;
//     cin >> n >> m;
//
//     // 用 vector 更好，因为 n,m 最大 5000，栈上可能不够
//     vector<vector<char>> g(n+2, vector<char>(m+2, '*'));
//     vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));
//
//     // 读入数据（注意：从 1 开始存储，方便处理边界）
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= m; j++) {
//             cin >> g[i][j];
//         }
//     }
//
//     int sx, sy;
//     cin >> sx >> sy;
//
//     // 起点处理
//     visited[sx][sy] = true;
//     int currentX = sx, currentY = sy;
//     int sweetness = getValue(g[sx][sy]);
//
//     // 如果起点吃完就负数，直接结束
//     if (sweetness < 0) {
//         cout << sweetness << " " << sx << " " << sy << endl;
//         return 0;
//     }
//
//     // 模拟移动
//     while (true) {
//         bool moved = false;
//
//         // 按顺序尝试四个方向：上 右 下 左
//         for (int dir = 0; dir < 4; dir++) {
//             int nx = currentX + dx[dir];
//             int ny = currentY + dy[dir];
//
//             // 条件1：在范围内
//             if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
//
//             // 条件2：未访问过
//             if (visited[nx][ny]) continue;
//
//             // 条件3：甜度不会变负
//             int targetValue = getValue(g[nx][ny]);
//             if (sweetness + targetValue < 0) continue;
//
//             // 满足所有条件，移动
//             moved = true;
//             currentX = nx;
//             currentY = ny;
//             sweetness += targetValue;
//             visited[nx][ny] = true;
//             break;  // 找到第一个可行方向就移动
//         }
//
//         // 如果四个方向都不可行，停止
//         if (!moved) break;
//     }
//
//     // 输出结果
//     cout << sweetness << " " << currentX << " " << currentY << endl;
//
//     return 0;
// }