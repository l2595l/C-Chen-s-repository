//
// Created by 28447 on 2026/8/15.
//
#include <bits/stdc++.h>
using namespace std;
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
///二分查找
/*lower_bound	第一个 ≥ target 的位置	迭代器/指针	非递减有序
upper_bound	第一个 > target 的位置	迭代器/指针	非递减有序
equal_range	同时找 lower_bound 和 upper_bound	pair 对（两个迭代器）	非递减有序
binary_search	判断 target 是否存在	bool（true/false）    非递减有序
int lower_bound(int arr[], int left, int right, int target) {
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= target) {
            right = mid;      // 往左半部分找
        } else {
            left = mid + 1;   // 往右半部分找
        }
    }
    return left;
}
*/
////另解
#include<cstdio>
#include<map>
std::map<int,int>m;
typedef std::map<int,int>::iterator it;
int main(){
    int n,ans=0x3f3f3f3f;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        int t;
        scanf("%d",&t);
        ++m[t];
        //记录图像。
    }
    while(!m.empty()){
        it i=m.begin(),j=m.begin();
        --(*i).second;
        int t=1;
        for(++j;j!=m.end()&&(*j).first==(*i).first+1&&(*j).second>(*i).second;++i,++j){
            ++t;
            --(*j).second;
        }
        //若 i,j 所对应的能力值是连续的，且 i 对应的那一列高度不高于 j，则继续画线。
        i=m.begin();
        while(i!=m.end()&&(*i).second==0){
            m.erase((*i++).first);
        }
        //高度降为 0 后直接删除，便于计算。
        if(t<ans){
            ans=t;
        }
        //记录答案。
    }
    printf("%d",ans);
    return 0;
}
