
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll pow (int k) {
    ll res=1;
    for (int i=0; i< k ;i++) res*=10;
    return res;
}
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int A, B, C;
        cin >> A >> B >> C;
        ll lowA=pow(A-1);ll highA=pow(A)-1;
        ll lowB=pow (B-1);ll highB=pow (B)-1;
        ll lowC=pow(C-1);ll highC=pow(C)-1;
        ll minSum = lowA + lowB;
        ll maxSum = highA + highB;
        if (minSum>highC || maxSum<lowC) {
            cout<<"-1"<<'\n';
            continue;

        }
        ll ans=0;
        for (ll a = lowA; a<=highA; a++) {
            // b ÐèÒªÂú×ã£ºlowC <= a + b <= highC
            // ¼´£ºlowC - a <= b <= highC - a
            ll b_low = max(lowB, lowC-a);
            ll b_high = min(highB, highC-a);
            if (b_low<= b_high) {
                ans+= b_high - b_low +1;

            }
        }
        cout << ans << '\n';

    }
    return 0;
}