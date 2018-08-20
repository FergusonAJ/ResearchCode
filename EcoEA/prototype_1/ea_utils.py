### The EA "meat" for the EA vs EcoEA testing
### 8/14/18
### Austin Ferguson

import random
from constants import *

def genRandomStrings(size):
    L = []
    for i in range(size):
        s = ''
        for j in range(STRING_LENGTH):
            s += random.choice(ALPHABET)
        L.append(s)
    return L

def evaluateFitness(gen, targetList, targetResources=None):
    L = []
    for s in gen:
        score = 0
        for target in targetList:
            matches = 0
            for i in range(len(target)):
                if s[i] == target[i]:
                    matches += 1
            l = len(target)
            S = 0
            bonus = 0
            if matches >= l/2:
                S = (((2 * matches) / len(target)) - 1) ** (2 * SPECIATION_FACTOR)
            if targetResources != None: #EcoEA 
                A = min(S * CONSUMPTION_FRAC * targetResources[target], MAX_AMOUNT)
                targetResources[target] -= A
                bonus = 2 ** A 
            else: #Naive
                bonus = 2 ** S
                bonus *= 5
            if score == 0:
                score = bonus
            else:
                score += bonus 
        L.append((s, score))
        L.sort(key=lambda x: x[1])
    return list(reversed(L))

def evaluateSpread(gen, targetList):
    D = {}
    for target in targetList:
        score = 0
        for s in gen:
            matches = 0
            for i in range(len(target)):
                if s[i] == target[i]:
                    matches += 1
            score += matches
            #l = len(target)
            #S = 0
            #bonus = 0
            #if matches >= l/2:
            #    S = (((2 * matches) / len(target)) - 1) ** 2
            #if targetResources != None: #EcoEA 
            #    A = min(S * CONSUMPTION_FRAC * targetResources[target], MAX_AMOUNT)
            #    targetResources[target] -= A
            #    bonus = 2 ** A 
            #else: #Naive
            #    bonus = 2 ** S
            #    bonus *= 5
            #if score == 0:
            #    score = bonus
            #else:
            #    score += bonus 
        D[target] = score
    return D

def evaluateTaskUsage(gen, targetList):
    D = {}
    for target in targetList:
        D[target] = 0
        for s in gen:
            score = 0
            for i in range(len(target)):
                if s[i] == target[i]:
                    score += (1/STRING_LENGTH)
            if score >= TASK_PCT:
                D[target] += score
    return D    

def getMutation(s):
    newS = ''
    for i in range(len(s)):
        if random.random() < MUT_RATE:
            newS += random.choice(ALPHABET)
        else:
            newS += s[i]
    return s

def getCrossover(a, b):
    s = ''    
    for i in range(len(a)):
        if random.random() > 0.5:
            s += a[i]
        else:
            s += b[i]
    return s
      

def getNextGen(gen):
    newGen = []
    size = len(gen)
    for i in range(int(PCT_CARRY * size)):
        idx = int(random.random() ** 3 * size)
        newGen.append(gen[idx][0])
    for i in range(int(PCT_MUT * size)):
        idx = int(random.random() ** 3 * size)
        newGen.append(getMutation(gen[idx][0]))
    for i in range(int(PCT_CROSS * size)):
        idxA = int(random.random() ** 3 * size)
        idxB = int(random.random() ** 3 * size)
        newGen.append(getCrossover(gen[idxA][0], gen[idxB][0]))
    numRandom = size - len(newGen)
    for s in genRandomStrings(numRandom):
        newGen.append(s)
    return newGen

def populationToFile(fitnessData, targetList, fName):
    with open(fName, 'w+') as fp:
        fp.write('Targets\n')
        fp.write('#############################\n')
        for t in targetList:
            fp.write(t)
            fp.write('\n')
        fp.write('\n')
        fp.write('Fitness Data\n')
        fp.write('#############################\n')
        for x in fitnessData:
            fp.write(str(x))
            fp.write('\n')
