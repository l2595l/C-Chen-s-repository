//
// Created by 28447 on 2026/8/14.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        pq.push({a,b});
    }
    ll ans = 0;
    int need= n;
    while (!pq.empty()) {
        auto[a,b]= pq.top();
        pq.pop();
        int buy=min(need,b);
        ans+=(ll)buy*a;
        need-=buy;
    }
    cout << ans << endl;
    return 0;
}