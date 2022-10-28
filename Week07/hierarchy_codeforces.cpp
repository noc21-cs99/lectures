#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<b;i++)
#define sq(a) (a)*(a)
#define vi vector<int>
#define vll vector<ll>
#define iii tuple<int, int,int>

class UnionFind{
public:
    vi p,rank,setsize;
    int numsets;
    UnionFind(int n){
        p.assign(n,0);
        for(int i=0;i<n;i++){
            p[i]=i;
        }
        rank.assign(n,0);
        setsize.assign(n,1);
        numsets=n;
    }
    int findset(int n){
        if(p[n]==n){
            return n;
        }
        else{
            return p[n]=findset(p[n]);
        }
    }
    bool issameset(int i,int j){
        return findset(i)==findset(j);
    }
    void unionset(int i,int j){
        if(issameset(i,j)){
            return;
        }
        int x=findset(i);
        int y=findset(j);
        if(rank[x]>rank[y]){
            swap(x,y);
        }
        p[x]=y;
        if(rank[x]==rank[y]){
            rank[y]++;
        }
        setsize[y]+=setsize[x];
        numsets--;
    }
};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin>>t;
    vector<iii> edj;
    // while(t--){
        int n;
        cin>>n;
        vi a(n);
        rep(i,0,n){
            cin>>a[i];
        }
        int m;
        cin>>m;
        edj.clear();
        rep(i,0,m){
            int u,v,w;
            cin>>u>>v>>w;
            edj.pb({w,u-1,v-1});
        }
        sort(edj.begin(),edj.end());
        int mst_cost=0,num_taken=0;
        vi taken(n,0);
        UnionFind q(n);
        for(auto &[w,u,v]:edj){
            if(q.issameset(u,v)){
                continue;
            }
            if(a[u]>a[v]&&!taken[v]){
                mst_cost+=w;
                q.unionset(u,v);
                num_taken++;
                taken[v]=1;
            }
            if(num_taken==n-1){
                break;
            }
        }
        if(q.numsets==1){
            cout<<mst_cost<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    // }
}