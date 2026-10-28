//
// Created by 28447 on 2026/8/20.
#include <bits/stdc++.h>
using namespace std;

#define ll long long

// 复数结构体
struct Complex {
    ll real;      // 实部
    ll imag;      // 虚部

    // 构造函数
    Complex(ll _real = 0, ll _imag = 0) : real(_real), imag(_imag) {}

    // 重载加法运算符
    Complex operator+(const Complex& other) const {
        return {real + other.real, imag + other.imag};
    }

    // 重载减法运算符
    Complex operator-(const Complex& other) const {
        return {real - other.real, imag - other.imag};
    }

    // 重载乘法运算符
    Complex operator*(const Complex& other) const {
        return {
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        };
    }

    // 计算模长的平方（用于比较大小）
    ll normSq() const {
        return real * real + imag * imag;
    }

    // 将复数转换为题目要求的输出格式
    string toString() const {
        // 情况1：实部和虚部都是0
        if (real == 0 && imag == 0) return "0";

        // 情况2：实部为0，只有虚部
        if (real == 0) {
            if (imag == 1) return "i";
            if (imag == -1) return "-i";
            return to_string(imag) + "i";
        }

        // 情况3：虚部为0，只有实部
        if (imag == 0) return to_string(real);

        // 情况4：虚部为±1的特殊格式
        if (imag == 1) return to_string(real) + "+i";
        if (imag == -1) return to_string(real) + "-i";

        // 情况5：一般情况
        if (imag > 0) {
            return to_string(real) + "+" + to_string(imag) + "i";
        } else {
            return to_string(real) + to_string(imag) + "i";
        }
    }
};

