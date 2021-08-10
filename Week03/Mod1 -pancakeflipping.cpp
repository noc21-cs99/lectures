//author : bhupathi07
//problem Link : https://codingcompetitions.withgoogle.com/codejam/round/00000000002017f7/0000000000201847
#include<bits/stdc++.h>
#include<iostream>
#include <cmath>
#include <vector>
using namespace std;

void testcase(int t)
{
	//s is the string encoding the input state of pancake
	//+ for happy and - for blank
	string s; 
	// size of pancake flipper(oversized)
	int k;
	cin >> s; cin >> k;

	int n = s.size(); //number of pancakes

	vector<int> obsolete_flips(n+1);
	for(int i = 0 ;i <= n ; i++)
	{
		obsolete_flips[i]=0;
	}

	int answer = 0,flipped;
	for(int j = 0 ; j < n-k+1 ; j++)
	{
		char state = s[j];
		//incorporate instructionos that we have so far by just adding the value from the previous cell
		obsolete_flips[j] += obsolete_flips[j-1];
		//count how many times the jth pancake does in fact get flipped
		flipped = answer - obsolete_flips[j];
		//figure out if a flip need to happen here 
		bool original_destroyed = (state == '+' and flipped%2 == 1);
		bool blank_not_fixed = (state == '-' and flipped%2==0);	

		if(original_destroyed or blank_not_fixed) //-> (plain side with even flips) or (happy side with odd flips)
		{
			//if flip need to happen
			//increment the answer
			answer++;
			// make it obsolete k steps later
			if(j < n-k+1)
			 	obsolete_flips[j+k] += 1;
		}
	}
	

       // checking remaining pancakes
	for(int j = n-k+1 ; j <= n; j++)
	{
		//similar to what happen before !

		obsolete_flips[j] += obsolete_flips[j-1];
		flipped = answer - obsolete_flips[j];
		char state = s[j];

		bool original_destroyed = (state =='+' and flipped%2==1);
		bool blank_not_fixed = (state == '-' and flipped%2 ==0);
		//if something is not right  it cannot be fixed anymore  , print the impossible as answer
		if(original_destroyed or blank_not_fixed)
		{
			cout<<"Case #"<<t<<": IMPOSSIBLE"<<endl;
			return;
		}
	}
	// if all k-1 pancakes at happy side print the number of flips you have to made to make all pancakes happyside(+)
	cout<<"Case #"<<t<<": "<<answer<<endl;
}
signed main()
{
	//processing testcases
	int tc;cin >> tc;
	for(int i = 1 ; i <= tc ; i++)
	{
		testcase(i);
	}
	return 0;
}
