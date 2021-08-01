# Problem: Magic Ship
# URL: 

# Origin
x1, y1 = list(map(int,input().split()))

# Destination
x2, y2 = list(map(int,input().split()))

# Length of weather forecast
n = int(input())

# Weather forecast
S = input()
 

# Storing the impact of the winds:

x = 0; y = 0
WALKLIST=[(0,0)]

for s in S:
    # Adjust location 
    # according to the forecast
    if s=="U":
        y += 1
    elif s=="D":
        y -= 1
    elif s=="L":
        x -= 1
    elif s=="R":
        x += 1
    
    # Keep track of offsets after i days
    # for all 1 <= i <= n
    WALKLIST.append((x,y))


# Initial limits
L = 0
# No need to search beyond 2*10**14
R = 10**15

impossible = False
 
while L != R:
    
    mid = (L+R)//2
 
    # There are Q cycles of the n-day forecast
    # and rem remaining days after that,
    # with rem < n
    Q,rem = divmod(mid,n)

    # Computing (x3,y3)
    x3 = x1 + Q*x + WALKLIST[rem][0]
    y3 = y1 + Q*y + WALKLIST[rem][1]

    # Computing the Manhattan distance
    xoffset = abs(x2 - x3)
    yoffset = abs(y2 - y3)

    if (xoffset+yoffset) <= mid:
        R= mid
    else:
        L= mid + 1
 
    # If mids hit the upper limit, then there's no hope!
    if L==10**15:
        print(-1)
        impossible = True 

if not impossible:
    print(R)