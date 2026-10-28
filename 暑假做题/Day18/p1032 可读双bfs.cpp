//
// Created by 28447 on 2026/9/3.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 6;        // 最大规则数
const int MAX_STEP = 10; // 最大步数限制

int n;                  // 实际规则数量
string A, B;            // 起始字符串和目标字符串
string a[N], b[N];      // 变换规则: a[i] -> b[i]

/**
 * 单向扩展函数 - BFS的一层扩展
 * @param q     当前方向的队列
 * @param da    当前方向的距离映射
 * @param db    另一方向的距离映射
 * @param from  变换规则的左部（源字符串）
 * @param to    变换规则的右部（目标字符串）
 * @return      如果相遇返回总步数，否则返回11（大于10表示未找到）
 */
int extend(queue<string>& q,
           unordered_map<string, int>& da,
           unordered_map<string, int>& db,
           string from[],
           string to[])
{
    // 记录当前层的距离值（BFS按层扩展）
    int currentDepth = da[q.front()];

    // 只扩展当前层的所有节点（同一深度的节点）
    while (!q.empty() && da[q.front()] == currentDepth)
    {
        string cur = q.front();
        q.pop();

        // 尝试所有变换规则
        for (int i = 0; i < n; i++)
        {
            // 在cur中查找所有可以应用规则的位置
            for (int j = 0; j < (int)cur.size(); j++)
            {
                // 检查从位置j开始的子串是否匹配规则左部
                if (cur.substr(j, from[i].size()) == from[i])
                {
                    // 构造替换后的新字符串
                    string nxt = cur.substr(0, j) + to[i] + cur.substr(j + from[i].size());

                    // 如果在另一方向已经访问过，说明相遇了！
                    if (db.count(nxt))
                    {
                        return da[cur] + db[nxt] + 1;
                    }

                    // 如果当前方向已经访问过，跳过（避免重复）
                    if (da.count(nxt))
                    {
                        continue;
                    }

                    // 新状态入队
                    da[nxt] = da[cur] + 1;
                    q.push(nxt);
                }
            }
        }
    }

    return 11; // 返回大于10的数表示未找到
}

/**
 * 双向BFS主函数
 * @return 最少步数（≤10），如果无解返回-1
 */
int bfs()
{
    // 特判：起点就是终点
    if (A == B) return 0;

    queue<string> qa, qb;              // 两个方向的队列
    unordered_map<string, int> da, db;  // 两个方向的距离映射

    // 初始化：起点和终点入队
    qa.push(A);
    qb.push(B);
    da[A] = 0;
    db[B] = 0;

    int step = 0; // 当前已经扩展的层数

    // 两个队列都非空时才继续
    while (!qa.empty() && !qb.empty())
    {
        int result;

        // 优化：每次扩展节点数较少的队列（平衡搜索树）
        if (qa.size() < qb.size())
        {
            // 从起点方向扩展（使用正向规则）
            result = extend(qa, da, db, a, b);
        }
        else
        {
            // 从终点方向扩展（使用反向规则）
            result = extend(qb, db, da, b, a);
        }

        // 如果找到结果且在步数限制内
        if (result <= MAX_STEP)
        {
            return result;
        }

        // 如果已经扩展了10层还没找到，说明无解
        if (++step == MAX_STEP)
        {
            return -1;
        }
    }

    return -1; // 队列为空，无法继续搜索
}

int main()
{
    // 读入起始字符串和目标字符串
    cin >> A >> B;

    // 读入所有变换规则（直到文件结束）
    n = 0;
    while (cin >> a[n] >> b[n])
    {
        n++;
    }

    // 执行双向BFS
    int result = bfs();

    // 输出结果
    if (result == -1)
    {
        cout << "NO ANSWER!" << endl;
    }
    else
    {
        cout << result << endl;
    }

    return 0;
}