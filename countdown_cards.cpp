#include <bits/stdc++.h>
using namespace std;

// 公式解:对每个数字 d,计算 [0,n] 内任意整数中 d 出现的最大次数,再求和。
long long solve(long long n) {
    string s = to_string(n);
    int L = (int)s.size();
    long long ans = 0;

    // 数字 0:含 k 个 0 的最小整数为 10^k (k>=1);另外数字 0 本身含 1 个 0。
    // 所以最大 0 个数 = max(1, L-1)。
    ans += max(1, L - 1);

    // 数字 1..9:含 k 个 d 的最小整数为重复数 "dd...d" (k 位)。
    // 位数 < L 的重复数必然 <= n;只需判断 L 位的重复数是否 <= n。
    for (int d = 1; d <= 9; ++d) {
        int k = L - 1;
        string rep(L, char('0' + d));
        if (rep <= s) k += 1;
        ans += k;
    }
    return ans;
}

// 暴力法:逐数字、逐整数统计最大出现次数。
long long brute(long long n) {
    long long ans = 0;
    for (int d = 0; d <= 9; ++d) {
        long long mx = 0;
        for (long long k = 0; k <= n; ++k) {
            long long cnt = 0;
            long long x = k;
            if (x == 0) {
                cnt = (d == 0) ? 1 : 0;
            } else {
                while (x) {
                    if (x % 10 == d) cnt++;
                    x /= 10;
                }
            }
            mx = max(mx, cnt);
        }
        ans += mx;
    }
    return ans;
}

int main() {
    // 对拍验证
    for (long long n = 0; n <= 5000; ++n) {
        if (solve(n) != brute(n)) {
            cout << "MISMATCH at n=" << n
                 << " solve=" << solve(n)
                 << " brute=" << brute(n) << "\n";
            return 1;
        }
    }
    cout << "all match (0..5000)\n";

    // 示例
    cout << "solve(60)     = " << solve(60) << "\n";
    cout << "solve(114514) = " << solve(114514) << "\n";

    // 大数示例
    cout << "solve(1000000000) = " << solve(1000000000LL) << "\n";
    cout << "solve(0)           = " << solve(0) << "\n";
    return 0;
}
