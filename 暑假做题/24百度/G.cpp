//
// Created by 28447 on 2026/9/9.
//
#include <bits/stdc++.h>
using namespace std;

vector<string> hand(2);
vector<int> hp(2, 4);
string cards;
int pos;

void discard(int player) {
    while((int)hand[player].size() > hp[player]) {
        size_t posD = hand[player].find('D');
        if(posD != string::npos) {
            hand[player].erase(posD, 1);
        } else {
            size_t posP = hand[player].find('P');
            if(posP != string::npos) {
                hand[player].erase(posP, 1);
            } else {
                break;
            }
        }
    }
}

bool usePeach(int player) {
    size_t posP = hand[player].find('P');
    if(posP != string::npos && hp[player] < 4) {
        hand[player].erase(posP, 1);
        hp[player]++;
        return true;
    }
    return false;
}

bool usePeachEmergency(int player) {
    size_t posP = hand[player].find('P');
    if(posP != string::npos) {
        hand[player].erase(posP, 1);
        hp[player]++;
        return true;
    }
    return false;
}

bool useKill(int attacker, int defender) {
    size_t posK = hand[attacker].find('K');
    if(posK == string::npos) return false;

    hand[attacker].erase(posK, 1);

    size_t posD = hand[defender].find('D');
    if(posD != string::npos) {
        hand[defender].erase(posD, 1);
        return false;
    } else {
        hp[defender]--;
        if(hp[defender] <= 0) {
            if(!usePeachEmergency(defender)) {
                return true;  // 对手死亡
            }
        }
        return true;
    }
}

// 递归模拟游戏
int dfs(int turn) {
    // 终止条件1：牌堆摸完
    if(pos >= (int)cards.size()) {
        if(hp[0] <= 0) return 1;   // George胜利
        if(hp[1] <= 0) return 0;   // Peppa胜利
        return -1;  // 平局
    }

    int other = 1 - turn;

    // 摸牌阶段
    char card = cards[pos++];
    hand[turn] += card;

    // 出牌阶段 - 出杀
    bool killed = useKill(turn, other);
    if(hp[other] <= 0) {
        return turn;  // 当前玩家胜利
    }

    // 出牌阶段 - 出桃
    usePeach(turn);

    // 弃牌阶段
    discard(turn);

    // 递归到下一个玩家
    return dfs(other);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        int n;
        string s;
        cin >> n >> s;

        // 重置状态
        hand[0].clear();
        hand[1].clear();
        hp[0] = 4;
        hp[1] = 4;
        cards = s;
        pos = 0;

        int result = dfs(0);  // 从Peppa开始

        if(result == 0) cout << "Peppa\n";
        else if(result == 1) cout << "George\n";
        else cout << "Draw\n";
    }

    return 0;
}