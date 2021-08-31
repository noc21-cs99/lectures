#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

vector<vector<pair<int, int>>> AL; 
vi notvisited;
vi dist; 
bool flag = true;
vi p;

int main(){


    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    for(int t = 1; t <= T; t++){
    // Outer loop for the test cases.

        int n, m;
        cin >> n >> m;

        // Reset the adjacency lists and the
        // notvisited and distance arrays

        AL.clear();
        AL.resize(n+1);

        notvisited.assign(n+1,1);
        dist.assign(n+1,1e9);

        // Read in the input.
      
        for(int i = 1; i <= m; i++) {
          int u,v;  
          cin >> u >> v;
          AL[u].push_back(make_pair(v,0)); 
          AL[v].push_back(make_pair(u,0)); 
        }

        // Make a plan to store the vertices
        // encountered at odd and even layers
        // separately.
    
        vi odd, even;
        
        // Introduce variables to track the
        // #of vertices encountered so far
        // of each type.
        
        int O = 0, E = 0; 
        
        // Standard BFS items.
        
        queue<int> q; q.push(1); 
        dist[1] = 0;
        even.push_back(1);

        // First layer is "even".
        // Just a convention! 

        E++; 

        // Usual BFS initalization.

        notvisited.assign(n+1, 1);
        notvisited[1] = 0;                   
        
        while (!q.empty()) {

            int u = q.front(); q.pop();

            for (auto &[v, w] : AL[u]) {                 
                if (notvisited[v]) {
                    notvisited[v] = 0;                        
                    q.push(v);        
                    dist[v] = dist[u] + 1;

                    // Update O/E/odd/even
                    // based on the parity of the distance.

                    if(dist[v] % 2 == 0){
                        E++; even.push_back(v);
                    }
                    else{
                        O++; odd.push_back(v);
                    }
                }
            }
        }
        
        // Output all vertices in the smaller set.

        if(O <= E){
            cout << O << endl;
            for(auto &x : odd)
                cout << x << " ";
        }else{
            cout << E << endl;
            for(auto &x : even)
                cout << x << " ";
        }
        cout << endl;

    }
}
