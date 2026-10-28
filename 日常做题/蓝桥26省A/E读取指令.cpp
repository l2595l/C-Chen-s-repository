#include <bits/stdc++.h>
using namespace std;

// 输入：T 组数据，每组 N、C、W。
// 设 x = W / C。要从 1..N 中选若干个数使它们的和恰为 x，求需要的最少连续区间数：
//   W 不是 C 的倍数，或 x 超过 1+2+...+N：无解，输出 -1
//   x == 0：不用选，输出 0
//   x 能写成一段连续整数之和：输出 1
//   其余情况输出 2（证明：取 1..m+1 再删掉一个数，最多拆成两段）

using Int = long long;

// x 能否写成 [1, n] 内一段连续整数之和（要求 x >= 1）。
// 长度为 k、起点为 l 的一段，和为 k * l + k * (k - 1) / 2。
bool IsSingleRun(Int n, Int x) {
    if (x <= n) {
        return true;  // 单独一个数 x
    }
    // l >= 1 时长度 k 的最小和是 k * (k + 1) / 2，超过 x 就不用再试了
    for (Int k = 2; k <= n && k * (k + 1) / 2 <= x; ++k) {
        Int rest = x - k * (k - 1) / 2;
        if (rest % k != 0) {//计算起点是否存在
            continue;
        }
        Int start = rest / k;
        if (start + k - 1 <= n) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        Int n, c, w;
        cin >> n >> c >> w;

        if (w % c != 0) {
            cout << -1 << '\n';
            continue;
        }
        // 先除后比，避免 c * n * (n + 1) 溢出
        Int x = w / c;
        if (x > n * (n + 1) / 2) {
            cout << -1 << '\n';
        } else if (x == 0) {
            cout << 0 << '\n';
        } else {
            cout << (IsSingleRun(n, x) ? 1 : 2) << '\n';
        }
    }
    return 0;
}
