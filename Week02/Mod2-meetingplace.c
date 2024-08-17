#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//
// We can combine construction of the list R (or) L and the searching for the min (or) max element without constructing them by the following approach
//

// Finding the min(R[i])
double leftmost_right(int * position,int * velocity,int n,double k){
    double min = 1e9;
    double temp ;
    for(int i = 0;i< n;i++){
        temp = position[i] + velocity[i]*k;
        if(temp < min)min = temp;
    }
    return min;
}

// Finding the max(L[i])
double rightmost_left(int * position,int * velocity,int n,double k){
    double max = -1e9;
    double temp ;
    for(int i = 0;i< n;i++){
        temp = position[i] - velocity[i]*k;
        if(temp > max)max = temp;
    }
    return max;
}

//checks k seconds satisfies or not
//return 1 if satisfied
int is_fesible(int * position,int * velocity,int n,double k){
    return (leftmost_right(position,velocity,n,k) >= rightmost_left(position,velocity,n,k))?1:0;
}


int main(){
    // n         : the number of persons
    // position  : the pointer stores the array contains the n persons position
    // velocity  : the pointer stores the array contains the n persons velocity
    //
    // we create the arrays using malloc due to the large input sizes
    int n;
    int * position;
    int * velocity;
    scanf("%d",&n);
    position = (int *)malloc(sizeof(int)*n);
    velocity = (int *)malloc(sizeof(int)*n);
    //scanning for the inputs
    for(int i = 0;i<n;i++){
        scanf("%d",&position[i]);
    }
    for(int i = 0;i<n;i++){
        scanf("%d",&velocity[i]);
    }
    double l = 0.0,r = 1e9;
    double mid;
    while(fabs(r-l) >= 1e-6){
        mid = (l+r)/2;
        if(is_fesible(position,velocity,n,mid)) r = mid;
        else l = mid;
    }
    printf("%.10f",mid);
}
