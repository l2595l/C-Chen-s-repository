#include<bits/stdc++.h>
using namespace std;

// ============================================================
// 1. 状态定义与全局变量
// ============================================================

const int MAX_STATE = 1 << 16;  // 状态总数 65536

char c;
int startState, targetState;     // 起点和终点的压缩状态
int a[5][5], b[5][5];           // 临时棋盘数组 (1-based)
int cnt;                         // 路径步数计数器
int res[100000][4];             // 存储最终路径 (每一步的4个坐标)

// 四个方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ----- 双向BFS数据结构 -----
// vis[0] 表示从起点开始访问，vis[1] 表示从终点开始访问
// 存储的值：访问时的步数 (从0开始)
int vis[2][MAX_STATE];

// parent[0] 记录从起点搜索时的父状态，parent[1] 记录从终点搜索时的父状态
int parent[2][MAX_STATE];

// 操作编码：存储产生该状态时的交换操作 (编码为 i*16+j)
int op[2][MAX_STATE];

// 两个队列：q[0] 从起点扩展，q[1] 从终点扩展
queue<int> q[2];

// 存储状态的详细信息 (用于路径回溯)
struct Ans {
    int nx, ny;    // 交换后新棋子的位置 (目标位置)
    int ox, oy;    // 交换前棋子的位置 (原始位置)
} ans[2][MAX_STATE];  // 分别存储两个方向的路径信息

// ============================================================
// 2. 编码与解码函数
// ============================================================

/**
 * 将 4x4 棋盘数组 (1-based) 编码为 16 位整数
 *
 * 编码方式：从右下角开始，逐行从右到左编码
 * 位置映射：a[4][4] -> bit 0, a[4][3] -> bit 1, ...
 *
 * @param board 4x4 棋盘数组
 * @return 压缩后的整数状态
 */
int encodeBoard(int board[5][5]) {
    int state = 0, bit = 0;
    for(int i = 4; i >= 1; i--) {
        for(int j = 4; j >= 1; j--) {
            if(board[i][j]) state |= (1 << bit);
            bit++;
        }
    }
    return state;
}

/**
 * 将整数状态解码为 4x4 棋盘数组
 *
 * @param state 压缩的整数状态
 * @param board 输出棋盘数组 (1-based)
 */
void decodeState(int state, int board[5][5]) {
    for(int i = 4; i >= 1; i--) {
        for(int j = 4; j >= 1; j--) {
            board[i][j] = state & 1;
            state >>= 1;
        }
    }
}

// ============================================================
// 3. 输入输出函数
// ============================================================

/**
 * 读入棋盘数据
 */
void init() {
    // 读取初始棋盘
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    // 读取目标棋盘
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            cin >> c;
            b[i][j] = c - '0';
        }
    }
}

// ============================================================
// 4. 双向BFS核心函数
// ============================================================

/**
 * 检查两个格子是否相邻且颜色不同 (合法交换)
 *
 * @param ox, oy 第一个格子的坐标
 * @param nx, ny 第二个格子的坐标
 * @param board 当前棋盘
 * @return 是否可以进行交换
 */
bool isValidSwap(int ox, int oy, int nx, int ny, int board[5][5]) {
    // 检查边界
    if(nx < 1 || nx > 4 || ny < 1 || ny > 4) return false;
    // 颜色不同才能交换 (相同颜色交换无意义)
    return board[ox][oy] != board[nx][ny];
}

/**
 * 扩展一侧队列 (双向BFS)
 *
 * @param dir      搜索方向: 0=从起点扩展, 1=从终点扩展
 * @param meetState 相遇点状态 (输出参数)
 * @return 是否找到相遇点
 */
bool expand(int dir, int& meetState) {
    // 取出队首状态
    int state = q[dir].front();
    q[dir].pop();

    // 将状态解码到数组 a 中 (用于操作)
    decodeState(state, a);

    // 枚举所有可能的交换操作
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            // 以 (i,j) 为起点，尝试四个方向
            for(int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];

                // 检查是否合法交换
                if(!isValidSwap(i, j, ni, nj, a)) continue;

                // 执行交换
                swap(a[i][j], a[ni][nj]);
                int nextState = encodeBoard(a);

                // 如果新状态在本次方向中未访问过
                if(!vis[dir][nextState]) {
                    vis[dir][nextState] = vis[dir][state] + 1;
                    parent[dir][nextState] = state;
                    op[dir][nextState] = i * 16 + ni;  // 编码: 原位置行*16+目标位置行 (实际只存行，列单独存储)
                    // 实际应该存储完整坐标，这里用 ans 结构体存储
                    ans[dir][nextState] = {ni, nj, i, j};  // 目标位置, 原始位置
                    q[dir].push(nextState);

                    // 检查是否在另一侧已访问 (相遇)
                    if(vis[1 - dir][nextState]) {
                        meetState = nextState;
                        return true;
                    }
                }

                // 回溯：恢复棋盘
                swap(a[i][j], a[ni][nj]);
            }
        }
    }
    return false;
}

