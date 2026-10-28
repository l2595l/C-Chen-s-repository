//
// Created by 28447 on 2026/8/30.
//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1000005;      // 区间最大长度
const ll MOD = 666623333;      // 取模数

ll l, r;                       // 区间 [l, r]
ll phi[MAXN], val[MAXN];       // phi: 欧拉函数值  val: 未处理的质因子
vector<ll> primes;             // sqrt(r) 以内的素数

// ============================================================
// 线性筛法：生成 sqrt(r) 以内的所有素数
// ============================================================
void init_primes() {
    int limit = sqrt(r) + 1;
    vector<bool> isComposite(limit + 1, false);

    for (int i = 2; i <= limit; i++) {
        if (!isComposite[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > limit) break;
            isComposite[i * p] = true;
            if (i % p == 0) break;  // 线性筛核心
        }
    }
}

// ============================================================
// 计算 Σ_{i=l}^{r} (i - φ(i)) mod MOD
// ============================================================
void solve() {
    int len = r - l + 1;

    // ---------- 步骤1：初始化 ----------
    // phi[i] 和 val[i] 都初始化为对应的数 n
    for (ll i = l; i <= r; i++) {
        phi[i - l] = i;
        val[i - l] = i;
    }

    // ---------- 步骤2：用素数筛处理区间 ----------
    // 遍历所有 <= sqrt(r) 的素数
    for (ll p : primes) {
        if (p * p > r) break;  // p 太大，不可能成为质因子

        // 找到区间内第一个能被 p 整除的数
        // max(p*p, ...) 从 p? 开始，避免重复处理
        ll start = max(p * p, (l + p - 1) / p * p);

        // 遍历区间内所有 p 的倍数
        for (ll x = start; x <= r; x += p) {
            int idx = x - l;

            // 应用欧拉函数公式：φ(n) = φ(n) × (p-1)/p
            phi[idx] /= p;
            phi[idx] *= (p - 1);

            // 去除 val 中所有的 p 因子
            while (val[idx] % p == 0) {
                val[idx] /= p;
            }
        }
    }

    // ---------- 步骤3：处理剩余的大质因子 ----------
    ll ans = 0;
    for (int i = 0; i < len; i++) {
        // 如果 val > 1，说明还剩一个 > sqrt(r) 的质因子
        if (val[i] > 1) {
            phi[i] /= val[i];
            phi[i] *= (val[i] - 1);
        }

        // 当前数 n = l + i
        ll n = l + i;

        // qiandao(n) = n - φ(n)
        // 累加答案并取模
        ans = (ans + (n - phi[i]) % MOD) % MOD;
    }

    printf("%lld\n", ans);
}

// ============================================================
// 主函数
// ============================================================
int main() {
    scanf("%lld%lld", &l, &r);
    init_primes();
    solve();
    return 0;
}