# -*- coding: utf-8 -*-
import sys

path = r"D:\IT_Program\Data\暑假做题\Day18\p1225双向BFS.cpp"

with open(path, "rb") as f:
    data = f.read()

repls = [
    # 1) memset vis to -1, and set start/target step to 0
    (
        b"    q[0].push(startState);\r\n"
        b"    q[1].push(targetState);\r\n"
        b"    vis[0][startState] = 1;\r\n"
        b"    vis[1][targetState] = 1;",
        b"    memset(vis, -1, sizeof(vis));\r\n"
        b"    q[0].push(startState);\r\n"
        b"    q[1].push(targetState);\r\n"
        b"    vis[0][startState] = 0;\r\n"
        b"    vis[1][targetState] = 0;",
    ),
    # 2) unvisited check: -1
    (
        b"        if (vis[dir][nextState]) continue;",
        b"        if (vis[dir][nextState] != -1) continue;",
    ),
    # 3) meet check: -1
    (
        b"        if (vis[1 - dir][nextState]) {",
        b"        if (vis[1 - dir][nextState] != -1) {",
    ),
]

for i, (old, new) in enumerate(repls, 1):
    count = data.count(old)
    print(f"repl {i}: matches = {count}")
    if count != 1:
        print(f"ERROR: repl {i} expected exactly 1 match, got {count}; aborting")
        sys.exit(1)
    data = data.replace(old, new)

with open(path, "wb") as f:
    f.write(data)

print("patch applied successfully")