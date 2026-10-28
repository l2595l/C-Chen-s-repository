//
// Created by 28447 on 2026/9/20.
//O(n)hash

#include<cstdio>
#define p 1000003//这个数越大就越好，最好是质数，这样冲突会减少，但至少要大于200000才行，这里1000003可以轻松AC
#define hash(a) a%p//hash函数
using namespace std;long long n,m,a[p],ans;
struct node
{
    long long x;int y;//x为这个位置对应的数，y为这个数出现了几次
}h[p];
long long abs(long long x){return x<0?-x:x;}//绝对值
int find(long long x)//找到x的位置
{
    int y=hash(abs(x));//因为x可能是负数，所以要abs
    while(h[y].x&&h[y].x!=x) y=hash(++y);
    return y;
}
void push(long long x){int y=find(x);h[y].y++;h[y].x=x;}//先找到此数在hash表中的位置，并将这个位置对应的数量+1，并且将数放进去
int check(long long x){return h[find(x)].y;}//输出这个数在hash表中出现的次数
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=1;i<=n;i++) scanf("%lld",&a[i]),push(a[i]);//输入并放入
    for(long long i=1;i<=n;i++) ans+=check(a[i]-m);//统计
    printf("%lld",ans);//输出
}
