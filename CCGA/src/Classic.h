#pragma once
#include "OrganismShared.h"
#include "Evolve/World.h"

//Variables
emp::World<emp::vector<bool>>* icWorldPtr;
emp::World<emp::vector<bool>>* rulesetWorldPtr;
std::multimap<double, size_t>* icFitnessMapPtr;
std::multimap<double, size_t>* rulesetFitnessMapPtr;

//Utility functions
void SetICWorldPtr(emp::World<emp::vector<bool>>* ptr){
    icWorldPtr = ptr;
}
void SetRulesetWorldPtr(emp::World<emp::vector<bool>>* ptr){
    rulesetWorldPtr = ptr;
}
void SetICFitnessMapPtr(std::multimap<double, size_t>* ptr){
    icFitnessMapPtr = ptr;
}
void SetRulesetFitnessMapPtr(std::multimap<double, size_t>* ptr){
    rulesetFitnessMapPtr = ptr;
}

//Generate a new IC
std::vector<bool> GetRandomOrg_Classic_IC(emp::Random& rand){
    return GenerateRandomBitstring(rand, width * height);
}

//Generate a new ruleset
std::vector<bool> GetRandomOrg_Classic_Ruleset(emp::Random& rand){
    return GenerateRandomBitstring(rand, 18);
}

//Print function - IC
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_classic_ic = [](std::vector<bool> & org, std::ostream & os) {
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            os << (org[x + y * width]? "1" : "0") << " ";
        }
        os << std::endl;
    }
    os << std::endl;
};

//Print function - Ruleset
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_classic_ruleset = [](std::vector<bool> & org, std::ostream & os) {
    os << "B";
    unsigned int a = 1;
    for(int i = 0; i < 9; i++){
        if(org[i] && (bBlackMask & a) == 0)
            os << i;
        a *= 2;
    }
    os << "/S";
    a = 1;
    for(int i = 0; i < 9; i++){
        if(org[i+9] && (sBlackMask & a) == 0)
            os << i;
        a *= 2;
    }
    os << std::endl;
};


//Fitness function - IC - Matching
auto fit_fun_match_classic_ic = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    auto iter = rulesetFitnessMapPtr->rbegin();
    for(size_t i = 0; i < numBestCollaborators; i++){
        ca.Reset();
        ca.AddSubsurface(tmp, 0, 0, width);
        if(rulesetFitnessMapPtr->size() > i){
            idx = iter->second;
            iter++;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){
        ca.Reset();
        ca.AddSubsurface(tmp, 0, 0, width);
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};

//Fitness function - IC - Static/Repeating or Gliders
auto fit_fun_static_rep_classic_ic = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    auto iter = rulesetFitnessMapPtr->rbegin();
    for(size_t i = 0; i < numBestCollaborators; i++){
        ca.Reset();
        ca.AddSubsurface(tmp, 0, 0, width);
        if(rulesetFitnessMapPtr->size() > i){
            idx = iter->second;
            iter++;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){
        ca.Reset();
        ca.AddSubsurface(tmp, 0, 0, width);
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};

//Fitness function - Ruleset - Matching
auto fit_fun_match_classic_ruleset = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    std::vector<unsigned char> tmp;
    double max = 0;
    double score = 0;
    size_t idx = 0;
    auto iter = icFitnessMapPtr->rbegin();
    for(size_t i = 0; i < numBestCollaborators; i++){  
        ca.Reset();
        if(icFitnessMapPtr->size() > i){ 
            idx = iter->second;
            iter++;
        } 
        else{      
            idx = randPtr->GetUInt(0, icWorldPtr->GetSize());   
        }
        std::vector<unsigned char> tmp = BitstringToVec(icWorldPtr->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, width);
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){  
        ca.Reset();
        idx = randPtr->GetUInt(0, icWorldPtr->GetSize());   
        std::vector<unsigned char> tmp = BitstringToVec(icWorldPtr->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, width);
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};

//Fitness function - Ruleset - Static/Repeating or Gliders
auto fit_fun_static_rep_classic_ruleset = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    std::vector<unsigned char> tmp;
    double max = 0;
    double score = 0;
    size_t idx = 0;
    auto iter = icFitnessMapPtr->rbegin();
    for(size_t i = 0; i < numBestCollaborators; i++){  
        ca.Reset(); 
        if(icFitnessMapPtr->size() > i){
            idx = iter->second;
            iter++;
        }
        else{
            idx = randPtr->GetUInt(0, icWorldPtr->GetSize());   
        }
        std::vector<unsigned char> tmp = BitstringToVec(icWorldPtr->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, width);
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){  
        ca.Reset(); 
        idx = randPtr->GetUInt(0, icWorldPtr->GetSize());   
        std::vector<unsigned char> tmp = BitstringToVec(icWorldPtr->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, width);
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};
