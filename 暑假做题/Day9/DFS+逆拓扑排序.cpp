//
// Created by 28447 on 2026/8/21.



//三色判断有无环
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VEX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

// 邻接表边结点
typedef struct ArcNode {
    int adjvex;                 // 邻接顶点编号
    struct ArcNode* nextarc;    // 下一条边
} ArcNode;

// 邻接表顶点结点
typedef struct VNode {
    int data;                   // 顶点数据
    ArcNode* firstarc;          // 第一条边
} VNode;

// 图结构
typedef struct {
    VNode vertices[MAX_VEX];    // 顶点数组
    int vexnum, arcnum;         // 顶点数，边数
} Graph;

// 颜色数组和环标志
int color[MAX_VEX];
bool hasCycle = false;

// 函数声明
void InitGraph(Graph* G);
void AddArc(Graph* G, int from, int to);
void DFSTraverse(Graph* G);
void DFS(Graph* G, int v);
void PrintGraph(Graph* G);

// 初始化图
void InitGraph(Graph* G) {
    G->vexnum = 0;
    G->arcnum = 0;
    for (int i = 0; i < MAX_VEX; i++) {
        G->vertices[i].data = -1;
        G->vertices[i].firstarc = NULL;
    }
}

// 添加顶点（返回顶点编号）
int AddVertex(Graph* G, int data) {
    if (G->vexnum >= MAX_VEX) {
        printf("顶点数超过最大限制\n");
        return -1;
    }
    G->vertices[G->vexnum].data = data;
    G->vertices[G->vexnum].firstarc = NULL;
    return G->vexnum++;
}

// 添加有向边 from -> to
void AddArc(Graph* G, int from, int to) {
    if (from < 0 || from >= G->vexnum || to < 0 || to >= G->vexnum) {
        printf("顶点编号错误\n");
        return;
    }

    // 创建边结点（头插法）
    ArcNode* newNode = (ArcNode*)malloc(sizeof(ArcNode));
    newNode->adjvex = to;
    newNode->nextarc = G->vertices[from].firstarc;
    G->vertices[from].firstarc = newNode;
    G->arcnum++;
}

// 获取第一个邻接顶点
int FirstNeighbor(Graph* G, int v) {
    if (v < 0 || v >= G->vexnum) return -1;
    if (G->vertices[v].firstarc == NULL) return -1;
    return G->vertices[v].firstarc->adjvex;
}

// 获取下一个邻接顶点
int NextNeighbor(Graph* G, int v, int w) {
    if (v < 0 || v >= G->vexnum) return -1;

    ArcNode* p = G->vertices[v].firstarc;
    // 找到当前邻接点w的位置
    while (p != NULL && p->adjvex != w) {
        p = p->nextarc;
    }
    if (p == NULL || p->nextarc == NULL) return -1;
    return p->nextarc->adjvex;
}

// DFS遍历（检测环并输出逆拓扑序列）
void DFSTraverse(Graph* G) {
    // 初始化颜色数组
    for (int v = 0; v < G->vexnum; v++) {
        color[v] = WHITE;
    }
    hasCycle = false;

    printf("逆拓扑排序序列：");

    // 对所有未访问顶点进行DFS
    for (int v = 0; v < G->vexnum; v++) {
        if (color[v] == WHITE) {
            DFS(G, v);
            if (hasCycle) {
                printf("\n??  检测到回路！该图不存在逆拓扑排序序列\n");
                return;
            }
        }
    }
    printf("\n? 该图无回路，以上为逆拓扑排序序列\n");
}

// 深度优先搜索（核心：三色标记法）
void DFS(Graph* G, int v) {
    // 标记为正在访问（当前递归栈中）
    color[v] = GRAY;

    // 遍历所有邻接顶点
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (color[w] == WHITE) {
            // 未访问，递归访问
            DFS(G, w);
            if (hasCycle) return;  // 已经发现环，提前退出
        }
        else if (color[w] == GRAY) {
            // 遇到灰色顶点，说明存在环（后向边）
            hasCycle = true;
            printf("\n发现环：顶点 %d -> 顶点 %d\n", v, w);
            return;
        }
        // 若 color[w] == BLACK，说明该顶点已完成，直接跳过
    }

    // 所有邻接点处理完毕，标记为已完成
    color[v] = BLACK;

    // ★ 逆拓扑排序：在顶点退栈（即将返回）时输出
    printf("%d ", G->vertices[v].data);
}

// 打印图的结构（用于调试）
void PrintGraph(Graph* G) {
    printf("\n图的邻接表结构：\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("顶点 %d: ", G->vertices[i].data);
        ArcNode* p = G->vertices[i].firstarc;
        while (p != NULL) {
            printf("-> %d ", G->vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
    printf("\n");
}

// 主函数 - 测试用例
int main() {
    Graph G;
    InitGraph(&G);

    printf("========== 测试1：无环有向图 ==========\n");
    // 创建顶点：0,1,2,3,4
    int v0 = AddVertex(&G, 0);
    int v1 = AddVertex(&G, 1);
    int v2 = AddVertex(&G, 2);
    int v3 = AddVertex(&G, 3);
    int v4 = AddVertex(&G, 4);

    // 添加有向边（DAG图）
    // 0 -> 1, 0 -> 2
    // 1 -> 3
    // 2 -> 3, 2 -> 4
    // 3 -> 4
    AddArc(&G, v0, v1);
    AddArc(&G, v0, v2);
    AddArc(&G, v1, v3);
    AddArc(&G, v2, v3);
    AddArc(&G, v2, v4);
    AddArc(&G, v3, v4);

    PrintGraph(&G);
    DFSTraverse(&G);

    printf("\n========================================\n\n");

    // ============================================
    // 测试2：有环有向图
    printf("========== 测试2：有环有向图 ==========\n");
    Graph G2;
    InitGraph(&G2);

    int a0 = AddVertex(&G2, 0);
    int a1 = AddVertex(&G2, 1);
    int a2 = AddVertex(&G2, 2);
    int a3 = AddVertex(&G2, 3);

    // 添加有向边（包含环）
    // 0 -> 1, 0 -> 2
    // 1 -> 2
    // 2 -> 0, 2 -> 3  （2 -> 0 形成环）
    // 3 -> 3          （自环）
    AddArc(&G2, a0, a1);
    AddArc(&G2, a0, a2);
    AddArc(&G2, a1, a2);
    AddArc(&G2, a2, a0);  // 环
    AddArc(&G2, a2, a3);
    AddArc(&G2, a3, a3);  // 自环

    PrintGraph(&G2);
    DFSTraverse(&G2);

    printf("\n========================================\n");

    // 释放内存（简化：未逐个释放边结点）
    // 在实际项目中需要遍历释放

    return 0;
}