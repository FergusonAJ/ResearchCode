import sys
import pygame

if len(sys.argv) == 1:
    print('You must specify a .txt!\n')
    quit()


values = []
with open(sys.argv[1], 'r') as fp:
    for line in fp:
        tmp = []
        line = line.strip()
        L = line.split()
        for c in L:
            if c == '1':
                tmp.append(True)
            else:
                tmp.append(False)
        if len(tmp) != 0:
            values.append(tmp)


pygame.init()
w = len(values[0])
h = len(values)
surf = pygame.Surface((w, h))
for y in range(h):
    for x in range(w):
        if values[y][x]:
            surf.set_at((x,y), (255,255,255))
        else:
            surf.set_at((x,y), (0,0,0))
pygame.image.save(surf, 'output.png')
