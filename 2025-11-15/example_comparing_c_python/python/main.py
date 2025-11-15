from functools import reduce

if __name__ == "__main__":

    array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    total = 0
    for val in array:
        total += val
    print(f"Total (method 1) is {total}")

    total = 0
    for index in range(0, len(array)):
        total += array[index]
    print(f"Total (method 2) is {total}")

    print(f"Total (method 3) is {sum(array)}")

    print(f"Total (method 4) is {reduce(lambda x, y: x + y, array)}")