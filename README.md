# C++ 刷题与算法练习

记录蓝桥杯、洛谷、Codeforces 的刷题代码，以及 C++ 语言与 STL 的学习笔记。

目前共 **317 个源文件**，约 **2.1 万行** C++ 代码。

---

## 目录结构

```
Data/
├── 日常做题/            日常训练：蓝桥杯真题、洛谷、Codeforces
│   ├── 蓝桥2025国A/      2025 蓝桥杯 国赛 A 组
│   ├── 蓝桥2025省A/      2025 蓝桥杯 省赛 A 组
│   ├── 蓝桥26省A/        2026 省赛 A 组
│   ├── 蓝桥26省B/        2026 省赛 B 组
│   └── cfdiv1+2(10.10)/  Codeforces Div.1 + Div.2
├── 暑假做题/            暑期集训：Day1 – Day22 题单，23ak / 24百度 / 25ak
├── 中国假期做题/        假期题单：Day1、Day2、Codeforces Div.3
├── 模板题/              常用算法模板
├── 第三阶段-录制代码/   C++ 教程第三阶段：STL 容器与常用算法
├── C++核心/             C++ 核心编程笔记
├── C++提高/             C++ 提高编程笔记
└── *.cpp                零散练习（ak_* 系列、倒计时卡牌、烟花等）
```

## 内容概览

| 目录 | 内容 | 源文件 |
| --- | --- | ---: |
| `暑假做题/` | 暑期集训题单，按天分组 | 159 |
| `第三阶段-录制代码/` | STL 容器、函数对象、常用算法 | 99 |
| `日常做题/` | 蓝桥杯真题、洛谷 P 题号、Codeforces | 32 |
| `中国假期做题/` | 假期题单 | 15 |
| `模板题/` | 线段树、哈希、三分、双链表、扫描线 | 5 |
| 根目录 | 零散练习程序 | 5 |

## 算法模板

`模板题/` 下收录了可直接复用的实现：

- `线段树（动态）.cpp`
- `扫描线 & 矩形面积并.cpp`
- `三分.cpp`
- `哈希.cpp` / `hash.md`
- `双链表.cpp`

绝大多数题目文件使用同一套开码头，便于在不同平台之间直接复制：

```cpp
#include <bits/stdc++.h>
#define lcm(x, y) x / __gcd(x, y) * y
#define lb(x) (x & -x)
#define str to_string

using namespace std;
using ll = long long;

const double EPS = 1e-6, PAI = acos(-1.0);
const int MAX = 3e4 + 5, mod = 1e9 + 7, MOD = 998244353;

ll quickly_pow(ll a, ll b, ll p);  // 快速幂
```

## 编译与运行

单个文件直接编译（推荐加优化，与评测机行为一致）：

```bash
g++ -O2 -std=c++17 -o A A.cpp
./A        # Linux / macOS
A.exe      # Windows
```

需要 CMake 工程的部分（`CLion_Data/`、`第三阶段-录制代码/` 中的 Visual Studio 工程）直接用 CLion 或 VS 打开对应目录运行。

## 开发环境

- **系统**：Windows 11
- **IDE**：CLion 2026.2（CMake + Ninja）、Visual Studio 2022、VS Code
- **编译器**：GNU g++，标准 `C++17`

## 版本管理

```bash
git add -A
git commit -m "做了什么"
git push
```

`.gitignore` 已排除编译产物与构建目录（`*.exe`、`*.obj`、`*.pdb`、`cmake-build-debug/`、`out/` 等），仓库里只保留源码与文档。

## 说明

- 题号优先使用原始编号（如 `P1379 八数码难题.cpp`），便于回溯原题；
- 同一道题可能存在多个版本（如八数码的 BFS、IDA*、优化版），通过文件名后缀区分；
- 中文注释为个人思路记录，不作为可读性标准。
