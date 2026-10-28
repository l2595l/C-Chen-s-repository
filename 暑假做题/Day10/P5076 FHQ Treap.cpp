//
// Created by 28447 on 2026/8/22.
//
// 题目：洛谷 P5076「普通二叉树」—— FHQ Treap（无旋平衡树）最优解
// 支持：1 查排名 / 2 查第 k 小 / 3 查前驱 / 4 查后继 / 5 插入
//
// 为什么用 Treap 而不是普通 BST：
//   普通 BST 遇到「有序插入」会退化成一条链，最坏 O(n)，可能超时甚至递归爆栈。
//   FHQ Treap 给每个节点一个随机优先级，用 split（按值分裂）+ merge（按优先级合并）
//   两个操作维持平衡，期望深度 O(log n)，所有操作都是期望 O(log n)，不随数据退化。
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int INF = 0x7fffffff;            // 2147483647，作「无前驱/后继」时的哨兵值

struct Node {
    int ls, rs;        // 左右儿子编号，0 表示空
    int val;           // 节点值
    int key;           // 随机优先级（维护堆性质，保证平衡）
    int siz;           // 子树大小
} t[N];

int root, tot;                          // 根节点编号、已分配节点数
mt19937 rnd((unsigned)chrono::steady_clock::now().time_since_epoch().count());

// 新建一个值为 v 的节点，返回其编号
int new_node(int v) {
    t[++tot] = {0, 0, v, (int)rnd(), 1};
    return tot;
}

// 更新子树大小
void pushup(int x) {
    t[x].siz = t[t[x].ls].siz + t[t[x].rs].siz + 1;
}

// 分裂：把以 x 为根的树按值 v 分成两棵 —— a 中所有值 ≤ v，b 中所有值 > v
void split(int x, int v, int &a, int &b) {
    if (!x) { a = b = 0; return; }      // 空树，两边都为空
    if (t[x].val <= v) {                // 当前节点归 a，右子树继续分裂
        a = x;
        split(t[x].rs, v, t[x].rs, b);
    } else {                            // 当前节点归 b，左子树继续分裂
        b = x;
        split(t[x].ls, v, a, t[x].ls);
    }
    pushup(x);
}

// 合并：把 a、b 合成一棵（要求 a 中所有值都 < b 中所有值）
int merge(int a, int b) {
    if (!a || !b) return a + b;         // 一边为空直接返回另一边
    if (t[a].key < t[b].key) {          // 小根堆：key 小的作根
        t[a].rs = merge(t[a].rs, b);
        pushup(a);
        return a;
    } else {
        t[b].ls = merge(a, t[b].ls);
        pushup(b);
        return b;
    }
}

// 插入 v
void insert(int v) {
    int a, b;
    split(root, v, a, b);                     // 分成 ≤v 和 >v 两段
    root = merge(merge(a, new_node(v)), b);   // 中间插新节点再拼回
}

// 查询 v 的排名 = 小于 v 的个数 + 1
int get_rank(int v) {
    int a, b;
    split(root, v - 1, a, b);                 // a 里全是 < v 的节点
    int rank = t[a].siz + 1;
    root = merge(a, b);                       // 用完记得合回去
    return rank;
}

// 查询排名第 k 的数（k 从 1 开始）
int get_kth(int k) {
    int x = root;
    while (true) {
        if (t[t[x].ls].siz >= k)              // 在左子树
            x = t[x].ls;
        else if (t[t[x].ls].siz + 1 == k)     // 正是当前节点
            return t[x].val;
        else {                                // 在右子树，k 减去左子树和当前节点
            k -= t[t[x].ls].siz + 1;
            x = t[x].rs;
        }
    }
}

// 查询 v 的前驱：小于 v 的最大值
int get_pre(int v) {
    int a, b;
    split(root, v - 1, a, b);                 // a 里全是 < v 的节点
    int x = a;
    while (t[x].rs) x = t[x].rs;              // a 中最右边的就是最大值
    int ans = x ? t[x].val : -INF;            // a 为空则无前驱
    root = merge(a, b);
    return ans;
}

// 查询 v 的后继：大于 v 的最小值
int get_nxt(int v) {
    int a, b;
    split(root, v, a, b);                     // b 里全是 > v 的节点
    int x = b;
    while (t[x].ls) x = t[x].ls;              // b 中最左边的就是最小值
    int ans = x ? t[x].val : INF;             // b 为空则无后继
    root = merge(a, b);
    return ans;
}

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
        if (opt == 1)      printf("%d\n", get_rank(x));
        else if (opt == 2) printf("%d\n", get_kth(x));
        else if (opt == 3) printf("%d\n", get_pre(x));
        else if (opt == 4) printf("%d\n", get_nxt(x));
        else               insert(x);
    }
    return 0;
}