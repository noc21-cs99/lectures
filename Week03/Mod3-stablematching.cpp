#include <bits/stdc++.h>
#define ll long long int;
#include <vector>
using namespace std;

int getRank(vector<int> v, int person, int N){
    return N - (find(v.begin(), v.end(), person) - v.begin());
}

bool singlesRemaining(int *arr, int N){
    if(find(arr, arr + N, -1) == arr + N){
        return false;
    }
    return true; 
}

void match(int w, int m, int *MM, int *WW){
    WW[w] = m;
    MM[m] = w;
}

void solveSM(vector<int> *M, vector<int> *W, int N){
    int WE[N], ME[N];
    // WE[i] stores the current partner of woman #(i+1) 
    // ME[i] stores the current partner of man #(i+1)
    // The name of the partner is also 0-based indexing.
    
    for(int i = 0; i < N; i++){
        WE[i] = -1; ME[i] = -1;
    }
    while(singlesRemaining(WE,N)){
        for(int i = 0; i < N; i++){
            //Man #(i+1) proposes to his current top partner if single
            if(ME[i] == -1){
                int top = M[i].back() - 1;
                M[i].pop_back();
                if(WE[top] == -1){
                    match(top,i,ME,WE);
                }
                else{
                    int competitor = WE[top];
                    
                    //Lower ranks are better.
                    //Want i to have a smaller rank to trigger a breakup
                    if(getRank(W[top],competitor+1,N) > getRank(W[top],i+1,N)){
                        match(top,i,ME,WE);
                        ME[competitor] = -1;
                    }
                }
            }        
        }
    }
    for(int i = 0; i < N; i++){
        cout << i+1 << " " << ME[i]+1 << endl;
    }
}

int main(){

    #ifndef ONLINE_JUDGE 
        freopen("../in.txt", "r", stdin);
        freopen("../myout.txt", "w", stdout);
    #endif 

    int T;
    cin >> T; 

    while(T--){
        int N, person;
        cin >> N;

        vector<int> men[N], women[N];

        // Read the data for the women's preferences.
        for(int i = 0; i < N; i++){
            
            cin >> person;
            for(int j = 0; j < N; j++){
                cin >> person;
                women[i].push_back(person);
            }
            reverse(women[i].begin(),women[i].end());
        }
        // Read the data for the men's preferences.
        for(int i = 0; i < N; i++){
            
            cin >> person;
            for(int j = 0; j < N; j++){
                cin >> person;
                men[i].push_back(person);

            }
            reverse(men[i].begin(),men[i].end());

        }

        solveSM(men,women,N);


    }
    
}