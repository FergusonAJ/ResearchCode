// Class defining one individual in the EA's population. Currently just a string wrapper.
// 8/20/18
// Austin Ferguson

#include <cstring>
#include <math.h>

#include "individual.h"
#include "conway.h"

Individual::Individual(){
    mData = new unsigned char[NUM_ROWS * NUM_COLS];
    mSafeData = new unsigned char[NUM_ROWS * NUM_COLS];
    std::memset(mData, EMPTY, NUM_ROWS * NUM_COLS);
    for(int i = 0; i < NUM_COLS * NUM_ROWS; i++)
        if((double)rand() / RAND_MAX < INIT_WIRE_PCT)
            mData[i] = WIRE;
    mData[ELECTRON_ROW * NUM_COLS + ELECTRON_COL] = HEAD;
    std::memcpy(mSafeData, mData, NUM_COLS * NUM_ROWS);
}

Individual::Individual(unsigned char* data){
    mData = new unsigned char[NUM_ROWS * NUM_COLS];
    mSafeData = new unsigned char[NUM_ROWS * NUM_COLS];
    std::memcpy(mData, data, NUM_COLS * NUM_ROWS);
    for(int i = 0; i < NUM_ROWS * NUM_COLS; i++){
        if(mData[i] != WIRE && mData[i] != EMPTY) // HEAD or TAIL
            mData[i] = WIRE;
    }
    mData[ELECTRON_ROW * NUM_COLS + ELECTRON_COL] = HEAD;
    std::memcpy(mSafeData, mData, NUM_COLS * NUM_ROWS);
}

Individual::Individual(const Individual& ind){
    mData = new unsigned char[NUM_ROWS * NUM_COLS];
    mSafeData = new unsigned char[NUM_ROWS * NUM_COLS];
    std::memcpy(mSafeData, ind.mSafeData, NUM_COLS * NUM_ROWS);
    std::memcpy(mData, ind.mData, NUM_COLS * NUM_ROWS);
    northCount = ind.northCount;
    northScore = ind.northScore;
    southCount = ind.southCount;
    southScore = ind.southScore;
    eastCount = ind.eastCount;
    eastScore = ind.eastScore;
    westCount = ind.westCount;
    westScore = ind.westScore;
}

Individual::~Individual(){
    delete[] mData;
    delete[] mSafeData;
}

Individual& Individual::operator=(Individual other){
    mData = new unsigned char[NUM_ROWS * NUM_COLS];
    mSafeData = new unsigned char[NUM_ROWS * NUM_COLS];
    std::memcpy(mSafeData, other.mSafeData, NUM_COLS * NUM_ROWS);
    std::memcpy(mData, other.mData, NUM_COLS * NUM_ROWS);
    northCount = other.northCount;
    northScore = other.northScore;
    southCount = other.southCount;
    southScore = other.southScore;
    eastCount = other.eastCount;
    eastScore = other.eastScore;
    westCount = other.westCount;
    westScore = other.westScore;
}

void Individual::print(){
    for(int j = 1; j < NUM_ROWS - 1; j++){
        for(int i = 1; i < NUM_COLS - 1; i++){
            std::cout << mData[j * NUM_COLS + i];
        }
        std::cout << std::endl;
    }
}

void Individual::tick(){
    UpdateGeneration(mData);
}

