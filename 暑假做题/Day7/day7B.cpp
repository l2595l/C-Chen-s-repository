//
// Created by 28447 on 2026/8/19.
//
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> stack;  // 用vector模拟栈
    stack.reserve(n+1);   // 预分配空间，提高效率

    for (int i = 0; i < n; i++) {
        int color;
        cin >> color;

        // 如果栈不为空且栈顶颜色与当前颜色相同，则消除
        if (!stack.empty() && stack.back() == color) {
            stack.pop_back();  // 消除一对
        } else {
            stack.push_back(color);  // 入栈
        }
    }

    // 输出结果
    cout << stack.size() << "\n";
    if (stack.empty()) {
        cout << "\n";  // 空行
    } else {
        for (size_t i = 0; i < stack.size(); i++) {
            if (i > 0) cout << " ";
            cout << stack[i];
        }
        cout << "\n";
    }

    return 0;
}