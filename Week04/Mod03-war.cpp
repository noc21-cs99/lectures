#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

class UnionFind {
    private:
        vi rank, friends;
    public:
        vi enemies; 
        
        // Initialization
        UnionFind(int N){
            // The goal here is to create N singleton sets.

            friends.assign(N, 0);
            // To begin with, everyone is their own friend:
            for(int i = 0; i < N; i++)
                friends[i] = i;
            
            // The height of all trees are zero:
            rank.assign(N, 0);

            // Nobody is an enemy of themselves
            enemies.assign(N, -1); 
        }

        // FindSet(i): return the representative element of the set that i belongs to.

        int findSet(int i){
            // if already at a representative element,
            // signified by the fact that the parent pointer points to the element itself,
            // return;

            if(friends[i] == i)
                return i;

            // otherwise find the representative of the parent,
            // but also perform path compression by pointing the current element
            // to the final representative:

            else
                return friends[i] = findSet(friends[i]);
        }

        // isSameSet(i,j): returns true if and only if i and j belong to the same set.

        bool isSameSet(int i, int j){
            // Observe that i and j belong to the same set
            // if and only if they have the same representative.
            return findSet(i) == findSet(j); 
        }     

        bool areFriends(int x, int y){
            return (findSet(x) == findSet(y)) ? true : false;
        }

        bool areEnemies(int x, int y){
            x = findSet(x);
            y = findSet(y); 
            return (x == enemies[y] or y == enemies[x]) ? true : false;
        }

        void unionSet(int i, int j){
            if(isSameSet(i,j)) 
                return; 
            
            int x = findSet(i);
            int y = findSet(j);

            if(rank[x] > rank[y])
                swap(x,y);
            
            friends[x] = y; 

            if (rank[x] == rank[y])
                rank[y]++;
            
        }


};



int main() {


    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int n = 0;
    cin >> n;
	
    int op, x, y; 
    int query = 0;

    UnionFind UF(n);

    while(cin >> op) {
    
        query++;
        cin >> x >> y; 
        
        if(op == 1){ 
            // Already enemies, invalid query.
            if(UF.areEnemies(x,y))
                cout << "-1" << endl;
            else
            {   
                x = UF.findSet(x);
                y = UF.findSet(y);

                // Case 1. x and y have no enemies, simple union will do.
                if(UF.enemies[x] == -1 and UF.enemies[y] == -1)
                    UF.unionSet(x,y);   
                
                // Case 2a. x has an enemy but y does not.
                if(UF.enemies[x] != -1 and UF.enemies[y] == -1)
                {
                    int z = UF.enemies[x];
                    UF.unionSet(x,y);   
                    x = UF.findSet(x);
                    UF.enemies[z] = x;
                    UF.enemies[x] = z;
                }
                // Case 2b. y has an enemy but x does not.
                if(UF.enemies[x] == -1 and UF.enemies[y] != -1)
                {
                    int z = UF.enemies[y];
                    UF.unionSet(x,y);   
                    x = UF.findSet(x);
                    UF.enemies[z] = x;
                    UF.enemies[x] = z;
                }

                // Case 3. x and y both have enemies.
                if(UF.enemies[x] != -1 and UF.enemies[y] != -1)
                {
                    int a = UF.enemies[x];
                    int b = UF.enemies[y];
                    UF.unionSet(x,y);   
                    UF.unionSet(a,b);   
                    a = UF.findSet(a);
                    x = UF.findSet(x);
                    UF.enemies[x] = a;
                    UF.enemies[a] = x;
                }


            }
        } 

        if(op == 2){
            // Already friends, invalid query.
            if(UF.areFriends(x,y))
                cout << "-1"  << endl;
            else
            {
                x = UF.findSet(x);
                y = UF.findSet(y);

                // Case 0. Already mutual enemies, nothing to do.
                if(UF.enemies[x] == y and UF.enemies[y] == x)
                    continue;

                // Case 1. Both x and y have no enemies currently.
                if(UF.enemies[x] == -1 and UF.enemies[y] == -1){
                    UF.enemies[x] = y;
                    UF.enemies[y] = x;
                }

                // Case 2a. x has an enemy and y does not.
                if(UF.enemies[x] != -1 and UF.enemies[y] == -1){
                    
                    int z = UF.enemies[x];
                    
                    UF.unionSet(z,y);
                    int w = UF.findSet(y);
                    // New leader may be y or z.
                    UF.enemies[w] = x;
                    UF.enemies[x] = w;
                }

                // Case 2b. y has an enemy and x does not.
                if(UF.enemies[y] != -1 and UF.enemies[x] == -1){
                    
                    int z = UF.enemies[y];
                    
                    UF.unionSet(z,x);
                    int w = UF.findSet(x);
                    // New leader may be y or z.
                    UF.enemies[w] = y;
                    UF.enemies[y] = w;
                }

                // Case 3. Both x and y have enemies (NOT each other).
                if(UF.enemies[x] != -1 and UF.enemies[y] != -1){

                    int a = UF.enemies[x];
                    int b = UF.enemies[y];

                    // a and y have a common enemy in x.
                    UF.unionSet(a,y);

                    // b and x have a common enemy in y.
                    UF.unionSet(b,x);

                    int p = UF.findSet(x);
                    int q = UF.findSet(y);

                    UF.enemies[p] = q;
                    UF.enemies[q] = p;

                }


            }
        } 

        if(op == 3){
            if(UF.areFriends(x,y))
                cout << "1" << endl;
            else
                cout << "0" << endl;            
        } 

        if(op == 4){
            if(UF.areEnemies(x,y))
                cout << "1" << endl;
            else
                cout << "0" << endl;  
        }

    }

	return 0;
}