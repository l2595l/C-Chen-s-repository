//
// Created by 28447 on 2026/8/30.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

// 最大节点数：矩阵中1的个数 + 列头节点数
// 对于 N*M 的矩阵，最多有 N*M 个1，加上 M+1 个列头
const int MAX_NODE = 250501;  // 250000 + 500 + 1

// 快速读入整数（优化输入速度）
inline int Read() {
    int x = 0;
    char c = getchar();
    // 跳过非数字字符
    while (c > '9' || c < '0') c = getchar();
    // 读入数字
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

int n, m;           // n: 行数, m: 列数
int node_cnt;       // 当前已使用的节点数（节点编号计数器）

// ============ 十字链表指针数组 ============
// 每个节点有四个方向的指针
int L[MAX_NODE];    // left  - 左指针
int R[MAX_NODE];    // right - 右指针
int U[MAX_NODE];    // up    - 上指针
int D[MAX_NODE];    // down  - 下指针

// 每个节点的行号和列号
int row[MAX_NODE];  // 节点所在的行
int col[MAX_NODE];  // 节点所在的列

int head[MAX_NODE]; // 每行的头节点（行链表入口）
int size[MAX_NODE]; // 每列的节点数量（用于启发式选择）

int answer[MAX_NODE]; // 存储选中的行号（最终答案）

/**
 * 初始化十字链表
 * @param m 列的数量
 *
 * 创建 m+1 个节点：节点0是总头节点，节点1~m是各列头节点
 * 列头节点之间形成双向循环链表
 * 每个列头节点的上下指针指向自己（表示该列暂时为空）
 */
void init(int m) {
    // 初始化列头节点的左右链接
    for (int i = 0; i <= m; i++) {
        R[i] = i + 1;    // 右指针指向下一个
        L[i] = i - 1;    // 左指针指向上一个
        U[i] = D[i] = i; // 上下指针指向自己（列暂时为空）
    }

    // 形成循环链表：尾节点的右指针指向头节点
    R[m] = 0;    // 最后一个节点的右边是头节点0
    L[0] = m;    // 头节点的左边是最后一个节点

    // 初始化行头数组和列大小数组
    memset(head, -1, sizeof(head));  // -1表示该行还没有节点
    memset(size, 0, sizeof(size));   // 所有列初始节点数为0

    // 节点编号从 m+1 开始（0~m 已经被列头节点占用）
    node_cnt = m + 1;
}

/**
 * 在矩阵的 (R, C) 位置插入一个节点（值为1）
 * @param R 行号
 * @param C 列号
 *
 * 插入过程分两步：
 * 1. 将节点插入到列链表中（上下方向）
 * 2. 将节点插入到行链表中（左右方向）
 */
inline void insert_node(int R, int C) {
    // ====== 第一步：在列链表中插入（上下方向） ======
    size[C]++;                     // 该列的节点数增加
    row[node_cnt] = R;             // 记录新节点的行号
    col[node_cnt] = C;             // 记录新节点的列号

    // 将新节点插入到列头 C 的下方
    U[node_cnt] = C;               // 新节点的上方指向列头
    D[node_cnt] = D[C];            // 新节点的下方指向列头原来的下一个
    U[D[C]] = node_cnt;            // 原来第一个节点的上方指向新节点
    D[C] = node_cnt;               // 列头的下方指向新节点

    // ====== 第二步：在行链表中插入（左右方向） ======
    if (head[R] == -1) {
        // 情况1：该行还没有任何节点
        // 新节点自己形成循环链表
        head[R] = node_cnt;        // 该行的头节点就是新节点
        L[node_cnt] = node_cnt;    // 左指针指向自己
        R[node_cnt] = node_cnt;    // 右指针指向自己
    } else {
        // 情况2：该行已有节点，将新节点插入到行头的前面
        //    头节点         新节点
        //   [head] ←→ [node] ←→ [其他节点]
        R[node_cnt] = head[R];            // 新节点右边指向头节点
        L[node_cnt] = L[head[R]];         // 新节点左边指向头节点的左边
        R[L[head[R]]] = node_cnt;         // 头节点左边节点的右边指向新节点
        L[head[R]] = node_cnt;            // 头节点的左边指向新节点
    }

    node_cnt++;  // 准备下一个节点的编号
}

/**
 * 删除列 C 及其相关的所有行
 * @param C 要删除的列
 *
 * 删除过程：
 * 1. 从列头链表中移除列 C
 * 2. 遍历列 C 中的所有节点
 * 3. 对于每个节点，删除其所在行的所有节点
 *
 * 这样做的目的是：选择列 C 后，所有包含列 C 的行都不能再选
 */
inline void remove_column(int C) {
    // ---- 第一步：从列头链表中移除列 C ----
    // 让 C 的左右节点直接相连，跳过 C
    R[L[C]] = R[C];
    L[R[C]] = L[C];

    // ---- 第二步：遍历列 C 中的所有节点 ----
    // 从列头 C 的下方开始，直到回到列头
    for (int i = D[C]; i != C; i = D[i]) {
        // 对于列 C 中的每个节点 i
        // 删除节点 i 所在行的所有节点（除了节点 i 自己）
        for (int j = R[i]; j != i; j = R[j]) {
            // 从列链表中移除节点 j
            U[D[j]] = U[j];  // 让 j 的上下节点直接相连
            D[U[j]] = D[j];
            size[col[j]]--;  // 该列的节点数减1
        }
    }
}

/**
 * 恢复被删除的列 C 及其相关的行（撤销 remove_column 操作）
 * @param C 要恢复的列
 *
 * 恢复过程与删除过程相反，必须按照逆序进行
 */
inline void restore_column(int C) {
    // ---- 第一步：恢复列 C 中的所有行节点（逆序） ----
    // 从列头 C 的上方开始，直到回到列头
    for (int i = U[C]; i != C; i = U[i]) {
        // 恢复节点 i 所在行的所有节点（除了节点 i 自己）
        for (int j = L[i]; j != i; j = L[j]) {
            // 恢复节点 j 到列链表中
            U[D[j]] = j;  // 恢复 j 的上下链接
            D[U[j]] = j;
            size[col[j]]++;  // 该列的节点数加1
        }
    }

    // ---- 第二步：恢复列 C 到列头链表中 ----
    R[L[C]] = C;
    L[R[C]] = C;
}

/**
 * Dancing Links 主搜索函数（深度优先搜索 + 回溯）
 * @param depth 当前搜索深度（已经选择了多少行）
 * @return 是否找到可行解
 *
 * 算法流程：
 * 1. 如果所有列都被覆盖（R[0]==0），找到解
 * 2. 选择节点数最少的列（启发式，减少分支）
 * 3. 删除该列
 * 4. 枚举该列中的每一行
 * 5. 选择该行，删除该行覆盖的所有列
 * 6. 递归搜索下一层
 * 7. 如果失败，恢复删除的列（回溯）
 */
bool dance(int depth) {
    // ----- 递归终止条件：找到解 -----
    if (R[0] == 0) {
        // 输出答案：选中的行号
        for (int i = 0; i < depth; i++) {
            printf("%d ", answer[i]);
        }
        printf("\n");
        return true;
    }

    // ----- 启发式：选择节点数最少的列 -----
    // 从第一个列头开始，比较各列的节点数
    int col_min = R[0];  // 假设第一列是最少
    for (int i = R[0]; i != 0; i = R[i]) {
        if (size[i] < size[col_min]) {
            col_min = i;  // 找到更少的列
        }
    }

    // ----- 删除选中的列 -----
    remove_column(col_min);

    // ----- 枚举该列中的所有行 -----
    for (int i = D[col_min]; i != col_min; i = D[i]) {
        // 选择第 row[i] 行
        answer[depth] = row[i];

        // 删除该行中所有1所在的列
        for (int j = R[i]; j != i; j = R[j]) {
            remove_column(col[j]);
        }

        // 递归搜索
        if (dance(depth + 1)) {
            return true;  // 找到解，逐层返回
        }

        // ----- 回溯：恢复删除的列 -----
        // 注意：恢复顺序必须与删除顺序相反
        for (int j = L[i]; j != i; j = L[j]) {
            restore_column(col[j]);
        }
    }

    // ----- 恢复最初删除的列 -----
    restore_column(col_min);

    return false;  // 无解
}

/**
 * 主程序入口
 */
int main() {
    // 读入矩阵大小
    n = Read();
    m = Read();

    // 初始化十字链表
    init(m);

    // 读入矩阵并构建十字链表
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int value = Read();
            if (value == 1) {
                insert_node(i, j);  // 矩阵值为1的位置插入节点
            }
        }
    }

    // 执行Dancing Links搜索
    if (!dance(0)) {
        printf("No Solution!");
    }

    return 0;
}