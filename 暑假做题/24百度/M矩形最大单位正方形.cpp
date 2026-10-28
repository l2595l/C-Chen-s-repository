//
// Created by 28447 on 2026/9/15.
//
#include <bits/stdc++.h>
  using namespace std;

  /*
   * 构造 n×n (n 为偶数) 的 01 矩阵, 满足:
   *   1) 恰好 k 个 1
   *   2) 每行的和奇偶性相同
   *   3) 每列的和奇偶性相同
   * 无法构造时输出 -1。
   *
   * 核心结论:
   *   - 因为 n 为偶数, 所有行和都同奇偶 => k = 行和之和 必为偶数 (奇数 k 无解)。
   *   - 整体取反 (0<->1) 时, 每行和变为 n-原和, n 为偶数故奇偶性不变,
   *     所以 k 与 n^2-k 的可行性相同 (用于把大 k 化成小 k)。
   *   - n>=4 时 k=2 与 k=n^2-2 无解:
   *       k=2: 两个 1 同在一行则有两列变奇; 分处两行则有两行变奇, 无法保持一致。
   *       k=n^2-2 由取反对称性同样无解。
   *   - 其余偶数 k 均可由 "2x2 块" + "6 环" 拼出。
   *
   * 构造思路 (目标是每行每列都为偶):
   *   2x2 全 1 块 -> 给两行、两列各 +2, 不改变任何奇偶性, 贡献 4 个 1。
   *   6 环 (3x3)  -> 每行每列恰好 2 个 1, 全部为偶, 贡献 6 个 1 (用于 k%4==2 的情况)。
   */
  void solve(int n, int k) {
      // ---- 可行性判定 ----
      if (k & 1) {                          // 奇数: 无解
          cout << -1 << '\n';
          return;
      }
      if (n == 2) {                         // n=2 特判
          if (k == 0) cout << "0 0\n0 0\n";
          else if (k == 2) cout << "1 0\n0 1\n";  // 每行每列都奇
          else if (k == 4) cout << "1 1\n1 1\n";
          else cout << -1 << '\n';
          return;
      }
      if (k == 2 || k == n * n - 2) {       // n>=4 时两端的小缺口: 无解
          cout << -1 << '\n';
          return;
      }

      // ---- 取反对称性: 只处理 k <= n^2/2, 最后再翻转 ----
      bool flip = false;
      if (k > n * n / 2) {
          k = n * n - k;
          flip = true;
      }

      vector<vector<int>> mat(n, vector<int>(n, 0));

      if (k != 0) {
          bool hasCycle = false;

          // k % 4 == 2 时 (k>=6), 先放一个 6 环 (每行每列恰好 2 个 1)
          if (k % 4 == 2) {
              // 左上角 3x3 的 6 环:
              //   1 1 0
              //   0 1 1
              //   1 0 1
              int cyc[6][2] = {{0,0},{0,1},{1,1},{1,2},{2,2},{2,0}};
              for (auto &p : cyc) mat[p[0]][p[1]] = 1;
              k -= 6;
              hasCycle = true;
          }

          // 剩余 k 是 4 的倍数, 用 2x2 全 1 块填满
          int cnt = k / 4;
          for (int bi = 0; bi < n / 2 && cnt; ++bi) {
              for (int bj = 0; bj < n / 2 && cnt; ++bj) {
                  // 放了 6 环时, 跳过与其重叠的左上角 4 个 2x2 块
                  // (6 环占行 0..2、列 0..2, 恰好覆盖块 (0,0)(0,1)(1,0)(1,1))
                  if (hasCycle && bi <= 1 && bj <= 1) continue;

                  // 该块对应第 2bi, 2bi+1 行, 第 2bj, 2bj+1 列
                  mat[2*bi][2*bj]     = 1;
                  mat[2*bi][2*bj + 1] = 1;
                  mat[2*bi + 1][2*bj]     = 1;
                  mat[2*bi + 1][2*bj + 1] = 1;
                  --cnt;
              }
          }
      }

      // ---- 整体取反恢复原来的大 k ----
      if (flip) {
          for (int i = 0; i < n; ++i)
              for (int j = 0; j < n; ++j)
                  mat[i][j] = 1 - mat[i][j];
      }

      // ---- 输出 ----
      for (int i = 0; i < n; ++i) {

      // ---- 整体取反恢复原来的大 k ----
      if (flip) {
          for (int i = 0; i < n; ++i)
              for (int j = 0; j < n; ++j)
                  mat[i][j] = 1 - mat[i][j];
      }

      // ---- 输出 ----
      for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
              cout << mat[i][j] << (j + 1 == n ? '\n' : ' ');
          }
      }
  }

