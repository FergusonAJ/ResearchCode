#pragma once

#include "basic_ea.h"

class EcoEAHandler : BasicEAHandler{
public:
    EcoEAHandler(int trialNum) : BasicEAHandler(trialNum){
        mResourceNames.push_back(RESOURCE_NORTH);
        mResourceNames.push_back(RESOURCE_SOUTH);
        mResourceNames.push_back(RESOURCE_EAST);
        mResourceNames.push_back(RESOURCE_WEST);
    }; 
    std::vector<std::tuple<Individual, double>> getFitness();
    void run(int numGens);
    
protected:
    std::map<std::string, double> mResources;
    std::vector<std::string> mResourceNames;
};

