#pragma once

#include "basic_ea.h"

class EcoEAHandler : BasicEAHandler{
public:
    EcoEAHandler(int trialNum) : BasicEAHandler(trialNum){}; 
    std::vector<std::tuple<Individual, int>> getFitness();
    void run(int numGens);
    
protected:
    std::map<std::string, double> mTargetResources;
};

