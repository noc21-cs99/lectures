#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<b;i++)
#define sq(a) (a)*(a)
#define vi vector<int>
#define mp make_pair
#define INF 99999

vector<vector<int>> adj;
vector<int> visited;

void dfs(int n){
    visited[n]++;
    for(auto i:adj[n]){
        if(!visited[i]){
            dfs(i);
        }
        else{
            visited[i]++;
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    for(int hell=1;hell<=t;hell++){
        int n;
        cin>>n;
        adj.resize(n);
        rep(i,0,n){
            int k;
            cin>>k;
            adj[i].clear();
            if(k>0){
                rep(j,0,k){
                    int var;
                    cin>>var;
                    adj[i].pb(var-1);
                }
            }
        }
        // rep(i,0,adj.size()){
        //     cout<<adj[i].size();
        //     for(auto k:adj[i]){
        //         cout<<k<<" ";
        //     }
        //     cout<<endl;
        // }
        int flag=0;
        for(int i=0;i<n;i++){
            visited.assign(n,0);
            dfs(i);
            // for(auto j:visited){
            //     cout<<j<<" ";
            // }
            // cout<<endl;
            for(auto j:visited){
                if(j>1){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            cout<<"Case #"<<hell<<": "<<"YES\n";
        }
        else{
            cout<<"Case #"<<hell<<": "<<"NO\n";
        }
    }
}