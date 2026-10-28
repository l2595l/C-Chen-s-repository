//
// Created by 28447 on 2026/9/29.
//
// #include<map>
// #include<cmath>
// #include<stack>
// #include<cstdio>
// #include<vector>
// #include<cstring>
// #include<iostream>
// #include<algorithm>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
map<string,int>a; //map定义，相当于数组的升级版，表示string到int的映射，举个简单例子，可以用a["OK"]=1;进行赋值（说白了就是括号里的数据类型是map<>前面的，=的后面就是map<>后面的数据类型）
string s;//用于读入的字符串
int n,m;
int main(){
    cin>>n;
    while(n--){//因为是n+m就可以了，所以直接n--，--QWQ
        cin>>s;
        a[s]=1;//直接这样赋值
    }
    cin>>m;
    while(m--){
        cin>>s;
        if(a[s]==1){puts("OK");a[s]=2;}//前面讲的很清楚，不赘述了
        else if(a[s]==2)puts("REPEAT");//输出
        else puts("WRONG");
    }
    return 0;//完美的过程，不是吗？
}

