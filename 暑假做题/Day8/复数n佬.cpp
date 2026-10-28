//
// Created by 28447 on 2026/8/26.
//
#include <bits/stdc++.h>
using namespace std;

long long read() {
    long long f = 1, s = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = (s << 1) + (s << 3) + ch - '0';
        ch = getchar();
    }
    return s * f;
}

struct fushu {
    long long shi, xu;

    fushu() : shi(0), xu(0) {}
    fushu(long long a, long long b) : shi(a), xu(b) {}

    __int128 mo() const {
        return (__int128)shi * shi + (__int128)xu * xu;
    }

    fushu operator+(const fushu &a) const {
        return fushu(shi + a.shi, xu + a.xu);
    }
    fushu operator-(const fushu &a) const {
        return fushu(shi - a.shi, xu - a.xu);
    }
    fushu operator*(const fushu &a) const {
        return fushu(shi * a.shi - xu * a.xu, shi * a.xu + xu * a.shi);
    }

    bool operator>(const fushu &a) const {
        return mo() > a.mo();
    }
    bool operator<(const fushu &a) const {
        return mo() < a.mo();
    }
    bool operator==(const fushu &a) const {
        return shi == a.shi && xu == a.xu;
    }

    // 简化输入：直接读两个整数
    friend istream& operator>>(istream &is, fushu &a) {
        string s;
        is >> s;

        // 简化：只处理 a+bi 格式
        size_t pos = s.find('+');
        if (pos == string::npos) pos = s.find('-', 1);

        if (pos != string::npos) {
            a.shi = stoll(s.substr(0, pos));
            string imag = s.substr(pos);
            if (imag == "i") a.xu = 1;
            else if (imag == "-i") a.xu = -1;
            else {
                imag.pop_back();  // 去掉 'i'
                a.xu = stoll(imag);
            }
        } else {
            if (s.back() == 'i') {
                a.shi = 0;
                s.pop_back();
                if (s.empty() || s == "+") a.xu = 1;
                else if (s == "-") a.xu = -1;
                else a.xu = stoll(s);
            } else {
                a.shi = stoll(s);
                a.xu = 0;
            }
        }
        return is;
    }
};

void print_fushu(const fushu &a) {
    if (a.shi == 0 && a.xu == 0) {
        cout << "0";
    } else if (a.xu == 0) {
        cout << a.shi;
    } else if (a.shi == 0) {
        if (abs(a.xu) != 1) cout << a.xu << "i";
        else if (a.xu == 1) cout << "i";
        else cout << "-i";
    } else {
        cout << a.shi;
        if (abs(a.xu) == 1) {
            cout << (a.xu == 1 ? "+i" : "-i");
        } else {
            cout << (a.xu > 0 ? "+" : "") << a.xu << "i";
        }
    }
}

fushu d[2005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    for (int i = 1; i <= n; i++) {
        // 初始化
        fushu bestadd, bestsub, bestmul;
        bool first = true;

        for (int j = 1; j <= n; j++) {
            if (i == j) continue;

            fushu add = d[i] + d[j];
            fushu sub = d[i] - d[j];
            fushu mul = d[i] * d[j];

            if (first || add > bestadd) bestadd = add;
            if (first || sub > bestsub) bestsub = sub;
            if (first || mul > bestmul) bestmul = mul;
            first = false;
        }

        // 如果 n=1，输出 0 0 0
        if (first) {
            cout << "0 0 0\n";
            continue;
        }

        print_fushu(bestadd);
        cout << " ";
        print_fushu(bestsub);
        cout << " ";
        print_fushu(bestmul);
        cout << "\n";
    }

    return 0;
}