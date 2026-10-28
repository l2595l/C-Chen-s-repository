//
// Created by 28447 on 2026/8/14.
//
// #include<bits/stdc++.h>
// using namespace std;
// #define ll long long
// ll Binary(int x) {
//     if (x == 0) return 0;
//     vector<ll> v;
//     while (x) {
//         v.push_back(x % 2);
//         x /= 2;
//     }
//     ll ans = 0;
//     for (ll i = v.size() - 1; i >= 0; i--) {
//         ans= ans*10 + v[i];
//     }
//     return ans;
// }
// int main() {
//     int x,k;
//     ll b;
//     cin>>x>>k;
//     b = Binary(x);
//     string s= to_string(b);
//     if (k<=s.length() && s[s.length()-k]=='1') cout<<"1";
//     else cout<<"0";
//     return 0;
// }
//////////位与
#include<bits/stdc++.h>
using namespace std;

int main() {
    int x, k;
    cin >> x >> k;

    // 将 x 右移 k-1 位，然后与 1 做按位与
    // 如果结果为 1，说明第 k 位是 1
    int result = (x >> (k - 1)) & 1;
    cout << result << endl;
    
    return 0;
}