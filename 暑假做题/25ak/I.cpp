//
// Created by 28447 on 2026/9/7.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    // good[i] 表示以 i 为起始位置（0-based）的长度为5的子串是否是 ABCBA 形
    vector<bool> good(n, false);
    for (int i = 0; i + 4 < n; i++) {
        if (s[i] == s[i+4] && s[i+1] == s[i+3]) {
            good[i] = true;
        }
    }

    long long ans = 0;
    int last_good_start = 0;  // 1-based，0 表示还没有好子串

    for (int r = 0; r < n; r++) {
        // 如果以 r-4 为起始位置是好子串，则更新 last_good_start
        if (r >= 4 && good[r-4]) {
            last_good_start = (r - 4) + 1;  // 转换为 1-based
        }

        if (last_good_start > 0) {
            ans += last_good_start;
        }
    }

    cout << ans << endl;
    return 0;
}