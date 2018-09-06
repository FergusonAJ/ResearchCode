// Class defining one individual in the EA's population. Currently just a string wrapper.
// 8/20/18
// Austin Ferguson

#pragma once

#include <string>
#include <iostream>
#include <map>

#include "constants.h"

class Individual{
public:
    Individual();
    Individual(unsigned char* data);
    Individual(const Individual& ind);
    ~Individual();
    void print();
    void tick();
    void reset();
    double getFitness(std::map<std::string, double>& resources);
    std::string getString();
    Individual getMutation();
    Individual getCrossover(Individual other);
    Individual& operator=(Individual other);
    void edgeClear();   
 
    unsigned char* mData;
    unsigned char* mSafeData;
    int northCount, southCount, eastCount, westCount;
    double northScore, southScore, eastScore, westScore;
};

