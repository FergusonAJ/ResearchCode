
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "eco_ea.h"
#include "ea_utils.h"



void EcoEAHandler::run(int numGens){
    mResources[RESOURCE_NORTH] = 0;
    std::ofstream scoreFP, taskFP, bestTaskFP;
    std::string trialS = std::to_string(mTrialNum);
    scoreFP.open("trial_eco_ea_score_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    scoreFP << "generation, score\n";
    taskFP.open("trial_eco_ea_tasks_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    taskFP << "task, generation, count\n";
    bestTaskFP.open("trial_eco_ea_best_tasks_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    bestTaskFP << "task, generation, count\n";
    std::vector<std::tuple<Individual, double>> fitness;
    for(std::string resource : mResourceNames)
        mResources[resource] = (double)INFLOW * INIT_STEPS;
    /*
    std::map<std::string, int> spread;
    std::map<std::string, int> taskUsage;
    */
    for(int i = 0; i < numGens; i++){
        for(std::string resource : mResourceNames){
            mResources[resource] += (double)INFLOW;
            mResources[resource] -= (double)OUTFLOW * mResources[resource];
        }
        double northMax = 0;
        double southMax = 0;
        double eastMax = 0;
        double westMax = 0;
        fitness.clear();
        for(Individual ind : mCurGen){
            fitness.push_back(std::make_tuple(ind, ind.getFitness(mResources)));
            if(ind.northCount > northMax)
                northMax = ind.northCount;
            if(ind.southCount > southMax)
                southMax = ind.southCount;
            if(ind.eastCount > eastMax)
                eastMax = ind.eastCount;
            if(ind.westCount > westMax)
                westMax = ind.westCount;
            ind.reset(); 
        }
        std::sort(fitness.begin(), fitness.end(), compareHelper);
        if(i % DATA_TRIM_FACTOR == 0){
            scoreFP << i << ",";
            Individual ind = std::get<0>(fitness[0]);
            scoreFP << std::get<1>(fitness[0]) << "\n";
            taskFP << "north, " << i << ", " << northMax << "\n";
            taskFP << "south, " << i << ", " << southMax << "\n";
            taskFP << "east, " << i << ", " << eastMax << "\n";
            taskFP << "west, " << i << ", " << westMax << "\n";
            bestTaskFP << "north, " << i << ", " << ind.northCount << "\n";
            bestTaskFP << "south, " << i << ", " << ind.southCount << "\n";
            bestTaskFP << "east, " << i << ", " << ind.eastCount << "\n";
            bestTaskFP << "west, " << i << ", " << ind.westCount << "\n";
        }
        getNextGen(fitness);
    }
    writePopulationToFile(fitness, "trial_eco_ea_" + trialS + ".txt");
    writeBestToFile(fitness[0], "trial_eco_ea_best_" + trialS + ".txt", numGens);
    scoreFP.close();
    taskFP.close();
    bestTaskFP.close();
}
