//
// Created by 28447 on 2026/10/19.
//
#include<cstdio>
#include<algorithm>
using namespace std;

inline int read(){                      // 全部统一用同一个读入器，避免 cin 和 getchar 混用
    int a = 0; char c = getchar();
    while(c < 48 || c > 57) c = getchar();
    while(c > 47 && c < 58){ a = (a<<3) + (a<<1) + c - 48; c = getchar(); }
    return a;
}

struct Bomb{ int l, a, r; };            // l,r 存成绝对端点；a 是位置 p
Bomb t[200005], s[200005];              // t 读入原序，s 排序后
int zyl[200005], cnt[200005];

int main(){
    int n = read();
    int maxa = 0;
    for(int i = 0; i < n; i++){
        t[i].a = read();
        t[i].l = t[i].a - read();       // 左端点 p-l
        t[i].r = t[i].a + read();       // 右端点 p+r
        maxa = max(maxa, t[i].a);
    }

    // 排序：位置范围小就用桶排，否则用快排
    if(maxa <= (n<<4)){
        for(int i = 0; i < n; i++) cnt[t[i].a + 1]++;   // 只在走桶排时才动 cnt，避免越界隐患
        for(int i = 2; i <= maxa + 1; i++) cnt[i] += cnt[i-1];
        for(int i = 0; i < n; i++) s[cnt[t[i].a]++] = t[i];
    }else{
        for(int i = 0; i < n; i++) s[i] = t[i];
        sort(s, s + n, [](const Bomb &x, const Bomb &y){ return x.a < y.a; });
    }

    // zyl[j] = 位置最靠右、且能直接炸到 j 的炸弹下标（只可能 >= j）
    for(int i = n-1, j = n-1; i > 0; i--)
        while(j >= 0 && s[j].a >= s[i].l) zyl[j--] = i;

    int ans = 0;
    for(int i = 0; i < n; ans++){
        // 沿着“谁能直接炸到我”一路向右跳，跳出最远的起爆点
        int j = i;
        while(zyl[j] > j) j = zyl[j];
        // 能连锁到 j 就说明 [i,j] 全部被炸到，取这段里最大的右端点
        int maxr = s[j].r;
        for(; i < j; i++) maxr = max(maxr, s[i].r);
        // 再向右继续扩张
        for(; i < n && s[i].a <= maxr; i++) maxr = max(maxr, s[i].r);
    }
    printf("%d\n", ans);
    return 0;
}
