//
// Created by 28447 on 2026/8/22.
//
// 题目：洛谷 P5076「普通二叉树」（二叉搜索树模板）
// 维护一个「可能有重复元素」的集合，支持 5 种操作：
//   1 x  查询 x 的排名（= 比 x 小的数的个数 + 1）
//   2 x  查询排名为 x 的数（从小到大第 x 个）
//   3 x  查询 x 的前驱（集合中小于 x 的最大数，不存在输出 -2147483647）
//   4 x  查询 x 的后继（集合中大于 x 的最小数，不存在输出 2147483647）
//   5 x  插入 x
//
// 实现：二叉搜索树（BST），用数组存储，不做旋转/平衡。
//   - 时间复杂度：平均 O(log n)，最坏 O(n)（数据有序插入会退化成一条链）。
//   - 本题数据较温和可通过；遇到严格数据应改用平衡树（Treap/Splay 等）。
//
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7fffffff;            // 2147483647，用作「不存在」时的哨兵值

struct Node {
    int val;        // 节点存的值
    int siz;        // 以该节点为根的子树大小（重复的 cnt 也计入）
    int cnt;        // 该值出现的次数（支持重复元素）
    int ls, rs;     // 左右儿子编号，0 表示空节点
} tree[1000010];

int tot;            // 已分配节点数（下一个新节点的编号）。编号 0 是「空节点」哨兵

// ------------------------- 插入 -------------------------
// 向以 x 为根的子树插入值 v
void insert(int x, int v) {
    tree[x].siz++;                    // 路径上每个节点的子树都变大 1
    if (tree[x].val == v) {           // 该值已存在：只加出现次数
        tree[x].cnt++;
        return;
    }
    if (tree[x].val > v) {            // v 更小，去左子树
        if (tree[x].ls != 0)
            insert(tree[x].ls, v);
        else {                        // 左子树为空，新建叶子节点
            tree[++tot] = {v, 1, 1, 0, 0};   // val=v, siz=1, cnt=1, ls=0, rs=0
            tree[x].ls = tot;
        }
    } else {                          // v 更大，去右子树
        if (tree[x].rs != 0)
            insert(tree[x].rs, v);
        else {
            tree[++tot] = {v, 1, 1, 0, 0};
            tree[x].rs = tot;
        }
    }
}

// ------------------------- 查询前驱 -------------------------
// 前驱 = 集合中小于 v 的最大数
// 参数 ans 记录沿途「已经遇到的小于 v 的最大候选值」，初始传 -INF（表示暂无）
int predecessor(int x, int v, int ans) {
    if (tree[x].val >= v) {                 // 当前值 >= v，不是前驱，只能去左子树找
        if (tree[x].ls == 0) return ans;    // 无左子树，答案就是沿途记下的 ans
        return predecessor(tree[x].ls, v, ans);
    } else {                                // 当前值 < v，是候选前驱
        if (tree[x].rs == 0) return tree[x].val;      // 右子树为空，当前值即答案
        return predecessor(tree[x].rs, v, tree[x].val);// 去右子树找更大的，带上当前值
    }
}

// ------------------------- 查询后继 -------------------------
// 后继 = 集合中大于 v 的最小数（与前驱完全对称）
// ans 记录沿途「已经遇到的大于 v 的最小候选值」，初始传 INF
int successor(int x, int v, int ans) {
    if (tree[x].val <= v) {                 // 当前值 <= v，不是后继，去右子树
        if (tree[x].rs == 0) return ans;
        return successor(tree[x].rs, v, ans);
    } else {                                // 当前值 > v，是候选后继
        if (tree[x].ls == 0) return tree[x].val;
        return successor(tree[x].ls, v, tree[x].val);
    }
}

// ------------------------- 查询第 rk 小的数 -------------------------
// 利用子树大小 siz 快速定位：rk 从 1 开始
int kth_value(int x, int rk) {
    if (x == 0) return INF;                           // 理论上不会走到，防御性返回
    int ls = tree[x].ls;
    if (tree[ls].siz >= rk)                           // 左子树已经能装下第 rk 个
        return kth_value(ls, rk);
    if (tree[ls].siz + tree[x].cnt >= rk)             // 第 rk 个正好落在当前节点（含重复）
        return tree[x].val;
    return kth_value(tree[x].rs,                      // 否则去右子树，rank 减去左子树和当前
                     rk - tree[ls].siz - tree[x].cnt);
}

// ------------------------- 查询比 v 小的元素个数 -------------------------
int count_less(int x, int v) {
    if (x == 0) return 0;
    if (v == tree[x].val) return tree[tree[x].ls].siz; // 等于 v：只算左子树（全小于 v）
    if (v < tree[x].val)  return count_less(tree[x].ls, v); // v 更小：去左子树
    return count_less(tree[x].rs, v)                    // v 更大：去右子树，
           + tree[tree[x].ls].siz + tree[x].cnt;        // 左子树和当前节点全都 < v
}

// ------------------------- 快速读入 -------------------------
// 比 scanf 更快，适合大数据量
int read() {
    int r = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();   // 跳过空格、换行等非数字
    while (ch >= '0' && ch <= '9') {
        r = (r << 3) + (r << 1) + (ch ^ 48);       // r*8 + r*2 + 数字 = r*10 + 数字
        ch = getchar();
    }
    return r;
}

int main() {
    int n = read();
    while (n--) {
        int opt = read(), x = read();
        if (opt == 1)      printf("%d\n", count_less(1, x) + 1);   // 排名 = 小于 x 的个数 + 1
        else if (opt == 2) printf("%d\n", kth_value(1, x));        // 第 x 小的数
        else if (opt == 3) printf("%d\n", predecessor(1, x, -INF));// 前驱
        else if (opt == 4) printf("%d\n", successor(1, x, INF));   // 后继
        else {                                                      // 插入
            if (tot == 0) {                 // 树为空：创建根节点
                tot = 1;
                tree[1] = {x, 1, 1, 0, 0};
            } else {
                insert(1, x);
            }
        }
    }
    return 0;
}
