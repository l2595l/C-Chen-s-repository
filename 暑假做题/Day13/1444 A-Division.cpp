//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;  // 测试用例数量

    while (T--) {
        ll p, q;
        cin >> p >> q;

        // 如果 p 根本不能被 q 整除，那最大 x 就是 p 本身
        if (p % q != 0) {
            cout << p << '\n';
            continue;
        }

        // 特殊情况：q = 1 时，任何 x 都不能被 1 整除（因为 1 能整除所有数）
        // 但实际上 "x % 1 == 0" 永远成立，所以没有 x 满足条件
        // 但题目保证有解，所以 q > 1
        if (q == 1) {
            cout << 0 << '\n';  // 或者根据题目要求处理
            continue;
        }

        ll ans = 0;
        ll temp = q;

        // 分解 q 的所有质因子
        for (ll d = 2; d * d <= temp; d++) {
            if (temp % d == 0) {
                // d 是 q 的一个质因子

                // 对每个质因子 d，尝试把 p 一直除以 d
                ll candidate = p;
                while (candidate % q == 0) {
                    candidate /= d;
                }
                ans = max(ans, candidate);

                // 把 temp 中所有因子 d 去掉
                while (temp % d == 0) {
                    temp /= d;
                }
            }
        }

        // 如果 temp > 1，说明 temp 本身是一个质因子
        if (temp > 1) {
            ll candidate = p;
            while (candidate % q == 0) {
                candidate /= temp;
            }
            ans = max(ans, candidate);
        }

        cout << ans << '\n';
    }

    return 0;
}