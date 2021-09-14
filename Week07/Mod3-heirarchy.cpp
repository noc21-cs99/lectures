#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

class UnionFind {
    private:
        vi p;
    public:

        // Initialization

        UnionFind(int N){
            // The goal here is to create N singleton sets.

            p.assign(N, 0);
            // To begin with, everyone is their own parent:
            for(int i = 0; i < N; i++)
                p[i] = i;
        }

        // FindSet(i): return the representative element of the set that i belongs to.

        int findSet(int i){
            // if already at a representative element,
            // signified by the fact that the parent pointer points to the element itself,
            // return;

            if(p[i] == i)
                return i;

            // otherwise find the representative of the parent,
            // but also perform path compression by pointing the current element
            // to the final representative:

            else
                return p[i] = findSet(p[i]);
        }

        // isSameSet(i,j): returns true if and only if i and j belong to the same set.

        bool isSameSet(int i, int j){
            // Observe that i and j belong to the same set
            // if and only if they have the same representative.
            return findSet(i) == findSet(j); 
        }

        void unionSet(int i, int j){
            if(isSameSet(i,j)) 
                return; 
            
            int x = findSet(i);
            int y = findSet(j);
            
            p[y] = x; 

        }
};


int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
 
 
    int q;
    for(int i = 0; i < n; i++){
        cin >> q;
    }    
 
    int m;
    cin >> m;
 
    vector<vi> EL;
    int a,b,c;
 
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        EL.push_back({c,a,b});
    }
 
    sort(begin(EL),end(EL));
    set<vi> mst;
 
    // 1-based indexing in the problem statement.

    UnionFind UF(n+1);                               
    int answer = 0;     
     
    for(auto &e: EL){
        
        if(mst.size() == n-1)
            break;
 
        int u = e[1], v = e[2];
        // u is willing to supervise v.

        if(UF.findSet(u) != UF.findSet(v) and v == UF.findSet(v)){
            mst.insert(e);
            answer += e[0];
            UF.unionSet(u,v);
        } 
    }
 
    if(mst.size() < n-1)
        cout << "-1";
    else
        cout << answer;

    
}