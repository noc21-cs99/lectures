import sys

sys.stdin = open('in.txt', 'r')
sys.stdout = open('out.txt', 'w')


N, M = list(map(int,input().strip().split()))
requests = []

for i in range(M):
    request = tuple(map(int,input().strip().split()))
    requests.append(request)

requests.sort(key = lambda x: x[1])

ans = 0
lastbridge = -1

for request in requests:
    if lastbridge > request[0]:
        continue
    else:
        lastbridge = request[1]
        ans += 1

print(ans)