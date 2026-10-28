#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100005;
#define ll long long

ll n, m, c[N], num[N], ans;
vector<ll> odd[N], even[N];
ll read () {
    int x=0 ,F=1;
    char ch = getchar_unlocked();
    while (!(ch>='0' && ch<='9')) {
        if (ch=='-') {
            F=-1;
        }
        ch = getchar_unlocked();
    }
    while(ch >= '0' && ch <= '9'){
        num = num * 10 + (ch - '0');
        ch = getchar_unlocked();
    }
    return x * F;
}
int main () {
    n=read(),m=read();
    for (int i=1;i<=n;i++) {
        num[i]=read() % mod;
    }
    for (int i=1;i<=n;i++) {}
}











// int mian(){
//     cin.tie(0) -> sync_with_stdio(0);
//     cin >> n >> m;
//     for(int i=1; i<=n; ++i){
//         cin >> v[i];
//     }
//     for(int i=1; i<=n; ++i){
//         cin >> c[i];
//     }
//     for(int i=1; i<=n; ++i){
//         if(i & 1){
//             odd[c[i]].push_back(i);
//         } else {
//             even[c[i]].push_back(i);
//         } // 分奇偶两类
//     }
//     for(int i=1; i<=m; ++i){
//         int len = odd[i].size() - 1;
//         for(int j=0; j < len; ++j){
//             for(int k=j+1; k < len + 1; ++k){ // 奇偶性相同
//                 ans += (odd[i][j] + odd[i][k]) * (v[odd[i][j]] + v[odd[i][k]]);
//                 ans %= 10007;
//             }
//         }
//         len = even[i].size() - 1;
//         for(int j=0; j < len; ++j){
//             for(int k=j+1; k < len + 1; ++k){
//                 ans += (even[i][j] + even[i][k]) * (v[even[i][j]] + v[even[i][k]]);
//                 ans %= 10007;
//             } // 代入式子中算
//         }
//     }
//     cout << ans << '\n';
//     return EXIT_SUCCESS;
// }
