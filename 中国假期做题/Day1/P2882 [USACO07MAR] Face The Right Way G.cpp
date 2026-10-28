//
// Created by 28447 on 2026/9/22.
//
//#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 10009;
int n;

// A[i] 存原始状态：0 表示 'B'，1 表示 'F'
bool A[maxn];

// B[i] 是异或差分数组，用来记录翻转区间的结束位置
bool B[maxn];

int main(){
    scanf("%d", &n);

    char ch;
    for(int i = 1; i <= n; ++i){
        cin >> ch;
        // 把字符转成 0/1
        // 'B' -> 0
        // 'F' -> 1
        A[i] = (ch == 'B' ? 0 : 1);
    }

    int mincnt = 0x7fffffff; // 最少翻转次数
    int anslen;              // 对应的翻转长度

    // 枚举每一种可能的翻转长度 len
    for(int len = 1; len <= n; ++len){

        // 每次换 len，都要重新初始化差分数组 B
        memset(B, 0, sizeof B);

        bool b = 0;        // b 是当前累计翻转状态，相当于前缀异或和
        bool flag = 1;     // flag 记录当前 len 是否有解
        int cnt = 0;       // 当前 len 下的翻转次数

        for(int i = 1; i <= n; ++i){

            // 第 1 步：前缀异或
            // 等价于普通差分里的 cur += diff[i]
            // 作用：把 B 里的端点标记展开成当前位置的翻转状态
            b ^= B[i];

            // 第 2 步：判断当前位置实际方向是否为 0
            // 实际方向 = A[i] ^ b
            // 如果实际方向是 0，就需要翻转
            if(!(A[i] ^ b)){

                // 如果从 i 开始翻转长度为 len 的区间，会超出 n，则当前 len 无解
                if(i + len - 1 > n){
                    flag = 0;
                    break;
                }

                // 第 3 步：从当前位置开始翻转
                // 等价于普通差分里的 diff[i] += 1
                // 因为只看奇偶，所以 +1 写成 ^= 1
                b ^= 1;

                // 第 4 步：在 i+len 位置打结束标记
                // 等价于普通差分里的 diff[i+len] -= 1
                // 模 2 下 -1 和 +1 一样，所以也写成 ^= 1
                B[i + len] ^= 1;

                // 翻转次数加一
                ++cnt;
            }
        }

        // 如果当前 len 有解，更新最少翻转次数和对应长度
        if(flag){
            if(cnt < mincnt){
                mincnt = cnt;
                anslen = len;
            }
        }
    }

    printf("%d %d\n", anslen, mincnt);
    return 0;
}
// #include<iostream>
// #include<cstdio>
// #include<cstring>
// using namespace std;
// const int maxn = 10009;
// int n;
// bool A[maxn],B[maxn];
// int main(){
//     scanf("%d",&n);
//     char ch;
//     for(int i=1;i<=n;++i){
//         cin>>ch;A[i]=ch=='B'?0:1;
//     }
//     int mincnt=0x7fffffff,anslen;
//     for(int len=1;len<=n;++len){
//         memset(B,0,sizeof B);
//         bool b=0,flag=1;int cnt=0;
//         for(int i=1;i<=n;++i){//因为区间翻转只有状态0和1，所以用^代替+和-//^异或符号
//             b^=B[i];
//             if(!(A[i]^b)){
//                 if(i+len-1>n){flag=0;break;}
//                 b^=1,B[i+len]^=1;
//                 ++cnt;
//             }
//         }
//         if(flag){if(cnt<mincnt)mincnt=cnt,anslen=len;}
//     }printf("%d %d\n",anslen, mincnt);
// }
