//
// Created by 28447 on 2026/8/22.
//
#include <iostream>
using namespace std;
#define ll long long
ll tail(ll n, ll a = 1) {
    if (n <= 1) return a;
    return tail(n - 1, n * a);
}
ll use(int n) {
    if (n < 0) return -1;
    return tail(n);
}
int main() {
    int n;
    cin>>n;
    cout<<use(n)<<endl;
    return 0;
}