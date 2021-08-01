#include <bits/stdc++.h>
using namespace std;
#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

double findmean(vll &pv, vll &v, int guess, int K, int N){
    if (K == 0)
        return v[guess];
    double sum;
    sum = (pv[guess+1] - pv[guess-K]) + (pv[N] - pv[N-K]); 
    return sum/(2*K+1);
}

int main(){
    #ifndef ONLINE_JUDGE 
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vll v; 
    int num;
    for(int i = 0; i < N; i++){
        cin >> num;
        v.push_back(num);
    }

    // Sort the array:
    
    sort(v.begin(), v.end());


    // Compute partial sums:

    vll pv;
    pv.push_back(0);
    for(int i = 0; i < N; i++){
        pv.push_back(pv.back()+v[i]);
    }


    // Sanity check, comment out later:

    // for(int i = 0; i < N; i++){
    //     cout << v[i] << "\t";
    // }

    // cout << "\n";

    // for(int i = 0; i < N; i++){
    //     cout << pv[i] << "\t";
    // }


    double answer = -1;
    double mean = 0, currmean = 0;
    int optguess, optK;

    for(int guess = 0; guess < N; guess++){

        // We want to pick K elements to the left of guess
        // and K elements from the end.
        // What's the largest possible value of K? 

        int range = min(guess, N-guess-1); 
        
        int L = 0, R = range, mid = (L+R)/2;

        while(R - L > 0){
            // mid is the current K.

            currmean = findmean(pv,v,guess,mid,N);
            // should we increase K? 

            int K = mid+1;
            int a = v[N-K];
            int b = v[guess-K];

            if(double(a+b)/2 <= currmean) // NO, K is an overestimate already.
                R = max(mid,L);
            else // YES, there's more potential for K! 
                L = min(mid + 1,R);     

            mid = (L+R)/2;
        }
        
        // When L = R, we have found K:

        mean = findmean(pv,v,guess,L,N);

        // If we are doing better than the best so far, update answers:

        if(mean - v[guess] > answer){
            answer = mean - v[guess];
            optguess = guess;
            optK = L;
        }
    }

    // Print answers:
    cout << optK*2 + 1 << "\n";
    
    for(int i = 0; i < optK; i++){
        cout << v[N-1-i] << " ";
    }
    
    for(int i = 0; i < optK+1; i++){
        cout << v[optguess-i] << " ";
    }
}