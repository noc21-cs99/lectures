//Problem Link : https://codingcompetitions.withgoogle.com/codejam/round/0000000000433085/0000000000432fe1

#include <bits/stdc++.h>
 
using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define trav(a,x) for (auto& a : x)
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end())

const int MOD = 1e9 + 7;
const int inf = 1e9 + 10;
const long long INF = 1e18 + 10;

// Do not use an approximation - it won't be good enough
// with the large numbers involved. 

const double golden = (1 + sqrt(5)) / 2;

int main () {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int tc = 1; cin >> tc;
    for (int i = 1; i <= tc; i++) {
        double a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        long long ans = 0;

        // Remember to account for symmetry when working through the
        // conditionals and counting in the code below.

        for (int b = b1; b <= b2; b++) {
            if (floor(golden * b) < a1 || floor((golden - 1) * b) > a2)
                
                // When either the lower threshold is below a1 or the upper threshold is above a2,
                // all games are winning

                ans += (a2 - a1 + 1);
            else {

                // When the thresholds intercept the (a1,a2) interval,
                // we have to explicitly count the # of winning games.

                ans += max(0.0, a2 - floor(golden * b));
                ans += max(0.0, ceil((golden - 1) * b) - a1);
            }
        } 


        cout << "Case #" << i << ":" << ' ' << ans << '\n';
    }
}

//Know more about Golden ratio : https://en.wikipedia.org/wiki/Golden_ratio
