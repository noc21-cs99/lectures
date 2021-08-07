//Problem link - https://codeforces.com/problemset/problem/1117/C
//Solution by - Ayush Gangwani

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

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //file_i_o();
    int t=1;
    while(t--)
    {
        //Taking the input
        getl(sx) getl(sy) getl(ex) getl(ey)
        getl(n)
        string s; cin>>s;

        //Declaring the required variables
        //As discussed in the lecture, the upper bound of the search space is n*D
        //where D is the manhattan distance between the start and the end point 
        ll lo=0, hi = (abs(sx-ex) + abs(sy-ey))*n, ans=-1;

        //vectors to store the x and y offsets 
        //Here devx[i] denotes the offset in x(i.e. the change in x-coordinate after i days)
        // and devy[i] denotes the offset in y(i.e. the change in y-coordinate after i days)
        vector<ll> devx(n+1,0);
        vector<ll> devy(n+1,0);

        //Pre - processing the offsets corresponding to the x and y coordinates 
        //This helps to determine the change in x and y coordinates in O(1) 
        rep(i,0,s.length()-1)
        {
            devx[i+1] = devx[i];
            devy[i+1] = devy[i];
            if(s[i] == 'U') devy[i+1]++;
            else if(s[i] == 'D') devy[i+1]--;
            else if(s[i] == 'L') devx[i+1]--;
            else devx[i+1]++;
        }

        //Binary Search Logic
        while(hi>=lo)
        {
            ll mid = mid(lo,hi);

            ll q = mid/n;                      // q determines the no of full cycles of n days 
            ll r = mid%n;                      // r determines the no of days which are not accounted in the 'q' cycles

            ll x3 = sx + devx[n]*q + devx[r];  // x3 and y3 determine the x and y coordinates after m days 
            ll y3 = sy + devy[n]*q + devy[r];  // only due to the wind(i.e, without the captain's influence) 
            ll d = abs(ex-x3) + abs(ey-y3);    //d is the manhattan distance between the end point and the point(x3,y3)

            if(d<=mid)                         //if we can get to the end point from (x3,y3) by performing <=mid no of 
            {                                  //operations, then mid is a possible ans, also any k>mid is a possible 
                ans = mid;                     //ans, thus we narrow down our search space and discard the part[mid,hi] 
                hi = mid-1;
            }
            else lo = mid+1;                   // Else, we start searching in [mid+1,hi] and discard [lo,mid].
        }
        putn(ans)
    }

    #ifndef ONLINE_JUDGE
    cerr<<"\ntime taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n";
    #endif
    return 0;
}
