#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;

#define INF 1e9
#define MAXNODES 1005
#define MAXEDGES 2005

vector<iii> EL(MAXEDGES);
int dist[MAXNODES], pred[MAXNODES];
int n, m;

int BellmanFord(int source){
  
  int i, j;


  // The following implementation of BF is borrowed from
  // CPBook. You can find their repository here:
  // https://github.com/stevenhalim/cpbook-code

  // To begin with, only the source is reachable
  // from the source (trivially),
  // and all other distances are infinity
  for(i = 0; i < n; i++){
    dist[i] = INF;
    pred[i] = -1;
  }

  dist[source] = 0;

  for(i = 0; i < n-1; i++)
  // repeat n-1 times (n = #vertices in G)
    for (auto &[u, v, w] : EL){
      // for every edge:
      if(dist[v] > dist[u] + w){
          // relax if tense
          dist[v] = dist[u]+w;
	        // update predecessor 
          pred[v] = u;
            
      }
    }
  
  // If some edge can be relaxed
  // even after all the iterations above
  // it indicates the presence of a 
  // negative-weight cycle... 
  
  for(auto &[u, v, w] : EL){
    if(dist[v] > dist[u]+w) return 0;
  }
  
  return 1;
}



int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int T; 
    cin >> T; 

    while(T--){
        
        cin >> n >> m; 
        int u,v,w; 
        
        EL.clear();
        EL.resize(m);
        
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            
            // This indicates an edge FROM u TO v
            // with weight t (#years transported)

            EL[i] = tie(u,v,w); 
        }
        
        // If BellmanFord returns 1,
        // there is NO negative weight cycle.
        if(BellmanFord(0)) 
            cout << "not possible" << endl; 
        else 
            cout << "possible" << endl;

    }
  
    return 0;
    
}