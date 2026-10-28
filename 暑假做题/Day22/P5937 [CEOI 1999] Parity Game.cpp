//
// Created by 28447 on 2026/9/16.
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005; // 2 * m (m <= 5000)
int fa[MAXN], siz[MAXN];

// 并查集：路径压缩 + 按大小合并
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    if (siz[fx] < siz[fy]) swap(fx, fy); // 按大小合并：小挂大
    fa[fy] = fx;
    siz[fx] += siz[fy];
}

int main() {
    ios::sync_with_stdio(false); // 加速 cin/cout（养成好习惯）
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    struct Query {
        int x, y, op; // op: 0表示even(相同)，1表示odd(不同)
    };
    vector<Query> queries(m);
    vector<int> points; // 用于离散化
    points.reserve(2 * m);

    for (int i = 0; i < m; ++i) {
        string s;
        cin >> queries[i].x >> queries[i].y >> s;
        queries[i].x--; // 前缀和转化：S_{l-1} 和 S_r
        queries[i].op = (s == "odd") ? 1 : 0;

        points.push_back(queries[i].x);
        points.push_back(queries[i].y);
    }

    // 离散化标准三连
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int tot = points.size();

    // 初始化扩展域并查集：1~tot为偶数域，tot+1~2*tot为奇数域
    for (int i = 1; i <= 2 * tot; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }

    for (int i = 0; i < m; ++i) {
        // 二分查找映射坐标，+1是为了让下标从1开始
        int x = lower_bound(points.begin(), points.end(), queries[i].x) - points.begin() + 1;
        int y = lower_bound(points.begin(), points.end(), queries[i].y) - points.begin() + 1;

        if (queries[i].op == 0) { // even：奇偶性相同
            if (find(x) == find(y + tot)) { // 矛盾
                cout << i << "\n"; // 注意这里输出i（因为原代码是i-1，这里循环从0开始，正好对应前i个满足）
                return 0;
            }
            merge(x, y);
            merge(x + tot, y + tot);
        } else { // odd：奇偶性不同
            if (find(x) == find(y)) { // 矛盾
                cout << i << "\n";
                return 0;
            }
            merge(x, y + tot);
            merge(x + tot, y);
        }
    }

    cout << m << "\n";
    return 0;
}