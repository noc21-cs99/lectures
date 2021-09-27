// This code is adapted from:
// https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
// This code solves the BerSU Ball problem on CF:
// https://codeforces.com/problemset/problem/489/B

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

  void print_edges(){
      for(int i = 0; i < V; i++){
        cout << i << "'s neighbors: " << endl;
        for(auto x : AL[i]){
            cout << x << endl;
        }
        cout << endl;
      }   
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

  ll edmonds_karp(int s, int t) {
    
    ll maxf = 0;                                 // maxf stands for max_flow
    
    while (BFS(s, t)) {                          // an O(V*E^2) algorithm
    
      ll f = send_one_flow(s, t);                // find and send 1 flow f
      if (f == 0) break;                         // if f == 0, stop
      maxf += f;                                 // if f > 0, add to maxf
    
    }
    
    return maxf;
  }



};

int main() {

  #ifndef ONLINE_JUDGE 
      freopen("in.txt", "r", stdin);
      freopen("out.txt", "w", stdout);
  #endif
  
  std::ios::sync_with_stdio(false);

  int boys, girls;
  vi B, G; 

  cin >> boys; 
  for(int i = 0; i < boys; i++){
    int skill;
    cin >> skill; 
    B.push_back(skill);
  }
  
  cin >> girls; 
  for(int i = 0; i < girls; i++){
    int skill;
    cin >> skill; 
    G.push_back(skill);
  }
   
  max_flow maxf(boys + girls + 2);


    for(int i = 0; i < boys; i++){
      for(int j = 0; j < girls; j++){
        // For each boy-girl pair:
        if(abs(B[i] - G[j]) <= 1){
          // Add an edge if their skill levels differ by at most one.
          maxf.add_edge(i+1,boys+j+1,1); 
        }
      }
    }


    // Add a source that is adjacent to every boy-vertex.
    for(int i = 1; i < boys+1; i++){
        maxf.add_edge(0,i,1); 
    }

    // Add a sink that is adjacent from every girl-vertex.
    for(int i = 1; i < girls+1; i++){
        maxf.add_edge(boys+i,boys+girls+1,1); 
    }
    
    // A max flow is a maximum matching. 
    cout << maxf.edmonds_karp(0,boys+girls+1); 


  return 0;

}