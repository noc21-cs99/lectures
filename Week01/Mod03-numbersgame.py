import math

T = int(input())

# Do not use an approximation - it won't be good enough
# with the large numbers involved. 

golden = (1 + 5 ** 0.5) / 2

for j in range(1,T+1):
    
    a1, a2, b1, b2 = list(map(int,input().strip().split()))
    
    ans = 0
    
    # Remember to account for symmetry when working through the
    # conditionals and counting in the code below.

    for b in range(b1,b2+1):
      if(math.floor(golden*b) < a1 or math.floor((golden - 1)*b) > a2):
        # When either the lower threshold is below a1 or the upper threshold is above a2,
        # all games are winning
        ans += (a2 - a1 + 1)
      else:
        # When the thresholds intercept the (a1,a2) interval,
        # we have to explicitly count the # of winning games.
        ans += max(0, a2 - math.floor(golden*b))
        ans += max(0, math.ceil((golden - 1)*b) - a1)
        



    print("Case #" + str(j) + ": " + str(ans))