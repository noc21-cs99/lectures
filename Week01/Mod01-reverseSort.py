def reverseSort(a):
    cost = 0
    for i in range(len(a)-1):

        # find minimum element from i to end
        m = min(a[i:])

        # find index of the minimum element
        m_index = a[i:].index(m)

        # reverse from i to m_index
        a[i:m_index+i+1] = a[i:m_index+i+1][::-1]

        # keep track of cost
        cost += len(a[i:m_index+i+1])

    # print(*a)
    return cost


for _ in range(int(input())):

    n = int(input())
    a = list(map(int, input().split()))

    print('Case #', _+1, ': ', reverseSort(a), sep='')

