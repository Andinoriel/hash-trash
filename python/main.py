import random

def get_hash(x, n, a=251):
    return (a**x) % n

def get_random_x(len):
    x = []
    for _ in range(len):
        x.append(random.randrange(0, 2**20))
    return x

def main():
    n = 2**8
    X = get_random_x(10)
    Y = []
    print(f"x: {X}")
    for x in X:
        Y.append(get_hash(x, n))
    print(f"Y: {Y}")

    X_ = X
    Y_ = []
    for i in range(len(X)):
        X_[i] = X[i]^1 << i
    print(f"x_: {X_}")
    
    for x in X_:
        Y_.append(get_hash(x, n))
    print(f"Y_: {Y_}")


if __name__ == '__main__':
    main()