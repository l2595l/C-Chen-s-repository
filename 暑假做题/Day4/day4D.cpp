//
// Created by 28447 on 2026/8/16.
//
#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;      // ? 先判断 n==2
    if (n % 2 == 0) return false; // ? 再判断偶数

    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

template <class I>
inline void read(I &num) {
    num = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) {
        num = (num << 1) + (num << 3) + (c ^ '0');
        c = getchar();
    }
}

int main() {
    int t;
    read(t);  // ? 统一用 read，避免 cin/getchar 混用

    while (t--) {
        int n;  // ? 用 int 就够了，10^8 在 int 范围内
        read(n);
        cout << (isPrime(n) ? "Yes\n" : "No\n");
    }
    return 0;
}