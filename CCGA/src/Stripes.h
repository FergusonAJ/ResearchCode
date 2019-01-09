#pragma once
#include "OrganismShared.h"
#include "Evolve/World.h"
#include "./Quads.h"


//Note: Stripes treatment does reuse code quads and classic


//Print functions
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_stripe_ic = [](std::vector<bool> & org, std::ostream & os) {
    for(int y = 0; y < subHeight / 4; y++){
        for(int x = 0; x < subWidth; x++){
            os << (org[x + y * subWidth]? "1" : "0") << " ";
        }
        os << std::endl;
    }
    os << std::endl;
};

//IC Fitness Functions - End State Matching
auto fit_fun_match_stripe_ic_1 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //1
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_match_stripe_ic_2 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //2
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score 
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_match_stripe_ic_3 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //3
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score 
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_match_stripe_ic_4 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //4
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //Score 
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};

//IC Fitness Functions - Statis/Repeating Structures
auto fit_fun_static_rep_stripe_ic_1 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //1
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_static_rep_stripe_ic_2 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //2
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score 
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_static_rep_stripe_ic_3 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //3
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score 
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_static_rep_stripe_ic_4 = [](std::vector<bool> & org){
    ca.Reset();
    std::vector<unsigned char> tmp = BitstringToVec(org);
    double max = 0;
    double score = 0;
    size_t idx = 0;
    for(size_t i = 0; i < numCollaborators; i++){
        ca.Reset();
        //4
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4, subWidth);
        //Ruleset
        idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //Score 
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};

//Ruleset Fitness Functions
auto fit_fun_match_stripe_ruleset = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    double max = 0;
    double score = 0;
    size_t idx = 0;
    std::vector<unsigned char> tmp;
    for(size_t i = 0; i < numCollaborators; i++){  
        ca.Reset();
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score
        score = GetMatchFitness();
        if(score > max)
            max = score;
    }
    return max;
};
auto fit_fun_static_rep_stripe_ruleset = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    double max = 0;
    double score = 0;
    size_t idx = 0;
    std::vector<unsigned char> tmp;
    for(size_t i = 0; i < numCollaborators; i++){  
        ca.Reset();
        //1 
        idx = randPtr->GetUInt(0, icWorldPtrs[0]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth);
        //2 
        idx = randPtr->GetUInt(0, icWorldPtrs[1]->GetSize());   
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 4, subWidth);
        //3 
        idx = randPtr->GetUInt(0, icWorldPtrs[2]->GetSize());   
        BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth);
        //4 
        idx = randPtr->GetUInt(0, icWorldPtrs[3]->GetSize());   
        BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * subHeight / 4,  subWidth);
        //Score
        score = GetStaticRepFitness();
        if(score > max)
            max = score;
    }
    return max;
};
