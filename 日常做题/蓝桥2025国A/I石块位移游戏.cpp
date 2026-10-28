#include <bits/stdc++.h>
using namespace std;

// n 个槽位排成一条链，前 n-1 个槽位各有一块石头，第 n 个槽位为空。
// 空槽位可以接收相邻槽位的石块。目标是让编号为 i 的石块回到槽位 i。
// 可以花 1 的代价任选两个槽位让它们相连，求使游戏有解的最小代价。
//
// 结论：
//   已经全部归位                        -> 0
//   错位部分恰是升序序列的一次循环移位   -> 1（连成环后，绕着环转动即可）
//   其余情况                            -> 2
//
// 说明：第一个和最后一个错位的位置之外，石块已在原位。
// 在这之间的石块编号恰好是 left..right 这些数，且互不相同。
// 这样的序列是升序序列的循环移位，当且仅当把它首尾相接后，
// "前一个大于后一个"的位置恰好出现一次。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> stone(n);  // stone[i]：槽位 i 里的石块编号，下标从 1 开始
    for (int i = 1; i < n; ++i) {
        cin >> stone[i];
    }

    int left = 1;
    while (left < n && stone[left] == left) {
        ++left;
    }
    if (left == n) {
        cout << 0 << '\n';
        return 0;
    }

    int right = n - 1;
    while (stone[right] == right) {
        --right;
    }

    // 在 [left, right] 内统计首尾相接后"前大于后"的位置数
    int descents = 0;
    for (int i = left; i <= right; ++i) {
        int next = (i == right) ? left : i + 1;
        if (stone[i] > stone[next]) {
            ++descents;
        }
    }

    cout << (descents == 1 ? 1 : 2) << '\n';
    return 0;
}
