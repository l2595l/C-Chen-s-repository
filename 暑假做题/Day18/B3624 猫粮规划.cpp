//
// Created by 28447 on 2026/9/3.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> w(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        sum += w[i];
    }

    // dp[j] 表示凑出能量和 j 的方案数
    // 只需要开到 sum 即可，因为不可能超过所有食物的总和
    vector<long long> dp(sum + 1, 0);
    dp[0] = 1;  // 空集方案数为 1

    for (int i = 0; i < n; i++) {
        // 关键：从大到小遍历，保证每个物品只用一次（0/1背包）
        for (int j = sum; j >= w[i]; j--) {
            dp[j] += dp[j - w[i]];
        }
    }

    long long ans = 0;
    for (int j = l; j <= r; j++) {
        if (j <= sum) ans += dp[j];
    }

    cout << ans << endl;
    return 0;
}

