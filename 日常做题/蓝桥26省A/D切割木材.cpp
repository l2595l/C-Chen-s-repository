//
// Created by 28447 on 2026/10/23.


//二分
#include <bits/stdc++.h>
using namespace std;
#define int long long // 二分题最好开 long long
int a[1000005], n, k, ans = 1e9;
bool check(int x) // 判断 x 是否可行
{
    int t = 0;
    for(int i = 1; i <= n; i++)
    {
        t += a[i] / x;
        if(a[i] % x == 0) t--; // 统计切割次数
    }
    return t <= k;
}
signed main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int l = 1, r = 1e9; // 1e9也可以，不会T
    while(l <= r) // 二分
    {
        int mid = (l + r) / 2;
        if(check(mid)) r = mid - 1, ans = min(ans, mid); // 模板
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}
