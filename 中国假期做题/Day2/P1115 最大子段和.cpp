//
// Created by 28447 on 2026/9/26.
//dp[i] = max(dp[i-1] + a[i], a[i])
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;

    int current_sum = 0; // 相当于 dp[i-1]
    int max_sum = INT_MIN; // 记录最终答案，初始化为极小值

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        // 状态转移：接在前面 或 从当前重新开始
        if (current_sum > 0) {
            current_sum += a;
        } else {
            current_sum = a;
        }

        // 更新全局最大值
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << endl;

    return 0;
}