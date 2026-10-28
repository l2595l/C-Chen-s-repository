//
// Created by 28447 on 2026/8/26.
//O(n!)
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int n;
string a[1001];
vector<int> e[1001];
bool used[1001];
int ind[1001];  // 作为首字母的次数（出度）
int rnd[1001];  // 作为尾字母的次数（入度）

void dfs(int s, string curr, int count) {
    if (count == n) {
        curr[curr.length() - 1] = ' ';
        cout << curr;
        exit(0);
    }

    for (auto i : e[s]) {
        if (!used[i]) {
            used[i] = true;
            dfs(i, curr + a[i] + '.', count + 1);
            used[i] = false;
        }
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    // 统计首字母和尾字母次数
    for (int i = 1; i <= n; ++i) {
        ++ind[a[i][0]];
        ++rnd[a[i][a[i].length() - 1]];
    }

    // 建图
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && a[i][a[i].length() - 1] == a[j][0]) {
                e[i].push_back(j);
            }
        }
    }

    // 优化：优先从满足度数条件的单词出发
    for (int i = 1; i <= n; ++i) {
        // 如果首字母的出度 == 入度 + 1，可能是起点
        if (ind[a[i][0]] == rnd[a[i][0]] + 1) {
            used[i] = true;
            dfs(i, a[i] + '.', 1);
            used[i] = false;
        }
    }

    // 兜底：从字典序最小的单词出发（欧拉回路情况）
    used[1] = true;
    dfs(1, a[1] + '.', 1);
    used[1] = false;

    cout << "***";
    return 0;
}