//
// Created by 28447 on 2026/8/20.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct fushu {
    ll x, y;
    fushu(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    fushu operator+(const fushu& o) const {
        return {x + o.x, y + o.y};
    }
    fushu operator-(const fushu& o) const {
        return {x - o.x, y - o.y};
    }
    fushu operator*(const fushu& o) const {
        return {x*o.x - y*o.y, x*o.y + y*o.x};
    }
    ll mo() const {
        return x*x + y*y;
    }
    string out() const {
        if (!x && !y) return "0";
        if (!x) {
            if (y == 1) return "i";
            if (y == -1) return "-i";
            return to_string(y) + "i";
        }
        if (!y) return to_string(x);
        if (y == 1) return to_string(x) + "+i";
        if (y == -1) return to_string(x) + "-i";
        return to_string(x) + (y > 0 ? "+" : "") + to_string(y) + "i";
    }
};
fushu get(string s) {
    if (s == "i") return {0, 1};
    if (s == "-i") return {0, -1};
    if (s.find('+') != -1) {
        int p = s.find('+');
        ll a = stoll(s.substr(0, p));
        string t = s.substr(p+1);
        ll b = (t == "i" ? 1 : stoll(t.substr(0, t.size()-1)));
        return {a, b};
    }
    int pos = s.find('-');
    if (pos != -1) {
        if (pos == 0) {
            pos = s.find('-', 1);
        }
        if (pos != -1) {
            ll a = stoll(s.substr(0, pos));
            string t = s.substr(pos+1);
            ll b;
            if (t == "i") b = -1;
            else if (t == "-i") b = 1;
            else b = -stoll(t.substr(0, t.size()-1));
            return {a, b};
        }
    }
    if (s.back() == 'i') {
        return {0, stoll(s.substr(0, s.size()-1))};
    }
    return {stoll(s), 0};
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<fushu> a(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        a[i] = get(s);
    }
    for (int i = 0; i < n; i++) {
        fushu ans1, ans2, ans3;
        bool f1 = 0, f2 = 0, f3 = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            fushu t1 = a[i] + a[j];
            fushu t2 = a[i] - a[j];
            fushu t3 = a[i] * a[j];
            if (!f1 || t1.mo() > ans1.mo()) {
                ans1 = t1;
                f1 = 1;
            }
            if (!f2 || t2.mo() > ans2.mo()) {
                ans2 = t2;
                f2 = 1;
            }
            if (!f3 || t3.mo() > ans3.mo()) {
                ans3 = t3;
                f3 = 1;
            }
        }
        cout << ans1.out() << ' ' << ans2.out() << ' ' << ans3.out() << '\n';
    }
    return 0;
}