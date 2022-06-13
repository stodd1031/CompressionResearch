#order yes, repitition yes
from math import sqrt
import random

size = 3
mod = 256

def max(val1, val2):
    if (val1 > val2):
        return val1
    else:
        return val2

def min(val1, val2):
    if (val1 < val2):
        return val1
    else:
        return val2

def getCodeRec(key, arr, currentLevel):
    setSize = mod ** (size - 1 - currentLevel)
    arr.append(int(key/setSize) % mod)
    if (currentLevel + 1 == size):
        return arr
    else:
        return getCodeRec(key, arr, currentLevel + 1)

def getCode(key):
    if (key >= mod ** size):
        return None
    return getCodeRec(key, [], 0)

def countOfPossibilities():
    return mod ** size

def getTotal(arr):
    newArr = []
    for index in range(0, len(arr)-1):
        newArr.append(arr[index] + arr[index + 1])
    if (len(arr) == 2):
        return newArr[0]
    else:
        return getTotal(newArr)

def order(arr):
    retArr = []
    for index in range(0, mod):
        for index2 in range(0, len(arr)):
            if arr[index2] == index:
                retArr.append(index)
                arr[index2] = -1
    return retArr

def getTopDiff(arr):
    newArr = []
    for index in range(0, len(arr)-1):
        diff = arr[index+1] - arr[index]
        if (diff < 0):
            diff = mod + diff
        newArr.append(diff)
    if (len(arr) == 2):
        return newArr[0]
    else:
        return getTopDiff(newArr)

def getDiffLeftArrRec(arr, outArr):
    newArr = []
    for index in range(0, len(arr)-1):
        diff = arr[index+1] - arr[index]
        if (diff < 0):
            diff = mod + diff
        newArr.append(diff)
    outArr.append(newArr[0])
    if (len(arr) == 2):
        return outArr
    else:
        return getDiffLeftArrRec(newArr, outArr)

def getDiffLeftArr(arr):
    outArr = []
    outArr.append(arr[0])
    return getDiffLeftArrRec(arr, outArr)

def getSumLeftArrRec(arr, outArr):
    newArr = []
    for index in range(0, len(arr)-1):
        newArr.append(arr[index] + arr[index + 1])
    outArr.append(newArr[0])
    if (len(arr) == 2):
        return outArr
    else:
        return getSumLeftArrRec(newArr, outArr)

def getSumLeftArr(arr):
    outArr = []
    outArr.append(arr[0])
    return getSumLeftArrRec(arr, outArr)
    
def getKey(code):
    num = 0
    for index in range(0, len(code)):
        num += mod ** (size - index - 1) * code[index]
    return num

def getArrayTotal(arr):
    num = 0
    for index in range(0, len(arr)):
        num += arr[index]
    return num

def getBotTot(arr):
    ret = 0
    for item in arr:
        ret += item
    return ret

# print(countOfPossibilities().bit_length())

totalAndLeftTotal = []

# for index in range(0, countOfPossibilities()):
#     code = getCode(index)
#     botTop = getTotal(code)
#     leftTop = getTotal(getDiffLeftArr(code))
#     botTot = getArrayTotal(code)
#     allTot = [botTop, leftTop, botTot]
#     if (allTot in totalAndLeftTotal):

#         at = totalAndLeftTotal.index(allTot)
#         print(getCode(at), end=' ')
#         print(getTotal(getCode(at)), end=' ')
#         print(getTotal(getDiffLeftArr(getCode(at))))
        
#         print(code, end=' ')
#         print(botTop, end=' ')
#         print(leftTop)
        
#     totalAndLeftTotal.append(allTot)


# for index in range(0, countOfPossibilities()):
#     code = getCode(index)
#     botTot = getTotal(code)
#     leftTot = getTotal(getDiffLeftArr(code))
#     rightTot = 0
#     allTot = [botTot, leftTot]
#     if (allTot in totalAndLeftTotal):

#         at = totalAndLeftTotal.index(allTot)
#         print(getCode(at), end=' ')
#         print(getTotal(getCode(at)), end=' ')
#         print(getTotal(getDiffLeftArr(getCode(at))))
        
#         print(code, end=' ')
#         print(botTot, end=' ')
#         print(leftTot)
        
#     totalAndLeftTotal.append(allTot)

outNum = getTotal(getCode(countOfPossibilities()-1))
outBit1 = outNum.bit_length()
print(outBit1 * 2)
print((mod-1).bit_length() * size)

dic = {}

for index in range (0, countOfPossibilities()):
    code = getCode(index)
    if getBotTot(code) not in dic:
        dic[getBotTot(code)] = 0
    dic[getBotTot(code) ] += 1
print(dic)