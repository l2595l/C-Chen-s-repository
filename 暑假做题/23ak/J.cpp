//
// Created by 28447 on 2026/9/8.
//


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    ll S = 0;
    for (ll x : a) S += x;

    // pmin[i] = min_{0<=j<=i} (a[j] - j)
    vector<ll> pmin(n);
    pmin[0] = a[0] - 0;
    for (int i = 1; i < n; i++) pmin[i] = min(pmin[i - 1], a[i] - (ll)i);

    while (q--) {
        ll k;
        cin >> k;

        // O = 最后一步为“+”(即操作次数为奇数)的卡牌数量,取可行的最大值
        ll O = min((ll)n, k);
        if ((O & 1) != (k & 1)) O--;

        // c0 = 各卡牌“上限值”(最终最多能达到的值)中的最小值
        ll c0;
        if (O == 0) {
            c0 = a[0];
        } else {
            ll m_odd = pmin[(int)(O - 1)] + k; // 奇数牌的最小上限
            if (O < n) c0 = min(a[(int)O], m_odd);
            else c0 = m_odd;
        }

        // 总增量上限 - 最小必需扣减,再平均分配
        ll T = S + O * k - O * (O - 1) / 2 - (k - O) / 2;

        // 向下取整的除法(处理负数)
        ll V = T / n;
        if (T % n != 0 && T < 0) V--;

        ll ans = min(c0, V);
        cout << ans << (q ? " " : "");
    }
    cout << "\n";
    return 0;
}