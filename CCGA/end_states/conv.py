import pygame

pygame.init()

img = pygame.image.load('smile.png')

with open('smile.txt', 'w') as fp:
    for y in range(img.get_height()):
        for x in range(img.get_width()):
            if img.get_at((x,y)) == (0,0,0):
                fp.write('#')
            else:
                fp.write('.')
        fp.write('\n')
