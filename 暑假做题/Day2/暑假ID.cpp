//
// Created by 28447 on 2026/8/14.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool check(int n, int k, vector<ll>& S) {
    for (int i = 1; i < k - 1; i++) {
        // a = S[i] - S[i-1]
        if (S[i] - S[i-1] > S[i+1] - S[i]) {
            return false;
        }
    }
    if (k == 1) {
        // 仅一个前缀和，总是可能的
        return true;
    }
    if (k < n) {
        ll d = S[1] - S[0];  // a_{n-k+2}

        // 每个a都 <=d，最大和<= (n-k+1)*d
        if (S[0] > (ll)(n - k + 1) * d) {
            return false;
        }
    } else {// k == n
        // 检查 a1 ≤ a2
        if (S[0] > S[1] - S[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;


        vector<ll> S(k);
        for (int i = 0; i < k; i++) {
            cin >> S[i];
        }

        cout << (check(n, k, S) ? "YES" : "NO") << '\n';
    }
    return 0;
}