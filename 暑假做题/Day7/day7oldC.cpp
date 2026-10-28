//
// Created by 28447 on 2026/8/19.
//delete hard
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (!stk.empty() && stk.back() == x) {
            stk.pop_back();
        } else {
            stk.push_back(x);
        }
    }
    cout << stk.size() << endl;
    for (int i = 0; i < stk.size(); i++) {
        if (i) cout << " ";
        cout << stk[i];
    }
    cout << endl;
    return 0;
}