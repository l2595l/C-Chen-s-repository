//
// Created by 28447 on 2026/8/17.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long

template<class I>
inline void read(I &num){
  num = 0; char c = getchar(), up = c;
  while(!isdigit(c)) up = c, c = getchar();
  while(isdigit(c)) num = (num<<1)+(num<<3)+(c^'0'), c = getchar();
  up == '-' ? num = -num : 0;
}

// 生成素数
vector<int> Primes(int limit){
  vector<int> primes;
  vector<char> isComp(limit+1, 0);
  for(int i=2;i<=limit;i++){
      if(!isComp[i]) primes.push_back(i);
      for(int p:primes){
          if(1LL*i*p>limit) break;//转ll
          isComp[i*p]=1;
          if(i%p==0) break;
      }
  }
  return primes;
}

// n 的最小质因子
int spf(int n, const vector<int>& primes){
  for(int p:primes){
      if(1LL*p*p>n) break;
      if(n%p==0) return p;
  }
  return n;// 是质数
}

// k 的因子个数公式
int num(int k, const vector<int>& primes){
  int cnt=1;
  for(int p:primes){
      if(1LL*p*p>k) break;
      if(k%p==0){
          int e=0;
          while(k%p==0){ k/=p; e++; }
          cnt*=e+1;
      }
  }
  if(k>1) cnt*=2;// 剩一个 >sqrt(k) 的质因子
  return cnt;
}

int main(){
    vector<int> primes = Primes(1415);// sqrt(2e6)≈1414

    // valid[m] = 满足 (2r?+3r+5m)%77==0 的余数 r
    vector<int> valid[77];
    for(int m=0;m<77;m++)
        for(int r=0;r<77;r++) {
            if((2*r*r+3*r+5*m)%77==0)valid[m].push_back(r);
        }

    int q; read(q);
    vector<pair<int,int>> qs(q);// (n, 原始下标)
    int maxN=0;
    for(int i=0;i<q;i++) {
        read(qs[i].first);
        qs[i].second=i;
        maxN=max(maxN,qs[i].first);
    }
    sort(qs.begin(), qs.end());

    vector<ll> out(q);
    ll sumResidue[77]={0};
    int ptr=0;

    for(int n=1;n<=maxN;n++){
        if(n>=2){// x=1 无合法 y，跳过
          int p=spf(n, primes);
          sumResidue[n%77] += num(n+p, primes);// 加入 x=n 的贡献
       }
        while(ptr<q && qs[ptr].first==n){// 回答所有 n 等于当前值的询问
          ll s=0;
          for(int r:valid[n%77]) s+=sumResidue[r];
          out[qs[ptr].second]=s;
          ptr++;
        }
    }

    for(int i=0;i<q;i++) cout<<out[i]<<'\n';
    return 0;
}
// int main(){
//     // ============================================================
//     // 第1步：生成质数表
//     // ============================================================
//     // 为什么是 1415？
//     // 因为后面要计算 divisors(n+p)，n最大1e6，p最大也是1e6左右
//     // 所以 n+p 最大约 2e6，sqrt(2e6) ≈ 1414.2，取 1415 就够了
//     vector<int> primes = sievePrimes(1415);
//
//     // ============================================================
//     // 第2步：预处理所有可能的余数组合
//     // ============================================================
//     // valid[m]：当 n % 77 == m 时，所有满足条件的 x % 77 的值
//     //
//     // 为什么只需要关心余数？
//     // 因为 (2x?+3x+5n) % 77 只取决于 x%77 和 n%77
//     // 所以提前把 77×77=5929 种组合全部算好
//     vector<int> valid[77];
//     for(int m=0; m<77; m++) {          // m = n % 77
//         for(int r=0; r<77; r++) {      // r = x % 77
//             // 检查这个余数组合是否满足整除条件
//             if((2*r*r + 3*r + 5*m) % 77 == 0) {
//                 valid[m].push_back(r); // 满足就记录下来
//             }
//         }
//     }
//
//     // ============================================================
//     // 第3步：读入所有询问（离线处理）
//     // ============================================================
//     int q;
//     read(q);  // 读入询问次数
//
//     // qs 存储所有询问：pair< n值, 原始下标 >
//     // 因为后面要排序，所以需要记录原始下标，保证输出顺序正确
//     vector<pair<int,int>> qs(q);
//     int maxN = 0;  // 所有询问中最大的 n，决定循环到哪里
//
//     for(int i=0; i<q; i++) {
//         read(qs[i].first);   // 读入 n
//         qs[i].second = i;    // 记录原始下标
//         maxN = max(maxN, qs[i].first);  // 更新最大值
//     }
//
//     // 按 n 从小到大排序，方便后面一次性扫描
//     sort(qs.begin(), qs.end());
//
//     // ============================================================
//     // 第4步：准备输出和辅助数组
//     // ============================================================
//     vector<ll> out(q);       // 存储每个询问的答案，按原始下标存放
//     ll sumResidue[77] = {0}; // sumResidue[r]：所有 x%77==r 的 x 的贡献之和
//     int ptr = 0;             // 指向下一个要回答的询问
//
//     // ============================================================
//     // 第5步：核心循环 - 增量计算
//     // ============================================================
//     // 从 n=1 到 maxN，依次处理每个 x
//     // 这样每个 x 只被处理一次，所有询问共享计算结果
//     for(int n=1; n<=maxN; n++) {
//
//         // ---------- 5.1 加入 x=n 的贡献 ----------
//         // x=1 没有"除1以外的最小正因子"，所以跳过
//         if(n >= 2) {
//             // p = x 的最小质因子（也就是题目中的 y）
//             int p = spf(n, primes);
//
//             // contribution = x+y = n+p 的因子个数（也就是 z 的个数）
//             int contribution = divisors(n+p, primes);
//
//             // 把这个贡献加到对应的余数分类中
//             // 因为后面回答询问时，需要按 x%77 来取
//             sumResidue[n % 77] += contribution;
//         }
//
//         // ---------- 5.2 回答所有 n 等于当前值的询问 ----------
//         // 可能有多个询问的 n 相同，用 while 一次性全部回答
//         while(ptr < q && qs[ptr].first == n) {
//             ll s = 0;
//
//             // 对于当前 n，所有满足条件的 x 的余数都在 valid[n%77] 中
//             // 把这些余数对应的 sumResidue 累加起来，就是答案
//             for(int r : valid[n % 77]) {
//                 s += sumResidue[r];
//             }
//
//             // 把答案存到对应的原始下标位置
//             out[qs[ptr].second] = s;
//             ptr++;  // 移动到下一个询问
//         }
//     }
//
//     // ============================================================
//     // 第6步：按原始顺序输出答案
//     // ============================================================
//     for(int i=0; i<q; i++) {
//         cout << out[i] << '\n';
//     }
//
//     return 0;
// }