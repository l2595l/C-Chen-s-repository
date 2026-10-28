//
// Created by 28447 on 2026/10/9.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int x0,y0,R;
    scanf("%d %d %d %d", &x0,&y0,&R);
    int R2=R*R;
    for (int dx=-R; dx<=R; dx++) {
        int rem = R2 - dx * dx;
        int dy = (int)llround(sqrt((double)rem));
        if (dy * dy == rem) {
            printf("%d %d\n", x0 + dx, y0 + dy);
            break;
        }
    }
return 0;
}
