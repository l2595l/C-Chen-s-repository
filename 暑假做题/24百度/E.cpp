//
// Created by 28447 on 2026/9/9.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int L, x, y;
        cin >> L >> x >> y;

        // 如果 |y| > L，点到支点的距离至少 |y|，不可能 ≤ L
        if (abs(y) > L) {
            cout << "NO\n";
            continue;
        }

        // d = sqrt(L^2 - y^2)
        double d = sqrt((double)L * L - (double)y * y);

        // p 需要满足: 0 ≤ p ≤ L 且 |x-p| ≤ d
        // 即 x-d ≤ p ≤ x+d
        double low = max(0.0, (double)x - d);
        double high = min((double)L, (double)x + d);

        // 判断区间是否非空（考虑浮点误差）
        if (low <= high + 1e-9) {
            cout << "YES\n";
            // 输出任意一个满足条件的支点横坐标
            // 这里输出 low，但要注意 low 可能略小于0或略大于L，但已经在max/min处理过了
            cout << fixed << setprecision(10) << low << "\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}