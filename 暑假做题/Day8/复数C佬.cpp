//
// Created by 28447 on 2026/8/26.
//
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using Real = double;

struct Cp {
    i64 x = 0, y = 0;

    constexpr Cp operator + (Cp o) const { return {x+o.x, y+o.y}; }
    constexpr Cp operator - (Cp o) const { return {x-o.x, y-o.y}; }
    constexpr Cp operator * (Cp o) const { return {x*o.x-y*o.y, x*o.y+y*o.x}; }

    friend istream& operator >> (istream &is, Cp &a) {
        string s;
        is >> s;

        if (s.empty()) return is;

        // 处理纯实数
        if (s.find('i') == string::npos) {
            a.x = stoll(s);
            a.y = 0;
            return is;
        }

        // 处理纯虚数
        if (s == "i") { a.x = 0; a.y = 1; return is; }
        if (s == "-i") { a.x = 0; a.y = -1; return is; }
        if (s == "+i") { a.x = 0; a.y = 1; return is; }

        // 处理一般形式
        int plusPos = s.find('+', 1);
        int minusPos = s.find('-', 1);
        int splitPos = -1;

        if (plusPos != string::npos) splitPos = plusPos;
        else if (minusPos != string::npos) splitPos = minusPos;

        if (splitPos != -1) {
            // 有实部和虚部
            string realPart = s.substr(0, splitPos);
            string imagPart = s.substr(splitPos);

            if (!realPart.empty() && realPart != "+" && realPart != "-") {
                a.x = stoll(realPart);
            }

            // 处理虚部
            if (imagPart == "i") a.y = 1;
            else if (imagPart == "+i") a.y = 1;
            else if (imagPart == "-i") a.y = -1;
            else {
                string num = imagPart;
                if (num.back() == 'i') num.pop_back();
                if (num == "+") a.y = 1;
                else if (num == "-") a.y = -1;
                else a.y = stoll(num);
            }
        } else {
            // 只有虚部
            string imagPart = s;
            if (imagPart.back() == 'i') imagPart.pop_back();
            if (imagPart == "" || imagPart == "+") a.y = 1;
            else if (imagPart == "-") a.y = -1;
            else a.y = stoll(imagPart);
        }

        return is;
    }

    friend ostream& operator << (ostream &os, const Cp &a) {
        if (a.x != 0 || a.y == 0) {
            os << a.x;
            if (a.y > 0) os << '+';
        }
        if (a.y != 0) {
            if (a.y == -1) os << '-';
            else if (a.y != 1) os << a.y;
            os << 'i';
        }
        if (a.x == 0 && a.y == 0) os << '0';
        return os;
    }

    constexpr Real sq() const { return Real(x)*x + Real(y)*y; }

    // 比较函数：基于模的平方
    friend bool operator < (const Cp &u, const Cp &v) {
        return u.sq() < v.sq();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Cp> a(n);
    for (auto &x : a) cin >> x;

    for (int i = 0; i < n; i++) {
        array<Cp, 3> r{};  // 初始化为 {0,0,0}

        for (int j = 0; j < n; j++) {
            if (i != j) {
                array<Cp, 3> t = {a[i] + a[j], a[i] - a[j], a[i] * a[j]};
                for (int k = 0; k < 3; k++) {
                    if (r[k] < t[k]) r[k] = t[k];  // 取最大值
                }
            }
        }

        for (int j = 0; j < 3; j++) {
            cout << r[j] << (j == 2 ? '\n' : ' ');
        }
    }

    return 0;
}