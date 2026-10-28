//
// Created by 28447 on 2026/8/28.
//
// A simple ModInt implementation.
// 一个简单的模整数（ModInt）实现
// 模数 M 必须是编译期常量（如 ModInt<1000000007>）
template <int M>
struct ModInt {
    // 空标记结构体，用于区分构造函数重载
    // 作用：标记"跳过取模校验"，仅供内部使用以提升性能
    struct skip_mod {};

    // 带 skip_mod 标记的构造函数：直接赋值，不进行取模
    // 前提：调用者保证 v 已经在 [0, M) 范围内
    // 用于内部运算结果返回，避免重复取模
    ModInt(int v, skip_mod) : v(v) {}

    // 存储模 M 下的值，始终在 [0, M-1] 范围内
    int v;

    // 默认构造函数：初始化为 0
    ModInt() : v(0) {}

    // 从 long long 类型构造，自动处理取模和负数
    // 等价于：v = int((x % M + M) % M)
    // 处理步骤：
    //   1. x %= M   → 将 x 缩小到 (-M, M) 范围
    //   2. 如果 x < 0，加 M → 转为非负数
    //   3. 强转为 int 存储
    ModInt(long long x) {
        x %= M;
        if (x < 0) x += M;
        v = int(x);
    }

    // ==================== 加法 ====================
    // 等价于：ModInt((l.v + r.v) % M)
    // 优化：因为 l.v + r.v 最大为 2M-2，只需减一次 M
    // 比使用 % 运算符更快
    friend ModInt operator+(ModInt l, ModInt r) {
        int res = l.v + r.v;
        if (res >= M) res -= M;
        return ModInt(res, skip_mod{});  // 使用 skip_mod 跳过重复取模
    }

    // ==================== 减法 ====================
    // 等价于：ModInt((l.v - r.v + M) % M)
    // 优化：因为 l.v - r.v 最小为 -(M-1)，只需加一次 M
    // 比使用 % 运算符更快
    friend ModInt operator-(ModInt l, ModInt r) {
        int res = l.v - r.v;
        if (res < 0) res += M;
        return ModInt(res, skip_mod{});  // 使用 skip_mod 跳过重复取模
    }

    // ==================== 乘法 ====================
    // 先转 long long 防止 int 溢出，然后取模
    // 用 skip_mod 标记避免二次取模（因为 % M 已经保证在范围内）
    friend ModInt operator*(ModInt l, ModInt r) {
        return ModInt(1LL * l.v * r.v % M, skip_mod{});
    }

    // ==================== 快速幂（模幂运算）====================
    // 计算当前值的 b 次幂（模 M）：this^b mod M
    // 使用二进制指数法（快速幂），时间复杂度 O(log b)
    // 常用于计算模逆元（当 M 为质数时，a^(M-2) ≡ a^(-1) mod M）
    ModInt pow(long long b) const {
        ModInt res{1};      // 结果，初始为 1（模 M 下的乘法单位元）
        ModInt po{*this};   // 底数，初始为当前值，之后不断平方

        // 遍历 b 的每一个二进制位
        // b >>= 1 表示右移一位，相当于 b /= 2
        for (; b; b >>= 1) {
            // 如果当前位是 1，将当前底数乘到结果中
            if (b & 1) res = res * po;
            // 底数平方：po = po^2，对应下一个二进制位
            po = po * po;
        }
        return res;
    }
};