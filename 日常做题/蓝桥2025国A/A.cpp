#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y
#define lb(x) (x&-x)
#define str to_string
using namespace std;
using ll=long long;
const double EPS=1e-6,PAI=acos(-1.0);
const int MAX=3e4+5,mod=1e9+7,MOD=998244353;
ll quickly_pow(ll a,ll b,ll p){// 快速幂
    ll ans=1;
    while(b){
        if(b&1)ans=(a*ans)%p;
        a=(a*a)%p;
        b>>=1;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<(quickly_pow(2,4042,mod)+quickly_pow(2,2021,mod))%mod<<'\n';// 按照推导直接输出就行
    return 0;
}
