//
// Created by 28447 on 2026/8/25.
//
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

// ========== 常量定义 ==========
const int MAXN = 30;      // 最多26个大写字母
const int MAXM = 905;     // 最多 26*26 条边

// ========== 链式前向星存储图 ==========
struct Edge {
    int v;              // 边的终点
    Edge *next;         // 下一条边
} *head[MAXN], pool[MAXM];  // head: 邻接表头, pool: 静态内存池
int edgeCnt = 0;        // 已使用的边数

// 添加有向边 u -> v
void addEdge(int u, int v) {
    Edge *e = &pool[++edgeCnt];  // 从内存池取一个节点
    e->v = v;
    e->next = head[u];           // 头插法
    head[u] = e;
}

// ========== 拓扑排序相关 ==========
int indegree[MAXN];      // 入度数组（会被修改）
int queue[MAXN];         // 拓扑排序队列
int headIdx, tailIdx;    // 队列头尾指针

/**
 * 执行拓扑排序并判断状态
 *
 * @param n  节点数量（1~26）
 * @return   1: 已确定唯一顺序
 *           0: 条件不足，有多种可能
 *          -1: 存在环，矛盾
 */
int topologicalSort(int n) {
    // 临时入度数组（因为传入的是全局数组，我们直接修改）
    // 注意：调用前已经复制好入度

    int headIdx = 0, tailIdx = 0;      // 初始化队列
    bool hasMultipleChoices = false;   // 标记是否存在多个选择（不唯一）

    // === 第一轮：找到所有入度为0的节点 ===
    int zeroCount = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[tailIdx++] = i;      // 入队
            zeroCount++;
        }
    }
    // 如果一开始就有多个入度为0，说明顺序不唯一
    if (zeroCount > 1) {
        hasMultipleChoices = true;
    }

    // === BFS 拓扑排序 ===
    while (headIdx < tailIdx) {
        zeroCount = 0;  // 当前层入度变为0的节点数
        int u = queue[headIdx++];      // 取出队首节点

        // 遍历 u 的所有后继
        for (Edge *e = head[u]; e != NULL; e = e->next) {
            int v = e->v;
            indegree[v]--;             // 删除边 u->v

            if (indegree[v] == 0) {
                queue[tailIdx++] = v;  // 入队
                zeroCount++;
            }
        }

        // 如果某一层有多个节点入度变为0，说明有多种选择
        if (zeroCount > 1) {
            hasMultipleChoices = true;
        }
    }

    // === 判断结果 ===
    if (tailIdx != n) {
        // 还有节点没入队 → 存在环 → 矛盾
        return -1;
    } else if (hasMultipleChoices) {
        // 所有节点都入队了，但存在分支 → 顺序不确定
        return 0;
    } else {
        // 所有节点都入队了，且每一步都唯一 → 顺序确定
        return 1;
    }
}

// ========== 主函数 ==========
int main() {
    int n, m;  // n: 节点数, m: 关系数
    cin >> n >> m;

    // 存储所有关系（先读入再增量处理）
    struct Relation {
        int u, v;
    } relations[MAXM];

    // 读入所有关系
    for (int i = 1; i <= m; i++) {
        char a, op, b;
        cin >> a >> op >> b;
        // 将 'A' 映射为 1, 'B' 映射为 2, ...
        relations[i].u = a - 'A' + 1;
        relations[i].v = b - 'A' + 1;
    }

    // === 增量处理每条关系 ===
    for (int i = 1; i <= m; i++) {
        // 1. 添加新边
        addEdge(relations[i].u, relations[i].v);

        // 2. 计算当前所有节点的入度
        memset(indegree, 0, sizeof(indegree));
        for (int j = 1; j <= i; j++) {
            indegree[relations[j].v]++;  // 每条边的终点入度+1
        }

        // 3. 执行拓扑排序
        int status = topologicalSort(n);

        // 4. 根据结果处理
        if (status == 1) {
            // ? 确定唯一顺序
            cout << "Sorted sequence determined after " << i << " relations: ";
            for (int j = 0; j < n; j++) {
                cout << (char)(queue[j] + 'A' - 1);
            }
            cout << '.' << endl;
            return 0;  // 找到答案，直接结束

        } else if (status == -1) {
            // ? 发现矛盾（环）
            cout << "Inconsistency found after " << i << " relations." << endl;
            return 0;  // 矛盾，直接结束

        }
        // status == 0: 条件不足，继续读入下一条关系
    }

    // 所有关系都读完了仍不能确定
    cout << "Sorted sequence cannot be determined." << endl;
    return 0;
}
//源代码
//
// #include <iostream>
// #include <cstring>
// #include <cstdio>
// using namespace std;
//
// const int maxn=30,maxm=905;
//
// struct Node
// {
//     int v;
//     Node *next;
// }*h[maxn],pool[maxm];
// int tot;
// int du[maxn];
// int q[maxn],head,tail;
// int n,m;
//
// void addEdge(int u, int v)
// {
//     Node *p=&pool[++tot];
//     p->v=v; p->next=h[u]; h[u]=p;
// }
//
// int toposort() //返回值为1代表成立，返回值为0代表条件不足，返回值为-1代表条件矛盾
// {
//     int temp=0;
//     int f=0;
//     for(int i=1;i<=n;i++)
//     {
//         if(du[i]==0)
//         {
//             q[tail++]=i;
//             temp++;
//         }
//     }
//     if(temp>1)
//         f=1;
//     while(head<tail)
//     {
//         temp=0;
//         int u=q[head++];
//         for(Node *p=h[u];p;p=p->next)
//         {
//             du[p->v]--;
//             if(du[p->v]==0)
//             {
//                 q[tail++]=p->v;
//                 temp++;
//             }
//         }
//         if(temp>1)
//             f=1;
//     }
//     if(tail!=n)
//         return -1;
//     else
//         if(f==1)
//             return 0;
//         else return 1;
// }
//
// struct Edge
// {
//     int u,v;
// }a[maxm];
//
// int main()
// {
//     cin>>n>>m;
//     for(int i=1;i<=m;i++)
//     {
//         char aa,bb,cc;
//         cin>>aa>>bb>>cc;
//         a[i].u=aa-'A'+1; a[i].v=cc-'A'+1;
//     }
//     for(int i=1;i<=m;i++)
//     {
//         addEdge(a[i].u,a[i].v);
//         head = tail = 0;
//         memset(du,0,sizeof(du));
//         for(int j=1;j<=i;j++) du[a[j].v]++;
//         int flag=toposort();
//         if(flag==1)
//         {
//             cout<<"Sorted sequence determined after "<<i<<" relations: ";
//             for(int j=0;j<=n-1;j++)
//             {
//                 cout<<(char)(q[j]+'A'-1);
//             }
//             cout<<'.'<<endl;
//             return 0;
//         }
//         else if(flag==0) continue;
//         else
//         {
//             cout<<"Inconsistency found after ";
//             cout<<i<<" relations."<<endl;
//             return 0;
//         }
//     }
//     cout<<"Sorted sequence cannot be determined."<<endl;
//     return 0;
// }

