//
// Created by 28447 on 2026/10/16.
//
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
namespace fast_IO
{
    char buf[1 << 23], *p1 = buf, *p2 = buf;
    char __getchar()
    {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
    }
    template <typename T>
    T read()
    {
        T x = 0;
        char ch = __getchar();
        while(!isdigit(ch)) ch = __getchar();
        while(isdigit(ch)) {x = x * 10 + (ch ^ 48); ch = __getchar();}
        return x;
    }
}
const int N = 1e7 + 19;
struct Hash_table{
    LL h[N], kk[N];
    bool exist[N];
    void init() //其实这个函数要不要都行
    {
        memset(h, 0, sizeof(h));
        memset(kk, 0, sizeof(kk));
        memset(exist, false, sizeof(exist));
        return;
    }
    void insert(LL x, LL y)
    {
        int k = x % N; //因为输入的都是正数，所以就不用再 +N 了
        while(exist[k] == true)
        {
            if(kk[k] == x) break;
            k ++;
            if(k == N) k = 0;
        }
        kk[k] = x, h[k] = y;
        exist[k] = true;
        return;
    }
    LL find(LL x)
    {
        int k = x % N;
        while(exist[k] == true)
        {
            if(kk[k] == x) return h[k];
            k ++;
            if(k == N) k = 0;
        }
        return 0;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    n = fast_IO::read<int>();
    Hash_table hash_table;
    hash_table.init();
    LL sum = 0;
    for(int i = 1; i <= n; i ++)
    {
        LL x, y;
        x = fast_IO::read<LL>(), y = fast_IO::read<LL>();
        LL ans = i * hash_table.find(x);
        sum += ans;
        hash_table.insert(x, y);
    }
    cout << sum << "\n";
    return 0;
}
