//
// Created by 28447 on 2026/8/14.
//卡特兰数
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int n;
    cin >> n;

    // 卡特兰数递推：C[0] = 1, C[n+1] = C[n] * 2*(2n+1) / (n+2)
    vector<ll> catalan(n + 1);
    catalan[0] = 1;

    for (int i = 0; i < n; i++) {
        catalan[i + 1] = catalan[i] * 2 * (2 * i + 1) / (i + 2);
    }

    cout << catalan[n] << endl;
    return 0;
}