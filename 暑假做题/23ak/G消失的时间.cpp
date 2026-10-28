#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;
        string s = to_string(n);
        int L = (int)s.size();

        long long ans = 0;

        // 数字 0：含 k 个 0 的最小整数是 10^k (k>=1)，另有数字 0 本身含 1 个 0
        ans += max(1, L - 1);

        // 数字 1..9：含 k 个 d 的最小整数是重复数 "dd...d"(k 位)
        for (int d = 1; d <= 9; ++d) {
            int k = L - 1;                       // 位数 < L 的重复数必然 ≤ n
            string rep(L, char('0' + d));        // L 位的重复数
            if (rep <= s) k += 1;                // 比较它是否 ≤ n
            ans += k;
        }

        cout << ans << "\n";
    }

    return 0;
}