/**
 * 双向BFS主函数
 *
 * @param meetState 输出相遇点状态
 */
void bidirectionalBFS(int& meetState) {
    // 初始化起点队列
    q[0].push(startState);
    vis[0][startState] = 1;      // 步数从1开始 (0表示未访问)
    parent[0][startState] = -1;

    // 初始化终点队列
    q[1].push(targetState);
    vis[1][targetState] = 1;
    parent[1][targetState] = -1;

    // 交替扩展两个队列，直到某一侧为空或找到相遇点
    while(!q[0].empty() && !q[1].empty()) {
        // 选择队列较小的一侧扩展 (优化性能)
        int dir = (q[0].size() < q[1].size()) ? 0 : 1;
        if(expand(dir, meetState)) {
            return;  // 找到相遇点
        }
    }
}

// ============================================================
// 5. 路径输出函数
// ============================================================

/**
 * 从起点侧回溯路径
 *
 * @param meetState 相遇点状态
 * @param path 输出路径向量 (每个元素是操作编码)
 */
void traceStartPath(int meetState, vector<int>& path) {
    int state = meetState;
    while(state != startState) {
        path.push_back(state);
        state = parent[0][state];
    }
    reverse(path.begin(), path.end());
}

/**
 * 从终点侧回溯路径
 *
 * @param meetState 相遇点状态
 * @param path 输出路径向量 (每个元素是操作编码)
 */
void traceTargetPath(int meetState, vector<int>& path) {
    int state = meetState;
    while(state != targetState) {
        path.push_back(state);
        state = parent[1][state];
    }
    // 注：path 是从 meetState 到 targetState 的顺序
}

/**
 * 输出最终路径
 *
 * @param meetState 相遇点状态
 */
void printPath(int meetState) {
    vector<int> startPath, targetPath;

    // 从两侧回溯路径
    traceStartPath(meetState, startPath);
    traceTargetPath(meetState, targetPath);

    // 总步数 = 起点到相遇点的步数 + 相遇点到终点的步数
    // 因为 vis 从 1 开始计数，所以实际步数要减 1
    int totalSteps = (vis[0][meetState] - 1) + (vis[1][meetState] - 1);

    // 将路径转换为输出格式
    vector<array<int, 4>> output;

    // 起点到相遇点的操作
    for(int state : startPath) {
        int code = op[0][state];
        int originalRow = ans[0][state].ox;
        int originalCol = ans[0][state].oy;
        int targetRow = ans[0][state].nx;
        int targetCol = ans[0][state].ny;
        output.push_back({originalRow, originalCol, targetRow, targetCol});
    }

    // 相遇点到终点的操作 (注意：终点侧存储的是目标位置在前，原始位置在后)
    // 但为了输出统一，我们输出 (原始位置 -> 目标位置)
    for(int state : targetPath) {
        int originalRow = ans[1][state].ox;
        int originalCol = ans[1][state].oy;
        int targetRow = ans[1][state].nx;
        int targetCol = ans[1][state].ny;
        output.push_back({originalRow, originalCol, targetRow, targetCol});
    }

    // 输出结果
    cout << totalSteps << endl;
    for(auto& step : output) {
        cout << step[0] << step[1] << step[2] << step[3] << endl;
    }
}

// ============================================================
// 6. 主函数
// ============================================================

int main() {
    // 读取输入
    init();

    // 编码起点和终点
    startState = encodeBoard(a);
    targetState = encodeBoard(b);

    // 如果起点就是终点
    if(startState == targetState) {
        cout << 0 << endl;
        return 0;
    }

    // 执行双向BFS
    int meetState = -1;
    bidirectionalBFS(meetState);

    // 输出结果
    if(meetState != -1) {
        printPath(meetState);
    } else {
        cout << -1 << endl;  // 理论上不会发生
    }

    return 0;
}