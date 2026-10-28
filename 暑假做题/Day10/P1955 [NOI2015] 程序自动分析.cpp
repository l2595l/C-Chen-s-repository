//
// Created by 28447 on 2026/8/22.
//
#include <cstdio>      // scanf, printf
#include <algorithm>   // sort, lower_bound, unique
using namespace std;

// ========== 常量与数组定义 ==========
const int MAXN = 1000005;      // 最大操作数
int f[MAXN];                   // 并查集父数组：f[i] 表示 i 的父节点
int book[MAXN * 2];            // 离散化临时数组：存储所有出现过的值（最多 2n 个）

// 结构体：存储每条约束
struct node {
    int x, y, e;               // x, y 是变量（需要离散化），e 是约束类型（1=相等，0=不等）
} a[MAXN];                     // 存储所有约束

// ========== 比较函数 ==========
// 按照 e 降序排列，让 e=1（相等约束）排在前面
// 原因：必须先处理所有相等关系，再检查不等关系是否矛盾
bool cmp(node a, node b) {
    return a.e > b.e;          // e=1 排在 e=0 前面
}

// ========== 并查集初始化 ==========
// 初始化 [0, n] 范围内的所有节点
void init(int n) {
    for(int i = 0; i <= n; i++) {
        f[i] = i;              // 每个节点的父节点指向自己
    }
}

// ========== 并查集查找（路径压缩） ==========
// 查找 x 所在集合的根节点，同时进行路径压缩
int find(int x) {
    if(f[x] == x) return x;    // 自己是根节点
    return f[x] = find(f[x]);  // 递归查找并压缩路径
}

// ========== 主函数 ==========
int main() {
    int T;                     // 测试数据组数
    scanf("%d", &T);

    while(T--) {               // 循环处理每组数据
        int n;                 // 本组数据的约束数量
        scanf("%d", &n);

        int tot = 0;           // book 数组的计数器，从 0 开始

        // ---------- 1. 读入所有约束，同时收集需要离散化的值 ----------
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].e);
            // 将 x 和 y 存入 book 数组，准备离散化
            // 使用 tot++ 先赋值再自增，从 book[0] 开始存放
            book[tot++] = a[i].x;
            book[tot++] = a[i].y;
        }
        // 此时 tot = 2n，book 中存放了所有 x 和 y 的值

        // ---------- 2. 排序 + 去重（离散化核心） ----------
        // 排序：book 中的值升序排列
        sort(book, book + tot);
        // 去重：unique 将重复元素移到末尾，返回去重后的新末尾迭代器
        // reu 表示去重后元素的个数
        int reu = unique(book, book + tot) - book;
        // 此时 book[0] ~ book[reu-1] 是所有不同的值

        // ---------- 3. 将原始值映射为排名（离散化） ----------
        // 用 lower_bound 查找每个值在 book 中的位置，映射为 1-based 编号
        for(int i = 1; i <= n; i++) {
            // lower_bound 返回第一个 >= a[i].x 的迭代器
            // 减去 book 得到 0-based 索引，+1 转为 1-based
            a[i].x = lower_bound(book, book + reu, a[i].x) - book + 1;
            a[i].y = lower_bound(book, book + reu, a[i].y) - book + 1;
        }
        // 离散化后：x, y 的范围变为 [1, reu]

        // ---------- 4. 初始化并查集 ----------
        // 需要初始化 [0, reu]，因为映射后的值是 1..reu
        init(reu + 1);

        // ---------- 5. 约束排序：相等约束优先 ----------
        sort(a + 1, a + n + 1, cmp);  // a[1] ~ a[n] 按 e 降序排列

        // ---------- 6. 并查集处理所有约束 ----------
        bool flag = true;              // 标记是否满足所有约束

        for(int i = 1; i <= n; i++) {
            // 查找 x 和 y 所在集合的根节点
            int rx = find(a[i].x);
            int ry = find(a[i].y);

            if(a[i].e == 1) {          // 约束：x == y
                // 合并两个集合：将 rx 的父节点设为 ry
                if(rx != ry) {
                    f[rx] = ry;        // 合并操作
                }
                // 如果 rx == ry，说明已经在同一集合，不需要操作
            } else {                   // 约束：x != y
                if(rx == ry) {         // 如果 x 和 y 在同一集合
                    flag = false;      // 矛盾！x == y 且 x != y 不可能同时成立
                    break;             // 提前退出循环
                }
            }
        }

        // ---------- 7. 输出结果 ----------
        // 如果所有约束都满足，输出 YES；否则输出 NO
        printf("%s\n", flag ? "YES" : "NO");
    }

    return 0;
}