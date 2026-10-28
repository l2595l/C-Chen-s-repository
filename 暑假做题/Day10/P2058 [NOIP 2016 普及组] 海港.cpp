//
// Created by 28447 on 2026/8/22.
//
// 题目：洛谷 P2058「海港」（NOIP 2016 普及组）
// 题意：有 n 艘船依次到港，第 i 艘船在 t[i] 时刻到港，载有 k 名乘客，
//       每名乘客有一个国籍。对每艘船，输出「最近 24 小时（86400 秒）内」到港的
//       所有乘客中，不同国籍的数量。
//
// 思路：滑动窗口
//   - 维护一个时间窗口，只保留「t[i] - 86400 < 到港时刻 ≤ t[i]」的船。
//   - cnt[国籍] = 窗口内该国籍的人数；ans = 窗口内不同国籍的数量。
//   - 每来一艘新船：先把乘客加入窗口（更新 cnt、ans），
//     再把队头所有「过期（超出 24 小时）」的船移出窗口，最后输出 ans。
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;            // 国籍、船数都不超过 1e5
const int WINDOW = 86400;               // 24 小时 = 86400 秒

vector<int> ship[MAXN];                 // ship[i]：第 i 艘船每位乘客的国籍
int t[MAXN];                            // t[i]：第 i 艘船的到港时刻
int cnt[MAXN];                          // cnt[国籍]：窗口内该国籍的人数
int head = 1;                           // 滑动窗口左端点（最早仍在窗口内的船）
int ans = 0;                            // 窗口内不同国籍的数量

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int k;                          // 本艘船乘客人数
        scanf("%d%d", &t[i], &k);

        // 1) 新船入窗口：登记每位乘客的国籍
        for (int j = 1; j <= k; j++) {
            int nation;                 // 乘客国籍
            scanf("%d", &nation);
            ship[i].push_back(nation);  // 记下这艘船上有哪些国籍，供日后移除
            if (cnt[nation] == 0) ans++;// 该国籍首次出现，种类数 +1
            cnt[nation]++;              // 该国籍人数 +1
        }

        // 2) 淘汰过期船：队头船若已超出 24 小时窗口，整体移出
        while (t[i] - t[head] >= WINDOW) {
            for (int j = 0; j < (int)ship[head].size(); j++) {
                cnt[ship[head][j]]--;          // 该乘客国籍人数 -1
                if (cnt[ship[head][j]] == 0)   // 减到 0：窗口内该国籍消失
                    ans--;
            }
            head++;                            // 左端点右移，丢弃这艘船
        }

        // 3) 输出当前窗口内的不同国籍数
        printf("%d\n", ans);
    }

    return 0;
}
