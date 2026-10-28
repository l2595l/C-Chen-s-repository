//
// Created by 28447 on 2026/9/21.
//
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int P = 200003; // 使用大于 2*10^5 的质数，减少冲突
const long long INF = 0x3f3f3f3f3f3f3f3f; // 用来表示哈希表位置为空

long long h[P]; // 哈希表

// 寻找 x 在哈希表中的位置
int find(long long x) {
    int y = ((x % P) + P) % P; // 处理负数取模，保证结果非负
    while (h[y] != INF && h[y] != x) {
        y = (y + 1) % P; // 线性探测
    }
    return y;
}

int main() {
    // 初始化哈希表全部为空
    memset(h, 0x3f, sizeof(h));

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);

        vector<int> used; // 记录本组数据用了哪些位置
        bool first = true; // 控制空格输出

        for (int i = 0; i < n; i++) {
            long long x;
            scanf("%lld", &x);

            int pos = find(x);
            if (h[pos] == INF) { // 没出现过
                h[pos] = x; // 插入哈希表
                used.push_back(pos); // 记录位置以便清理

                if (!first) printf(" ");
                printf("%lld", x);
                first = false;
            }
            // 如果 h[pos] == x，说明之前出现过，直接跳过不输出
        }
        printf("\n");

        // 快速清空哈希表，只清空刚才用过的地方
        for (int pos : used) {
            h[pos] = INF;
        }
    }
    return 0;
}