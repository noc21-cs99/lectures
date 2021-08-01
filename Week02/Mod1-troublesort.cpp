#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>


int main(){
    
    std::ios::sync_with_stdio(false);
    
    int T;
    cin >> T; 

    for(int tcase = 1; tcase < T+1; tcase++){ 
        
        int N;
        cin >> N;        

        int num = 0;
        vi v; // This stores the input array
        for(int i = 0; i < N; i++){ 
            cin >> num;            
            v.push_back(num);
        }

        // Prepare to split the input array
        // into subarrays with odd and even indices

        vi odd, even;

        for(int i = 0; i < N; i++){
            if(i % 2 == 0)
                even.push_back(v[i]);
            else
                odd.push_back(v[i]);
        }

        // Sort the spliced arrays separately

        sort(even.begin(),even.end());
        sort(odd.begin(),odd.end());

        // Interleave back the two spliced and sorted arrays

        vi vsorted;

        for(int i = 0; i < N; i++){
            if(i % 2 == 0){
                vsorted.push_back(even[0]);
                even.erase(even.begin());
            }
            else{
                vsorted.push_back(odd[0]);
                odd.erase(odd.begin());
            }
        }


        // Check if the combined array is sorted or not
        int flag = -1;
        for(int i = 0; i < N; i++){
            if(i < N-1){
                // This identifies the first pair that is out of order
                if(vsorted[i] > vsorted[i+1]){ 
                    flag = i;
                    // When such a pair is found we break out of this loop
                    break; 
                }
            }
        }

        // Output based on whether the flag tracking inversions 
        // was triggered or not:
        
        if(flag == -1)
            cout << "Case #" << tcase << ": OK\n";
        else 
            cout << "Case #" << tcase << ": " << flag << "\n";
    }
    
}