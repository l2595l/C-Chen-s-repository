//
// Created by 28447 on 2026/8/25.
//
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int count;  // 集合数量

public:
    UnionFind(int size, int start) {
        parent.resize(size + 1);
        rank.resize(size + 1, 0);
        count = size - start + 1;
        for (int i = start; i <= size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;

        // 按秩合并
        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;
        }
        count--;
    }

    int getCount() const { return count; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, p;
    cin >> a >> b >> p;

    // 使用vector代替固定数组，动态分配
    vector<bool> isComposite(b + 1, false);
    UnionFind uf(b, a);

    // 埃氏筛优化：只筛到sqrt(b)
    int limit = sqrt(b);

    for (int i = 2; i <= b; ++i) {
        if (!isComposite[i]) {  // i是质数
            // 如果质数 >= p，才进行合并
            if (i >= p) {
                // 从 max(i*i, (a+i-1)/i*i) 开始，避免重复和超出范围
                int start = max(i * i, ((a + i - 1) / i) * i);
                for (int j = start; j <= b; j += i) {
                    isComposite[j] = true;
                    if (j - i >= a) {
                        uf.unite(j, j - i);
                    }
                }
            } else {
                // 只标记，不合并
                for (int j = i * i; j <= b; j += i) {
                    isComposite[j] = true;
                }
            }
        }
    }

    cout << uf.getCount() << endl;
    return 0;
}