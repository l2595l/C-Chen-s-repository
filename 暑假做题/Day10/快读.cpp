//
// Created by 28447 on 2026/8/22.
//
#include <bits/stdc++.h>
using namespace std;
//只读数字
int read(){
    int sum=0, fu=1;
    char ch=getchar();
    while(ch != '-' && !isdigit(ch)) ch=getchar();  // 跳过非数字（不含负号）
    if(ch == '-') { fu = -1; ch = getchar(); }
    while(isdigit(ch)){
        sum = sum*10 + (ch-'0');
        ch = getchar();
    }
    return sum*fu;
}
#include <bits/stdc++.h>
using namespace std;
//
// // long long
// long long readLL() {
//     long long x = 0;
//     int f = 1;
//     int ch = getchar();
//     while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
//     if (ch == '-') { f = -1; ch = getchar(); }
//     while (ch >= '0' && ch <= '9') {
//         x = x * 10 + (ch - '0');
//         ch = getchar();
//     }
//     return x * f;
// }
//
// // unsigned long long
// unsigned long long readULL() {
//     unsigned long long x = 0;
//     int ch = getchar();
//     while (ch < '0' || ch > '9') ch = getchar();
//     while (ch >= '0' && ch <= '9') {
//         x = x * 10 + (ch - '0');
//         ch = getchar();
//     }
//     return x;
// }
//
// // double，支持小数和科学计数法，如 1.23e-4
// double readDouble() {
//     double x = 0;
//     int f = 1;
//     int ch = getchar();
//
//     while (ch != '-' && (ch < '0' || ch > '9') && ch != '.') ch = getchar();
//
//     if (ch == '-') {
//         f = -1;
//         ch = getchar();
//     }
//
//     while (ch >= '0' && ch <= '9') {
//         x = x * 10 + (ch - '0');
//         ch = getchar();
//     }
//
//     if (ch == '.') {
//         ch = getchar();
//         double p = 0.1;
//         while (ch >= '0' && ch <= '9') {
//             x += (ch - '0') * p;
//             p *= 0.1;
//             ch = getchar();
//         }
//     }
//
//     if (ch == 'e' || ch == 'E') {
//         int exp = 0, ef = 1;
//         ch = getchar();
//         if (ch == '-') {
//             ef = -1;
//             ch = getchar();
//         } else if (ch == '+') {
//             ch = getchar();
//         }
//         while (ch >= '0' && ch <= '9') {
//             exp = exp * 10 + (ch - '0');
//             ch = getchar();
//         }
//         x *= pow(10, ef * exp);
//     }
//
//     return f * x;
// }
//
// // 读第一个非空白字符
// char readChar() {
//     int ch = getchar();
//     while (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') ch = getchar();
//     return (char)ch;
// }
//
// // 读一个不含空白的字符串
// string readString() {
//     string s;
//     int ch = getchar();
//     while (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') ch = getchar();
//     while (ch != EOF && !(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')) {
//         s.push_back((char)ch);
//         ch = getchar();
//     }
//     return s;
// }
//
// // 读一整行，包含空格
// string readLine() {
//     string s;
//     int ch = getchar();
//     while (ch != '\n' && ch != EOF) {
//         s.push_back((char)ch);
//         ch = getchar();
//     }
//     return s;
// }
//
// // __int128
// __int128 readInt128() {
//     __int128 x = 0;
//     int f = 1;
//     int ch = getchar();
//     while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
//     if (ch == '-') {
//         f = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9') {
//         x = x * 10 + (ch - '0');
//         ch = getchar();
//     }
//     return x * f;
// }
int main() {
    printf("%d",read());
    return 0;
}