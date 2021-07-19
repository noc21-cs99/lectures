n = int(input())

# Check if n is a power of two.
# Why does the expression used below work?

if (n ^ n-1) & n == n:
    # In this case the program terminates:
    print("TAK")
else:
    # When n is not a power of two, the program
    # does not terminate:
    print("NIE")