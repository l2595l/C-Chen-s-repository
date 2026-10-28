//
// Created by 28447 on 2026/8/30.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 高精度乘以低精度
vector<int> mul(vector<int> a, int b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i < a.size() || carry; i++) {
        long long sum = carry;
        if (i < a.size()) sum += (long long)a[i] * b;
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

// 高精度除以低精度
vector<int> div(vector<int> a, int b) {
    vector<int> res;
    int remainder = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        long long cur = (long long)remainder * 10 + a[i];
        res.push_back(cur / b);
        remainder = cur % b;
    }
    reverse(res.begin(), res.end());
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

// 计算组合数 C(n, k)
vector<int> comb(int n, int k) {
    if (k < 0 || k > n) return {0};
    k = min(k, n - k);

    vector<int> res = {1};
    for (int i = 1; i <= k; i++) {
        res = mul(res, n - k + i);
        res = div(res, i);
    }
    return res;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    
    // ans = C(a+n, n) * C(b+n, n)
    vector<int> c1 = comb(a + n, n);
    vector<int> c2 = comb(b + n, n);

    // 高精度乘法
    vector<int> ans(c1.size() + c2.size(), 0);
    for (int i = 0; i < c1.size(); i++) {
        for (int j = 0; j < c2.size(); j++) {
            ans[i + j] += c1[i] * c2[j];
            ans[i + j + 1] += ans[i + j] / 10;
            ans[i + j] %= 10;
        }
    }
    while (ans.size() > 1 && ans.back() == 0) ans.pop_back();

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    cout << endl;

    return 0;
}