//
// Created by 28447 on 2026/8/19.
//
//É¨À×
#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+2,vector<int>(m+2,0));
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            cin >> a[i][j];
        }
    }
    const int bx[8]{-1, -1, -1, 0, 0, 1, 1, 1};
    const int by[8]{-1, 0, 1, -1, 1, -1, 0, 1};
    int q;
    cin >> q;
    while (q--) {
        int x,y;
        cin >> x >> y;
        if (a[x][y] == 1) {
            cout<<"BOOM!\n";
        }
        else {
            int num = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + bx[i];
                int ny = y + by[i];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                    if (a[nx][ny] == 1) num++;

                }
            }
            cout << num << "\n";
        }

    }
    return 0;
}