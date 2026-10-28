//
// Created by 28447 on 2026/8/22.
//
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string TtT(int n) {
    if (n == 0) return "0";
    if (n == 1) return "";
    vector<int> v;
    for (int i = 0; n >> i; i++) {
        if ((n >> i) & 1) v.push_back(i);
    }
    reverse(v.begin(), v.end());
    string result;
    for (int i = 0; i < v.size(); i++) {
        if (i > 0) result += "+";
        if (v[i] == 0) {
            result += "2(0)";
        } else if (v[i] == 1) {
            result += "2";
        } else {
            result += "2(" + TtT(v[i]) + ")";
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << TtT(n) << endl;
    return 0;
}