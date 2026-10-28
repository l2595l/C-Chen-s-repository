//
// Created by 28447 on 2026/9/8.
//
// inline int Read() {
//     int x = 0;
//     char c = getchar();
//     // 跳过非数字字符
//     while (c > '9' || c < '0') c = getchar();
//     // 读入数字
//     while (c >= '0' && c <= '9') {
//         x = x * 10 + c - '0';
//         c = getchar();
//     }
//     return x;
// }
#include <iostream>
#include <string>
using namespace std;

int countKaze(const string& s) {
    int cnt = 0;
    int n = s.length();

    for (int i = 0; i < n; i++) {
        // 检查 k a -? z e
        if (s[i] == 'k' && i + 1 < n && s[i+1] == 'a') {
            int j = i + 2;

            // 跳过可能的 '-'
            if (j < n && s[j] == '-') j++;

            // 检查 z e
            if (j + 1 < n && s[j] == 'z' && s[j+1] == 'e') {
                // 检查前面是否连着 'k'
                if (i == 0 || s[i-1] != 'k') {
                    cnt++;
                }
            }
        }
    }

    return cnt;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        string s;
        cin >> s;
        cout << countKaze(s) << endl;
    }

    return 0;
}