// 解析输入字符串为复数
Complex parseComplex(const string& str) {
    // 处理纯虚数 ±i
    if (str == "i") return {0, 1};
    if (str == "-i") return {0, -1};

    // 处理 a+bi 格式（中间有加号）
    if (str.find('+') != string::npos) {
        int pos = str.find('+');
        ll real = stoll(str.substr(0, pos));
        string imagPart = str.substr(pos + 1);
        ll imag;
        if (imagPart == "i") {
            imag = 1;
        } else {
            imag = stoll(imagPart.substr(0, imagPart.size() - 1));
        }
        return {real, imag};
    }

    // 处理 a-bi 格式（中间有减号）
    int pos = str.find('-');
    if (pos != string::npos) {
        // 如果第一个字符就是负号，说明实部是负数，要找第二个负号
        if (pos == 0) {
            pos = str.find('-', 1);
        }
        // 如果找到了第二个负号
        if (pos != string::npos) {
            ll real = stoll(str.substr(0, pos));
            string imagPart = str.substr(pos + 1);
            ll imag;
            if (imagPart == "i") {
                imag = -1;
            } else if (imagPart == "-i") {
                imag = 1;
            } else {
                imag = -stoll(imagPart.substr(0, imagPart.size() - 1));
            }
            return {real, imag};
        }
    }

    // 处理纯虚数 bi（没有实部）
    if (str.back() == 'i') {
        ll imag = stoll(str.substr(0, str.size() - 1));
        return {0, imag};
    }

    // 处理纯实数（没有虚部）
    return {stoll(str), 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<Complex> numbers(n);
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        numbers[i] = parseComplex(input);
    }

    // 对每个复数进行处理
    for (int i = 0; i < n; i++) {
        Complex bestAdd, bestSub, bestMul;
        bool initAdd = false, initSub = false, initMul = false;

        // 遍历其他所有复数
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            // 计算加法、减法、乘法的结果
            Complex resultAdd = numbers[i] + numbers[j];
            Complex resultSub = numbers[i] - numbers[j];
            Complex resultMul = numbers[i] * numbers[j];

            // 更新加法最大值
            if (!initAdd || resultAdd.normSq() > bestAdd.normSq()) {
                bestAdd = resultAdd;
                initAdd = true;
            }

            // 更新减法最大值
            if (!initSub || resultSub.normSq() > bestSub.normSq()) {
                bestSub = resultSub;
                initSub = true;
            }

            // 更新乘法最大值
            if (!initMul || resultMul.normSq() > bestMul.normSq()) {
                bestMul = resultMul;
                initMul = true;
            }
        }

        // 输出结果：加法、减法、乘法的最大值
        cout << bestAdd.toString() << ' '
             << bestSub.toString() << ' '
             << bestMul.toString() << '\n';
    }

    return 0;
}
// #include <bits/stdc++.h>
// using namespace std;
// #define ll long long
// struct Complex {
//     ll a, b;
//     Complex(ll _a = 0, ll _b = 0) : a(_a), b(_b) {}
//
//     Complex operator+(const Complex& o) const { return {a + o.a, b + o.b}; }
//     Complex operator-(const Complex& o) const { return {a - o.a, b - o.b}; }
//     Complex operator*(const Complex& o) const { return {a*o.a - b*o.b, a*o.b + b*o.a}; }
//     ll norm() const { return a*a + b*b; }
//
//     string str() const {
//         if (!a && !b) return "0";
//         if (!a) return (b == 1 ? "i" : b == -1 ? "-i" : to_string(b) + "i");
//         if (!b) return to_string(a);
//         if (b == 1) return to_string(a) + "+i";
//         if (b == -1) return to_string(a) + "-i";
//         return to_string(a) + (b > 0 ? "+" : "") + to_string(b) + "i";
//     }
// };
//
// Complex parse(const string& s) {
//     if (s == "i") return {0, 1};
//     if (s == "-i") return {0, -1};
//     if (s.find('+') != -1) {
//         int p = s.find('+');
//         ll a = stoll(s.substr(0, p));
//         string t = s.substr(p+1);
//         ll b = (t == "i" ? 1 : stoll(t.substr(0, t.size()-1)));
//         return {a, b};
//     }
//     if (s.find('-') != -1 && s[0] != '-') {
//         int p = s.find('-');
//         ll a = stoll(s.substr(0, p));
//         string t = s.substr(p+1);
//         ll b = (t == "i" ? -1 : -stoll(t.substr(0, t.size()-1)));
//         return {a, b};
//     }
//     if (s.back() == 'i') return {0, stoll(s.substr(0, s.size()-1))};
//     return {stoll(s), 0};
// }
//
// int main() {
//     ios::sync_with_stdio(0), cin.tie(0);
//     int n; cin >> n;
//     vector<Complex> v(n);
//     for (int i = 0; i < n; i++) { string s; cin >> s; v[i] = parse(s); }
//
//     for (int i = 0; i < n; i++) {
//         Complex add, sub, mul;
//         bool fa = 0, fs = 0, fm = 0;
//         for (int j = 0; j < n; j++) if (i != j) {
//             Complex ca = v[i] + v[j], cs = v[i] - v[j], cm = v[i] * v[j];
//             if (!fa || ca.norm() > add.norm()) add = ca, fa = 1;
//             if (!fs || cs.norm() > sub.norm()) sub = cs, fs = 1;
//             if (!fm || cm.norm() > mul.norm()) mul = cm, fm = 1;
//         }
//         cout << add.str() << ' ' << sub.str() << ' ' << mul.str() << '\n';
//     }
// }
// #include <bits/stdc++.h>
// using namespace std;
//
// using C = complex<long long>;
//
// C parse(const string& s) {
//     size_t p = s.find('i');
//     if (p == string::npos) return C(stoll(s), 0);
//
//     string t = s.substr(0, p); // 去掉末尾的 i
//     if (t.empty()) return C(0, 1);
//     if (t == "-") return C(0, -1);
//
//     size_t q = t.find_first_of("+-", 1);
//     if (q == string::npos) return C(0, stoll(t)); // 纯虚数
//
//     long long a = stoll(t.substr(0, q));
//     string u = t.substr(q);
//     long long b;
//     if (u == "+") b = 1;
//     else if (u == "-") b = -1;
//     else b = stoll(u);
//
//     return C(a, b);
// }
//
// string str(const C& z) {
//     long long a = z.real(), b = z.imag();
//
//     if (a == 0 && b == 0) return "0";
//     if (a == 0) {
//         if (b == 1) return "i";
//         if (b == -1) return "-i";
//         return to_string(b) + "i";
//     }
//     if (b == 0) return to_string(a);
//     if (b == 1) return to_string(a) + "+i";
//     if (b == -1) return to_string(a) + "-i";
//
//     return to_string(a) + (b > 0 ? "+" : "") + to_string(b) + "i";
// }
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int n;
//     cin >> n;
//
//     vector<C> v(n);
//     for (int i = 0; i < n; ++i) {
//         string s;
//         cin >> s;
//         v[i] = parse(s);
//     }
//
//     // 乘法：维护最大和次大模长
//     long long mx1 = -1, mx2 = -1;
//     int id1 = -1, id2 = -1;
//
//     for (int i = 0; i < n; ++i) {
//         long long x = norm(v[i]);
//         if (x > mx1) {
//             mx2 = mx1;
//             id2 = id1;
//             mx1 = x;
//             id1 = i;
//         } else if (x > mx2) {
//             mx2 = x;
//             id2 = i;
//         }
//     }
//
//     vector<C> add(n), sub(n);
//     vector<long long> bestAdd(n, -1), bestSub(n, -1);
//
//     // 加法/减法：只枚举 i < j，同时更新两个位置
//     for (int i = 0; i < n; ++i) {
//         for (int j = i + 1; j < n; ++j) {
//             C a = v[i] + v[j];
//             long long an = norm(a);
//
//             if (an > bestAdd[i]) {
//                 bestAdd[i] = an;
//                 add[i] = a;
//             }
//             if (an > bestAdd[j]) {
//                 bestAdd[j] = an;
//                 add[j] = a;
//             }
//
//             C d = v[i] - v[j];
//             long long dn = norm(d);
//
//             if (dn > bestSub[i]) {
//                 bestSub[i] = dn;
//                 sub[i] = d;
//             }
//
//             C nd(-d.real(), -d.imag()); // v[j] - v[i]
//             if (dn > bestSub[j]) {
//                 bestSub[j] = dn;
//                 sub[j] = nd;
//             }
//         }
//     }
//
//     for (int i = 0; i < n; ++i) {
//         C mul(0, 0);
//
//         if (n > 1) {
//             int j = (i == id1 ? id2 : id1);
//             mul = v[i] * v[j];
//         }
//
//         cout << str(add[i]) << ' ' << str(sub[i]) << ' ' << str(mul) << '\n';
//     }
//
//     return 0;
// }
