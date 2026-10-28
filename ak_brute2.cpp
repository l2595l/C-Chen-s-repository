#include <bits/stdc++.h>
using namespace std;

long long best;
int n;

void dfs(int i, int k, vector<int>& val, vector<int>& col) {
    if (i == k + 1) {
        best = max(best, (long long)*min_element(val.begin(), val.end()));
        return;
    }
    for (int c = 0; c < n; c++) {
        int ov = val[c], oc = col[c];
        if (col[c] == 0) { val[c] += i; col[c] = 1; }
        else { val[c] -= i; col[c] = 0; }
        dfs(i + 1, k, val, col);
        val[c] = ov; col[c] = oc;
    }
}

long long brute(int N, vector<int> a, int k) {
    n = N;
    vector<int> col(N, 0);
    best = LLONG_MIN;
    dfs(1, k, a, col);
    return best;
}

int main() {
    // n=2 with varied a
    vector<vector<int>> cases = {
        {0,0}, {0,1}, {0,5}, {1,1}, {2,3}, {0,10}, {10,10}, {3,7}
    };
    for (auto& a : cases) {
        cout << "n=2 a=[" << a[0] << "," << a[1] << "]: ";
        for (int k = 0; k <= 14; k++) {
            cout << brute(2, a, k) << (k==14?"\n":" ");
        }
    }
    cout << "====\n";
    // n=3 with varied a
    vector<vector<int>> cases3 = {
        {0,0,0}, {0,0,1}, {0,1,2}, {1,1,1}, {0,5,10}
    };
    for (auto& a : cases3) {
        cout << "n=3 a=[" << a[0] << "," << a[1] << "," << a[2] << "]: ";
        for (int k = 0; k <= 13; k++) {
            cout << brute(3, a, k) << (k==13?"\n":" ");
        }
    }
    return 0;
}
