//
// Created by 28447 on 2026/8/17.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long

template<class I>
inline void read(I &num) {
    num = 0;
    char c = getchar(), up = c;
    while (!isdigit(c)) up = c, c = getchar();
    while (isdigit(c)) num = (num << 1) + (num << 3) + (c ^ '0'), c = getchar();
    up == '-' ? num = -num : 0;
}

const int MAXN = 1000000;
const int MAXZ = 2 * MAXN + 5; // z = x + spf(x) 最大到 2×10^6
int minPrime[MAXN + 5]; // 最小质因子 = 除 1 外最小正因子
int factorCnt[MAXZ + 5]; // 因子个数
ll ans[MAXN + 5];

void initMinPrime() {
    vector<int> primes;
    for (int i = 2; i <= MAXN; i++) {
        if (minPrime[i] == 0) {
            minPrime[i] = i;
            primes.push_back(i);
        }
        for (int p: primes) {
            if (p > minPrime[i] || 1LL * i * p > MAXN) break;
            minPrime[i * p] = p;
        }
    }
}

void initFactorCnt() {
    for (int i = 1; i <= MAXZ; i++)
        for (int j = i; j <= MAXZ; j += i)
            factorCnt[j]++;
}

ll sumResidue[77]; // sumResidue[r] = Σ_{x≤n, x≥2, x%77==r} d(x+spf(x))
vector<int> valid[77]; // valid[m] = { r : (2r?+3r+5m) % 77 == 0 }

void initAns() {
    // 预处理：m = n%77 时，哪些余数 r 满足条件
    for (int m = 0; m < 77; m++)
        for (int r = 0; r < 77; r++)
            if ((2 * r * r + 3 * r + 5 * m) % 77 == 0)
                valid[m].push_back(r);

    for (int n = 1; n <= MAXN; n++) {
        if (n >= 2) {
            // x=1 无合法 y，跳过
            int y = minPrime[n];
            sumResidue[n % 77] += factorCnt[n + y]; // 加入 x = n 的贡献
        }
        ll s = 0;
        for (int r: valid[n % 77]) s += sumResidue[r];
        ans[n] = s; // 单个 n 的答案，不累计
    }
}

