'''
Problem: Trouble Sort
URL: https://codingcompetitions.withgoogle.com/codejam/round/00000000000000cb/00000000000079cb
Author : Ayush Modi
Discord Tag : hot9cups#3125
'''

tests = int(input())

for test in range(1, tests + 1):
    n = int(input())
    nums = list(map(int, input().split()))
    
    # 1)Splitting the input array into subarrays with odd and even indices
    # 2)Sorting the spliced arrays
    odds = sorted([num for num in nums[1::2]])
    evens = sorted([num for num in nums[::2]])
    finalList = []

    # Interleaving the spliced and sorted arrays
    for num1, num2 in zip(evens, odds):
        finalList.append(num1)
        finalList.append(num2)
    if len(evens) > len(odds):
        finalList.append(evens[-1])
        
    
    badIdx = -1
    # Check if combined array is sorted, if not - store the first index of sorting error in 'badIdx'
    for i in range(len(nums) - 1):
        if(finalList[i] > finalList[i+1]):
            badIdx = i
            break
    
    if badIdx == -1:
        print(f"Case #{test}: OK")
    else:
        print(f"Case #{test}: {badIdx}")