// Simple class implementing a naive evolutioanry algorithm
// 8/20/18
// Austin Ferguson

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "basic_ea.h"
#include "ea_utils.h"

bool compareHelper(std::tuple<Individual, int> a, std::tuple<Individual, int> b) { 
    return (std::get<1>(a) > std::get<1>(b)); 
}

BasicEAHandler::BasicEAHandler(int trialNum){
    mTrialNum = trialNum;
    mGenSize = GEN_SIZE;
    std::vector<std::string> dataVec = genRandomStrings(mGenSize);
    for(int i = 0; i < mGenSize; i++){
        mCurGen.push_back(Individual(dataVec[i]));
    }

    mTargets = genRandomStrings(NUM_STRINGS);
}

BasicEAHandler::~BasicEAHandler(){

}

void BasicEAHandler::printCurGen(){
    for(int i = 0; i < mGenSize; i++){
        std::cout << mCurGen[i] << std::endl;
    }
}

void BasicEAHandler::printTargets(){
    for(int i = 0; i < mTargets.size(); i++){
        std::cout << mTargets[i] << std::endl;
    }
}
    
std::vector<std::tuple<Individual, int>> BasicEAHandler::getFitness(){
    std::vector<std::tuple<Individual, int>> result;
    for(Individual curInd : mCurGen){
        std::string s = curInd.getString();
        int score = 0;
        for(std::string target : mTargets){
            int matches = 0;
            int length = target.length();
            //If we ever have variable length strings, look at this
            for(int i = 0; i < length; i++){
                if(s[i] == target[i])
                    matches++;
            } 
            int S = 0;
            int bonus = 0;
            if(matches > length / 2)
                S = pow((((2 * matches) / length) - 1), 2 * SPECIATION_FACTOR);
            bonus = pow(2, S) * 5;
            score += bonus;
        }
        result.push_back(std::make_tuple(curInd, score));
    }
    std::sort(result.begin(), result.end(), compareHelper); 
    return result;
}

void BasicEAHandler::run(int numGens){
    std::ofstream fullMatchFP;
    std::ofstream charMatchFP;
    std::string trialS = std::to_string(mTrialNum);
    fullMatchFP.open("trial_naive_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    fullMatchFP << "target, generation, matches\n";
    charMatchFP.open("trial_naive_char_match_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    charMatchFP << "target, generation, char_matches\n";
    std::vector<std::tuple<Individual, int>> fitness;
    std::map<std::string, int> spread;
    std::map<std::string, int> taskUsage;
    for(int i = 0; i < numGens; i++){
        fitness = getFitness();
        spread = getSpread();
        taskUsage = getTaskUsage();
        for(std::string target : mTargets){
            fullMatchFP << target << ",";
            fullMatchFP << i << ",";
            fullMatchFP << taskUsage[target] << "\n";
            charMatchFP << target << ",";
            charMatchFP << i << ",";
            charMatchFP << spread[target] << "\n";
        }
        getNextGen(fitness);
    }
    writePopulationToFile(fitness, "trial_naive_" + trialS + ".txt");
    fullMatchFP.close();
    charMatchFP.close();
}

void BasicEAHandler::getNextGen(std::vector<std::tuple<Individual, int>> fitness){
    std::vector<Individual> newGen;
    for(int i = 0; i < (int)(PCT_CARRY * mGenSize); i++){
        int idx = (int)pow((double)rand() / RAND_MAX, 3) * mGenSize;
        newGen.push_back(std::get<0>(fitness[idx]));
    }
    for(int i = 0; i < (int)(PCT_MUT * mGenSize); i++){
        int idx = (int)pow((double)rand() / RAND_MAX, 3) * mGenSize;
        newGen.push_back(std::get<0>(fitness[idx]).getMutation());
    }
    for(int i = 0; i < (int)(PCT_CROSS * mGenSize); i++){
        int idxA = (int)pow((double)rand() / RAND_MAX, 3) * mGenSize;
        int idxB = (int)pow((double)rand() / RAND_MAX, 3) * mGenSize;
        newGen.push_back(std::get<0>(fitness[idxA]).getCrossover(std::get<0>(fitness[idxB])));
    }
    int numRandom = GEN_SIZE - newGen.size();
    for(std::string s : genRandomStrings(numRandom)){
        newGen.push_back(Individual(s));
    }
    mCurGen.clear();
    for(Individual ind : newGen)
        mCurGen.push_back(ind);
}

std::map<std::string, int> BasicEAHandler::getSpread(){
    std::map<std::string, int> M;
    for(std::string target : mTargets){
        int length = target.length();
        int score = 0;
        for(Individual ind : mCurGen){
            std::string s = ind.getString();    
            int matches = 0;
            for(int i = 0; i < length; i++){
                if(target[i] == s[i])
                    matches++;
            }
            score += matches;
        }
        M[target] = score;
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
            if(score >= STRING_LENGTH * TASK_PCT)
                M[target]++;
        }
    }
    return M;
}

void BasicEAHandler::writePopulationToFile(
    std::vector<std::tuple<Individual, int>>& fitness, std::string fileName){
    std::ofstream fp;
    fp.open(fileName, std::ios::out | std::ios::trunc);
    fp << "Targets\n";
    fp << "########################\n";
    for(std::string target : mTargets)
        fp << target << "\n";
    fp << "\n" << "Fitness Data" << "\n";
    fp << "########################\n";
    for(std::tuple<Individual, int> t : fitness){
        Individual ind = (Individual)std::get<0>(t);
        int score = (int)std::get<1>(t);
        fp << ind.getString() << " -> " << score << "\n";
    }
    fp.close();
}
