//
// Created by 28447 on 2026/10/24.
//
#include <iostream>
using namespace std;

int main() {
    // 加速 cin 和 cout
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        long long n, x, y; // 使用 long long 防止溢出
        cin >> n >> x >> y;

        if (x > y) {
            cout << 0 << '\n'; // 换行用 '\n' 速度更快
        } else {
            cout << y - x + 1 << '\n';
        }
    }
    return 0;
}