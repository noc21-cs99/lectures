#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>
#define iii tuple<int, int, int>
#define ii pair<int, int>
#define vii vector<ii>


vi taken; 
// to track seen vertices and avoid cycles 

vector<vii> AL;

int main(){


    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);
    int s;
	cin >> s;


	while(s--){	
        priority_queue<ii, vector<ii>, greater<ii>> pq;     // priority queue
        AL.clear();
        taken.clear();
		
        int n; 
        cin >> n; 

        AL.assign(n+1,vii());

		for(int i = 0; i < n; i++){
			
            string temp;
			cin >> temp;

			int degree;
			cin >> degree;
			
            while(degree--){
				
                int j,w;
				cin >> j >> w;

                AL[i].emplace_back(j-1, w);
			
            }
		}
		
        taken.assign(n, 0);                            // no vertex is taken
        
        taken[0] = 1;                                  // mark the source as taken

        for (auto &[v,w] : AL[0])                      // process all neighbors of the source
            pq.push({w,v});                            // assuming no self-loops here! 
        
        int mst_cost = 0, num_taken = 0;               // no edge has been taken
        
        while (!pq.empty()) {                          // up to O(E)
        
            auto [w, u] = pq.top(); pq.pop();          // considering the cheapest edge incident to a taken vertex
            
            if (taken[u]) continue;                    // the other endpoint already taken, skipped
            
            taken[u] = 1;                              // this is the best cut edge at this point, take it
            mst_cost += w;                             // add it's weight to the MST cost
            for (auto &[v,w] : AL[u])                  // process all non-taken neighbors of u
                if (!taken[v])
                pq.push({w,v});                        // add their weights to the PQ.

            
            num_taken++;                               // 1 more edge is taken
            if (num_taken == n-1) break;               // optimization
        
        }        
        
        cout << mst_cost << endl;        
    }
}