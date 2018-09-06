import pygame
import time

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

states = []
curState = []
with open('Best.txt', 'r') as fp:
    for line in fp:
        stripped = line.strip()
        if not len(stripped) > 1:
            if curState != []:
                states.append(curState)
                curState = []
            continue
        nonData = False
        for c in stripped:
            if c not in '.XO!':
                nonData = True
        if nonData:
            continue
        curState.append(stripped)
numCols = len(states[0][0])
numRows = len(states[0])
colSpacing = SCREEN_WIDTH // numCols
rowSpacing = SCREEN_HEIGHT // numRows

curState = 0
play = False
done = False
while not done:
    evt = pygame.event.poll()
    if evt.type == pygame.KEYDOWN:
        if evt.key == pygame.K_ESCAPE or evt.key == pygame.K_q:
            done = True
        if evt.key == pygame.K_SPACE:
            curState += 1
            if curState >= len(states):
                curState = 0
        if evt.key == pygame.K_RETURN:
            play = not play
        if evt.key == pygame.K_r:
            curState = 0
    screen.fill((0,0,0))
    for i in range(numCols):
        pygame.draw.line(screen, (255,255,255), (colSpacing * i, 0), (colSpacing * i, SCREEN_HEIGHT))
    for i in range(numRows):
        pygame.draw.line(screen, (255,255,255), (0, i * rowSpacing), (SCREEN_WIDTH, rowSpacing * i))
    for j in range(numRows):
        for i in range(numCols):
            col = None
            if states[curState][j][i] == 'O':
                col = (255,0,0)
            elif states[curState][j][i] == '!':
                col = (128,0,0)
            elif states[curState][j][i] == 'X':
                col = (255,255,0)
            if col != None:
                pygame.draw.rect(screen, col, (colSpacing * i, rowSpacing * j, colSpacing, rowSpacing))
    pygame.display.flip()
    if play:
        time.sleep(0.1)
        curState += 1
        if curState >= len(states):
            curState = 0

pygame.quit()
