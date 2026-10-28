//
// Created by 28447 on 2026/8/17.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> buildPrefix(const string& pattern) {
    int m = pattern.size();           // 模式串长度
    vector<int> pi(m, 0);             // 初始化前缀表，所有位置默认为0

    // i从1开始，因为pi[0]始终为0（单个字符没有真前后缀）
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];  // 回退到更短的相等前后缀
        }
        // 如果当前字符匹配成功，可以扩展前缀长度
        if (pattern[i] == pattern[j]) {
            j++;  // 相等前后缀长度+1
        }
        // 存储当前位置的最长相等前后缀长度
        pi[i] = j;
    }
    return pi;
}
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> result;  // 存储所有匹配位置的索引

    // 如果模式串为空，直接返回空结果
    if (pattern.empty()) return result;

    // 第一步：构建模式串的前缀表
    vector<int> pi = buildPrefix(pattern);

    int n = text.size();     // 文本串长度
    int m = pattern.size();  // 模式串长度
    int j = 0;               // j表示当前已匹配的模式串字符数（也是下一个要匹配的模式串位置）

    // 遍历文本串的每个字符
    for (int i = 0; i < n; i++) {
        // 当字符不匹配时，利用前缀表回退模式串指针
        // 注意：这里不会回退文本指针i，这是KMP高效的关键
        while (j > 0 && text[i] != pattern[j]) {
            // 回退到前一个位置的最长相等前后缀长度
            // 这样可以充分利用已经匹配的信息
            j = pi[j - 1];
        }

        // 如果当前字符匹配，继续匹配下一个字符
        if (text[i] == pattern[j]) {
            j++;  // 已匹配长度+1
        }

        // 如果完全匹配了一个模式串
        if (j == m) {
            // 记录匹配的起始位置：当前文本位置 - 模式串长度 + 1
            result.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return result;
}
int main() {
    // 1. 加上输入加速（可选，但推荐）
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text, pattern;
    cin >> text >> pattern;

    // 执行KMP搜索
    vector<int> matches = kmpSearch(text, pattern);

    // 2. 修复：匹配位置必须每行输出一个
    for (int pos : matches) {
        cout << pos + 1 << "\n";
    }

    // 3. 修复：输出前缀表
    vector<int> pi = buildPrefix(pattern);
    // 注意：题目要求最后一个整数后面不能有多余空格（有些OJ会卡这个，虽然P3375一般不卡）
    for (int i = 0; i < pi.size(); i++) {
        if (i > 0) cout << " ";
        cout << pi[i];
    }
    cout << "\n"; // 最后换行

    return 0;
}