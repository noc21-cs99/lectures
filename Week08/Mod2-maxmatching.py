'''
Problem: https://codeforces.com/problemset/problem/489/B
Author: Sudhanshu (@sudhi23)
214
'''
INF = 1e18

class MaxFlow():
    EL = []
    AL = []
    d = []
    p = []
    V = 0

    def __init__(self, initialV):
        self.V = initialV
        self.EL = []
        self.AL = [[] for i in range(self.V)]


    def BFS(self, s, t):
        self.d = [-1 for i in range(self.V)]
        self.d[s] = 0

        q = [s]

        self.p = [[-1, -1] for i in range(self.V)]

        while(len(q) != 0):
            u = q.pop(0)

            if u == t:
                break

            for idx in self.AL[u]:
                v, cap, flow = self.EL[idx]

                if cap-flow>0 and self.d[v] == -1:
                    self.d[v] = self.d[u] + 1
                    q.append(v)
                    self.p[v] = [u, idx]

        return self.d[t] != -1

    def send_one_flow(self, s, t, f=INF):

        if s==t:
            return f

        u, idx = self.p[t]

        cap, flow = self.EL[idx][1], self.EL[idx][2]

        pushed = self.send_one_flow(s, u, min(f, cap-flow))
        self.EL[idx][2] += pushed

        self.EL[idx^1][2] -= pushed

        return pushed

    def add_edge(self, u, v, w, directed=True):
        if u==v:
            return
        
        self.EL.append([v, w, 0])
        self.AL[u].append(len(self.EL) - 1)

        self.EL.append([u, 0 if directed else w, 0])
        self.AL[v].append(len(self.EL) - 1)

    def edmonds_karp(self, s, t):
        maxf = 0

        while self.BFS(s, t):
            f = self.send_one_flow(s, t)
            if f == 0:
                break
            maxf += f

        return maxf

boys = int(input())
B = list(map(int, input().split()))

girls = int(input())
G = list(map(int, input().split()))

maxf = MaxFlow(boys + girls + 2)

for i in range(boys):
    for j in range(girls):
        if abs(B[i] - G[j]) <= 1:
            maxf.add_edge(i+1, boys+j+1, 1)

for i in range(1, boys+1):
    maxf.add_edge(0, i, 1)

for i in range(1, girls+1):
    maxf.add_edge(boys+i, boys+girls+1, 1)

print(maxf.edmonds_karp(0, boys+girls+1))