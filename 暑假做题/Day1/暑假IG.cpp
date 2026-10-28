//
// Created by 28447 on 2026/8/13.
// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef pair<ll,int> pli;
// const int MAXN=1e5+5;
// const ll INF=4e18;
// int n,m,k;
// vector<pair<int,ll>>g[MAXN];
// ll distence[MAXN];
// int way[MAXN],train_num[MAXN];
//
// void dijkstra() {
//     for (int i=0;i<n;i++) {
//         distence[i]=INF;
//         way[i]=0;
//
//     }
//     //首都
//     distence[1]=0;
//     way[1]=1;
//     //储存
//     priority_queue<pli,vector<pli>,greater<pli>>pq;
//     pq.push(pli(0,1));
//     //dijkstra算法循环
//     while (!pq.empty()) {
//         pli p=pq.top();
//         pq.pop();
//         ll d=p.first;
//         int u = p.second;
//         if (d!=distence[u]) continue;
//         for (auto flag:g[u]) {
//             int v=flag.first;
//             ll w=flag.second;
//             if (distence[v]>distence[u]+w) {
//                 distence[v]=distence[u]+w;
//                 if (u==1){
//                     way[v]=1;
//                 }
//                 else {
//                     way[v]=0;
//                 }
//                 pq.push(pli(distence[v],v));
//             }
//         }
//
//     }
// }
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cin >> n >> m >> k;
//     for (int i=0;i<m;i++) {
//         int u,v,x;
//         cin >> u >> v >> x;
//         g[u].push_back({v,x});
//         g[v].push_back({u,x});
//     }
//     //总线
//     vector<pair<int,ll>>a_train;
//     for (int i=0;i<k;i++) {
//         int s,y;
//     cin >> s >> y;
//     a_train.emplace_back(s,y);
//     g[1].push_back({s,y});
//     g[s].push_back({1,y});
//     train_num[s]++;
//
//     }
//     dijkstra();
//     int cancel=0;
//     for (auto flag:a_train) {
//         int s = flag.first;
//         ll y = flag.second;
//         if (y>distence[s]) cancel++;
//         else if (y==distence[s]) {
//             if (train_num[s]>1||way[s]==0) cancel++;
//         }
//     }
//     cout << cancel << '\n';
//
//     return 0;
// }
//////////////success
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const int MAXN=1e5+5;
const ll INF=4e18;

int n, m, k;
vector<pair<int,ll>> g[MAXN];
ll dist1[MAXN], dist2[MAXN];

void dijkstra(ll dist[]) {
    for(int i = 1; i <= n; i++) dist[i] = INF;
    dist[1] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;

        for(auto [v, w] : g[u]) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    // 保存所有公路
    vector<tuple<int,int,ll>> roads;
    for(int i = 0; i < m; i++) {
        int u, v;
        ll x;
        cin >> u >> v >> x;
        roads.push_back({u, v, x});
    }

    // 保存所有火车路线
    vector<pair<int,ll>> trains;
    for(int i = 0; i < k; i++) {
        int s;
        ll y;
        cin >> s >> y;
        trains.push_back({s, y});
    }

    // 第一次：只加公路
    for(auto [u, v, x] : roads) {
        g[u].push_back({v, x});
        g[v].push_back({u, x});
    }
    dijkstra(dist1);

    // 第二次：加上火车路线
    for(auto [s, y] : trains) {
        g[1].push_back({s, y});
        g[s].push_back({1, y});
    }
    dijkstra(dist2);

    // 判断哪些火车路线可以删除
    int ans = 0;
    for(auto [s, y] : trains) {
        // 如果火车路线不是最短路径的一部分，或者即使没有它也能达到同样距离
        if(y > dist2[s] || dist1[s] <= y) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}