//
// Created by 28447 on 2026/8/19.
//
/////正常
///
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;
//
// int main() {
//     int n;
//     cin >> n;
//
//     // 正确的二维vector创建方式
//     vector<vector<int>> matrix(n, vector<int>(n));
//
//     // 读入矩阵
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> matrix[i][j];
//         }
//     }
//
//     int minZeros = n;
//
//     // 检查每一行
//     for (int i = 0; i < n; i++) {
//         int zeros = 0;
//         for (int j = 0; j < n; j++) {
//             if (matrix[i][j] == 0) zeros++;
//         }
//         minZeros = min(minZeros, zeros);
//     }
//
//     // 检查每一列
//     for (int j = 0; j < n; j++) {
//         int zeros = 0;
//         for (int i = 0; i < n; i++) {
//             if (matrix[i][j] == 0) zeros++;
//         }
//         minZeros = min(minZeros, zeros);
//     }
//
//     // 检查主对角线
//     int zeros = 0;
//     for (int i = 0; i < n; i++) {
//         if (matrix[i][i] == 0) zeros++;
//     }
//     minZeros = min(minZeros, zeros);
//
//     // 检查副对角线
//     zeros = 0;
//     for (int i = 0; i < n; i++) {
//         if (matrix[i][n - 1 - i] == 0) zeros++;
//     }
//     minZeros = min(minZeros, zeros);
//
//     cout << minZeros << endl;
//
//     return 0;
// }

/////优化
///
#include <iostream>
#include <algorithm>
using namespace std;
#include<bi>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int hangZeros[1005] = {0};
    int lieZeros[1005] = {0};
    int mxie = 0, sxie = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            if (val == 0) {
                hangZeros[i]++;
                lieZeros[j]++;
                if (i == j) mxie++;
                if (i + j == n - 1) sxie++;
            }
        }
    }

    int minZeros = n;
    for (int i = 0; i < n; i++) {
        minZeros = min(minZeros, hangZeros[i]);
        minZeros = min(minZeros, lieZeros[i]);
    }
    minZeros = min(minZeros, mxie);
    minZeros = min(minZeros, sxie);

    cout << minZeros << endl;
    return 0;
}