//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> s(n+1);
    while (q--) {
        int opr, x, y;
        cin >> opr >> x >> y;

        if (opr == 1) {
            s[x].push_back(y);
        }
        else {
            cout << s[x][y-1] << '\n';
        }
    }
    return 0;
}