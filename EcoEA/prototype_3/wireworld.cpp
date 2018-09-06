#include "wireworld.h"
#include <cstring>

void UpdateGeneration(unsigned char* oldGen){
    unsigned char* newGen = new unsigned char[NUM_ROWS * NUM_COLS];
    for(int j = 0; j < NUM_COLS; j++){
        for(int i = 0; i < NUM_ROWS; i++){
            unsigned char c = oldGen[j * NUM_COLS + i];
            switch(c){
                case EMPTY:
                    newGen[j * NUM_COLS + i] = EMPTY;
                    break;
                case HEAD:
                    newGen[j * NUM_COLS + i] = TAIL;
                    break;
                case TAIL:
                    newGen[j * NUM_COLS + i] = WIRE;
                    break;
                case WIRE:
                    unsigned char neighbors = 0;
                    if(j > 0){
                        if(oldGen[(j-1) * NUM_COLS + i] == HEAD)
                            neighbors++;
                        if (i > 0 && oldGen[(j-1) * NUM_COLS + i - 1] == HEAD)
                            neighbors++;
                        if (i < NUM_COLS - 1 && oldGen[(j-1) * NUM_COLS + i + 1] == HEAD)
                            neighbors++;
                    }
                    if(j < NUM_ROWS - 1){
                        if(oldGen[(j+1) * NUM_COLS + i] == HEAD)
                            neighbors++;
                        if (i > 0 && oldGen[(j+1) * NUM_COLS + i - 1] == HEAD)
                            neighbors++;
                        if (i < NUM_COLS - 1 && oldGen[(j+1) * NUM_COLS + i + 1] == HEAD)
                            neighbors++;
                    }
                    if (i > 0 && oldGen[j * NUM_COLS + i - 1] == HEAD)
                        neighbors++;
                    if (i < NUM_COLS - 1 && oldGen[j * NUM_COLS + i + 1] == HEAD)
                        neighbors++;   
                    if (neighbors == 1 || neighbors == 2)
                        newGen[j * NUM_COLS + i] = HEAD;
                    else
                        newGen[j * NUM_COLS + i] = WIRE;
                    break;
            }
        }
    }
    std::memcpy(oldGen, newGen, NUM_COLS * NUM_ROWS);
    delete[] newGen;
}
