//
// Created by 28447 on 2026/8/18.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//
// int main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//
//     int n;
//     cin >> n;
//
//     ll sum = 0;//
//     ll max_val, min_val;
//
//     for (int i = 0; i < n; i++) {
//         ll x;
//         cin >> x;
//         sum += x;
//         if (i == 0) {
//             max_val = min_val = x;
//         } else {
//             max_val = max(max_val, x);
//             min_val = min(min_val, x);
//         }
//     }
//
//     cout << sum << " " << max_val << " " << min_val << endl;
//     return 0;
// }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<char> A(n), B(n);
    for (int i=0; i<n; i++) {
        cin >> A[i];
    }
    for (int i=0; i<n; i++) {
        cin >> B[i];
    }
    int min_steps = n;  // 初始化为 n，表示不可能
    // 尝试顺时针旋转 k 格
    for (int k = 0; k < n; k++) {
        bool flag=true;
        // 检查 A 顺时针旋转 k 格后是否等于 B
        // A[i] 旋转后到达位置 (i + k) % n
        // 所以需要 A[i] == B[(i + k) % n]
        for (int i= 0; i < n; i++) {
            if (A[i]!= B[(i + k) % n]) {
                flag=false;
                break;
            }
        }
        if (flag) {
            // 顺时针 k 格，等价于逆时针 n-k 格
            int steps=min(k,n - k);
            min_steps=min(min_steps,steps);
        }
    }

    if (min_steps== n) {
        cout<<"No"<<endl;
    } else {
        cout<<"Yes "<<min_steps<<endl;
    }
    return 0;
}