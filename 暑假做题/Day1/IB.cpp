//
// Created by 28447 on 2026/8/13.
//
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<string> a(n);
        unordered_set<string> s;
        for(int i=0;i<n;i++) {
            cin >> a[i];
            if (a[i].size() > 8) a[i].resize(8);
            s.insert(a[i]);
        }
        string ans;
        ans.reserve(n);

        for (const auto &str : a) {
            bool flag = false;
            for (int j=1; j < static_cast<int>(str.size()); j++) {
                string left = str.substr(0, j);
                string right = str.substr(j);
                if (s.find(left) != s.end() && s.find(right) != s.end()) {
                    flag = true;
                    break;
                }
            }
            ans.push_back(flag ? '1' : '0');
        }
        cout << ans << '\n';
    }
    return 0;
}