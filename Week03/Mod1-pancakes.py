T = int(input())

for C in range(1,T+1):
        
    X = input().split()
    
    # S is the string encoding the input state of the pancakes: 
    # + for happy and - for blank
    S = X[0]
    
    # K is the size of the oversized pancacke flipper
    K = int(X[1])
    
    # The number of pancakes:
    N = len(S)
    
    # The memo array
    obsolete_flips = [0 for _ in range(N)]
    
    # The answer variable
    answer = 0
    
    for j in range(N-K+1):
        
        state = S[j]
        
        # Incorporate instructions that we have "so far"
        # by just adding the value from the previous cell
        obsolete_flips[j] += obsolete_flips[j-1]
    
        # Count how many times the 
        # j-th pancake DOES in fact get flipped:
        flipped = answer - obsolete_flips[j]
        
        # Figure out if a flip needs to happen here!
        original_destroyed = (state == "+" and flipped % 2 == 1)
        blank_not_fixed = (state == "-" and flipped % 2 == 0)
        
        # If a flip needs to happen...
        if (blank_not_fixed or original_destroyed):
            
            # ...track it in the answer
            answer += 1
            
            # ...and make it obsolete K steps later. 
            if j < N-K:
              obsolete_flips[j + K] += 1
    


    for j in range(N-K+1,N):
        
        # Very similar to what happened before
        # except: no more flips!
        
        obsolete_flips[j] += obsolete_flips[j-1]
        flipped = answer - obsolete_flips[j]
        
        state = S[j]
    
        original_destroyed = (state == "+" and flipped % 2 == 1)
        blank_not_fixed = (state == "-" and flipped % 2 == 0)
        
        # If something is not right...
        if (blank_not_fixed or original_destroyed):
            # ...it cannot be fixed any more:
            answer = "IMPOSSIBLE"
            break
        
    
    print("Case #" + str(C) + ": " + str(answer))
    