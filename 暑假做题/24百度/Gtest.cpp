//
// Created by 28447 on 2026/9/9.
//
#include <bits/stdc++.h>
using namespace std;

vector<string> hand(2);
vector<int> hp(2, 4);
string cards;
int pos;

// 深拷贝当前状态
struct GameState {
    vector<string> hand;
    vector<int> hp;
    int pos;

    GameState() {}
    GameState(const GameState& other) {
        hand = other.hand;
        hp = other.hp;
        pos = other.pos;
    }
};

GameState saveState() {
    GameState state;
    state.hand = hand;
    state.hp = hp;
    state.pos = pos;
    return state;
}

void restoreState(const GameState& state) {
    hand = state.hand;
    hp = state.hp;
    pos = state.pos;
}

// 弃牌：优先弃闪(D)，再弃桃(P)
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

// 正常使用桃回血
bool usePeach(int player) {
    if(hp[player] >= 4) return false;
    size_t posP = hand[player].find('P');
    if(posP != string::npos) {
        hand[player].erase(posP, 1);
        hp[player]++;
        return true;
    }
    return false;
}

// 濒死用桃自救
bool usePeachEmergency(int player) {
    size_t posP = hand[player].find('P');
    if(posP != string::npos) {
        hand[player].erase(posP, 1);
        hp[player]++;
        return true;
    }
    return false;
}

// 出杀，返回是否击杀对手
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
                return true;
            }
        }
        return true;
    }
}

// 判断胜负：返回1表示Peppa赢，0表示George赢，-1表示平局
int checkResult() {
    if(hp[0] <= 0 && hp[1] <= 0) return -1;
    if(hp[0] <= 0) return 0;   // George赢
    if(hp[1] <= 0) return 1;   // Peppa赢
    return -1;  // 未结束
}

// 博弈搜索：双方都用最优策略
int dfs(int turn) {
    // 终止条件1：牌堆摸完
    if(pos >= (int)cards.size()) {
        return checkResult();
    }

    int other = 1 - turn;
    int best = (turn == 0) ? -2 : 2;

    // ===== 先摸牌 =====
    char card = cards[pos++];
    hand[turn] += card;

    // ===== 尝试所有出牌策略 =====

    // 策略1：什么都不出
    {
        GameState saved = saveState();
        int result = dfs(other);
        best = (turn == 0) ? max(best, result) : min(best, result);
        restoreState(saved);
    }

    // 策略2：出杀
    size_t posK = hand[turn].find('K');
    if(posK != string::npos) {
        GameState saved = saveState();

        bool killed = useKill(turn, other);
        // 如果击杀对手，直接返回胜利
        if(hp[other] <= 0) {
            return turn;
        }

        int result = dfs(other);
        best = (turn == 0) ? max(best, result) : min(best, result);
        restoreState(saved);
    }

    // 策略3：出桃（回血）
    size_t posP = hand[turn].find('P');
    if(posP != string::npos && hp[turn] < 4) {
        GameState saved = saveState();

        hand[turn].erase(posP, 1);
        hp[turn]++;

        int result = dfs(other);
        best = (turn == 0) ? max(best, result) : min(best, result);
        restoreState(saved);
    }

    // ===== 弃牌阶段 =====
    // 注意：弃牌是强制的，不需要尝试不同策略
    discard(turn);

    return best;
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

        hand[0].clear();
        hand[1].clear();
        hp[0] = 4;
        hp[1] = 4;
        cards = s;
        pos = 0;

        int result = dfs(0);

        if(result == 1) {
            cout << "Peppa\n";
        } else if(result == 0) {
            cout << "George\n";
        } else {
            cout << "回家吃饭\n";
        }
    }

    return 0;
}