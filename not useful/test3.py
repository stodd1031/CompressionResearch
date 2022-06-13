import random

mod = 16

leftArr = []

for index in range(0, 28):
    leftArr.append(random.randint(0,mod-1))
    # leftArr.append(1)

# leftArr = [1,2,0,1,3,1,1,3,1,0,3,14,12,1,4,8,10]

size = len(leftArr)

keyArr = []
for index in range(0, size):
    tmpArr = []
    for index2 in range(0, size):
        tmpArr.append(0)
    keyArr.append(tmpArr)


for index in range(0, size):
    keyArr[index][index] = leftArr[index]

for x in range(0, size):
    for y in range(size-1, -1, -1):
        if y >= x:
            continue
        keyArr[y][x] = (keyArr[y+1][x] + keyArr[y][x-1]) % mod

def displayChart(array):
    for y in range(size-1, -1, -1):
        for x in range(0, size):
            if y > x:
                print("\t",end='')
            else:
                print(str(array[y][x]) + "\t", end='')
        print()

def order(arr):
    retArr = []
    for index in range(0, mod):
        for index2 in range(0, len(arr)):
            if arr[index2] == index:
                retArr.append(index)
                arr[index2] = -1
    return retArr

botArr = []
rightArr = []

for index in range(0,size):
    botArr.append(keyArr[0][index])
    rightArr.append(keyArr[size-1-index][size-1])

# displayChart(keyArr)


diffs = []

for y in range(0,size):
    tmpArr = []
    for x in range(0, size):
        tmpArr.append(0)
    diffs.append(tmpArr)
    

    
for index in range(0, size): # set right collumn and top row to 1
    diffs[index][size-1] = 1
    diffs[size-1][index] = 1

for y in range(size-2, -1,-1):
    for x in range(size-2, -1,-1):
        diffs[y][x] = diffs[y+1][x] + diffs[y][x+1]

def displayDiffs():
    for y in range(size-1, -1,-1):
        for x in range(0, size):
            print(diffs[y][x],end='\t')
        print()

print()
# displayDiffs()

testLeftArr = []
testBotArr = []

for index in range(0, size):
    testLeftArr.append(0)
    testBotArr.append(0)

def rec(current):
    possibilities = []
    if current == 0:
        for index in range(0, size):
            if leftArr[index] in botArr and [leftArr[index], leftArr[index]] not in possibilities:
                possibilities.append([leftArr[index],leftArr[index]])
    else:
        test = 0
        for index in range(0, current):
            test+= testLeftArr[index] * diffs[size-1-index][size-1-current+index]
            # print("tets", test)
        for index in range(0, mod):
            if index in leftArr and ((test+index) % mod) in botArr and [index,((test+index) % mod)] not in possibilities:
                possibilities.append([index,((test+index) % mod)])
    if len(possibilities) == 0:
        return
    else:
        # print(current)
        # print(possibilities)
        # print(testLeftArr)
        # print(testBotArr)
        # print(leftArr)
        # print(botArr)
        # print(testLeftArr[0], testBotArr[0])
        pass
    if current == size-1:
        testLeftArr[current] = possibilities[0][0]
        testBotArr[current] = possibilities[0][1]
        
        testRightArr = []
        for index in range(0, size-1):
            rightItem = 0
            for index2 in range(0, index+1):
                rightItem += testLeftArr[size-1-index2] * diffs[size-1-index2][size-1-index+index2]
                # print(rightItem)
            testRightArr.append(rightItem%mod)
        testRightArr.append(testBotArr[size-1])
        leftArrCpy = leftArr[0:size]
        if order(testRightArr[0:size]) == order(rightArr[0:size]):
            pass
            print(testLeftArr)
            print(testBotArr)
            print(testRightArr)
            print("found")
            # print(order(testLeftArr[0:size]))
            # print(order(testBotArr[0:size]))
            # print(order(testRightArr[0:size]))
            print()
        # print("test")
        return
    for index in range(0,len(possibilities)):
        if current == 0 or current == 3 or current == 5:
            print(current, index, len(possibilities))
        testLeftArr[current] = possibilities[index][0]
        testBotArr[current] = possibilities[index][1]
        leftIn = leftArr.index(possibilities[index][0])
        botIn = botArr.index(possibilities[index][1])
        leftArr[leftIn] = -1
        botArr[botIn] = -1
        # print(leftArr)
        # print(botArr)
        rec(current+1)
        leftArr[leftIn] = possibilities[index][0]
        botArr[botIn] = possibilities[index][1]


print(leftArr)
print(botArr)

rec(0)

modMinus = mod -1

returnSize = modMinus.bit_length() * size

inputSize = 0

topMult = mod + size -1
botMult = size

top = 1
bot = 1

for index in range(0,topMult):
    top *= topMult-index

for index in range(0, botMult):
    bot *= botMult-index

for index in range(0, topMult-botMult):
    bot *= topMult-botMult-index

print(topMult)
print(botMult)

print(top)
print(bot)
total = int(top/bot)

print(total)

inputOrderMatter = ((mod) ** size)-1

int2 = 4228250625

print(int2.bit_length())
# print(inputOrderMatter)
print("input order", inputOrderMatter.bit_length())
print("input 3", (total.bit_length()-1)*3)
print("return bits", returnSize)


