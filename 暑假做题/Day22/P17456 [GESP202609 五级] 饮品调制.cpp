#include <bits/stdc++.h>
using namespace std;

struct Water {
    long long volume;  // 体积
    long long delta;   // 与目标温度的温差，恒为正数
};

// 从 waters 中取出一部分水，使其总热量差恰好为 needHeat。
// 返回这些水的总体积。
// 注意：会按温差升序排序，因为温差越小，同样热量差能换到更多体积。
double takeWaterToMatchHeat(vector<Water>& waters, long long needHeat) {
    sort(waters.begin(), waters.end(),
         [](const Water& a, const Water& b) {
             return a.delta < b.delta;
         });

    long long usedHeat = 0;
    double extraVolume = 0.0;

    for (const auto& w : waters) {
        long long heat = w.volume * w.delta;  // 这份水能提供的总热量差

        if (heat <= needHeat - usedHeat) {
            // 整份水都可以用
            usedHeat += heat;
            extraVolume += w.volume;
        } else {
            // 只能取一部分，使热量差刚好补足
            extraVolume += (double)(needHeat - usedHeat) / w.delta;
            break;
        }
    }

    return extraVolume;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;

    double answer = 0.0;  // 最终能得到的、温度为 target 的水的总体积

    vector<Water> lower;   // 温度低于 target 的水
    vector<Water> higher;  // 温度高于 target 的水

    long long lowerHeat = 0;     // 低于 target 的总热量差：Σ v*(target-s)
    long long higherHeat = 0;    // 高于 target 的总热量差：Σ v*(s-target)
    long long lowerVolume = 0;   // 低于 target 的总体积
    long long higherVolume = 0;  // 高于 target 的总体积
    //处理每一行
    
    for (int i = 0; i < n; ++i) {
        long long volume, temp;
        cin >> volume >> temp;

        if (temp == target) {
            // 本身就是目标温度，直接可用
            answer += volume;
        } else if (temp < target) {
            long long delta = target - temp;
            lowerHeat += volume * delta;
            lowerVolume += volume;
            lower.push_back({volume, delta});
        } else {  // temp > target
            long long delta = temp - target;
            higherHeat += volume * delta;
            higherVolume += volume;
            higher.push_back({volume, delta});
        }
    }

    // 如果只有一边有热量差，无法互相中和，只能保留本身等于 target 的水
    if (lowerHeat == 0 || higherHeat == 0) {
        cout << fixed << setprecision(3) << answer << '\n';
        return 0;
    }

    if (lowerHeat < higherHeat) {
        // 低温水全部可用，再从高温水中取一部分来补足热量差
        answer += lowerVolume;
        answer += takeWaterToMatchHeat(higher, lowerHeat);
    } else if (lowerHeat > higherHeat) {
        // 高温水全部可用，再从低温水中取一部分来补足热量差
        answer += higherVolume;
        answer += takeWaterToMatchHeat(lower, higherHeat);
    } else {
        // 两边热量差相等，可以全部混合
        answer += lowerVolume + higherVolume;
    }

    cout << fixed << setprecision(3) << answer << '\n';
    return 0;
}