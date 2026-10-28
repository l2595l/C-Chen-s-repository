//
// Created by 28447 on 2026/8/31.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// ========== 常量定义 ==========
const int MAX_NODE = 100100;  // 最大节点数，需大于 n*n*(6*n-2)
const int MAX_ANS = 100000;   // 最大答案存储数量
const int MAX_N = 14;         // 最大皇后数量（用于答案数组）

// ========== 全局变量 ==========
long long solution_count = 0;  // 方案总数
int queen_num;                 // 皇后数量（N）

// 存储答案的结构体
struct Answer {
    int queen_pos[MAX_N];  // queen_pos[col] = row，表示第col列皇后在第row行
} answers[MAX_ANS];

// ========== Dancing Links (DLX) 算法实现 ==========
class DancingLinks {
public:
    int n, m;           // 矩阵行数(n)，列数(m)
    int node_cnt;       // 当前节点总数

    // 双向循环链表指针
    int left[MAX_NODE], right[MAX_NODE];   // 左右指针
    int up[MAX_NODE], down[MAX_NODE];      // 上下指针
    int row[MAX_NODE], col[MAX_NODE];      // 节点所在行列

    int head_row[MAX_NODE];  // 每行的头节点
    int col_size[MAX_NODE];  // 每列的节点数量
    int answer_stack[MAX_NODE];  // 当前选择的答案行

    /**
     * 初始化DLX结构
     * @param _n 行数（棋盘格子数 = n*n）
     * @param _m 列数（约束条件数 = 6*n-2）
     */
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        node_cnt = m + 1;  // 0号节点 + m个列头节点

        // 初始化列头节点的左右指针
        for (int i = 0; i <= m; i++) {
            left[i] = i - 1;
            right[i] = i + 1;
            up[i] = down[i] = i;  // 上下指针指向自己
        }
        right[m] = 0;   // 循环链表：最右指向0
        left[0] = m;    // 循环链表：最左指向m

        // 初始化行头和列大小
        memset(head_row, -1, sizeof(head_row));
        memset(col_size, 0, sizeof(col_size));
    }

    /**
     * 在矩阵中插入一个节点
     * @param R 行号
     * @param C 列号
     */
    void link(int R, int C) {
        col_size[C]++;  // 该列节点数+1

        // 设置当前节点信息
        row[node_cnt] = R;
        col[node_cnt] = C;

        // 纵向连接：插入到列头C的下方
        up[node_cnt] = C;
        down[node_cnt] = down[C];
        up[down[C]] = node_cnt;
        down[C] = node_cnt;

        // 横向连接：插入到行头R的右侧
        if (head_row[R] < 0) {
            // 该行第一个节点，作为行头
            head_row[R] = left[node_cnt] = right[node_cnt] = node_cnt;
        } else {
            // 插入到行头右侧
            right[node_cnt] = head_row[R];
            left[node_cnt] = left[head_row[R]];
            right[left[head_row[R]]] = node_cnt;
            left[head_row[R]] = node_cnt;
        }

        node_cnt++;
    }

    /**
     * 删除一列及其关联的行
     * @param c 要删除的列
     */
    void remove_col(int c) {
        // 从列头链表中移除该列
        right[left[c]] = right[c];
        left[right[c]] = left[c];

        // 遍历该列的所有节点
        for (int i = down[c]; i != c; i = down[i]) {
            // 删除该节点所在行的所有其他节点
            for (int j = right[i]; j != i; j = right[j]) {
                up[down[j]] = up[j];
                down[up[j]] = down[j];
                col_size[col[j]]--;
            }
        }
    }

    /**
     * 恢复一列及其关联的行
     * @param c 要恢复的列
     */
    void restore_col(int c) {
        // 遍历该列的所有节点（反向恢复）
        for (int i = up[c]; i != c; i = up[i]) {
            // 恢复该节点所在行的所有其他节点
            for (int j = left[i]; j != i; j = left[j]) {
                up[down[j]] = j;
                down[up[j]] = j;
                col_size[col[j]]++;
            }
        }

        // 恢复列头节点到链表中
        right[left[c]] = c;
        left[right[c]] = c;
    }

    /**
     * DLX递归搜索（核心算法）
     * @param depth 当前搜索深度
     */
    void dance(int depth) {
        // 前n列都已删除，表示n个皇后都已放置（每列对应一行）
        if (right[0] > queen_num) {
            solution_count++;

            // 将答案转换为棋盘坐标存储
            for (int i = 0; i < depth; i++) {
                int row_idx = answer_stack[i];  // 选中的行号
                int col = row_idx % queen_num;
                int row = (row_idx - 1) / queen_num + 1;
                if (col == 0) col = queen_num;
                answers[solution_count].queen_pos[col] = row;
            }
            return;
        }

        // 选择节点数最少的列（优化搜索效率）
        int min_col = right[0];
        for (int i = right[0]; i <= queen_num; i = right[i]) {
            if (col_size[i] < col_size[min_col]) {
                min_col = i;
            }
        }

        // 删除选中的列
        remove_col(min_col);

        // 遍历该列的所有行
        for (int i = down[min_col]; i != min_col; i = down[i]) {
            answer_stack[depth] = row[i];  // 记录选中的行

            // 删除该行所覆盖的所有其他列
            for (int j = right[i]; j != i; j = right[j]) {
                remove_col(col[j]);
            }

            // 递归搜索下一层
            dance(depth + 1);

            // 恢复该行所覆盖的所有列（回溯）
            for (int j = left[i]; j != i; j = left[j]) {
                restore_col(col[j]);
            }
        }

        // 恢复选中的列（回溯）
        restore_col(min_col);
    }
};

