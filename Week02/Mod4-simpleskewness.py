'''
Problem: Simple Skewness
URL: https://codeforces.com/contest/626/problem/E
Author : Ayush Modi
Discord Tag : hot9cups#3125
'''

from fractions import Fraction
# We need the fractions module because Python's inbuilt precision for floats isn't enough to solve the problem.
# Fraction is roughtly Python's equivalent of C++'s long double.

def findMean(prefixSum, n, k, medianIdx):
    total = prefixSum[medianIdx + 1] - prefixSum[medianIdx - k] + prefixSum[n] - prefixSum[n - k]
    return Fraction(total, (2 * k + 1))

n = int(input())
nums = sorted(list(map(int, input().split())))
bestSkewness, bestK, bestMedianIdx = 0, 0, 0

# Compute Prefix Sums:
prefSum = [0]
for i in range(n):
    prefSum.append(prefSum[-1] + nums[i])

for medianIdx in range(1, n-1):
    # We want to pick K elements to the left of medianIdx
    # and K elements from the end.
    # What's the largest possible value of K? 

    rangeOfK = min(medianIdx, n - medianIdx - 1)
    left, right = 0, rangeOfK
    
    # mid is the current K
    mid = (left + right) // 2
    
    while right > left:
        a = nums[n - mid - 1]
        b = nums[medianIdx - mid - 1]

        if (2 * mid + 1) * (a + b) <= 2 * (prefSum[medianIdx + 1] - prefSum[medianIdx - mid] + prefSum[n] - prefSum[n - mid]):
            right = mid     # K is an overestimate already.
        else:
            left = mid + 1  # There is more potential for K!
        mid = (left + right) // 2

    # When L = R, we have found K:
    bestCurrentMean = findMean(prefSum, n, left, medianIdx)
    # If we are doing better than the best so far, update answers:
    if bestCurrentMean - nums[medianIdx] > bestSkewness: 
        bestSkewness = bestCurrentMean - nums[medianIdx]
        bestMedianIdx = medianIdx
        bestK = left

# Print answers:
print(2 * bestK + 1)
for i in range(bestK):
    print(nums[n - 1 - i], end = " ")
for i in range(bestK+1):
    print(nums[bestMedianIdx - i], end = " ")
