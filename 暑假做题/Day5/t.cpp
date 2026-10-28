//
// Created by 28447 on 2026/8/17.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long

// ============================================================
// 快速读入（和原来一样）
// ============================================================
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

// ============================================================
// 常量定义
// ============================================================
const int MAXN = 1000000;
const int MAXV = 2000000;      // 最大需要：x + y，x最大10^6，y最大x，所以2*10^6

int minPrime[MAXN + 5];        // 最小质因子（只用到 MAXN）
int factorCnt[MAXV + 5];       // 因子个数（需要开到 2*MAXN）
ll sumByResidue[77];           // sumByResidue[r] = 所有 x%77==r 的 f(x) 之和
ll ans[MAXN + 5];              // 预处理答案

// ============================================================
// 欧拉筛求最小质因子（和原来一样）
// ============================================================
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
    // 特殊处理 1：除 1 以外没有正因子，这里设为 1 方便后续判断
    minPrime[1] = 1;
}

// ============================================================
// 求因子个数（开到 2*MAXN）
// ============================================================
void initFactorCnt() {
    for (int i = 1; i <= MAXV; i++) {
        for (int j = i; j <= MAXV; j += i) {
            factorCnt[j]++;
        }
    }
}

// ============================================================
// 预处理：利用 mod 77 周期性
// ============================================================
void initAns() {
    // 第一步：计算每个 x 对应的 f(x) = factorCnt[x + minPrime[x]]
    // 并按 x % 77 分类累加
    for (int x = 1; x <= MAXN; x++) {
        int y = minPrime[x];              // x 的最小质因子
        int f = factorCnt[x + y];         // f(x)
        int r = x % 77;                   // 余数类
        sumByResidue[r] += f;             // 累加到对应的余数类
    }

    // 第二步：对每个 n，计算答案
    // 对于给定的 n，需要找到所有 x (1≤x≤n) 满足：
    // 2x? + 3x + 5n ≡ 0 (mod 77)
    //
    // 因为 x 最多 10^6，不可能遍历所有 x
    // 但我们只需要知道：对于每个余数 r，满足条件的 x 的 f(x) 之和
    //
    // 关键：条件只取决于 x mod 77 和 n mod 77
    // 对于给定的 n，我们枚举 x 的余数 r（0~76），检查是否满足条件
    // 然后把 sumByResidue[r] 加到答案中
    //
    // 但注意：sumByResidue[r] 包含了所有 x（1~MAXN）中余数为 r 的 f(x) 之和
    // 如果 n < MAXN，我们不能包含 x > n 的部分！
    //
    // 所以需要按余数分类的前缀和：pref[r][k] = 前 k 个余数为 r 的 f(x) 之和
    // 但这样需要 77 * (MAXN/77) ≈ 77 * 12987 ≈ 10^6 空间，可以接受
    //
    // 更简单的方法：直接遍历 x（但只遍历到 n），利用余数分组优化
    //
    // 实际上 MAXN=10^6，对每个 n 遍历所有 x 仍然超时（O(q*n)）
    // 所以我们需要更高效的查询方法
}

// ============================================================
// 更好的预处理：按余数分组存储
// ============================================================
vector<int> groupByResidue[77];   // groupByResidue[r] 存储所有 x%77==r 的 f(x)
vector<ll> prefByResidue[77];     // prefByResidue[r][k] = 前 k 个 f(x) 之和

void initGroups() {
    // 按余数分组
    for (int x = 1; x <= MAXN; x++) {
        int y = minPrime[x];
        int f = factorCnt[x + y];
        int r = x % 77;
        groupByResidue[r].push_back(f);
    }

    // 对每个余数类做前缀和
    for (int r = 0; r < 77; r++) {
        prefByResidue[r].resize(groupByResidue[r].size() + 1, 0);
        for (int i = 0; i < (int)groupByResidue[r].size(); i++) {
            prefByResidue[r][i + 1] = prefByResidue[r][i] + groupByResidue[r][i];
        }
    }
}

// ============================================================
// 查询函数：O(77 * log(MAXN)) 或 O(77)
// ============================================================
ll query(int n) {
    ll res = 0;
    int nMod = n % 77;

    // 枚举 x 的余数 r (0~76)
    for (int r = 0; r < 77; r++) {
        // 计算当 x % 77 == r 时，表达式 mod 77 的值
        // 2x? + 3x + 5n ≡ 2*r? + 3*r + 5*nMod (mod 77)
        ll exprMod = (2LL * r * r + 3LL * r + 5LL * nMod) % 77;

        if (exprMod == 0) {
            // 这个余数类满足条件
            // 需要加上所有 x≤n 且 x%77==r 的 f(x)
            // 用二分查找找到这个余数类中 ≤ n 的个数
            auto &vec = groupByResidue[r];
            // 计算这个余数类中对应的 x 有多少个 ≤ n
            // 因为 groupByResidue[r] 中的元素是**按 x 从小到大**存放的
            // 但注意：groupByResidue 里只存了 f(x)，没存 x！
            // 需要同时存 x 和 f(x)
        }
    }
    return res;
}

// ============================================================
// 更完整的版本：存储 pair(x, f)
// ============================================================
vector<pair<int, int>> groupByResidue2[77];   // (x, f(x))
vector<ll> prefByResidue2[77];                // 前缀和

void initGroups2() {
    for (int x = 1; x <= MAXN; x++) {
        int y = minPrime[x];
        int f = factorCnt[x + y];
        int r = x % 77;
        groupByResidue2[r].push_back({x, f});
    }

    for (int r = 0; r < 77; r++) {
        prefByResidue2[r].resize(groupByResidue2[r].size() + 1, 0);
        for (int i = 0; i < (int)groupByResidue2[r].size(); i++) {
            prefByResidue2[r][i + 1] = prefByResidue2[r][i] + groupByResidue2[r][i].second;
        }
    }
}

ll query2(int n) {
    ll res = 0;
    int nMod = n % 77;

    for (int r = 0; r < 77; r++) {
        ll exprMod = (2LL * r * r + 3LL * r + 5LL * nMod) % 77;
        if (exprMod == 0) {
            auto &vec = groupByResidue2[r];
            // 二分查找：找到最后一个 x ≤ n 的位置
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
                res += prefByResidue2[r][pos + 1];
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