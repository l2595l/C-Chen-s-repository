//
// Created by 28447 on 2026/8/29.
//
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,s,e,P=9901;
inline int qpow(int x,int q=P-2) {int r=1;for(;q;q>>=1,x=x*x%P) if(q&1) r=r*x%P;return (r+P)%P;}
signed main()
{
    scanf("%lld%lld",&a,&b),s=1,e=sqrt(a);
    for(int i=2,t=0;i<=e;i++,t=0) {while(a%i==0) a/=i,t++;t*=b,s=s*(i%P!=1?(qpow(i,t+1)-1)%P*qpow(i-1)%P:(t+1)%P)%P;}
    if(a>1) s=s*(a%P!=1?(qpow(a,b+1)-1)%P*qpow(a-1)%P:2);
    return printf("%lld\n",(s+P)%P),0;
}
