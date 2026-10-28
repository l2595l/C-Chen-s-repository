//
// Created by 28447 on 2026/10/20.
//
#include <bits/stdc++.h>

using namespace std;

const int nn = 100005;
char s[nn];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> s;
    int brk = 0, l = 0;
    int64_t ans = 0;
    for (int r = 0; s[r]; r++) {
        if (r && s[r - 1] + 1 != s[r] && s[r - 1] != s[r])
            brk++;
        while (brk > 1) {
            l++;
            if ((s[l] != s[l - 1] && s[l - 1] + 1 != s[l]))
                brk--;
        }
        ans += r - l + 1;
    }
    cout << ans << '\n';
    return 0;
}
