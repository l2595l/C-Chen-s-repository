// //
// // Created by 28447 on 2026/8/15.
// //
// #include<bits/stdc++.h>
// using namespace std;
// #define ll long long
// template <class I>
// inline void read(I &num){
//     num = 0;
//     char c = getchar(), up = c;
//     while(!isdigit(c)) up = c, c = getchar();
//     while(isdigit(c)) num = (num << 1) + (num << 3) + (c ^ '0'), c = getchar();
//     up == '-' ? num = -num : 0;
// }
// template <class I>
// inline void read(I &x, I &y) {read(x); read(y);}
// int main() {
//     ll x,y;
//     read(x,y);
//     double ans=abs(x*y)/2.00;
//     cout << fixed << setprecision(2) << ans << '\n';
//     return 0;
// }
#include<bits/stdc++.h>
using namespace std;
#define ll long long

template <class I>
inline void read(I &num){
    num = 0;
    char c = getchar(), up = c;
    while(!isdigit(c)) up = c, c = getchar();
    while(isdigit(c)) num = (num << 1) + (num << 3) + (c ^ '0'), c = getchar();
    up == '-' ? num = -num : 0;
}

template <class I>
inline void read(I &x, I &y) {read(x); read(y);}

int main() {
    ll x, y;
    read(x, y);
    ll p = x * y;
    if (p < 0) p = -p;
    if (p % 2 == 0) {
        cout << p / 2 << ".00\n";
    } else {
        cout << p / 2 << ".50\n";
    }
    return 0;
}