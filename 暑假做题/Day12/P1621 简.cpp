//
// Created by 28447 on 2026/8/25.
//
#include <iostream>
using namespace std;

const int MAXN = 100010;
int parent[MAXN];
bool isComposite[MAXN];

int find(int x) {
    if (x != parent[x]) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y, int& ans) {
    int rx = find(x), ry = find(y);
    if (rx != ry) {
        parent[rx] = ry;
        --ans;
    }
}
int main() {
    int a, b, p;
    cin >> a >> b >> p;
    for (int i = a; i <= b; ++i) {
        parent[i] = i;
    }

    int ans = b - a + 1;
    for (int i = 2; i <= b; ++i) {
        if (!isComposite[i]) {
            for (int j = i * 2; j <= b; j += i) {
                isComposite[j] = true;
                if (i >= p && j - i >= a) {
                    unite(j, j - i, ans);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}