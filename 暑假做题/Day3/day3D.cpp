//
// Created by 28447 on 2026/8/15.
//
#include<bits/stdc++.h>
using namespace std;
bool isleep(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
bool istrue(int y,int m,int d) {
    int day[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m<1||m>12) return false;
    if (d<1) return false;
    int maxd = day[m-1];
    if (m==2 && isleep(y)) maxd = 29;
    return d <= maxd;
}

int main() {
    int y,m,d;
    cin >> y >> m >> d;
    if (m==4&&d==1) {cout << "NO\n"; return 0;}
    cout << (istrue(y,m,d) ? "YES\n" : "NO\n");
    return 0;
}