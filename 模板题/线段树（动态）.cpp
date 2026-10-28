//
// Created by 28447 on 2026/10/21.
//
#include <bits/stdc++.h>
using namespace std;

#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

// 节点摘要：区间和 + 区间长度
struct Info {
  long long sum = 0;   // 区间和
  int len = 0;         // 区间长度（lazy 更新时要乘它）
  Info operator+(const Info& o) const {   // 合并
    return {sum + o.sum, len + o.len};
  }
};

// 懒惰标记：区间每个元素加 add
struct Transform {
  long long add = 0;   // 默认 0 = 单位变换（什么都没加）
  // 复合：先做 o 再做 this（加法可交换，顺序无所谓）
  Transform operator*(const Transform& o) const {
    return {add + o.add};
  }
  // 把变换作用到节点摘要上
  void apply(Info& x) const {
    x.sum += add * x.len;
  }
};

int rt, id, L, R;
vector<array<int, 2>> ch;
vector<Info> val;
vector<Transform> lazy;

// 给节点 cr 打上变换 t：更新值 + 累积标记
void apply_node(int cr, const Transform& t) {
  t.apply(val[cr]);
  lazy[cr] = t * lazy[cr];
}

void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

// 下传标记（只在非叶子调用）
void push_down(int cr) {
  if (lazy[cr].add == 0) return;      // 没欠账
  apply_node(lc(cr), lazy[cr]);
  apply_node(rc(cr), lazy[cr]);
  lazy[cr] = Transform{};             // 还清，恢复单位变换
}

void build(int cr, int ll, int rr, const vector<long long>& a) {
  if (ll == rr) {
    val[cr] = {a[ll - L], 1};
    return;
  }
  int mm = ll + ((rr - ll) >> 1);
  build(lc(cr) = ++id, ll, mm, a);
  build(rc(cr) = ++id, mm + 1, rr, a);
  push_up(cr);
}

void build(int l, int r, const vector<long long>& a) {
  L = l, R = r, id = 0;
  int n = r - l + 1;
  ch.assign(n << 1, {0, 0});
  val.assign(n << 1, {});
  lazy.assign(n << 1, {});           // 默认构造 = 单位变换
  build(rt = ++id, L, R, a);
}

// 区间 [ql,qr] 每个元素加 v
void range_add(int cr, int ll, int rr, int ql, int qr, long long v) {
  if (ql <= ll && rr <= qr) {        // 完全覆盖：打标记，不往下走
    apply_node(cr, {v});
    return;
  }
  push_down(cr);                     // 要进孩子，先还账
  int mm = ll + ((rr - ll) >> 1);
  if (ql <= mm) range_add(lc(cr), ll, mm, ql, qr, v);
  if (qr > mm)  range_add(rc(cr), mm + 1, rr, ql, qr, v);
  push_up(cr);                       // 回溯重算
}

void range_add(int ql, int qr, long long v) { range_add(rt, L, R, ql, qr, v); }

// 区间 [ql,qr] 求和
Info query(int cr, int ll, int rr, int ql, int qr) {
  if (ql <= ll && rr <= qr) return val[cr];
  push_down(cr);                     // 进孩子前还账
  int mm = ll + ((rr - ll) >> 1);
  Info res{};                        // 单位元：sum=0, len=0
  if (ql <= mm) res = res + query(lc(cr), ll, mm, ql, qr);
  if (qr > mm)  res = res + query(rc(cr), mm + 1, rr, ql, qr);
  return res;
}

long long query(int ql, int qr) { return query(rt, L, R, ql, qr).sum; }