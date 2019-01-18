import sys

if(len(sys.argv) < 4):
	print('You must pass two command line arguments!')
	print('\t1. The filepath of the file to be analyzed.')
	print('\t2. The number of files to analyze')
	print('\t3. The output directory for the generated file')
	exit()
filepath = sys.argv[1]
numFiles = int(sys.argv[2])
outputDir = sys.argv[3]

batchID = filepath.split('_')[-1]

for runID in range(1, numFiles + 1):
	orgL = []
	cur = ''
	with open(filepath + '_' + str(runID) + '.txt', 'r') as fp:
		for line in fp:
			line = line.strip().replace(' ', '')
			if 'ID' in line or 'Fitness' in line: #Metadata => skip
				continue
			if line == '' and cur != '':
				orgL.append(cur)	#Blank line => push current org
				cur = ''
			else:
				cur += line	#Piece of organism

	print('Detected', len(orgL), 'organisms in run#' + str(runID) + '!')	
	with open(outputDir + '/diversity_' + batchID + '_' + str(runID) + '.csv', 'w+') as fp:
		for i in range(len(orgL)):
			A = orgL[i]
			s = ''
			for j in range(0, i+1):
				s += '-1,'
			for j in range(i+1, len(orgL)):
				B = orgL[j]
				diffs = 0
				for k in range(len(A)):
					if A[k] != B[k]:
						diffs += 1
				s += str(diffs) + ','
			fp.write(s[:-1] + '\n')
