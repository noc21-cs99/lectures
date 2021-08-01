//Problem Link : https://szkopul.edu.pl/problemset/problem/w2LtiQBD8_pL0PTNosP1F83u/site/?key=statement

#include <stdio.h>

int main(void) {
    
    long long n;
    scanf("%lld",&n);
    // This function is used to count the number of one’s(set bits) in an long long data type.
    if (__builtin_popcountll(n) == 1)
    {
    printf("TAK");
    }
    else{
    printf("NIE");
    }
    return 0;
  
}
//https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
