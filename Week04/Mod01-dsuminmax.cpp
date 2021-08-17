#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

class UnionFind {
    private:
        vi p, rank, setSize, maxSet, minSet;
        int numSets;
    public:

        // Initialization

        UnionFind(int N){
            // The goal here is to create N singleton sets.

            p.assign(N, 0);
            // To begin with, everyone is their own parent:
            for(int i = 0; i < N; i++)
                p[i] = i;
            
            // the height of all trees are zero:
            rank.assign(N, 0);

            // the sizes of the individual sets are one:
            setSize.assign(N, 1);

            // the maximum and minimum element in the set is the element itself:

            maxSet.assign(N, 0);
            minSet.assign(N, 0);
            for(int i = 0; i < N; i++){
                maxSet[i] = i;            
                minSet[i] = i;            
            }

            // the number of sets is N:
            numSets = N;
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

        // sizeOfSet(i): returns the size of the set that the element i belongs to.

        int sizeOfSet(int i){
            return setSize[findSet(i)];
        }
        
        // numDisjointSets(): returns the number of sets being maintained currently.

        int numDisjointSets(){
            return numSets; 
        }
        
        // maxInSet(): returns the maximum element of the set

        int maxInSet(int i){
            return maxSet[findSet(i)]; 
        }
        
        // minInSet(): returns the minimum element of the set

        int minInSet(int i){
            return minSet[findSet(i)]; 
        }

        void unionSet(int i, int j){
            if(isSameSet(i,j)) 
                return; 
            
            int x = findSet(i);
            int y = findSet(j);

            if(rank[x] > rank[y])
                swap(x,y);
            
            p[x] = y; 

            if (rank[x] == rank[y])
                rank[y]++;
            
            setSize[y] += setSize[x];
            maxSet[y] = max(maxSet[x],maxSet[y]);
            minSet[y] = min(minSet[x],minSet[y]);
            numSets--;

        }


};


int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    
    UnionFind UF(n+1);

    while(m--){
        string S;
        cin >> S;


        if(S == "union"){
            int x,y;
            cin >> x >> y;
            UF.unionSet(x,y);
        }          
        else{
            int x;
            cin >> x;
            cout << UF.minInSet(x) << " " << UF.maxInSet(x) <<  " " << UF.sizeOfSet(x) << endl;
        }
    }

    return 0;
}