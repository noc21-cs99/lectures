class DSU:
    def __init__(self, n):
        self.p = [-1] * n
        self.numset = n;

    def find(self, a):
        if self.p[a] < 0:
            return a
        self.p[a] = self.find(self.p[a])
        return self.p[a]

    def union(self, a, b):
        a, b = self.find(a), self.find(b)
        if a != b:
            if self.p[a] > self.p[b]:
                a, b = b, a
            self.p[a] -= self.p[a] == self.p[b]
            self.p[b] = a
            self.numset += 1

    def isSameSet(self,i,x):
         return self.find(i)==self.find(j);


n, m = map(int, input().split())
d = DSU(n)
for _ in range(m):
  type, u, v = input().split()
  u, v = map(lambda x: int(x)-1, [u, v])
  if type == "union":
    d.union(u, v)
  else:
    if (d.find(u) == d.find(v)):
        print("YES")
    else:
      print("NO")    
