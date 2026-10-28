//
// Created by 28447 on 2026/8/16.
//
#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n;
    cin >> n;
    // 能被 6、8、9 同时整除 <=> 能被 lcm(6,8,9)=72 整除
    // 所以 OO 数 = 72 的倍数，且不能被 5、7 整除
    long long m = n / 72;   // 小于等于 n 的 72 的倍数个数

    // 因为 72 与 5、7 都互质，所以「72k 能被 5 整除」等价于「k 能被 5 整除」
    // 用容斥原理：总数 - 能被5整除的 - 能被7整除的 + 能被35整除的
    long long ans = m - m / 5 - m / 7 + m / 35;
    cout << ans << '\n';
    return 0;
}