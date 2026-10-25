#include <iostream>
#include <vector>
#include <string>

using namespace std;
using ll = long long;

ll count_leq(const string& s, int m) {
    int L = s.size();
    vector<vector<ll>> dp(m, vector<ll>(2, 0));
    dp[0][1] = 1;

    for (int pos = 0; pos < L; ++pos) {
        vector<vector<ll>> next_dp(m, vector<ll>(2, 0));
        for (int rem = 0; rem < m; ++rem) {
            for (int tight = 0; tight <= 1; ++tight) {
                if (dp[rem][tight] == 0) continue;

                int limit = tight ? (s[pos] - '0') : 9;
                int low = (pos == 0) ? 1 : 0;

                for (int d = low; d <= limit; ++d) {
                    int newTight = tight && (d == limit);
                    int newRem = (rem * 10LL + d) % m;
                    next_dp[newRem][newTight] += dp[rem][tight];
                }
            }
        }
        dp = next_dp;
    }
    return dp[0][0] + dp[0][1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    int m;
    if (!(cin >> n >> m)) return 0;

    if (n == "1" || n.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    int L = n.size();
    ll answer = 0;

    for (int k = 1; k < L; ++k) {
        string prefix = n.substr(0, k);
        answer += count_leq(prefix, m);
    }

    ll same = count_leq(n, m);
    int nMod = 0;
    for (char c : n) {
        nMod = (nMod * 10LL + (c - '0')) % m;
    }
    if (nMod == 0) --same;

    answer += same;
    cout << answer << '\n';
    return 0;
}