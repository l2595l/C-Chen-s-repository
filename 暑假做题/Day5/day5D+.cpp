//
// Created by 28447 on 2026/8/17.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

const int MAXN = 1000000;
const int MAXZ = 2 * MAXN + 5;

int minPrime[MAXN + 5];
int factorCnt[MAXZ + 5];
int expCnt[MAXZ + 5];  // 最小质因子的指数

ll sumResidue[77];
vector<int> valid[77];
ll ans[MAXN + 5];

// ============================================================
// 合并预处理：欧拉筛 + 求因子个数
// ============================================================
void initPrimesAndFactors() {
    vector<int> primes;
    factorCnt[1] = 1;

    for (int i = 2; i <= MAXZ; i++) {
        if (minPrime[i] == 0) {
            if (i <= MAXN) minPrime[i] = i;  // 只记录 ≤ MAXN 的
            primes.push_back(i);
            factorCnt[i] = 2;      // 质数有 2 个因子：1 和 i
            expCnt[i] = 1;         // 质因子的指数为 1
        }
        for (int p : primes) {
            if (1LL * i * p > MAXZ) break;
            minPrime[i * p] = p;

            if (p == minPrime[i]) {
                // p 是 i * p 的最小质因子
                expCnt[i * p] = expCnt[i] + 1;
                factorCnt[i * p] = factorCnt[i] / (expCnt[i] + 1) * (expCnt[i] + 2);
                break;
            } else {
                expCnt[i * p] = 1;
                factorCnt[i * p] = factorCnt[i] * 2;
            }
        }
    }
    // 单独处理 1 的最小质因子
    minPrime[1] = 1;
}

void initAns() {
    // 预处理合法余数
    for (int m = 0; m < 77; m++) {
        for (int r = 0; r < 77; r++) {
            if ((2 * r * r + 3 * r + 5 * m) % 77 == 0) {
                valid[m].push_back(r);
            }
        }
    }

    // 滚动累加
    for (int n = 1; n <= MAXN; n++) {
        if (n >= 2) {
            int y = minPrime[n];
            sumResidue[n % 77] += factorCnt[n + y];
        }
        ll res = 0;
        for (int r : valid[n % 77]) {
            res += sumResidue[r];
        }
        ans[n] = res;
    }
}

int main() {
    initPrimesAndFactors();
    initAns();

    int q;
    read(q);
    while (q--) {
        int n;
        read(n);
        cout << ans[n] << '\n';
    }
    return 0;
}