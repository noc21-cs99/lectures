# This is the number of people:
n = int(input())

# Read the location array:
x = [int(x) for x in input().split()]

# Read the velocity array:
v=[int(x) for x in input().split()]

def rightmost_left_ep(t):
    return max([x[i]-(v[i]*t) for i in range(n)])

def leftmost_right_ep(t):
    return min([x[i]+(v[i]*t) for i in range(n)])

def is_feasible(K):
    return rightmost_left_ep(K) <= leftmost_right_ep(K)

L,R = 0.0, 1e9

while abs(R-L)>1e-6:
    mid=(L+R)/2
    
    # If mid is feasible, try with less time.
    # So truncate the top half of the search space
    if(is_feasible(mid)): R=mid
    
    # If mid is infeasible, try with more time.
    # So truncate the bottom half of the search space
    else: L=mid
        
print(mid)