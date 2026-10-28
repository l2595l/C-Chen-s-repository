//
// Created by 28447 on 2026/9/5.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int n,m,a[maxn],s[maxn];

int main() {
    n=read();
    for (int i=1;i<=n;i++)
        s[i]=s[i-1]+(a[i]=read());
    m=read();
    for (int i=1;i<=m;i++)
    {
        int l=read(),r=read();
        cout << s[r]-s[l-1] << endl;
    }
    return 0;
}