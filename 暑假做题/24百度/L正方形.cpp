//
// Created by 28447 on 2026/9/13.
//
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    int N = n * n;

    // 无解判定
    if (k % 2 == 1) {
        cout << "No solution\n";
        return;
    }
    if (n == 2) {
        // n=2 时 0,2,4 都有解
        if (k == 0) {
            cout << "0 0\n0 0\n";
        } else if (k == 2) {
            cout << "1 0\n0 1\n";
        } else if (k == 4) {
            cout << "1 1\n1 1\n";
        } else {
            cout << "No solution\n";
        }
        return;
    }
    // n>=4
    if (k == 2 || k == N - 2) {
        cout << "No solution\n";
        return;
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (k == 0) {
        // 全0
    } else if (k == N) {
        // 全1
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = 1;
    } else if (k % 4 == 0) {
        // 用 k/4 个 2x2 块
        int cnt = k / 4;
        for (int i = 0; i < n && cnt > 0; i += 2) {
            for (int j = 0; j < n && cnt > 0; j += 2) {
                a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1;
                --cnt;
            }
        }
    } else {
        // k % 4 == 2，且 k >= 6
        // 先放一个 6 环在左上角 3x3
        if (n == 4 && k == 6) {
            // 特判 n=4, k=6
            a[0][2] = 1;
            a[1][2] = 1;
            a[2][0] = a[2][1] = a[2][2] = 1;
            a[3][3] = 1;
        } else if (n == 4 && k == 10) {
            // 特判 n=4, k=10
            a[0][0] = a[0][1] = a[0][2] = 1;
            a[1][0] = a[1][1] = a[1][2] = 1;
            a[2][0] = a[2][1] = a[2][2] = 1;
            a[3][3] = 1;
        } else {
            // 一般情况：6 环 + 2x2 块
            // 放 6 环
            a[0][0] = 1; a[0][2] = 1;
            a[1][0] = 1; a[1][1] = 1;
            a[2][1] = 1; a[2][2] = 1;
            int rem = k - 6; // 4 的倍数
            int cnt = rem / 4;
            // 从第 3 列开始找 2x2 位置（避开已占的 3x3）
            for (int i = 0; i < n && cnt > 0; i += 2) {
                for (int j = 0; j < n && cnt > 0; j += 2) {
                    // 检查 2x2 区域是否与已占的 3x3 冲突
                    bool ok = true;
                    for (int x = i; x <= i+1 && ok; ++x)
                        for (int y = j; y <= j+1 && ok; ++y)
                            if (x < 3 && y < 3) ok = false;
                    if (!ok) continue;
                    a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1;
                    --cnt;
                }
            }
        }
    }

    // 输出
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << a[i][j] << " \n"[j == n-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}