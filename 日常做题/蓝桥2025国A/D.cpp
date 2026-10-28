//
// Created by 28447 on 2026/10/19.
//
#include <stdio.h>

constexpr int s[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
// 12 个月天数的前缀和，后面用于计算

#define leap(x) ((x) % 4 == 0)
// 是否为闰年（因为 k 很小，不会让年份满足 mod 100 = 0 或 mod 400 = 0，所以简化判断）

#define day(m, d) (/* 距离年初的天数 */\
s[(m) - 1] /* 整月的天数 */ \
+ (m == 2 && d == 29 && !leap(y) ? 28 : d) /* 如果 2 月 29 日且平年，按 28 日计算，否则正常计算*/\
+ (leap(y) && m > 2)) /* 如果是闰年，比平年多 1 天 */

int m1, d1, m2, d2, k; bool fg;
int main(void) {
    scanf("%d %d %d %d %d", &m1, &d1, &m2, &d2, &k);
    for (int y = 2025; y < 2025 + k; ++y) // 遍历
        if ((day(m1, d1) - day(m2, d2)) % 7 == 0 /* 天数之差 mod 7 = 0 */ )
            printf("%d\n", y), fg = true /* 打标记 */;
    if (!fg) printf("No Answer"); // 如果没有合法的，输出“No answer”
    return 0;
}
