//
//
// Created by 28447 on 2026/8/31.
//
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXC = 305;        // 坐标最大可能值，留一些余量
const int INF = 1e9;

int destroyTime[MAXC + 5][MAXC + 5];  // 每个格子的最早被摧毁时间
bool visited[MAXC + 5][MAXC + 5];

// 四个方向：上、下、左、右
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Node {
    int x, y, t;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M;
    cin >> M;

    // 初始化摧毁时间为无穷大
    for (int i = 0; i < MAXC + 5; i++) {
        for (int j = 0; j < MAXC + 5; j++) {
            destroyTime[i][j] = INF;
        }
    }

    // 读入流星数据并更新摧毁时间
    for (int i = 0; i < M; i++) {
        int x, y, t;
        cin >> x >> y >> t;

        // 流星本身及其四个相邻格子
        int around[5][2] = {{0,0}, {1,0}, {-1,0}, {0,1}, {0,-1}};
        for (int j = 0; j < 5; j++) {
            int nx = x + around[j][0];
            int ny = y + around[j][1];
            if (nx >= 0 && ny >= 0 && nx <= MAXC && ny <= MAXC) {
                if (t < destroyTime[nx][ny]) {
                    destroyTime[nx][ny] = t;
                }
            }
        }
    }

    // 如果起点在时刻 0 就被摧毁
    if (destroyTime[0][0] == 0) {
        cout << -1 << endl;
        return 0;
    }

    // BFS
    queue<Node> q;
    q.push({0, 0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int x = cur.x, y = cur.y, t = cur.t;

        // 如果当前格子永远不会被摧毁，说明找到了安全位置
        if (destroyTime[x][y] == INF) {
            cout << t << endl;
            return 0;
        }

        // 尝试四个方向移动
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx > MAXC || ny > MAXC) continue;
            if (visited[nx][ny]) continue;

            int nt = t + 1;
            // 只有到达时格子还没被摧毁才能进入
            if (nt < destroyTime[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny, nt});
            }
        }
    }

    // 队列为空，无法到达安全格子
    cout << -1 << endl;
    return 0;
}