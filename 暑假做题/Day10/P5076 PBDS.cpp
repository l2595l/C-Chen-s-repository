//
// Created by 28447 on 2026/8/22.
//
// 题目：洛谷 P5076「普通二叉树」—— PBDS 平衡树「偷懒版」
// 支持：1 查排名 / 2 查第 k 小 / 3 查前驱 / 4 查后继 / 5 插入
//
// 说明：
//   这是 GNU 扩展 pb_ds（Policy-Based Data Structure）里现成的红黑树，
//   自带按名次取数（find_by_order）和查排名（order_of_key），几行就能过题。
//   但它是「黑盒」，学不到平衡树原理；且部分竞赛（NOI/CSP）环境可能不提供，
//   只建议应急/对拍时使用，平时请用 FHQ Treap 版本。
//
// 注意 less_equal 的一个坑：
//   用 less_equal<int> 作比较器时，order_of_key(k) 返回的是「≤ k 的元素个数」，
//   而不是常见的「< k」。所以求排名/前驱时要自己换算（见代码注释）。
//
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// 可重复元素的有序平衡树（红黑树）
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update> oset;

oset T;

// 快速读入（支持负数）
inline int read() {
    int r = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') w = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { r = (r << 3) + (r << 1) + (ch ^ 48); ch = getchar(); }
    return r * w;
}

int main() {
    int n = read();
    while (n--) {
        int opt = read(), x = read();
        if (opt == 1) {
            // 排名 = 小于 x 的个数 + 1；而 order_of_key(x-1) = 「≤ x-1」= 小于 x 的个数
            printf("%d\n", (int)T.order_of_key(x - 1) + 1);
        } else if (opt == 2) {
            // 第 x 小 = 排序后下标 x-1 处的元素
            printf("%d\n", *T.find_by_order(x - 1));
        } else if (opt == 3) {
            // 前驱 = 小于 x 的最大数，下标 = (小于 x 的个数) - 1
            int cnt = (int)T.order_of_key(x - 1);
            if (cnt == 0) printf("-2147483647\n");        // 无前驱
            else printf("%d\n", *T.find_by_order(cnt - 1));
        } else if (opt == 4) {
            // 后继 = 大于 x 的最小数，下标 = (≤ x 的个数) = order_of_key(x)
            int cnt = (int)T.order_of_key(x);
            if (cnt == (int)T.size()) printf("2147483647\n"); // 无后继
            else printf("%d\n", *T.find_by_order(cnt));
        } else {
            T.insert(x);                                   // 插入
        }
    }
    return 0;
}