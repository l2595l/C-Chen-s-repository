//
// Created by 28447 on 2026/8/26.
//欧拉回路O(n)
//注意：这只是部分代码
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int n;
int letter[27], in[27], out[27], fa[27], set_count;
int Eular_start, Eular_end;
int vis[1002];
string s[1002], res[1002];

struct node {
    int to, ord;
    string word;
};
vector<vector<node> > E;

// 并查集查找（路径压缩）
int find(int x) {
    if (fa[x] != x) return fa[x] = find(fa[x]);
    return fa[x];
}

// 并查集合并
void unionn(int x, int y) {
    fa[y] = x;
}

// DFS搜索欧拉路径
void dfs(int st, int now) {
    // 所有单词都用完了 → 找到答案
    if (st == n) {
        for (int i = 1; i <= n; i++) {
            cout << res[i];
            if (i < n) cout << ".";
        }
        exit(0);
    }

    // 遍历当前顶点的所有出边
    for (int k = 0; k < E[now].size(); k++) {
        int edge_id = E[now][k].ord;
        if (!vis[edge_id]) {                    // 边未被使用
            vis[edge_id] = 1;                   // 标记已用
            res[st + 1] = E[now][k].word;       // 记录单词
            dfs(st + 1, E[now][k].to);          // 递归到下一个顶点
            vis[edge_id] = 0;                   // 回溯（取消标记）
        }
    }
}

int main() {
    cin >> n;
    E.resize(27);

    for (int i = 1; i <= n; i++) cin >> s[i];
    sort(s + 1, s + n + 1);  // 按字典序排序

    // 初始化并查集
    for (int i = 1; i <= 26; i++) fa[i] = i;

    // 建图
    for (int i = 1; i <= n; i++) {
        int st = s[i][0] - 'a' + 1;                    // 首字母
        int ed = s[i][s[i].length() - 1] - 'a' + 1;    // 末字母

        out[st]++;  // 出度
        in[ed]++;   // 入度

        // 标记字母出现 + 并查集初始化
        if (!letter[st]) { letter[st] = 1; set_count++; }
        if (!letter[ed]) { letter[ed] = 1; set_count++; }

        // 并查集合并（检查连通性）
        if (st != ed) {
            int root1 = find(st), root2 = find(ed);
            if (root1 != root2) {
                set_count--;
                unionn(root1, root2);
            }
        }

        // 添加边
        E[st].push_back({ed, i, s[i]});
    }

    // 1. 检查连通性
    if (set_count != 1) { cout << "***"; return 0; }

    // 2. 检查欧拉路径度数条件
    for (int i = 1; i <= 26; i++) {
        if (!letter[i]) continue;

        if (out[i] == in[i] + 1) {          // 出度多1 → 起点
            if (Eular_start) { cout << "***"; return 0; }
            Eular_start = i;
        }
        else if (in[i] == out[i] + 1) {     // 入度多1 → 终点
            if (Eular_end) { cout << "***"; return 0; }
            Eular_end = i;
        }
        else if (in[i] != out[i]) {         // 不满足欧拉路径条件
            cout << "***"; return 0;
        }
    }

    // 3. 起点终点必须成对出现
    if ((Eular_start && !Eular_end) || (!Eular_start && Eular_end)) {
        cout << "***"; return 0;
    }

    // 4. 确定起点
    if (!Eular_start) {  // 欧拉回路：选字典序最小的字母
        for (int i = 1; i <= 26; i++) {
            if (letter[i]) { Eular_start = i; break; }
        }
    }

    // 5. 每个顶点的出边按字典序排序（保证输出最小）
    for (int i = 1; i <= 26; i++) {
        sort(E[i].begin(), E[i].end(), [](node a, node b) {
            return a.word < b.word;
        });
    }

    // 6. DFS搜索
    dfs(0, Eular_start);

    cout << "***";
    return 0;
}