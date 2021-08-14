//*****************************************
//******* #######      #########   ********
//******* #     #      #           ********
//******* #     #      #           ********
//******* #     #      #           ********
//******* #######      #########   ********
//******* ##                   #   ********
//******* # #                  #   ********
//******* #   #                #   ********
//******* #     #      #########   ********
//*****************************************
//*****************************************

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <vector>
#define e "\n"
#define f first
#define s second
#define pb push_back
#define PI 3.1415926535
#define deb(x) cout<<x<<endl;
#define debs(x) cout<<" "<<x<<" ";
#define fr(j,p) for (int i=j; i<p ;i++)
#define rep(i,j,n) for (int i=j ; i<n ; i++)
#define repn(i,n,j) for (int i=n ; i>j ; i--)
#define mem(x,val) memset((x),(val),sizeof(x));
#define INF  std::numeric_limits<int>::max()
#define precision std::cout << std::setprecision(6) << std::fixed;
#define fastScan ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

const long long md=1000000007 ;

bool custom_key(pair<int,int> p1 , pair<int,int> p2)
{
    return p1.second<p2.second;
}

int main()
{
   fastScan
   precision
    int n , m;
    cin>>n>>m;

    vector<pair<int,int>> requests(m);

    fr(0,m)
    {
        cin>>requests[i].first>>requests[i].second;
    }

    sort(requests.begin() , requests.end() , custom_key);

    int ans = 0;
    int lastbridge = -1;

    fr(0,m)
    {
        if (lastbridge > requests[i].first)
            continue ;
        else {
            lastbridge = requests[i].second;;
            ans += 1;
        }
    }

    cout<<ans<<e;

    return 0;
}
