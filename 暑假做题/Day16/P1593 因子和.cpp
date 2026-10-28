//
// Created by 28447 on 2026/8/29.
//
#include <iostream>
#include <cstdio>
using namespace std;

const int MOD = 9901;  // 模数，是质数

int a, b;
int factors[10010][2];  // factors[i][0] = 质因子p, factors[i][1] = 指数k
int factorCnt = 0;      // 质因子个数
int ans = 1;            // 最终答案

// ============================================
// 快速幂：计算 base^exp % MOD
// 时间复杂度 O(log exp)
// 核心思想：二进制分解指数，边乘边取模
// ============================================
long long quickPow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {                    // 当前二进制位为1
            res = (res * base) % MOD;     // 乘到结果上，立即取模
        }
        base = (base * base) % MOD;       // base自乘（平方），立即取模
        exp >>= 1;                        // 右移一位
    }
    return res;
}

// ============================================
// 计算等比数列和：1 + p + p^2 + ... + p^(k*b)  mod MOD
//
// 【核心疑难点1：为什么要乘以b？】
//   因为 a = p1^k1 * p2^k2 * ...
//   所以 a^b = p1^(k1*b) * p2^(k2*b) * ...
//   每个质因子的指数都要乘以 b
//
// 【核心疑难点2：为什么分两种情况？】
//   公式 S = (p^(n+1) - 1) / (p - 1)
//   在模运算中不能直接除，要转为乘逆元
//   但逆元存在的条件是 gcd(p-1, MOD) = 1
//   当 p % MOD == 1 时，p-1 是 MOD 的倍数，逆元不存在
// ============================================
long long calcSum(long long p, long long k) {
    long long n = k * b;  // 指数乘以b，因为求的是a^b的因子和

    // 【核心疑难点3：逆元不存在时怎么办？】
    // 当 p % MOD == 1 时：
    //   p^0 ≡ p^1 ≡ p^2 ≡ ... ≡ p^n ≡ 1 (mod MOD)
    //   所以 S = 1 + 1 + ... + 1 = n + 1 (mod MOD)
    //   直接O(1)算出，不需要任何循环或递归！
    if (p % MOD == 1) {
        return (n + 1) % MOD;
    }

    // 【核心疑难点4：逆元存在时怎么算？】
    // 用等比数列公式：S = (p^(n+1) - 1) / (p - 1)
    // 除法转为乘法：S = (p^(n+1) - 1) * (p-1)^(-1)  (mod MOD)
    //
    // 【核心疑难点5：费马小定理怎么用？】
    // 因为 MOD = 9901 是质数，且 p-1 不是 MOD 的倍数
    // 所以 (p-1)^(-1) ≡ (p-1)^(MOD-2)  (mod MOD)
    // 这就是 quickPow(p-1, MOD-2) 的由来

    // ----- 第1步：计算分子 (p^(n+1) - 1) mod MOD -----
    // quickPow(p % MOD, n + 1) 计算 p^(n+1) % MOD
    // 减 1 后可能为负数，加 MOD 再取模保证结果在 [0, MOD-1] 范围内
    long long numerator = (quickPow(p % MOD, n + 1) - 1 + MOD) % MOD;
    // ----- 第2步：计算分母 (p-1) 的逆元 -----
    // 根据费马小定理：当 MOD 是质数且 a 不是 MOD 的倍数时
    // a^(-1) ≡ a^(MOD-2) (mod MOD)
    // 所以 (p-1)^(-1) ≡ (p-1)^(MOD-2) (mod MOD)
    long long denominatorInv = quickPow((p - 1) % MOD, MOD - 2);
    // ----- 第3步：分子 × 分母的逆元，再取模 -----
    // 即 S = (p^(n+1) - 1) × (p-1)^(-1) (mod MOD)
    // 这就相当于在模意义下完成了除法
    return numerator * denominatorInv % MOD;
}

// ============================================
// 质因数分解
// 时间复杂度 O(√a)
//
// 【核心疑难点6：为什么最后要判断 a != 1？】
//   循环条件是 i*i <= a，当循环结束时：
//   如果 a 被完全分解，a 会变成 1
//   如果 a 还剩一个大于 √(原a) 的质因子，a 会 > 1
//   这个剩余的质因子指数一定是1（因为如果有平方，早就被除了）
// ============================================
void factorize(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            factorCnt++;
            factors[factorCnt][0] = i;    // 记录质因子 p
            factors[factorCnt][1] = 0;    // 指数先置0

            while (x % i == 0) {
                factors[factorCnt][1]++;  // 指数加1
                x /= i;
            }
        }
    }
    // 如果 x 还大于1，说明剩下的 x 是一个质因子
    if (x > 1) {
        factorCnt++;
        factors[factorCnt][0] = x;
        factors[factorCnt][1] = 1;
    }
}

// ============================================
// 主函数
// ============================================
int main() {
    scanf("%d%d", &a, &b);

    // 特判：a=0时因子和为0（虽然题目保证a>=1）
    if (a == 0) {
        printf("0\n");
        return 0;
    }

    // 分解质因数
    factorize(a);

    // 对每个质因子，计算其等比数列和，然后累乘
    for (int i = 1; i <= factorCnt; i++) {
        long long p = factors[i][0];      // 质因子
        long long k = factors[i][1];      // 指数
        long long sum = calcSum(p, k);    // 计算 1+p+...+p^(k*b)
        ans = ans * sum % MOD;
    }//模运算对乘法满足分配律：(A×B)modM=((AmodM)×(BmodM))modM

    printf("%d\n", ans);
    return 0;
}