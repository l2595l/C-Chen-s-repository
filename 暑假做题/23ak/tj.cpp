//
// Created by 28447 on 2026/9/8.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int n,q;
    cin>>n>>q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    ll S=0;
    for (ll x: a) S+=x;


    vector<ll> pmin(n);
    pmin[0] = a[0] - 0;
    for (int i=1; i <n; i++) {
        pmin[i] = min(pmin[i-1],a[i]-i);
    }
    while (q--) {
        ll k;
        cin >> k;
        ll ji= min((ll)n, k),Mmin;// ji=奇数次的牌的数量
        if ((ji &1)!= (k & 1)) ji--;
        if (ji == 0) Mmin = a[0];
        else {
            ll m_odd = pmin[(ji - 1)] + k; // ji的最小上限
            if (ji < n) Mmin = min(a[ji], m_odd);

            else Mmin = m_odd;
        }

        ll Sum = S +  ji * k - (ji * (ji - 1) / 2) -  (k - ji) / 2;
        ll ave = Sum / n;
        if (Sum%n!=0 &&Sum < 0) ave--;

        ll ans = min(Mmin, ave);
        cout << ans << (q ? " " : "");
    }
    cout << "\n";
    return 0;
}