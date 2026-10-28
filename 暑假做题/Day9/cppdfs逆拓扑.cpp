//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int vexnum, arcnum;
    vector<vector<int>> adj;  // 邻接表（C++ vector代替链表）
    vector<int> color;        // 颜色数组：0-未访问，1-正在访问，2-已完成
    vector<int> topo;         // 存储逆拓扑序列
    bool hasCycle;

    // 三色标记DFS
    void dfs(int v) {
        color[v] = 1;  // GRAY：正在访问

        for(int w : adj[v]) {
            if(color[w] == 0) {  // WHITE：未访问
                dfs(w);
                if(hasCycle) return;
            }
            else if(color[w] == 1) {  // GRAY：发现环
                hasCycle = true;
                cout << "发现环：顶点 " << v << " -> 顶点 " << w << endl;
                return;
            }
            // color[w] == 2 (BLACK)：已完成，跳过
        }

        color[v] = 2;  // BLACK：已完成
        topo.push_back(v);  // 退栈时记录（逆拓扑序）
    }

public:
    Graph(int n = 0) : vexnum(n), arcnum(0) {
        adj.resize(n);
        color.assign(n, 0);
        hasCycle = false;
    }

    // 添加有向边 from -> to
    void addEdge(int from, int to) {
        if(from < 0 || from >= vexnum || to < 0 || to >= vexnum) {
            cout << "顶点编号错误" << endl;
            return;
        }
        adj[from].push_back(to);
        arcnum++;
    }

    // 添加顶点（动态扩展）
    void addVertex() {
        adj.push_back({});
        color.push_back(0);
        vexnum++;
    }

    // 检测环并获取逆拓扑序列
    bool getReverseTopo() {
        // 重置状态
        fill(color.begin(), color.end(), 0);
        topo.clear();
        hasCycle = false;

        // 对所有未访问顶点进行DFS
        for(int v = 0; v < vexnum; v++) {
            if(color[v] == 0) {
                dfs(v);
                if(hasCycle) return false;
            }
        }

        return true;
    }

    // 打印逆拓扑序列
    void printReverseTopo() {
        if(getReverseTopo()) {
            cout << "逆拓扑排序序列：";
            for(int v : topo) {
                cout << v << " ";
            }
            cout << endl << "该图无回路，以上为逆拓扑排序序列" << endl;
        } else {
            cout << "该图存在回路，不存在逆拓扑排序序列" << endl;
        }
    }

    // 打印图结构
    void printGraph() {
        cout << "\n图的邻接表结构：" << endl;
        for(int i = 0; i < vexnum; i++) {
            cout << "顶点 " << i << ": ";
            for(int w : adj[i]) {
                cout << "-> " << w << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // 获取结果
    vector<int> getTopoResult() {
        return topo;
    }

    bool hasCycleResult() {
        return hasCycle;
    }
};

// 使用示例
int main() {
    int n, m;
    cout << "请输入顶点数和边数：";
    cin >> n >> m;

    Graph G(n);

    cout << "请输入 " << m << " 条有向边 (from to)：" << endl;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G.addEdge(u, v);
    }

    G.printGraph();
    G.printReverseTopo();

    return 0;
}