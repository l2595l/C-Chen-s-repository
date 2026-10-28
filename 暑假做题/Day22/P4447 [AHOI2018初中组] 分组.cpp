//
// Created by 28447 on 2026/9/9.
//
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1e5+40;
int f[MAXN],n,ans=1e9,siz[MAXN],top,q[MAXN];
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&f[i]);
	sort(f+1,f+n+1);
	for(int i=1;i<=n;i++){
		int pos=lower_bound(q+1,q+top+1,f[i])-q; //查找当前成员应该放在那一组
		while(q[pos+1]==f[i]&&pos<top) pos++; //一直找到相等的最后一个
		if(pos>top||q[pos]!=f[i]) siz[++top]=1,q[top]=f[i]+1; //无法更新，重开一个组
		else siz[pos]++,q[pos]++; //对当前组更新
	}
	for(int i=1;i<=top;i++) ans=min(ans,siz[i]); //对所有组取最小值
	printf("%d\n",ans);
	return 0;
}
