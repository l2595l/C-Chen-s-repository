//
// Created by 28447 on 2026/10/14.
//
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// 小木棍问题：若干根木棍由若干根等长的原始木棍切割而来，
// 求原始木棍可能的最小长度。
// 输入：第一行 n，第二行 n 个整数（棍长）。长度超过 kMaxLength 的视为无效数据并丢弃。
// 输出：原始木棍的最小长度。

constexpr int kMaxLength = 50;

class StickSolver {
public:
    explicit StickSolver(std::vector<int> sticks) : sticks_(std::move(sticks)) {
        // 从长到短排序：先放长棍，失败得更早，剪枝效果更好。
        std::sort(sticks_.begin(), sticks_.end(), std::greater<int>());
        used_.assign(sticks_.size(), false);

        // lastSame_[i]：与 sticks_[i] 等长的最后一根的下标。
        // 某根棍放进去无解时，等长的棍也一定无解，可以整段跳过。
        lastSame_.resize(sticks_.size());
        for (int i = static_cast<int>(sticks_.size()) - 1; i >= 0; --i) {
            bool sameAsNext = i + 1 < static_cast<int>(sticks_.size()) &&
                              sticks_[i] == sticks_[i + 1];
            lastSame_[i] = sameAsNext ? lastSame_[i + 1] : i;
        }
    }

    // 从小到大枚举原始长度，第一个能拼成功的长度就是答案。
    int Solve() {
        if (sticks_.empty()) {
            return 0;
        }
        int total = std::accumulate(sticks_.begin(), sticks_.end(), 0);
        for (groupLength_ = sticks_.front(); groupLength_ <= total / 2; ++groupLength_) {
            if (total % groupLength_ != 0) {
                continue;
            }
            groupCount_ = total / groupLength_;

            // 每根原始木棍都必须用到最长的那根，所以先把它固定为第一根的开头。
            used_[0] = true;
            bool found = Build(0, 1, groupLength_ - sticks_[0]);
            used_[0] = false;
            if (found) {
                return groupLength_;
            }
        }
        return total;  // 只能是一整根
    }

private:
    // completed：已经拼好的原始木棍数；
    // from：下一根候选棍的最小下标（保证同一根原始木棍里按下标递增取，避免重复排列）；
    // remaining：当前这根原始木棍还差的长度。
    bool Build(int completed, int from, int remaining) {
        if (remaining == 0) {
            if (completed + 1 == groupCount_) {
                return true;
            }
            // 新一根原始木棍必须从最长的未用棍开始。
            // 这一根一定要用上，换别的开头只是同一种拼法的重排，所以失败就直接返回。
            int first = 0;
            while (used_[first]) {
                ++first;
            }
            used_[first] = true;
            bool found = Build(completed + 1, first + 1, groupLength_ - sticks_[first]);
            used_[first] = false;
            return found;
        }

        // 棍已按降序排列，二分找到第一根长度不超过 remaining 的棍。
        auto begin = sticks_.begin() + from;
        int i = static_cast<int>(std::lower_bound(begin, sticks_.end(), remaining,
                                                  std::greater<int>()) -
                                 sticks_.begin());

        for (; i < static_cast<int>(sticks_.size()); ++i) {
            if (used_[i]) {
                continue;
            }
            used_[i] = true;
            bool found = Build(completed, i + 1, remaining - sticks_[i]);
            used_[i] = false;
            if (found) {
                return true;
            }
            // 恰好填满剩余长度却仍然失败，换别的棍凑这个长度也不会更好。
            if (remaining == sticks_[i]) {
                return false;
            }
            i = lastSame_[i];  // 跳过与失败棍等长的棍
        }
        return false;
    }

    std::vector<int> sticks_;
    std::vector<bool> used_;
    std::vector<int> lastSame_;
    int groupLength_ = 0;
    int groupCount_ = 0;
};

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> sticks;
    for (int i = 0; i < n; ++i) {
        int length = 0;
        std::cin >> length;
        if (length > 0 && length <= kMaxLength) {
            sticks.push_back(length);
        }
    }

    StickSolver solver(std::move(sticks));
    std::cout << solver.Solve() << std::endl;
    return 0;
}
