//
// Created by 28447 on 2026/8/31.
//

// ============================================================
// 洛谷 P1225 [CEOI 1999] 黑白棋游戏
//
// 【题意】
//   有一个 4×4 的棋盘，每个格子是黑(1)或白(0)。
//   每次可以交换两个「上下或左右相邻」的格子。
//   给出初始局面和目标局面，求最少交换次数，并输出每一步
//   （每一步输出四个数字：要交换的两个格子的 行 列 行 列，1 起算）。
//
// 【核心思路：状态压缩 + BFS】
//   1. 4×4 = 16 个格子，每个格子只有 0/1 两种取值，
//      所以整个棋盘可以压缩成一个 16 位的二进制整数（0 ~ 65535）。
//      这样"一个棋盘"就变成了"一个 int"，可以用数组直接下标访问。
//   2. 一次相邻交换 = 在这个 int 上交换两个 bit。
//   3. 因为每次交换的代价都是 1，所以从初始状态做 BFS，
//      第一次搜到目标状态就是最少步数（BFS 层序性质）。
//   4. 用 pre[] 记录"每个状态是从哪个状态来的"，
//      用 op[] 记录"那一步交换的是哪两个格子"，
//      最后从目标状态一路回溯到初始状态，就能还原出操作序列。
// ============================================================

#include <bits/stdc++.h>
using namespace std;

int startState = 0, targetState = 0;   // 初始状态、目标状态（压缩后的 int）
int pre[1 << 16];                      // pre[s] = 状态 s 在 BFS 中的前驱状态；-1 表示还没被访问过
int op[1 << 16];                       // op[s] = 从 pre[s] 变成 s 时交换的两个格子，编码为 i*16+j
int dist[1 << 16];                     // dist[s] = 从初始状态到 s 的最少步数（本解法里其实没用于输出）
vector<pair<int,int>> edges;           // 所有「相邻格子」的下标对 (i, j)，i、j 取值范围 0~15

// 将 4 行字符串编码成 16 位整数
// 棋盘按行优先读入：先第 0 行、再第 1 行…… 每个字符依次变成从高位到低位的一个 bit。
// 例如 board[0][0] 对应最高位(第15位)，board[3][3] 对应最低位(第0位)。
int encodeState(vector<string>& board) {
    int state = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int bit = board[i][j] - '0';   // 字符 '0'/'1' -> 数字 0/1（迭代器转int）
            state = (state << 1) | bit;    // 左移一位腾出位置，再把当前 bit 放到最低位
        }
    }
    return state;
}

// 交换 state 中第 i 位和第 j 位（i、j 是 0~15 的格子下标，不是 bit 位置）
// 注意：这里 15-i 是因为「格子下标 0 对应最高位 bit15」。
//       格子下标越大，对应的 bit 越靠右（越低位）。
int swapBits(int state, int i, int j) {
    // 取出两个格子各自的值
    int bi = (state >> (15 - i)) & 1;   // 第 i 个格子的值（0 或 1）
    int bj = (state >> (15 - j)) & 1;   // 第 j 个格子的值（0 或 1）

    // 两个格子一样，交换后局面不变，直接返回原状态
    if (bi == bj) return state;

    // 两个格子不一样（一个0一个1），用异或把这两位翻转即可实现"交换"
    // （异或 1 会翻转那一位：0<->1）
    state ^= (1 << (15 - i));
    state ^= (1 << (15 - j));
    return state;
}

// 获取状态中第 pos 个格子的值（pos 为 0~15 的格子下标）
// （本解法里其实没用到这个函数，保留作为工具）
int getBit(int state, int pos) {
    return (state >> (15 - pos)) & 1;
}

// 输出一步操作：即"变成 state 这一步"交换的是哪两个格子
void printOperation(int state) {
    int code = op[state];        // op 里存的是 i*16+j
    int a = code / 16;           // 拆出第一个格子的下标（0~15）
    int b = code % 16;           // 拆出第二个格子的下标（0~15）

    // 把下标(0~15)转成 1 起算的 (行, 列)
    // 下标 a 对应的行 = a/4，列 = a%4，再加 1 变成题目要求的 1 起算
    int ar = a / 4 + 1, ac = a % 4 + 1;
    int br = b / 4 + 1, bc = b % 4 + 1;

    cout << ar << ac << br << bc << '\n';
}

int main() {
    ios::sync_with_stdio(false);   // 关闭 C 风格 IO 同步，加快读写
    cin.tie(0);                    // 解除 cin/cout 绑定

    // 读入初始状态（4 行）和目标状态（4 行）
    vector<string> startBoard(4), targetBoard(4);
    for (int i = 0; i < 4; i++) {
        cin >> startBoard[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> targetBoard[i];
    }

    // 把两个棋盘压缩成整数
    startState = encodeState(startBoard);
    targetState = encodeState(targetBoard);

    // 预先构建所有「相邻格子」的下标对
    // 每个格子一个 id = r*4 + c（0~15），只向右、向下连边，避免重复。
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int id = r * 4 + c;
            if (r + 1 < 4) edges.push_back({id, id + 4});  // 和下方格子相邻（id+4）
            if (c + 1 < 4) edges.push_back({id, id + 1});  // 和右方格子相邻（id+1）
        }
    }

    // ---------- BFS ----------
    memset(pre, -1, sizeof(pre));   // 所有状态初始化为"未访问"(-1)
    queue<int> q;
    q.push(startState);
    pre[startState] = startState;   // 起点标记为自己，作为回溯的终点哨兵
    dist[startState] = 0;

    while (!q.empty()) {
        int state = q.front();
        q.pop();

        if (state == targetState) break;   // 第一次搜到目标即可停止（BFS 保证最短）

        // 枚举所有相邻交换
        for (auto [i, j] : edges) {
            int nextState = swapBits(state, i, j);   // 交换后得到新状态

            if (pre[nextState] == -1) {              // 该状态还没访问过
                pre[nextState] = state;              // 记录前驱
                op[nextState] = i * 16 + j;          // 记录这一步交换的是 i、j
                dist[nextState] = dist[state] + 1;   // 记录步数
                q.push(nextState);
            }
        }
    }

    // 理论上一定能到达（初始和目标的黑白数量相同）；若到不了就输出 -1
    if (pre[targetState] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    // ---------- 回溯还原操作序列 ----------
    vector<int> path;// 从目标到起点的逆序路径
    // 从目标一路沿着 pre 往回走，直到回到起点；起点本身不放进 path
    // 所以 path 里存的是"被交换产生"的那些状态，每个状态的 op 就是一步操作
    for (int state = targetState; state != startState; state = pre[state]) {//每次执行后沿着父指针向上回溯
        path.push_back(state);
    }
    reverse(path.begin(), path.end());   // 反转成从第一步到最后一步的顺序

    // 输出步数和每一步
    cout << path.size() << '\n';
    for (int state : path) {
        printOperation(state);
    }

    return 0;
}