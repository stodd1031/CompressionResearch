#order no, repitition yes
size = 4

mod = 3

pascal = []
# for index in range(0, size):
#     pascal.append([])

for y in range(0,size):
    tmpArr = []
    for x in range(0, mod):
        tmpArr.append(0)
    pascal.append(tmpArr)
    
for index in range(0, mod): # set top row to 1
    pascal[size-1][index] = 1
for index in range(0, size): # set right collumn to 1
    pascal[index][mod-1] = 1

for y in range(size-2, -1,-1):
    for x in range(mod-2, -1,-1):
        pascal[y][x] = pascal[y+1][x] + pascal[y][x+1]

def displaypascal():
    for y in range(size-1, -1,-1):
        for x in range(0, mod):
            print(pascal[y][x],end='\t')
        print()

def getCodeRec(key, arr, currentLevel, test, index):
    for j in range(index, mod):
        test += pascal[currentLevel][j]
        # print(currentLevel, j)
        # print(key, test)
        if key < test:
            if size-1 == currentLevel:
                # arr.append(j)
                arr[currentLevel] = j
                return arr
            else:
                # arr.append(j)
                arr[currentLevel] = j
                return getCodeRec(key, arr, currentLevel+1, test-pascal[currentLevel][j], j)

def getCode(key):
    return getCodeRec(key,[None]*size,0,0,0)

def getKeyRec(code, currentLevel, test, index):
    for j in range(index, mod):
        if code[currentLevel] == j:
            if currentLevel == size-1:
                return test
            else:
                return getKeyRec(code, currentLevel+1,test,j)
        test += pascal[currentLevel][j]

def getKey(arr):
    return getKeyRec(arr, 0, 0, 0)

def order(arr):
    retArr = []
    for index in range(0, mod):
        for index2 in range(0, len(arr)):
            if arr[index2] == index:
                retArr.append(index)
                arr[index2] = -1
    return retArr

def countOfPossibilities():
    numStart = mod - 1 + size
    numTot = 1
    demTot = 1
    for index in range(0, size):
        numTot *= numStart - index
        demTot *= index + 1
    return int(numTot/demTot)

# print(countOfPossibilities())
# print(getCode(0))

# displaypascal()

# print(getCode(3875))

possibilities = countOfPossibilities()
# print(countOfPossibilities())
for x in range(0,15):
    print(getCode(x))

# for x in range(0, possibilities):

# print(getKey([4,4,5,13]))



