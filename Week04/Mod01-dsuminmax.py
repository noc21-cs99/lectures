# Problem Link: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/B

import sys
input = sys.stdin.readline

class DSU:
  def __init__(self, n):
    """Initializes the data structure with 'n' singleton sets"""
    
    # Every element is its own parent
    self.parent = list(range(n))

    # The height of all trees is 0 (an upper bound of depth)
    self.rank = [0] * n

    # The size of each set is 1 (singleton sets)
    self.setSize = [1] * n

    # Each set's minimum and the maximum element is the one element in it
    self.minSet = list(range(n))
    self.maxSet = list(range(n))

    # There are n singleton sets initially
    self.setCount = n

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

      # Update the min and max values of the combined set
      self.minSet[y] = min(self.minSet[y], self.minSet[x])
      self.maxSet[y] = max(self.maxSet[y], self.maxSet[x])

      # Lastly, reduce the set count, since we merged two sets into one
      self.setCount -= 1

  def sizeOfSet(self, i):
    """Returns the size of the set that the given element belongs to"""
    return self.setSize[self.findSet(i)]
  
  def getSetCount(self):
    """Returns the current count of disjoint sets"""
    return self.setCount

  def minInSet(self, i):
    """Returns the minimum value of the set that 'i' belongs to"""
    return self.minSet[self.findSet(i)]

  def maxInSet(self, i):
    """Returns the maximum value of the set that 'i' belongs to"""
    return self.maxSet[self.findSet(i)]

if __name__ == '__main__':
  n, m = (int(i) for i in input().split())

  disjointSet = DSU(n+1)

  for _ in range(m):
    query = input().split()

    if len(query) == 3:
      u, v = int(query[1]), int(query[2])
      disjointSet.union(u, v)
    else:
      v = int(query[1])
      print(disjointSet.minInSet(v), disjointSet.maxInSet(v), disjointSet.sizeOfSet(v))