//
// Created by 28447 on 2026/8/16.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    string N;
    cin >> N;
    reverse(N.begin(), N.end());
    //»•¡„
    int pos = 0;
    while (pos < N.size() && N[pos] == '0') {
        pos++;
    }
    if (pos == N.size()) {
        cout << 0 << endl;
    } else {
        cout << N.substr(pos) << endl;
    }

    return 0;
}
