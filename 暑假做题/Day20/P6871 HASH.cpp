//
// Created by 28447 on 2026/9/4.


//双向搜索
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int n, k, m;          // n: 单词长度, k: 目标哈希值, m: 模数 (2的幂次)
int inv;              // 33 在模 m 下的乘法逆元
int64 ans = 0;        // 答案（可能很大，用 long long）

// 动态分配数组大小，避免浪费内存
vector<int> cnt;

// 将字符转换为序号: 'a' -> 1, 'b' -> 2, ..., 'z' -> 26
inline int ord(char c) {
    return c - 'a' + 1;
}

// 正向哈希：从左到右构建字符串
// dep: 剩余要处理的字符数, hash: 当前哈希值
void dfs_forward(int dep, int hash) {
    if (dep == 0) {
        cnt[hash]++;   // 记录这个哈希值出现了多少次
        return;
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        int new_hash = ((hash * 33LL) ^ ord(c)) % m;
        dfs_forward(dep - 1, new_hash);
    }
}

// 反向搜索：从目标哈希值反向推导
// dep: 剩余要处理的字符数, hash: 当前哈希值
void dfs_backward(int dep, int hash) {
    if (dep == 0) {
        ans += cnt[hash];   // 匹配成功，累加方案数
        return;
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        // 逆运算: X = (y ^ i) * inv % m
        int prev_hash = ((hash ^ ord(c)) * 1LL * inv) % m;
        dfs_backward(dep - 1, prev_hash);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m;
    m = 1 << m;  // MOD = 2^m

    // 特殊情况：n 较小时，直接暴力搜索所有可能
    if (n <= 5) {
        // 最多 26^5 = 11,881,376 种，勉强可行
        cnt.assign(m, 0);
        dfs_forward(n, 0);
        cout << cnt[k] << '\n';
        return 0;
    }

    // 求 33 在模 m 下的乘法逆元
    // 即找到 inv 使得 33 * inv ≡ 1 (mod m)
    for (int i = 1; i < m; ++i) {
        if ((33LL * i) % m == 1) {
            inv = i;
            break;
        }
    }

    // 双向搜索：前半段正向，后半段反向
    int half = n / 2;
    int rest = (n + 1) / 2;

    // 分配足够大的数组来存储所有可能的哈希值
    cnt.assign(m, 0);

    // 正向搜索左半部分，记录所有可能的哈希值
    dfs_forward(half, 0);

    // 反向搜索右半部分，匹配中间结果
    dfs_backward(rest, k);

    cout << ans << '\n';
    return 0;
}