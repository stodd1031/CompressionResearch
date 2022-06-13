import random
import math

mod = 16
returnBytes = 4
size = int(math.log(256, mod)) * returnBytes

inArr = []
for index in range(0,size):
    inArr.append(random.randint(0,mod-1))
inArr = [1, 13, 0, 0]
size = len(inArr)


def displayChart(array):
    for y in range(size-1, -1, -1):
        for x in range(0, size):
            if y > x:
                print("\t",end='')
            else:
                print(str(array[y][x]) + "\t", end='')
        print()




keyArr = []

for y in range(0, size):
    tmparr = []
    for x in range(0, size):
        tmparr.append(0)
    keyArr.append(tmparr)

keyArr[0][0:size-1] = inArr[0:size]

for y in range(1, size):
    for x in range(1, size):
        if y > x:
            continue
        keyArr[y][x] = (keyArr[y-1][x] - keyArr[y-1][x-1]) % mod


botLeft = inArr[0]
botRight = inArr[size-1]
top = keyArr[size-1][size-1]

bottomPro = 1
bottomSum = 0
leftPro = 1
leftSum = 0
rightPro = 1
rightSum = 0
allrowSum = 0

for index in range(0, size):
    if index == 0 or index == size-1:
        # continue
        pass
    if keyArr[0][index] != 0:
        bottomPro *= keyArr[0][index]
    bottomSum += keyArr[0][index]
    if keyArr[index][index] != 0:
        leftPro *= keyArr[index][index]
    leftSum += keyArr[index][index]
    if keyArr[index][size-1] != 0:
        rightPro *= keyArr[index][size-1]
    rightSum += keyArr[index][size-1]

for y in range(0, size):
    for x in range(0, size):
        if y > x:
            continue
        allrowSum += keyArr[y][x]

print(allrowSum)
print(bottomPro, leftPro, rightPro)
print(bottomSum, leftSum, rightSum)
displayChart(keyArr)

arr = []

for y in range(0, size):
    tmparr = []
    for x in range(0, size):
        tmparr.append(0)
    arr.append(tmparr)

# arr[size-1][size-1] = top
# arr[0][0] = botLeft
# arr[0][size-1] = botRight

topDownDiff = 0

for index in range(0, size):
    if index % 2 == 0:
        topDownDiff += keyArr[index][index] - keyArr[0][index] % mod
    else:
        topDownDiff -= keyArr[index][index] - keyArr[0][index] % mod


print("diff",topDownDiff)


# displayChart(arr)


def rec(current):
    start = 0
    # if current == 1:
    #     start = mod/2
    index = start
    # for index in range(start, mod):
    while index < mod:
        # if current == 1:# and index % int(mod/1000)==0:
        #     print(index)
        arr[size-current-1][size-current-1] = index
        if (size-2 != current):
            lowVal = rec(current+1)
            
            if lowVal == -1:
                print(-1)
                return -1
            if lowVal > 0:
                # print(lowVal)
                if lowVal + index > mod-1:
                    return lowVal-(mod-1)
                else:
                    index += lowVal
        if (size-2 == current):
            currentLeftOneOne = leftSum
            for left in range(0, size):
                if left == 1:
                    continue
                currentLeftOneOne -= arr[left][left]
            arr[1][1] = currentLeftOneOne
            # arr[1][1] = int(currentLeftOneOne)
            # if arr[1][1] != currentLeftOneOne:
            #     return 0
            if (arr[1][1] > mod-1):
                return arr[1][1] - (mod-1)
            elif arr[1][1] < 0:
                return 0
            

            for y in range(size-2, -1, -1):
                for x in range(0, size):
                    if y > x:
                        continue
                    if (y == x):
                        continue
                    if (y == 0) and (x == size-1):
                        continue
                    # print(arr[size-2][size-2])
                    # print(x, y, arr[y][x-1] + arr[y+1][x])
                    arr[y][x] = (arr[y][x-1] + arr[y+1][x]) % mod
            currentBotPro = 1
            currentBotSum = 0
            currentLeftPro = 1
            currentLeftSum = 0
            currentRightPro = 1
            currentRightSum = 0
            currentTopDownDiff = 0
            for index2 in range(0, size):
                # if index2 == 0 or index2 == size-1:
                #     # continue
                #     pass
                # if arr[0][index2] != 0:
                #     currentBotPro *= arr[0][index2]
                currentBotSum += arr[0][index2]
                # if arr[index2][index2] != 0:
                #     currentLeftPro *= arr[index2][index2]
                # currentLeftSum += arr[index2][index2]
                # if arr[index2][size-1] != 0:
                #     currentRightPro *= arr[index2][size-1]
                currentRightSum += arr[index2][size-1]

                if index2 % 2 == 0:
                    currentTopDownDiff += arr[index2][index2] - arr[0][index2] % mod
                else:
                    currentTopDownDiff -= arr[index2][index2] - arr[0][index2] % mod
                
            
            # print(currentBot, currentLeft, currentRight)
            # displayChart(arr)
            # print()
            if (currentBotSum == bottomSum) and currentTopDownDiff == topDownDiff and currentRightSum == rightSum:#(currentBotPro == bottomPro):# and :# and (currentRightSum == rightSum):# and (currentRightPro == rightPro):
                currentAllSum = 0
                for y in range(0, size):
                    for x in range(0, size):
                        if y > x:
                            continue
                        currentAllSum += arr[y][x]
                if currentAllSum == allrowSum or True:
                    print("found")
                    print(currentAllSum)
                    print(currentBotPro, currentLeftPro, currentRightPro)
                    print(currentBotSum, currentLeftSum, currentRightSum)
                    displayChart(arr)
                    # return 1
            return 0
        index += 1
    return 0


rec(0)
print()
# displayChart(arr)

