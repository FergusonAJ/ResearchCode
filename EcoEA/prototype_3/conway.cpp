#include "conway.h"
#include <cstring>

void UpdateGeneration(unsigned char* oldGen){
    unsigned char* newGen = new unsigned char[NUM_ROWS * NUM_COLS];
    for(int j = 0; j < NUM_COLS; j++){
        for(int i = 0; i < NUM_ROWS; i++){
            unsigned char c = oldGen[j * NUM_COLS + i];
            unsigned char neighbors = 0;
            if(j > 0){
                if(oldGen[(j-1) * NUM_COLS + i] == WIRE)
                    neighbors++;
                if (i > 0 && oldGen[(j-1) * NUM_COLS + i - 1] == WIRE)
                    neighbors++;
                if (i < NUM_COLS - 1 && oldGen[(j-1) * NUM_COLS + i + 1] == WIRE)
                    neighbors++;
            }
            else{
                if(oldGen[(NUM_ROWS-1) * NUM_COLS + i] == WIRE)
                    neighbors++;
                if (i > 0 && oldGen[(NUM_ROWS-1) * NUM_COLS + i - 1] == WIRE)
                    neighbors++;
                if (i < NUM_COLS - 1 && oldGen[(NUM_ROWS-1) * NUM_COLS + i + 1] == WIRE)
                    neighbors++;
            }
            if(j < NUM_ROWS - 1){
                if(oldGen[(j+1) * NUM_COLS + i] == WIRE)
                    neighbors++;
                if (i > 0 && oldGen[(j+1) * NUM_COLS + i - 1] == WIRE)
                    neighbors++;
                if (i < NUM_COLS - 1 && oldGen[(j+1) * NUM_COLS + i + 1] == WIRE)
                    neighbors++;
            }
            else{
                if(oldGen[i] == WIRE)
                    neighbors++;
                if (i > 0 && oldGen[i - 1] == WIRE)
                    neighbors++;
                if (i < NUM_COLS - 1 && oldGen[i + 1] == WIRE)
                    neighbors++;
            }
            if (i > 0 && oldGen[j * NUM_COLS + i - 1] == WIRE)
                neighbors++;
            if (i == 0 && oldGen[j * NUM_COLS + (NUM_COLS-1)] == WIRE)
                neighbors++;
            if (i < NUM_COLS - 1 && oldGen[j * NUM_COLS + i + 1] == WIRE)
                neighbors++;   
            if (i == NUM_COLS - 1 && oldGen[j * NUM_COLS] == WIRE)
                neighbors++;   
            if (neighbors <= 1 || neighbors >= 4)
                newGen[j * NUM_COLS + i] = EMPTY;
            else if (neighbors == 2)
                newGen[j * NUM_COLS + i] = oldGen[j * NUM_COLS + i];
            else if (neighbors == 3)
                newGen[j * NUM_COLS + i] = WIRE;
        }
    }
    std::memcpy(oldGen, newGen, NUM_COLS * NUM_ROWS);
    delete[] newGen;
}
