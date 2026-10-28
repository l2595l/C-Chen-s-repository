//
// Created by 28447 on 2026/10/24.
//
#include <bits/stdc++.h>
using namespace std;

// 第一象限里有 n 颗地雷，每颗是一个圆（圆心 (x, y)，半径 r）。
// 从原点出发，沿 [0, π/2] 内均匀随机的方向一直走，求不碰到任何圆的概率。
//
// 思路：从原点看过去，每个圆挡住的是一个角度区间 [圆心方位角 - 半张角, 圆心方位角 + 半张角]。
// 概率 = 1 - 这些区间的并集长度 / (π/2)。
// 区间都在同一条角度轴上，是一维问题：按左端点排序后线性扫一遍即可合并，
// 不需要线段树（线段树扫描线用于二维的矩形面积并）。

const double kPi = acos(-1.0);
const double kQuarterTurn = kPi / 2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<double, double>> arcs;  // 每个圆在原点看过去的角度区间
    arcs.reserve(n);
    for (int i = 0; i < n; ++i) {
        double x, y, r;
        cin >> x >> y >> r;

        double center = atan2(y, x);
        // 原点在圆内或圆上时 r / d >= 1，半张角取 π/2，该圆挡住所有方向
        double halfWidth = asin(min(1.0, r / hypot(x, y)));

        // 只有 [0, π/2] 内的方向才会被选中，区间需要裁剪到这个范围
        double lo = max(0.0, center - halfWidth);
        double hi = min(kQuarterTurn, center + halfWidth);
        if (lo < hi) {
            arcs.emplace_back(lo, hi);
        }
    }

    sort(arcs.begin(), arcs.end());

    double covered = 0;  // 已经统计的并集长度
    double reach = 0;    // 已被覆盖的最右位置
    for (auto [lo, hi] : arcs) {
        lo = max(lo, reach);  // 与前面重叠的部分不再重复计算
        if (hi > lo) {
            covered += hi - lo;
            reach = hi;
        }
    }

    // 浮点误差可能让结果出现 -0.000，截到 0
    double probability = max(0.0, 1 - covered / kQuarterTurn);
    printf("%.3f\n", probability);
    return 0;
}
