//
// Created by 28447 on 2026/8/29.
//
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 1000005;
int n, maxVal = 0;
int cnt[MAXN], ans[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    vector<int> nums(n);

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        cnt[nums[i]]++;
        maxVal = max(maxVal, nums[i]);
    }

    // 方法1：如果值域很小，用倍数枚举
    if(maxVal <= 1000000) {
        for(int d = 1; d <= maxVal; d++) {
            int sum = 0;
            for(int multiple = d; multiple <= maxVal; multiple += d) {
                sum += cnt[multiple];
            }
            if(sum > 0) ans[sum] = max(ans[sum], d);
        }
    }

    // 方法2：如果n很小，用因子枚举
    if(n <= 1000) {
        for(int i = 0; i < n; i++) {
            int x = nums[i];
            for(int d = 1; d <= sqrt(x); d++) {
                if(x % d == 0) {
                    // 直接处理
                }
            }
        }
    }

    // 后缀最大值
    for(int i = n - 1; i >= 1; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}