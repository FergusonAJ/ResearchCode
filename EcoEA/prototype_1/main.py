### Very rough comparison of a naive EA approach against a rough EcoEA approach
### 8/14/18
### Austin Ferguson

### Imports
import random
import sys
import cProfile

from constants import *
from ea_utils import *

NUM_TRIALS = 1
if len(sys.argv) > 1:
    c = 1
    while c < len(sys.argv):
        s = sys.argv[c]
        if s[0] != '-':
            NUM_TRIALS = int(sys.argv[c])
        c += 1

def run():
    #EcoEA
    for trial in range(NUM_TRIALS):
        fullMatchFP = open('trial_eco_ea_' + str(trial) + '.csv', 'w+')
        resourceFP = open('trial_eco_ea_resources_' + str(trial) + '.csv', 'w+')
        charMatchFP = open('trial_eco_ea_char_match_' + str(trial) + '.csv', 'w+')
        files = [fullMatchFP, resourceFP, charMatchFP]
        print('EcoEA Trial #' + str(trial))
        fullMatchFP.write('target, generation, matches\n')
        resourceFP.write('target, generation, resources\n')
        charMatchFP.write('target, generation, char_matches\n')
        targetList = genRandomStrings(NUM_STRINGS)
        targetResources = {}
        for t in targetList:
            targetResources[t] = INFLOW * INIT_STEPS

        curGen = genRandomStrings(GEN_SIZE)
        fitnessData = evaluateFitness(curGen, targetList, targetResources)
        for i in range(NUM_GENS):
            for t in targetList:
                targetResources[t] += INFLOW
                targetResources[t] -= targetResources[t] * OUTFLOW
            curGen = getNextGen(fitnessData)    
            fitnessData = evaluateFitness(curGen, targetList, targetResources)
            if i % DATA_TRIM_FACTOR == 0:
                taskUsage = evaluateTaskUsage(curGen, targetList)
                spreadData = evaluateSpread(curGen, targetList)
                for t in range(len(targetList)):
                    fullMatchFP.write(targetList[t] + ',')
                    fullMatchFP.write(str(i + 1) + ',')
                    fullMatchFP.write(str(taskUsage[targetList[t]]) + '\n')
                    resourceFP.write(targetList[t] + ',')
                    resourceFP.write(str(i + 1) + ',')
                    resourceFP.write(str(targetResources[targetList[t]]) + '\n')
                    charMatchFP.write(targetList[t] + ',')
                    charMatchFP.write(str(i + 1) + ',')
                    charMatchFP.write(str(spreadData[targetList[t]]) + '\n')
            if ((i / NUM_GENS) * 100) % 10 == 0:
                print('#', end='', flush=True)
        print('')
        populationToFile(fitnessData, targetList, 'trial_eco_ea_' + str(trial) + '.txt')
        for f in files:
            f.close()
    #Naive
    for trial in range(NUM_TRIALS):
        fullMatchFP = open('trial_naive_' + str(trial) + '.csv', 'w+')
        charMatchFP = open('trial_naive_char_match_' + str(trial) + '.csv', 'w+')
        files = [fullMatchFP, charMatchFP]
        print('Naive Trial #' + str(trial))
        fullMatchFP.write('target, generation, matches\n')
        charMatchFP.write('target, generation, char_matches\n')
        targetList = genRandomStrings(NUM_STRINGS)

        curGen = genRandomStrings(GEN_SIZE)
        fitnessData = evaluateFitness(curGen, targetList)
        for i in range(NUM_GENS):
            curGen = getNextGen(fitnessData)    
            fitnessData = evaluateFitness(curGen, targetList)
            if i % DATA_TRIM_FACTOR == 0:
                taskUsage = evaluateTaskUsage(curGen, targetList)
                spreadData = evaluateSpread(curGen, targetList)
                for t in range(len(targetList)):
                    fullMatchFP.write(targetList[t] + ',')
                    fullMatchFP.write(str(i + 1) + ',')
                    fullMatchFP.write(str(taskUsage[targetList[t]]) + '\n')
                    charMatchFP.write(targetList[t] + ',')
                    charMatchFP.write(str(i + 1) + ',')
                    charMatchFP.write(str(spreadData[targetList[t]]) + '\n')
            if ((i / NUM_GENS) * 100) % 10 == 0:
                print('#', end='', flush=True)
        print('')
        populationToFile(fitnessData, targetList, 'trial_naive_' + str(trial) + '.txt')
        for f in files:
            f.close()

    print('Script finished!')

if __name__ == "__main__":
    if '-d' in sys.argv:
        print('Running in debug mode!')
        print('Firing up the profileri...')
        cProfile.run('run()')
    else:
        run()
