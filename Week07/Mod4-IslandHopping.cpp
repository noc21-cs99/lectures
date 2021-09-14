#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>
#define iii tuple<double, int, int>

const int MAXN = 64;
double X[MAXN], Y[MAXN], M[MAXN];
double inhabitants[MAXN];

class UnionFind {
    private:
        vi p, rank, setSize;
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

        void unionSet(int i, int j){
            if(isSameSet(i,j)) 
                return; 
                          
            int x = findSet(i);
            int y = findSet(j);

            if (setSize[x] > setSize[y]) {
                p[y] = x;
                inhabitants[x] += inhabitants[y];
                setSize[x] += setSize[y];
            } else {
                p[x] = y;
                inhabitants[y] += inhabitants[x];
                setSize[y] += setSize[x];
            }
            numSets--;
        }
};

int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);


    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    int n, cases = 0;
    vector<iii> EL;

	while (true) {
        cin >> n;
        if(n){
            for (int i = 0; i < n; i++)
                cin >> X[i] >> Y[i] >> M[i];

            EL.clear();
            
            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    double wt = hypot(X[i] - X[j], Y[i] - Y[j]);
                    EL.push_back({wt,i,j});
                }
            }

            sort(EL.begin(), EL.end());

            double div = 0, sum = 0;
            int u, v;

            UnionFind UF(n);   

            for (int i = 0; i < n; i++)
                inhabitants[i] = M[i], div += M[i];
            
            // Keep track of the total number of inhabitants 
            // in the group of isalnds in every component 
            // using inhabitants.

            for (auto &[w, u, v] : EL) {
                if (UF.findSet(u) != UF.findSet(v)) {
                    // if u's component has the main island
                    // then v's connection time, and the connection time
                    // of all vertices in v's component
                    // need to be updated.
                    // We directly add w * (inhabitants[v]) to the sum;
                    // recalling that w is t_i for all islands in v's component
                    // and inhabitants[v] denotes the total number of inhabitants in these islands:
                    if (UF.findSet(u) == UF.findSet(0))
                        sum += inhabitants[UF.findSet(v)] * w;

                    // As above, swap the roles of u and v
                    if (UF.findSet(v) == UF.findSet(0))
                        sum += inhabitants[UF.findSet(u)] * w;
                        
                    UF.unionSet(u, v);
                }

            }
            
            cases++;

            cout << "Island Group: " << cases << " Average " << sum / div << endl << endl; 
        }
        else
            break;
	}
	return 0;
}