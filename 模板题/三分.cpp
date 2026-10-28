//
// Created by 28447 on 2026/10/16.
//
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e4+10;
const double EPS=1e-9;
int n,a[N],b[N],c[N];
double calc(double x,int p){ //计算二次函数 f(x)
    return a[p]*x*x+b[p]*x+c[p];
}
double f(double x){ //求最大值 F(x)
    double res=-1e18;
    for(int i=1;i<=n;++i)
        res=max(res,calc(x,i));
    return res;
}
void solve(){
    n=read();
    for(int i=1;i<=n;++i)
        a[i]=read(),b[i]=read(),c[i]=read();
    // double l=0,r=1000; //已知 F(x) 在区间 [0,1000] 内
    while(r-l>EPS){
        double lmid=l+(r-l)/3,rmid=r-(r-l)/3.0; //两个中间点
        if(f(lmid)<f(rmid)) //M1 更贴近答案
            r=rmid; //舍去区间 (M2,R]
        else l=lmid; //舍去区间 [L,M1)
    }
    printf("%.4lf\n",f(l)); //最终输出的是 F(x) 的最小值
    return;
}
int main(){
    int T=read();
    while(T--)
        solve();
    return 0;
}
