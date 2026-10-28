//
// Created by 28447 on 2026/9/22.
//
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 111111;
const int MOD = 10007;

// 快读模板 (提高读入速度)
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

// 定义结构体，清晰表示我们需要维护的 4 个前缀和状态
// 状态属于同一个 (颜色, 奇偶性) 组
struct GroupState {
    long long cnt = 0;       // 组内元素个数 (k)
    long long sum_x_num = 0; // 组内 ∑(x * number_x)
    long long sum_num = 0;   // 组内 ∑number_z
    long long sum_x = 0;     // 组内 ∑z
};

int num[MAXN];
int col[MAXN];
GroupState states[MAXN][2]; // 第一维颜色，第二维奇偶性(0/1)

int main() {
    int n = read();
    int m = read();

    for (int i = 1; i <= n; i++) {
        num[i] = read();
    }
    for (int i = 1; i <= n; i++) {
        col[i] = read();
    }

    long long ans = 0;

    // 从左到右遍历每个格子，把它当作三元组的右侧格子 z
    for (int i = 1; i <= n; i++) {
        int c = col[i];
        int p = i % 2; // 奇偶性

        // 获取当前 (颜色, 奇偶性) 组的历史前缀和
        GroupState& s = states[c][p];

        long long current_x = i;
        long long current_num = num[i];

        // ---------------------------------------------------------
        // 计算当前格子与前面所有满足条件的 x 配对产生的新增分数
        // 根据乘法分配律展开：∑(x + z)(num_x + num_z)
        // = ∑(x * num_x) + num_z * ∑x + z * ∑num_x + z * num_z * ∑1
        // ---------------------------------------------------------

        // 1. ∑(x * num_x) 部分
        ans = (ans + s.sum_x_num) % MOD;

        // 2. num_z * ∑x 部分
        ans = (ans + (current_num % MOD) * (s.sum_x % MOD)) % MOD;

        // 3. z * ∑num_x 部分
        ans = (ans + (current_x % MOD) * (s.sum_num % MOD)) % MOD;

        // 4. z * num_z * k 部分
        ans = (ans + s.cnt % MOD * (current_x % MOD) % MOD * (current_num % MOD)) % MOD;

        // ---------------------------------------------------------
        // 将当前格子加入前缀和，供后面的格子配对使用
        // ---------------------------------------------------------
        s.cnt++;
        s.sum_x_num = (s.sum_x_num + (current_x % MOD) * (current_num % MOD)) % MOD;
        s.sum_num = (s.sum_num + current_num) % MOD;
        s.sum_x = (s.sum_x + current_x) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
#include <iostream>
#include <vector>
// using namespace std;
//
// const int MOD = 10007;
//
// int main() {
//     int n, m;
//     cin >> n >> m;
//
//     vector<int> number(n + 1);
//     vector<int> color(n + 1);
//
//     for (int i = 1; i <= n; i++) cin >> number[i];
//     for (int i = 1; i <= n; i++) cin >> color[i];
//
//     // 用于存储每个 (颜色, 奇偶性) 组的状态
//     // key = color * 2 + (i % 2)
//     // 分别维护：cnt(个数), sum_f(编号和), sum_n(数字和), sum_fn(编号*数字和)
//     struct Group {
//         long long cnt = 0;
//         long long sum_f = 0;
//         long long sum_n = 0;
//         long long sum_fn = 0;
//     };
//     vector<Group> groups(m * 2 + 1);
//
//     long long ans = 0;
//
//     for (int i = 1; i <= n; i++) {
//         int c = color[i];
//         int p = i % 2;
//         int idx = c * 2 + p; // 构造唯一键
//
//         long long f = i;          // 当前格子的编号
//         long long num = number[i]; // 当前格子的数字
//
//         // 1. 计算当前格子与前面所有同组格子产生的新增分数
//         long long delta = 0;
//         delta = (delta + groups[idx].sum_fn) % MOD;
//         delta = (delta + (num % MOD) * (groups[idx].sum_f % MOD)) % MOD;
//         delta = (delta + (f % MOD) * (groups[idx].sum_n % MOD)) % MOD;
//         delta = (delta + groups[idx].cnt * (f % MOD) * (num % MOD)) % MOD;
//
//         ans = (ans + delta) % MOD;
//
//         // 2. 将当前格子加入该组的统计数据中
//         groups[idx].cnt++;
//         groups[idx].sum_f = (groups[idx].sum_f + f) % MOD;
//         groups[idx].sum_n = (groups[idx].sum_n + num) % MOD;
//         groups[idx].sum_fn = (groups[idx].sum_fn + (f % MOD) * (num % MOD)) % MOD;
//     }
//
//     cout << ans % MOD << endl;
//
//     return 0;
// }