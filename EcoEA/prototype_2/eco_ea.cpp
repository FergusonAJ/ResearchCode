
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "eco_ea.h"
#include "ea_utils.h"


std::vector<std::tuple<Individual, double>> EcoEAHandler::getFitness(){
    std::vector<std::tuple<Individual, double>> result;
    for(Individual curInd : mCurGen){
        std::string s = curInd.getString();
        double score = 0;
        for(std::string target : mTargets){
            int matches = 0;
            int length = target.length();
            //If we ever have variable length strings, look at this
            for(int i = 0; i < length; i++){
                if(s[i] == target[i])
                    matches++;
            } 
            double S = 0;
            double bonus = 0;
            if(matches > (float)length / 2)
                S = pow((((2.0 * matches) / length) - 1), 2.0f * SPECIATION_FACTOR);
            if(S == 0)
                S = matches / 1000.0f;
            double tmpA = S * CONSUMPTION_FRAC * mTargetResources[target];
            double A = (tmpA > MAX_AMOUNT) ? MAX_AMOUNT: tmpA;
            mTargetResources[target] -= A;
            bonus = pow(2.0f, A);
            score += bonus;
        }
        result.push_back(std::make_tuple(curInd, score));
    }
    std::sort(result.begin(), result.end(), compareHelper); 
    return result;
}

void EcoEAHandler::run(int numGens){
    for(std::string target : mTargets)
        mTargetResources[target] = (double)INFLOW * INIT_STEPS;
    std::ofstream fullMatchFP;
    std::ofstream charMatchFP;
    std::ofstream resourceFP;
    std::string trialS = std::to_string(mTrialNum);
    fullMatchFP.open("trial_eco_ea_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    fullMatchFP << "target, generation, matches\n";
    charMatchFP.open("trial_eco_ea_char_match_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    charMatchFP << "target, generation, char_matches\n";
    resourceFP.open("trial_eco_ea_resources_" + trialS + ".csv", std::ios::out | std::ios::trunc);
    resourceFP << "target, generation, resources\n";
    std::vector<std::tuple<Individual, double>> fitness;
    std::map<std::string, int> spread;
    std::map<std::string, int> taskUsage;
    for(int i = 0; i < numGens; i++){
        for(std::string target : mTargets){
            mTargetResources[target] += (double)INFLOW;
            mTargetResources[target] -= mTargetResources[target] * (double)OUTFLOW;
        }
        fitness = getFitness();
        if(i% DATA_TRIM_FACTOR == 0){
            spread = getSpread();
            taskUsage = getTaskUsage();
            for(std::string target : mTargets){
                fullMatchFP << target << ",";
                fullMatchFP << i << ",";
                fullMatchFP << taskUsage[target] << "\n";
                charMatchFP << target << ",";
                charMatchFP << i << ",";
                charMatchFP << spread[target] << "\n";
                resourceFP << target << ",";
                resourceFP << i << ",";
                resourceFP << mTargetResources[target] << "\n";
            }
        }
        getNextGen(fitness);
    }
    writePopulationToFile(fitness, "trial_eco_ea_" + trialS + ".txt");
    fullMatchFP.close();
    charMatchFP.close();
}
