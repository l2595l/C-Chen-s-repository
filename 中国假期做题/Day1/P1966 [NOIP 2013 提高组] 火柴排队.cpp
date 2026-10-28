//
// Created by 28447 on 2026/9/25.
//顺序乘 >= 乱序乘 >= 逆序乘
//认真看，杜绝抄袭
#include<cstdio>
#include<algorithm>
using namespace std;
const int mod=99999997;
long long n,x[10000005],p[1000005],ans=0;
struct fire{
    int hi,bh;
}l1[1000005],l2[1000005];
bool cmp1(fire a,fire b)
{
    return a.hi<b.hi;
}
void msort(int s,int t)//归并排序;
{
    if(s==t)return ;
    int mid=(s+t)/2;
    msort(s,mid);msort(mid+1,t);
    int i=s,k=s,j=mid+1;
    while(i<=mid && j<=t)
    {
        if(x[i]<=x[j])
        {
            p[k]=x[i];
            ++k;++i;

        }
        else
        {
            p[k]=x[j];
            ++k;++j;
            ans=(ans+mid-i+1)%mod;
            //此处找到逆序对，mid-i~mid中数全都与j构成逆序，还会少算一个，+1;
        }
    }
    while(i<=mid)
    {
        p[k]=x[i];
        ++k;++i;
    }
    while(j<=t)
    {
        p[k]=x[j];
        ++k;++j;
    }
    for(int i=s;i<=t;i++)
    {
        x[i]=p[i];
    }
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&l1[i].hi),l1[i].bh=i;
    for(int i=1;i<=n;i++)
        scanf("%d",&l2[i].hi),l2[i].bh=i;
    sort(l1+1,l1+n+1,cmp1);
    sort(l2+1,l2+n+1,cmp1);
    //排序;
    for(int i=1;i<=n;i++)
        x[l2[i].bh]=l1[i].bh;
    msort(1,n);
    //调用归并;
    printf("%lld",ans);
    return 0;//这个不会有人忘的吧？
}
