//
// Created by 28447 on 2026/9/16.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
int fa[N], siz[N];
int n, m;

int find(int x){
    if(fa[x] == x) return x; // 已经是根节点
    else return fa[x] = find(fa[x]); // 继续找
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1; // 初始化
    for(int i = 1; i <= m; ++i){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1){ // 合并操作
            x = find(x), y = find(y); // 查询各自的代表元素
            if(x == y) continue; // 如果已经在同一个集合，跳过
            if(siz[y] < siz[x]) swap(x, y); // 改变合并顺序
            siz[y] += siz[x]; // 计算新的秩
            fa[x] = y; // 合并
        }
        else{ // 查询操作的一种变形
            x = find(x), y = find(y); // 查询各自的代表元素
            if(x == y) cout << "Y" << endl; // 是否在同一个集合
            else       cout << "N" << endl;
        }
    }
    return 0;
}
