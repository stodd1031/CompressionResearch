import random
import math

mod = 16
size = 4

left = []
for index in range(0,size):
    left.append(random.randint(0,mod))
left = [1,12,0,0]



keyArr = []
for index in range(0, size):
    tmpArr = []
    for index2 in range(0, size):
        tmpArr.append(0)
    keyArr.append(tmpArr)

for index in range(0, size):
    keyArr[index][index] = left[index]

def displayChart(array):
    for y in range(size-1, -1, -1):
        for x in range(0, size):
            if y > x:
                print("\t",end='')
            else:
                print(str(array[y][x]) + "\t", end='')
        print()



for x in range(0, size):
    for y in range(size-1, -1, -1):
        if y >= x:
            continue
        keyArr[y][x] = (keyArr[y+1][x] + keyArr[y][x-1]) % mod

displayChart(keyArr)