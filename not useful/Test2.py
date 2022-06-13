import random
import math

mod = 4
returnBytes = 4
# size = int(math.log(256, mod)) * returnBytes
size = 6

triangle = []

for index in range(0, size):
    tmpArr = []
    for index2 in range(0,size):
        tmpArr.append(0)
    triangle.append(tmpArr)

for index in range(0, size):
    triangle[0][index] = 1
    triangle[index][0] = 1

for y in range(1,size):
    for x in range(1,size):
        triangle[y][x] = triangle[y-1][x] + triangle[y][x-1]

left = []

for index in range(0,size):
    left.append(random.randint(0,mod))

# left = [15,6,14,14,2,12,7,5]
# left = [0,2,0,0,0,0,0,0]
left = [1,2,2,3,0,1]


leftArr = []
botArr = []

for index in range(0, size):
    leftArr.append(0)
    botArr.append(0)

keyLeftArr = left
keyBotArr = []
for index in range(0, size):
    keyBotArr.append(0)

for index in range(0,size): #loop through leftArr
    for index2 in range(index, size): # loop throught botArr starting at index
        keyBotArr[index2] = (keyBotArr[index2] + (triangle[index][index2-index] * keyLeftArr[index])) % mod

leftSum = 0
botSum = 0


for index in range(0,size):
    leftSum += keyLeftArr[index]
    botSum += keyBotArr[index]


def displayChart(array):
    for y in range(size-1, -1, -1):
        for x in range(0, size):
            if y > x:
                print("\t",end='')
            else:
                print(str(array[y][x]) + "\t", end='')
        print()

def printTriangle():
    for index in range(size-1,-1,-1):
        print(triangle[index])

# keyArr[0][1:size] = triangle[1][0:size-1]

def updateBotArr():
    for index in range(0, size): #zero botArr
        botArr[index] = 0
    for index in range(0,size): #loop through leftArr
        # botArr[x] = ((botArr[x] + triangle[index][x-index]) * amount) % mod
        for index2 in range(index, size): # loop throught botArr starting at index
            botArr[index2] = (botArr[index2] + (triangle[index][index2-index] * leftArr[index])) % mod

def rec(current):
    index = 0
    while index<mod:
        if current == size-1:
            last = leftSum
            for index2 in range(0,size-1):
                last -= leftArr[index2]
            if last > mod -1:
                return last - (mod-1)
            elif last < 0:
                return -1
            else:
                leftArr[size-1] = last
            updateBotArr()

            currentBotSum = 0
            currentLeftSum = 0
            for index2 in range(0, size):
                currentBotSum += botArr[index2]
                currentLeftSum += leftArr[index2]
            if currentBotSum == botSum:
                print(currentLeftSum, currentBotSum)
                print(leftArr)
                print(botArr)
                # print(rightArr)
                print()
                return 0
        else:
            leftArr[current] = index
            ret = rec(current+1)
            if ret > 0:
                if ret > mod-1:
                    return ret - (mod-1)
                else:
                    index += ret
            if ret == -1:
                return -1
        index += 1
    return 0


print(leftSum, botSum)
print(keyLeftArr)
print(keyBotArr)


rec(0)