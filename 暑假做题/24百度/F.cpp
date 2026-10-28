//
// Created by 28447 on 2026/9/9.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        vector<int> arr;
        for (int i = n;i > m;i--) {
            arr.push_back(i);
        }
        for (int i=1;i<=m;i++) {
            arr.push_back(i);
        }
        for (int i=0;i<arr.size();i++) {
            cout<<arr[i]<<" ";
        }
        cout<<'\n';
    }
}