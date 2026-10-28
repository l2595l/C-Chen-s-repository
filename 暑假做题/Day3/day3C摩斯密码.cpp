//
// Created by 28447 on 2026/8/15.
//
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    switch(n) {
        case 0: cout << "-----\n"; break;
        case 1: cout << ".----\n"; break;
        case 2: cout << "..---\n"; break;
        case 3: cout << "...--\n"; break;
        case 4: cout << "....-\n"; break;
        case 5: cout << ".....\n"; break;
        case 6: cout << "-....\n"; break;
        case 7: cout << "--...\n"; break;
        case 8: cout << "---..\n"; break;
        case 9: cout << "----.\n"; break;
        default: break;
    }

    return 0;
}
//法2
// for (std::cin >> n; i++ < 5; )
//     std::cout << "-."[n-- - 1u < 5];
//等价
// #include <iostream>
// using namespace std;
//
// int main() {
//     int n;
//     cin >> n;
//
//     for (int i = 0; i < 5; i++) {
//         if (n - 1 < 5) {  // 判断当前位置是否在范围内
//             cout << '.';
//         } else {
//             cout << '-';
//         }
//         n--;  // 移到下一个位置
//     }
//
//     return 0;
// }