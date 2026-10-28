//
// Created by 28447 on 2026/8/14.


//下面是六种位运算在 C++ 中的语法：
/*
x&y  // x 与 y
x|y  // x 或 y
~x   // x 取反
x^y  // x 异或 y
x<<y // x 左移 y 位
x>>y // x 右移 y 位
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ll a,b,c;
    cin>>a>>b>>c;
    cout << (a ^ b ^ c) << endl;
    return 0;
}
////结构化绑定
// // 数组
// int arr[2] = {1, 2};
// auto [a, b] = arr;  // a=1, b=2
//
// // pair
// pair<int, string> p = {1, "hello"};
// auto [id, name] = p;  // id=1, name="hello"
//
// // tuple
// tuple<int, double, string> t = {1, 3.14, "pi"};
// auto [i, d, s] = t;  // i=1, d=3.14, s="pi"
//
// // 结构体
// struct Point { int x, y; };
// Point pt = {10, 20};
// auto [x, y] = pt;  // x=10, y=20
////////使用 map 计数
// #include <bits/stdc++.h>
// using namespace std;
//
// int main() {
//     int x, y, z;
//     cin >> x >> y >> z;
//
//     unordered_map<int, int> cnt;
//     cnt[x]++; cnt[y]++; cnt[z]++;
//
//     for (auto [num, count] : cnt) {
//         if (count == 1) {
//             cout << num << endl;
//             break;
//         }
//     }
//     return 0;
// }