#include <bits/stdc++.h>
using namespace std;
 
#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>
 
vector<vector<pair<int, int>>> AL; 
vi notvisited;
vll side;

// The standard DFS traversal
// enhanced with a tracker variable s
// that allows us to remember which
// "side" of the bipartition we are on.
 
void dfs(int u, int s){

  // u is on side s (s is 0 or 1)  
  // update the #vertices in side[s]
  side[s]++;

  // the rest of this is usual DFS...
  notvisited[u] = 0;
  for(auto &[v,w] : AL[u]){
    if(notvisited[v])
      //...but remember to switch sides
      //when you invoke dfs on v:
      dfs(v,1-s);
      //1 - s = 0 when s = 1
      //1 - s = 1 when s = 0
  }
}
 
int main(){
  // 0 vertices on both sides 
  // to begin with:
  side.assign(2,0);
  int n;
  cin >> n;

  AL.resize(n+1);
  notvisited.assign(n+1,1);

  for (int i = 1; i <= n-1; i++) {
    int u,v;  
    cin >> u >> v;
    AL[u].push_back(make_pair(v,0)); 
    AL[v].push_back(make_pair(u,0)); 
  }

  // initialize dfs on 1:
  dfs(1,0);
  // output a*b - (n-1), where
  // a = side[0] and b = side[1]
  // as discussed in the lecture.
  cout << (side[0]*side[1]) - (n-1)  << endl;
 
}