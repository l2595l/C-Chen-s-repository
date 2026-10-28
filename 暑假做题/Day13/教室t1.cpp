//
// Created by 28447 on 2026/8/26.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    unordered_map<int, vector<int>> s;
    while (q--) {
        int opr;
        cin >> opr;
        if (opr == 1) {
            int x, id;
            cin >> x >> id;
            s[x].push_back(id);
        }
        else if (opr == 2) {
            int x, y;
            cin >> x >> y;
            if (s.find(x) != s.end() && y <= s[x].size()) {
                cout << s[x][y-1] << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
        else if (opr == 3) {
            int x, y, id;
            cin >> x >> y >> id;
            s[x][y-1] = id;
        }
        else if (opr == 4) {
            int x;
            cin >> x;
            auto it = s.find(x);
            if (it != s.end() && !it->second.empty()) {
                it->second.pop_back();
            }
        }
    }
    return 0;
}