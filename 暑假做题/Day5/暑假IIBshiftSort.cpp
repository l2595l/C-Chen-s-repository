//
// Created by 28447 on 2026/8/16.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        // 统计字符串中0的个数
        int wrong_0 = 0;
        for (char c : s) {
            if (c == '0') wrong_0++;
        }

        // 统计前cnt0个位置中1的个数（即错位的1）
        int wrong_1 = 0;
        for (int i = 0; i < wrong_0; i++) {
            if (s[i] == '1') wrong_1++;
        }

        cout << wrong_1 << endl;
    }

    return 0;
}