//
// Created by 28447 on 2026/10/16.
//
#include <iostream>

// 使用 std 命名空间
using namespace std;

// 定义最大节点数，稍微开大一点防止越界
const int MX = 500005;

// l[i] 记录 i 左边的节点，r[i] 记录 i 右边的节点
int l[MX], r[MX];

// del 数组用来标记节点是否被永久删除，true 表示已删除
bool del[MX];

// 辅助函数：将节点 x 从当前链表中摘除
// 注意：这只是断开链接，并没有永久删除数据
void rm(int x) {
    // 让 x 左边的节点直接连向 x 右边的节点
    r[l[x]] = r[x];
    // 让 x 右边的节点直接连向 x 左边的节点
    l[r[x]] = l[x];
}

// 辅助函数：将节点 x 插入到节点 p 的右边
void ins(int p, int x) {
    // 设置 x 自身的左右指针
    l[x] = p;
    r[x] = r[p];

    // 更新 p 右边那个节点的左指针指向 x
    l[r[p]] = x;
    // 更新 p 的右指针指向 x
    r[p] = x;
}

int main() {
    // 优化输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    // 初始化链表
    // 0 号节点作为虚拟头节点
    r[0] = 1;

    // 构建 1 到 n 的初始链接
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1;
        r[i] = i + 1;
    }
    // n 号节点的右边没有节点，设为 0
    r[n] = 0;

    // 处理 m 条指令
    while (m--) {
        int op, x, y;
        cin >> op;

        if (op == 1) {
            cin >> x >> y;
            // 如果 x 和 y 是同一个点，或 x 已删除，则忽略
            if (x == y || del[x]) continue;

            // 移动 x 到 y 的左边
            // 先把 x 从原位置摘除
            rm(x);
            // y 的左边就是 l[y]，把 x 插到 l[y] 的右边
            ins(l[y], x);
        }
        else if (op == 2) {
            cin >> x >> y;
            if (x == y || del[x]) continue;

            // 移动 x 到 y 的右边
            rm(x);
            // 直接把 x 插到 y 的右边
            ins(y, x);
        }
        else if (op == 3) {
            cin >> x;
            // 如果 x 已经被删除，则忽略
            if (del[x]) continue;
            
            // 摘除 x 并标记为永久删除
            rm(x);
            del[x] = true;
        }
    }

    // 输出结果
    // 从虚拟头节点 0 的右边开始遍历
    int cur = r[0];

    if (cur == 0) {
        // 如果 0 的右边还是 0，说明链表为空
        cout << "Empty!";
    } else {
        // 只要没走到 0 (链表末尾)，就一直输出
        while (cur != 0) {
            cout << cur << " ";
            cur = r[cur];
        }
    }
    cout << endl;

    return 0;
}
