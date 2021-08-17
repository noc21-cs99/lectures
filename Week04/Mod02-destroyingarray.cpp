#include <bits/stdc++.h>
using namespace std;
#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>
 
class UnionFind {
    private:
        vi p, rank, setSize;
        vll sumSet;
        int numSets;
    public:

        // Initialization

        UnionFind(int N){
            // We create space for N sets, but initially there are no sets.

            p.assign(N, -1);
                        
            // the height of all trees are not defined:
            rank.assign(N, -1);

            // the sizes of the individual sets are zero, as is sumset:
            setSize.assign(N, 0);
            sumSet.assign(N, 0);

            // the number of sets is N:
            numSets = 0;
        }

        void makeSet(int i, int x){
            p[i] = i;
            rank[i] = 0;
            setSize[i] = 1;
            sumSet[i] = x;
            numSets += 1;
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
        
        // sumOfSet(): returns the sum of all elements of the set

        ll sumOfSet(int i){
            return sumSet[findSet(i)]; 
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
            sumSet[y] += sumSet[x];
            numSets--;

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
    
    // The elements of the input array.
    vi arr(n+1,0);
    
    // state[i] is 0 if position i 
    // is currently destroyed/missing, 1 otherwise.
    vi state(n+1,0);
    
    // The destruction sequence. 
    // This is a permutation of 1 to n. 
    vi sequence(n);
    
    for(ll i = 1; i <= n; i++){
        cin >> arr[i];
    }
        
    for(int i = 0; i < n; i++){
        cin >> sequence[i];
    }
 
    // Initialize the DSU data structure
    // n+1 for 1-based indexing
    UnionFind UF(n+1);

    // Reverse the sequence of deletions.
    reverse(sequence.begin(),sequence.end());
 
    // Declare an array to track the answers.
    vll answers;

    // The last answer is always zero.
    answers.push_back(0);
    
    ll currentans = 0;
    
    for(auto x: sequence){

        // The x-th index is now occupied:
        state[x] = 1;

        // Create a singleton set out of the x-th index
        // with the sum being initialized to the value arr[x]
        UF.makeSet(x,arr[x]);
        
        // Merge with the left chunk if the location
        // to the immediate left is occupied:
        // remembering to avoid the edge case:
        if(x - 1 > 0 and state[x-1])
            UF.unionSet(x-1,x);
        
        // Merge with the right chunk if the location
        // to the immediate right is occupied,
        // remembering to avoid the edge case:
        if(x + 1 <= n and state[x+1])
            UF.unionSet(x,x+1);

        // Update the answer by checking against
        // the sum of the newly created set: 
        currentans = max(UF.sumOfSet(x),currentans); 

        // Record the answer for this stage:
        answers.push_back(currentans);
    }
    
    // The last answer (the sum of the whole array)
    // is not required:

    answers.pop_back();

    // Remember to reverse the lsit of answers! 
    reverse(begin(answers),end(answers));
    
    for(auto x: answers)
        cout << x << endl;
 
}