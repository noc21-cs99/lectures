#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

vector<vector<pair<int, int>>> AL; 
vi notvisited;
bool flag = true;

void dfs(int u){
        notvisited[u] = 0;
        for(auto &[v,w] : AL[u]){      
          if(notvisited[v]){
            dfs(v);
          }
          else{
            // Some vertex was visited more tha once
            // from the root of the current DFS traversal.
            // The first visit gives us one path;
            // the second visit is a second path. 
            flag = false;
            return;
          }
        }
}

bool solve(int n){
  // Guess the top of the diamond.
  for(int i = 1; i <= n; i++){
    // Clean up the notvisited array
    // for this particular guess.
    notvisited.assign(n+1,1);

    // Execute modified DFS:
    dfs(i);

    // If DFS detected a common meeting point,
    // we are done:
    if(!flag)
      return true;
  }
  return false;
}

int main(){


    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    for(int t = 1; t <= T; t++){
      int n;
      cin >> n;

      // Clear out the adjacency list
      // and the notvisited array.

      AL.clear();
      AL.resize(n+1);

      notvisited.assign(n+1,1);

      // Read the input into the global
      // adjacency list.
      
      for(int i = 1; i <= n; i++){
        int k;  
        cin >> k;
        for(int q = 1; q <= k; q++){
          int v;
          cin >> v;
          AL[i].push_back(make_pair(v,0)); 
        }
      }

      // The heavy lifting happens here.

      bool ans = solve(n);      

      if(ans)
        cout << "Case #" << t << ": " << "Yes" << endl;
      else
        cout << "Case #" << t << ": " << "No" << endl;
      
      // Remember to reset the flag
      // for the next test case.
      flag = true;
   
    }

}