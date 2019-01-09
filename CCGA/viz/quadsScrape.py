import sys
import os.path

maxGen = 50
if len(sys.argv) < 3:
    print('You need to pass the directory filepath and the idStr!')
    quit()
srcDir = sys.argv[1]
idStr = sys.argv[2]

ic1FP = open('../output/quads_ic1' + idStr + '.csv', 'w')
ic2FP = open('../output/quads_ic2' + idStr + '.csv', 'w')
ic3FP = open('../output/quads_ic3' + idStr + '.csv', 'w')
ic4FP = open('../output/quads_ic4' + idStr + '.csv', 'w')
rulesetFP = open('../output/quads_ruleset' + idStr + '.csv', 'w')

ic1FP.write('id,gen,value\n')
ic2FP.write('id,gen,value\n')
ic3FP.write('id,gen,value\n')
ic4FP.write('id,gen,value\n')
icFPL = [ic1FP, ic2FP, ic3FP, ic4FP]
rulesetFP.write('id,gen,value\n')




for i in range(maxGen):
    for j in range(4):
        if not os.path.isfile(srcDir + 'QUADS_IC_' + str(j) + '_Gen_' + str(i) +  idStr + '.txt'):
            print('Stopping at', i)
            break
        idx = 0
        with open(srcDir + 'QUADS_IC_' + str(j) + '_Gen_' + str(i) +  idStr + '.txt', 'r') as tmpFP:
            for line in tmpFP:
                line = line.strip()
                L = line.split(' ')
                if len(L) > 0 and L[0] == 'Fitness:':
                    icFPL[j].write(str(idx))
                    icFPL[j].write(',')
                    icFPL[j].write(str(i))
                    icFPL[j].write(',')
                    icFPL[j].write(L[1])
                    icFPL[j].write('\n')
                    idx+=1
    
    if not os.path.isfile(srcDir + 'QUADS_Ruleset_Gen_' + str(i) +  idStr + '.txt'):
        print('Stopping at', i+1)
        break
    
    idx = 0
    with open(srcDir + 'QUADS_Ruleset_Gen_' + str(i) +  idStr + '.txt', 'r') as tmpFP:
        for line in tmpFP:
            line = line.strip()
            L = line.split(' ')
            if len(L) > 0 and L[0] == 'Fitness:':
                rulesetFP.write(str(idx))
                rulesetFP.write(',')
                rulesetFP.write(str(i))
                rulesetFP.write(',')
                rulesetFP.write(L[1])
                rulesetFP.write('\n')
                idx+=1
    

ic1FP.close()
rulesetFP.close()
