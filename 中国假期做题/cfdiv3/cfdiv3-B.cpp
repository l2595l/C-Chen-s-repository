//
// Created by 28447 on 2026/10/9.
//
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        scanf("%d", &n);
        static char s[200005];
        scanf("%s", s);

        vector<char> printed(n + 1, 0);   // 文档 1..n 是否被打印
        vector<int> stk;                  // 打印机内存，栈顶在末尾
        stk.reserve(n);
        for (int i = 1; i <= n; ++i) {
            char c = s[i - 1];
            if (c == '1') {
                stk.push_back(i);
            } else if (c == '2') {
                if (!stk.empty()) {
                    printed[stk.back()] = 1;//弹出顶端
                    stk.pop_back();
                } else {
                    printed[i] = 1;//打印文件i
                }
            } else {
                printed[i] = 1;
            }
        }
        vector<int> ans;
        for (int i = 1; i <= n; ++i)
            if (!printed[i]) ans.push_back(i);//输出违背打印的

        printf("%d\n", (int)ans.size());
        for (size_t j = 0; j < ans.size(); ++j)
            printf("%d%c", ans[j], j + 1 == ans.size() ? '\n' : ' ');
        if (ans.empty()) printf("\n");
    }
    return 0;
}