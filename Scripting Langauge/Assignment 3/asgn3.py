import sys

#scan the file and put segements with corrsponding cookies 
def getData(fileName):
    cookiesDict = {}
    eachLine = []
    splitLine = []
    file = open(fileName)
    readLine = file.readlines()
    for line in readLine:
        if("evaluated:" in line):
            eachLine = line.split("==>")
            splitLine = eachLine[0].split(":")
            cookies = splitLine[-1].strip()
            segments = eachLine[-1].strip()
            cookiesDict[cookies] = segments
    return cookiesDict

#get the cookies with empty segments 
def getEmptyCook(dataDict):
    result = []
    for key, value in dataDict.items():
        if(value == "[]"):
            result.append(key)
    return result

#get the cookies with nonempty segments
def getNonEmptyCook(dataDict):
    result = []
    for key, value in dataDict.items():
        if(value != "[]"):
            result.append(key)
    return result

#Find the cookies that had their segments changed
def differCook(dictA, dictB):
    rDict = {}
    for keyA, ValueA in dictA.items():
        for KeyB, ValueB in dictB.items():
            if(keyA == KeyB):
                A = ValueA.strip("[").strip("]").replace(" ","").split(",")
                B = ValueB.strip("[").strip("]").replace(" ","").split(",")
                tempList = []
                for i in B:
                    if i not in A and i != "":
                        tempList.append(i)
                if tempList:
                    rDict[keyA]= tempList
    return rDict

#Find all the segments are added or removed
def diffSeg(dataDict):
    rDict = {}
    for key in sorted(dataDict.keys()):
        for value in sorted(dataDict[key]):
            if value in rDict:
                rDict[value].append(key)
            else:
                rDict[value] = key.split()
    return rDict

#Find the total amount of segments 
def getSegSize(dataDict):
    rSet = set()
    for value in baseDict.values():
        seg = value.strip("[").strip("]").replace(" ","").split(",")
        for i in seg:
            rSet.add(i)
    return len(rSet)

if __name__ == '__main__':
    #Parse the data from input
    baseDict = getData(sys.argv[1])
    testDict = getData(sys.argv[2])

    #Get the total, empty, and nonempty cookies
    nonEmptyBase = getNonEmptyCook(baseDict)
    emptyBase = getEmptyCook(baseDict)
    baseCookieSet = set(nonEmptyBase)
    nonEmptyTest = getNonEmptyCook(testDict)
    emptyTest = getEmptyCook(testDict)
    testCookieSet = set(nonEmptyTest)
    
    #Get the data for missing or added cookies
    totalSegBase = getSegSize(baseDict)
    missDict = differCook(testDict,baseDict)
    addDict = differCook(baseDict,testDict)

    #get the data for missing or added segments
    sAddDict = diffSeg(addDict)
    sMissDict = diffSeg(missDict)

    # #Print out the results
    print("Summary:")
    #Part 1: Total, empty, nonempty cookies
    print("total cookies in baseline = ",len(baseDict))
    print("empty cookies in baseline = ",len(emptyBase))
    print("non-empty cookies in baseline = ", len(nonEmptyBase),"\n")
    print("total cookies in text = ",len(testDict))
    print("empty cookies in text = ",len(emptyTest))

    #Part 2: nonempty cookes in baseline, test, both, and empty
    print("non-empty cookies in text = ",len(nonEmptyTest),"\n")
    baseOnly = len(baseCookieSet.difference(testCookieSet))
    testOnly = len(testCookieSet.difference(baseCookieSet))
    both = len(baseCookieSet.intersection(testCookieSet))
    either = len(baseCookieSet.union(testCookieSet))
    print("non-empty cookies in baseline only = ",baseOnly)
    print("non-empty cookies in test only = ", testOnly)
    print("non-empty cookies in both = ", both)
    print("non-empty cookies in either = ", either,"\n")

    #Part 3: segments and cookies changes
    print(("Cookies with added segments: %s/%s") % (len(addDict),len(baseDict)))
    for index, (key, value) in enumerate(sorted(addDict.items())):
        print(("%d\t%s\t%d\t%s") % (index, key, len(value), value))
    print(("\nCookies with missing segments: %s/%s") % (len(missDict),len(baseDict)))
    for index, (key, value) in enumerate(sorted(missDict.items())):
        print(("%d\t%s\t%d\t%s") % (index, key, len(value), value))

    print(("\nSegments with added cookies: %s/%s") % (len(sAddDict),totalSegBase))
    for index, (key, value) in enumerate(sorted(sAddDict.items())):
        print(("%d\t%s\t%d\t%s") % (index,key, len(value),value))
    print(("\nSegments with missing cookies: %s/%s") % (len(sMissDict),totalSegBase))
    for index, (key, value) in enumerate(sorted(sMissDict.items())):
        print(("%d\t%s\t%d\t%s") % (index,key, len(value),value))
    