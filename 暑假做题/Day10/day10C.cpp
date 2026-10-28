//
// Created by 28447 on 2026/8/22.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll shu(ll a, ll b) {
    if (b == 0) return a;
    return shu(b, a % b);
}
int main() {
    ll a, b;
    cin >> a >> b;
    cout << shu(a, b);
    return 0;
}