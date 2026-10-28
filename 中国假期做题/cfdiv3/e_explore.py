import sys
sys.setrecursionlimit(10000)

def gen_paths(n):
    """图：A=[1..n], B=[1..n]，边 (i,j) 当 |i-j|<=1。返回所有从 a1 出发的哈密顿路径（用 (side,idx) 表示）"""
    adj = {}
    for i in range(1, n + 1):
        adj[('A', i)] = [('B', j) for j in range(1, n + 1) if abs(i - j) <= 1]
        adj[('B', i)] = [('A', j) for j in range(1, n + 1) if abs(i - j) <= 1]
    allv = [('A', i) for i in range(1, n + 1)] + [('B', i) for i in range(1, n + 1)]
    res = []
    path = [('A', 1)]
    used = {('A', 1)}
    def dfs(v):
        if len(path) == 2 * n:
            res.append(path[:])
            return
        for w in adj[v]:
            if w not in used:
                used.add(w); path.append(w)
                dfs(w)
                path.pop(); used.remove(w)
    dfs(('A', 1))
    return res

for n in range(1, 8):
    p = gen_paths(n)
    print('n =', n, ' 哈密顿路径数 =', len(p))
