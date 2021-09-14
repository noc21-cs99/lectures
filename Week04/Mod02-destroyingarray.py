# Problem Link: https://codeforces.com/problemset/problem/722/C

class DSU:
  def __init__(self, n):
    """Initializes the data structure spaces for 'n' sets"""
    
    # No element's parent is defined as of yet
    self.parent = [-1] * n

    # The height of all trees is not defined yet
    self.rank = [-1] * n

    # The size of each set is 0
    self.setSize = [0] * n

    # The sum of each set is also 0
    self.setSum = [0] * n

    # There are no sets initially
    self.setCount = n

  def makeSet(self, i, x):
    """Creates a new singleton set with the given 'x' as value at index 'i'"""

    # It is it's own parent, hence at rank 0
    self.parent[i] = i
    self.rank[i] = 0

    # It is a Singleton set, hence the sum is itself
    self.setSize[i] = 1
    self.setSum[i] = x

    # Increment the set count
    self.setCount += 1

  def findSet(self, i):
    """Returns the parent element of the set that 'i' belongs to"""
    
    # If the element is already a parent element of a set, return it
    if self.parent[i] == i:
      return i
    
    # Else, move up the tree to find the parent, and perform path compression
    self.parent[i] = self.findSet(self.parent[i])

    # Return the parent
    return self.parent[i]

  def sameSet(self, i, j):
    """Checks if the two elements belong to the same set"""
    return self.findSet(i) == self.findSet(j)

  def union(self, i, j):
    """Combines the sets that 'i' and 'j' belong to"""

    # if the elements belong to the same set, we don't need to do anything
    # If they're not, we perform the union operation
    if not self.sameSet(i, j):

      # Find the parent elements of the two elements
      x = self.findSet(i)
      y = self.findSet(j)

      # Make sure that 'x' is the tree with the smaller rank (proxy to depth)
      x, y = (y, x) if self.rank[x] > self.rank[y] else (x, y)

      # Set y as the parent of x
      self.parent[x] = y

      # If the ranks were the same, then the depth of the final tree must increase by 1
      if self.rank[x] == self.rank[y]:
        self.rank[y] += 1
      
      # Update the size of the combined set
      self.setSize[y] += self.setSize[x]

      # Update the sum of the combined set
      self.setSum[y] += self.setSum[x]

      # Lastly, reduce the set count, since we merged two sets into one
      self.setCount -= 1

  def sizeOfSet(self, i):
    """Returns the size of the set that the given element belongs to"""
    return self.setSize[self.findSet(i)]
  
  def getSetCount(self):
    """Returns the current count of disjoint sets"""
    return self.setCount

  def sumOfSet(self, i):
    """Returns the sum of the set that the given element belongs to"""
    return self.setSum[self.findSet(i)]

if __name__ == '__main__':
  n = int(input())
  arr = [int(i) for i in input().split()]
  sequence = [int(i)-1 for i in input().split()]

  # Reverse the sequence since we are going in reverse
  sequence.reverse()

  # To store the state of each element (1 -> not destroyed, 0 -> destroyed)
  state = [0] * n
  
  # List of answers at each stage, and a current answer variable
  answers = [0]
  currentAns = 0

  disjointSets = DSU(n)
  for idx in sequence:
    # Create the singleton set
    state[idx] = 1
    disjointSets.makeSet(idx, arr[idx])

    # Form unions with the left and right elements, if they're not destroyed
    if idx > 0 and state[idx-1]:
      disjointSets.union(idx-1, idx)
    if idx < n-1 and state[idx+1]:
      disjointSets.union(idx, idx+1)

    # Find the answer at this stage and append it to the answer array
    currentAns = max(disjointSets.sumOfSet(idx), currentAns)
    answers.append(currentAns)

  # Pop the last element and reverse the answer array and disply the answers
  answers.pop()
  answers.reverse()
  for answer in answers:
    print(answer)