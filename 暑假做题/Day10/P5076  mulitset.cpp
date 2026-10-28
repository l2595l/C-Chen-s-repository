//
// Created by 28447 on 2026/8/22.
//
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;
multiset<int>q;
int n,t,x,order;
int main()
{
    q.insert(-0x7fffffff);
    q.insert(0x7fffffff);
    //提前放入这两个数，避免错误
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d",&t,&x);
        if(t==1)
        {
            auto it=q.lower_bound(x);
            //auto是自动判断数据类型，只有C++14以上才支持
            //可以写作multiset<int>::iterator，因为lower_bound方法返回的是迭代器
            // it 取得 x 的位置

            order=0;
            //order为排名

            for(auto i=q.begin();i!=it;i++,order++);
            //这里的auto同理，也是迭代器
            //这里就处理出了x的排名——order

            printf("%d\n",order);
            //输出order即为答案
        }
        else if(t==2)
        {
            order=-1;
            //初值为-1是因为前面有一个-0x7fffffff，所以order要多跑一步

            for(int i:q)
                if(++order==x)
                //缩写，order先自增一，再判断是否与x相等
                //如果是(order++==x)，那就是先判断再自增，这里要尤其注意
                    printf("%d\n",i);
                //i就是容器里的值，输出i

            //注意这里的for(:)循环，是只有C++11以上才支持的
            //和auto一样，都是noip不能用的
            //这种循环，i就是容器里的值而不是下标
            //也可以使用迭代器循环，上面的循环等价于
            /*
                for(multiset<int>::iterator it=q.begin();it!=q.end();it++)
                {
                    order++;
                    if(order==x)
                        printf("%d\n",*it);
                }
            */
            //这种循环是noip可以使用的
        }
        else if(t==3)
        {
            auto it=q.lower_bound(x);
            //取得第一个大于等于x的值
            //也就是第一个x的位置
            //由于我们要取得前驱，所以it要自减一
            printf("%d\n",*--it);
            //这句是先自减，再输出，是缩写
            //等价于：
            /*
                it--;
                printf("%d\n",*it);
            */
            //因为是迭代器（指针），所以输出前面加 *
        }
        else if(t==4)
        {
            printf("%d\n",*q.upper_bound(x));
            //要取得后继，就是第一个大于x的值
            //用upper_bound方法取得第一个大于x的迭代器
            //输出即可
            //因为是迭代器（指针），所以输出前面加 *
        }
        else
        {
            q.insert(x);
            //直接添加即可
        }
    }
    return 0;
}
