//
// Created by 28447 on 2026/8/22.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Go(int n) {
    if (n<=1) return 1;
    ll ff=1,fb=1;
    ll fi;
    for (int i=2;i<=n;i++) {
        fi= ff + fb;ff=fb;fb=fi;
    }
    return fi;
}

int main() {
    int n;
    cin>>n;
    cout<<Go(n);
    return 0;
}