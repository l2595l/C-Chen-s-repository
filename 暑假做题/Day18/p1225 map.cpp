//
// Created by 28447 on 2026/8/31.
//
#include <bits/stdc++.h>
using namespace std;

string startBoard, targetBoard;
unordered_map<string, pair<string, string>> pre;
queue<string> q;

// 获取相邻位置
vector<pair<int,int>> getNeighbors(int pos) {
    int r = pos / 4, c = pos % 4;
    vector<pair<int,int>> res;
    if (r > 0) res.push_back({pos, pos - 4});
    if (r < 3) res.push_back({pos, pos + 4});
    if (c > 0) res.push_back({pos, pos - 1});
    if (c < 3) res.push_back({pos, pos + 1});
    return res;
}

// 交换字符串中的两个字符
string swapChars(string s, int i, int j) {
    swap(s[i], s[j]);
    return s;
}

// 输出操作
string formatOp(int i, int j) {
    int ar = i / 4 + 1, ac = i % 4 + 1;
    int br = j / 4 + 1, bc = j % 4 + 1;
    string res = "";
    res += char('0' + ar);
    res += char('0' + ac);
    res += char('0' + br);
    res += char('0' + bc);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 读入：直接拼接成16字符的字符串
    startBoard = "";
    targetBoard = "";
    string line;
    for (int i = 0; i < 4; i++) {
        cin >> line;
        startBoard += line;
    }
    for (int i = 0; i < 4; i++) {
        cin >> line;
        targetBoard += line;
    }

    q.push(startBoard);
    pre[startBoard] = {"", ""};

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        if (cur == targetBoard) break;

        for (int i = 0; i < 16; i++) {
            for (auto [j, k] : getNeighbors(i)) {
                string next = swapChars(cur, j, k);
                if (pre.find(next) == pre.end()) {
                    pre[next] = {cur, formatOp(j, k)};
                    q.push(next);
                }
            }
        }
    }

    // 回溯
    vector<string> ops;
    string cur = targetBoard;
    while (cur != startBoard) {
        ops.push_back(pre[cur].second);
        cur = pre[cur].first;
    }
    reverse(ops.begin(), ops.end());

    cout << ops.size() << '\n';
    for (string op : ops) {
        cout << op << '\n';
    }

    return 0;
}