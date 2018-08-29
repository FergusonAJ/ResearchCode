// Simple class implementing a naive evolutioanry algorithm
// 8/20/18
// Austin Ferguson

#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <map>

#include "individual.h"

class BasicEAHandler{
public:
    BasicEAHandler(int trialNum);
    ~BasicEAHandler();
    void printCurGen();
    void printTargets();
    virtual std::vector<std::tuple<Individual, double>> getFitness();
    virtual void run(int numGens);
    void getNextGen(std::vector<std::tuple<Individual, double>> fitness);
    std::map<std::string, int> getSpread();
    std::map<std::string, int> getTaskUsage();
    void writePopulationToFile(std::vector<std::tuple<Individual, double>>& fitness, std::string fileName);
protected:
    int mGenSize, mTrialNum;
    std::vector<Individual> mCurGen;
    std::vector<std::string> mTargets;
};

inline bool compareHelper(std::tuple<Individual, double> a, std::tuple<Individual, double> b) { 
    return (std::get<1>(a) > std::get<1>(b)); 
}
