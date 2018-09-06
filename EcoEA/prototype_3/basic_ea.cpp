// Simple class implementing a naive evolutioanry algorithm
// 8/20/18
// Austin Ferguson

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "basic_ea.h"
#include "ea_utils.h"


BasicEAHandler::BasicEAHandler(int trialNum){
    mTrialNum = trialNum;
    mGenSize = GEN_SIZE;
    mCurGen = std::vector<Individual>(mGenSize, Individual());
}

BasicEAHandler::~BasicEAHandler(){
    mCurGen.clear();
}

void BasicEAHandler::printCurGen(){
    for(int i = 0; i < mGenSize; i++){
        std::cout << mCurGen[i].getString() << std::endl;
    }
}

void BasicEAHandler::run(int numGens){
    std::ofstream scoreFP, taskFP, bestTaskFP;
    std::string trialS = std::to_string(mTrialNum);
    scoreFP.open("trial_naive_score_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    scoreFP << "generation, score\n";
    taskFP.open("trial_naive_tasks_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    taskFP << "task, generation, count\n";
    bestTaskFP.open("trial_naive_best_tasks_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    bestTaskFP << "task, generation, count\n";
    std::vector<std::tuple<Individual, double>> fitness;
    std::map<std::string, double> dummyMap;
    dummyMap.clear();
    /*
    std::map<std::string, int> spread;
    std::map<std::string, int> taskUsage;
    */
    for(int i = 0; i < numGens; i++){
        double northMax = 0;
        double southMax = 0;
        double eastMax = 0;
        double westMax = 0;
        fitness.clear();
        for(Individual ind : mCurGen){
            fitness.push_back(std::make_tuple(ind, ind.getFitness(dummyMap)));
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
            /*
            spread = getSpread();
            taskUsage = getTaskUsage();
            */
            Individual ind = std::get<0>(fitness[0]);
            double score = std::get<1>(fitness[0]);
            scoreFP << i << ",";
            scoreFP << score << "\n";
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
    writePopulationToFile(fitness, "trial_naive_" + trialS + ".txt");
    writeBestToFile(fitness[0], "trial_naive_best_" + trialS + ".txt", numGens);
    scoreFP.close();
    taskFP.close();
    bestTaskFP.close();
}

void BasicEAHandler::getNextGen(std::vector<std::tuple<Individual, double>> fitness){
    std::vector<Individual> newGen;
    int numCarry = (int)(PCT_CARRY * (float)mGenSize);
    for(int i = 0; i < numCarry; i++){
        int idx = (int)(pow((double)rand() / RAND_MAX, 3) * mGenSize);
        newGen.push_back(std::get<0>(fitness[idx]));
    }
    int numMut = (int)(PCT_MUT * (float)mGenSize);
    for(int i = 0; i < numMut; i++){
        int idx = (int)(pow((double)rand() / RAND_MAX, 3) * mGenSize);
        newGen.push_back(std::get<0>(fitness[idx]).getMutation());
    }
    int numCross = (int)(PCT_CROSS * (float)mGenSize);
    for(int i = 0; i < numCross; i++){
        int idxA = (int)(pow((double)rand() / RAND_MAX, 3) * mGenSize);
        int idxB = (int)(pow((double)rand() / RAND_MAX, 3) * mGenSize);
        newGen.push_back(std::get<0>(fitness[idxA]).getCrossover(std::get<0>(fitness[idxB])));
    }
    int numRandom = GEN_SIZE - newGen.size();
    for(int i = 0; i < numRandom; i++){    
        Individual ind;
        newGen.push_back(ind);
    }
    mCurGen.clear();
    for(Individual ind : newGen){
        mCurGen.push_back(ind);
    }
}

std::map<std::string, int> BasicEAHandler::getSpread(){
    std::map<std::string, int> M;
    for(std::string target : mTargets){
        M[target] = 0;
        int length = target.length();
        for(Individual ind : mCurGen){
            std::string s = ind.getString();    
            int matches = 0;
            for(int i = 0; i < length; i++){
                if(target[i] == s[i])
                    matches++;
            }
            if(matches > M[target])
                M[target] = matches;
        }
    }
    return M;
}

std::map<std::string, int> BasicEAHandler::getTaskUsage(){
    std::map<std::string, int> M;
    for(std::string target : mTargets){
        M[target] = 0;
        int length = target.length();
        for(Individual ind : mCurGen){
            std::string s = ind.getString();    
            int score = 0;
            for(int i = 0; i < length; i++){
                if(target[i] == s[i])
                    score += 1;
            }
                M[target]++;
        }
    }
    return M;
}

void BasicEAHandler::writePopulationToFile(
    std::vector<std::tuple<Individual, double>>& fitness, std::string fileName){
    std::ofstream fp;
    fp.open(fileName, std::ios::out | std::ios::trunc);
    fp << "\n" << "Fitness Data" << "\n";
    fp << "########################\n";
    for(std::tuple<Individual, double> t : fitness){
        Individual ind = (Individual)std::get<0>(t);
        ind.reset();
        double score = (double)std::get<1>(t);
        fp << ind.getString() << " " << score << "\n\n";
    }
    fp.close();
}

void BasicEAHandler::writeBestToFile(
    std::tuple<Individual, double>& data, std::string fileName, int numGens){
    std::ofstream fp;
    Individual ind = (Individual)std::get<0>(data);
    double score = (double)std::get<1>(data);
    fp.open(fileName, std::ios::out | std::ios::trunc);
    fp  << "Best Individual After " << numGens <<" Generations\n";
    fp  << "Score: " << score << "\n";
    ind.reset(); 
    for(int i = 0; i < NUM_TICKS; i++){
        ind.tick();
        ind.edgeClear();
        fp << "Step #" << i << "\n";
        fp << ind.getString() << "\n\n";
    }
    fp  << "Counts: \n";
    fp  << "\tNorth:" << ind.northCount << "\n";
    fp  << "\tSouth:" << ind.southCount << "\n";
    fp  << "\tEast:" << ind.eastCount << "\n";
    fp  << "\tWest:" << ind.westCount << "\n";
    fp  << "Subscores: \n";
    fp  << "\tNorth:" << ind.northScore << "\n";
    fp  << "\tSouth:" << ind.southScore << "\n";
    fp  << "\tEast:" << ind.eastScore << "\n";
    fp  << "\tWest:" << ind.westScore << "\n";
    fp.close(); 
}