double Individual::getFitness(std::map<std::string, double>& resources){
    double score = 0;
    northCount = southCount = eastCount = westCount = 0;
    northScore = southScore = eastScore = westScore = 0;
    for(int t = 0; t < NUM_TICKS; t++){
        tick();
        for(int i = 1; i < NUM_COLS - 1; i++){
            if(mData[i] == POINT_STATE){
                northCount++;
                //mData[i] = CLEAR_STATE;
            }
            if(mData[(NUM_ROWS - 1) * NUM_COLS + i] == POINT_STATE){
                southCount++;
                //mData[(NUM_ROWS - 1) * NUM_COLS + i] = CLEAR_STATE;
            }
        }
        for(int j = 1; j < NUM_ROWS - 1; j++){
            if(mData[j * NUM_COLS] == POINT_STATE){
                westCount++;
                //mData[j * NUM_COLS] = CLEAR_STATE;
            }
            if(mData[(j + 1) * NUM_COLS - 1] == POINT_STATE){
                eastCount++;
                //mData[(j+1) * NUM_COLS - 1] = CLEAR_STATE;
            }
        }
    }
    if(CLEAR_EDGES)
        edgeClear();
    for(int i = 0; i < northCount; i++){
        northScore += 1.0/pow(SCORE_BASE, i);
    }
    for(int i = 0; i < southCount; i++){
        southScore += 1.0/pow(SCORE_BASE, i);
    }
    for(int i = 0; i < eastCount; i++){
        eastScore += 1.0/pow(SCORE_BASE, i);
    }
    for(int i = 0; i < westCount; i++){
        westScore += 1.0/pow(SCORE_BASE, i);
    }
    northScore = northCount;
    southScore = southCount;
    eastScore = eastCount;
    westScore = westCount; 

    if(!resources.empty()){
        northScore = northScore * CONSUMPTION_FRAC * resources[RESOURCE_NORTH];
        northScore = (northScore > MAX_AMOUNT) ? MAX_AMOUNT : northScore;
        resources[RESOURCE_NORTH] -= northScore;
        southScore = southScore * CONSUMPTION_FRAC * resources[RESOURCE_SOUTH];
        southScore = (southScore > MAX_AMOUNT) ? MAX_AMOUNT : southScore;
        resources[RESOURCE_SOUTH] -= southScore;
        eastScore = eastScore * CONSUMPTION_FRAC * resources[RESOURCE_EAST];
        eastScore = (eastScore > MAX_AMOUNT) ? MAX_AMOUNT : eastScore;
        resources[RESOURCE_EAST] -= eastScore;
        westScore = westScore * CONSUMPTION_FRAC * resources[RESOURCE_WEST];
        westScore = (westScore > MAX_AMOUNT) ? MAX_AMOUNT : westScore;
        resources[RESOURCE_WEST] -= westScore;
    } 
    score = northScore + southScore + eastScore + westScore;
    return score;
}

void Individual::reset(){
    std::memcpy(mData, mSafeData, NUM_COLS * NUM_ROWS);
    mData[ELECTRON_ROW * NUM_COLS + ELECTRON_COL] = HEAD;
}

std::string Individual::getString(){
    std::string s;
    for(int j = 0; j < NUM_ROWS; j++){
        for(int i = 0; i < NUM_COLS; i++){
            s += mData[j * NUM_COLS + i];
        }
        s += "\n";
    }
    return s;
}

Individual Individual::getMutation(){
    unsigned char* tmpData = new unsigned char[NUM_ROWS * NUM_COLS];
    for(int i = 0; i < NUM_COLS * NUM_ROWS; i++){
        if((double)rand() / RAND_MAX < MUT_RATE){
            if(mData[i] == EMPTY)
                tmpData[i] = WIRE;
            else
                tmpData[i] = EMPTY;
        }
        else{
            tmpData[i] = mData[i];
        }
    }
    return Individual(tmpData);
}

Individual Individual::getCrossover(Individual other){
    unsigned char* tmpData = new unsigned char[NUM_ROWS * NUM_COLS];
    for(int i = 0; i < NUM_COLS * NUM_ROWS; i++){
        if((double)rand() / RAND_MAX < 0.5f)
            tmpData[i] = mData[i];
        else
            tmpData[i] = other.mData[i];
    }
    return Individual(tmpData);
}

void Individual::edgeClear(){
     if(CLEAR_EDGES){
         for(int i = 1; i < NUM_COLS - 1; i++){
            if(mData[i] == POINT_STATE){
                mData[i] = CLEAR_STATE;
            }
            if(mData[(NUM_ROWS - 1) * NUM_COLS + i] == POINT_STATE){
                mData[(NUM_ROWS - 1) * NUM_COLS + i] = CLEAR_STATE;
            }
        }
        for(int j = 1; j < NUM_ROWS - 1; j++){
            if(mData[j * NUM_COLS] == POINT_STATE){
                mData[j * NUM_COLS] = CLEAR_STATE;
            }
            if(mData[(j + 1) * NUM_COLS - 1] == POINT_STATE){
                mData[(j+1) * NUM_COLS - 1] = CLEAR_STATE;
            }
        }
    }
}
