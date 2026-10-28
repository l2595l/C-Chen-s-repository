//
// Created by 28447 on 2026/9/8.
//
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// 统计 0 到 n 中每个数字出现的次数
array<int64, 10> count_digits(int64 n) {
    array<int64, 10> cnt = {};
    if (n < 0) return cnt;

    int64 factor = 1;
    while (factor <= n) {
        int64 high = n / (factor * 10);
        int64 cur = (n / factor) % 10;
        int64 low = n % factor;

        for (int d = 0; d < 10; d++) {
            if (d < cur) {
                cnt[d] += (high + 1) * factor;
            } else if (d == cur) {
                cnt[d] += high * factor + low + 1;
            } else {
                cnt[d] += high * factor;
            }
        }

        // 减去前导零的影响（数字 0 不能有前导零）
        cnt[0] -= factor;

        factor *= 10;
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int64 n;
        cin >> n;

        auto cnt = count_digits(n);

        int64 ans = 0;
        for (int i = 0; i < 10; i++) {
            ans = max(ans, cnt[i]);
        }

        cout << ans << "\n";
    }

    return 0;
}