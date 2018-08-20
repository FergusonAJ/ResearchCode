// Simple class implementing a naive evolutioanry algorithm
// 8/20/18
// Austin Ferguson

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
    std::vector<std::tuple<Individual, int>> getFitness();
    void run(int numGens);
    void getNextGen(std::vector<std::tuple<Individual, int>> fitness);
    std::map<std::string, int> getSpread();
    std::map<std::string, int> getTaskUsage();

protected:
    int mGenSize, mTrialNum;
    std::vector<Individual> mCurGen;
    std::vector<std::string> mTargets;
};

