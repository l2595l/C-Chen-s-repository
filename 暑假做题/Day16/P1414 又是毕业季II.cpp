//
// Created by 28447 on 2026/8/29.
//
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int n, t = 0, c[1000010];
// c[d] 表示数字d作为因子在所有人的能力值中出现的总次数
// 例如：如果c[3]=5，表示有5个人的能力值都能被3整除

int main() {
    cin >> n;

    // 第一阶段：统计每个因子出现的次数
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        t = max(t, x);  // 记录所有能力值中的最大值，用于后续输出

        int m = sqrt(x);  // 只需要枚举到sqrt(x)即可找到所有因子

        for(int j = 1; j <= m; j++) {  // j从1到sqrt(x)
            if(x % j == 0) {  // 如果j是x的因子
                c[j]++;  // j作为因子出现次数+1
                // 注意：x/j也是x的因子
                // 但要避免重复计数：当x是完全平方数时，j*j==x
                if(x != j * j) c[x / j]++;
                // 例如x=12, j=3时，3和4都是因子
                // 例如x=16, j=4时，4是平方根，只计数一次
            }
        }
    }

    // 第二阶段：从大到小找出每个k对应的最大默契值
    int x = t;  // x从最大值开始向下查找

    for(int i = 1; i <= n; i++) {
        // 核心逻辑：c[x]表示有多少个人的能力值能被x整除
        // 如果c[x] < i，说明没有足够的人（至少i人）都能被x整除
        // 所以需要减小x，直到找到满足条件的最大x
        while(c[x] < i) x--;
        // 当while循环结束时，c[x] >= i
        // 即至少有i个人的能力值能被x整除
        // 所以x就是k=i时的最大默契值

        cout << x << endl;  // 输出第i行的答案
    }

    return 0;
}