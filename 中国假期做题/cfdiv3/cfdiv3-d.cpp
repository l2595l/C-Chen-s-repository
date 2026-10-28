//
// Created by 28447 on 2026/10/8.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 单个实验室：a,b,c 为三个读数（顺序固定），k 次操作内最大可达到的和
// 若原始顺序 (a,b,c) 非升序 => 存在可加的 +1 操作，可无限爬升：F(m) = s + m
// 若 a<=b<=c => 先花 tau = min(b-a, c-b) + 1 次操作破坏升序，每次净亏 1，之后爬升
//               => F(m) = max(s, s + m - 2*tau)
// 若 a==b==c => 死局，F(m) = s
int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        ll k;
        scanf("%d %lld", &n, &k);

        vector<ll> s(n);          // 每个实验室的初始和
        vector<ll> costBase(n);   // 目标 T 时的代价 = T + costBase[i]（且仅当 T > s[i]）
        ll minS = LLONG_MAX;
        ll cap = LLONG_MAX;       // 死局实验室给出的上界

        for (int i = 0; i < n; ++i) {
            ll a, b, c;
            scanf("%lld %lld %lld", &a, &b, &c);
            ll sum = a + b + c;
            s[i] = sum;
            minS = min(minS, sum);

            if (a == b && b == c) {
                cap = min(cap, sum);
                costBase[i] = 0;              // 永远不会被计入（T <= cap <= sum）
            } else if (!(a <= b && b <= c)) {
                costBase[i] = -sum;           // tau = 0 => 代价 max(0, T - sum)
            } else {
                ll tau = min(b - a, c - b) + 1;
                costBase[i] = -sum + 2 * tau; // 代价 T - sum + 2*tau
            }
        }

        auto total = [&](ll T) -> ll {        // 让所有实验室的和都 >= T 所需最少操作数
            ll res = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] < T) {
                    res += T + costBase[i];
                    if (res > k) return res;  // 提前截断，避免溢出
                }
            }
            return res;
        };

        ll lo = minS;
        ll hi = min(minS + k + 1, cap);       // 超过 hi 一定不可行
        while (lo < hi) {
            ll mid = lo + (hi - lo + 1) / 2;
            if (total(mid) <= k) lo = mid;
            else hi = mid - 1;
        }
        printf("%lld\n", lo);
    }
    return 0;
}
