//
// Created by 28447 on 2026/9/2.
//
#include<bits/stdc++.h>
using namespace std;

const int N = 20;

int n = 1;

map<string,bool> vis;  //标记数组

string a[N],b[N],s,t;

void bfs() {
    queue<pair<string,int> > q;
    q.push({s,0});             //将初始状态进队，步数为0

    while(!q.empty()) {
        string now = q.front().first;
        string nown = now;                      //存一下未变换时的初始状态
        int step = q.front().second;
        q.pop();                                //一定要记得删掉！

        if(vis[now]) continue;                  //走过了就continue
        vis[now] = true;

        if(step > 10) continue;                 //超过10步不管走没走到直接continue
        if(now == t) {                          //走到了，输出当前步数（bfs首解最优）
            cout << step;
            return;
        }
        ///关键
        for(int i = 1;i<=n;i++) {
            now = nown;                         //每次尝试能否变换为新的字符串前前需要重置当前字符串
            while(true) {
                int p = now.find(a[i]);//返回位置
                if(p == -1) break;              //找不到就break
                string str = nown;
                str.replace(p,a[i].size(),b[i]);//替换从地p位到a[i]
                q.push({str,step+1});           //新状态入队
                now[p] = ' ';                   //将已经变换的位换成其他字符
            }
        }
    }
    cout << "NO ANSWER!";                       //s变换不到t，输出无解
}

int main() {
    cin >> s >> t;
    while(cin >> a[n] >> b[n]) n++;
    n--;
    if(n == 0 && s != t) {             //特判，如果没有可以变换的方案，并且两个字符串不相等，输出无解
        cout << "NO ANSWER!";
        return 0;
    }
    bfs();
    return 0;
}
