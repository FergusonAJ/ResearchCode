import os
import sys


if len(sys.argv) < 2:
    print('You have to pass the filepath of the directory to explore!')
    quit()

idStrL = []

with open('tmpClassic.sh', 'w') as fp:
    for _, _, files in os.walk(sys.argv[1]):
        for fileName in files:
            withoutExt = fileName.split('.')[0]
            tmpL = withoutExt.split('_')
            idStr = '_' + tmpL[4] + '_' + tmpL[5]
            if idStr not in idStrL:
                idStrL.append(idStr)

    for idStr in idStrL:
        print(idStr)
        fp.write('python3 classicScrape.py ' + sys.argv[1] + ' ' + idStr+ '\n')
        fp.write('Rscript --vanilla classic.r ' + idStr + '\n')
        
        
