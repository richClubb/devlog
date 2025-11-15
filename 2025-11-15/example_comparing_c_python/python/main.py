from functools import reduce

if __name__ == "__main__":

    array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    # Basic for loop using the iterator
    total = 0
    for val in array:
        total += val
    print(f"Total (method 1) is {total}")

    # Basic for loop using indexing
    total = 0
    for index in range(0, len(array)):
        total += array[index]
    print(f"Total (method 2) is {total}")

    # Using the inbuilt 'sum' function
    print(f"Total (method 3) is {sum(array)}")

    # Using a functional method
    print(f"Total (method 4) is {reduce(lambda x, y: x + y, array)}")