#include <bits/stdc++.h>
using namespace std;

// E. Array Emptying（CF 2271E）
// 每次操作：x <= k 就删掉 x；否则删掉 x、插入两个 ?x/2?（向上取整！）。两种操作都让 k += 1。
// 答案 = n + 2*S_min，S_min = 最少劈次数；对 S 二分，check 用「逆向贪心」判定。
// ?? 曾经写错成 ?x/2?（H/2），在 test2 第 48 个用例 [3,3,3] k=0 上报 WA（expected 7 / found 5）。

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        long long k0;
        scanf("%d %lld", &n, &k0);
        vector<int> a(n);
        int mx = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            mx = max(mx, a[i]);
        }

        // check(c)：假设总共只做 c 次「劈」，能不能清空。
        // 逆向处理：从最后一次删除往前，k 从 S = k0 + n + 2c - 1 逐次递减。
        auto check = [&](long long c) -> bool {
            vector<int> cnt(mx + 1, 0);
            for (int x : a) ++cnt[x];
            long long S = k0 + (long long)n + 2 * c - 1;
            long long splits = 0, size = n;
            int cur = mx;
            while (size > 0) {
                while (cur > 0 && cnt[cur] == 0) --cur;
                if (cnt[cur] == 0) break;
                int H = cur;
                if (H <= S) {          // 现在能删，就删掉它
                    --cnt[H];
                    --size;
                    --S;
                } else {               // 删不掉 → 只能在这一步劈开
                    if (splits == c) return false;
                    --cnt[H];
                    cnt[(H + 1) / 2] += 2;   // 题面是「插入两个 ?x/2?」(向上取整!)
                    ++size;
                    ++splits;
                }
            }
            return true;
        };

        long long lo = 0, hi = n;      // 每个元素各劈一次一定够
        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            if (check(mid)) hi = mid;
            else lo = mid + 1;
        }
        printf("%lld\n", (long long)n + 2 * lo);
    }
    return 0;
}
