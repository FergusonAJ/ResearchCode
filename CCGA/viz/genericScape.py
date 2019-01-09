import sys
import os.path

maxGen = 50
if len(sys.argv) < 4:
    print('You need to pass the directory filepath (prefix), job id, and the suffix!')
    quit()
prefix = sys.argv[1]
job_id = sys.argv[2]
out_dir = sys.argv[3]

outFP = open(out_dir + '/' +  job_id  + '_SCRAPED.csv', 'w')
outFP.write('arr_id,id,gen,value\n')

for arr_id in range(1, 51):
    for i in range(maxGen+1):
        filename = prefix + '_' +  str(i) + '_' + job_id + '_' + str(arr_id) + '.txt'
        if not os.path.isfile(filename):
            print('Stopping at', i)
            print('Was looking for (' + filename + ')!')
            break
        idx = 0
        with open(filename, 'r') as inFP:
            for line in inFP:
                line = line.strip()
                L = line.split(' ')
                if len(L) > 0 and L[0] == 'Fitness:':
                    outFP.write(str(arr_id))
                    outFP.write(',')
                    outFP.write(str(idx))
                    outFP.write(',')
                    outFP.write(str(i))
                    outFP.write(',')
                    outFP.write(L[1])
                    outFP.write('\n')
                    idx+=1
        
outFP.close()
