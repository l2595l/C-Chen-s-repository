//
// Created by 28447 on 2026/9/26.
//
#include <cstdio>
#include <iostream>
using namespace std;

#define ll long long

const int MAXN = 50010;
int n, a[MAXN], c[MAXN];
ll ans = 0;

void msort(int b, int e) {
    if (b >= e) return;

    int mid = (b + e) / 2;
    msort(b, mid);
    msort(mid + 1, e);

    int i = b, j = mid + 1, k = b;

    while (i <= mid && j <= e) {
        if (a[i] <= a[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = a[j++];
            ans += mid - i + 1;   // 左半部分从 i 到 mid 都大于 a[j]
        }
    }

    while (i <= mid) c[k++] = a[i++];
    while (j <= e) c[k++] = a[j++];

    for (int t = b; t <= e; ++t) {
        a[t] = c[t];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    ans = 0;
    msort(1, n);
    printf("%lld\n", ans);

    return 0;
}