// This code is borrowed from:
// https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
// This solves FASTFLOW on SPOJ
// https://www.spoj.com/problems/FASTFLOW/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;                             // large enough

class max_flow {
private:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;

  bool BFS(int s, int t) {                       // find augmenting path
    
    d.assign(V, -1);                             // initialize distance array
    d[s] = 0;                                    // s is the source, so d[s] = 0
    
    queue<int> q({s});                           // load s on the queue 
    
    p.assign(V, {-1, -1});                       // record BFS sp tree

    while (!q.empty()) {
    
      int u = q.front(); q.pop();                // current vertex to be processed

      if (u == t) break;                         // stop as sink t reached
     
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        
        if ((cap-flow > 0) && (d[v] == -1)){     // positive residual edge + unexplored
            
            d[v] = d[u]+1;                       // set distance
            q.push(v);                           // push on queue
            p[v] = {u, idx};                     // set parent information
        
        }
      }
    }
    
    return d[t] != -1;                           // has an augmenting path
  
  }

  ll send_one_flow(int s, int t, ll f = INF) {   // send one flow from s->t
    
    if (s == t) return f;                        // bottleneck edge f found
    
    auto &[u, idx] = p[t];    
    auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
    
    ll pushed = send_one_flow(s, u, min(f, cap-flow));    
    flow += pushed;
    
    auto &rflow = get<2>(EL[idx^1]);             // back edge
    rflow -= pushed;                             // back flow
    
    return pushed;
    
  }


public:
  max_flow(int initialV) : V(initialV) {
    EL.clear();
    AL.assign(V, vi());
  }

  // if you are adding a bidirectional edge u<->v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    
    EL.emplace_back(v, w, 0);                    // u->v, cap w, flow 0
    AL[u].push_back(EL.size()-1);                // remember this index
    
    EL.emplace_back(u, directed ? 0 : w, 0);     // back edge
    AL[v].push_back(EL.size()-1);                // remember this index
  
  }

  ll dinic(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(V^2*E) algorithm
      last.assign(V, 0);                         // important speedup
      while (ll f = DFS(s, t))                   // exhaust blocking flow
        mf += f;
    }
    return mf;
  }

  ll DFS(int u, int t, ll f = INF) {             // traverse from s->t
    if ((u == t) || (f == 0)) return f;
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) { // from last edge
      auto &[v, cap, flow] = EL[AL[u][i]];
      if (d[v] != d[u]+1) continue;              // not part of layer graph
      if (ll pushed = DFS(v, t, min(f, cap-flow))) {
        flow += pushed;
        auto &rflow = get<2>(EL[AL[u][i]^1]);     // back edge
        rflow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

};

int main() {

  #ifndef ONLINE_JUDGE 
      freopen("in.txt", "r", stdin);
      freopen("out.txt", "w", stdout);
  #endif
  
  std::ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m; 

  
  max_flow maxf(n+1);

  for(int i = 0; i < m; i++){
    int u, v, cap; 
    cin >> u >> v >> cap; 
    maxf.add_edge(u,v,cap,false); 

  }
  
  cout << maxf.edmonds_karp(1,n); 
  return 0;

}