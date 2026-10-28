```c++
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// /**
//  * 构建部分匹配表（前缀函数/next数组）
//  *
//  * 核心思想：对于模式串的每个位置i，计算pattern[0..i]这个子串中，
//  * 最长的相等真前缀和真后缀的长度。
//  *
//  * 例如：pattern = "ABABCABAB"
//  * pi[0] = 0  ("A"没有真前后缀)
//  * pi[1] = 0  ("AB"没有相等的真前后缀)
//  * pi[2] = 1  ("ABA"中"A"是相等的前后缀)
//  * pi[3] = 2  ("ABAB"中"AB"是相等的前后缀)
//  * pi[4] = 0  ("ABABC"没有相等的真前后缀)
//  *
//  * @param pattern 要匹配的模式串
//  * @return 前缀表数组，pi[i]表示以i结尾的子串的最长相等前后缀长度
//  */
vector<int> buildPrefix(const string& pattern) {
    int m = pattern.size();           // 模式串长度
    vector<int> pi(m, 0);             // 初始化前缀表，所有位置默认为0

    // i从1开始，因为pi[0]始终为0（单个字符没有真前后缀）
    for (int i = 1; i < m; i++) {
        // j表示前一个位置的最长相等前后缀长度
        // 也是我们要尝试匹配的前缀的最后一个字符的下一个位置
        int j = pi[i - 1];

        // 关键步骤：当不匹配时，利用已经计算好的前缀表进行回退
        // 为什么回退到pi[j-1]？
        // 因为pattern[0..j-1]已经和pattern[i-j..i-1]匹配，
        // 而pattern[0..pi[j-1]-1]是pattern[0..j-1]的最长相等真前缀，
        // 这个前缀也是pattern[i-j..i-1]的后缀，所以可以继续尝试匹配
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

/**
 * KMP字符串匹配算法
 *
 * 算法思路：
 * 1. 利用前缀表避免文本指针的回退
 * 2. 当匹配失败时，模式串指针根据前缀表回退到合适位置
 * 3. 时间复杂度O(n+m)，远优于暴力匹配的O(n*m)
 *
 * @param text 要在其中搜索的文本串
 * @param pattern 要查找的模式串
 * @return 所有匹配位置的起始索引（从0开始）
 */
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

            // 继续寻找下一个匹配
            // 回退模式串指针，利用已经匹配的部分信息
            // 注意：这里不是回退到0，而是利用前缀表
            j = pi[j - 1];
        }
    }
    return result;
}

/**
 * 主函数 - 演示KMP算法的使用
 */
int main() {
    // 测试数据
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    // 执行KMP搜索
    vector<int> matches = kmpSearch(text, pattern);

    // 输出结果
    cout << "文本: " << text << endl;
    cout << "模式: " << pattern << endl;
    cout << "匹配位置: ";
    for (int pos : matches) {
        cout << pos << " ";
    }
    cout << endl;

    // 输出前缀表，帮助理解匹配过程
    vector<int> pi = buildPrefix(pattern);
    cout << "前缀表: ";
    for (int v : pi) {
        cout << v << " ";
    }
    cout << endl;

    // 附加说明：手动验证匹配过程
    cout << "\n匹配过程说明：" << endl;
    cout << "模式串: ";
    for (char c : pattern) cout << c << " ";
    cout << endl;
    cout << "前缀表: ";
    for (int v : pi) cout << v << " ";
    cout << endl;
    cout << "在文本中成功匹配到模式串" << endl;

    return 0;
}
```