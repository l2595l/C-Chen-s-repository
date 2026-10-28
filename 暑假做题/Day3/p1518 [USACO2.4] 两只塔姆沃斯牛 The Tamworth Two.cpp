//
// Created by 28447 on 2026/8/15.
//
#include <bits/stdc++.h>
using namespace std;

char g[12][12];                  // 地图，边界第 0、11 行/列都设为障碍 '*'
bool vis[4][4][12][12][12][12];  // 状态去重：[农夫朝向][牛朝向][农夫x][农夫y][牛x][牛y]
const int dx[4] = {-1, 0, 1, 0}; // 北 东 南 西 的行偏移
const int dy[4] = {0, 1, 0, -1}; // 北 东 南 西 的列偏移

int main() {
    // 初始化整张图边界为障碍
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            g[i][j] = '*';

    int fx = 0, fy = 0, fd = 0;  // 农夫坐标与朝向（0=北）
    int cx = 0, cy = 0, cd = 0;  // 牛坐标与朝向（0=北）

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'F') fx = i, fy = j;
            if (g[i][j] == 'C') cx = i, cy = j;
        }
    }

    int ans = 0;
    while (fx != cx || fy != cy) {  // 不重叠就继续模拟
        // 状态重复出现 → 进入死循环，永远遇不到
        if (vis[fd][cd][fx][fy][cx][cy]) {
            cout << 0 << '\n';
            return 0;
        }
        vis[fd][cd][fx][fy][cx][cy] = true;

        // 农夫：前方是障碍就顺时针转 90°，否则前进一步
        if (g[fx + dx[fd]][fy + dy[fd]] == '*') fd = (fd + 1) % 4;
        else fx += dx[fd], fy += dy[fd];

        // 牛：同理
        if (g[cx + dx[cd]][cy + dy[cd]] == '*') cd = (cd + 1) % 4;
        else cx += dx[cd], cy += dy[cd];

        ans++;
    }
    cout << ans << '\n';
    return 0;
}