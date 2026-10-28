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
    // n=1
    for (int k = 0; k <= 12; k++) {
        cout << "n=1 a=[0] k=" << k << " -> " << brute(1, {0}, k) << "\n";
    }
    cout << "----\n";
    // n=2 a=[0,0]
    for (int k = 0; k <= 14; k++) {
        cout << "n=2 a=[0,0] k=" << k << " -> " << brute(2, {0,0}, k) << "\n";
    }
    cout << "----\n";
    // n=3 a=[0,0,0]
    for (int k = 0; k <= 12; k++) {
        cout << "n=3 a=[0,0,0] k=" << k << " -> " << brute(3, {0,0,0}, k) << "\n";
    }
    return 0;
}
