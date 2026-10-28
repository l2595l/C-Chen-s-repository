//
// Created by 28447 on 2026/10/23.
//
#include<bits/stdc++.h>
#define L ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define F(x, l, r) for(int x = l; x <= r; ++x)
#define ll long long
using namespace std;

//const int N = ;

ll num = 2026202620262026;
ll ans50 = 0;
ll ans52 = 0;
ll fac[53] = {1};

int main() {
    L;
    F (i, 1, 52) fac[i] = fac[i - 1] * 2;

    // 50 位
    F (i, 24, 49) ans50 += fac[i];

    // 52 位
    ans52 += fac[51];
    F (i, 0, 24) ans52 += fac[i];

    // 比较
    if (num - ans50 <= ans52 - num) cout << ans50;
    else cout << ans52;

    return 0;
}
