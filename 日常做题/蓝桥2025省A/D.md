法一：只建"根到目标"这条链（推荐）
```c++
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int color;          // 1 = 红, 0 = 黑
    Node *left, *right;
    Node(int c) : color(c), left(nullptr), right(nullptr) {}
};

int main(){
    int m; scanf("%d", &m);
    while(m--){
        int n; long long k;
        scanf("%d %lld", &n, &k);

        Node *root = new Node(1);                  // 根：红
        Node *cur = root;
        long long x = k - 1;                       // k-1 的 n-1 位二进制就是路径
        for(int d = n - 2; d >= 0; d--){           // 从最高位开始逐层往下
            if(((x >> d) & 1) == 0){
                cur->left  = new Node(cur->color);     // 左儿子：同色
                cur = cur->left;
            }else{
                cur->right = new Node(cur->color ^ 1); // 右儿子：反色
                cur = cur->right;
            }
        }
        puts(cur->color ? "RED" : "BLACK");
    }
    return 0;
}
```
```c++
#include <bits/stdc++.h>
using namespace std;
bool dfs(int x, int y) {
    if (x == 1) {
        return true;           // 根结点为红色结点
    }
    if (y % 2 != 0) {          
        int ty = (y + 1) / 2;  // 奇数->左枝（左子结点）
        if (dfs(x - 1, ty)) {  // 递归判断父结点颜色
            return true;       // 父结点为红色，左子结点为红色
        }
        return false;          // 父结点为黑色，左子结点为黑色
    } else {                    
        int ty = y / 2;        // 偶数->右枝（右子结点）
        if (dfs(x - 1, ty)) {  // 递归判断父结点颜色
            return false;      // 父结点为红色，右子结点为黑色
        }
        return true;           // 父结点为黑色，右子结点为红色
    }
}
int main() {
    int m;
    cin >> m;
    while (m--) {
        int n, k;
        cin >> n >> k;
        cout << (dfs(n, k) ? "RED" : "BLACK") << endl;
    }
    return 0; 
}

```
法三：直接数 k-1 的二进制里 1 的个数（右转次数）
```c++

int by_popcount(long long k){ return (__builtin_popcountll(k - 1) & 1) ? 0 : 1; }

int main(){
    const int MAXR = 20;
    build(MAXR);
    long long cnt = 0;
    for(int n = 1; n <= MAXR; n++)
        for(long long k = 1; k <= (1LL << (n-1)); k++){
            int a = lvl[n][k-1], b = by_path(n, k), c = by_popcount(k);
            if(a != b || a != c){
                printf("不一致 n=%d k=%lld 建树=%d 走链=%d 数位=%d\n", n, k, a, b, c);
                return 0;
            }
            cnt++;
        }
    printf("检查了 %lld 个 (n,k)，三种方法完全一致\n", cnt);

    // 顺手验证范围极限：n=30 也能秒出
    printf("n=30,k=2^29 走链法 = %s\n", by_path(30, 1LL<<29) ? "RED" : "BLACK");
    return 0;
}
```