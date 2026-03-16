arr = [3, 2, 1,4, 5, 6, 7, 2]

for i in range(len(arr)):
    for j in range(len(arr) - 1 - i):
        if arr[j] > arr [j + 1]:
            t = arr[j]
            arr[j] = arr[j + 1]
            arr[j + 1] = t

print(arr)
