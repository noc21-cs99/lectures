# You can use this function to sanity check your answer:
def cost(a):
  n = len(a)
  ans = 0
  for j in range(n-1):
      x = min(a[j:])
      i = a.index(x)
      ans += (i - j) + 1
      a = a[:j] + a[j:i+1][::-1] + a[i+1:]
        
  return ans


def construct(N,C,M):
    # Construct an array with elements from M...N
    # which, when reversorted, incurs a cost of C.
    # Precondition: C is an attainable cost. 

    if(N == 1):
        # The base case is easy but important!
        return str(M)
    else:
        if((C-1) >= N-2 and (C-1) <= N*(N-1)/2 - 1):
            # If C-1 is within valid bounds for N-1,
            # Then place X at the beginning and recurse directly.
            # Note that the minimum increases to M+1 in recursion. 
            
            return str(M) + " " + construct(N-1,C-1,M+1)
        
        else:
            # If we are not in the "easy" case above,
            # then reduce C by as much as you need to to be
            # within valid bounds in recursion:
            delta = int(C - N*(N-1)/2 + 1)

            # Now recurse with the appropriately adjusted cost 
            # (i.e, C-delta) and updated minimum (M+1):
            y = construct(N-1, C - delta, M+1)

            # Sneak M to the array obtained from recursion:
            smallarr = y.split(" ")
            newarr = [str(M)]
            newarr.extend(smallarr)

            # Reverse the subarray upto delta so that the cost of
            # getting M in its correct place is exactly delta,
            # and the reversal that puts M in its correct place
            # leads to the array "smallarr" which had cost C-delta
            # by the correctness of recursion,
            # so that the total cost is C, as desired:

            ans = " ".join(newarr[:delta][::-1] + newarr[delta:])
            return ans


T = int(input())

for case in range(1,T+1):
    
    N, C = list(map(int,input().strip().split()))
    
    if C < N-1 or C > N*(N+1)/2 - 1:        
        # If C is not within the appropriate bounds, 
        # reject immediately:
        print("Case #" + str(case) + ": IMPOSSIBLE")
    else:
        
        # Otheriwse, invoke the recursive mechanism
        # for constructing an array with the appropriate cost:
        A = construct(N,C,1)
        print("Case #" + str(case) + ": " + A)