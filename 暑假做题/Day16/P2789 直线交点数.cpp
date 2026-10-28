//
// Created by 28447 on 2026/8/29.
//
#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
int n,MAX=-1,ans=0;
bool f[11000];
void g(int n,int k)
{
    if (n==0) {f[k]=true;MAX=max(k,MAX);}
    else for (int r=n;r>=1;r--)g(n-r,r*(n-r)+k);
}
int main()
{
    cin>>n;
    memset(f,false,sizeof(f));
    g(n,0);
    for (int i=0;i<=MAX;i++)
        if (f[i]) ans++;
    cout<<ans;
    return 0;
}

////
//动态规划
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;

    // dp[i] 表示拆分 i 能得到的所有 k 值集合
    vector<unordered_set<int>> dp(n + 1);
    dp[0].insert(0);  // 基准情况

    for (int i = 1; i <= n; i++) {
        for (int r = 1; r <= i; r++) {
            int product = r * (i - r);
            for (int k : dp[i - r]) {
                dp[i].insert(product + k);
            }
        }
    }

    cout << dp[n].size() << endl;
    return 0;
}
//bitset
#include <iostream>
#include <bitset>
using namespace std;

const int MAXN = 10000;
bitset<MAXN * MAXN / 4 + 5> dp[105];  // 预估最大 k 值

int main() {
    int n;
    cin >> n;

    dp[0][0] = 1;  // dp[i] 表示拆分 i 能得到的 k 值的 bitset

    for (int i = 1; i <= n; i++) {
        for (int r = 1; r <= i; r++) {
            int shift = r * (i - r);
            dp[i] |= (dp[i - r] << shift);
        }
    }

    cout << dp[n].count() << endl;  // count() 返回 1 的个数
    return 0;
}