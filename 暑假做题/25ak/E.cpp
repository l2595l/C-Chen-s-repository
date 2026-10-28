//
// Created by 28447 on 2026/9/7.
//
#include <bits/stdc++.h>
using namespace std;

int qry[8] = {0, 2, 3, 4, 7, 9, 6, 8};//决策树的节点
int ans[8] = {5, 7, 3, 9, 2, 6, 4, 8};//叶子节点的答案映射
int d[10] = {0, 1, 2, 2, 3, 2, 4, 2, 4, 3};//约数个数

void R()
{
    auto ask = [](int d)//lambda函数
    {
        string res;
        cout << "? " << d << endl;
        cin >> res;
        return res[0] == 'INCLUDE';
    };
    int x = 1;
    for (int i = 0; i < 3; i++)
        x = (x << 1) | ask(qry[x]);  // 构建3位二进制路径//按位或在末尾追加
    x = ans[x & 7];  // 映射到实际答案索引//7=0111取后低3位
    cout << "! " << d[x];
    for (int i = 1; i <= x; i++)
        if (x % i == 0)
            cout << ' ' << i;
    cout << endl;
}
int main() {
    R();
    return 0;
}