//
// Created by 28447 on 2026/8/17.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000000;
const int MAXV = 2000000;
const int MOD = 77;

int minPrime[MAXN + 5];
int factorCnt[MAXV + 5];
vector<pair<int, int>> groupByResidue[MOD];
vector<ll> prefByResidue[MOD];

// 快速读入
template <class I>
inline void read(I &num) {
    num = 0;
    char c = getchar();
    char up = c;
    while (!isdigit(c)) {
        up = c;
        c = getchar();
    }
    while (isdigit(c)) {
        num = (num << 1) + (num << 3) + (c ^ '0');
        c = getchar();
    }
    if (up == '-') num = -num;
}

// 欧拉筛
void initMinPrime() {
    vector<int> primes;
    for (int i = 2; i <= MAXN; i++) {
        if (minPrime[i] == 0) {
            minPrime[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minPrime[i] || 1LL * i * p > MAXN) break;
            minPrime[i * p] = p;
        }
    }
    minPrime[1] = 1;
}

// 因子个数
void initFactorCnt() {
    for (int i = 1; i <= MAXV; i++) {
        for (int j = i; j <= MAXV; j += i) {
            factorCnt[j]++;
        }
    }
}

// 预处理分组
void initGroups() {
    for (int x = 1; x <= MAXN; x++) {
        int y = minPrime[x];
        int f = factorCnt[x + y];
        int r = x % MOD;
        groupByResidue[r].push_back({x, f});
    }

    for (int r = 0; r < MOD; r++) {
        prefByResidue[r].resize(groupByResidue[r].size() + 1, 0);
        for (int i = 0; i < (int)groupByResidue[r].size(); i++) {
            prefByResidue[r][i + 1] = prefByResidue[r][i] + groupByResidue[r][i].second;
        }
    }
}

// 查询：O(77 * log(MAXN/77))
ll query(int n) {
    ll res = 0;
    int nMod = n % MOD;

    for (int r = 0; r < MOD; r++) {
        ll exprMod = (2LL * r * r + 3LL * r + 5LL * nMod) % MOD;
        if (exprMod == 0) {
            auto &vec = groupByResidue[r];
            // 二分查找最后一个 x ≤ n
            int lo = 0, hi = (int)vec.size() - 1, pos = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (vec[mid].first <= n) {
                    pos = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (pos != -1) {
                res += prefByResidue[r][pos + 1];
            }
        }
    }
    return res;
}

int main() {
    // 注意：这里用 getchar() 读入，不要用 ios::sync_with_stdio(false)
    // 否则会混用 getchar 和 cin，可能导致问题

    initMinPrime();
    initFactorCnt();
    initGroups();

    int q;
    read(q);

    while (q--) {
        int n;
        read(n);
        cout << query(n) << '\n';
    }

    return 0;
}