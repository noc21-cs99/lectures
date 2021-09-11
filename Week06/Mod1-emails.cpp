#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

#define INF 1e9
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;

int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int T, cases=1;
    cin >> T;

    while(T--){
        
        int n,m,s,t;

        cin >> n >> m >> s >> t;
        vector<vii> AL(n, vii());
        int u, v, w;
        
        for (int i = 0; i < m; ++i)
        {
            cin >> u >> v >> w;
            // The graph here is undirected:
            AL[u].emplace_back(v, w);
            AL[v].emplace_back(u, w);
        }

        // The following implementation of Dijkstra is borrowed from
        // CPBook. You can find their repository here:
        // https://github.com/stevenhalim/cpbook-code

        vi dist(n, INF);
        dist[s] = 0;
        
        set<ii> pq;                                    // balanced BST version
        for (int u = 0; u < n; ++u)                    // dist[u] = INF
            pq.insert({dist[u], u});                   // but dist[s] = 0

        // The set data structure automatically
        // sorts the pairs by non-decreasing distance from s

        while (!pq.empty()) {                          // main loop
            
            auto [d, u] = *pq.begin();                 // finding closest unvisited u
            pq.erase(pq.begin());                      // simulating extraction
            
            for (auto &[v, w] : AL[u]) {               // all edges from u
            
                if (dist[u]+w >= dist[v])              // not improving
                    continue;                          // so skip
            
                pq.erase(pq.find({dist[v], v}));       // erase old pair
                dist[v] = dist[u]+w;                   // relax operation
                pq.insert({dist[v], v});               // enqueue better pair
            
            }
        }
                
        
        if(dist[t]!=INF){
            printf("Case #%d: %d\n",cases,dist[t]);
        }else{
            printf("Case #%d: unreachable\n",cases);
        }
        
        cases++;

    }


 return 0;   

}