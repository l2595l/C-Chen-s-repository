//
// Created by 28447 on 2026/8/13.
//
///////////勾股
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    // 使用 lambda 表达式（编译器会自动内联）
    auto tri = [](const int& x, const int& y) -> double {
        return sqrt(static_cast<double>(x)*x + static_cast<double>(y)*y);
    };

    cout << fixed << setprecision(2) << tri(a, b) << endl;
    return 0;
}