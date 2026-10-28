//
// Created by 28447 on 2026/10/20.
//
#include <iostream>
#include <map>
#include <vector>

// 输入：第一行 total，第二行 total 个正整数。
// 从中取出两个数 n、m，使 n * m == total - 2，其余 total - 2 个数任意排列。
// 输出：所有 (n, m) 有序取法对应的不同排列数之和，对 1e9+7 取模。

using Int = long long;
constexpr Int kMod = 1'000'000'007;

Int PowMod(Int base, Int exponent) {
    Int result = 1;
    base %= kMod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % kMod;
        }
        base = base * base % kMod;
        exponent >>= 1;
    }
    return result;
}

// 预处理 0..limit 的阶乘与阶乘逆元。
// 只做一次快速幂求 limit! 的逆元，再倒推出其余逆元。
struct Factorials {
    std::vector<Int> fact;
    std::vector<Int> invFact;

    explicit Factorials(int limit) : fact(limit + 1, 1), invFact(limit + 1, 1) {
        for (int i = 1; i <= limit; ++i) {
            fact[i] = fact[i - 1] * i % kMod;
        }
        invFact[limit] = PowMod(fact[limit], kMod - 2);
        for (int i = limit; i > 0; --i) {
            invFact[i - 1] = invFact[i] * i % kMod;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total = 0;
    std::cin >> total;

    // product = n * m 需要满足的乘积
    const int product = total - 2;
    if (product < 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::map<int, int> count;  // 每个数值出现的次数
    for (int i = 0; i < total; ++i) {
        int value = 0;
        std::cin >> value;
        ++count[value];
    }

    const Factorials factorials(total);

    // 完整多重集去掉两个数之后的排列数为
    //   product! / ∏ (c_v')!   （c_v' 为去掉后的出现次数）
    // 先对未去掉任何数的次数 c_v 算出 baseline = product! * ∏ 1/c_v!，
    // 每个因子对再按去掉的数做 O(1) 修正：
    // n=m时，  去掉一个 v：1/(c-1)! = c / c! => baseline *a*b
    // n!=m时， 一个数拿走两次1/(c-2)! = c（c-1） / c!，故乘a(a-1)=>baseline * a * (a-1)


    //算基准值
    Int baseline = factorials.fact[product];
    for (const auto& entry : count) {
        baseline = baseline * factorials.invFact[entry.second] % kMod;
    }
    //查次数工具
    auto countOf = [&count](int value) {
        auto it = count.find(value);
        return it == count.end() ? 0 : it->second;
    };
    //a、b:拿走的两个数出现的次数
    // 枚举 product 的因子 factor，另一个数为 product / factor。
    // 返回取 (factor, product / factor) 时的排列数，取不到时返回 0。
    auto arrangements = [&](int factor) -> Int {
        const int other = product / factor;
        const Int a = countOf(factor);
        const Int b = countOf(other);
        if (factor == other) {
            if (a < 2) {
                return 0;  // 同一个数要取两次，至少得出现两次
            }
            return baseline * a % kMod * (a - 1) % kMod;
        }
        if (a == 0 || b == 0) {
            return 0;
        }
        return baseline * a % kMod * b % kMod;
    };
    //枚举因子
    Int answer = 0;
    for (int factor = 1; static_cast<Int>(factor) * factor <= product; ++factor) {//1LL * factor * factor转换类型
        if (product % factor != 0) {
            continue;
        }
        const int other = product / factor;
        answer = (answer + arrangements(factor)) % kMod;
        if (other != factor) {
            // (factor, other) 与 (other, factor) 是两个不同的有序取法，各贡献一次
            answer = (answer + arrangements(other)) % kMod;
        }
    }

    std::cout << answer << std::endl;
    return 0;
}
