//
// Created by 28447 on 2026/8/13.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

// 快速读入
template <class I>
inline void read(I &num){
    num = 0; char c = getchar(), up = c;
    while(!isdigit(c)) up = c, c = getchar();
    while(isdigit(c)) num = (num << 1) + (num << 3) + (c ^ '0'), c = getchar();
    up == '-' ? num = -num : 0; return;
}
template <class I>
inline void read(I &a, I &b) {read(a); read(b);}
template <class I>
inline void read(I &a, I &b, I &c) {read(a); read(b); read(c);}

const int fx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
const int fy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};

int bx, by, mx, my;
ll f[40];   //这次只需要一维数组啦
bool s[40][40];

int main(){
    read(bx, by); read(mx, my);
    bx += 2; by += 2; mx += 2; my += 2;
    f[2] = 1;   //初始化
    s[mx][my] = 1;
    for(int i = 1; i <= 8; i++) s[mx + fx[i]][my + fy[i]] = 1;
    for(int i = 2; i <= bx; i++){
        for(int j = 2; j <= by; j++){
            if(s[i][j]){
                f[j] = 0; // 还是别忘了清零
                continue;
            }
            f[j] += f[j - 1];
            //全新的 简洁的状态转移方程
        }
    }
    printf("%lld\n", f[by]);
    return 0;
}
// //切比雪夫距离、曼哈顿距离
// #include <cmath>
// #include <cctype>
// #include <cstdio>
// #include <cstdlib>
// #include <iostream>
// #include <algorithm>
// #define ll long long
//
// inline int read(){
//     int num = 0; char c = getchar();
//     while(!isdigit(c)) c = getchar();
//     while(isdigit(c)) num = (num << 1) + (num << 3) + (c ^ '0'), c = getchar();
//     return num;
// }
//
// int bx, by, mx, my;
// ll f[30];
//
// inline bool check(int x, int y) {
//     if(x == mx && y == my) return 1;
//     return (std::abs(mx - x) + std::abs(my - y) == 3) && (std::max ((std::abs(mx - x)), std::abs(my - y)) == 2);
// }
//
// int main(){
//     bx = read() + 2, by = read() + 2, mx = read() + 2, my = read() + 2;
//     f[2] = 1;
//     for(int i = 2; i <= bx; i++){
//         for(int j = 2; j <= by; j++){
//             if(check(i, j)){
//                 f[j] = 0;
//                 continue;
//             }
//             f[j] += f[j - 1];
//         }
//     }
//     printf("%lld\n", f[by]);
//     return 0;
// }

// //////////组合数
// ///#include<bits/stdc++.h>
// #define ll long long
// using namespace std;
// ll C(int m,int n)
// {
//     if(n<0 || m<0 || n<m)
//         return 0;
//     ll tot=1;
//     for(int i=1;i<=m;i++)
//     {
//         tot*=n-i+1;
//         tot/=i;
//     }
//     return tot;
// }
// int n,m,x,y;
// int rt[5][5]={
//     0,0,1,0,0,
//     0,0,1,1,0,
//     0,0,0,1,1};//我们记录下哪些节点作为起点时，可以从右边的口子出去，其中(2,2)为马的位置
// int dw[5][5]={
//     {},
//     {},
//     1,1,0,0,0,
//     0,1,1,0,0,
//     0,0,1,0,0};//同理，哪些可以从下边口子出去
// int main()
// {
//     cin>>n>>m>>x>>y;
//     if(n-x<3 && m-y<3)
//     {
//         x=n-x;
//         y=m-y;
//     }//为了不想把特判代码写两遍，如果终点离得太近就旋转180度，变成起点离得太近的情况
//     if(x<3 && y<3)
//     {
//         int nx=2-x;
//         int ny=2-y;//起点相对于马的坐标而言的位置
//         ll tot=0;
//         tot+=C(n-x,m+n-x-y-3)*rt[nx][ny];//右边出去的方法数
//         tot+=C(n-x-3,m+n-x-y-3)*dw[nx][ny];//同理
//         cout<<tot;
//         return 0;
//     }
//     ll tot=C(n,n+m);
//     for(int i=-2;i<=2;i++)
//         tot-=C(x-i,x+y)*C(n-x+i,n+m-x-y);
//     //情况1
//     tot+=C(x+2,x+y-1)*C(n-x-3,n+m-x-y-1);//情况2
//     tot+=C(x-3,x+y-1)*C(n-x+2,n+m-x-y-1);//情况3
//     tot+=C(x,x+y-3)*C(n-x-3,n+m-x-y-3);//情况4
//     tot+=C(x-3,x+y-3)*C(n-x,n+m-x-y-3);//情况5
//     cout<<tot;
//     return 0;
// }
