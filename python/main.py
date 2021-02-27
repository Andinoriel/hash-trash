import random
import numpy as np


def get_hash(x: int, n: int, a: int = 251) -> int:
    return (a ** x) % n


def get_random_x(length, up_pow):
    x = []
    y = []
    for i in range(length):
        x.append(random.randrange(0, 2 ** up_pow))
        y.append(x[i] ^ 1 << random.randrange(0, up_pow))
    return np.array(x), np.array(y)


def get_bin(arr, up_pow):
    bin_arr = []
    for el in arr:
        bin_arr.append(f"{el:0{up_pow}b}")
    return bin_arr


def get_differences(str_1, str_2) -> str:
    result = ""
    for i in range(min(len(str_1), len(str_2))):
        result += str_1[i] if str_1[i] == str_2[i] else "\033[31m" + str_1[i] + "\033[0m"
    return result


def main():
    n = 2 ** 8
    up_pow = 20
    arr_x, arr_y = get_random_x(10, up_pow)
    arr_x_hash = []
    arr_y_hash = []

    for x in arr_x:
        arr_x_hash.append(get_hash(x, n))

    for x in arr_y:
        arr_y_hash.append(get_hash(x, n))

    arr_x_bin = get_bin(arr_x, up_pow)
    arr_y_bin = get_bin(arr_y, up_pow)

    print("X:")
    for i in range(len(arr_x)):
        print(f"{arr_x[i]:{up_pow}}\t\t{get_differences(arr_x_bin[i], arr_y_bin[i])}{arr_x_hash[i]:{up_pow}}")
    print("Y:")
    for i in range(len(arr_y)):
        print(f"{arr_y[i]:{up_pow}}\t\t{get_differences(arr_y_bin[i], arr_x_bin[i])}{arr_y_hash[i]:{up_pow}}")

    print(f"\ncorrelation_coefficient between x and H(x): {round(np.corrcoef(arr_x, arr_x_hash)[1][0], 4)}")
    print(f"correlation_coefficient between y and H(y): {round(np.corrcoef(arr_y, arr_y_hash)[1][0], 4)}")
    print(f"correlation_coefficient between x and y: {round(np.corrcoef(arr_x, arr_y)[1][0], 4)}")
    print(f"correlation_coefficient between H(x) and H(y): {round(np.corrcoef(arr_x_hash, arr_y_hash)[1][0], 4)}")

    return 0


if __name__ == '__main__':
    main()
