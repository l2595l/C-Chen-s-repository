//
// Created by 28447 on 2026/9/6.
//向前星+bfs删除+dfs统计剩余分量
#include<bits/stdc++.h>
#define int long long
#define maxn 1000010
using namespace std;
int n,k,tot,deg[maxn],lnk[maxn],q[maxn],t[maxn],vis[maxn],f[maxn],ans;
struct edge{
    int to,nxt;
}e[maxn*2];
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
    return ret*f;
}
void add_edge(int x,int y){
    e[++tot]=(edge){y,lnk[x]};
    lnk[x]=tot;
}
void dfs(int x){
    f[x]=1;
    for(int i=lnk[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(f[v]||vis[v])continue;
        f[v]=1;
        dfs(v);
    }
}
void bfs(){
    int hed=0,til=0;
    for(int i=1;i<=n;i++)if(deg[i]==k)q[++til]=i,vis[i]=1;
    while(hed!=til){
        int tot1=0;
        while(hed!=til){
            hed++;
            int u=q[hed];
            deg[u]=0,vis[u]=1;
            for(int i=lnk[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(vis[v]==1)continue;
                deg[v]--;
                if(deg[v]==k)t[++tot1]=v;
            }
        }
        for(int i=1;i<=tot1;i++)if(deg[t[i]]==k)q[++til]=t[i],vis[t[i]]=1;
    }
}
signed main(){
    n=read(),k=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add_edge(u,v),add_edge(v,u);
        deg[u]++,deg[v]++;
    }
    bfs();
    for(int i=1;i<=n;i++)if(!vis[i]&&!f[i])ans++,dfs(i);
    printf("%lld\n",ans);
    return 0;
}
