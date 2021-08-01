//Problem link - https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d12d7
//Solution by Scythe (Ayush gangwani)

#include <bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define ll              long long
#define ld              long double
#define get(a)          int a; cin>>a;
#define getl(a)         long long a; cin>>a;
#define put(a)          cout<<a<<" ";
#define putn(a)         cout<<a<<"\n";
#define rep(i,a,b)      for(int i=a; i<=b; i++)
#define repr(i,a,b)     for(int i=a; i>=b; i--)
#define vi              vector<long long>
#define vs              vector<string>
#define ump             unordered_map
#define mp              map
#define pq_max          priority_queue<long long>
#define pq_min          priority_queue< long long , vi , greater<long long> >
#define init(a,n)       vector<long long> a(n+1); for(int i=1; i<=n; i++) { cin>>a[i]; }
#define logarr(a)       for(auto i:a) { cout<<i<<" "; } cout<<"\n"; 
#define log(args...)    { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define token(str,ch)   (std::istringstream var((str)); vs v; string t; while(getline((var), t, (ch))) {v.pb(t);} return v;)
#define all(x)          x.begin(), x.end()
#define mid(l,r)        (l+(r-l)/2)
#define pii             pair<ll,ll>
#define mod             1000000007
#define N               100001
#define pb              emplace_back
#define pf              first
#define ps              second
#define bpc             __builtin_popcountll
#define ctz             __builtin_ctzll
#define clz             __builtin_clzll
#define precise(n)      cout<<fixed<<setprecision(n)

// #define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
//using namespace __gnu_pbds;
using namespace std;

vs tokenizer(string str,char ch) {std::istringstream var((str)); vs v; string t; while(getline((var), t, (ch))) {v.pb(t);} return v;}

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cout << *it << " = " << a << "\n";
    err(++it, args...);
}

void file_i_o()
{
    freopen("./tests/test01.txt", "r", stdin);
    freopen("./tests/output01.txt", "w", stdout);
}

//Ignore the long template, main code begins here
//Use of list STL container as the insertion operations
//in a list are more efficient than vectors

list<int> construct(int n, int c, int m)      
{
    //Helper function to construct the list
    //Function Arguments :
    //n : length of the required list.
    //c : cost of reversorting the required list.
    //m : minimum element in the list ,i.e., 
    // elements of the list can be m,m+1....n

    //Base Case 
    //If the length of the required list is 1,
    //we simply return a new list with only one element, i.e., m 
    if(n==1) return list<int> (1,m);        

    //If the cost required for current list is also a favourable cost for a list of lenght n-1, 
    // we simply build the list with lenght n-1 and cost c-1 
    // (as minimum cost for each iteration is 1) recusively,
    // and add the minimum element to the beginning of the list(reversal of which costs 1)
    if(c-1 >=n-2 and c-1<=(n*(n-1))/2 -1)
    {
        list<int> arr = construct(n-1,c-1,m+1);
        arr.push_front(m);
        return arr;
    }

    //If the cost for current list lies beyond the bounds for list of length n-1,
    //we calculate the minimum value x to be subtracted from current cost such that
    //c-x lies in the bounds for list of length n-1 and build the list with length n-1 and cost c-x recursively,
    //Now, we reverse the first x-1 elements of the list and add the minimum element at the position x,
    int x = c - (n*(n-1))/2 +1;
    list<int> arr = construct(n-1,c-x,m+1);
    list<int> ::iterator end = arr.begin();
    advance(end,x-1);
    reverse(arr.begin(),end); 
    arr.insert(end,m);
    return arr;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //file_i_o();
    int t=1;
    cin>>t;
    rep(i,1,t)
    {
        get(n) get(c)                      //get is custom macro for input
        put("Case #"<<i<<":")              //put is custom macro for output
        if(c<n-1 or c>(n*(n+1))/2 -1) 
        {
            putn("IMPOSSIBLE")             //putn is custom macro for output
            continue;
        }
        list<int> ans = construct(n,c,1);
        logarr(ans)                        //logarr is custom macro for printing stl containers
    }

    #ifndef ONLINE_JUDGE
    cerr<<"\ntime taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n";
    #endif
    return 0;
}
