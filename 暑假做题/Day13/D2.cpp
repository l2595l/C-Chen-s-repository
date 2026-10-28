//
// Created by 28447 on 2026/8/25.
//
#include <bits/stdc++.h>

using namespace std;

struct node {
    int opr, x, y;
};

const int M = 1e6;
node v[M];

int main() {
    int n, q;
    cin >> n >> q;
    int* len = new int[n + 1]{};
    for (int i = 1; i <= q; ++i) {
        cin >> v[i].opr >> v[i].x >> v[i].y;
        if (v[i].opr == 1) {
            len[v[i].x]++;
        }
    }

    int** arr = new int*[n + 1]{};

    for (int i = 1; i <= n; ++i) {
        arr[i] = new int[len[i] + 1];
    }

    int* dex = new int[n + 1]{};
    for (int i = 1; i <= q; ++i) {
        if (v[i].opr == 1) {
            dex[v[i].x]++;
            arr[v[i].x][dex[v[i].x]] = v[i].y;
        } else {
            cout << arr[v[i].x][v[i].y] << "\n";
        }
    }

    for (int i = 1; i <= n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] dex;
    delete[] len;
    return 0;
}

