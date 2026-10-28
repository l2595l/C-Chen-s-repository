//
// Created by 28447 on 2026/10/24.
//
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD=998244353;

inline ll qpow(ll a,ll b) {
    a%=MOD;
    if (a<0) a+=MOD;
    ll ret = 1;
    while (b) {
        if (b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;

    }
    return ret;
}
int main() {
    cout<<1ll*2026*qpow(2,2025)%MOD<<endl;
    return 0;
}


// #include <bits/stdc++.h>
// #define int long long
// using namespace std;
// signed main() {
//     register int n = 2026, ans = 1;
//     for (register int i = 1; i < n; ++i)
//         ans <<= 1, ans %= 998244353;
//     ans *= n, ans %= 998244353;
//     cout << ans;
//     return 0;
// } // ans = 792264670
