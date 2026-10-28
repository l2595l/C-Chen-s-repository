//
// Created by 28447 on 2026/10/8.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

static const int MAXA = 1000000;
static vector<int> spf;          // smallest prime factor

static inline ull splitmix64(ull x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

static void buildSieve() {
    spf.assign(MAXA + 1, 0);
    for (int i = 2; i <= MAXA; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            if ((ll)i * i <= MAXA)
                for (ll j = (ll)i * i; j <= MAXA; j += i)
                    if (!spf[j]) spf[j] = i;
        }
    }
}

// Zobrist hash of the square-free kernel of x (XOR of random values of primes with odd exponent)
static inline ull kernelHash(int x) {
    ull h = 0;
    while (x > 1) {
        int p = spf[x];
        int e = 0;
        while (x % p == 0) { x /= p; e ^= 1; }
        if (e) h ^= splitmix64((ull)p);
    }
    return h;
}

struct SplitMixHash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const { return (size_t)splitmix64(x); }
};

int main() {
    buildSieve();
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        unordered_map<ull, ll, SplitMixHash> cntA, cntP;
        cntA.reserve(n * 2 + 10);
        cntP.reserve(n * 2 + 10);

        ull cur = 0;                       // hash of square-free kernel of a_1*...*a_j
        for (int i = 1; i <= n; ++i) {
            int a;
            scanf("%d", &a);
            ull h = kernelHash(a);         // hash of sf(a_i)
            ++cntA[h];
            cur ^= h;                      // prefix: sf(a_1*...*a_i)
            ++cntP[cur];                   // j = i
        }

        ll ans = 0;
        for (auto &kv : cntA) {
            auto it = cntP.find(kv.first);
            if (it != cntP.end()) ans += kv.second * it->second;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
