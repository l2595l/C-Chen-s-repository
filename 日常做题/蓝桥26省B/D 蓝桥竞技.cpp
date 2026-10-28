//
// Created by 28447 on 2026/10/24.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main () {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& v : a) {
        cin >> v;
    }
    for (ll& v : a) {
        cout << v << " ";
    }
    return 0;
}