//
// Created by 28447 on 2026/9/26.
//
#include <iostream>
using namespace std;

long long a, b, p;

long long fastpow(long long a, long long b, long long p) {
    long long res = 1;
    while (b != 0) {
        if (b % 2 == 1) res = res * a % p;
        a = a * a % p, b /= 2;
    } return res;
}

int main() {
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << '=' << fastpow(a, b, p) << '\n';
    return 0;
}
