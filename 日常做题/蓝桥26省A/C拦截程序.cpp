//
// Created by 28447 on 2026/10/23.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        long long L, V, T;
        cin >> L >> V >> T;
        // 两个可能的坐标距离之差
        long long diff = abs(2 * V * T - L);
        // 最小偏差就是距离差的一半（向上取整）
        long long ans = (diff + 1) / 2;

        cout << ans << "\n"; // 记得换行
    }
    return 0;
}