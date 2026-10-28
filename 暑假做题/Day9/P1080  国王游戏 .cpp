//
// Created by 28447 on 2026/8/21.
//
// 题目：洛谷 P1080「国王游戏」
//
// 题意：国王和 n 位大臣排成一排，国王在最前面。每位大臣得到的金币数 =
//       「排在他前面所有人左手数的乘积」除以「他自己的右手数」向下取整。
//       请安排大臣顺序，使获得金币最多的人拿到的金币尽可能少，输出这个最小值。
//
// 思路：贪心 + 高精度
//   1) 贪心策略：把大臣按「左手数 × 右手数」从小到大排队，即为最优。
//      正确性（相邻交换法）：设相邻两人 i 在 j 前，他们前面的乘积为 S。
//         交换前两人最大值 = max(S / r_i, S·l_i / r_j)
//         交换后两人最大值 = max(S / r_j, S·l_j / r_i)
//        若 l_i·r_i > l_j·r_j，则 S·l_i/r_j > S·l_j/r_i 且 S·l_i/r_j ≥ S/r_j，
//        故交换后最大值不增，说明应把 l·r 小的人放前面。按乘积升序即最优。
//   2) 数据会很大（乘积可达 10000^1000），必须用高精度：
//      - 维护「当前前缀乘积 sum」（高精度），依次除以每位大臣的右手得到他的金币，
//        取最大值；再把乘积乘上这位大臣的左手，供下一位使用。
//
#include <bits/stdc++.h>
using namespace std;

// ------------------------- 快速读入 -------------------------
// 比 cin 更快，适合大数据量；返回读到的整数（保留负数处理）
int read() {
    int c = getchar();
    // 跳过空格、换行等非数字字符
    while (c != '-' && c != EOF && (c < '0' || c > '9'))
        c = getchar();
    if (c == EOF) exit(0);          // 输入结束则直接退出程序
    int sign = 1;
    if (c == '-') {                 // 处理负号（本题数据非负，保留以防万一）
        sign = -1;
        c = getchar();
    }
    int k = 0;
    while (c >= '0' && c <= '9') {  // 连续读入数字
        k = k * 10 + (c - '0');
        c = getchar();
    }
    return k * sign;
}

// ------------------------- 高精度（万进制） -------------------------
// 用数组表示大整数：每个元素存 4 位十进制（0 ~ 9999），下标越小位越低。
// 例如十进制 123456789 表示为 sum[1]=6789, sum[2]=2345, sum[3]=1。
const int BASE = 10000;             // 万进制基数
const int MAXN = 1010;              // n ≤ 1000，留一点余量

struct node {
    int l, r;                       // 大臣左、右手上的数
} a[MAXN];

int n;                              // 大臣个数
int A, B;                           // 国王左、右手上的数（B 不影响结果，仅读入占位）

int sum[MAXN];                      // 当前前缀乘积：排到某大臣前所有人左手数的乘积
int m;                              // sum 的有效长度（最高位下标）
int ans[MAXN];                      // 当前大臣分到的金币数 = 乘积 / 他的右手数
int ls;                             // ans 的有效长度
int best[MAXN];                     // 全局最大金币数（最终答案）
int lb;                             // best 的有效长度

// 贪心排序：按 l*r 升序；乘积相等时按 r 升序（此 tie-break 非必需，不影响正确性）
bool cmp(const node &u, const node &v) {
    long long pu = 1LL * u.l * u.r; // 用 long long 防止乘法溢出
    long long pv = 1LL * v.l * v.r;
    if (pu == pv) return u.r < v.r;
    return pu < pv;
}

// 高精度除法：ans = sum / a[id].r（低位在前），返回商的有效长度
int divide(int id) {
    int divisor = a[id].r;
    memset(ans, 0, sizeof(ans));
    long long cur = 0;                          // 竖式除法中的当前余数
    for (int i = m; i >= 1; i--) {              // 从最高位到最低位模拟竖式
        cur = cur * BASE + sum[i];              // 余数左移一位，拼上当前位
        ans[i] = cur / divisor;                 // 得到当前位的商
        cur %= divisor;                         // 更新余数
    }
    int len = m;                                // 去掉高位多余的 0
    while (len > 1 && ans[len] == 0) len--;
    return len;
}

// 判断 ans 是否大于 best（两者都是低位在前，长度分别为 ls、lb）
bool greater_than_best() {
    if (ls != lb) return ls > lb;               // 位数多的更大
    for (int i = ls; i >= 1; i--)               // 位数相同，从高位到低位逐位比较
        if (ans[i] != best[i])
            return ans[i] > best[i];
    return false;                               // 完全相等不算「更大」
}

// 高精度乘法：sum *= a[id].l
void multiply(int id) {
    int x = a[id].l;
    for (int i = 1; i <= m; i++)                // 第一步：每一位先乘以 x
        sum[i] *= x;
    for (int i = 1; i <= m; i++) {              // 第二步：从低位到高位统一进位
        sum[i + 1] += sum[i] / BASE;
        sum[i] %= BASE;
    }
    if (sum[m + 1] > 0) m++;                    // 最高位产生进位，长度 +1
}

int main() {
    n = read();
    A = read();
    B = read();                                 // B 用不到，仅消费输入
    for (int i = 1; i <= n; i++) {
        a[i].l = read();
        a[i].r = read();
    }

    sort(a + 1, a + n + 1, cmp);                // 贪心：按 l*r 升序排队

    // 初始化乘积为国王左手数 A，转成万进制存入 sum（低位在前）
    memset(sum, 0, sizeof(sum));
    m = 0;
    int t = A;
    while (t > 0) {                             // 逐位拆分 A
        sum[++m] = t % BASE;
        t /= BASE;
    }
    if (m == 0) { m = 1; sum[1] = 0; }          // 题目保证 A≥1，此分支仅作防御

    // 依次处理每位大臣：先算他的金币数（除以右手），再更新乘积（乘上左手）
    for (int i = 1; i <= n; i++) {
        ls = divide(i);                         // 第 i 位大臣的金币数
        if (greater_than_best()) {              // 若超过历史最大值则更新
            lb = ls;
            memcpy(best, ans, sizeof(ans));
        }
        multiply(i);                            // 乘积乘上他的左手，供下一位使用
    }

    // 输出答案（低位在前，需从最高位开始打印）
    printf("%d", best[lb]);                     // 最高位不带前导 0
    for (int i = lb - 1; i >= 1; i--)
        printf("%04d", best[i]);                // 其余每位补足 4 位（万进制）

    return 0;
}