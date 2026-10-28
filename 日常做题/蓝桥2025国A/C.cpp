//
// Created by 28447 on 2026/10/19.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 5;

ll n, h[N], a[N];
bool f[N];  // 标记是否存在高度 i

int main() {
    cin >> n;
    ll x, cnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (x != h[cnt])
            h[++cnt] = x;  // 压缩数组，去除连续重复
    }
    if (cnt == 1) {  // 已经全部相同
        cout << "0\n";
        return 0;
    }
    // 统计每个高度的出现次数（不包括首尾）
    for (ll i = 1; i <= cnt; i++) {
        f[h[i]] = 1;
        a[h[i]]++;
    }
    a[h[1]]--;
    a[h[cnt]]--;
    ll ans = INT_MAX - 1;
    for (ll i = 1; i <= (ll)1e6; i++) {
        if (!f[i])
            continue;  // 只考虑存在的高度
        ans = min(ans, i * (a[i] + 1));
    }
    cout << ans << "\n";
}
