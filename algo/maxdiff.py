def maxDiff(arr):
    if(len(arr) == 1):
        return -1
    maxx = arr[1] - arr[0]
    if(maxx == 0):
        return -1
    minn = arr[0]

    for i in range(1, len(arr)):
        if (arr[i] - minn > maxx):
            maxx = arr[i] - minn

        if (arr[i] < minn):
            minn = arr[i]
    return maxx


arr = [-1, 10, 100, -2, 90, 2]
print(maxDiff(arr))
