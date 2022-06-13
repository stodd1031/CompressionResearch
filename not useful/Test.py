import random

mod = 256

inArr = []
for index in range(0,5):
    inArr.append(random.randint(0,mod-1))
size = len(inArr)
sizeHalf = int((size+1)/2)
inArr = [4, 5, 12, 8, 14, 12, 0, 8]

sum = 0
pro = 1
sumDif = 0
xor = 0

for index in range(0, size):
    if inArr[index] == 0:
        continue
    sum += inArr[index]
    pro *= inArr[index]
    if index % 2 == 0:
        sumDif += inArr[index]
    elif index % 2 == 1:
        sumDif -= inArr[index]
    xor = xor ^ inArr[index]

halfDiff = 0

for index in range(0, sizeHalf):
    if index == sizeHalf-1 and size % 2 != 0:
        if index % 2 == 0:
            halfDiff += inArr[size-1-index]
        elif index % 2 == 1:
            halfDiff -= inArr[size-1-index]
    elif index % 2 == 0:
        halfDiff += inArr[size-1-index] - inArr[index] % mod
    elif index % 2 == 1:
        halfDiff -= inArr[size-1-index] - inArr[index] % mod




diffHalfArr = []

for index in range(0, int((size+1)/2)):
	if index == int((size+1)/2)-1 and size % 2 != 0:
		diffHalfArr.append(inArr[index])
	else:
		diffHalfArr.append(inArr[size-1-index]-inArr[index] % mod)

diffArr = 0
for index in range(0, len(diffHalfArr)):
    if index % 2 == 0:
        diffArr += diffHalfArr[index]
    elif index % 2 == 1:
        diffArr -= diffHalfArr[index]

print("diff",diffArr)

print(diffHalfArr)

print(sum, pro, sumDif)
testArr = []
for index in range(0, size):
    testArr.append(0)
    if index == 0:
        testArr[index] = inArr[index]
    elif index == size-1:
        testArr[index] = inArr[size-1]
        

print(testArr)
print(inArr)

usedSets = []

count = 0

def rec(current):
    index =0
    
    # for index in range(0, mod):
    while index < mod:
        if current == 1 and index % int(mod/10) == 0:
            print(index)
        testArr[current] = index
        if current == size-2:
            secondLast = sum
            for index2 in range(0, size):
                if index2 == size-2:
                        continue
                secondLast -= testArr[index2]
            if secondLast > mod-1:
                # print(secondLast)
                # return 0
                return secondLast - (mod-1)
            elif secondLast < 0:
                return 0
            else:
                testArr[size-2] = secondLast
            currentSum = 0
            currentPro = 1
            currentSumDif = 0
            currentXor = 0
            for index2 in range(0, size):
                if testArr[index2] == 0:
                    continue
                currentSum += testArr[index2]
                currentPro *= testArr[index2]
                if index2 % 2 == 0:
                    currentSumDif += testArr[index2]
                else:
                    currentSumDif -= testArr[index2]
                currentXor = currentXor ^ testArr[index2]
                
            currentHalfDiff = 0

            for index2 in range(0, sizeHalf):
                if index2 == sizeHalf-1 and size % 2 != 0:
                    if index2 % 2 == 0:
                        currentHalfDiff += testArr[size-1-index2]
                    elif index2 % 2 == 1:
                        currentHalfDiff -= testArr[size-1-index2]
                elif index2 % 2 == 0:
                    currentHalfDiff += testArr[size-1-index2] - testArr[index2] % mod
                elif index2 % 2 == 1:
                    currentHalfDiff -= testArr[size-1-index2] - testArr[index2] % mod
            
            if currentHalfDiff == halfDiff:# and currentSum == sum:
                    
                testArrCop = testArr[0:size]
                orderedTest = []
                look = 0
                while len(orderedTest) < size:
                    for index3 in range(0, size):
                        if testArrCop[index3] == look:
                            orderedTest.append(testArrCop[index3])
                            testArrCop[index3] = -1
                            break
                        if index3 == size-1:
                            look += 1
                

                if orderedTest[0:size] not in usedSets:
                    print(index)
                    print(currentSum, currentPro)
                    print(testArr)
                    print(orderedTest)
                    usedSets.append(orderedTest[0:size])



                inArrCop = []
                for index2 in range(0, size):
                    inArrCop.append(inArr[index2])
                for index2 in range(0,size): #check every number in test is in inArr uniquecly
                    if testArr[index2] in inArrCop:
                        inArrCop[inArrCop.index(testArr[index2])] = -1
                    else:
                        # print("false")
                        break
                        pass
                    if index2 == size-1:
                        testArrCop = testArr[0:size]
                        orderedTest = []
                        look = 0
                        while len(orderedTest) < size:
                            for index3 in range(0, size):
                                if testArrCop[index3] == look:
                                    orderedTest.append(testArrCop[index3])
                                    testArrCop[index3] = -1
                                    break
                                if index3 == size-1:
                                    look += 1
                        

                        if orderedTest[0:size] not in usedSets:
                            print(index)
                            print(currentSum, currentPro)
                            print(testArr)
                            print(orderedTest)
                            usedSets.append(orderedTest[0:size])
                        pass
                pass
        else:
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
        index +=1
    return 0
rec(1)