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
outFP.write('arr_id,gen,min,max,avg\n')

for arr_id in range(1, 51):
    filename = prefix + '_' + job_id + '_' + str(arr_id) + '.csv'
    if not os.path.isfile(filename):
        print('Stopping at', arr_id)
        print('Was looking for (' + filename + ')!')
        continue
    idx = 0
    with open(filename, 'r') as inFP:
        for line in inFP:
            line = line.strip()
            if 'update' not in line:
                L = line.split(',')
                if len(L) > 4:
                    outFP.write(str(arr_id))
                    outFP.write(',')
                    outFP.write(L[0])
                    outFP.write(',')
                    outFP.write(L[2])
                    outFP.write(',')
                    outFP.write(L[3])
                    outFP.write(',')
                    outFP.write(L[1])
                    outFP.write('\n')
                    idx+=1
        
outFP.close()