// ========== 辅助函数 ==========
/**
 * 比较两个答案，用于排序（字典序）
 */
bool compare_answers(const Answer& a, const Answer& b) {
    for (int i = 1; i <= queen_num; i++) {
        if (a.queen_pos[i] != b.queen_pos[i]) {
            return a.queen_pos[i] < b.queen_pos[i];
        }
    }
    return false;
}

// ========== 主程序 ==========
int main() {
    // 读取皇后数量
    scanf("%d", &queen_num);

    // 初始化DLX
    // 行数 = n*n（每个格子一种放置可能）
    // 列数 = 6*n-2（行约束n个 + 列约束n个 + 对角线约束4*n-2个）
    DancingLinks dlx;
    dlx.init(queen_num * queen_num, 6 * queen_num - 2);

    /**
     * 列编号说明：
     * 1 ~ n         : 行约束（每行只能有一个皇后）
     * n+1 ~ 2n      : 列约束（每列只能有一个皇后）
     * 2n+1 ~ 4n-1   : 主对角线约束（/ 方向，共2n-1条）
     * 4n ~ 6n-2     : 副对角线约束（\ 方向，共2n-1条）
     */
    int row_count = 0;
    for (int i = 1; i <= queen_num; i++) {
        for (int j = 1; j <= queen_num; j++) {
            row_count++;  // 当前格子对应的行号

            // 在该位置放置皇后，添加四个约束
            dlx.link(row_count, i);                        // 行约束
            dlx.link(row_count, j + queen_num);            // 列约束
            dlx.link(row_count, i - j + 3 * queen_num);    // 主对角线约束
            dlx.link(row_count, i + j + 4 * queen_num - 2); // 副对角线约束
        }
    }

    // 执行DLX搜索
    dlx.dance(0);

    // 对答案按字典序排序
    sort(answers + 1, answers + solution_count + 1, compare_answers);

    // 输出前3个解
    for (int i = 1; i <= 3 && i <= solution_count; i++) {
        for (int j = 1; j <= queen_num; j++) {
            printf("%d ", answers[i].queen_pos[j]);
        }
        printf("\n");
    }

    // 输出总解数
    printf("%lld\n", solution_count);

    return 0;
}