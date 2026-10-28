//
// Created by 28447 on 2026/8/13.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    //
    while(t--) {
        int n;
        cin >> n;
        string v;
        cin >> v;

        int bal=0;
        unordered_set<char> seen;
        for (char c:v) {
            if (seen.count(c)) {
                bal++;
            }
            else {
                bal+=2;
                seen.insert(c);
            }

        }
        cout<<bal<<endl;

    }
    return 0;
}