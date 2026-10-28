//
// Created by 28447 on 2026/9/6.
//
#include <bits/stdc++.h>
using namespace std;

using int128 = __int128_t;

// 安全计算 C(n+1, 3) = (n+1)*n*(n-1)/6
long long comb3_safe(long long n, long long mod) {
    if (n < 2) return 0;

    long long nums[3] = {n + 1, n, n - 1};

    // 约去因子 2
    for (int i = 0; i < 3; i++) {
        if (nums[i] % 2 == 0) {
            nums[i] /= 2;
            break;
        }
    }

    // 约去因子 3
    for (int i = 0; i < 3; i++) {
        if (nums[i] % 3 == 0) {
            nums[i] /= 3;
            break;
        }
    }

    // 边乘边取模
    int128 result = 1;
    for (int i = 0; i < 3; i++) {
        result = (result * (nums[i] % mod)) % mod;
    }

    return (long long)result;
}

// 安全计算 L = n*(n+1)*m*(m+1)/4
long long comb4_safe(long long n, long long m, long long mod) {
    if (n == 0 || m == 0) return 0;

    long long nums[4] = {n, n + 1, m, m + 1};

    // 约去两个因子 2
    for (int i = 0; i < 4; i++) {
        if (nums[i] % 2 == 0) {
            nums[i] /= 2;
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (nums[i] % 2 == 0) {
            nums[i] /= 2;
            break;
        }
    }

    // 边乘边取模
    int128 result = 1;
    for (int i = 0; i < 4; i++) {
        result = (result * (nums[i] % mod)) % mod;
    }

    return (long long)result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long n, m, p;
        cin >> n >> m >> p;

        if (p == 1) {
            cout << "0 0 0\n";
            continue;
        }

        // C = C(n+1, 3) * (m+1)
        long long c = comb3_safe(n, p);
        c = (c * ((m + 1) % p)) % p;

        // K = (n+1) * C(m+1, 3)
        long long k = comb3_safe(m, p);
        k = (k * ((n + 1) % p)) % p;

        // L = n*(n+1)*m*(m+1)/4
        long long l = comb4_safe(n, m, p);

        cout << c << " " << k << " " << l << "\n";
    }

    return 0;
}