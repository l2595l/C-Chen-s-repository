//
// Created by 28447 on 2026/8/14.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1e5+7;
const int M= 1e5+5;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while (t--) {
        ll val=0;
        int n;
        string s;
        cin>>n>>s;
        vector<ll>Tol;
        //判断翻转后收益+加入
        for (int k=0;k<n;k++) {
            int left=k;
            int right=n-1-k;
            if (s[k]=='L') {
                val+=left;//累计
                ll tol=right-left;
                if (tol>0)Tol.push_back(tol);

            }
            else {
                val+=right;//累计
                ll tol=left-right;
                if (tol>0)Tol.push_back(tol);
            }
        }
        //排
        sort(Tol.begin(), Tol.end(),greater<ll>());
        ll c=val;
        //vector<ll> ans;

        for (int k=0;k<n;k++) {
            if (k<Tol.size()) c+=Tol[k];
            cout<<c<<(k==n?"\n":" ");
        }

    }
    return 0;
}