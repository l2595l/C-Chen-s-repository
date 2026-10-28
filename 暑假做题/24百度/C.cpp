//
// Created by 28447 on 2026/9/9.
//
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int x, y;
        cin >> x >> y;

        // 大图标需要的屏幕数（每屏最多2个大图标）
        int screens = (y + 1) / 2;

        // 这些屏幕中剩余的小图标容量
        int remaining_cells = screens * 15 - y * 4;

        // 如果小图标放不下，增加屏幕
        if(x > remaining_cells) {
            screens += (x - remaining_cells + 14) / 15;  // 向上取整
        }

        cout << screens << endl;
    }

    return 0;
}