int main() {

    initMinPrime();
    initFactorCnt();
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

//////////注释版
// #include <bits/stdc++.h>
// // 万能头文件，包含了C++所有标准库，方便但不推荐在大型项目中使用
// using namespace std;
// // 使用标准命名空间，这样可以直接用 cin/cout/vector 等，不用写 std::
//
// #define ll long long
// // 宏定义：把 ll 替换为 long long，简化长整型的写法
//
// // ============================================================
// // 快速读入函数模板
// // ============================================================
// // template <class I> 表示这是一个模板函数，可以适配 int/long long 等不同类型
// template <class I>
// inline void read(I &num){    // inline 建议编译器内联展开，提高速度
//     num = 0;                 // 初始化结果为 0
//     char c = getchar();      // 读入一个字符
//     char up = c;             // 记录第一个字符，用于判断正负号
//
//     // 跳过所有非数字字符（如空格、换行、负号等）
//     while(!isdigit(c)) {
//         up = c;              // 更新 up 为当前字符
//         c = getchar();       // 继续读下一个字符
//     }
//
//     // 当 c 是数字字符时，循环累加
//     while(isdigit(c)) {
//         // (num << 1) + (num << 3) 等价于 num * 2 + num * 8 = num * 10
//         // (c ^ '0') 等价于 c - '0'，把字符 '0'~'9' 转为数字 0~9
//         num = (num << 1) + (num << 3) + (c ^ '0');
//         c = getchar();       // 读下一个字符
//     }
//
//     // 如果最开始读到的负号，把结果变成负数
//     up == '-' ? num = -num : 0;
//     return;                  // 函数结束
// }
//
// // ============================================================
// // 常量定义
// // ============================================================
// const int MAXN = 1000000;      // 题目中 n 的最大值：10^6
// int minPrime[MAXN + 5];        // minPrime[i] 表示 i 的最小质因子
// int factorCnt[MAXN + 5];       // factorCnt[i] 表示 i 的正因子个数
// ll ans[MAXN + 5];              // ans[n] 表示 n 对应的答案（预处理）
//
// // ============================================================
// // 函数1：欧拉筛（线性筛）求每个数的最小质因子
// // ============================================================
// void initMinPrime() {
//     vector<int> primes;        // 用于存储已经找到的质数
//
//     // 从 2 开始遍历到 MAXN
//     for (int i = 2; i <= MAXN; i++) {
//         // 如果 minPrime[i] == 0，说明 i 还没有被标记过
//         // 意味着 i 是质数（因为所有合数都会被它的最小质因子标记）
//         if (minPrime[i] == 0) {
//             minPrime[i] = i;   // 质数的最小质因子就是它本身
//             primes.push_back(i); // 把这个质数加入 primes 列表
//         }
//
//         // 遍历已有的质数列表
//         for (int p : primes) {
//             // 两个退出条件（欧拉筛的核心）：
//             // 条件1：如果 p > minPrime[i]，说明 p 不是 i 的最小质因子，退出
//             // 条件2：如果 i * p > MAXN，超出范围，退出
//             if (p > minPrime[i] || 1LL * i * p > MAXN) break;
//
//             // 标记 i * p 的最小质因子为 p
//             minPrime[i * p] = p;
//         }
//     }
// }
//
// // ============================================================
// // 函数2：求每个数的因子个数
// // ============================================================
// void initFactorCnt() {
//     // 枚举因子 i
//     for (int i = 1; i <= MAXN; i++) {
//         // 枚举 i 的所有倍数 j = i, 2i, 3i, ...
//         // 对于每个 j，i 都是 j 的一个因子，所以 factorCnt[j]++
//         for (int j = i; j <= MAXN; j += i) {
//             factorCnt[j]++;    // 每找到一个因子就加 1
//         }
//     }
// }
//
// // ============================================================
// // 函数3：预处理所有 n 的答案
// // ============================================================
// void initAns() {
//     // 从 1 到 MAXN 依次计算答案
//     for (int n = 1; n <= MAXN; n++) {
//         ans[n] = ans[n - 1];   // 继承上一个 n 的答案（因为 n 增大后，x 的范围变大了）
//
//         // 遍历所有可能的 x (1 ≤ x ≤ n)
//         for (int x = 1; x <= n; x++) {
//             // 计算表达式 2*x? + 3*x + 5*n
//             // 用 2LL 让整个计算变成 long long，避免溢出
//             ll expr = 2LL * x * x + 3LL * x + 5LL * n;
//
//             // 判断是否能被 77 整除
//             if (expr % 77 == 0) {
//                 // 条件满足时：
//                 // y = x 的最小质因子（除 1 以外最小的正因子 = 最小质因子）
//                 int y = minPrime[x];
//
//                 // z = x + y 的因子个数
//                 // 把 z 累加到 ans[n] 中
//                 ans[n] += factorCnt[x + y];
//             }
//         }
//     }
// }
//
// // ============================================================
// // 主函数
// // ============================================================
// int main() {
//     // 关闭 C++ 输入输出流与 C 标准输入输出的同步，提高 cin/cout 速度
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);          // 解除 cin 和 cout 的绑定，进一步提高速度
//
//     // 调用三个预处理函数
//     initMinPrime();            // 计算每个数的最小质因子
//     initFactorCnt();           // 计算每个数的因子个数
//     initAns();                 // 预处理所有 n 的答案
//
//     int q;                     // 询问次数
//     read(q);                   // 使用快速读入读取 q
//
//     // 循环处理 q 次询问
//     while (q--) {
//         int n;                 // 当前询问的 n
//         read(n);               // 快速读入 n
//
//         // 直接输出预处理好的答案
//         cout << ans[n] << '\n'; // 用 '\n' 而不是 endl（endl 会刷新缓冲区，较慢）
//     }
//
//     return 0;                  // 程序正常结束
// }














