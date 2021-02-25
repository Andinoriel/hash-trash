import random


def get_hash(x: int, n: int, a: int = 251) -> int:
    return (a ** x) % n


def get_random_x(length):
    x = []
    for _ in range(length):
        x.append(random.randrange(0, 2 ** 20))
    return x


def correlation_coefficient(x: list, y: list, length: int) -> float:
    x_avg = 0
    y_avg = 0
    x2_avg = 0
    y2_avg = 0

    for i in range(length):
        x_avg += x[i]
        y_avg += y[i]
        x2_avg += x[i] ** 2
        y2_avg += y[i] ** 2

    x_avg /= length
    y_avg /= length
    x2_avg /= length
    y2_avg /= length

    delta_x2 = x2_avg - x_avg ** 2
    delta_y2 = y2_avg - y_avg ** 2
    delta_x = delta_x2 ** (1 / 2)
    delta_y = delta_y2 ** (1 / 2)

    numerator = 0

    for i in range(length):
        numerator += (x[i] - x_avg) * (y[i] - y_avg)

    denominator = length * delta_x * delta_y

    corrcoef = numerator / denominator

    return corrcoef


def main():
    n = 2 ** 8
    X = get_random_x(10)
    Y = []

    for x in X:
        Y.append(get_hash(x, n))

    X_ = X
    Y_ = []
    for i in range(len(X)):
        X_[i] = X[i] ^ 1 << i

    for x in X_:
        Y_.append(get_hash(x, n))

    print(f"x: {X}")
    print(f"Y: {Y}")
    print(f"x_: {X_}")
    print(f"Y_: {Y_}")

    print(f"correlation_coefficient: {correlation_coefficient(Y, Y_, len(Y))}")


if __name__ == '__main__':
    main()
