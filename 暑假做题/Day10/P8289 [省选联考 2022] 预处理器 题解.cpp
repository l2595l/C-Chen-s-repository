//
// Created by 28447 on 2026/8/22.
//
// 洛谷 P8289 [省选联考 2022] 预处理器
// 模拟 #define / #undef 的宏展开：递归展开 + 用标记防止互相引用死循环
//
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> val;    // 宏名 -> 展开内容
unordered_map<string, bool> in;       // 该宏是否正在展开（防止死循环）

// 是否为标识符字符：字母 / 数字 / 下划线
inline bool isid(char c) {
    return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z') || c == '_';
}

// 递归展开字符串 s 中的所有宏
string expand(string s) {
    string r;
    for (int i = 0; i < (int)s.size();) {
        if (!isid(s[i])) {                 // 非标识符：原样保留
            r += s[i++];
            continue;
        }
        int j = i;
        while (j < (int)s.size() && isid(s[j])) j++;   // 截取一个完整标识符
        string id = s.substr(i, j - i);//substr截取
        i = j;

        if (val.count(id) && !in[id]) {    // 已定义且未处于展开中
            in[id] = true;                 // 标记展开中，避免死循环
            r += expand(val[id]);          // 递归展开内容
            in[id] = false;
        } else {                           // 未定义或正在展开：原样保留
            r += id;
        }
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string line;
    getline(cin, line);                    // 吃掉 n 之后残留的换行符

    while (n--) {
        getline(cin, line);

        if (line[0] != '#') {              // 普通文本：直接展开并输出
            cout << expand(line) << '\n';
            continue;
        }

        // 预处理命令 #define / #undef
        stringstream ss(line.substr(1));
        string op, name, content;
        ss >> op >> name;

        if (op == "define") {
            getline(ss >> ws, content);    // >> ws 先跳过前导空格
            val[name] = content;
        } else {                           // #undef
            val.erase(name);
        }
        cout << '\n';                      // 预处理命令输出空行
    }
    return 0;
}
